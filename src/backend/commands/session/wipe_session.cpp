#include "backend/command.hpp"
#include "network/CNetworkPlayerMgr.hpp"
#include "pointers.hpp"
#include "services/players/player_service.hpp"

namespace big
{
	class empty_session : command
	{
		using command::command;
		virtual void execute(const command_arguments&, const std::shared_ptr<command_context> ctx) override
		{
			const auto player_mgr = *g_pointers->m_gta.m_network_player_mgr;
			for (const auto& plyr : g_player_service->players() | std::ranges::views::values)
			{
				player_mgr->RemovePlayer(plyr->get_net_game_player());
			}
			g_notification_service.push("EMPTY_SESSION"_T.data(), "BACKEND_WIPE_SESSION_COMPLETE"_T.data());
		}
	};
	empty_session g_empty_session("emptysession", "EMPTY_SESSION", "BACKEND_WIPE_SESSION_DESC", 0);
}
