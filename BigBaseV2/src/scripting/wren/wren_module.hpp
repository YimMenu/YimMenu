#pragma once
#include "wren.hpp"

namespace big
{
    class wren_module
    {
        WrenVM* m_vm = nullptr;
        std::string m_name{};

    public:
        wren_module();
        wren_module(WrenVM* vm, const std::string& module_name);
        ~wren_module();

    };
}
