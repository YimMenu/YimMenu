#include "pointers.hpp"
#include "pugixml.hpp"
#include "services/vehicle/xml_vehicles_service.hpp"
#include "util/vehicle.hpp"
#include "views/view.hpp"

namespace big
{
	void view::xml_vehicles()
	{
		ImGui::BeginGroup();

		components::button("Reload", [] {
			g_xml_vehicles_service->fetch_xml_files();
		});
		if (ImGui::BeginListBox("##xmllist", {300, static_cast<float>(*g_pointers->m_gta.m_resolution_y - 188 - 38 * 4)}))
		{
			for (auto& [name, doc] : g_xml_vehicles_service->m_all_xml_vehicles)
			{
				components::selectable(name, false, [&doc] {
					auto handle = g_xml_vehicles_service->spawn_from_xml(doc, self::pos);
					if (g.spawn_vehicle.spawn_inside)
						vehicle::teleport_into_vehicle(handle);
				});
			}

			ImGui::EndListBox();
		}

		ImGui::EndGroup();
	}
}