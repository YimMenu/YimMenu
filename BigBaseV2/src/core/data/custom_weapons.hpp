#pragma once
#include "core/enums.hpp"

struct custom_weapon {
	big::CustomWeapon id;
	const char name[16];
};

const custom_weapon custom_weapons[] = {
	{ big::CustomWeapon::NONE, "No weapon" },
	{ big::CustomWeapon::GRAVITY_GUN, "Gravity Gun" },
	{ big::CustomWeapon::REPAIR_GUN, "Repair Gun" }
};