#include "gta_util.hpp"
#include "friends_service.hpp"
#include "player_service.hpp"

namespace big
{
	player::player(CNetGamePlayer* net_game_player)
		: m_net_game_player(net_game_player)
	{

	}

	CAutomobile* player::get_current_vehicle()
	{
		if (CPed* ped = this->get_ped(); ped != nullptr)
			if (CAutomobile* vehicle = ped->m_vehicle; vehicle != nullptr)
				return vehicle;
		return nullptr;
	}

	const char* player::get_name()
	{
		return m_net_game_player == nullptr ? "" : m_net_game_player->get_name();
	}

	rage::netPlayerData* player::get_net_data()
	{
		return m_net_game_player == nullptr ? nullptr : m_net_game_player->get_net_data();
	}

	CNetGamePlayer* player::get_net_game_player()
	{
		return m_net_game_player;
	}

	CPed* player::get_ped()
	{
		if (CPlayerInfo* player_info = this->get_player_info(); player_info != nullptr)
			if (CPed* ped = player_info->m_ped; ped != nullptr)
				return ped;
		return nullptr;
	}

	CPlayerInfo* player::get_player_info()
	{
		if (m_net_game_player != nullptr && m_net_game_player->m_player_info != nullptr)
			return m_net_game_player->m_player_info;
		return nullptr;
	}

	uint8_t player::id()
	{
		return m_net_game_player == nullptr ? -1 : m_net_game_player->m_player_id;
	}

	bool player::is_host()
	{
		return m_net_game_player == nullptr ? false : m_net_game_player->is_host();
	}

	bool player::is_friend()
	{
		return m_is_friend;
	}


	bool player::is_valid()
	{
		return m_net_game_player == nullptr ? false : m_net_game_player->is_valid();
	}

	bool player::equals(CNetGamePlayer* net_game_player)
	{
		return net_game_player == m_net_game_player;
	}

	std::string player::to_lowercase_identifier()
	{
		std::string lower = this->get_name();
		std::transform(lower.begin(), lower.end(), lower.begin(), ::tolower);

		return lower;
	}

	player_service::player_service()
	{
		g_player_service = this;

		m_dummy_player = new player(nullptr);

		auto network_player_mgr = gta_util::get_network_player_mgr();
		if (!network_player_mgr)
			return;

		const auto network_self = network_player_mgr->m_local_net_player;
		if (!network_self)
			return;

		player_join(network_self, true);

		for (uint16_t i = 0; i < network_player_mgr->m_player_limit; ++i)
		{
			const auto network_player = network_player_mgr->m_player_list[i];
			if (network_player == network_self)
				continue;

			player_join(network_player, false);
		}
	}

	player_service::~player_service()
	{
		g_player_service = nullptr;
	
		delete m_dummy_player;
	}

	void player_service::do_cleanup()
	{
		m_selected_player = nullptr;
		m_self.reset();
		m_players.clear();
	}

	player* player_service::get_by_name(std::string name)
	{
		std::transform(name.begin(), name.end(), name.begin(), ::tolower);

		if (auto it = m_players.find(name); it != m_players.end())
			return it->second.get();
		return nullptr;
	}

	player* player_service::get_by_msg_id(uint32_t msg_id)
	{
		for (auto it = m_players.begin(); it != m_players.end(); it++)
		{
			if (it->second.get()->get_net_game_player()->m_msg_id == msg_id)
				return it->second.get();
		}
		return nullptr;
	}

	player* player_service::get_by_host_token(uint64_t token)
	{
		for (auto it = m_players.begin(); it != m_players.end(); it++)
		{
			if (it->second.get()->get_net_data()->m_host_token == token)
				return it->second.get();
		}
		return nullptr;
	}

	player* player_service::get_selected()
	{
		return m_selected_player == nullptr ? m_dummy_player : m_selected_player;
	}

	void player_service::player_join(CNetGamePlayer* net_game_player, const bool self)
	{
		if (net_game_player == nullptr) return;

		auto plyr = std::make_shared<player>(net_game_player);

		if (self)
			m_self = plyr;
		else
			plyr->m_is_friend = friends_service::is_friend(plyr);

		m_players.emplace(
			plyr->to_lowercase_identifier(),
			std::move(plyr)
		);
	}

	void player_service::player_leave(CNetGamePlayer* net_game_player)
	{
		if (net_game_player == nullptr) return;
		if (m_selected_player && m_selected_player->equals(net_game_player))
			m_selected_player = nullptr;

		auto plyr = std::make_unique<player>(net_game_player);
		m_players.erase(plyr->to_lowercase_identifier());
	}

	void player_service::set_selected(player* plyr)
	{
		m_selected_player = plyr;
	}
}