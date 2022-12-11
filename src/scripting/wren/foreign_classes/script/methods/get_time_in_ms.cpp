#include "scripting/wren/foreign_classes/script/wren_script.hpp"

namespace big
{
    void wren_script::get_time_in_ms(WrenVM* vm)
    {
        const double time_in_ms = (double)std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now().time_since_epoch()).count();
        wrenSetSlotDouble(vm, 0, time_in_ms);
    }
}
