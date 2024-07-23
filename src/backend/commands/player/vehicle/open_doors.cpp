#include "backend/player_command.hpp"
#include "natives.hpp"
#include "util/entity.hpp"

namespace big
{
	class open_doors : player_command
	{
		using player_command::player_command;

		virtual void execute(player_ptr player, const command_arguments& _args, const std::shared_ptr<command_context> ctx) override
		{
			Ped ped = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player->id());
			if (!PED::IS_PED_IN_ANY_VEHICLE(ped, true))
			{
				g_notification_service.push_warning("TOXIC"_T.data(), "ERROR_PLAYER_IS_NOT_IN_VEHICLE"_T.data());
			}
			else
			{
				Vehicle vehicle = PED::GET_VEHICLE_PED_IS_USING(ped);

				if (entity::take_control_of(vehicle))
				{
					for (int i = 0; i < VEHICLE::GET_NUMBER_OF_VEHICLE_DOORS(vehicle); i++)
					{
						VEHICLE::SET_VEHICLE_DOOR_OPEN(vehicle, i, true, false);
					}
				}
				else
				{
					g_notification_service.push_warning("TOXIC"_T.data(), "ERROR_FAILED_TO_TAKE_CONTROL"_T.data());
				}
			}
		}
	};

	open_doors g_open_doors("opendoors", "BACKEND_OPEN_VEHICLE_DOORS", "BACKEND_OPEN_VEHICLE_DOORS_DESC", 0);
}
