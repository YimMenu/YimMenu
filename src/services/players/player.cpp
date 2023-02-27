#include "player.hpp"

#include "gta_util.hpp"
#include "network/CNetGamePlayer.hpp"
#include "services/friends/friends_service.hpp"

#include <network/Network.hpp>
#include <network/RemoteGamerInfoMsg.hpp>

namespace big
{
	player::player(CNetGamePlayer* net_game_player) :
	    m_net_game_player(net_game_player)
	{
		m_is_friend = friends_service::is_friend(net_game_player);
	}

	CVehicle* player::get_current_vehicle() const
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

	rage::rlGamerInfo* player::get_net_data() const
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

	rage::snPlayer* player::get_session_player()
	{
		for (std::uint32_t i = 0; i < gta_util::get_network()->m_game_session_ptr->m_player_count; i++)
		{
			if (gta_util::get_network()->m_game_session_ptr->m_players[i]->m_player_data.m_host_token == get_net_data()->m_host_token)
			{
				return gta_util::get_network()->m_game_session_ptr->m_players[i];
			}
		}

		if (gta_util::get_network()->m_game_session_ptr->m_local_player.m_player_data.m_host_token == get_net_data()->m_host_token)
			return &gta_util::get_network()->m_game_session_ptr->m_local_player;

		return nullptr;
	}

	rage::snPeer* player::get_session_peer()
	{
		for (std::uint32_t i = 0; i < gta_util::get_network()->m_game_session_ptr->m_peer_count; i++)
		{
			if (gta_util::get_network()->m_game_session_ptr->m_peers[i]->m_peer_data.m_gamer_handle.m_rockstar_id
			    == get_net_data()->m_gamer_handle.m_rockstar_id)
			{
				return gta_util::get_network()->m_game_session_ptr->m_peers[i];
			}
		}

		return nullptr;
	}

	netAddress player::get_ip_address()
	{
		if (this == g_player_service->get_self().get() && get_net_data())
			return get_net_data()->m_external_ip;

		if (auto session_player = get_session_player())
			if (auto peer = g_pointers->m_get_connection_peer(gta_util::get_network()->m_game_session_ptr->m_net_connection_mgr,
			        (int)get_session_player()->m_player_data.m_peer_id_2))
				return netAddress{((netConnectionPeer*)peer)->m_external_ip};

		return {0};
	}

	uint16_t player::get_port()
	{
		if (this == g_player_service->get_self().get() && get_net_data())
			return get_net_data()->m_external_port;

		if (auto session_player = get_session_player())
			if (auto peer = g_pointers->m_get_connection_peer(gta_util::get_network()->m_game_session_ptr->m_net_connection_mgr,
			        (int)get_session_player()->m_player_data.m_peer_id_2))
				return ((netConnectionPeer*)peer)->m_external_port;

		return 0;
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
