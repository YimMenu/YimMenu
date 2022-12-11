#include "scripting/wren/foreign_classes/script/wren_script.hpp"
#include "script_global.hpp"

namespace big
{
    void wren_script::get_global_int(WrenVM* vm)
    {
        const auto index = (size_t)wrenGetSlotDouble(vm, 1);
        const auto value = *script_global(index).as<int*>();
        wrenSetSlotDouble(vm, 0, (double)value);
    }

    void wren_script::set_global_int(WrenVM* vm)
    {
        const auto index = (size_t)wrenGetSlotDouble(vm, 1);
        const auto value = (int)wrenGetSlotDouble(vm, 2);
        *script_global(index).as<int*>() = value;
    }
}
