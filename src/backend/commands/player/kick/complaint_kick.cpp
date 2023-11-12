#include "backend/player_command.hpp"
#include "core/scr_globals.hpp"
#include "gta_util.hpp"
#include "natives.hpp"
#include "pointers.hpp"
#include "services/notifications/notification_service.hpp"

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
			if (!player)
				return;

			g_notification_service->push_success("Kick", std::format("Desync kick to {}", player->get_name()), true);

			if (auto net_data = player->get_net_data(); net_data && gta_util::get_network()->m_game_session_ptr->is_host())
			{
				gta_util::get_network()->m_game_complaint_mgr.raise_complaint(net_data->m_host_token);
				return;
			}

			g_player_service->m_player_to_use_complaint_kick = player;
		}
	};

	complaint_kick g_complaint_kick("desync", "Desync Kick", "This may take around 10 seconds to kick the player. Does not work against the host", 0); // this is pretty much desync except we don't actually remove the player from CNetworkPlayerMgr
}