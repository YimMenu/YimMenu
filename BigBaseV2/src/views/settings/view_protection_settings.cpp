#include "views/view.hpp"

namespace big
{
	void view::protection_settings()
	{
		ImGui::BeginGroup();
		ImGui::Checkbox("Bounty", &g->protections.script_events.bounty);
		ImGui::Checkbox("CEO Ban", &g->protections.script_events.ceo_ban);
		ImGui::Checkbox("CEO Kick", &g->protections.script_events.ceo_kick);
		ImGui::Checkbox("CEO Money", &g->protections.script_events.ceo_money);
		ImGui::Checkbox("TSE Crash", &g->protections.script_events.crash);
		ImGui::Checkbox("Fake Deposit", &g->protections.script_events.fake_deposit);
		ImGui::Checkbox("Force Mission", &g->protections.script_events.force_mission);
		ImGui::EndGroup();

		ImGui::SameLine();

		ImGui::BeginGroup();
		ImGui::Checkbox("Force Teleport", &g->protections.script_events.force_teleport);
		ImGui::Checkbox("GTA Banner", &g->protections.script_events.gta_banner);
		ImGui::Checkbox("MC Teleport", &g->protections.script_events.mc_teleport);
		ImGui::Checkbox("Network Bail", &g->protections.script_events.network_bail);
		ImGui::Checkbox("Personal Vehicle Destroyed", &g->protections.script_events.personal_vehicle_destroyed);
		ImGui::Checkbox("Remote Off Radar", &g->protections.script_events.remote_off_radar);
		ImGui::Checkbox("Rotate Cam", &g->protections.script_events.rotate_cam);
		ImGui::EndGroup();

		ImGui::SameLine();

		ImGui::BeginGroup();
		ImGui::Checkbox("Send to Cutscene", &g->protections.script_events.send_to_cutscene);
		ImGui::Checkbox("Send to Location", &g->protections.script_events.send_to_location);
		ImGui::Checkbox("Sound Spam", &g->protections.script_events.sound_spam);
		ImGui::Checkbox("Spectate", &g->protections.script_events.spectate);
		ImGui::Checkbox("Transaction Error", &g->protections.script_events.transaction_error);
		ImGui::Checkbox("Vehicle Kick", &g->protections.script_events.vehicle_kick);
		ImGui::Checkbox("Wanted Level", &g->protections.script_events.clear_wanted_level);
		ImGui::EndGroup();

		ImGui::SameLine();

		ImGui::BeginGroup();
		ImGui::Checkbox("Teleport To Warehouse", &g->protections.script_events.teleport_to_warehouse);
		ImGui::Checkbox("Start Activity", &g->protections.script_events.start_activity);
		ImGui::EndGroup();
	}

}
