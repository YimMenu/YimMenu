#include "player.hpp"
#include "util/system.hpp"
#include "network/CNetGamePlayer.hpp"
#include "services/friends/friends_service.hpp"

namespace big
{
	player::player(CNetGamePlayer* net_game_player)
		: m_net_game_player(net_game_player)
	{
		m_is_friend = friends_service::is_friend(net_game_player);
	}

	CAutomobile* player::get_current_vehicle() const
	{
		if (const auto ped = this->get_ped(); ped != nullptr)
			if (const auto vehicle = ped->m_vehicle; vehicle != nullptr)
				return vehicle;
		return nullptr;
	}

	const char* player::get_name() const
	{
		return m_net_game_player == nullptr ? "" : m_net_game_player->get_name();
	}

	rage::netPlayerData* player::get_net_data() const
	{
		return m_net_game_player == nullptr ? nullptr : m_net_game_player->get_net_data();
	}

	CNetGamePlayer* player::get_net_game_player() const
	{
		return m_net_game_player;
	}

	CPed* player::get_ped() const
	{
		if (const auto player_info = this->get_player_info(); player_info != nullptr)
			if (const auto ped = player_info->m_ped; ped != nullptr)
				return ped;
		return nullptr;
	}

	CPlayerInfo* player::get_player_info() const
	{
		if (m_net_game_player != nullptr && m_net_game_player->m_player_info != nullptr)
			return m_net_game_player->m_player_info;
		return nullptr;
	}

	rage::snPlayer* player::get_session_player() const
	{
		for (auto i = 0; i < system::get_network()->m_game_session_ptr->m_player_count; i++)
		{
			if (system::get_network()->m_game_session_ptr->m_players[i]->m_player_data.m_host_token == get_net_data()->m_host_token)
			{
				return system::get_network()->m_game_session_ptr->m_players[i];
			}
		}

		if (system::get_network()->m_game_session_ptr->m_local_player.m_player_data.m_host_token == get_net_data()->m_host_token)
			return &system::get_network()->m_game_session_ptr->m_local_player;

		return nullptr;
	}

	rage::snPeer* player::get_session_peer() const
	{
		for (uint32_t i = 0; i < system::get_network()->m_game_session_ptr->m_peer_count; i++)
		{
			if (system::get_network()->m_game_session_ptr->m_peers[i]->m_peer_data.m_rockstar_id2 == get_net_data()->m_rockstar_id2)
			{
				return system::get_network()->m_game_session_ptr->m_peers[i];
			}
		}
		return nullptr;
	}

	uint8_t player::id() const
	{
		return m_net_game_player == nullptr ? -1 : m_net_game_player->m_player_id;
	}

	bool player::is_host() const
	{
		return m_net_game_player == nullptr ? false : m_net_game_player->is_host();
	}

	bool player::is_friend() const
	{
		return m_is_friend;
	}


	bool player::is_valid() const
	{
		return m_net_game_player == nullptr ? false : m_net_game_player->is_valid();
	}

	bool player::equals(const CNetGamePlayer* net_game_player) const
	{
		return net_game_player == m_net_game_player;
	}

	std::string player::to_lowercase_identifier() const
	{
		std::string lower = this->get_name();
		std::transform(lower.begin(), lower.end(), lower.begin(), ::tolower);

		return lower;
	}
}
