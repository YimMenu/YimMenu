#include "fiber_pool.hpp"
#include "util/session.hpp"
#include "views/view.hpp"
#include "logger.hpp"
#include "services/player_database/player_database_service.hpp"

namespace big
{
	void view::player_db()
	{
		static char search[64];

		components::input_text_with_hint("Player Name", "Search", search, sizeof(search), ImGuiInputTextFlags_None);

		if (ImGui::ListBoxHeader("###player_list"))
		{
			if (g_player_database_service->player_list_().empty())
			{
				ImGui::Text("Player DataBase is empty");
			}
			else
			{
				std::string lower_search = search;
				std::transform(lower_search.begin(), lower_search.end(), lower_search.begin(), tolower);

				for (const auto& player : g_player_database_service->player_list_())
				{
					const auto& name = player.player_name;
					const auto& relationship = player.relationship;
					const auto& rid = player.rid;

					std::string name_d = name;
					std::string rid_d = std::to_string(rid);
					std::transform(name_d.begin(), name_d.end(), name_d.begin(), ::tolower);

					if (name.find(lower_search) != std::string::npos ||
						rid_d.find(lower_search) != std::string::npos)
					{
						components::selectable(name, false, [rid] {

							strcpy(search, "");
							session::join_by_rockstar_id(rid);
						});
						if (ImGui::BeginPopupContextItem()) // <-- use last item id as popup id
						{
							ImGui::Text("Name: %s", name.c_str());
							ImGui::Text("RID: %d", rid);
							ImGui::Text("Relationship: %s", relationship.c_str());
							components::button("Open SC Profile", [rid_d]
							{
								int gamerHandle;
								NETWORK::NETWORK_HANDLE_FROM_MEMBER_ID(rid_d.c_str(), &gamerHandle, 13);
								NETWORK::NETWORK_SHOW_PROFILE_UI(&gamerHandle);
							});
							ImGui::EndPopup();
						}
						if (ImGui::IsItemHovered())
							ImGui::SetTooltip("Right-click to open popup");
					}
				}
			}
			ImGui::ListBoxFooter();
		}
		if (ImGui::TreeNode("Manual Add"))
		{
			static char name[16] = "";
			static int rid = 0;
			static char relationship[16] = "";
			components::input_text_with_hint("###name", "Name", name, 16);
			ImGui::InputInt("RID", &rid);
			components::input_text_with_hint("###relationship", "Relationship", relationship, 16);
			components::button("Add", [] {
				g_player_database_service->add_player_to_db(rid, name, relationship);
			});

			ImGui::TreePop();
		}

		ImGui::TreePop();
	}
}