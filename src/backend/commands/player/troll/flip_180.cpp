#include "backend/player_command.hpp"
#include "natives.hpp"
#include "pointers.hpp"
#include "util/teleport.hpp"

namespace big
{
	class flip_180 : player_command
	{
		using player_command::player_command;

		virtual void execute(player_ptr player, const std::vector<std::uint64_t>& _args, const std::shared_ptr<command_context> ctx)
		{
			Ped ped            = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player->id());
			float heading      = ENTITY::GET_ENTITY_HEADING(ped);
			Vector3 car_coords = ENTITY::GET_ENTITY_COORDS(ped, 1);
			
			if (!PED::IS_PED_IN_ANY_VEHICLE(ped, true))
			{
				g_notification_service->push_warning("Toxic", "Target player is not in any vehicle.");
			}
			else
			{
				Vehicle vehicle = PED::GET_VEHICLE_PED_IS_USING(ped);
				float speed     = ENTITY::GET_ENTITY_SPEED(vehicle);

				if (entity::take_control_of(vehicle))
				{
					if (heading > 180.0)
						heading -= 180.0;

					else
						heading += 180.0;
					
					ENTITY::SET_ENTITY_COORDS(vehicle, car_coords.x, car_coords.y, car_coords.z, 0, 0, 0, 1);
					ENTITY::SET_ENTITY_HEADING(vehicle, heading);
					VEHICLE::SET_VEHICLE_FORWARD_SPEED(vehicle, speed);
				}
			}
		}
	};

	flip_180
		g_flip_180("flip180", "Rotate 180", "Rotates their car around", 0)
			;
}