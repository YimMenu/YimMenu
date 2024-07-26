#include "player_database_service.hpp"

#include "backend/bool_command.hpp"
#include "file_manager.hpp"
#include "gta/enums.hpp"
#include "hooking/hooking.hpp"
#include "pointers.hpp"
#include "util/session.hpp"

namespace big
{
	bool_command g_player_db_auto_update_online_states("player_db_auto_update_states", "AUTO_UPDATE_STATES", "AUTO_UPDATE_STATES_DESC",
	    g.player_db.update_player_online_states);

	const char* player_database_service::get_name_by_content_id(const std::string& content_id)
	{
		if (NETWORK::UGC_QUERY_BY_CONTENT_ID(content_id.c_str(), false, "gta5mission"))
		{
			while (NETWORK::UGC_IS_GETTING())
				script::get_current()->yield();

			if (!NETWORK::UGC_DID_GET_SUCCEED())
				return "";

			return NETWORK::UGC_GET_CONTENT_NAME(0);
		}

		return "";
	}

	void player_database_service::handle_session_type_change(persistent_player& player, GSType new_session_type)
	{
		if (!player.notify_online)
			return;

		if (g.player_db.notify_when_joinable && !is_joinable_session(player.session_type, player.game_mode) && is_joinable_session(new_session_type, player.game_mode))
		{
			g_notification_service.push_success("Player DB", std::format("{} is now in a joinable session", player.name));
		}
		else if (g.player_db.notify_when_online && (player.session_type == GSType::Invalid || player.session_type == GSType::Unknown) && new_session_type != GSType::Invalid)
		{
			g_notification_service.push_success("Player DB", std::format("{} is now online", player.name));
		}
		else if (g.player_db.notify_when_unjoinable && is_joinable_session(player.session_type, player.game_mode) && !is_joinable_session(new_session_type, player.game_mode) && new_session_type != GSType::Invalid)
		{
			g_notification_service.push("Player DB", std::format("{} is no longer in a joinable session", player.name));
		}
		else if (g.player_db.notify_when_offline && player.session_type != GSType::Invalid && player.session_type != GSType::Unknown && new_session_type == GSType::Invalid)
		{
			g_notification_service.push("Player DB", std::format("{} is no longer online", player.name));
		}

		if (g.player_db.notify_on_session_type_change && (int)new_session_type >= (int)GSType::InviteOnly && (int)new_session_type < (int)GSType::Max)
		{
			g_notification_service.push("Player DB", std::format("{} is now in a{} {} session", player.name, new_session_type == GSType::InviteOnly ? "n" : "", get_session_type_str(new_session_type)));
		}
	}

	void player_database_service::handle_game_mode_change(uint64_t rid, GameMode old_game_mode, GameMode new_game_mode, std::string mission_id, std::string mission_name)
	{
		const char* old_game_mode_str = get_game_mode_str(old_game_mode);
		const char* new_game_mode_str = get_game_mode_str(new_game_mode);
		auto player                   = g_player_database_service->get_player_by_rockstar_id(rid);

		if (new_game_mode == GameMode::None && old_game_mode != GameMode::None && old_game_mode_str != "None")
		{
			g_notification_service.push("Player DB", std::format("{} is no longer in a {}", player->name, old_game_mode_str));
			return;
		}

		if (!can_fetch_name(new_game_mode))
		{
			if (new_game_mode_str != "None")
				g_notification_service.push("Player DB", std::format("{} is now in a {}", player->name, new_game_mode_str));

			return;
		}

		if (mission_name.empty())
		{
			mission_name = get_name_by_content_id(mission_id);
		}

		if (mission_name.empty())
		{
			g_notification_service.push("Player DB", std::format("{} is now in a {}", player->name, new_game_mode_str));
			return;
		}

		g_notification_service.push("Player DB", std::format("{} has joined the {} \"{}\"", player->name, new_game_mode_str, mission_name));
		player->game_mode_name = mission_name;
	}

