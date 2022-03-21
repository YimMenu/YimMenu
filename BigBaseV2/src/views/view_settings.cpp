#include "views/view.hpp"
#include "widgets/imgui_hotkey.hpp"

namespace big
{
	void draw_pair_option(const std::string_view name, decltype(g->notifications.gta_thread_kill)& option)
	{
		ImGui::Text(name.data());

		ImGui::PushID(name.data());
		ImGui::Checkbox("Log", &option.log);
		ImGui::Checkbox("Notify", &option.notify);
		ImGui::PopID();
	}

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
			ImGui::BeginGroup();
			ImGui::Checkbox("Bounty", &g->protections.script_events.bounty);
			ImGui::Checkbox("CEO Ban", &g->protections.script_events.ceo_ban);
			ImGui::Checkbox("CEO Kick", &g->protections.script_events.ceo_kick);
			ImGui::Checkbox("CEO Money", &g->protections.script_events.ceo_money);
			ImGui::Checkbox("Wanted Level", &g->protections.script_events.clear_wanted_level);
			ImGui::Checkbox("Fake Deposit", &g->protections.script_events.fake_deposit);
			ImGui::Checkbox("Force Mission", &g->protections.script_events.force_mission);
			ImGui::EndGroup();

			ImGui::SameLine();

			ImGui::BeginGroup();
			ImGui::Checkbox("Force Teleport", &g->protections.script_events.force_teleport);
			ImGui::Checkbox("GTA Banner", &g->protections.script_events.gta_banner);
			ImGui::Checkbox("Network Bail", &g->protections.script_events.network_bail);
			ImGui::Checkbox("Personal Vehicle Destroyed", &g->protections.script_events.personal_vehicle_destroyed);
			ImGui::Checkbox("Remote Off Radar", &g->protections.script_events.remote_off_radar);
			ImGui::Checkbox("Rotate Cam", &g->protections.script_events.rotate_cam);
			ImGui::EndGroup();

			ImGui::SameLine();

			ImGui::BeginGroup();
			ImGui::Checkbox("Send to Cutscene", &g->protections.script_events.send_to_cutscene);
			ImGui::Checkbox("Send to Island", &g->protections.script_events.send_to_island);
			ImGui::Checkbox("Sound Spam", &g->protections.script_events.sound_spam);
			ImGui::Checkbox("Spectate", &g->protections.script_events.spectate);
			ImGui::Checkbox("Transaction Error", &g->protections.script_events.transaction_error);
			ImGui::Checkbox("Vehicle Kick", &g->protections.script_events.vehicle_kick);
			ImGui::EndGroup();
			ImGui::TreePop();
		}

		if (ImGui::TreeNode("Notifications"))
		{
			if (ImGui::TreeNode("GTA Threads"))
			{
				draw_pair_option("Terminate", g->notifications.gta_thread_kill);
				draw_pair_option("Start", g->notifications.gta_thread_start);

				ImGui::TreePop();
			}

			if (ImGui::TreeNode("Network Player Manager"))
			{
				ImGui::Text("Player Join");

				ImGui::Checkbox("Above Map", &g->notifications.player_join.above_map);
				ImGui::Checkbox("Log", &g->notifications.player_join.log);
				ImGui::Checkbox("Notify", &g->notifications.player_join.notify);

				draw_pair_option("Player Leave", g->notifications.player_leave);
				draw_pair_option("Shutdown", g->notifications.network_player_mgr_shutdown);

				ImGui::TreePop();
			}

			if (ImGui::TreeNode("Received Event"))
			{
				auto& received_event = g->notifications.received_event;

				ImGui::BeginGroup();
				draw_pair_option("Clear Ped Tasks", received_event.clear_ped_task);
				draw_pair_option("Modder Detection", received_event.modder_detect);
				ImGui::EndGroup();

				ImGui::SameLine();

				ImGui::BeginGroup();
				draw_pair_option("Report Cash Spawn", received_event.report_cash_spawn);
				draw_pair_option("Request Control Event", received_event.request_control_event);
				ImGui::EndGroup();

				ImGui::TreePop();
			}

			if (ImGui::TreeNode("Script Event Handler"))
			{
				auto& script_event_handler = g->notifications.script_event_handler;

				ImGui::BeginGroup();
				draw_pair_option("Bounty", script_event_handler.bounty);
				draw_pair_option("CEO Ban", script_event_handler.ceo_ban);
				draw_pair_option("CEO Kick", script_event_handler.ceo_kick);
				draw_pair_option("CEO Money", script_event_handler.ceo_money);
				draw_pair_option("Wanted Level", script_event_handler.clear_wanted_level);
				draw_pair_option("Fake Deposit", script_event_handler.fake_deposit);
				draw_pair_option("Force Mission", script_event_handler.force_mission);
				ImGui::EndGroup();

				ImGui::SameLine();

				ImGui::BeginGroup();
				draw_pair_option("Force Teleport", script_event_handler.force_teleport);
				draw_pair_option("GTA Banner", script_event_handler.gta_banner);
				draw_pair_option("Network Bail", script_event_handler.network_bail);
				draw_pair_option("Destroy Personal Vehicle", script_event_handler.personal_vehicle_destroyed);
				draw_pair_option("Remote Off Radar", script_event_handler.remote_off_radar);
				draw_pair_option("Rotate Cam", script_event_handler.rotate_cam);
				ImGui::EndGroup();

				ImGui::SameLine();

				ImGui::BeginGroup();
				draw_pair_option("Send to Cutscene", script_event_handler.send_to_cutscene);
				draw_pair_option("Send to Island", script_event_handler.send_to_island);
				draw_pair_option("Sound Spam", script_event_handler.sound_spam);
				draw_pair_option("Spectate", script_event_handler.spectate);
				draw_pair_option("Transaction Error", script_event_handler.transaction_error);
				draw_pair_option("Vehicle Kick", script_event_handler.vehicle_kick);
				ImGui::EndGroup();

				ImGui::TreePop();
			}

			if (ImGui::TreeNode("Other"))
			{
				draw_pair_option("Net Array Error", g->notifications.net_array_error);
				draw_pair_option("Reports", g->notifications.reports);
				draw_pair_option("Transaction Error / Rate Limit", g->notifications.transaction_rate_limit);

				ImGui::TreePop();
			}

			ImGui::TreePop();
		}
	}
}