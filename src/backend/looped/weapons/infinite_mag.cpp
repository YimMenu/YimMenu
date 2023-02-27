#include "backend/looped_command.hpp"
#include "natives.hpp"

namespace big
{
	class infinite_mag : looped_command
	{
		using looped_command::looped_command;

		CWeaponInfo* p_modified_weapon = nullptr;
		float og_recoil_value          = 0.0f;

		virtual void on_tick() override
		{
			WEAPON::SET_PED_INFINITE_AMMO_CLIP(self::ped, TRUE);
		}

		virtual void on_disable() override
		{
			WEAPON::SET_PED_INFINITE_AMMO_CLIP(self::ped, FALSE);
		}
	};

	infinite_mag g_infinite_mag("infclip", "Infinite Clip", "Shoot forever without needing to reload", g.weapons.infinite_mag);
}
