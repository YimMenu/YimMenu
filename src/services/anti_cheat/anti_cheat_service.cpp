#include "anti_cheat_service.hpp"
#include "services/player_database/player_database_service.hpp"

namespace big
{
	anti_cheat_service::anti_cheat_service()
	{
		g_anti_cheat_service = this;
	}

	anti_cheat_service::~anti_cheat_service()
	{
		g_anti_cheat_service = nullptr;
	}

	bool anti_cheat_service::is_player_in_moddb(uint64_t rid)
	{
		for (const auto& [_, rid_s, __, _detections] : m_modders)
			if (rid_s == rid)
				return true;
		return false;
	}

	void anti_cheat_service::add_score_or_mark_as_modder(Player player, int score, std::string detections)
	{
		uint64_t rid = g_player_service->get_by_id(player)->get_net_data()->m_gamer_handle_2.m_rockstar_id;
		if (is_player_in_moddb(rid))
		{
			if (modders()[g_anti_cheat_service->get_moddb_player_from_rid(rid)].score)
				add_score_to_modder(rid, score, detections + ", ");
		}
		else
		{
			mark_as_modder(rid, score, detections + ", ");
		}
	}

	void anti_cheat_service::add_score_or_mark_as_modder(uint64_t rid, int score, std::string detections)
	{
		if (is_player_in_moddb(rid))
		{
			if (modders()[g_anti_cheat_service->get_moddb_player_from_rid(rid)].score)
				add_score_to_modder(rid, score, detections + ", ");
		}
		else
		{
			mark_as_modder(rid, score, detections + ", ");
		}
	}

	bool anti_cheat_service::mark_as_modder(Player player, int score, std::string detections)
	{
		rage::rlGamerInfo* net_player_data = g_player_service->get_by_id(player)->get_net_data();
		uint64_t rid = net_player_data->m_gamer_handle_2.m_rockstar_id;

		for (const auto& [_, rid_s, __, _detection] : m_modders)
			if (rid_s == rid)
				return false;

		m_modders.push_back({ net_player_data->m_name, rid, score, detections });
		// g_player_database_service->add_player_to_db(rid, net_player_data->m_name, "Modder", player); // TODO: Replace existing entry.

		LOG(INFO) << "Modder Detected: " << net_player_data->m_name << ", " << rid << ", " << score;

		g_notification_service->push("Modder Detected", net_player_data->m_name + detections);
		return true;
	}

	bool anti_cheat_service::mark_as_modder(uint64_t rid, int score, std::string detections)
	{
		rage::rlGamerInfo* net_player_data = g_player_service->get_by_rid(rid)->get_net_data();

		for (const auto& [_, rid_s, __, _detection] : m_modders)
			if (rid_s == rid)
				return false;

		m_modders.push_back({ net_player_data->m_name, rid, score, detections });
		// g_player_database_service->add_player_to_db(rid, net_player_data->m_name, "Modder", player); // TODO: Replace existing entry.

		LOG(INFO) << net_player_data->m_name << ", " << rid << ", " << score;

		g_notification_service->push("Modder Detected", std::format("{} - {}", net_player_data->m_name, detections));
		return true;
	}

	bool anti_cheat_service::add_score_to_modder(uint64_t rid, int score_to_add, std::string detections)
	{
		for (int i = 0; i < m_modders.size(); i++) // This is shit
		{
			if (m_modders[i].rid == rid)
			{
				m_modders[i].score = m_modders[i].score + score_to_add;
				if(m_modders[i].detections.find(detections) == std::string::npos) // FIXME: This is a shitty check but it's better then nothing.
					m_modders[i].detections = m_modders[i].detections + detections;
			}
		}

		return false;
	}

	int anti_cheat_service::get_moddb_player_from_rid(uint64_t rid)
	{
		for (int i = 0; i < m_modders.size(); i++) // This is shit
			if (m_modders[i].rid == rid)
				return i;

		return false;
	}

	int anti_cheat_service::modder_check(Player player)
	{
		int score = 0;
		Ped ped = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player);
		auto cplayer = g_player_service->get_by_id(player);
		CPed* cped = cplayer->get_ped();
		CPlayerInfo* cplayer_info = cplayer->get_player_info();
		rage::rlGamerInfo* net_player_data = cplayer->get_net_data();
		std::string detections;


		if (ped != 0 && cped != nullptr)
		{
			if (anti_cheat::is_in_godmode(ped, cped))
			{
				score++;
				detections += "Godmode, ";
			}

			if (anti_cheat::is_in_godmode_vehicle(ped, cped))
			{
				score++;
				detections += "Vehicle godmode, ";
			}

			if (!anti_cheat::is_health_normal(ped, cped))
			{
				score++;
				detections += "Weird health, ";
			}

			if (!anti_cheat::is_model_normal(cped))
			{
				score++;
				detections += "Non freemode model, ";
			}
		}

		if (player != 0 && cplayer != nullptr && cplayer_info != nullptr)
		{
			if (anti_cheat::is_using_damage_mods(cplayer_info))
			{
				score++;
				detections += "Damage mods, ";
			}

			if (anti_cheat::is_using_movement_mods(cplayer_info))
			{
				score++;
				detections += "Movement mods, ";
			}

			if (anti_cheat::is_using_frame_flags(cplayer_info))
			{
				score++;
				detections += "Frame flags, ";
			}

			if (!anti_cheat::is_name_normal(cplayer_info))
			{
				score++;
				detections += "Weird name, ";
			}

			if (anti_cheat::is_using_money_mods(player))
			{
				score++;
				detections += "Too much money, ";
			}
		}

		if (score >= 4 && !is_player_in_moddb(net_player_data->m_gamer_handle_2.m_rockstar_id)) 
		{
			mark_as_modder(cplayer->id(), score, detections);
		}
		else if (is_player_in_moddb(net_player_data->m_gamer_handle_2.m_rockstar_id))
		{
			int current_player = get_moddb_player_from_rid(net_player_data->m_gamer_handle_2.m_rockstar_id);
			int corrent_score = m_modders[current_player].score;
			if (corrent_score < score)
			{
				add_score_to_modder(net_player_data->m_gamer_handle_2.m_rockstar_id, score - corrent_score, detections);
			}
		}

		return score;
	}
}