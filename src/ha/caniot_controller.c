#include <stdio.h>

#include <caniot/caniot.h>
#include <caniot/controller.h>
#include <caniot/datatype.h>

#include <drivers/can.h>
#include <device.h>

#include <sys/dlist.h>
#include <assert.h>

#include "caniot_controller.h"
#include "devices.h"
#include "net_time.h"
#include "utils.h"
#include "../utils.h"

#include <logging/log.h>
LOG_MODULE_REGISTER(caniot, LOG_LEVEL_WRN);

CAN_DEFINE_MSGQ(can_rxq, 4U);

const struct device *can_dev = DEVICE_DT_GET(DT_NODELABEL(can1));

/* initialized with 0 */
static ha_ciot_ctrl_did_cb_t did_callbacks[CANIOT_DID_MAX_VALUE];


static void thread(void *_a, void *_b, void *_c);

K_THREAD_DEFINE(ha_ciot_thread, 0x800, thread, NULL, NULL, NULL,
		K_PRIO_COOP(2), 0U, 0U);

static int z_can_init(void)
{
	/* wait for device ready */
        while (!device_is_ready(can_dev)) {
                LOG_WRN("CAN: Device %s not ready.\n", can_dev->name);
                k_sleep(K_SECONDS(1));
        }

	/* attach message q */
	struct zcan_filter filter = {
		.id_type = CAN_ID_STD, /* currently we ignore extended IDs */
	};

	int ret = can_attach_msgq(can_dev, &can_rxq, &filter);
	if (ret) {
		LOG_ERR("can_attach_msgq failed: %d", ret);
	}

	return ret;
}

static int z_can_send(const struct caniot_frame *frame,
		      uint32_t delay_ms)
{
	__ASSERT(frame != NULL, "frame is NULL");

	struct zcan_frame zframe;
	caniot_to_zcan(&zframe, frame);

	return can_send(can_dev, &zframe, K_FOREVER, NULL, NULL);
}

const struct caniot_drivers_api driv =
{
	.entropy = NULL,
	.get_time = NULL,
	.set_time = NULL,
	.recv = NULL,
	.send = z_can_send
};

static struct caniot_controller ctrl;

K_FIFO_DEFINE(fifo_queries);
// K_FIFO_DEFINE(fifo_waiting);

typedef enum {
	SYNCQ_UNDEFINED = 0,
	SYNCQ_WAITING,
	SYNCQ_QUEUED,
	SYNCQ_ANSWERED,
	SYNCQ_ALREADY,
	SYNCQ_NOWAIT,
	SYNCQ_TIMEOUT,
	SYNCQ_CANIOT_ERROR,
	SYNCQ_ERROR,
} syncq_status_t;

// convert syncq_status_t to string
static const char *syncq_status_to_str(syncq_status_t event)
{
	switch (event) {
	case SYNCQ_WAITING:
		return "SYNCQ_WAITING";
	case SYNCQ_QUEUED:
		return "SYNCQ_QUEUED";
	case SYNCQ_ANSWERED:
		return "SYNCQ_ANSWERED";
	case SYNCQ_ALREADY:
		return "SYNCQ_ALREADY";
	case SYNCQ_NOWAIT:
		return "SYNCQ_NOWAIT";
	case SYNCQ_TIMEOUT:
		return "SYNCQ_TIMEOUT";
	case SYNCQ_CANIOT_ERROR:
		return "SYNCQ_CANIOT_ERROR";
	case SYNCQ_ERROR:
		return "SYNCQ_ERROR";
	case SYNCQ_UNDEFINED:
	default:
		return "SYNCQ_UNDEFINED";
	}
}

struct syncq
{
	union {
		void *_tie; /* for k_fifo_put */
		sys_dnode_t _node;
	};
	
	struct k_sem _sem;

	/* query waiting to be queued */
	syncq_status_t status;

	/* query queued to be answered */
	struct caniot_frame *query;

	/* buffer which will contain the response on success */
	struct caniot_frame *response;

	/* query timeout */
	uint32_t timeout;

	/* TODO union { */

	/* handle of the query when queued */
	uint8_t handle;

	/* query pending on this device */
	caniot_did_t did;

	/* }; */

	union {
		/* contain update on creation */
		uint32_t uptime;

		/* and duration when answered (or timeout) */
		uint32_t delta;
	};	
};

