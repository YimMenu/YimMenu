#include "core/settings/notifications.hpp"
#include "core/settings/reactions.hpp"
#include "views/view.hpp"

namespace big
{
	void draw_pair_option(const std::string_view name, decltype(g_notifications.player_join)& option)
	{
		ImGui::Text(name.data());

		ImGui::PushID(name.data());
		ImGui::Checkbox("Notify", &option.notify);
		ImGui::Checkbox("Log", &option.log);
		
		ImGui::PopID();
	}

	void draw_reaction(reaction& reaction)
	{
		ImGui::PushID(&reaction);
		if (ImGui::TreeNode(reaction.m_event_name))
		{
			ImGui::Checkbox("Notify", &reaction.notify);
			ImGui::Checkbox("Log", &reaction.log);
			ImGui::TreePop();
		}
		ImGui::PopID();
	}

	void view::reaction_settings()
	{
		components::title("Reactions");
		draw_reaction(g_reactions.ceo_kick);
		draw_reaction(g_reactions.ceo_money);
		draw_reaction(g_reactions.clear_wanted_level);
		draw_reaction(g_reactions.crash);
		draw_reaction(g_reactions.end_session_kick);
		draw_reaction(g_reactions.destroy_personal_vehicle);
		draw_reaction(g_reactions.fake_deposit);
		draw_reaction(g_reactions.force_mission);
		draw_reaction(g_reactions.force_teleport);
		draw_reaction(g_reactions.give_collectible);
		draw_reaction(g_reactions.gta_banner);
		draw_reaction(g_reactions.kick_from_interior);
		draw_reaction(g_reactions.mc_teleport);
		draw_reaction(g_reactions.network_bail);
		draw_reaction(g_reactions.null_function_kick);
		draw_reaction(g_reactions.personal_vehicle_destroyed);
		draw_reaction(g_reactions.remote_off_radar);
		draw_reaction(g_reactions.rotate_cam);
		draw_reaction(g_reactions.send_to_cutscene);
		draw_reaction(g_reactions.send_to_location);
		draw_reaction(g_reactions.send_to_interior);
		draw_reaction(g_reactions.sound_spam);
		draw_reaction(g_reactions.spectate_notification);
		draw_reaction(g_reactions.start_activity);
		draw_reaction(g_reactions.start_script);
		draw_reaction(g_reactions.teleport_to_warehouse);
		draw_reaction(g_reactions.transaction_error);
		draw_reaction(g_reactions.trigger_business_raid);
		draw_reaction(g_reactions.tse_freeze);
		draw_reaction(g_reactions.tse_sender_mismatch);
		draw_reaction(g_reactions.vehicle_kick);
		draw_reaction(g_reactions.turn_into_beast);
		draw_reaction(g_reactions.remote_wanted_level);
		ImGui::Separator();
		draw_reaction(g_reactions.clear_ped_tasks);
		draw_reaction(g_reactions.remote_ragdoll);
		draw_reaction(g_reactions.kick_vote);

		draw_reaction(g_reactions.modder_detection);
		draw_reaction(g_reactions.game_anti_cheat_modder_detection);

		draw_reaction(g_reactions.report);
		draw_reaction(g_reactions.report_cash_spawn);
		draw_reaction(g_reactions.request_control_event);
		draw_reaction(g_reactions.spectate);

		ImGui::Separator();
		draw_reaction(g_reactions.gamer_instruction_kick);

		components::title("Notifications");
		components::sub_title("GTA Threads");

		draw_pair_option("Terminate", g_notifications.gta_thread_kill);
		draw_pair_option("Start", g_notifications.gta_thread_start);

		components::sub_title("Network Player Manager");

		draw_pair_option("Player Join", g_notifications.player_leave);
		draw_pair_option("Player Leave", g_notifications.player_leave);

		components::sub_title("Other");

		draw_pair_option("Transaction Error / Rate Limit", g_notifications.transaction_rate_limit);
	}

}
