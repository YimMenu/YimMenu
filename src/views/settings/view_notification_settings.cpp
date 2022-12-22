#include "views/view.hpp"

namespace big
{
	void draw_pair_option(const std::string_view name, decltype(g.notifications.gta_thread_kill)& option)
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

		draw_pair_option("Terminate", g.notifications.gta_thread_kill);
		draw_pair_option("Start", g.notifications.gta_thread_start);
		
		components::sub_title("Network Player Manager");

		ImGui::Text("Player Join");

		ImGui::Checkbox("Above Map", &g.notifications.player_join.above_map);
		ImGui::Checkbox("Log", &g.notifications.player_join.log);
		ImGui::Checkbox("Notify", &g.notifications.player_join.notify);

		draw_pair_option("Player Leave", g.notifications.player_leave);

		draw_pair_option("Init", g.notifications.network_player_mgr_init);
		draw_pair_option("Shutdown", g.notifications.network_player_mgr_shutdown);

		components::sub_title("Received Event");

		auto& received_event = g.notifications.received_event;

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

		auto& script_event_handler = g.notifications.script_event_handler;

		draw_pair_option("All", script_event_handler);

		components::sub_title("Other");
		
		draw_pair_option("Reports", g.notifications.reports);
		draw_pair_option("Transaction Error / Rate Limit", g.notifications.transaction_rate_limit);
		draw_pair_option("Mismatch sync type", g.notifications.mismatch_sync_type);
		draw_pair_option("Out of allowed range sync type", g.notifications.out_of_allowed_range_sync_type);
		draw_pair_option("Invalid sync", g.notifications.invalid_sync);
	}

}
