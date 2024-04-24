#include "backend/looped_command.hpp"
#include "natives.hpp"

namespace big
{
	class infinite_veh_ammo : looped_command
	{
		using looped_command::looped_command;

		virtual void on_tick() override
        {
            Vehicle player_veh = self::veh;

            if (player_veh != 0 && VEHICLE::DOES_VEHICLE_HAVE_WEAPONS(player_veh))
            {
                for (int i = 0; i < 3; i++)
                {
                    VEHICLE::SET_VEHICLE_WEAPON_RESTRICTED_AMMO(player_veh, i, -1);
                }

                VEHICLE::SET_VEHICLE_BOMB_AMMO(player_veh, -1);
                VEHICLE::SET_VEHICLE_COUNTERMEASURE_AMMO(player_veh, -1);
            }
        }

		virtual void on_disable() override
		{
			Vehicle player_veh = self::veh;

			if (player_veh != 0 && VEHICLE::DOES_VEHICLE_HAVE_WEAPONS(player_veh))
			{
				for (int i = 0; i < 3; i++)
				{
					VEHICLE::SET_VEHICLE_WEAPON_RESTRICTED_AMMO(player_veh, i, 20);
				}

				VEHICLE::SET_VEHICLE_BOMB_AMMO(player_veh, 20);
				VEHICLE::SET_VEHICLE_COUNTERMEASURE_AMMO(player_veh, 20);
			}
		}
	};

	infinite_veh_ammo g_infinite_veh_ammo("infinitevehammo", "VEHICLE_INFINITE_AMMO", "VEHICLE_INFINITE_AMMO_DESC", g.vehicle.infinite_veh_ammo);
}