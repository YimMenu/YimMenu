#include "backend/player_command.hpp"
#include "natives.hpp"
#include "util/vehicle.hpp"

namespace big
{
	class remote_control_vehicle : player_command
	{
		using player_command::player_command;

		virtual void execute(player_ptr player, const command_arguments& _args, const std::shared_ptr<command_context> ctx) override
		{
			Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player->id()), FALSE);
			if (veh == 0)
			{
				if (g.player.spectating)
					g_notification_service.push_warning("REMOTE_CONTROL"_T.data(), "ERROR_PLAYER_IS_NOT_IN_VEHICLE"_T.data());
				else
					g_notification_service.push_warning("REMOTE_CONTROL"_T.data(), std::format("{} {}", "ERROR_PLAYER_IS_NOT_IN_VEHICLE"_T, "BACKEND_REMOTE_CONTROL_VEHICLE_SPECTATE"_T).c_str());
				return;
			}

			vehicle::remote_control_vehicle(veh);
			g.player.spectating = false;
		}
	};

	remote_control_vehicle g_remote_control_vehicle("rcplayer", "BACKEND_REMOTE_CONTROL_VEHICLE", "BACKEND_REMOTE_CONTROL_VEHICLE_DESC", 0, false);
}
