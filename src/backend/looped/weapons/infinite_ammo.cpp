#include "backend/looped_command.hpp"
#include "natives.hpp"

namespace big
{
	class infinite_ammo : looped_command
	{
		using looped_command::looped_command;

		virtual void on_tick() override
		{
			WEAPON::SET_PED_INFINITE_AMMO(self::ped, TRUE, NULL);
		}

		virtual void on_disable() override
		{
			WEAPON::SET_PED_INFINITE_AMMO(self::ped, FALSE, NULL);
		}
	};

	infinite_ammo g_infinite_ammo("infammo", "VIEW_OVERLAY_INFINITE_AMMO", "", g.weapons.infinite_ammo);
}