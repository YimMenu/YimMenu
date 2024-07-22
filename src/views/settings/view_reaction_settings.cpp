#include "core/data/block_join_reasons.hpp"
#include "views/view.hpp"

namespace big
{
	void draw_pair_option(const std::string_view name, decltype(g.notifications.gta_thread_kill)& option)
	{
		ImGui::Text(name.data());

		ImGui::PushID(name.data());
		ImGui::Checkbox("LOG"_T.data(), &option.log);
		ImGui::Checkbox("NOTIFY"_T.data(), &option.notify);
		ImGui::PopID();
	}

	void draw_reaction(reaction& reaction)
	{
		ImGui::PushID(&reaction);
		if (ImGui::TreeNode(g_translation_service.get_translation(reaction.m_event_name).data()))
		{
			ImGui::Checkbox("REACTION_CHAT"_T.data(), &reaction.announce_in_chat);
			ImGui::SameLine();
			ImGui::Checkbox("IS_TEAM"_T.data(), &reaction.is_team_only);
			ImGui::Checkbox("NOTIFY"_T.data(), &reaction.notify);
			ImGui::Checkbox("LOG"_T.data(), &reaction.log);
			ImGui::Checkbox("REACTION_ADD_TO_DATABASE"_T.data(), &reaction.add_to_player_db);
			ImGui::Checkbox("REACTION_BLOCK_JOINS"_T.data(), &reaction.block_joins);
			if (reaction.block_joins)
				if (ImGui::BeginCombo("BLOCK_JOIN_ALERT"_T.data(), block_join_reasons[reaction.block_join_reason]))
				{
					block_join_reason_t i = block_join_reason_t::UNK_0;
					for (const auto& reason_str : block_join_reasons)
					{
						if (reason_str != "")
						{
							const bool is_selected = reaction.block_join_reason == i;

							if (ImGui::Selectable(reason_str, is_selected))
							{
								reaction.block_join_reason = i;
							}

							if (is_selected)
							{
								ImGui::SetItemDefaultFocus();
							}
						}

						i++;
					}
					ImGui::EndCombo();
				}
			ImGui::Checkbox("REACTION_KICK_PLAYER"_T.data(), &reaction.kick);
			ImGui::Checkbox("TIMEOUT"_T.data(), &reaction.timeout);
			ImGui::TreePop();
		}
		ImGui::PopID();
	}

	// TODO code duplication
	void draw_interloper_reaction(interloper_reaction& reaction)
	{
		ImGui::PushID(&reaction);
		if (ImGui::TreeNode(g_translation_service.get_translation(reaction.m_event_name).data()))
		{
			ImGui::Checkbox("REACTION_CHAT"_T.data(), &reaction.announce_in_chat);
			ImGui::SameLine();
			ImGui::Checkbox("IS_TEAM"_T.data(), &reaction.is_team_only);
			ImGui::Checkbox("NOTIFY"_T.data(), &reaction.notify);
			ImGui::Checkbox("LOG"_T.data(), &reaction.log);
			ImGui::Checkbox("REACTION_ADD_TO_DATABASE"_T.data(), &reaction.add_to_player_db);
			ImGui::Checkbox("REACTION_BLOCK_JOINS"_T.data(), &reaction.block_joins);
			if (reaction.block_joins)
				if (ImGui::BeginCombo("BLOCK_JOIN_ALERT"_T.data(), block_join_reasons[reaction.block_join_reason]))
				{
					block_join_reason_t i = block_join_reason_t::UNK_0;
					for (const auto& reason_str : block_join_reasons)
					{
						if (reason_str != "")
						{
							const bool is_selected = reaction.block_join_reason == i;

							if (ImGui::Selectable(reason_str, is_selected))
							{
								reaction.block_join_reason = i;
							}

							if (is_selected)
							{
								ImGui::SetItemDefaultFocus();
							}
						}

						i++;
					}
					ImGui::EndCombo();
				}
			ImGui::Checkbox("REACTION_KICK_ATTACKER"_T.data(), &reaction.kick);
			ImGui::Checkbox("TIMEOUT"_T.data(), &reaction.timeout);

			if (reaction.m_blockable || reaction.m_karmaable)
				ImGui::Separator();

			if (reaction.m_blockable)
				ImGui::Checkbox("BLOCK"_T.data(), &reaction.block);

			if (reaction.m_karmaable)
				ImGui::Checkbox("KARMA"_T.data(), &reaction.karma);

			ImGui::TreePop();
		}
		ImGui::PopID();
	}

