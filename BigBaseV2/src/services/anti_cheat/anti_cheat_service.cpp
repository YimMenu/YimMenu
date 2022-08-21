#pragma 
#include "anti_cheat_service.hpp"

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
		for (const auto& [_, rid_s, __] : m_modders)
			if (rid_s == rid)
				return true;
		return false;
	}

	bool anti_cheat_service::mark_as_modder(Player player, int score)
	{
		auto cplayer = g_player_service->get_by_id(player);
		m_modders.push_back({ cplayer->get_name(), cplayer->get_net_data()->m_rockstar_id2, score });
	}

	int anti_cheat_service::modder_check(Player player)
	{
		int score = 0;
		Ped ped = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player);
		auto cplayer = g_player_service->get_by_id(player);
		CPed* cped = cplayer->get_ped();
		CPlayerInfo* cplayer_info = cplayer->get_player_info();
		rage::netPlayerData* net_player_data = cplayer->get_net_data();

		if (ped != 0 && cped != nullptr)
		{
			if (anti_cheat::is_in_godmode(ped, cped))
				score++;

			if (anti_cheat::is_in_godmode_vehicle(cped))
				score++;

			if (!anti_cheat::is_health_normal(ped, cped))
				score++;
		}

		if (player != 0 && cplayer != nullptr && cplayer_info != nullptr)
		{
			if (anti_cheat::is_using_damage_mods(cplayer_info))
				score++;

			if (anti_cheat::is_using_movement_mods(cplayer_info))
				score++;

			if (anti_cheat::is_using_frame_flags(cplayer_info))
				score++;

			if (!anti_cheat::is_name_normal(player))
				score++;

			if (anti_cheat::is_using_money_mods(player))
				score++;
		}

		if (score >= 4 && !is_player_in_moddb(net_player_data->m_rockstar_id2))
		{
			m_modders.push_back({ cplayer->get_name(), net_player_data->m_rockstar_id2, score });
			LOG(INFO) << cplayer->get_name() << ", " << net_player_data->m_rockstar_id2 << ", " << score;

			g_notification_service->push("Modder Detected", cplayer->get_name());
		}

		return score;
	}
}