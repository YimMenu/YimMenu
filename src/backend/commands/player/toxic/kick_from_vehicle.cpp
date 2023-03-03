#include "backend/player_command.hpp"
#include "gta/net_object_mgr.hpp"
#include "natives.hpp"
#include "pointers.hpp"

namespace big
{
	class kick_from_vehicle : player_command
	{
		using player_command::player_command;

		virtual CommandAccessLevel get_access_level()
		{
			return CommandAccessLevel::AGGRESSIVE;
		}

		virtual void execute(player_ptr player, const std::vector<std::uint64_t>& _args, const std::shared_ptr<command_context> ctx)
		{
			auto vehicle = player->get_current_vehicle();

			if (!vehicle || !vehicle->m_net_object)
			{
				// vehicle hasn't synced yet, use TSE
				const size_t arg_count  = 9;
				int64_t args[arg_count] = {(int64_t)eRemoteEvent::VehicleKick, self::id, 0, 0, 0, 0, 0, 0, 0};

				g_pointers->m_trigger_script_event(1, args, arg_count, 1 << player->id());
			}
			else
			{
				// use a private method to kick player from vehicle
				(*g_pointers->m_network_object_mgr)->ChangeOwner(vehicle->m_net_object, g_player_service->get_self()->get_net_game_player(), 0);
			}
		}
	};

	kick_from_vehicle g_kick_from_vehicle("vehkick", "Vehicle Kick", "Kicks the player from their current vehicle", 0);
}