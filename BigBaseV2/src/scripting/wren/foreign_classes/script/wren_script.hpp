#pragma once
#include "wren.hpp"

namespace big
{
    class wren_script
    {
        static constexpr auto internal_class_name = "SCRIPT_INTERNAL";
        static constexpr auto internal_tick_method_name = "TICK()";

        static constexpr auto class_name = "Script";
        static constexpr auto get_time_in_ms_method_name = "get_time_in_ms()";
        static constexpr auto get_global_int_method_name = "get_global_int(_)";
        static constexpr auto set_global_int_method_name = "set_global_int(_,_)";
        static constexpr auto trigger_script_event_method_name = "tse(_,_)";
        static constexpr auto joaat_method_name = "joaat(_)";

        WrenVM* m_vm = nullptr;

        bool m_has_tick_function = false;
        WrenHandle* m_script_internal_metaclass_handle = nullptr;
        WrenHandle* m_script_internal_tick_fn_handle = nullptr;

    public:
        wren_script();
        wren_script(WrenVM* vm);

        static WrenForeignMethodFn bind_foreign_method(const char* class_name, const char* signature);

        const bool has_tick_function() const;

        void tick_all_modules() const;

        void cleanup_memory();

    private:
        static void get_time_in_ms(WrenVM* vm);

        static void get_global_int(WrenVM* vm);
        static void set_global_int(WrenVM* vm);

        static void trigger_script_event(WrenVM* vm);

        static void joaat(WrenVM* vm);
    };
}
