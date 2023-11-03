#include "backend/looped_command.hpp"
#include "natives.hpp"

namespace big
{
	class always_full_ammo : looped_command
	{
		using looped_command::looped_command;

		virtual void on_tick() override
		{
			int max_ammo;
			Hash weapon_hash;
			WEAPON::GET_CURRENT_PED_WEAPON(self::ped, &weapon_hash, NULL);
			if (WEAPON::IS_WEAPON_VALID(weapon_hash) && WEAPON::GET_MAX_AMMO(self::ped, weapon_hash, &max_ammo))
				WEAPON::SET_PED_AMMO(self::ped, weapon_hash, max_ammo, 0);
		}
	};

	always_full_ammo g_always_full_ammo("alwaysfullammo", "BACKEND_LOOPED_WEAPONS_ALWAYS_FULL_AMMO", "BACKEND_LOOPED_WEAPONS_ALWAYS_FULL_AMMO_DESC", g.weapons.always_full_ammo);
}