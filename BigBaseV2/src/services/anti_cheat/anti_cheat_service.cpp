#pragma 
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

	bool anti_cheat_service::mark_as_modder(Player player, int score, std::string detections)
	{
		auto cplayer = g_player_service->get_by_id(player);

		for (const auto& [_, rid_s, __, _detection] : m_modders)
			if (rid_s == cplayer->get_net_data()->m_gamer_handle_2.m_rockstar_id)
				return false;

		m_modders.push_back({ cplayer->get_name(), cplayer->get_net_data()->m_gamer_handle_2.m_rockstar_id, score, detections });
		g_player_database_service->add_player_to_db(cplayer->get_net_data()->m_gamer_handle_2.m_rockstar_id, cplayer->get_name(), "Modder", player);

		LOG(INFO) << cplayer->get_name() << ", " << cplayer->get_net_data()->m_gamer_handle_2.m_rockstar_id << ", " << score;

		g_notification_service->push("Modder Detected", cplayer->get_name() + detections);
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

			if (anti_cheat::is_in_godmode_vehicle(cped))
			{
				score++;
				detections += "Vehicle godmode, ";
			}

			if (!anti_cheat::is_health_normal(ped, cped))
			{
				score++;
				detections += "Weird health, ";
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

			if (!anti_cheat::is_name_normal(player))
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