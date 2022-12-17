#include "scripting/wren/foreign_classes/script/wren_script.hpp"

namespace big
{
    void wren_script::tick_all_modules() const
    {
        if (m_has_tick_function)
        {
            wrenEnsureSlots(m_vm, 1);
            wrenSetSlotHandle(m_vm, 0, m_script_internal_metaclass_handle);
            wrenCall(m_vm, m_script_internal_tick_fn_handle);
        }
    }
}
