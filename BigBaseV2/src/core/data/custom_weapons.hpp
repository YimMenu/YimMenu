#pragma once
#include "core/enums.hpp"

struct custom_weapon {
	big::CustomWeapons id;
	const char name[16];
};

const custom_weapon custom_weapons[] = {
	{ big::CustomWeapons::NONE, "No weapon" },
	{ big::CustomWeapons::GRAVITY_GUN, "Gravity Gun" }
};