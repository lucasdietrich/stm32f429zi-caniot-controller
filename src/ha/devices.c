#include <zephyr.h>

#include "devices.h"

#include "uart_ipc/ipc_frame.h"
#include "uart_ipc/ipc.h"

#include "ble/xiaomi_record.h"
#include "net_time.h"

#include "caniot/datatype.h"

#include <logging/log.h>
LOG_MODULE_REGISTER(ha_dev, LOG_LEVEL_NONE);

/*___________________________________________________________________________*/

struct {
	struct k_mutex mutex;
	ha_dev_t list[20];
	uint8_t count;
} devices = {
	.mutex = Z_MUTEX_INITIALIZER(devices.mutex),
	.count = 0U
};

typedef int (*mac_cmp_func_t)(const ha_dev_mac_addr_t *a,
			      const ha_dev_mac_addr_t *b);

static int internal_caniot_addr_cmp(const ha_dev_mac_addr_t *a,
				    const ha_dev_mac_addr_t *b)
{
	return caniot_deviceid_cmp(a->caniot, b->caniot);
}

static int internal_ble_addr_cmp(const ha_dev_mac_addr_t *a,
				 const ha_dev_mac_addr_t *b)
{
	return bt_addr_le_cmp(&a->ble, &b->ble);
}

static mac_cmp_func_t get_mac_cmp_func(ha_dev_medium_type_t medium)
{
	switch (medium) {
	case HA_DEV_MEDIUM_BLE:
		return internal_ble_addr_cmp;
	case HA_DEV_MEDIUM_CAN:
		return internal_caniot_addr_cmp;
	default:
		return NULL;
	}	
}

static bool mac_valid(const ha_dev_mac_t *mac)
{
	return get_mac_cmp_func(mac->medium) != NULL;
}

static int mac_cmp(const ha_dev_mac_t *m1, const ha_dev_mac_t *m2)
{
	int ret = -EINVAL;

	mac_cmp_func_t cmpf = get_mac_cmp_func(m1->medium);

	if (cmpf != NULL) {
		ret = cmpf(&m1->addr, &m2->addr);
	}

	return ret;
}

static ha_dev_t *get_device_by_mac(const ha_dev_mac_t *mac)
{
	ha_dev_t *device = NULL;

	for (ha_dev_t *dev = devices.list;
	     dev < devices.list + devices.count;
	     dev++) {

		if (mac_cmp(mac, &dev->addr.mac) == 0) {
			device = dev;
			break;
		}
	}

	return device;
}

static ha_dev_t *get_first_device_by_type(ha_dev_type_t type)
{
	ha_dev_t *device = NULL;

	for (ha_dev_t *dev = devices.list;
	     dev < devices.list + devices.count;
	     dev++) {
		if (dev->addr.type == type) {
			device = dev;
			break;
		}
	}

	return device;
}

bool ha_dev_valid(ha_dev_t *const dev)
{
	return (dev != NULL) && (mac_valid(&dev->addr.mac) == true);
}

static ha_dev_t *ha_dev_get(const ha_dev_addr_t *addr)
{
	ha_dev_t *device = NULL;

	if (mac_valid(&addr->mac)) {
		/* Get device by address if possible */
		device = get_device_by_mac(&addr->mac);
	} else {
		/* if medium type is not set, device should be
		* differienciated using their device_type */
		device = get_first_device_by_type(addr->type);
	}

	return device;
}

int ha_dev_addr_cmp(const ha_dev_addr_t *a,
		    const ha_dev_addr_t *b)
{
	if (mac_valid(&a->mac) && mac_valid(&b->mac)) {
		return mac_cmp(&a->mac, &b->mac);
	} else {
		return a->type - b->type;
	}
}

static void ha_dev_clear(ha_dev_t *dev)
{
	memset(dev, 0U, sizeof(*dev));
}

/**
 * @brief Register a new device in the list, addr duplicates are not verified
 *
 * @param medium
 * @param type
 * @param addr
 * @return int
 */
static ha_dev_t *ha_dev_register(ha_dev_addr_t *addr)
{
	if (devices.count >= ARRAY_SIZE(devices.list)) {
		return NULL;
	}

	ha_dev_t *dev = devices.list + devices.count;

	ha_dev_clear(dev);

	dev->addr = *addr;
	dev->registered_timestamp = net_time_get();

	devices.count++;

	return dev;
}

static ha_dev_t *ha_dev_get_or_register(ha_dev_addr_t *addr)
{
	ha_dev_t *dev;

	dev = ha_dev_get(addr);

	if (dev == NULL) {
		dev = ha_dev_register(addr);
	}

	return dev;
}

