#include "core/data/language_codes.hpp"
#include "core/scr_globals.hpp"
#include "natives.hpp"
#include "views/view.hpp"

#include <script/globals/GPBD_FM.hpp>
#include <script/globals/GPBD_FM_3.hpp>
#include <script/globals/GlobalPlayerBD.hpp>

namespace big
{
	const char* get_nat_type_str(int type)
	{
		switch (type)
		{
		case 1: return "Open";
		case 2: return "Moderate";
		case 3: return "Strict";
		}

		return "Unknown";
	}

	void view::player_info()
	{
		ImGui::BeginGroup();
		components::sub_title("Info");

		if (ImGui::BeginListBox("##infobox", get_listbox_dimensions()))
		{
			uint32_t ped_damage_bits = 0;
			uint32_t ped_task_flag   = 0;
			uint32_t ped_health      = 0;
			uint32_t ped_maxhealth   = 0;
			uint32_t veh_damage_bits = 0;

			if (CPed* ped = g_player_service->get_selected()->get_ped(); ped != nullptr)
			{
				ped_damage_bits = ped->m_damage_bits;
				ped_task_flag   = ped->m_ped_task_flag;
				ped_health      = ped->m_health;
				ped_maxhealth   = ped->m_maxhealth;
			}

			components::options_modal(
			    "Extra Info",
			    [ped_health, ped_maxhealth] {
				    ImGui::BeginGroup();

				    auto id = g_player_service->get_selected()->id();

				    if (id != -1)
				    {
					    auto& stats     = scr_globals::gpbd_fm_1.as<GPBD_FM*>()->Entries[id].PlayerStats;
					    auto& boss_goon = scr_globals::gpbd_fm_3.as<GPBD_FM_3*>()->Entries[id].BossGoon;

					    const auto money  = reinterpret_cast<uint64_t&>(stats.Money);
					    const auto wallet = reinterpret_cast<uint64_t&>(stats.WalletBalance);

					    if (boss_goon.Language >= 0 && boss_goon.Language < 13)
						    ImGui::Text("Language: %s", languages[boss_goon.Language].name);

					    ImGui::Text("Money In Wallet: %llu", wallet);
					    ImGui::Text("Money In Bank: %llu", money - wallet);
					    ImGui::Text("Total Money: %llu", money);
					    ImGui::Text("Rank: %d (RP %d)", stats.Rank, stats.RP);
					    ImGui::Text("Health: %d (MaxHealth: %d)", ped_health, ped_maxhealth);
					    ImGui::Text("K/D Ratio: %f", stats.KdRatio);
					    ImGui::Text("Kills On Players: %d", stats.KillsOnPlayers);
					    ImGui::Text("Deaths By Players: %d", stats.DeathsByPlayers);
				    }

				    ImGui::EndGroup();

				    ImGui::SameLine();

				    ImGui::BeginGroup();

				    ImGui::Text("NAT Type: %s", get_nat_type_str(g_player_service->get_selected()->get_net_data()->m_nat_type));

				    ImGui::EndGroup();

				    ImGui::Separator();

				    ImGui::Checkbox("Block Explosions", &g_player_service->get_selected()->block_explosions);
				    ImGui::Checkbox("Block Clone Creates", &g_player_service->get_selected()->block_clone_create);
				    ImGui::Checkbox("Block Clone Syncs", &g_player_service->get_selected()->block_clone_sync);
				    ImGui::Checkbox("Block Network Events", &g_player_service->get_selected()->block_net_events);
				    ImGui::Checkbox("Log Clones", &g_player_service->get_selected()->log_clones);
			    },
			    false,
			    "Extra Info");

			ImGui::SameLine();

			if (ImGui::SmallButton("SC Profile"))
				g_fiber_pool->queue_job([] {
					uint64_t gamerHandle[13];
					NETWORK::NETWORK_HANDLE_FROM_PLAYER(g_player_service->get_selected()->id(), (Any*)&gamerHandle, 13);
					NETWORK::NETWORK_SHOW_PROFILE_UI((Any*)&gamerHandle);
				});

			ImGui::EndListBox();
		}
		ImGui::EndGroup();
	}
}
