#pragma once
#include "enums.hpp"
#include "settings.h"

#ifndef GLOBALS_H
#define GLOBALS_H

using namespace big;
struct globals {
	void load()
	{
		this->self.noclip = g_settings.options["self"]["godmode"];
	}

	void save()
	{
		g_settings.options["self"]["godmode"] = this->self.noclip;

		g_settings.save();
	}

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

	globals()
	{
		this->load();
	}

	self self{};
	vehicle vehicle{};
	weapons weapons{};
};

extern struct globals g;
#endif // !GLOBALS_H