#include "main_tabs.hpp"
#include "util/system.hpp"
#include "features.hpp"
#include "fiber_pool.hpp"
#include "natives.hpp"
#include <widgets/imgui_hotkey.hpp>


namespace big
{
	void tab_main::tab_settings()
	{
		if (ImGui::BeginTabItem("Settings"))
		{
			if (ImGui::TreeNode("Protections"))
			{
				ImGui::Checkbox("Bounty", &g.protections.script_events.bounty);
				ImGui::Checkbox("CEO Ban", &g.protections.script_events.ceo_ban);
				ImGui::Checkbox("CEO Kick", &g.protections.script_events.ceo_kick);
				ImGui::Checkbox("CEO Money", &g.protections.script_events.ceo_money);
				ImGui::Checkbox("Wanted Level", &g.protections.script_events.clear_wanted_level);
				ImGui::Checkbox("Fake Deposit", &g.protections.script_events.fake_deposit);
				ImGui::Checkbox("Force Mission", &g.protections.script_events.force_mission);
				ImGui::Checkbox("Force Teleport", &g.protections.script_events.force_teleport);
				ImGui::Checkbox("GTA Banner", &g.protections.script_events.gta_banner);
				ImGui::Checkbox("Destroy Personal Vehicle", &g.protections.script_events.personal_vehicle_destroyed);
				ImGui::Checkbox("Remote Off Radar", &g.protections.script_events.remote_off_radar);
				ImGui::Checkbox("Send to Cutscene", &g.protections.script_events.send_to_cutscene);
				ImGui::Checkbox("Send to Island", &g.protections.script_events.send_to_island);
				ImGui::Checkbox("Sound Spam", &g.protections.script_events.sound_spam);
				ImGui::Checkbox("Spectate", &g.protections.script_events.spectate);
				ImGui::Checkbox("Transaction Error", &g.protections.script_events.transaction_error);
				ImGui::Checkbox("Vehicle Kick", &g.protections.script_events.vehicle_kick);

				ImGui::TreePop();
			}

			ImGui::Separator();

			if (ImGui::Button("Reset cooldown"))
			{
				g_fiber_pool->queue_job([] {
					STATS::STAT_SET_INT(RAGE_JOAAT("MPPLY_CASINO_CHIPS_WON_GD"), 0, TRUE);
					STATS::STAT_SET_INT(RAGE_JOAAT("MPPLY_CASINO_CHIPS_WONTIM"), 0, TRUE);
					STATS::STAT_SET_INT(RAGE_JOAAT("MPPLY_CASINO_CHIPS_PUR_GD"), 0, TRUE);
					STATS::STAT_SET_INT(RAGE_JOAAT("MPPLY_CASINO_CHIPS_PURTIM"), 0, TRUE);
					STATS::STAT_SET_INT(RAGE_JOAAT("MPPLY_CASINO_MEM_BONUS"), 0, TRUE);
					STATS::STAT_SET_INT(RAGE_JOAAT("MPPLY_CAS_TIME_GMBLNG_0"), 0, TRUE);
					STATS::STAT_SET_INT(RAGE_JOAAT("MPPLY_CAS_TIME_GMBLNG_1"), 0, TRUE);
					STATS::STAT_SET_INT(RAGE_JOAAT("MPPLY_CAS_TIME_GMBLNG_2"), 0, TRUE);
					STATS::STAT_SET_INT(RAGE_JOAAT("MPPLY_CAS_TIME_GMBLNG_3"), 0, TRUE);
					STATS::STAT_SET_INT(RAGE_JOAAT("MPPLY_CAS_TIME_GMBLNG_4"), 0, TRUE);
					STATS::STAT_SET_INT(RAGE_JOAAT("MPPLY_CAS_TIME_GMBLNG_5"), 0, TRUE);
					STATS::STAT_SET_INT(RAGE_JOAAT("MPPLY_CAS_TIME_GMBLNG_6"), 0, TRUE);
					STATS::STAT_SET_INT(RAGE_JOAAT("MPPLY_CAS_TIME_GMBLNG_7"), 0, TRUE);
					STATS::STAT_SET_INT(RAGE_JOAAT("MPPLY_CAS_TIME_GMBLNG_8"), 0, TRUE);
					STATS::STAT_SET_INT(RAGE_JOAAT("MPPLY_CAS_TIME_GMBLNG_9"), 0, TRUE);
					STATS::STAT_SET_INT(RAGE_JOAAT("MPPLY_CAS_TIME_PLYING_0"), 0, TRUE);
					STATS::STAT_SET_INT(RAGE_JOAAT("MPPLY_CAS_TIME_PLYING_1"), 0, TRUE);
					STATS::STAT_SET_INT(RAGE_JOAAT("MPPLY_CAS_TIME_PLYING_2"), 0, TRUE);
					STATS::STAT_SET_INT(RAGE_JOAAT("MPPLY_CAS_TIME_PLYING_3"), 0, TRUE);
					STATS::STAT_SET_INT(RAGE_JOAAT("MPPLY_CAS_TIME_PLYING_4"), 0, TRUE);
					STATS::STAT_SET_INT(RAGE_JOAAT("MPPLY_CAS_TIME_PLYING_5"), 0, TRUE);
					STATS::STAT_SET_INT(RAGE_JOAAT("MPPLY_CAS_TIME_PLYING_6"), 0, TRUE);
					STATS::STAT_SET_INT(RAGE_JOAAT("MPPLY_CAS_TIME_PLYING_7"), 0, TRUE);
					STATS::STAT_SET_INT(RAGE_JOAAT("MPPLY_CAS_TIME_PLYING_8"), 0, TRUE);
					STATS::STAT_SET_INT(RAGE_JOAAT("MPPLY_CAS_TIME_PLYING_9"), 0, TRUE);
					STATS::STAT_SET_INT(RAGE_JOAAT("MPPLY_CASINO_BAN_TIME"), 0, TRUE);
					STATS::STAT_SET_INT(RAGE_JOAAT("MPPLY_CASINO_GMBLNG_GD"), 0, TRUE);
					STATS::STAT_SET_INT(RAGE_JOAAT("MPPLY_CAS_CUR_GMBLNG_GD"), 0, TRUE);
					STATS::STAT_SET_INT(RAGE_JOAAT("MPPLY_CAS_CUR_GMBLNG_PX"), 0, TRUE);
					STATS::STAT_SET_INT(RAGE_JOAAT("MPPLY_CAS_GMBLNG_L24_PX"), 0, TRUE);
					STATS::STAT_SET_INT(RAGE_JOAAT("MPPLY_CAS_GMBLNG_L24"), 0, TRUE);
					STATS::STAT_SET_INT(RAGE_JOAAT("MPPLY_CAS_GMBLNG_TRHSLD"), 0, TRUE);
					STATS::STAT_SET_INT(RAGE_JOAAT("MPPLY_CAS_GMBLNG_L24_1"), 0, TRUE);
					STATS::STAT_SET_INT(RAGE_JOAAT("MPPLY_CAS_GMBLNG_L24_2"), 0, TRUE);
					STATS::STAT_SET_INT(RAGE_JOAAT("MPPLY_CAS_GMBLNG_L24_3"), 0, TRUE);
					STATS::STAT_SET_INT(RAGE_JOAAT("MPPLY_CAS_GMBLNG_L24_4"), 0, TRUE);
					STATS::STAT_SET_INT(RAGE_JOAAT("MPPLY_CAS_GMBLNG_L24_5"), 0, TRUE);
					STATS::STAT_SET_INT(RAGE_JOAAT("MPPLY_CAS_GMBLNG_L24_6"), 0, TRUE);
					STATS::STAT_SET_INT(RAGE_JOAAT("MPPLY_CAS_GMBLNG_L24_7"), 0, TRUE);
					STATS::STAT_SET_INT(RAGE_JOAAT("MPPLY_CAS_GMBLNG_L24_8"), 0, TRUE);
					STATS::STAT_SET_INT(RAGE_JOAAT("MPPLY_CAS_CUR_GMBLNG_HR"), 0, TRUE);
					STATS::STAT_SET_INT(RAGE_JOAAT("MPPLY_CAS_24H_GMBLNG_PX"), 0, TRUE);
					STATS::STAT_SET_INT(RAGE_JOAAT("MPPLY_CHIPS_COL_TIME"), 0, TRUE);
					});
			}

			ImGui::EndTabItem();

		}
	}
}