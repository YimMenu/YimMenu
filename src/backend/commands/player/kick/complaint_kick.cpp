#include "complaint_kick.hpp"

#include "core/scr_globals.hpp"
#include "gta_util.hpp"
#include "natives.hpp"
#include "pointers.hpp"

#include <network/Network.hpp>
namespace big
{
	CommandAccessLevel complaint_kick::get_access_level()
	{
		return CommandAccessLevel::TOXIC;
	}

	void complaint_kick::execute(player_ptr player, const std::vector<std::uint64_t>& _args, const std::shared_ptr<command_context> ctx)
	{
		if (gta_util::get_network()->m_game_session_ptr->is_host())
		{
			gta_util::get_network()->m_game_complaint_mgr.raise_complaint(player->get_net_data()->m_host_token);
			return;
		}

		g_player_service->m_player_to_use_complaint_kick = player;
	}
}