	void player_database_service::handle_join_redirect()
	{
		if (!*g_pointers->m_gta.m_presence_data)
			return;

		int current_preference_level = 0;
		rage::rlSessionInfo preferred_session{};

		for (auto& player : m_players)
		{
			if (player.second->join_redirect && is_joinable_session(player.second->session_type, player.second->game_mode))
			{
				current_preference_level = player.second->join_redirect_preference;
				preferred_session        = player.second->redirect_info;
			}
		}

		if (current_preference_level != 0)
		{
			join_being_redirected = true;
			char buf[0x100]{};
			g_pointers->m_gta.m_encode_session_info(&preferred_session, buf, 0xA9, nullptr);

			g_hooking->get_original<hooks::update_presence_attribute_string>()(*g_pointers->m_gta.m_presence_data, 0, (char*)"gsinfo", buf);
			g_hooking->get_original<hooks::update_presence_attribute_int>()(*g_pointers->m_gta.m_presence_data,
			    0,
			    (char*)"gstok",
			    preferred_session.m_session_token);
			g_hooking->get_original<hooks::update_presence_attribute_int>()(*g_pointers->m_gta.m_presence_data,
			    0,
			    (char*)"gsid",
			    preferred_session.m_unk);
			g_hooking->get_original<hooks::update_presence_attribute_int>()(*g_pointers->m_gta.m_presence_data, 0, (char*)"gstype", 5);
			g_hooking->get_original<hooks::update_presence_attribute_int>()(*g_pointers->m_gta.m_presence_data, 0, (char*)"gshost", 0);
			g_hooking->get_original<hooks::update_presence_attribute_int>()(*g_pointers->m_gta.m_presence_data, 0, (char*)"gsjoin", 1);
		}
		else
		{
			join_being_redirected = false;
		}
	}

	player_database_service::player_database_service() :
	    m_file_path(g_file_manager.get_project_file("./players.json").get_path())
	{
		load();

		start_update_loop();

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

	std::unordered_map<uint64_t, std::shared_ptr<persistent_player>>& player_database_service::get_players()
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

	void player_database_service::remove_filtered_players(bool filter_modder, bool filter_trust, bool filter_block_join, bool filter_track_player)
	{
		for (auto it = m_players.begin(); it != m_players.end();)
		{
			auto player = it->second;
			if ((filter_modder && player->is_modder) || (filter_trust && player->is_trusted)
			    || (filter_block_join && player->block_join) || (filter_track_player && player->notify_online))
			{
				it = m_players.erase(it);
			}
			else
			{
				++it;
			}
		}

		for (auto it = m_sorted_players.begin(); it != m_sorted_players.end();)
		{
			auto player = it->second;
			if ((filter_modder && player->is_modder) || (filter_trust && player->is_trusted)
			    || (filter_block_join && player->block_join) || (filter_track_player && player->notify_online))
			{
				it = m_sorted_players.erase(it);
			}
			else
			{
				++it;
			}
		}
	}

	std::shared_ptr<persistent_player> player_database_service::get_player_by_rockstar_id(uint64_t rockstar_id)
	{
		if (m_players.contains(rockstar_id))
			return m_players[rockstar_id];
		return nullptr;
	}

	std::shared_ptr<persistent_player> player_database_service::get_or_create_player(player_ptr player)
	{
		if (m_players.contains(player->get_rockstar_id()))
			return m_players[player->get_rockstar_id()];
		else
		{
			auto player_ptr = add_player(player->get_rockstar_id(), player->get_name());
			save();
			return player_ptr;
		}
	}

	void player_database_service::update_rockstar_id(uint64_t old, uint64_t _new)
	{
		auto player  = m_players.extract(old);
		player.key() = _new;

		m_players.insert(std::move(player));
	}

	void player_database_service::remove_rockstar_id(uint64_t rockstar_id)
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
		// So that it doesnt immediately exit the first time.
		static bool first_time = true;

		if (!g.player_db.update_player_online_states)
		{
			first_time = false;
			return;
		}

		g_thread_pool->push([this] {
			if (first_time)
			{
				while (!g_running)
				{
					std::this_thread::yield();
				}

				first_time = false;
			}

			static auto last_update = std::chrono::high_resolution_clock::now() - 45s;

			while (g_running && g.player_db.update_player_online_states)
			{
				const auto cur = std::chrono::high_resolution_clock::now();
				if (cur - last_update > 45s && !updating)
				{
					updating = true;
					g_fiber_pool->queue_job([this] {
						update_player_states(true);
						updating = false;
						last_update = std::chrono::high_resolution_clock::now();
					});
				}

				std::this_thread::sleep_for(1s);
			}
		});
	}

