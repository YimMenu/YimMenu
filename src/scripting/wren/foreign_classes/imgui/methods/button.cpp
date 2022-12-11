#include "scripting/wren/foreign_classes/imgui/wren_imgui.hpp"
#include "scripting/wren/wren_manager.hpp"

namespace big
{
    void wren_imgui::button(WrenVM* vm)
    {
        wren_imgui_button_data btn(wrenGetSlotString(vm, 1), wrenGetSlotHandle(vm, 2));
        g_wren_manager->m_imgui.m_buttons.push_back(btn);
    }
}
