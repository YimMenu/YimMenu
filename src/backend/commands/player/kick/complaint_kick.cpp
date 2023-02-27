#include "backend/player_command.hpp"
#include "core/scr_globals.hpp"
#include "gta_util.hpp"
#include "natives.hpp"
#include "pointers.hpp"

#include <network/Network.hpp>

namespace big
{
	class complaint_kick : player_command
	{
		using player_command::player_command;

		virtual CommandAccessLevel get_access_level()
		{
			return CommandAccessLevel::TOXIC;
		}

		virtual void execute(player_ptr player, const std::vector<std::uint64_t>& _args, const std::shared_ptr<command_context> ctx)
		{
			if (gta_util::get_network()->m_game_session_ptr->is_host())
			{
				gta_util::get_network()->m_game_complaint_mgr.raise_complaint(player->get_net_data()->m_host_token);
				return;
			}

			g_player_service->m_player_to_use_complaint_kick = player;
		}
	};

	complaint_kick g_complaint_kick("desync", "Desync Kick", "This may take around 10 seconds to kick the player. Does not work against the host", 0);// this is pretty much desync except we don't actually remove the player from CNetworkPlayerMgr
}