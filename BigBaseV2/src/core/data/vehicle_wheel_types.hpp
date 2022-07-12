#pragma once
#include "gta\VehicleValues.h"

struct vehicle_wheel_type {
	WheelTypes type;
	const char name[16];
};

std::map<int, std::string> vehicle_wheel_types = {
	{ WHEEL_TYPE_SPORT, "Sport" },
	{ WHEEL_TYPE_MUSCLE, "Muscle" },
	{ WHEEL_TYPE_LOWRIDER, "Lowrider" },
	{ WHEEL_TYPE_SUV, "SUV" },
	{ WHEEL_TYPE_OFFROAD, "Offroad" },
	{ WHEEL_TYPE_TUNER, "Tuner" },
	{ WHEEL_TYPE_BIKEWHEELS, "Bike Wheels" },
	{ WHEEL_TYPE_HIGHEND, "High End" },
	{ WHEEL_TYPE_BENNYS_ORIGINAL, "Bennys Original" },
	{ WHEEL_TYPE_BENNYS_BESPOKE, "Bennys Bespoke" },
	{ WHEEL_TYPE_F1, "F1" }
};
