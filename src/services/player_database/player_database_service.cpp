#include "player_database_service.hpp"

#include "backend/bool_command.hpp"
#include "file_manager.hpp"
#include "gta/enums.hpp"
#include "pointers.hpp"
#include "util/session.hpp"

namespace big
{
	bool_command g_player_db_auto_update_online_states("player_db_auto_update_states", "Auto Update Tracked Player States", "Toggling this feature will automatically update the tracked players' online states every minute",
	    g.player_db.update_player_online_states);

	void player_database_service::handle_session_type_change(persistent_player& player, GSType new_session_type)
	{
		if (!player.notify_online)
			return;

		if (g.player_db.notify_when_joinable && !is_joinable_session(player.session_type) && is_joinable_session(new_session_type))
		{
			g_notification_service->push_success("Player DB", std::format("{} is now in a joinable session", player.name));
		}
		else if (g.player_db.notify_when_online && (player.session_type == GSType::Invalid || player.session_type == GSType::Unknown) && new_session_type != GSType::Invalid)
		{
			g_notification_service->push_success("Player DB", std::format("{} is now online", player.name));
		}
		else if (g.player_db.notify_when_unjoinable && is_joinable_session(player.session_type) && !is_joinable_session(new_session_type) && new_session_type != GSType::Invalid)
		{
			g_notification_service->push("Player DB", std::format("{} is no longer in a joinable session", player.name));
		}
		else if (g.player_db.notify_when_offline && player.session_type != GSType::Invalid && player.session_type != GSType::Unknown && new_session_type == GSType::Invalid)
		{
			g_notification_service->push("Player DB", std::format("{} is no longer online", player.name));
		}

		if (g.player_db.notify_on_session_type_change && (int)new_session_type >= (int)GSType::InviteOnly && (int)new_session_type < (int)GSType::Max)
		{
			g_notification_service->push("Player DB", std::format("{} is now in a{} {} session", player.name, new_session_type == GSType::InviteOnly ? "n" : "", get_session_type_str(new_session_type)));
		}
	}

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
			static auto last_update = std::chrono::high_resolution_clock::now() - 45s;
			while (g_running && g.player_db.update_player_online_states)
			{
				const auto cur = std::chrono::high_resolution_clock::now();
				if (cur - last_update > 45s)
				{
					g_fiber_pool->queue_job([this] {
						update_player_states(true);
					});
					last_update = cur;
				}

				std::this_thread::sleep_for(1s);
			}
		});
	}

	void player_database_service::update_player_states(bool tracked_only)
	{
		const auto player_count    = m_players.size();
		constexpr auto bucket_size = 100;

		std::vector<std::vector<rage::rlScHandle>> gamer_handle_buckets;
		gamer_handle_buckets.resize(std::ceil(player_count / (float)bucket_size));

		size_t i = 0;
		for (auto& player : m_players)
		{
			if (!tracked_only || player.second->notify_online)
			{
				gamer_handle_buckets[i / bucket_size].push_back(player.second->rockstar_id);
				i++;
			}
		}

		if (i == 0)
			return;

		for (auto& bucket : gamer_handle_buckets)
		{
			rage::rlTaskStatus status{};
			rage::rlQueryPresenceAttributesContext contexts[bucket_size][2]{};
			rage::rlQueryPresenceAttributesContext* contexts_per_player[bucket_size]{};

			for (int i = 0; i < bucket_size; i++)
			{
				contexts[i][0].m_presence_attibute_type = 3;
				strcpy(contexts[i][0].m_presence_attribute_key, "gstype");
				strcpy(contexts[i][0].m_presence_attribute_value, "-1");
				contexts[i][1].m_presence_attibute_type = 3;
				strcpy(contexts[i][1].m_presence_attribute_key, "gsinfo");
				contexts_per_player[i] = contexts[i];
			}

			if (g_pointers->m_sc.m_start_get_presence_attributes(0, bucket.data(), bucket.size(), contexts_per_player, 2, &status))
			{
				while (status.status == 1)
				{
					script::get_current()->yield();
				}

				if (status.status == 3)
				{
					for (size_t i = 0; i < bucket.size(); ++i)
					{
						if (const auto& it = m_players.find(bucket[i].m_rockstar_id); it != m_players.end())
						{
							rage::rlSessionInfo info{};
							info.m_session_token = -1;
							GSType gstype        = (GSType)atoi(contexts[i][0].m_presence_attribute_value);

							if (!g_pointers->m_gta.m_decode_session_info(&info, contexts[i][1].m_presence_attribute_value, nullptr))
								gstype = GSType::Invalid;

							if (it->second->session_type != gstype)
							{
								handle_session_type_change(*it->second, gstype);
							}
							else if (it->second->notify_online && it->second->session_id != info.m_session_token)
							{
								g_notification_service->push("Player DB",
								    std::format("{} has joined a new session", it->second->name));
							}

							it->second->session_type = gstype;
							it->second->session_id   = info.m_session_token;
						}
					}
				}
				else
				{
					LOG(WARNING) << "Presence attribute endpoint failed";
				}
			}
		}
	}

	bool player_database_service::is_joinable_session(GSType type)
	{
		return type == GSType::Public || type == GSType::OpenCrew;
	}

	const char* player_database_service::get_session_type_str(GSType type)
	{
		switch (type)
		{
		case GSType::Invalid: return "Offline";
		case GSType::InviteOnly: return "Invite Only";
		case GSType::FriendsOnly: return "Friends Only";
		case GSType::ClosedCrew: return "Closed Crew";
		case GSType::OpenCrew: return "Crew";
		case GSType::Job: return "In Mission";
		case GSType::Public: return "Public";
		case GSType::Modder: return "Unknown (Concealed By Modder)";
		}

		return "Unknown";
	}
}