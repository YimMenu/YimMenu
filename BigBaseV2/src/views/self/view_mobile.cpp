#include "fiber_pool.hpp"
#include "services/mobile/mobile_service.hpp"
#include "util/mobile.hpp"
#include "views/view.hpp"

namespace big
{
	void view::mobile() {
		components::button("Mors Mutual Fix All Vehicles", [] {
			int amount_fixed = mobile::mors_mutual::fix_all();
			g_notification_service->push("Mobile",
				fmt::format("{} vehicle{} been fixed.", amount_fixed, amount_fixed == 1 ? " has" : "s have")
			);
		});

		ImGui::Separator();

		components::small_text("Lester");

		ImGui::Checkbox("Off Radar", &g->self.off_radar);

		ImGui::Separator();

		components::small_text("Mechanic - Personal Vehicles");

		static char search[64];
		static std::string lower_search;

		ImGui::BeginGroup();

		ImGui::SetNextItemWidth(400.f);
		if (ImGui::InputTextWithHint("##search_pv_list", "Search", search, sizeof(search)))
		{
			lower_search = search;
			std::transform(lower_search.begin(), lower_search.end(), lower_search.begin(), tolower);
		}

		g_mobile_service->refresh_personal_vehicles();
		if (ImGui::ListBoxHeader("##personal_veh_list", { 400.f, 500.f }))
		{
			if (g_mobile_service->personal_vehicles().empty())
			{
				ImGui::Text("No personal vehicles found, are you online?");
			}
			else
			{
				const auto personal_veh_idx = mobile::util::get_current_personal_vehicle();
				for (const auto& it : g_mobile_service->personal_vehicles())
				{
					const auto& label = it.first;
					const auto& personal_veh = it.second;

					auto lower = label;
					std::transform(lower.begin(), lower.end(), lower.begin(), ::tolower);

					if (lower.find(lower_search) != std::string::npos)
					{
						if (ImGui::Selectable(label.c_str(), personal_veh->get_id() == personal_veh_idx))
						{
							strcpy(search, "");
							lower_search = search;

							g_fiber_pool->queue_job([&personal_veh] {
								personal_veh->summon();
							});
						}
					}
				}
			}

			ImGui::ListBoxFooter();
		}

		ImGui::EndGroup();

		ImGui::BeginGroup();
		
		ImGui::Checkbox("Spawn in Vehicle", &g->vehicle.pv_teleport_into);

		ImGui::EndGroup();
			
	}
}
