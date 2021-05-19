#pragma once
#include "enums.hpp"

#ifndef GLOBALS_H
#define GLOBALS_H

struct globals {
	struct self {
		bool noclip = false;
	};

	struct weapons {
		big::CustomWeapons custom_weapon = big::CustomWeapons::NONE;
	};

	self self{};
	weapons weapons{};
};

extern struct globals g;
#endif // !GLOBALS_H