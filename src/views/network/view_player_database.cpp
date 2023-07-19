#include "core/data/block_join_reasons.hpp"
#include "core/data/command_access_levels.hpp"
#include "core/data/infractions.hpp"
#include "fiber_pool.hpp"
#include "gta/enums.hpp"
#include "pointers.hpp"
#include "services/api/api_service.hpp"
#include "services/player_database/player_database_service.hpp"
#include "services/players/player_service.hpp"
#include "util/session.hpp"
#include "views/view.hpp"

namespace big
{
	char name_buf[32];
	char search[64];
	char note_buffer[1024];
	bool notes_dirty = false;
	std::shared_ptr<persistent_player> current_player;

	ImVec4 get_player_color(persistent_player& player)
	{
		if (player.session_type == GSType::Unknown)
			return ImVec4(.5f, .5f, .5f, 1.0f);
		else if (player.session_type == GSType::Invalid)
			return ImVec4(1.f, 0.f, 0.f, 1.f);
		else if (!player_database_service::is_joinable_session(player.session_type))
			return ImVec4(1.f, 1.f, 0.f, 1.f);
		else
			return ImVec4(0.f, 1.f, 0.f, 1.f);
	}

	void draw_player_db_entry(std::shared_ptr<persistent_player> player, const std::string& lower_search)
	{
		std::string name = player->name;
		std::transform(name.begin(), name.end(), name.begin(), ::tolower);

		if (lower_search.empty() || name.find(lower_search) != std::string::npos)
		{
			ImGui::PushID(player->rockstar_id);

			float circle_size = 7.5f;
			auto cursor_pos   = ImGui::GetCursorScreenPos();

			//render status circle
			ImGui::GetWindowDrawList()->AddCircleFilled(ImVec2(cursor_pos.x + 4.f + circle_size, cursor_pos.y + 4.f + circle_size), circle_size, ImColor(get_player_color(*player)));

			//we need some padding
			ImVec2 cursor = ImGui::GetCursorPos();
			ImGui::SetCursorPos(ImVec2(cursor.x + 25.f, cursor.y));

			if (components::selectable(player->name, player == g_player_database_service->get_selected()))
			{
				if (notes_dirty)
				{
					// Ensure notes are saved
					g_player_database_service->save();
					notes_dirty = false;
				}

				g_player_database_service->set_selected(player);
				current_player = player;
				strncpy(name_buf, current_player->name.data(), sizeof(name_buf));
				strncpy(note_buffer, current_player->notes.data(), sizeof(note_buffer));
			}

			if (ImGui::IsItemHovered())
				ImGui::SetTooltip(player_database_service::get_session_type_str(player->session_type));

			ImGui::PopID();
		}
	}

