#include "backend/player_command.hpp"
#include "network/CNetworkPlayerMgr.hpp"
#include "pointers.hpp"
#include "services/players/player_service.hpp"

namespace big
{
	class empty_session : command
	{
		using command::command;
		virtual void execute(const std::vector<uint64_t>&, const std::shared_ptr<command_context> ctx)
		{
			g_player_service->iterate([](const player_entry& player) {
				auto mgr = *g_pointers->m_gta.m_network_player_mgr;
				mgr->RemovePlayer(player.second->get_net_game_player());
			});
			g_notification_service->push_success("Empty Session", "Completed");
		}
	};
	empty_session g_empty_session("emptysession", "Remove All Players From Session", "Removes everyone from the session", 0);
}