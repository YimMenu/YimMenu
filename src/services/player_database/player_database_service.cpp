#include "player_database_service.hpp"
#include "services/players/player_service.hpp"
#include "util/vehicle.hpp"
#include "pointers.hpp"


namespace big
{
	player_database_service::player_database_service()
	{
		g_player_database_service = this;
		load_players();
	}

	player_database_service::~player_database_service()
	{
		g_player_database_service = nullptr;
	}

	void player_database_service::save_players()
	{
		const auto file = get_players_folder().get_file("players.json");

		std::ofstream file_stream(file.get_path(), std::ios::out | std::ios::trunc);
		nlohmann::json players_json;

		players_json[players_key] = get_players_json();

		file_stream << players_json.dump(4);

		file_stream.close();
	}

	void player_database_service::load_players()
	{
		const auto file = get_players_folder().get_file("players.json");

		if (file.exists())
		{
			std::ifstream file_stream(file.get_path());

			nlohmann::json players_json;

			file_stream >> players_json;
			file_stream.close();

			load_players_from_json(players_json);
		}
		else
		{
			create_dummy_player();
			save_players();
		}
	}

	void player_database_service::create_dummy_player()
	{
		add_player_to_db(0, "Dummy", "unknown");
	}

	void player_database_service::add_player_to_db(uint64_t rid, std::string name, std::string relationship)
	{
		if (!is_player_in_db(rid))
		{
			g_player_database_service->m_player_list.push_back({ name, rid, relationship, 33 });
			save_players();
		}
	}

	void player_database_service::add_player_to_db(uint64_t rid, std::string name, std::string relationship, Player player)
	{
		if (!is_player_in_db(rid))
		{
			g_player_database_service->m_player_list.push_back({ name, rid, relationship, player });
			save_players();
		}
	}

	bool player_database_service::is_player_in_db(uint64_t rid)
	{
		for (const auto& [name_, rid_, relationship_, tmp_player_id] : g_player_database_service->m_player_list)
		{
			if (rid_ == rid)
			{
				return true;
			}
		}

		return false;
	}

	player_l player_database_service::get_player_from_db(uint64_t rid)
	{
		for (const auto& i : g_player_database_service->m_player_list)
		{
			if (i.rid == rid)
			{
				return i;
			}
		}
		return g_player_database_service->m_player_list[0];
	}

	void player_database_service::load_players_from_json(nlohmann::json player_json)
	{
		std::vector<nlohmann::json> players = player_json[players_key];
		
		for (const auto& j : players)
		{
			const auto name = j.at(name_key);
			const auto rid = j.at(rid_key);
			const auto relationship = j.at(relationship_key);
			g_player_database_service->m_player_list.push_back({ name, rid, relationship, 33 });
		}
	}

	std::vector<nlohmann::json> player_database_service::get_players_json()
	{
		std::vector<nlohmann::json> players_json_v;
		for (const auto& [name, rid, relation, tmp_player_id] : g_player_database_service->m_player_list)
		{
			if (tmp_player_id != 33)
			{
				players_json_v.push_back(get_player_json_full(rid, tmp_player_id, relation));
			}
			else
			{
				players_json_v.push_back(get_player_json_small(rid, name, relation));
			}
		}
		return players_json_v;
	}

	nlohmann::json player_database_service::get_player_json_small(uint64_t rid, std::string name, std::string relationship)
	{
		nlohmann::json player_json;
		player_json[name_key] = name;
		player_json[rid_key] = rid;
		player_json[relationship_key] = relationship;
		return player_json;
	}

	nlohmann::json player_database_service::get_player_json_full(uint64_t rid, Player player, std::string relationship) // TODO: Rename this.
	{
		nlohmann::json player_json;
		if (player != 33)
		{
			auto cplayer = g_player_service->get_by_id(player);

			player_json[name_key] = cplayer->get_name();
			player_json[rid_key] = rid;
			player_json[relationship_key] = relationship;
		}
		else 
		{
			g_notification_service->push_error("Player database", "Player id not found");
			LOG(WARNING) << "Player id not found";
		}

		return player_json;
	}

	big::folder player_database_service::get_players_folder()
	{
		const auto folder = g_file_manager->get_project_folder("./saved_players");

		return folder;
	}
}