	void player_database_service::update_player_states(bool tracked_only)
	{
		constexpr auto bucket_size = 100;

		std::vector<std::vector<rage::rlScHandle>> gamer_handle_buckets{};

		size_t i = 0;
		for (auto& player : m_players)
		{
			if (!tracked_only || (player.second->notify_online || player.second->join_redirect))
			{
				if (gamer_handle_buckets.size() <= i / bucket_size)
					gamer_handle_buckets.push_back({});

				if (player.second->rockstar_id == 0 || ((int64_t)player.second->rockstar_id) < 0)
					continue;

				gamer_handle_buckets[i / bucket_size].push_back(player.second->rockstar_id);
				i++;
			}
		}

		if (i == 0)
			return;

		for (auto& bucket : gamer_handle_buckets)
		{
			rage::rlScTaskStatus status{};

			// TODO: big sized object on the stack, might be a problem in the future
			rage::rlQueryPresenceAttributesContext contexts[bucket_size][9]{};
			rage::rlQueryPresenceAttributesContext* contexts_per_player[bucket_size]{};

			for (int i = 0; i < bucket.size(); i++)
			{
				contexts[i][0].m_presence_attibute_type = 1;
				strcpy(contexts[i][0].m_presence_attribute_key, "gstype");
				contexts[i][0].m_presence_attribute_int_value = -1;
				contexts[i][1].m_presence_attibute_type       = 3;
				strcpy(contexts[i][1].m_presence_attribute_key, "gsinfo");
				contexts[i][2].m_presence_attibute_type = 1;
				strcpy(contexts[i][2].m_presence_attribute_key, "sctv");
				contexts[i][3].m_presence_attibute_type = 1;
				strcpy(contexts[i][3].m_presence_attribute_key, "gshost");
				contexts[i][4].m_presence_attibute_type = 3;
				strcpy(contexts[i][4].m_presence_attribute_key, "trinfo");
				contexts[i][5].m_presence_attibute_type = 1;
				strcpy(contexts[i][5].m_presence_attribute_key, "trhost");
				contexts[i][6].m_presence_attibute_type = 3;
				strcpy(contexts[i][6].m_presence_attribute_key, "mp_mis_str");
				contexts[i][7].m_presence_attibute_type = 3;
				strcpy(contexts[i][7].m_presence_attribute_key, "mp_mis_id");
				contexts[i][8].m_presence_attibute_type = 1;
				strcpy(contexts[i][8].m_presence_attribute_key, "mp_curr_gamemode");
				contexts_per_player[i] = contexts[i];
			}

			if (g_pointers->m_sc.m_start_get_presence_attributes(0, bucket.data(), bucket.size(), contexts_per_player, 9, &status))
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
							rage::rlSessionInfo transition_info{};
							info.m_session_token            = -1;
							transition_info.m_session_token = -1;
							GSType gstype           = (GSType)(int)contexts[i][0].m_presence_attribute_int_value;
							bool is_spectating      = (bool)contexts[i][2].m_presence_attribute_int_value;
							bool is_host_of_session = (bool)contexts[i][3].m_presence_attribute_int_value;
							bool is_host_of_transition_session = (bool)contexts[i][5].m_presence_attribute_int_value;
							GameMode game_mode       = (GameMode)contexts[i][8].m_presence_attribute_int_value;
							std::string mission_id   = contexts[i][7].m_presence_attribute_string_value;
							std::string mission_name = contexts[i][6].m_presence_attribute_string_value;

							if (contexts[i][1].m_presence_attribute_string_value[0] == 0
							    || !g_pointers->m_gta.m_decode_session_info(&info, contexts[i][1].m_presence_attribute_string_value, nullptr))
								gstype = GSType::Invalid;

							if (can_fetch_name(game_mode) && mission_name.empty() && mission_id.empty())
								game_mode = GameMode::None;

							if (contexts[i][4].m_presence_attribute_string_value[0] == 0
							    || !g_pointers->m_gta.m_decode_session_info(&transition_info, contexts[i][4].m_presence_attribute_string_value, nullptr))
								transition_info.m_session_token = -1;

							if (it->second->session_type != gstype)
							{
								handle_session_type_change(*it->second, gstype);
							}
							else if (it->second->notify_online && it->second->session_id != info.m_session_token
							    && g.player_db.notify_on_session_change)
							{
								g_notification_service.push("Player DB",
								    std::format("{} has joined a new session", it->second->name));
							}

							if (gstype != GSType::Invalid)
							{
								if (it->second->notify_online && is_spectating != it->second->is_spectating
								    && g.player_db.notify_on_spectator_change)
								{
									if (is_spectating)
									{
										g_notification_service.push("Player DB",
										    std::format("{} is now spectating", it->second->name));
									}
									else
									{
										g_notification_service.push("Player DB",
										    std::format("{} is no longer spectating", it->second->name));
									}
								}

								if (it->second->notify_online && is_host_of_session != it->second->is_host_of_session
								    && g.player_db.notify_on_become_host && is_host_of_session && it->second->session_id == info.m_session_token)
								{
									g_notification_service.push("Player DB",
									    std::format("{} is now the host of their session", it->second->name));
								}

								if (it->second->notify_online && g.player_db.notify_on_transition_change
								    && transition_info.m_session_token != -1 && it->second->transition_session_id == -1)
								{
									if (is_host_of_transition_session)
									{
										g_notification_service.push("Player DB",
										    std::format("{} has hosted a job lobby", it->second->name));
									}
									else
									{
										g_notification_service.push("Player DB",
										    std::format("{} has joined a job lobby", it->second->name));
									}
								}
								else if (it->second->notify_online && g.player_db.notify_on_transition_change
								    && transition_info.m_session_token == -1 && it->second->transition_session_id != -1)
								{
									g_notification_service.push("Player DB",
									    std::format("{} is no longer in a job lobby", it->second->name));
								}

								if (it->second->notify_online && g.player_db.notify_on_mission_change
								    && game_mode != it->second->game_mode)
								{
									auto rid           = it->second->rockstar_id;
									auto old_game_mode = it->second->game_mode;
									g_fiber_pool->queue_job([rid, old_game_mode, game_mode, mission_id, mission_name] {
										handle_game_mode_change(rid, old_game_mode, game_mode, mission_id, mission_name);
									});
								}
							}

							if (it->second->join_redirect)
								it->second->redirect_info = info;

							it->second->session_type                  = gstype;
							it->second->session_id                    = info.m_session_token;
							it->second->is_spectating                 = is_spectating;
							it->second->is_host_of_session            = is_host_of_session;
							it->second->transition_session_id         = transition_info.m_session_token;
							it->second->is_host_of_transition_session = is_host_of_transition_session;
							it->second->game_mode                     = game_mode;
							it->second->game_mode_id                  = mission_id;
							it->second->game_mode_name                = mission_name;
						}
					}
					handle_join_redirect();
				}
				else
				{
					LOG(WARNING) << "Presence attribute endpoint failed";
				}
			}
		}
	}

	bool player_database_service::is_joinable_session(GSType type, GameMode mode)
	{
		return (type == GSType::Public || type == GSType::OpenCrew) && !can_fetch_name(mode);
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

	const char* player_database_service::get_game_mode_str(GameMode mode)
	{
		switch (mode)
		{
		case GameMode::None: return "None";
		case GameMode::Mission: return "Mission";
		case GameMode::Deathmatch: return "Deathmatch";
		case GameMode::Race: return "Race";
		case GameMode::Survival: return "Survival";
		case GameMode::GangAttack: return "Gang Attack";
		case GameMode::Golf: return "Golf";
		case GameMode::Tennis: return "Tennis";
		case GameMode::ShootingRange: return "Shooting Range";
		}

		return "Unknown";
	}

	bool player_database_service::can_fetch_name(GameMode mode)
	{
		switch (mode)
		{
		case GameMode::Mission:
		case GameMode::Deathmatch:
		case GameMode::Race:
		case GameMode::Survival: return true;
		}

		return false;
	}
}
