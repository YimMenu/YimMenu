#include "backend/looped_command.hpp"
#include "natives.hpp"
#include "core/data/weapons.hpp"

namespace big
{
	class infinite_mag : bool_command
	{
		using bool_command::bool_command;

		CWeaponInfo* p_modified_weapon = nullptr;
		float og_recoil_value          = 0.0f;

		virtual void on_enable() override
		{
			WEAPON::SET_PED_INFINITE_AMMO_CLIP(self::ped, TRUE);
		}

		virtual void on_disable() override
		{
			WEAPON::SET_PED_INFINITE_AMMO_CLIP(self::ped, FALSE);
		}
	};

	infinite_mag g_infinite_mag("infclip", "Freeze Clip", "Freeze clip ammo (no reload)", g_weapons.infinite_mag);
}
