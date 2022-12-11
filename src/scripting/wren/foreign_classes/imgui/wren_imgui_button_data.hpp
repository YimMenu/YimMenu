#pragma once
#include "wren.hpp"

namespace big
{
    class wren_imgui_button_data
    {
        std::string m_label;
        WrenHandle* m_fn_instance;

    public:
        wren_imgui_button_data(const std::string& label, WrenHandle* fn_instance);

        const std::string& label() const;

        void cleanup_memory(WrenVM* vm);

        void call() const;
    };
}
