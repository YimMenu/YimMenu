#include "backend/player_command.hpp"
#include "natives.hpp"
#include "pointers.hpp"
#include "core/scr_globals.hpp"
#include "gta_util.hpp"

#include <network/Network.hpp>

namespace big
{
	class host_kick : player_command
	{
		using player_command::player_command;

		virtual CommandAccessLevel get_access_level()
		{
			return CommandAccessLevel::TOXIC;
		}

		virtual void execute(player_ptr player, const std::vector<std::uint64_t>& _args, const std::shared_ptr<command_context> ctx)
		{
			if (!g_player_service->get_self()->is_host())
			{
				g_notification_service->push_error("Kick", "You have to be the session host");
				return;
			}

			rage::snMsgRemoveGamersFromSessionCmd cmd{};
			cmd.m_session_id = gta_util::get_network()->m_game_session_ptr->m_rline_session.m_session_id;
			cmd.m_num_peers = 1;
			cmd.m_peer_ids[0] = player->get_session_peer()->m_peer_data.m_peer_id_2;

			g_pointers->m_handle_remove_gamer_cmd(gta_util::get_network()->m_game_session_ptr, player->get_session_player(), &cmd);
		}
	};

	host_kick g_host_kick("hostkick", "Host Kick", "Unblockable and undetectable, but requires session host", 0, false);
}