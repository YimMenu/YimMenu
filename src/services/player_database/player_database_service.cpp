#include "player_database_service.hpp"

#include "file_manager.hpp"
#include "pointers.hpp"
#include "util/session.hpp"

namespace big
{
	player_database_service::player_database_service() :
	    m_file_path(g_file_manager->get_project_file("./players.json").get_path())
	{
		load();
		g_player_database_service = this;
	}

	player_database_service::~player_database_service()
	{
		g_player_database_service = nullptr;
	}

	void player_database_service::save()
	{
		nlohmann::json json;

		for (auto& [rid, player] : m_players)
		{
			json[std::to_string(rid)] = player;
		}

		std::ofstream file_stream(m_file_path);
		file_stream << json;
	}

	void player_database_service::load()
	{
		m_selected = nullptr;
		if (std::filesystem::exists(m_file_path))
		{
			std::ifstream file_stream(m_file_path);

			nlohmann::json json;
			file_stream >> json;
			file_stream.close();

			for (auto& p : json.items())
			{
				m_players[std::stoll(p.key())] = p.value().get<persistent_player>();
			}
		}
	}

	std::unordered_map<std::uint64_t, persistent_player>& player_database_service::get_players()
	{
		return m_players;
	}

	persistent_player* player_database_service::get_player_by_rockstar_id(std::uint64_t rockstar_id)
	{
		if (m_players.contains(rockstar_id))
			return &m_players[rockstar_id];
		return nullptr;
	}

	persistent_player* player_database_service::get_or_create_player(player_ptr player)
	{
		if (m_players.contains(player->get_net_data()->m_gamer_handle.m_rockstar_id))
			return &m_players[player->get_net_data()->m_gamer_handle.m_rockstar_id];
		else
		{
			m_players[player->get_net_data()->m_gamer_handle.m_rockstar_id] = {player->get_name(),
			    player->get_net_data()->m_gamer_handle.m_rockstar_id};
			save();
			return &m_players[player->get_net_data()->m_gamer_handle.m_rockstar_id];
		}
	}

	void player_database_service::update_rockstar_id(std::uint64_t old, std::uint64_t _new)
	{
		auto player  = m_players.extract(old);
		player.key() = _new;

		m_players.insert(std::move(player));
	}

	void player_database_service::remove_rockstar_id(std::uint64_t rockstar_id)
	{
		if (m_selected && m_selected->rockstar_id == rockstar_id)
			m_selected = nullptr;

		m_players.erase(rockstar_id);
	}

	void player_database_service::set_selected(persistent_player* selected)
	{
		m_selected = selected;
	}

	persistent_player* player_database_service::get_selected()
	{
		return m_selected;
	}

	void player_database_service::invalidate_player_states()
	{
		for (auto& item : m_players)
			item.second.online_state = PlayerOnlineStatus::UNKNOWN;
	}

	void player_database_service::update_player_states()
	{
		invalidate_player_states();

		//fetch current stat for each player.. this will need some time.
		for (auto& item : m_players)
		{
			auto& player = item.second;
			rage::rlGamerHandle player_handle(player.rockstar_id);
			rage::rlSessionByGamerTaskResult result;
			bool success = false;
			rage::rlTaskStatus state{};

			if (g_pointers->m_start_get_session_by_gamer_handle(0, &player_handle, 1, &result, 1, &success, &state))
			{
				while (state.status == 1)
					script::get_current()->yield();

				if (state.status == 3 && success)
				{
					player.online_state = PlayerOnlineStatus::ONLINE;
					continue;
				}
			}

			player.online_state = PlayerOnlineStatus::OFFLINE;
		}
	}
}