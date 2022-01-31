#include "main_tabs.hpp"
#include "fiber_pool.hpp"
#include "script.hpp"
#include "util/mobile.hpp"
#include "util/notify.hpp"
#include "services/mobile_service.hpp"

namespace big
{
	void tab_main::tab_mobile()
	{
		if (ImGui::BeginTabItem("Mobile"))
		{
			if (ImGui::Button("Mors Mutual Fix All Vehicles"))
			{
				int amount_fixed = mobile::mors_mutual::fix_all();

				QUEUE_JOB_BEGIN_CLAUSE(amount_fixed)
				{
					char vehicles_fixed[42];
					sprintf(vehicles_fixed, "<C>%d</C> vehicle%s been fixed.", amount_fixed, amount_fixed == 1 ? " has" : "s have");

					notify::above_map(vehicles_fixed);
				}QUEUE_JOB_END_CLAUSE
			}

			ImGui::Separator();

			if (ImGui::TreeNode("Lester"))
			{
				ImGui::Checkbox("Off Radar", &g.self.off_radar);

				ImGui::TreePop();
			}

			ImGui::Separator();

			if (ImGui::TreeNode("Mechanic - Personal Vehicles"))
			{
				static char search[64];
				static std::string lower_search;

				ImGui::BeginGroup();

				ImGui::SetNextItemWidth(400.f);
				if (ImGui::InputTextWithHint("##search_pv_list", "Search", search, sizeof(search)))
				{
					lower_search = search;
					std::transform(lower_search.begin(), lower_search.end(), lower_search.begin(), tolower);
				}

				if (ImGui::ListBoxHeader("##personal_veh_list", { 400.f, 500.f }))
				{
					for (auto& it : g_mobile_service->m_personal_vehicles)
					{
						std::string label = it.first;
						auto& personal_veh = it.second;

						std::string lower = label.c_str();
						std::transform(lower.begin(), lower.end(), lower.begin(), ::tolower);

						if (lower.find(lower_search) != std::string::npos)
						{
							if (ImGui::Selectable(
								label.c_str(),
								personal_veh->get_id() == mobile::util::get_current_personal_vehicle()
							))
							{
								strcpy(search, "");
								lower_search = search;

								QUEUE_JOB_BEGIN_CLAUSE(&personal_veh)
								{
									personal_veh->summon();
								}QUEUE_JOB_END_CLAUSE
							}
						}
					}

					ImGui::ListBoxFooter();
				}

				ImGui::EndGroup();

				ImGui::SameLine();

				ImGui::BeginGroup();

				if (ImGui::Button("Load/Reload Personal Vehicles"))
				{
					QUEUE_JOB_BEGIN_CLAUSE()
					{
						g_mobile_service->register_vehicles();
					}QUEUE_JOB_END_CLAUSE
				}
				ImGui::Checkbox("Spawn in Vehicle", &g.vehicle.pv_teleport_into);

				ImGui::TreePop();
			}

			ImGui::EndTabItem();
		}
	}
}