K_MEM_SLAB_DEFINE(sq_pool, sizeof(struct syncq),
		  CANIOT_MAX_PENDING_QUERIES, 4U);


/* requires ~80B of stack */
void log_caniot_frame(const struct caniot_frame *frame)
{
	char repr[64];
	int ret = caniot_explain_frame_str(frame, repr, sizeof(repr));
	if (ret > 0) {
		LOG_INF("%s", log_strdup(repr));
	} else {
		LOG_WRN("Failed to encode frame, ret = %d", ret);
	}
}

bool event_cb(const caniot_controller_event_t *ev,
	      void *user_data)
{
	int ret;

	bool response_is_set = false;

	switch (ev->status) {
	case CANIOT_CONTROLLER_EVENT_STATUS_OK:
	{
		const struct caniot_frame *resp = ev->response;
		__ASSERT(resp != NULL, "response is NULL");

		response_is_set = true;

		if ((resp->id.type == CANIOT_FRAME_TYPE_TELEMETRY) &&
		    (resp->id.endpoint == CANIOT_ENDPOINT_BOARD_CONTROL)) {
			if (resp->len != 8U) {
				LOG_WRN("Expected length for board control "
					"telemetry is 8, got %d",
					resp->len);
			}

			ret = ha_dev_register_caniot_telemetry(
				net_time_get(),
				CANIOT_DID(resp->id.cls, resp->id.sid),
				AS_BOARD_CONTROL_TELEMETRY(resp->buf)
			);
		}
	}
	break;
	case CANIOT_CONTROLLER_EVENT_STATUS_ERROR:
		response_is_set = true;
		break;
	case CANIOT_CONTROLLER_EVENT_STATUS_TIMEOUT:
		break;
	case CANIOT_CONTROLLER_EVENT_STATUS_CANCELLED:
		break;
	default:
		break;
	}

	/* call associated general callback */
	if ((response_is_set == true) && (did_callbacks[ev->did] != NULL)) {
		__ASSERT(ev->response != NULL, "response is NULL");

		LOG_DBG("callback set for did %d : %p", ev->did, did_callbacks[ev->did]);

		/* implement a user_data mechanism to pass the context for example*/
		did_callbacks[ev->did](ev->did, ev->response, NULL);
	}

	struct syncq *const qx = ev->user_data;
	if ((qx != NULL) &&
	    (ev->context == CANIOT_CONTROLLER_EVENT_CONTEXT_QUERY)) {
		LOG_DBG("Query %p answered", qx);

		if (ev->status == CANIOT_CONTROLLER_EVENT_STATUS_OK) {
			qx->status = SYNCQ_ANSWERED;
		} else if (ev->status == CANIOT_CONTROLLER_EVENT_STATUS_ERROR) {
			qx->status = SYNCQ_CANIOT_ERROR;
		} else {
			qx->status = SYNCQ_TIMEOUT;
		}

		if (response_is_set == true) {
			memcpy(qx->response, ev->response, sizeof(struct caniot_frame));
		}

		qx->delta = k_uptime_delta32(&qx->uptime);
		k_sem_give(&qx->_sem);
	}

	return true;
}

