#include "backend/player_command.hpp"
#include "natives.hpp"
#include "pointers.hpp"
#include "util/vehicle.hpp"

namespace big
{
	class remote_control_vehicle : player_command
	{
		using player_command::player_command;

		virtual void execute(player_ptr player, const std::vector<std::uint64_t>& _args, const std::shared_ptr<command_context> ctx)
		{
			Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player->id()), FALSE);
			if (veh == 0)
			{
				if (g.player.spectating)
					g_notification_service->push_warning("Remote Control", "Player not in a vehicle");
				else
					g_notification_service->push_warning("Remote Control", "Player not in a vehicle, try spectating the player");
				return;
			}

			vehicle::remote_control_vehicle(veh);
			g.player.spectating = false;
		}
	};

	remote_control_vehicle g_remote_control_vehicle("rcplayer", "Remote Control Vehicle", "Take control of the player's vehicle. Spectate the player beforehand for best results", 0, false);
}