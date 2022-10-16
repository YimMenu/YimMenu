#pragma once
#include "wren.hpp"

namespace big
{
    class wren_script
    {
        WrenVM* m_vm = nullptr;
        std::string m_module_name{};

    public:
        wren_script();
        wren_script(WrenVM* vm, const std::string& module_name);
        ~wren_script();

    };
}
