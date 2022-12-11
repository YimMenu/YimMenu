#include "views/view.hpp"
#include "scripting/wren/wren_manager.hpp"

namespace big
{
    void view::wren()
    {
        components::button("Reload Scripts", [&]
        {
            g_wren_manager->reload_modules();
        });

        for (const auto& btn : g_wren_manager->m_imgui.buttons())
        {
            components::button(btn.label().c_str(), [&]
            {
                btn.call();
            });
        }
    }
}
