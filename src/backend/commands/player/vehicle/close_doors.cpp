#include "backend/player_command.hpp"
#include "natives.hpp"
#include "util/entity.hpp"

namespace big
{
	class close_doors : player_command
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
					VEHICLE::SET_VEHICLE_DOORS_SHUT(vehicle, false);
				}
				else
				{
					g_notification_service.push_warning("TOXIC"_T.data(), "ERROR_FAILED_TO_TAKE_CONTROL"_T.data());
				}
			}
		}
	};

	close_doors g_close_doors("closedoors", "BACKEND_CLOSE_VEHICLE_DOORS", "BACKEND_CLOSE_VEHICLE_DOORS_DESC", 0);
}
