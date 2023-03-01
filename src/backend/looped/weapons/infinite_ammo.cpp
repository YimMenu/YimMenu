#include "backend/looped_command.hpp"
#include "natives.hpp"

namespace big
{
	class infinite_ammo : looped_command
	{
		using looped_command::looped_command;

		CWeaponInfo* p_modified_weapon = nullptr;
		float og_recoil_value          = 0.0f;

		virtual void on_tick() override
		{
			WEAPON::SET_PED_INFINITE_AMMO(self::ped, TRUE, NULL);
		}

		virtual void on_disable() override
		{
			WEAPON::SET_PED_INFINITE_AMMO(self::ped, FALSE, NULL);
		}
	};

	infinite_ammo g_infinite_ammo("infammo", "Infinite Ammo", "Never run out of ammo again", g.weapons.infinite_ammo);
}
