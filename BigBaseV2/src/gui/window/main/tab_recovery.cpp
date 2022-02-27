#include "fiber_pool.hpp"
#include "util/player.hpp"
#include "main_tabs.hpp"
#include "natives.hpp"
#include "script.hpp"
#include "gta_util.hpp"
#include "features.hpp"

namespace big
{
	void tab_main::tab_recovery()
	{


		if (ImGui::BeginTabItem("Recovery"))
		{
			ImGui::Text("Set Current Character Level:");
			ImGui::SliderInt("##input_levels_self", &g->player.set_level, 0, 8000);
			if (ImGui::Button("Set Level"))
			{
				QUEUE_JOB_BEGIN_CLAUSE()
				{
					player::set_player_level(g->player.set_level);
				}QUEUE_JOB_END_CLAUSE
			}
			if (ImGui::Button("Max Character Stats"))
			{
				g_fiber_pool->queue_job([]
					{

						STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_SCRIPT_INCREASE_STAM"), 100, 1);
						STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_SCRIPT_INCREASE_SHO"), 100, 1);
						STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_SCRIPT_INCREASE_STRN"), 100, 1);
						STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_SCRIPT_INCREASE_STL"), 100, 1);
						STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_SCRIPT_INCREASE_FLY"), 100, 1);
						STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_SCRIPT_INCREASE_DRIV"), 100, 1);
						STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_SCRIPT_INCREASE_LUNG"), 100, 1);
					});
			}

			if (ImGui::BeginMenu("Cayo Perico Heist")) {

				if (ImGui::Button("Skip Heist Prep")) {
					g_fiber_pool->queue_job([] {
						STATS::STAT_SET_INT(RAGE_JOAAT("MP0_H4CNF_BS_GEN"), 131071, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP0_H4CNF_WEAPONS"), 1, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP0_H4CNF_WEP_DISRP"), 3, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP0_H4CNF_ARM_DISRP"), 3, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP0_H4CNF_HEL_DISRP"), 3, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP0_H4CNF_TARGET"), 5, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP0_H4CNF_BOLTCUT"), 4424, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP0_H4CNF_UNIFORM"), 5256, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP0_H4CNF_GRAPPEL"), 5156, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP0_H4CNF_TROJAN"), 1, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP0_H4LOOT_CASH_I"), 0, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP0_H4LOOT_CASH_I_SCOPED"), 0, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP0_H4LOOT_CASH_C"), 0, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP0_H4LOOT_CASH_C_SCOPED"), 0, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP0_H4LOOT_COKE_I"), 0, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP0_H4LOOT_COKE_I_SCOPED"), 0, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP0_H4LOOT_COKE_C"), 0, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP0_H4LOOT_COKE_C_SCOPED"), 0, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP0_H4LOOT_GOLD_I"), 16777215, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP0_H4LOOT_GOLD_I_SCOPED"), 16777215, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP0_H4LOOT_GOLD_C"), 255, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP0_H4LOOT_GOLD_C_SCOPED"), 255, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP0_H4LOOT_WEED_I"), 0, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP0_H4LOOT_WEED_I_SCOPED"), 0, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP0_H4LOOT_WEED_C"), 0, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP0_H4LOOT_WEED_C_SCOPED"), 0, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP0_H4LOOT_PAINT"), 127, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP0_H4LOOT_PAINT_SCOPED"), 127, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP0_H4LOOT_GOLD_V"), 598484, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP0_H4LOOT_PAINT_V"), 448863, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP0_H4_PROGRESS"), 124271, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP0_H4_MISSIONS"), 65535, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP0_H4_PLAYTHROUGH_STATUS"), 40000, TRUE);
						STATS::STAT_SAVE(0, 0, 3, 0);
						});
				}

				ImGui::Separator();

				if (ImGui::Button("Enable Hard Mode")) {
					g_fiber_pool->queue_job([] {
				
							STATS::STAT_SET_INT(RAGE_JOAAT("MP0_H4_PROGRESS"), 131055, TRUE);
							STATS::STAT_SAVE(0, 0, 3, 0);
					});
				}

				ImGui::EndMenu();
			}
			

			ImGui::EndTabItem();
		}
	}
}