#include "views/view.hpp"
#include "fiber_pool.hpp"
#include "pointers.hpp"
#include "services/players/player_service.hpp"
#include "services/player_database/player_database_service.hpp"
#include "services/api/api_service.hpp"
#include "core/data/block_join_reasons.hpp"
#include "core/data/infractions.hpp"
#include "core/data/command_access_levels.hpp"
#include "util/session.hpp"

namespace big
{
	persistent_player current_player;

	void view::player_database()
	{
		static char name_buf[32];
		static char search[64];

		ImGui::SetNextItemWidth(300.f);
		components::input_text_with_hint("Player", "Search", search, sizeof(search), ImGuiInputTextFlags_None);

		if (ImGui::ListBoxHeader("###players", { 180, static_cast<float>(*g_pointers->m_resolution_y - 400 - 38 * 4) }))
		{
		    auto& item_arr = g_player_database_service->get_players();
			if (item_arr.size() > 0)
			{
				std::string lower_search = search;
				std::transform(lower_search.begin(), lower_search.end(), lower_search.begin(), tolower);

				for (auto& item : item_arr)
				{
					auto& player = item.second;

					std::string name = player.name;
					std::transform(name.begin(), name.end(), name.begin(), ::tolower);

					if (lower_search.empty() || name.find(lower_search) != std::string::npos)
					{
						ImGui::PushID(item.first);

						if (components::selectable(player.name, &player == g_player_database_service->get_selected()))
						{
							g_player_database_service->set_selected(&player);
							current_player = player;
							strncpy(name_buf, current_player.name.data(), sizeof(name_buf));
						}

						ImGui::PopID();
					}
				}
			}
			else
			{
				ImGui::Text("No stored players");
			}

			ImGui::ListBoxFooter();
		}

		if (auto selected = g_player_database_service->get_selected())
		{
			ImGui::SameLine();
			if (ImGui::BeginChild("###selected_player", { 500, static_cast<float>(*g_pointers->m_resolution_y - 388 - 38 * 4) }, false, ImGuiWindowFlags_NoBackground))
			{
				if (ImGui::InputText("Name", name_buf, sizeof(name_buf)))
				{
					current_player.name = name_buf;
				}

				ImGui::InputScalar("Rockstar ID", ImGuiDataType_S64, &current_player.rockstar_id);
				ImGui::Checkbox("Is Modder", &current_player.is_modder);
				ImGui::Checkbox("Block Join", &current_player.block_join);

				if (ImGui::BeginCombo("Block Join Alert", block_join_reasons[current_player.block_join_reason]))
				{
					for (const auto& reason : block_join_reasons)
					{
						if (ImGui::Selectable(reason.second, reason.first == current_player.block_join_reason))
						{
							current_player.block_join_reason = reason.first;
						}

						if (reason.first == current_player.block_join_reason)
						{
							ImGui::SetItemDefaultFocus();
						}
					}

					ImGui::EndCombo();
				}

				if (ImGui::IsItemHovered())
					ImGui::SetTooltip("Only works as host");


				if (ImGui::BeginCombo("Chat Command Permissions", COMMAND_ACCESS_LEVELS[current_player.command_access_level.value_or(g.session.chat_command_default_access_level)]))
				{
					for (const auto& [type, name] : COMMAND_ACCESS_LEVELS)
					{
						if (ImGui::Selectable(name, type == current_player.command_access_level.value_or(g.session.chat_command_default_access_level)))
						{
							current_player.command_access_level = type;
						}

						if (type == current_player.command_access_level.value_or(g.session.chat_command_default_access_level))
						{
							ImGui::SetItemDefaultFocus();
						}
					}

					ImGui::EndCombo();
				}

				if (!current_player.infractions.empty())
				{
					ImGui::Text("Infractions:");

					for (auto& infraction : current_player.infractions)
					{
						ImGui::BulletText(infraction_desc[(Infraction)infraction]);
					}
				}

				components::button("Kick", []
				{
					session::kick_by_rockstar_id(current_player.rockstar_id);
				});

				components::button("Join Session", []
				{
					session::join_by_rockstar_id(current_player.rockstar_id);
				});

				static char message[256];
				components::input_text("Input Message", message, sizeof(message));
				if (components::button("Send Message"))
				{
					g_thread_pool->push([selected]
					{
						if (g_api_service->send_socialclub_message(selected->rockstar_id, message))
						{
							g_notification_service->push("SCAPI", "Message successfully sent");
							return;
						}
						g_notification_service->push_error("SCAPI", "Message not sent. Are you connected to the internet?");
					});
				};

				if (ImGui::Button("Save"))
				{
					if (current_player.rockstar_id != selected->rockstar_id)
						g_player_database_service->update_rockstar_id(selected->rockstar_id, current_player.rockstar_id);

					*selected = current_player;
					g_player_database_service->save();
				}

				ImGui::SameLine();

				if (ImGui::Button("Remove"))
				{
					g_player_database_service->remove_rockstar_id(selected->rockstar_id);
				}
			}
			ImGui::EndChild();
		}

		if (ImGui::Button("Remove All"))
		{
			g_player_database_service->set_selected(nullptr);
			g_player_database_service->get_players().clear();
			g_player_database_service->save();
		}

		ImGui::Separator();
		components::sub_title("New Entry");

		static char new_name[64];
		static int64_t new_rockstar_id;

		components::input_text("Name", new_name, sizeof(new_name));
		ImGui::InputScalar("Rockstar ID", ImGuiDataType_S64, &new_rockstar_id);

		if (ImGui::Button("Add"))
		{
			g_player_database_service->get_players()[new_rockstar_id] = persistent_player(new_name, new_rockstar_id);
			g_player_database_service->save();
		}
	}
}
