#include "player_service.hpp"

#include "gta_util.hpp"
#include "util/math.hpp"


namespace big
{
	player_service::player_service() :
	    m_self(nullptr),
	    m_selected_player(m_dummy)
	{
		g_player_service = this;

		const auto network_player_mgr = gta_util::get_network_player_mgr();
		if (!network_player_mgr)
			return;

		m_self = &network_player_mgr->m_local_net_player;

		for (uint16_t i = 0; i < network_player_mgr->m_player_limit; ++i)
			player_join(network_player_mgr->m_player_list[i]);
	}

	player_service::~player_service()
	{
		g_player_service = nullptr;
	}

	void player_service::do_cleanup()
	{
		m_players_sending_modder_beacons.clear();
		m_selected_player = m_dummy;
		m_players.clear();
	}

	player_ptr player_service::get_by_msg_id(uint32_t msg_id) const
	{
		for (const auto& [_, player] : m_players)
		{
			if (auto net_game_player = player->get_net_game_player())
			{
				if (net_game_player->m_msg_id == msg_id)
				{
					return player;
				}
			}
		}
		return nullptr;
	}

	player_ptr player_service::get_by_id(uint32_t id) const
	{
		for (const auto& [_, player] : m_players)
		{
			if (player && player->id() == id)
			{
				return player;
			}
		}
		return nullptr;
	}

	player_ptr player_service::get_by_host_token(uint64_t token) const
	{
		for (const auto& player : m_players | std::ranges::views::values)
		{
			if (auto net_data = player->get_net_data())
			{
				if (net_data->m_host_token == token)
				{
					return player;
				}
			}
		}
		return nullptr;
	}

		player_ptr player_service::get_by_name(std::string_view name) const
	{
		std::string self_name  = g_player_service->get_self()->get_name();
		std::string name_lower = name.data();
		std::transform(self_name.begin(), self_name.end(), self_name.begin(), ::tolower);
		std::transform(name_lower.begin(), name_lower.end(), name_lower.begin(), ::tolower);

		for (auto& [_, player] : m_players)
		{
			std::string player_name = player->get_name();
			std::transform(player_name.begin(), player_name.end(), player_name.begin(), ::tolower);
			if (player_name == name_lower)
				return player;
		}
		return nullptr;
	}

	player_ptr player_service::get_by_name_closest(std::string_view guess) const
	{
		std::string self_name   = g_player_service->get_self()->get_name();
		std::string lower_guess = guess.data();
		std::transform(self_name.begin(), self_name.end(), self_name.begin(), ::tolower);
		std::transform(lower_guess.begin(), lower_guess.end(), lower_guess.begin(), ::tolower);

		for (auto& [_, player] : m_players)
		{
			std::string player_name = player->get_name();
			std::transform(player_name.begin(), player_name.end(), player_name.begin(), ::tolower);

			if (player_name.find(lower_guess) != std::string::npos)
			{
				return player;
			}
		}

		return nullptr;
	}

	player_ptr player_service::get_closest(bool exclude_friends) const
	{
		float closest_distance    = std::numeric_limits<float>::max();
		player_ptr closest_player = nullptr;
		for (auto player : m_players | std::ranges::views::values)
		{
			if (exclude_friends && player->is_friend())
				continue;

			if (player && player->get_ped() && player->get_ped()->get_position())
			{
				if (math::distance_between_vectors(*player->get_ped()->get_position(),
				        *g_player_service->get_self()->get_ped()->get_position())
				    < closest_distance)
				{
					closest_distance = math::distance_between_vectors(*player->get_ped()->get_position(),
					    *g_player_service->get_self()->get_ped()->get_position());
					closest_player   = player;
				}
			}
		}

		return closest_player;
	}

	player_ptr player_service::get_selected() const
	{
		return m_selected_player;
	}

	player_ptr player_service::get_self()
	{
		if (!m_self_ptr || !m_self_ptr->equals(*m_self))
		{
			m_self_ptr                       = std::make_shared<player>(*m_self);
			m_self_ptr->command_access_level = CommandAccessLevel::ADMIN;
		}

		return m_self_ptr;
	}

	void player_service::player_join(CNetGamePlayer* net_game_player)
	{
		if (net_game_player == nullptr || net_game_player == *m_self)
			return;

		auto plyr = std::make_shared<player>(net_game_player);
		m_players.insert({plyr->get_name(), std::move(plyr)});
	}

	void player_service::player_leave(CNetGamePlayer* net_game_player)
	{
		if (net_game_player == nullptr)
			return;

		if (m_selected_player && m_selected_player->equals(net_game_player))
			m_selected_player = m_dummy;

		if (auto it = std::find_if(m_players.begin(),
		        m_players.end(),
		        [net_game_player](const auto& p) {
			        return p.second->id() == net_game_player->m_player_id;
		        });
		    it != m_players.end())
		{
			m_players.erase(it);
		}
	}

	void player_service::mark_player_as_sending_modder_beacons(std::uint64_t rid)
	{
		m_players_sending_modder_beacons.insert(rid);
	}

	bool player_service::did_player_send_modder_beacon(std::uint64_t rid)
	{
		return m_players_sending_modder_beacons.contains(rid);
	}

	void player_service::set_selected(player_ptr plyr)
	{
		m_selected_player = plyr;
	}
}
