#pragma once
#include "wren.hpp"
#include "wren_script.hpp"

namespace big
{
    struct wren_imgui_button_data
    {
        std::string label;
        WrenHandle* fn_instance;
    };

    class wren_manager
    {
        static constexpr auto natives_module_name = "natives";

        static constexpr auto script_internal_class_name = "SCRIPT_INTERNAL";
        static constexpr auto script_internal_tick_method_name = "TICK()";

        static constexpr auto script_class_name = "Script";
        static constexpr auto script_get_time_in_ms_method_name = "get_time_in_ms()";
        static constexpr auto script_get_global_int_method_name = "get_global_int(_)";
        static constexpr auto script_set_global_int_method_name = "set_global_int(_,_)";
        static constexpr auto script_trigger_script_event_method_name = "tse(_,_)";

        static constexpr auto func_internal_class_name = "FUNC_INTERNAL";
        static constexpr auto func_internal_call_method_name = "call(_)";

        static constexpr auto imgui_class_name = "ImGui";
        static constexpr auto imgui_button_method_name = "button(_,_)";

        WrenConfiguration m_config;

        WrenVM* m_vm;

        folder m_scripts_folder;
        std::filesystem::path m_scripts_wren_folder;

        std::unordered_map<std::string, std::unique_ptr<wren_script>> m_wren_scripts;

        bool m_has_any_error = false;

        bool m_has_tick_function = false;
        WrenHandle* m_script_internal_metaclass_handle = nullptr;
        WrenHandle* m_script_internal_tick_fn_handle = nullptr;

        bool m_has_func_internal_function = false;
        WrenHandle* m_func_internal_metaclass_handle = nullptr;
        WrenHandle* m_func_internal_call_fn_handle = nullptr;

        static void wren_error(WrenVM* vm, WrenErrorType errorType,
            const char* module, const int line,
            const char* msg);


        static WrenForeignMethodFn wren_bind_foreign_method(
            WrenVM* vm,
            const char* module, const char* class_name,
            bool is_static,
            const char* signature);

        static void wren_load_module_complete(WrenVM* vm, const char* module, WrenLoadModuleResult result);
        static WrenLoadModuleResult wren_load_module(WrenVM* vm, const char* name);

        void cleanup_memory();

        void restart_vm();

    public:
        std::vector<wren_imgui_button_data> m_imgui_buttons;

        wren_manager();
        ~wren_manager();

        void for_each_wren_script_file(std::function<void(const std::string& module_name, const std::filesystem::path& file_path, const std::filesystem::directory_entry& dir_entry)> cb);

        void remove_all_scripts();

        void reload_scripts();

        void compile_script(const std::string& module_name, const std::filesystem::path& file_path);

        static void tick_all_scripts();

        void call_btn(const wren_imgui_button_data& btn);

    };

    inline wren_manager* g_wren_manager{};
}
