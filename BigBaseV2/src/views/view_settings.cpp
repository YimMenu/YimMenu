#include "views/view.hpp"
#include "widgets/imgui_hotkey.hpp"

namespace big
{
	void view::settings() {
		if (ImGui::TreeNode("Hotkeys"))
		{
			ImGui::PushItemWidth(350.f);

			if (ImGui::Hotkey("Menu Toggle", &g->settings.hotkeys.menu_toggle))
				g->settings.hotkeys.editing_menu_toggle = true; // make our menu reappear

			ImGui::Text("(Below hotkey is not implemented)");
			ImGui::Hotkey("Teleport to waypoint", &g->settings.hotkeys.teleport_waypoint);

			ImGui::PopItemWidth();

			ImGui::TreePop();
		}

		if (ImGui::TreeNode("Protections"))
		{
			ImGui::Checkbox("Bounty", &g->protections.script_events.bounty);
			ImGui::Checkbox("CEO Ban", &g->protections.script_events.ceo_ban);
			ImGui::Checkbox("CEO Kick", &g->protections.script_events.ceo_kick);
			ImGui::Checkbox("CEO Money", &g->protections.script_events.ceo_money);
			ImGui::Checkbox("Wanted Level", &g->protections.script_events.clear_wanted_level);
			ImGui::Checkbox("Fake Deposit", &g->protections.script_events.fake_deposit);
			ImGui::Checkbox("Force Mission", &g->protections.script_events.force_mission);
			ImGui::Checkbox("Force Teleport", &g->protections.script_events.force_teleport);
			ImGui::Checkbox("GTA Banner", &g->protections.script_events.gta_banner);
			ImGui::Checkbox("Network Bail", &g->protections.script_events.network_bail);
			ImGui::Checkbox("Destroy Personal Vehicle", &g->protections.script_events.personal_vehicle_destroyed);
			ImGui::Checkbox("Remote Off Radar", &g->protections.script_events.remote_off_radar);
			ImGui::Checkbox("Rotate Cam", &g->protections.script_events.rotate_cam);
			ImGui::Checkbox("Send to Cutscene", &g->protections.script_events.send_to_cutscene);
			ImGui::Checkbox("Send to Island", &g->protections.script_events.send_to_island);
			ImGui::Checkbox("Sound Spam", &g->protections.script_events.sound_spam);
			ImGui::Checkbox("Spectate", &g->protections.script_events.spectate);
			ImGui::Checkbox("Transaction Error", &g->protections.script_events.transaction_error);
			ImGui::Checkbox("Vehicle Kick", &g->protections.script_events.vehicle_kick);

			ImGui::TreePop();
		}
	}
}