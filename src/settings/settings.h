#ifndef _SETTINGS_H_
#define _SETTINGS_H_

#include <stdint.h>

typedef enum {
	SETTINGS_SYSTEM_ID = 0x00,
	SETTINGS_NETWORK_ID = 0x01,
	SETTINGS_BLE_ID = 0x02,
	SETTINGS_CAN_ID = 0x03,
	SETTINGS_AWS_ID = 0x04,
	SETTINGS_HA_ID = 0x05
} settings_id_t;

struct settings_system
{

};

int settings_init(void);

#endif