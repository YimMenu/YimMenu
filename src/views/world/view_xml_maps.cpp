#include "views/view.hpp"
#include "services/xml_maps/xml_map_service.hpp"

namespace big
{
   void view::xml_maps()
   {
        components::button("REFRESH"_T, [] {
            g_fiber_pool->queue_job([] {
                g_xml_map_service->fetch_xml_files();
            });
        });
        if(ImGui::BeginListBox("##xmlmaps", get_listbox_dimensions()))
        {
            for (auto& [name, xml_map] : g_xml_map_service->m_all_xml_maps)
            {
                if (ImGui::Selectable(name.c_str()))
                {
                    g_fiber_pool->queue_job([=, &xml_map] {
                        g_xml_map_service->spawn_from_xml(xml_map);
                    });
                }
            }
            ImGui::EndListBox();
        }
   } 
} 
