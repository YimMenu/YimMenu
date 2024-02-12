#pragma once
#include "memory/module.hpp"

namespace big
{
    inline bool is_proton()
    {
        static auto module = memory::module("ntdll.dll");
        
        const auto env_no_color = std::getenv("NO_COLOR");
        return module.get_export("wine_get_version") || (env_no_color && strlen(env_no_color));
    }
}
