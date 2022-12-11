#include "scripting/wren/foreign_classes/script/wren_script.hpp"

namespace big
{
    void wren_script::joaat(WrenVM* vm)
    {
        wrenSetSlotDouble(vm, 0, (double)rage::joaat(wrenGetSlotString(vm, 1)));
    }
}
