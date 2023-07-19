#include "player_database_service.hpp"

#include "backend/bool_command.hpp"
#include "file_manager.hpp"
#include "pointers.hpp"
#include "util/session.hpp"

namespace big
{
	bool_command g_player_db_auto_update_online_states("player_db_auto_update_states", "Auto Update Player Online States", "Toggling this feature will automatically update the player online states every 5minutes.",
	    g.player_db.update_player_online_states);

	player_database_service::player_database_service() :
	    m_file_path(g_file_manager.get_project_file("./players.json").get_path())
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
			try
			{
				std::ifstream file_stream(m_file_path);

				nlohmann::json json;
				file_stream >> json;
				file_stream.close();

				for (auto& [key, value] : json.items())
				{
					auto player                = value.get<std::shared_ptr<persistent_player>>();
					m_players[std::stoll(key)] = player;

					std::string lower = player->name;
					std::transform(lower.begin(), lower.end(), lower.begin(), ::tolower);
					m_sorted_players[lower] = player;
				}
			}
			catch (std::exception& e)
			{
				LOG(WARNING) << "Failed to load player database file. " << e.what();
			}
		}
	}

	std::unordered_map<std::uint64_t, std::shared_ptr<persistent_player>>& player_database_service::get_players()
	{
		return m_players;
	}

	std::map<std::string, std::shared_ptr<persistent_player>>& player_database_service::get_sorted_players()
	{
		return m_sorted_players;
	}

	std::shared_ptr<persistent_player> player_database_service::add_player(std::int64_t rid, const std::string_view name)
	{
		std::string lower = name.data();
		std::transform(lower.begin(), lower.end(), lower.begin(), ::tolower);
		if (m_players.contains(rid))
		{
			m_sorted_players.erase(lower);
		}

		auto player    = std::make_shared<persistent_player>(name.data(), rid);
		m_players[rid] = player;

		m_sorted_players[lower] = player;

		return player;
	}

	std::shared_ptr<persistent_player> player_database_service::get_player_by_rockstar_id(std::uint64_t rockstar_id)
	{
		if (m_players.contains(rockstar_id))
			return m_players[rockstar_id];
		return nullptr;
	}

	std::shared_ptr<persistent_player> player_database_service::get_or_create_player(player_ptr player)
	{
		if (m_players.contains(player->get_net_data()->m_gamer_handle.m_rockstar_id))
			return m_players[player->get_net_data()->m_gamer_handle.m_rockstar_id];
		else
		{
			auto player_ptr = add_player(player->get_net_data()->m_gamer_handle.m_rockstar_id, player->get_name());
			save();
			return player_ptr;
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

		if (auto it = m_players.find(rockstar_id); it != m_players.end())
		{
			std::string lower = it->second->name;
			std::transform(lower.begin(), lower.end(), lower.begin(), ::tolower);

			m_sorted_players.erase(lower);
			m_players.erase(it);
		}
	}

	void player_database_service::set_selected(std::shared_ptr<persistent_player> selected)
	{
		m_selected = selected;
	}

	std::shared_ptr<persistent_player> player_database_service::get_selected()
	{
		return m_selected;
	}

	void player_database_service::start_update_loop()
	{
		if (!g.player_db.update_player_online_states)
			return;

		g_thread_pool->push([this] {
			static auto last_update = std::chrono::high_resolution_clock::now() - 5min;
			while (g_running && g.player_db.update_player_online_states)
			{
				const auto cur = std::chrono::high_resolution_clock::now();
				if (cur - last_update > 5min)
				{
					g_fiber_pool->queue_job([this] {
						update_player_states();
					});
					last_update = cur;
				}

				std::this_thread::sleep_for(1s);
			}
		});
	}

	void player_database_service::update_player_states()
	{
		const auto player_count = m_players.size();

		std::vector<std::vector<rage::rlGamerHandle>> gamer_handle_buckets;
		gamer_handle_buckets.resize(std::ceil(player_count / 32.f));

		auto it = m_players.begin();
		for (size_t i = 0; i < player_count; ++i)
		{
			gamer_handle_buckets[i / 32].push_back(it->second->rockstar_id);

			it++;
		}

		for (auto& bucket : gamer_handle_buckets)
		{
			rage::rlTaskStatus status;
			std::array<int, 32> online;

			if (g_pointers->m_gta.m_get_gamer_online_state(0, bucket.data(), bucket.size(), online.data(), &status))
			{
				while (status.status == 1)
				{
					script::get_current()->yield();
				}

				for (size_t i = 0; i < bucket.size(); ++i)
				{
					if (const auto& it = m_players.find(bucket[i].m_rockstar_id); it != m_players.end())
					{
						if (online[i] == 1)
						{
							if (it->second->online_state == PlayerOnlineStatus::OFFLINE && it->second->notify_online)
							{
								g_notification_service->push_success("Player DB",
								    std::format("{} is now online!", it->second->name));
							}
							it->second->online_state = PlayerOnlineStatus::ONLINE;

							continue;
						}
						it->second->online_state = PlayerOnlineStatus::OFFLINE;
					}
				}
			}
		}
	}
}