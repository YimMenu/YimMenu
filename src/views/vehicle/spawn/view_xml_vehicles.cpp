#include "pointers.hpp"
#include "services/vehicle/xml_vehicles_service.hpp"
#include "util/vehicle.hpp"
#include "views/view.hpp"

namespace big
{
	void view::xml_vehicles()
	{
		static char search[64];
		components::input_text_with_hint("MODEL_NAME"_T, "SEARCH"_T, search, IM_ARRAYSIZE(search), ImGuiInputTextFlags_None);
		std::string lower_search = search;
		std::transform(lower_search.begin(), lower_search.end(), lower_search.begin(), tolower);

		ImGui::BeginGroup();

		components::button("Reload", [] {
			g_xml_vehicles_service->fetch_xml_files();
		});
		if (ImGui::BeginListBox("##xmllist", {300, static_cast<float>(*g_pointers->m_gta.m_resolution_y - 188 - 38 * 4)}))
		{
			for (auto& [name, doc] : g_xml_vehicles_service->m_all_xml_vehicles)
			{
				std::string lower_name = name;
				std::transform(lower_name.begin(), lower_name.end(), lower_name.begin(), tolower);
				if (lower_name.find(lower_search) != std::string::npos)
				{
					components::selectable(name, false, [&doc] {
						auto handle = g_xml_vehicles_service->spawn_from_xml(doc, self::pos);
						if (g.spawn_vehicle.spawn_inside)
							vehicle::teleport_into_vehicle(handle);
					});
				}
			}

			ImGui::EndListBox();
		}

		ImGui::EndGroup();
	}
}