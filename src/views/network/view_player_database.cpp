#include "views/view.hpp"
#include "fiber_pool.hpp"
#include "pointers.hpp"
#include "services/players/player_service.hpp"
#include "services/player_database/player_database_service.hpp"
#include "core/data/block_join_reasons.hpp"
#include "core/data/infractions.hpp"
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

		if (ImGui::ListBoxHeader("###players", { 200, static_cast<float>(*g_pointers->m_resolution_y - 388 - 38 * 4) }))
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
			if (ImGui::BeginChild("###selected_player", { 500, static_cast<float>(*g_pointers->m_resolution_y - 388 - 38 * 4) }))
			{
				ImGui::PushStyleVar(ImGuiStyleVar_Alpha, 1.0f);
				if (ImGui::InputText("Name", name_buf, sizeof(name_buf)))
				{
					current_player.name = name_buf;
				}

				ImGui::InputScalar("Rockstar ID", ImGuiDataType_S64, &current_player.rockstar_id);
				ImGui::Checkbox("Block Join", &current_player.block_join);

				if (ImGui::BeginCombo("Block Join Alert Message", block_join_reasons[current_player.block_join_reason]))
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

				ImGui::Checkbox("Is Modder", &current_player.is_modder);

				if (!current_player.infractions.empty())
				{
					ImGui::Text("Infractions:");

					for (auto& infraction : current_player.infractions)
					{
						ImGui::BulletText(infractions[infraction]);
					}
				}

				components::button("Join Session", []
				{
					session::join_by_rockstar_id(current_player.rockstar_id);
				});

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
				ImGui::PopStyleVar();
			}
			ImGui::EndChild();
		}
	}
}
