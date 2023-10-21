#pragma once

namespace big
{
	inline struct g_weapons
	{
		bool infinite_ammo = false;
		bool infinite_mag  = false;
		bool rapid_fire    = false;

		struct aimbot
		{
			bool enable    = false;
			float distance = 1000.f;
		} aimbot{};
	} g_weapons{};
}