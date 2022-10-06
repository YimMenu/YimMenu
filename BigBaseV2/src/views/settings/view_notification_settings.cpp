#include "views/view.hpp"

namespace big
{
	void draw_pair_option(const std::string_view name, decltype(g->notifications.gta_thread_kill)& option)
	{
		ImGui::Text("%s", name.data());

		ImGui::PushID(name.data());
		ImGui::Checkbox("Log", &option.log);
		ImGui::Checkbox("Notify", &option.notify);
		ImGui::PopID();
	}

	void view::notification_settings()
	{
		components::sub_title("GTA Threads");

		draw_pair_option("Terminate", g->notifications.gta_thread_kill);
		draw_pair_option("Start", g->notifications.gta_thread_start);
			

		components::sub_title("Network Player Manager");

		ImGui::Text("Player Join");

		ImGui::Checkbox("Above Map", &g->notifications.player_join.above_map);
		ImGui::Checkbox("Log", &g->notifications.player_join.log);
		ImGui::Checkbox("Notify", &g->notifications.player_join.notify);

		ImGui::SameLine();

		draw_pair_option("Player Leave", g->notifications.player_leave);

		draw_pair_option("Init", g->notifications.network_player_mgr_init);
		draw_pair_option("Shutdown", g->notifications.network_player_mgr_shutdown);

		components::sub_title("Received Event");

		auto& received_event = g->notifications.received_event;

		ImGui::BeginGroup();
		draw_pair_option("Clear Ped Tasks", received_event.clear_ped_task);
		draw_pair_option("Kick Votes Notification", received_event.kick_vote);
		draw_pair_option("Detect Modder Events", received_event.modder_detect);
		ImGui::EndGroup();

		ImGui::SameLine();

		ImGui::BeginGroup();
		draw_pair_option("Report Cash Spawn", received_event.report_cash_spawn);
		draw_pair_option("Request Control Event", received_event.request_control_event);
		draw_pair_option("Vehicle Temp Action", received_event.vehicle_temp_action);
		ImGui::EndGroup();

		components::sub_title("Script Event Handler");

		auto& script_event_handler = g->notifications.script_event_handler;

		ImGui::BeginGroup();
		draw_pair_option("Bounty", script_event_handler.bounty);
		draw_pair_option("CEO Ban", script_event_handler.ceo_ban);
		draw_pair_option("CEO Kick", script_event_handler.ceo_kick);
		draw_pair_option("CEO Money", script_event_handler.ceo_money);
		draw_pair_option("Destroy Personal Vehicle", script_event_handler.personal_vehicle_destroyed);
		draw_pair_option("Fake Deposit", script_event_handler.fake_deposit);
		draw_pair_option("Force Mission", script_event_handler.force_mission);
		draw_pair_option("Force Teleport", script_event_handler.force_teleport);
		ImGui::EndGroup();

		ImGui::SameLine();

		ImGui::BeginGroup();
		draw_pair_option("GTA Banner", script_event_handler.gta_banner);
		draw_pair_option("MC Teleport", script_event_handler.mc_teleport);
		draw_pair_option("Network Bail", script_event_handler.network_bail);
		draw_pair_option("Remote Off Radar", script_event_handler.remote_off_radar);
		draw_pair_option("Rotate Cam", script_event_handler.rotate_cam);
		draw_pair_option("Send to Cutscene", script_event_handler.send_to_cutscene);
		draw_pair_option("Send to Location", script_event_handler.send_to_location);
		ImGui::EndGroup();

		ImGui::SameLine();

		ImGui::BeginGroup();
		draw_pair_option("Sound Spam", script_event_handler.sound_spam);
		draw_pair_option("Spectate", script_event_handler.spectate);
		draw_pair_option("Transaction Error", script_event_handler.transaction_error);
		draw_pair_option("TSE Crash", script_event_handler.crash);
		draw_pair_option("TSE Freeze", script_event_handler.tse_freeze);
		draw_pair_option("Vehicle Kick", script_event_handler.vehicle_kick);
		draw_pair_option("Wanted Level", script_event_handler.clear_wanted_level);
		ImGui::EndGroup();

		ImGui::SameLine();

		ImGui::BeginGroup();
		draw_pair_option("Teleport To Warehouse", script_event_handler.teleport_to_warehouse);
		draw_pair_option("Start Activity", script_event_handler.start_activity);
		ImGui::EndGroup();

		components::sub_title("Other");
		
		draw_pair_option("Reports", g->notifications.reports);
		draw_pair_option("Transaction Error / Rate Limit", g->notifications.transaction_rate_limit);
		draw_pair_option("Mismatch sync type", g->notifications.mismatch_sync_type);
		draw_pair_option("Out of allowed range sync type", g->notifications.out_of_allowed_range_sync_type);
		draw_pair_option("Invalid sync", g->notifications.invalid_sync);
	}

}
