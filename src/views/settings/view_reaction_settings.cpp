#include "views/view.hpp"
#include "core/settings.hpp"

namespace big
{
	void draw_pair_option(const std::string_view name, decltype(g.notifications.player_join)& option)
	{
		ImGui::Text(name.data());

		ImGui::PushID(name.data());
		ImGui::Checkbox("Log", &option.log);
		ImGui::Checkbox("Notify", &option.notify);
		ImGui::PopID();
	}

	void draw_reaction(reaction& reaction)
	{
		ImGui::PushID(&reaction);
		if (ImGui::TreeNode(reaction.m_event_name))
		{
			ImGui::Checkbox("Notify", &reaction.notify);
			ImGui::Checkbox("Log", &reaction.log);
			ImGui::Checkbox("Kick Player", &reaction.kick);
			ImGui::Checkbox("Timeout", &reaction.timeout);
			ImGui::TreePop();
		}
		ImGui::PopID();
	}

	// TODO code duplication
	void draw_interloper_reaction(interloper_reaction& reaction)
	{
		ImGui::PushID(&reaction);
		if (ImGui::TreeNode(reaction.m_event_name))
		{
			ImGui::Checkbox("Notify", &reaction.notify);
			ImGui::Checkbox("Log", &reaction.log);
			ImGui::Checkbox("Kick Attacker", &reaction.kick);

			if (reaction.m_blockable || reaction.m_karmaable)
				ImGui::Separator();

			if (reaction.m_blockable)
				ImGui::Checkbox("Block", &reaction.block);

			if (reaction.m_karmaable)
				ImGui::Checkbox("Karma", &reaction.karma);

			ImGui::TreePop();
		}
		ImGui::PopID();
	}

	void view::reaction_settings()
	{
		components::title("Reactions");
		draw_reaction(g.reactions.ceo_kick);
		draw_reaction(g.reactions.ceo_money);
		draw_reaction(g.reactions.clear_wanted_level);
		draw_reaction(g.reactions.crash);
		draw_reaction(g.reactions.end_session_kick);
		draw_reaction(g.reactions.destroy_personal_vehicle);
		draw_reaction(g.reactions.fake_deposit);
		draw_reaction(g.reactions.force_mission);
		draw_reaction(g.reactions.force_teleport);
		draw_reaction(g.reactions.give_collectible);
		draw_reaction(g.reactions.gta_banner);
		draw_reaction(g.reactions.kick_from_interior);
		draw_reaction(g.reactions.mc_teleport);
		draw_reaction(g.reactions.network_bail);
		draw_reaction(g.reactions.null_function_kick);
		draw_reaction(g.reactions.personal_vehicle_destroyed);
		draw_reaction(g.reactions.remote_off_radar);
		draw_reaction(g.reactions.rotate_cam);
		draw_reaction(g.reactions.send_to_cutscene);
		draw_reaction(g.reactions.send_to_location);
		draw_reaction(g.reactions.send_to_interior);
		draw_reaction(g.reactions.sound_spam);
		draw_reaction(g.reactions.spectate_notification);
		draw_reaction(g.reactions.start_activity);
		draw_reaction(g.reactions.start_script);
		draw_reaction(g.reactions.teleport_to_warehouse);
		draw_reaction(g.reactions.transaction_error);
		draw_reaction(g.reactions.trigger_business_raid);
		draw_reaction(g.reactions.tse_freeze);
		draw_reaction(g.reactions.tse_sender_mismatch);
		draw_reaction(g.reactions.vehicle_kick);
		draw_reaction(g.reactions.turn_into_beast);
		draw_reaction(g.reactions.remote_wanted_level);
		draw_interloper_reaction(g.reactions.remote_wanted_level_others);
		ImGui::Separator();
		draw_reaction(g.reactions.clear_ped_tasks);
		draw_reaction(g.reactions.remote_ragdoll);
		draw_reaction(g.reactions.kick_vote);

		draw_reaction(g.reactions.modder_detection);
		draw_reaction(g.reactions.game_anti_cheat_modder_detection);
		
		draw_reaction(g.reactions.report);
		draw_reaction(g.reactions.report_cash_spawn);
		draw_reaction(g.reactions.request_control_event);
		draw_reaction(g.reactions.spectate);

		ImGui::Separator();
		draw_reaction(g.reactions.gamer_instruction_kick);

		components::title("Notifications");
		components::sub_title("GTA Threads");

		draw_pair_option("Terminate", g.notifications.gta_thread_kill);
		draw_pair_option("Start", g.notifications.gta_thread_start);

		components::sub_title("Network Player Manager");

		draw_pair_option("Player Join", g.notifications.player_leave);
		draw_pair_option("Player Leave", g.notifications.player_leave);

		components::sub_title("Other");

		draw_pair_option("Transaction Error / Rate Limit", g.notifications.transaction_rate_limit);
	}

}
