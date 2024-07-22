#include "backend/player_command.hpp"
#include "natives.hpp"
#include "util/entity.hpp"

namespace big
{
	class stop_vehicle : player_command
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
					VEHICLE::BRING_VEHICLE_TO_HALT(vehicle, 0.0f, 1, 0);
				}
				else
				{
					g_notification_service.push_warning("TOXIC"_T.data(), "ERROR_FAILED_TO_TAKE_CONTROL"_T.data());
				}
			}
		}
	};

	stop_vehicle g_stop_vehicle("stopveh", "BACKEND_STOP_VEHICLE", "BACKEND_STOP_VEHICLE_DESC", 0);
}
