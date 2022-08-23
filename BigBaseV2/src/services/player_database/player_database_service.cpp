#include "player_database_service.hpp"
#include "services/players/player_service.hpp"
#include "util/vehicle.hpp"
#include "pointers.hpp"


namespace big
{
	player_database_service::player_database_service()
	{
		g_player_database_service = this;
	}

	player_database_service::~player_database_service()
	{
		g_player_database_service = nullptr;
	}

	void player_database_service::save_players()
	{
		const auto file = check_players_folder().get_file("players.json");

		std::ofstream file_stream(file.get_path(), std::ios::out | std::ios::trunc);

		for (const auto& [name, rid, relation, tmp_player_id] : g_player_database_service->m_player_list)
		{
			if (tmp_player_id) 
			{
				file_stream << get_player_json(rid, tmp_player_id, relation).dump(4);
			}
			else 
			{
				file_stream << get_player_json(rid, name, relation).dump(4);
			}
		}

		file_stream.close();
	}

	void player_database_service::load_players()
	{
		const auto file = check_players_folder().get_file("players.json");

		std::ifstream file_stream(file.get_path());

		nlohmann::json players_json;

		file_stream >> players_json;
		file_stream.close();

		load_players_from_json(players_json);
	}

	void player_database_service::add_player_to_db(uint64_t rid, std::string name, std::string relationship)
	{
		g_player_database_service->m_player_list.push_back({ name, rid, relationship, 0 });
		save_players();
	}


	void player_database_service::load_players_from_json(nlohmann::json player_json)
	{
		std::vector<nlohmann::json> players = player_json[players_key];
		for (const auto& j : players)
		{
			g_player_database_service->m_player_list.push_back({ j.at(name_key), j.at(rid_key), j.at(relation_key), 0 });
		}
	}

	nlohmann::json player_database_service::get_player_json(uint64_t rid, Player player, std::string relation)
	{
		nlohmann::json players_json;
		auto cplayer = g_player_service->get_by_id(player);

		players_json[cplayer->get_name()] = get_player_json_full(rid, player, relation);
		
		return players_json;
	}

	nlohmann::json player_database_service::get_player_json(uint64_t rid, std::string name, std::string relation)
	{
		nlohmann::json players_json;

		players_json[name] = get_player_json_small(rid, name, relation);

		return players_json;
	}

	nlohmann::json player_database_service::get_player_json_small(uint64_t rid, std::string name, std::string relation)
	{
		nlohmann::json player_json;
		player_json[name_key] = name;
		player_json[rid_key] = rid;
		player_json[ipv4_key] = "Unknown";
		player_json[relation_key] = relation;
		player_json[frame_flags_key] = "Unknown";
		return player_json;
	}

	nlohmann::json player_database_service::get_player_json_full(uint64_t rid, Player player, std::string relation)
	{
		nlohmann::json player_json;
		if (player)
		{
			Ped ped = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player);
			auto cplayer = g_player_service->get_by_id(player);
			CPed* cped = cplayer->get_ped();
			CPlayerInfo* cplayer_info = cplayer->get_player_info();
			rage::netPlayerData* net_player_data = cplayer->get_net_data();

			player_json[name_key] = cplayer->get_name();
			player_json[rid_key] = rid;
			player_json[ipv4_key] = net_player_data->m_external_ip.m_field1 << net_player_data->m_external_ip.m_field2 << net_player_data->m_external_ip.m_field3 << net_player_data->m_external_ip.m_field4;
			player_json[relation_key] = relation;
			player_json[frame_flags_key] = cplayer_info->m_frame_flags;
		}
		else 
		{
			g_notification_service->push_error("Player database", "Player id not found");
			LOG(WARNING) << "Player id not found";
		}

		return player_json;
	}

	big::folder player_database_service::check_players_folder()
	{
		const auto folder = g_file_manager->get_project_folder("./saved_players");

		return folder;
	}
}
