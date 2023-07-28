#include "backend/player_command.hpp"
#include "natives.hpp"
#include "pointers.hpp"
#include "util/teleport.hpp"
namespace big
{
	class stop_vehicle : player_command
	{
		using player_command::player_command;

		virtual void execute(player_ptr player, const command_arguments& _args, const std::shared_ptr<command_context> ctx)
		{
			Ped ped = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player->id());
			if (!PED::IS_PED_IN_ANY_VEHICLE(ped, true))
			{
				g_notification_service->push_warning("TOXIC"_T.data(), "ERROR_PLAYER_IS_NOT_IN_VEHICLE"_T.data());
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
					g_notification_service->push_warning("Toxic", "Failed to take control of player vehicle.");
				}
			}
		}
	};

	stop_vehicle g_stop_vehicle("stopveh", "Stop Vehicle", "Stops players vehicle", 0);
}