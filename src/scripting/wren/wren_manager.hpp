#pragma once
#include "wren.hpp"
#include "wren_module.hpp"
#include "foreign_classes/imgui/wren_imgui.hpp"
#include "foreign_classes/script/wren_script.hpp"

namespace big
{
    class wren_manager
    {
        static constexpr auto func_internal_class_name = "FUNC_INTERNAL";
        static constexpr auto func_internal_call_method_name = "call(_)";

        WrenConfiguration m_config;

        WrenVM* m_vm;

        folder m_scripts_folder;
        std::filesystem::path m_scripts_wren_folder;

        std::unordered_map<std::string, std::unique_ptr<wren_module>> m_wren_modules;

        bool m_has_any_error = false;

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

        void on_native_module_loaded();

        void cleanup_memory();

        void restart_vm();

    public:
        // Name of the wren module file which contains all the native method definitions
        // and all utility methods
        static constexpr auto natives_module_name = "natives";

        wren_script m_script;
        wren_imgui m_imgui;

        wren_manager();
        ~wren_manager();

        void for_each_wren_module_file(std::function<void(const std::string& module_name, const std::filesystem::path& file_path, const std::filesystem::directory_entry& dir_entry)> cb);

        void remove_all_modules();

        void reload_modules();

        void compile_module(const std::string& module_name, const std::filesystem::path& file_path);

        static void tick_all_modules();

        void call_fn_callback(WrenHandle* fn_instance);
    };

    inline wren_manager* g_wren_manager{};
}