static bool ha_dev_match_filter(ha_dev_t *dev, ha_dev_filter_t *filter)
{
	if (dev == NULL) {
		return false;
	}

	if (filter == NULL) {
		return true;
	}

	if (filter->type == HA_DEV_FILTER_NONE) {
		return true;
	}

	switch (filter->type) {
	case HA_DEV_FILTER_MEDIUM:
		return dev->addr.mac.medium == filter->data.medium;
	case HA_DEV_FILTER_DEVICE_TYPE:
		return dev->addr.type == filter->data.device_type;
	case HA_DEV_FILTER_MEASUREMENTS_TIMESTAMP:
		return dev->data.measurements_timestamp >= filter->data.timestamp;
	default:
		LOG_WRN("Unknown filter type %hhu", filter->type);
		break;
	}

	return false;
}

/*___________________________________________________________________________*/

size_t ha_dev_iterate(void (*callback)(ha_dev_t *dev,
				       void *user_data),
		      ha_dev_filter_t *filter,
		      void *user_data)
{
	k_mutex_lock(&devices.mutex, K_FOREVER);

	size_t count = 0U;

	for (ha_dev_t *dev = devices.list;
	     dev < devices.list + devices.count;
	     dev++) {
		if (ha_dev_match_filter(dev, filter)) {
			callback(dev, user_data);
			count++;
		}
	}

	k_mutex_unlock(&devices.mutex);

	return count;
}

size_t ha_dev_xiaomi_iterate(void (*callback)(ha_dev_t *dev,
					      void *user_data),
			     void *user_data)
{
	ha_dev_filter_t filter = {
		.type = HA_DEV_FILTER_DEVICE_TYPE,
		.data = {
			.device_type = HA_DEV_TYPE_XIAOMI_MIJIA
		}
	};

	return ha_dev_iterate(callback, &filter, user_data);
}

/*___________________________________________________________________________*/

static int handle_ble_xiaomi_record(xiaomi_record_t *rec)
{
	/* check if device already exists */
	ha_dev_addr_t record_addr;
	record_addr.type = HA_DEV_TYPE_XIAOMI_MIJIA;
	record_addr.mac.medium = HA_DEV_MEDIUM_BLE;
	bt_addr_le_copy(&record_addr.mac.addr.ble, &rec->addr);

	ha_dev_t *dev = ha_dev_get_or_register(&record_addr);
	if (dev == NULL) {
		LOG_ERR("Failed to register device, list full %hhu / %lu",
			devices.count,
			ARRAY_SIZE(devices.list));
		return -ENOMEM;
	}

	/* device does exist now, update it measurements */
	dev->data.measurements_timestamp = rec->time;
	dev->data.xiaomi.temperature.type = HA_DEV_SENSOR_TYPE_EMBEDDED;
	dev->data.xiaomi.temperature.value = rec->measurements.temperature;
	dev->data.xiaomi.humidity = rec->measurements.humidity;
	dev->data.xiaomi.battery_level = rec->measurements.battery;

	return 0;
}

int ha_register_xiaomi_from_dataframe(xiaomi_dataframe_t *frame)
{
	int ret = 0;
	char addr_str[BT_ADDR_LE_STR_LEN];

	// show dataframe records
	LOG_DBG("Received BLE Xiaomi records count: %u, frame_time: %u",
		frame->count, frame->time);

	uint32_t frame_ref_time = frame->time;
	uint32_t now = net_time_get();

	k_mutex_lock(&devices.mutex, K_FOREVER);

	// Show all records
	for (uint8_t i = 0; i < frame->count; i++) {
		xiaomi_record_t *const rec = &frame->records[i];

		bt_addr_le_to_str(&rec->addr,
				  addr_str,
				  sizeof(addr_str));

		int32_t record_rel_time = rec->time - frame_ref_time;
		uint32_t record_timestamp = now + record_rel_time;
		rec->time = record_timestamp;

		ret = handle_ble_xiaomi_record(rec);
		if (ret != 0) {
			goto exit;
		}


		/* Show BLE address, temperature, humidity, battery
		 *   Only raw values are showed in debug because, 
		 *   there is no formatting (e.g. float)
		 */
		LOG_DBG("BLE Xiaomi record %u [%d s]: addr: %s, " \
			"temp: %d°C, hum: %u %%, bat: %u mV",
			i, record_rel_time,
			log_strdup(addr_str),
			(int32_t)rec->measurements.temperature,
			(uint32_t)rec->measurements.humidity,
			(uint32_t)rec->measurements.battery);
	}

exit:
	k_mutex_unlock(&devices.mutex);

	return ret;
}

