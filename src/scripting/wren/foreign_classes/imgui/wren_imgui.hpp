#pragma once
#include "wren.hpp"
#include "wren_imgui_button_data.hpp"

namespace big
{
    class wren_imgui
    {
        static constexpr auto class_name = "ImGui";
        static constexpr auto button_method_name = "button(_,_)";

        WrenVM* m_vm = nullptr;
        std::vector<wren_imgui_button_data> m_buttons;

        static void button(WrenVM* vm);

    public:
        wren_imgui();
        wren_imgui(WrenVM* vm);

        static WrenForeignMethodFn bind_foreign_method(const char* class_name, const char* signature);

        const std::vector<wren_imgui_button_data>& buttons() const;

        void cleanup_memory();

    };
}
