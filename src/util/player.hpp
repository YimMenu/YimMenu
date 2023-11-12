#pragma once
#include "services/players/player.hpp"

namespace big
{
	inline std::string get_blocked_player_joined_log_string(big::player_ptr plyr)
	{
		if (auto net_data = plyr->get_net_data())
		{
			auto rockstar_id = net_data->m_gamer_handle.m_rockstar_id;
			auto player_name = net_data->m_name;

			plyr->is_blocked = true;
			plyr->is_spammer = bad_players_nm::bad_players_list[rockstar_id].is_spammer;

			return std::format("A Blocked {} {} ({}) has joined.", plyr->is_spammer ? "Spammer" : "Player", player_name, rockstar_id);
		}

		return "";
	}
}