	void view::player_database()
	{
		ImGui::SetNextItemWidth(300.f);
		components::input_text_with_hint("PLAYER"_T, "SEARCH"_T, search, sizeof(search), ImGuiInputTextFlags_None);

		if (ImGui::BeginListBox("###players", {180, static_cast<float>(*g_pointers->m_gta.m_resolution_y - 400 - 38 * 4)}))
		{
			auto& item_arr = g_player_database_service->get_sorted_players();
			if (item_arr.size() > 0)
			{
				std::string lower_search = search;
				std::transform(lower_search.begin(), lower_search.end(), lower_search.begin(), tolower);

				for (auto& player : item_arr | std::ranges::views::values)
				{
					if (player_database_service::is_joinable_session(player->session_type))
						draw_player_db_entry(player, lower_search);
				}

				for (auto& player : item_arr | std::ranges::views::values)
				{
					if (!player_database_service::is_joinable_session(player->session_type) && player->session_type != GSType::Invalid
					    && player->session_type != GSType::Unknown)
						draw_player_db_entry(player, lower_search);
				}

				for (auto& player : item_arr | std::ranges::views::values)
				{
					if (player->session_type == GSType::Invalid || player->session_type == GSType::Unknown)
						draw_player_db_entry(player, lower_search);
				}
			}
			else
			{
				ImGui::Text("NO_STORED_PLAYERS"_T.data());
			}

			ImGui::EndListBox();
		}

		if (auto selected = g_player_database_service->get_selected())
		{
			ImGui::SameLine();
			if (ImGui::BeginChild("###selected_player", {500, static_cast<float>(*g_pointers->m_gta.m_resolution_y - 388 - 38 * 4)}, false, ImGuiWindowFlags_NoBackground))
			{
				if (ImGui::InputText("NAME"_T.data(), name_buf, sizeof(name_buf)))
				{
					current_player->name = name_buf;
				}

				if (ImGui::InputScalar("RID"_T.data(), ImGuiDataType_S64, &current_player->rockstar_id)
				    || ImGui::Checkbox("IS_MODDER"_T.data(), &current_player->is_modder)
				    || ImGui::Checkbox("BLOCK_JOIN"_T.data(), &current_player->block_join)
				    || ImGui::Checkbox("Track Player", &current_player->notify_online))
				{
					if (current_player->rockstar_id != selected->rockstar_id)
						g_player_database_service->update_rockstar_id(selected->rockstar_id, current_player->rockstar_id);
					g_player_database_service->save();
				}

				if (ImGui::BeginCombo("BLOCK_JOIN_ALERT"_T.data(), block_join_reasons[current_player->block_join_reason]))
				{
					for (const auto& reason : block_join_reasons)
					{
						if (ImGui::Selectable(reason.second, reason.first == current_player->block_join_reason))
						{
							current_player->block_join_reason = reason.first;
							g_player_database_service->save();
						}

						if (reason.first == current_player->block_join_reason)
						{
							ImGui::SetItemDefaultFocus();
						}
					}

					ImGui::EndCombo();
				}

				if (ImGui::IsItemHovered())
					ImGui::SetTooltip("ONLY_AS_HOST"_T.data());


				if (ImGui::BeginCombo("CHAT_COMMAND_PERMISSIONS"_T.data(),
				        COMMAND_ACCESS_LEVELS[current_player->command_access_level.value_or(g.session.chat_command_default_access_level)]))
				{
					for (const auto& [type, name] : COMMAND_ACCESS_LEVELS)
					{
						if (ImGui::Selectable(name, type == current_player->command_access_level.value_or(g.session.chat_command_default_access_level)))
						{
							current_player->command_access_level = type;
							g_player_database_service->save();
						}

						if (type == current_player->command_access_level.value_or(g.session.chat_command_default_access_level))
						{
							ImGui::SetItemDefaultFocus();
						}
					}

					ImGui::EndCombo();
				}

				if (!current_player->infractions.empty())
				{
					ImGui::Text("INFRACTIONS"_T.data());

					for (auto& infraction : current_player->infractions)
					{
						ImGui::BulletText(infraction_desc[(Infraction)infraction]);
					}
				}

				if (ImGui::InputTextMultiline("Notes", note_buffer, sizeof(note_buffer)))
				{
					current_player->notes = note_buffer;
					notes_dirty           = true;
				}

				ImGui::Checkbox("Join Redirect", &current_player->join_redirect);
				if (ImGui::IsItemHovered())
					ImGui::SetTooltip("Anyone trying to join you will join this player instead if they are active. The preference slider will control redirect priority if multiple players with join redirect are active");

				if (current_player->join_redirect)
				{
					ImGui::SliderInt("Preference", &current_player->join_redirect_preference, 1, 10);
				}

				components::button("JOIN_SESSION"_T, [] {
					session::join_by_rockstar_id(current_player->rockstar_id);
				});

				static char message[256];
				components::input_text("INPUT_MSG"_T, message, sizeof(message));
				if (components::button("SEND_MSG"_T))
				{
					g_thread_pool->push([selected] {
						if (g_api_service->send_socialclub_message(selected->rockstar_id, message))
						{
							g_notification_service->push_success("SCAPI"_T.data(), "MSG_SENT_SUCCESS"_T.data());
							return;
						}
						g_notification_service->push_error("SCAPI"_T.data(), "MSG_SENT_FAIL"_T.data());
					});
				};

				ImGui::Text("Session Type: %s", player_database_service::get_session_type_str(selected->session_type));

				if (selected->session_type != GSType::Invalid && selected->session_type != GSType::Unknown)
				{
					ImGui::Text("Is Host Of Session: %s", selected->is_host_of_session ? "Yes" : "No");
					ImGui::Text("Is Spectating: %s", selected->is_spectating ? "Yes" : "No");
					ImGui::Text("In Job Lobby: %s", selected->transition_session_id != -1 ? "Yes" : "No");
					ImGui::Text("Is Host Of Job Loby: %s", selected->is_host_of_transition_session ? "Yes" : "No");
					ImGui::Text("Current Mission Type: %s", player_database_service::get_game_mode_str(selected->game_mode));
					if (selected->game_mode != GameMode::None && player_database_service::can_fetch_name(selected->game_mode))
					{
						ImGui::Text("Current Mission Name: %s", selected->game_mode_name.c_str());
						if ((selected->game_mode_name == "Unknown" || selected->game_mode_name.empty())
						    && !selected->game_mode_id.empty())
						{
							ImGui::SameLine();
							components::button("Fetch", [] {
								current_player->game_mode_name =
								    player_database_service::get_name_by_content_id(current_player->game_mode_id);
							});
						}
					}
				}

				if (ImGui::Button("SAVE"_T.data()))
				{
					if (current_player->rockstar_id != selected->rockstar_id)
						g_player_database_service->update_rockstar_id(selected->rockstar_id, current_player->rockstar_id);

					selected = current_player;
					g_player_database_service->save();
				}

				ImGui::SameLine();

				if (ImGui::Button("REMOVE"_T.data()))
				{
					g_player_database_service->remove_rockstar_id(selected->rockstar_id);
				}
			}
			ImGui::EndChild();
		}

		if (ImGui::Button("REMOVE_ALL"_T.data()))
		{
			ImGui::OpenPopup("##removeall");
		}

		if (ImGui::BeginPopupModal("##removeall"))
		{
			ImGui::Text("Are you sure?");

			if (ImGui::Button("Yes"))
			{
				g_player_database_service->set_selected(nullptr);
				g_player_database_service->get_players().clear();
				g_player_database_service->get_sorted_players().clear();
				g_player_database_service->save();
				ImGui::CloseCurrentPopup();
			}
			ImGui::SameLine();
			if (ImGui::Button("No"))
			{
				ImGui::CloseCurrentPopup();
			}

			ImGui::EndPopup();
		}

		ImGui::SameLine();

		components::button("RELOAD_PLYR_ONLINE_STATES"_T, [] {
			g_player_database_service->update_player_states();
		});

		if (ImGui::TreeNode("Player Tracking"))
		{
			if (components::command_checkbox<"player_db_auto_update_states">("Enable"))
				g_player_database_service->start_update_loop();
			ImGui::Checkbox("Notify When Online", &g.player_db.notify_when_online);
			ImGui::Checkbox("Notify When Joinable", &g.player_db.notify_when_joinable);
			ImGui::Checkbox("Notify When Unjoinable", &g.player_db.notify_when_unjoinable);
			ImGui::Checkbox("Notify When Offline", &g.player_db.notify_when_offline);
			ImGui::Checkbox("Notify On Session Type Change", &g.player_db.notify_on_session_type_change);
			ImGui::Checkbox("Notify On Session Change", &g.player_db.notify_on_session_change);
			ImGui::Checkbox("Notify On Spectator Change", &g.player_db.notify_on_spectator_change);
			ImGui::Checkbox("Notify On Become Host", &g.player_db.notify_on_become_host);
			ImGui::Checkbox("Notify On Job Lobby Change", &g.player_db.notify_on_transition_change);
			ImGui::Checkbox("Notify On Mission Change", &g.player_db.notify_on_mission_change);
			ImGui::TreePop();
		}

		ImGui::Separator();
		components::sub_title("NEW_ENTRY"_T);

		static char new_name[64];
		static int64_t new_rockstar_id;

		components::input_text("NAME"_T, new_name, sizeof(new_name));
		ImGui::InputScalar("RID"_T.data(), ImGuiDataType_S64, &new_rockstar_id);

		if (ImGui::Button("ADD"_T.data()))
		{
			current_player = g_player_database_service->add_player(new_rockstar_id, new_name);
			g_player_database_service->save();
		}
		ImGui::SameLine();
		if (ImGui::Button("SEARCH"_T.data()))
		{
			g_thread_pool->push([] {
				if (!g_api_service->get_rid_from_username(new_name, *(uint64_t*)&new_rockstar_id))
				{
					g_notification_service->push_error("New Player DB Entry", std::format("No user '{}' called could be found.", new_name));
					new_rockstar_id = 0;
				}
			});
		}
		if (ImGui::IsItemHovered())
		{
			ImGui::SetTooltip("Do you know only the name of someone and not their Rockstar ID? Just fill in the username and click \"search\".");
		}
	}
}
