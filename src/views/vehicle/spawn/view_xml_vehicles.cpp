#include "views/view.hpp"
#include "services/vehicle/xml_vehicles_service.hpp"

namespace big
{
    void view::xml_vehicles()
    {
        ImGui::BeginGroup();

        components::button("Reload", []{ g_xml_vehicles_service->fetch_xml_files();});
        if(ImGui::BeginListBox("##xmllist", {300, static_cast<float>(*g_pointers->m_gta.m_resolution_y - 188 - 38 * 4)}))
        {
            for(const auto& xml_vehicle : g_xml_vehicles_service->m_all_xml_vehicles)
            {
                components::selectable(xml_vehicle.first, false, [] {

                });
            }

            ImGui::EndListBox();
        }

        ImGui::EndGroup();
    }
}