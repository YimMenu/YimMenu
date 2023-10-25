#pragma once

namespace big
{
	inline struct g_weapons
	{
		bool infinite_ammo = false;
		bool infinite_mag  = false;
		bool rapid_fire    = false;

		bool no_recoil        = false;
		bool no_spread        = false;
		bool damage_modifier  = false;
		int damage_modifier_v = 3;

		struct aimbot
		{
			bool enable    = false;
			float distance = 1000.f;
		} aimbot{};
	} g_weapons{};
}