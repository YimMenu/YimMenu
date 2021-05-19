#pragma once
#include "enums.hpp"

#ifndef GLOBALS_H
#define GLOBALS_H

using namespace big;
struct globals {
	struct self {
		bool godmode = false;
		bool noclip = false;
	};

	struct vehicle {
		SpeedoMeter speedo_meter = SpeedoMeter::DISABLED;
	};

	struct weapons {
		CustomWeapon custom_weapon = CustomWeapon::NONE;
	};

	self self{};
	vehicle vehicle{};
	weapons weapons{};
};

extern struct globals g;
#endif // !GLOBALS_H