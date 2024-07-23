#include "backend/player_command.hpp"
#include "gta_util.hpp"

#include <network/Network.hpp>

namespace big
{
	class complaint_kick : player_command
	{
		using player_command::player_command;

		virtual CommandAccessLevel get_access_level() override
		{
			return CommandAccessLevel::TOXIC;
		}

		virtual void execute(player_ptr player, const command_arguments& _args, const std::shared_ptr<command_context> ctx) override
		{
			if (!player || !player->is_valid())
				return;
			if (gta_util::get_network()->m_game_session_ptr->is_host())
			{
				gta_util::get_network()->m_game_complaint_mgr.raise_complaint(player->get_net_data()->m_host_token);
				return;
			}

			player->trigger_desync_kick = true;
		}
	};

	complaint_kick g_complaint_kick("desync", "COMPLAINT_KICK", "COMPLAINT_KICK_DESC", 0); // this is pretty much desync except we don't actually remove the player from CNetworkPlayerMgr
}