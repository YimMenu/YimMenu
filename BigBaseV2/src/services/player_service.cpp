#include "friends_service.hpp"
#include "gta_util.hpp"
#include "player_service.hpp"

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

	player_service::player_service()
		: m_selected_player(m_dummy)
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
		m_selected_player = m_dummy;
		m_players.clear();
	}

	player_ptr player_service::get_by_name(std::string name)
	{
		std::transform(name.begin(), name.end(), name.begin(), ::tolower);

		if (const auto it = m_players.find(name); it != m_players.end())
			return it->second;
		return nullptr;
	}

	player_ptr player_service::get_by_msg_id(uint32_t msg_id) const
	{
		for (const auto& [name, player] : m_players)
			if (player->get_net_game_player()->m_msg_id == msg_id)
				return player;
		return nullptr;
	}

	player_ptr player_service::get_by_host_token(uint64_t token) const
	{
		for (const auto& [name, player] : m_players)
			if (player->get_net_data()->m_host_token == token)
				return player;
		return nullptr;
	}

	player_ptr player_service::get_selected() const
	{
		return m_selected_player;
	}

	player_ptr player_service::get_self()
	{
		if (!m_self_ptr || !m_self_ptr->equals(*m_self))
		{
			m_self_ptr = std::make_shared<player>(*m_self);
		}

		return m_self_ptr;
	}

	void player_service::player_join(CNetGamePlayer* net_game_player)
	{
		if (net_game_player == nullptr || net_game_player == *m_self) return;

		auto plyr = std::make_shared<player>(net_game_player);
		m_players.emplace(
			plyr->to_lowercase_identifier(),
			std::move(plyr)
		);
	}

	void player_service::player_leave(CNetGamePlayer* net_game_player)
	{
		if (net_game_player == nullptr) return;
		if (m_selected_player && m_selected_player->equals(net_game_player))
			m_selected_player = m_dummy;

		auto plyr = std::make_unique<player>(net_game_player);
		m_players.erase(plyr->to_lowercase_identifier());
	}

	void player_service::set_selected(player_ptr plyr)
	{
		m_selected_player = plyr;
	}
}
