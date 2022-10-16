#include "views/view.hpp"
#include "scripting/wren/wren_manager.hpp"

namespace big
{
    void view::wren()
    {
        components::button("Reload Scripts", [&]
        {
            g_wren_manager->reload_scripts();
        });

        for (const auto& btn : g_wren_manager->m_imgui_buttons)
        {
            components::button(btn.label.c_str(), [&]
            {
                g_wren_manager->call_btn(btn);
            });
        }
    }
}
