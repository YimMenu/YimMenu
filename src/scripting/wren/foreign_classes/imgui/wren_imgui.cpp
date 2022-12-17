#include "wren_imgui.hpp"

namespace big
{
    wren_imgui::wren_imgui()
    {

    }

    wren_imgui::wren_imgui(WrenVM* vm) :
        m_vm(vm)
    {

    }

    WrenForeignMethodFn wren_imgui::bind_foreign_method(const char* class_name, const char* signature)
    {
        if (strcmp(class_name, wren_imgui::class_name) == 0)
        {
            if (strcmp(signature, button_method_name) == 0)
            {
                return button;
            }
        }

        return nullptr;
    }

    const std::vector<wren_imgui_button_data>& wren_imgui::buttons() const
    {
        return m_buttons;
    }

    void wren_imgui::cleanup_memory()
    {
        for (auto& button : m_buttons)
        {
            button.cleanup_memory(m_vm);
        }

        m_buttons.clear();

        m_vm = nullptr;
    }
}
