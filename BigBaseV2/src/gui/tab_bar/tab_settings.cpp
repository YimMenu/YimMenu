#include "tab_bar.hpp"

namespace big
{
	void tabbar::render_settings()
	{
		if (ImGui::BeginTabItem("Settings"))
		{
			if (ImGui::TreeNode("Protections"))
			{
				auto &protections = g_settings.options["settings"]["protections"];

				if (
					ImGui::Checkbox("Bounty", protections["bounty"].get<bool*>()) ||
					ImGui::Checkbox("Ceo Ban", protections["ceo_ban"].get<bool*>()) ||
					ImGui::Checkbox("Ceo Kick", protections["ceo_kick"].get<bool*>()) ||
					ImGui::Checkbox("Ceo Money", protections["ceo_money"].get<bool*>()) ||
					ImGui::Checkbox("Clear Wanted Level", protections["clear_wanted_level"].get<bool*>()) ||
					ImGui::Checkbox("Fake Deposit", protections["fake_deposit"].get<bool*>()) ||
					ImGui::Checkbox("Force Mission", protections["force_mission"].get<bool*>()) ||
					ImGui::Checkbox("GTA Banner", protections["gta_banner"].get<bool*>()) ||
					ImGui::Checkbox("Kick", protections["kick"].get<bool*>()) ||
					ImGui::Checkbox("Personal Vehicle Destroyed", protections["personal_vehicle_destroyed"].get<bool*>()) ||
					ImGui::Checkbox("Remote Off Radar", protections["remote_off_radar"].get<bool*>()) ||
					ImGui::Checkbox("Rotate Cam", protections["rotate_cam"].get<bool*>()) ||
					ImGui::Checkbox("Send To Cutscene", protections["send_to_cutscene"].get<bool*>()) ||
					ImGui::Checkbox("Send To Island", protections["send_to_island"].get<bool*>()) ||
					ImGui::Checkbox("Sound Spam", protections["sound_spam"].get<bool*>()) ||
					ImGui::Checkbox("Spectate", protections["spectate"].get<bool*>()) ||
					ImGui::Checkbox("Force Teleport", protections["force_teleport"].get<bool*>()) ||
					ImGui::Checkbox("Transaction Error", protections["transaction_error"].get<bool*>()) ||
					ImGui::Checkbox("Vehicle Kick", protections["vehicle_kick"].get<bool*>())
				) { g_settings.save(); }

				if (ImGui::Button("Enable All"))
					features::functions::toggle_protections(true);
				ImGui::SameLine();
				if (ImGui::Button("Disable All"))
					features::functions::toggle_protections(false);

				ImGui::TreePop();
			}

			ImGui::EndTabItem();
		}
	}
}