static void thread(void *_a, void *_b, void *_c)
{
	ARG_UNUSED(_a);
	ARG_UNUSED(_b);
	ARG_UNUSED(_c);

	int ret;
	static struct caniot_frame frame;
	static struct zcan_frame zframe;

	z_can_init();

	caniot_controller_driv_init(&ctrl, &driv, event_cb, NULL);

	struct k_poll_event events[] = {
		K_POLL_EVENT_STATIC_INITIALIZER(
			K_POLL_TYPE_MSGQ_DATA_AVAILABLE,
			K_POLL_MODE_NOTIFY_ONLY,
			&can_rxq, 0),
		K_POLL_EVENT_STATIC_INITIALIZER(
			K_POLL_TYPE_FIFO_DATA_AVAILABLE,
			K_POLL_MODE_NOTIFY_ONLY,
			&fifo_queries, 0),
	};

	uint32_t reftime = k_uptime_get_32();

	while (1) {
		const uint32_t timeout_ms = caniot_controller_next_timeout(&ctrl);
		LOG_DBG("k_poll(., ., %u)", timeout_ms);
		ret = k_poll(events, ARRAY_SIZE(events), K_MSEC(timeout_ms));
		if (ret == 0) {
			struct caniot_frame *resp = NULL;

			/* events */
			if (events[0].state == K_POLL_STATE_MSGQ_DATA_AVAILABLE) {
				ret = k_msgq_get(&can_rxq, &zframe, K_NO_WAIT);
				if (ret == 0) {
					zcan_to_caniot(&zframe, &frame);
					log_caniot_frame(&frame);
					resp = &frame;
				}
			}

			/* we need to process the response before sending a query,
			 * otherwise the query could timeout immediately because 
			 * the timeout queue was not shifted before
			 */
			const uint32_t delta = k_uptime_delta32(&reftime);
			caniot_controller_process_single(&ctrl, delta, resp);

			if (events[1].state == K_POLL_STATE_FIFO_DATA_AVAILABLE) {
				struct syncq *qx = k_fifo_get(&fifo_queries, K_NO_WAIT);
				if (qx != NULL) {
					__ASSERT_NO_MSG(qx->timeout != CANIOT_TIMEOUT_FOREVER);

					ret = caniot_controller_query(&ctrl, qx->did,
									   qx->query, qx->timeout);
					log_caniot_frame(qx->query);

					if (ret > 0) {
						/* pending query registered */
						qx->handle = (uint8_t) ret;

						caniot_controller_handle_set_user_data(&ctrl, qx->handle, qx);

						LOG_DBG("Query %p registered", qx);
					} else {
						if (ret == 0) {
							qx->status = SYNCQ_NOWAIT;

						} else if (ret == -CANIOT_EAGAIN) {
							qx->status = SYNCQ_ALREADY;
							LOG_WRN("Query SYNCQ_ALREADY pending: %d", qx->did);
							/* requeue the frame for later */
						} else if (ret < 0) {
							qx->status = SYNCQ_ERROR;
							LOG_ERR("Query SYNCQ_ERROR : %d", qx->did);
						} else {
							qx->status = SYNCQ_UNDEFINED;
						}

						qx->delta = k_uptime_delta32(&qx->uptime);

						k_sem_give(&qx->_sem);
					}
				}
			}
		} else if (ret == -EAGAIN) {
			const uint32_t delta = k_uptime_delta32(&reftime);
			caniot_controller_process_single(&ctrl, delta, NULL);
		} else {
			LOG_ERR("k_poll failed: %d", ret);
			break;
		}

		events[0].state = K_POLL_STATE_NOT_READY;
		events[1].state = K_POLL_STATE_NOT_READY;
	}
}

int ha_ciot_ctrl_query(struct caniot_frame *__RESTRICT req,
		       struct caniot_frame *__RESTRICT resp,
		       caniot_did_t did,
		       uint32_t timeout)
{
	int ret = -EINVAL;
	struct syncq *qx = NULL;

	if ((req == NULL) || (resp == NULL)) {
		goto exit;
	}

	/* forever wait not supported */
	if (timeout == CANIOT_TIMEOUT_FOREVER) {
		goto exit;
	} else if (timeout == 0) {
		LOG_WRN("Timeout=%d not recommended, use ha_ciot_ctrl_send() instead", 0);
	}

	/* alloc and prepare */
	if (k_mem_slab_alloc(&sq_pool, (void **)&qx, K_NO_WAIT) != 0) {
		goto exit;
	}

	k_sem_init(&qx->_sem, 0, 1);
	qx->did = did;
	qx->query = req;
	qx->response = resp;
	qx->timeout = timeout;
	qx->uptime = k_uptime_get_32();

	/* queue synchronous query */
	k_fifo_put(&fifo_queries, qx);

	/* wait for response */
	ret = k_sem_take(&qx->_sem, K_MSEC(qx->timeout + 10000U));
	__ASSERT(ret == 0, "k_sem_take shouldn't timeout");

	if (qx->status == SYNCQ_ANSWERED) {
		ret = 0;
		LOG_INF("Sync query completed in %u ms with status : %s",
			qx->delta, syncq_status_to_str(qx->status));
	} else { /* other error */
		ret = -1;
		LOG_WRN("Sync query completed in %u ms with status : %s",
			qx->delta, syncq_status_to_str(qx->status));
	}

exit:
	/* cleanup */
	if (qx != NULL) {
		k_mem_slab_free(&sq_pool, (void **)&qx);
	}

	return ret;
}

int ha_ciot_ctrl_send(struct caniot_frame *__RESTRICT req,
		      caniot_did_t did)
{
	/* this is safe because no context is allocated */
	return caniot_controller_send(&ctrl, did, req);
}