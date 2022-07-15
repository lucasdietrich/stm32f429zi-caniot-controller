#include <zephyr.h>

#include <device.h>
#include <drivers/sensor.h>

#include "net_interface.h"
#include "net_time.h"
#include "crypto.h"

#include "userio/leds.h"
#include "userio/button.h"

#ifndef CONFIG_BOARD_QEMU_X86
#include "ha/devices.h"
#include "ha/ble_controller.h"
#endif /* CONFIG_BOARD_QEMU_X86 */

#include <mbedtls/memory_buffer_alloc.h>

#include <stdio.h>

#include <logging/log.h>
LOG_MODULE_REGISTER(main, LOG_LEVEL_NONE);

#if DT_HAS_COMPAT_STATUS_OKAY(st_stm32_temp)
#define TEMP_NODE DT_INST(0, st_stm32_temp)
#else
// #error "Could not find a compatible temperature sensor"
#endif

#ifdef TEMP_NODE
static const struct device *die_temp_dev = DEVICE_DT_GET(TEMP_NODE);

static int die_temp_dev_init(void)
{
	if (!device_is_ready(die_temp_dev)) {
		LOG_ERR("(%p) Temperature sensor is not ready", die_temp_dev);
		return -EIO;
	}

	return 0U;
}

static int die_temp_fetch(void)
{
	int rc;
	struct sensor_value val;

	rc = sensor_sample_fetch(die_temp_dev);
	if (rc) {
		LOG_ERR("Failed to fetch sample (%d)", rc);
		goto exit;
	}

	rc = sensor_channel_get(die_temp_dev, SENSOR_CHAN_DIE_TEMP, &val);
	if (rc) {
		LOG_ERR("Failed to get data (%d)", rc);
		goto exit;
	}

	const float temperature = (float)sensor_value_to_double(&val);
	if (temperature > -276.0) {
		ha_dev_register_die_temperature(net_time_get(), temperature);

		LOG_DBG("Current DIE temperature: %.1f °C ", temperature);
	} else {
		LOG_WRN("Invalid DIE temperature: %.1f °C", temperature);
	}

exit:
	return rc;
}

#endif /* TEMP_NODE */

static void debug_mbedtls_memory(void)
{
        size_t cur_used, cur_blocks, max_used, max_blocks;
        mbedtls_memory_buffer_alloc_cur_get(&cur_used, &cur_blocks);
        mbedtls_memory_buffer_alloc_max_get(&max_used, &max_blocks);

        LOG_DBG("MAX %u (%u) CUR %u (%u)", max_used,
                max_blocks, cur_used, cur_blocks);
}

void main(void)
{
#ifndef CONFIG_BOARD_QEMU_X86
	leds_init();
	button_init();
#endif
	crypto_mbedtls_heap_init();
	net_interface_init();

#ifndef CONFIG_BOARD_QEMU_X86
	ha_ble_controller_init();
#endif /* CONFIG_BOARD_QEMU_X86 */

#ifdef TEMP_NODE
	die_temp_dev_init();
#endif /* TEMP_NODE */

	printk("Starting...\n");

	uint32_t counter = 0;

	for (;;) {

		/* 1 second tasks */

		/* 10 second tasks */
		if (counter % 10 == 0) {
#ifdef TEMP_NODE
			die_temp_fetch();
#endif /* TEMP_NODE */
		}

		/* 1min tasks */
		if (counter % 60 == 0) {

		}

		/* 10min tasks but 5 seconds after startup*/
		if (counter % 600 == 5) {
			net_time_show();
			debug_mbedtls_memory();
		}

		counter++;
		k_msleep(1000);
	}
}