	void view::reaction_settings()
	{
		components::title("SETTINGS_REACTIONS"_T);
		draw_reaction(g.reactions.bounty);
		draw_reaction(g.reactions.break_game);
		draw_reaction(g.reactions.ceo_kick);
		draw_reaction(g.reactions.ceo_money);
		draw_reaction(g.reactions.chat_spam);
		draw_reaction(g.reactions.clear_ped_tasks);
		draw_reaction(g.reactions.clear_wanted_level);
		draw_reaction(g.reactions.crash);
		draw_reaction(g.reactions.delete_vehicle);
		draw_reaction(g.reactions.destroy_personal_vehicle);
		draw_reaction(g.reactions.fake_deposit);
		draw_reaction(g.reactions.force_mission);
		draw_reaction(g.reactions.force_teleport);
		draw_reaction(g.reactions.game_anti_cheat_modder_detection);
		draw_reaction(g.reactions.give_collectible);
		draw_reaction(g.reactions.gta_banner);
		draw_reaction(g.reactions.kick);
		draw_reaction(g.reactions.kick_from_interior);
		draw_reaction(g.reactions.kick_vote);
		draw_reaction(g.reactions.mc_teleport);
		draw_reaction(g.reactions.modder_detection);
		draw_reaction(g.reactions.personal_vehicle_destroyed);
		draw_reaction(g.reactions.remote_off_radar);
		draw_reaction(g.reactions.remote_ragdoll);
		draw_reaction(g.reactions.remote_wanted_level);
		draw_interloper_reaction(g.reactions.remote_wanted_level_others);
		draw_reaction(g.reactions.report);
		draw_reaction(g.reactions.report_cash_spawn);
		draw_reaction(g.reactions.request_control_event);
		draw_reaction(g.reactions.rotate_cam);
		draw_reaction(g.reactions.send_to_cutscene);
		draw_reaction(g.reactions.send_to_interior);
		draw_reaction(g.reactions.send_to_location);
		draw_reaction(g.reactions.sound_spam);
		draw_reaction(g.reactions.spectate);
		draw_reaction(g.reactions.spectate_notification);
		draw_interloper_reaction(g.reactions.spectate_others);
		draw_reaction(g.reactions.start_activity);
		draw_reaction(g.reactions.start_script);
		draw_reaction(g.reactions.teleport_to_warehouse);
		draw_reaction(g.reactions.transaction_error);
		draw_reaction(g.reactions.trigger_business_raid);
		draw_reaction(g.reactions.tse_freeze);
		draw_reaction(g.reactions.tse_sender_mismatch);
		draw_reaction(g.reactions.turn_into_beast);
		draw_reaction(g.reactions.vehicle_kick);

		components::title("SETTINGS_NOTIFICATIONS"_T);
		components::sub_title("SETTINGS_NOTIFY_GTA_THREADS"_T);

		draw_pair_option("SETTINGS_NOTIFY_GTA_THREADS_TERMINATE"_T, g.notifications.gta_thread_kill);
		draw_pair_option("SETTINGS_NOTIFY_GTA_THREADS_START"_T, g.notifications.gta_thread_start);

		components::sub_title("SETTINGS_NOTIFY_PLAYER_MGR"_T);

		ImGui::Text("SETTINGS_NOTIFY_PLAYER_JOIN"_T.data());

		ImGui::Checkbox("SETTINGS_NOTIFY_PLAYER_JOIN_ABOVE_MAP"_T.data(), &g.notifications.player_join.above_map);
		ImGui::Checkbox("LOG"_T.data(), &g.notifications.player_join.log);
		ImGui::Checkbox("NOTIFY"_T.data(), &g.notifications.player_join.notify);

		draw_pair_option("SETTINGS_NOTIFY_PLAYER_LEAVE"_T, g.notifications.player_leave);

		draw_pair_option("SETTINGS_NOTIFY_PLAYER_MGR_INIT"_T, g.notifications.network_player_mgr_init);
		draw_pair_option("SETTINGS_NOTIFY_PLAYER_MGR_SHUTDOWN"_T, g.notifications.network_player_mgr_shutdown);

		components::sub_title("SETTINGS_NOTIFY_OTHER"_T);

		draw_pair_option("SETTINGS_NOTIFY_TRANSACTION_RATE_LIMIT"_T, g.notifications.transaction_rate_limit);
	}

}
