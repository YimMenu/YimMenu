#pragma once
#include "core/enums.hpp"

struct speedo_meter {
	big::SpeedoMeter id;
	const char name[16];
};

const speedo_meter speedo_meters[] = {
	{ big::SpeedoMeter::DISABLED, "Disabled" },
	{ big::SpeedoMeter::KMH, "km/h" },
	{ big::SpeedoMeter::MPH, "mph" }
};