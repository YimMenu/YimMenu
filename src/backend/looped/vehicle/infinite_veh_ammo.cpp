#include "backend/looped_command.hpp"
#include "natives.hpp"

namespace big
{
	class infinite_veh_ammo : looped_command
	{
		using looped_command::looped_command;

		virtual void on_tick() override
        	{
			if (self::veh && VEHICLE::DOES_VEHICLE_HAVE_WEAPONS(self::veh))
            		{
				for (int i = 0; i < 3; i++)
				{
					VEHICLE::SET_VEHICLE_WEAPON_RESTRICTED_AMMO(self::veh, i, -1);
				}

				VEHICLE::SET_VEHICLE_BOMB_AMMO(self::veh, -1);
				VEHICLE::SET_VEHICLE_COUNTERMEASURE_AMMO(self::veh, -1);
            		}
        	}

		virtual void on_disable() override
		{
			if (self::veh && VEHICLE::DOES_VEHICLE_HAVE_WEAPONS(self::veh))
			{
				for (int i = 0; i < 3; i++)
				{
					VEHICLE::SET_VEHICLE_WEAPON_RESTRICTED_AMMO(self::veh, i, 20);
				}

				VEHICLE::SET_VEHICLE_BOMB_AMMO(self::veh, 20);
				VEHICLE::SET_VEHICLE_COUNTERMEASURE_AMMO(self::veh, 20);
			}
		}
	};

	infinite_veh_ammo g_infinite_veh_ammo("infinitevehammo", "VEHICLE_INFINITE_AMMO", "VEHICLE_INFINITE_AMMO_DESC", g.vehicle.infinite_veh_ammo);
}
