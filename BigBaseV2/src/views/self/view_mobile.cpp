#include "fiber_pool.hpp"
#include "services/mobile/mobile_service.hpp"
#include "services/vehicle_preview/vehicle_preview_service.hpp"
#include "util/mobile.hpp"
#include "views/view.hpp"

namespace big
{
	void view::mobile() {
		ImGui::SetWindowSize({ 0.f, (float)*g_pointers->m_resolution_y }, ImGuiCond_Always);

		components::small_text("Lester");

		ImGui::Checkbox("Off Radar", &g->self.off_radar);

		ImGui::Separator();

		components::button("Mors Mutual Fix All Vehicles", [] {
			int amount_fixed = mobile::mors_mutual::fix_all();
			g_notification_service->push("Mobile",
				fmt::format("{} vehicle{} been fixed.", amount_fixed, amount_fixed == 1 ? " has" : "s have")
			);
			});

		ImGui::Separator();

		components::small_text("Mechanic - Personal Vehicles");

		ImGui::Checkbox("Preview", &g->mobile.preview_vehicle);
		ImGui::SameLine();
		ImGui::Checkbox("Spawn in", &g->mobile.spawn_inside);

		static char search[64];
		static std::string lower_search;

		if (ImGui::InputTextWithHint("Model Name", "Search", search, sizeof(search)))
		{
			lower_search = search;
			std::transform(lower_search.begin(), lower_search.end(), lower_search.begin(), tolower);
		}

		g_mobile_service->refresh_personal_vehicles();
		if (ImGui::ListBoxHeader("##personal_veh_list", { 0, static_cast<float>(*g_pointers->m_resolution_y - 400) }))
		{
			if (g_mobile_service->personal_vehicles().empty())
			{
				ImGui::Text("No personal vehicles found, \nare you online?");
			}
			else
			{
				const auto personal_veh_idx = mobile::util::get_current_personal_vehicle();
				for (const auto& it : g_mobile_service->personal_vehicles())
				{
					const auto& label = it.first;
					const auto& personal_veh = it.second;
					auto item = g_vehicle_preview_service->find_vehicle_item_by_hash(personal_veh->get_hash());

					std::string display_name = label;
					std::string display_manufacturer = item.display_manufacturer;
					std::transform(display_name.begin(), display_name.end(), display_name.begin(), ::tolower);
					std::transform(display_manufacturer.begin(), display_manufacturer.end(), display_manufacturer.begin(), ::tolower);

					if (
						display_name.find(lower_search) != std::string::npos ||
						display_manufacturer.find(lower_search) != std::string::npos
					) {
						if (ImGui::Selectable(label.c_str(), personal_veh->get_id() == personal_veh_idx))
						{
							strcpy(search, "");
							lower_search = search;

							g_fiber_pool->queue_job([&personal_veh] {
								personal_veh->summon();
							});
						}

						if (g->mobile.preview_vehicle && ImGui::IsItemHovered()) {
							g_vehicle_preview_service->set_preview_vehicle(item);
						} else if (g->mobile.preview_vehicle && !ImGui::IsAnyItemHovered()) {
							g_vehicle_preview_service->stop_preview();
						}
					}
				}
			}

			ImGui::ListBoxFooter();
		}
			
	}
}
