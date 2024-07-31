#include "backend/player_command.hpp"
#include "natives.hpp"
#include "util/entity.hpp"

namespace big
{
	class flip_180 : player_command
	{
		using player_command::player_command;

		virtual void execute(player_ptr player, const command_arguments& _args, const std::shared_ptr<command_context> ctx) override
		{
			Ped player_ped           = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player->id());
			Vehicle vehicle          = PED::GET_VEHICLE_PED_IS_IN(player_ped, false);
			float heading            = ENTITY::GET_ENTITY_HEADING(vehicle);
			Vector3 flipCar180Coords = ENTITY::GET_ENTITY_COORDS(vehicle, 1);

			if (!PED::IS_PED_IN_ANY_VEHICLE(player_ped, true))
			{
				g_notification_service.push_warning("TOXIC"_T.data(), "ERROR_PLAYER_IS_NOT_IN_VEHICLE"_T.data());
			}
			else
			{
				if (entity::take_control_of(vehicle))
				{
					if (heading > 180.0)
					{
						heading -= 180.0;
					}
					else
					{
						heading += 180.0;
						ENTITY::SET_ENTITY_COORDS(vehicle, flipCar180Coords.x, flipCar180Coords.y, flipCar180Coords.z, 0, 0, 0, 1);
						ENTITY::SET_ENTITY_HEADING(vehicle, heading);
						VEHICLE::SET_VEHICLE_FORWARD_SPEED(vehicle, ENTITY::GET_ENTITY_SPEED(vehicle));
					}
				}
			}
		}
	};

	flip_180 g_flip_180("flip180", "BACKEND_FLIP", "BACKEND_FLIP_DESC", 0);
}
