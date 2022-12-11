#include "wren_script.hpp"
#include "scripting/wren/wren_manager.hpp"

namespace big
{
    wren_script::wren_script()
    {

    }

    wren_script::wren_script(WrenVM* vm) :
        m_vm(vm)
    {
        m_has_tick_function = wrenHasModule(m_vm, wren_manager::natives_module_name) &&
            wrenHasVariable(m_vm, wren_manager::natives_module_name, internal_class_name);
        if (m_has_tick_function)
        {
            wrenGetVariable(m_vm, wren_manager::natives_module_name, internal_class_name, 0);
            m_script_internal_metaclass_handle = wrenGetSlotHandle(m_vm, 0);
            m_script_internal_tick_fn_handle = wrenMakeCallHandle(m_vm, internal_tick_method_name);
        }
    }

    WrenForeignMethodFn wren_script::bind_foreign_method(const char* class_name, const char* signature)
    {
        if (strcmp(class_name, wren_script::class_name) == 0)
        {
            if (strcmp(signature, get_time_in_ms_method_name) == 0)
            {
                return get_time_in_ms;
            }
            else if (strcmp(signature, get_global_int_method_name) == 0)
            {
                return get_global_int;
            }
            else if (strcmp(signature, set_global_int_method_name) == 0)
            {
                return set_global_int;
            }
            else if (strcmp(signature, trigger_script_event_method_name) == 0)
            {
                return trigger_script_event;
            }
            else if (strcmp(signature, joaat_method_name) == 0)
            {
                return joaat;
            }
        }

        return nullptr;
    }

    const bool wren_script::has_tick_function() const
    {
        return m_has_tick_function;
    }

    void wren_script::cleanup_memory()
    {
        if (m_has_tick_function)
        {
            wrenReleaseHandle(m_vm, m_script_internal_tick_fn_handle);
            wrenReleaseHandle(m_vm, m_script_internal_metaclass_handle);

            m_has_tick_function = false;
        }

        m_vm = nullptr;
    }
}
