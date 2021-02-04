#include "gui/tab_bar.hpp"
#include "pointers.hpp"

namespace big
{
	void tabbar::render_settings()
	{
		if (ImGui::BeginTabItem("Settings"))
		{
			if (ImGui::TreeNode("Dev Logging"))
			{
				auto& logging = g_settings.options["settings"]["logging"];

				if (ImGui::Checkbox("Get Event Data", logging["get_event_data"].get<bool*>()))
					g_settings.save();

				if (ImGui::Checkbox("Script Events", logging["script_events"].get<bool*>()))
					g_settings.save();

				ImGui::Separator();

				static const uint8_t max_count = 64;
				static char str_args[max_count][38];
				static int arg_count = 0;
				static Player target = 0;
				static char* selected;

				ImGui::Text("Trigger Script Event:");

				ImGui::Text("Target:");

				if (ImGui::BeginCombo("##player_target", selected))
				{
					for (int i = 0; i < 32; i++)
					{
						bool is_selected = (g_players[i].id == target);
						if (g_players[i].is_online && ImGui::Selectable(g_players[i].name, is_selected))
						{
							selected = g_players[i].name;
							target = g_players[i].id;
						}
						if (is_selected)
							ImGui::SetItemDefaultFocus();
					}
					ImGui::EndCombo();
				}

				ImGui::SliderInt(": Argument Count", &arg_count, 0, max_count);

				for (int i = 0; i < arg_count; i++)
				{
					char label[16];

					sprintf(label, ": arg #%d", i);

					ImGui::InputText(label, str_args[i], sizeof(str_args[i]));
				}

				if (ImGui::Button("Send Event"))
				{
					QUEUE_JOB_BEGIN_CLAUSE(= )
					{

						int64_t* event_args = new int64_t[arg_count];

						for (int i = 0; i < arg_count; i++)
						{
							event_args[i] = strtoll(str_args[i], NULL, 10);

							script::get_current()->yield();
						}

						g_pointers->m_trigger_script_event(true, event_args, arg_count, 1 << target);
					}QUEUE_JOB_END_CLAUSE
				}

				ImGui::TreePop();
			}

			ImGui::Separator();

			if (ImGui::TreeNode("Protections"))
			{
				auto& protections = g_settings.options["settings"]["protections"];

				if (
					ImGui::Checkbox("Attach Protection", protections["attach"].get<bool*>()) ||
					ImGui::Checkbox("Cage Protection", protections["cage"].get<bool*>())// ||
					//ImGui::Checkbox("Version Mismatch Protection", protections["version_mismatch"].get<bool*>())
					)
					g_settings.save();

				ImGui::TreePop();
			}

			ImGui::Separator();

			if (ImGui::TreeNode("Script Protection"))
			{
				auto& protections = g_settings.options["settings"]["script_protections"];

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
					) {
					g_settings.save();
				}

				if (ImGui::Button("Enable All"))
					func::toggle_protections(true);
				ImGui::SameLine();
				if (ImGui::Button("Disable All"))
					func::toggle_protections(false);

				ImGui::TreePop();
			}

			ImGui::EndTabItem();
		}
	}
}