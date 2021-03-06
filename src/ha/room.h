#ifndef _HA_ROOM_H_
#define _HA_ROOM_H_

#include <stdint.h>

#include "devices.h"

typedef enum {
	HA_ROOM_NONE = 0x00U,

	HA_ROOM_ENTRANCE,
	HA_ROOM_LIVING_ROOM,
	HA_ROOM_KITCHEN,
	HA_ROOM_DINING_ROOM,
	HA_ROOM_STAIRS,
	HA_ROOM_BATHROOM,
	HA_ROOM_TOILET,
	HA_ROOM_STORE_ROOM,

	HA_ROOM_GARAGE_LEFT,
	HA_ROOM_GARAGE_RIGHT,
	HA_ROOM_GARAGE_BACK,
	HA_ROOM_WORKSHOP,
	HA_ROOM_BOILER_ROOM,
	HA_ROOM_LAUNDRY,

	HA_ROOM_FLOOR_CORRIDOR,
	HA_ROOM_FLOOR_BATHROOM,
	HA_ROOM_FLOOR_TOILET,
	HA_ROOM_OFFICE,
	HA_ROOM_GAMES_ROOM,
	HA_ROOM_BEDROOM_1,
	HA_ROOM_BEDROOM_1_DRESSING,
	HA_ROOM_BEDROOM_2,
	HA_ROOM_BEDROOM_3,
	HA_ROOM_FLOOR_STAIRS,

	HA_ROOM_LOFT_OFFICE,
	HA_ROOM_LOFT_KITCHEN,
	HA_ROOM_LOFT_BEDROOM,
	HA_ROOM_LOFT_DRESSING,

	HA_ROOM_ATTIC_SOUTH,
	HA_ROOM_ATTIC_NORTH,
} room_id_t;

struct ha_room
{
	const char *name;
};

room_id_t ha_get_device_room(ha_dev_t *const dev);

#endif