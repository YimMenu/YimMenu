#include "backend/looped_command.hpp"
#include "core/data/weapons.hpp"
#include "natives.hpp"

namespace big
{
	class infinite_ammo : bool_command
	{
		using bool_command::bool_command;

		virtual void on_enable() override
		{
			WEAPON::SET_PED_INFINITE_AMMO(self::ped, TRUE, NULL);
		}

		virtual void on_disable() override
		{
			WEAPON::SET_PED_INFINITE_AMMO(self::ped, FALSE, NULL);
		}
	};

	infinite_ammo g_infinite_ammo("infammo", "Freeze Ammo", "(clip + refill) = ammo = constant", g_weapons.infinite_ammo);
}