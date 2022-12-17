#include "scripting/wren/foreign_classes/imgui/wren_imgui_button_data.hpp"
#include "scripting/wren/wren_manager.hpp"

namespace big
{
    wren_imgui_button_data::wren_imgui_button_data(const std::string& label, WrenHandle* fn_instance) :
        m_label(label),
        m_fn_instance(fn_instance)
    {

    }

    const std::string& wren_imgui_button_data::label() const
    {
        return m_label;
    }

    void wren_imgui_button_data::cleanup_memory(WrenVM* vm)
    {
        wrenReleaseHandle(vm, m_fn_instance);
    }

    void wren_imgui_button_data::call() const
    {
        g_wren_manager->call_fn_callback(m_fn_instance);
    }
}
