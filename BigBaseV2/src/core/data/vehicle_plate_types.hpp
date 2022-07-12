#pragma once
#include "gta\VehicleValues.h"

struct vehicle_plate_type {
	PlateTextIndexs type;
	const char name[16];
};


#define PLATE_TYPE_SIZE 6
vehicle_plate_type vehicle_plate_types[PLATE_TYPE_SIZE] = {
	{ PLATE_BLUEONWHITE1, "Blue on White 1" },
	{ PLATE_BLUEONWHITE2, "Blue on White 2" },
	{ PLATE_BLUEONWHITE3, "Blue on White 3" },
	{ PLATE_YELLOWONBLACK, "Yellow on Black" },
	{ PLATE_YELLOWONBLUE, "Yellow on Blue" },
	{ PLATE_YANKTON, "Yankton" }
};