int ha_dev_register_die_temperature(uint32_t timestamp,
				    float die_temperature)
{
	int ret = 0;

	k_mutex_lock(&devices.mutex, K_FOREVER);

	/* check if device already exists */
	ha_dev_addr_t record_addr;
	record_addr.type = HA_DEV_TYPE_NUCLEO_F429ZI;
	record_addr.mac.medium = HA_DEV_MEDIUM_NONE;

	ha_dev_t *dev = ha_dev_get_or_register(&record_addr);
	if (dev == NULL) {
		LOG_ERR("Failed to register device, list full %hhu / %lu",
			devices.count,
			ARRAY_SIZE(devices.list));
		ret = -ENOMEM;
		goto exit;
	}

	/* device does exist now, update it measurements */
	dev->data.measurements_timestamp = timestamp;
	dev->data.nucleo_f429zi.die_temperature = die_temperature;

exit:
	k_mutex_unlock(&devices.mutex);

	return ret;
}

static int save_caniot_temperature(ha_dev_t *dev,
				   uint8_t temp_index,
				   uint16_t temperature,
				   ha_dev_sensor_type_t sens_type)
{
	int ret = -EINVAL;

	if ((dev != NULL) &&
	    (dev->addr.type == HA_DEV_TYPE_CANIOT) &&
	    (temp_index < ARRAY_SIZE(dev->data.caniot.temperatures))) {
		if (CANIOT_DT_VALID_T10_TEMP(temperature)) {
			dev->data.caniot.temperatures[temp_index].type = sens_type;
			dev->data.caniot.temperatures[temp_index].value =
				caniot_dt_T10_to_T16(temperature);
			ret = 1U;
		} else {
			dev->data.caniot.temperatures[temp_index].type =
				HA_DEV_SENSOR_TYPE_NONE;
			return 0U;
		}

		ret = 0;
	}

	return ret;
}

int ha_dev_register_caniot_telemetry(uint32_t timestamp,
				     union deviceid did,
				     struct caniot_board_control_telemetry *data)
{
	int ret = 0;

	k_mutex_lock(&devices.mutex, K_FOREVER);

	/* check if device already exists */
	ha_dev_addr_t addr;
	addr.type = HA_DEV_TYPE_CANIOT;
	addr.mac.addr.caniot = did;
	addr.mac.medium = HA_DEV_MEDIUM_CAN;

	ha_dev_t *dev = ha_dev_get_or_register(&addr);
	if (dev == NULL) {
		LOG_ERR("Failed to register device, list full %hhu / %lu",
			devices.count,
			ARRAY_SIZE(devices.list));
		ret = -ENOMEM;
		goto exit;
	}

	/* device does exist now, update it measurements */
	dev->data.measurements_timestamp = timestamp;

	save_caniot_temperature(dev, 0U, data->int_temperature,
				HA_DEV_SENSOR_TYPE_EMBEDDED);
	save_caniot_temperature(dev, 1U, data->ext_temperature,
				HA_DEV_SENSOR_TYPE_EMBEDDED);
	// save_caniot_temperature(dev, 2U, data->ext_temperature2,
	// 			HA_DEV_SENSOR_TYPE_EMBEDDED);

	/* todo board IO */

	LOG_INF("Registered CANIOT record for device 0x%hhx", did.val);

exit:
	k_mutex_unlock(&devices.mutex);

	return ret;
}

/*___________________________________________________________________________*/


K_MSGQ_DEFINE(ipc_ble_msgq, sizeof(ipc_frame_t), 1U, 4U);
struct k_poll_event ipc_event =
	K_POLL_EVENT_STATIC_INITIALIZER(K_POLL_TYPE_MSGQ_DATA_AVAILABLE,
					K_POLL_MODE_NOTIFY_ONLY,
					&ipc_ble_msgq, 0);
static struct k_work_poll ipc_ble_work;

static void ipc_work_handler(struct k_work *work)
{
	int ret;

	ipc_frame_t frame;

	/* process all available messages */
	while (k_msgq_get(&ipc_ble_msgq, &frame, K_NO_WAIT) == 0U) {
		ret = ha_register_xiaomi_from_dataframe(
			(xiaomi_dataframe_t *)frame.data.buf);
		if (ret != 0) {
			LOG_ERR("Failed to handle BLE Xiaomi record, err: %d",
				ret);
		}
	}

	ipc_event.state = K_POLL_STATE_NOT_READY;

	/* re-register for next event */
	ret = k_work_poll_submit(&ipc_ble_work, &ipc_event, 1U, K_FOREVER);
	if (ret != 0) {
		LOG_ERR("Failed to resubmit work %p to poll queue: %d", work, ret);
	}
}


int ha_dev_init(void)
{
	int ret = net_time_wait_synced(K_FOREVER);
	if (ret == 0) {
		ipc_attach_rx_msgq(&ipc_ble_msgq);

		k_work_poll_init(&ipc_ble_work, ipc_work_handler);
		k_work_poll_submit(&ipc_ble_work, &ipc_event, 1U, K_FOREVER);

	} else {
		LOG_ERR("Time not synced ! ret = %d", ret);
	}

	return ret;
}