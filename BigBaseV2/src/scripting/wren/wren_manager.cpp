#include "wren_manager.hpp"
#include "wren.hpp"
#include "wren_Vector3.hpp"
#include "wren_natives.hpp"
#include "script.hpp"
#include "fiber_pool.hpp"
#include "pointers.hpp"
#include "script_global.hpp"
#include "util/notify.hpp"

namespace big
{
    static void wren_write(WrenVM* vm, const char* text)
    {
        if (text && *text)
        {
            size_t i = 0;
            while (text[i])
            {
                if (!isspace(text[i]))
                {
                    LOG(INFO) << "[wren] " << text;
                    return;
                }

                i++;
            }
        }
    }

    void wren_manager::wren_error(WrenVM* vm, WrenErrorType errorType,
        const char* module, const int line,
        const char* msg)
    {
        switch (errorType)
        {
        case WREN_ERROR_COMPILE:
        {
            LOG(INFO) << "[wren] [" << module << " line " << line << "] [Error] " << msg;
        } break;
        case WREN_ERROR_STACK_TRACE:
        {
            LOG(INFO) << "[wren] [" << module << " line " << line << "] in " << msg;
        } break;
        case WREN_ERROR_RUNTIME:
        {
            LOG(INFO) << "[wren] [Runtime Error] " << msg;
        } break;
        }

        g_wren_manager->m_has_any_error = true;
    }

    static WrenForeignClassMethods wren_bind_foreign_class(
        WrenVM* vm, const char* module, const char* class_name)
    {
        WrenForeignClassMethods methods;

        if (strcmp(class_name, "Vector3") == 0)
        {
            methods.allocate = wren_Vector3::allocate;
            methods.finalize = NULL;
        }
        else
        {
            // Unknown class.
            methods.allocate = NULL;
            methods.finalize = NULL;
        }

        return methods;
    }

    static void wren_script_get_time_in_ms(WrenVM* vm)
    {
        const double time_in_ms = (double)std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now().time_since_epoch()).count();
        wrenSetSlotDouble(vm, 0, time_in_ms);
    }

    static void wren_script_get_global_int(WrenVM* vm)
    {
        const auto index = (size_t)wrenGetSlotDouble(vm, 1);
        const auto value = *script_global(index).as<int*>();
        wrenSetSlotDouble(vm, 0, (double)value);
    }

    static void wren_script_set_global_int(WrenVM* vm)
    {
        const auto index = (size_t)wrenGetSlotDouble(vm, 1);
        const auto value = (int)wrenGetSlotDouble(vm, 2);
        *script_global(index).as<int*>() = value;
    }

    static void wren_script_trigger_script_event(WrenVM* vm)
    {
        constexpr int event_group = 1;

        constexpr int player_bits_slot = 1;
        int player_bits = (int)wrenGetSlotDouble(vm, player_bits_slot);
        constexpr int send_to_everyone = -1;
        if (player_bits != send_to_everyone)
        {
            player_bits = 1 << player_bits;
        }

        constexpr int args_slot = 2;
        const int arg_count = wrenGetListCount(vm, args_slot);
        std::vector<int64_t> args(arg_count);
        for (int i = 0; i < arg_count; i++)
        {
            constexpr int get_el_slot = 0;
            wrenGetListElement(vm, args_slot, i, get_el_slot);
            args.push_back((int64_t)wrenGetSlotDouble(vm, get_el_slot));
        }

        constexpr size_t args_sender_index = 1;
        if (args.size() > args_sender_index)
            args[args_sender_index] = self::id; // prevent detection from AC
        g_pointers->m_trigger_script_event(event_group, args.data(), arg_count, player_bits);
    }

    static void wren_imgui_button(WrenVM* vm)
    {
        wren_imgui_button_data btn;
        btn.label = wrenGetSlotString(vm, 1);
        btn.fn_instance = wrenGetSlotHandle(vm, 2);
        g_wren_manager->m_imgui_buttons.push_back(btn);
    }

    WrenForeignMethodFn wren_manager::wren_bind_foreign_method(
        WrenVM* vm,
        const char* module,
        const char* class_name,
        bool is_static,
        const char* signature)
    {
        if (const auto it = wren_natives_handlers.find(signature); it != wren_natives_handlers.end())
        {
            return it->second;
        }
        else if (strcmp(module, wren_manager::natives_module_name) == 0)
        {
            if (strcmp(class_name, wren_manager::script_class_name) == 0)
            {
                if (strcmp(signature, wren_manager::script_get_time_in_ms_method_name) == 0)
                {
                    return wren_script_get_time_in_ms;
                }
                else if (strcmp(signature, wren_manager::script_get_global_int_method_name) == 0)
                {
                    return wren_script_get_global_int;
                }
                else if (strcmp(signature, wren_manager::script_set_global_int_method_name) == 0)
                {
                    return wren_script_set_global_int;
                }
                else if (strcmp(signature, wren_manager::script_trigger_script_event_method_name) == 0)
                {
                    return wren_script_trigger_script_event;
                }
            }
            else if (strcmp(class_name, wren_manager::imgui_class_name) == 0)
            {
                if (strcmp(signature, wren_manager::imgui_button_method_name) == 0)
                {
                    return wren_imgui_button;
                }
            }
            else if (strcmp(class_name, "Vector3") == 0)
            {
                if (strcmp(signature, "x") == 0)
                {
                    return wren_Vector3::get_x;
                }
                else if (strcmp(signature, "y") == 0)
                {
                    return wren_Vector3::get_y;
                }
                else if (strcmp(signature, "z") == 0)
                {
                    return wren_Vector3::get_z;
                }
                else if (strcmp(signature, "x=(_)") == 0)
                {
                    return wren_Vector3::set_x;
                }
                else if (strcmp(signature, "y=(_)") == 0)
                {
                    return wren_Vector3::set_y;
                }
                else if (strcmp(signature, "z=(_)") == 0)
                {
                    return wren_Vector3::set_z;
                }
            }
        }

        return nullptr;
    }

    void wren_manager::wren_load_module_complete(WrenVM* vm, const char* module, WrenLoadModuleResult result)
    {
        if (result.source)
        {
            delete[] result.source;

            g_wren_manager->m_wren_scripts[module] = std::make_unique<wren_script>(g_wren_manager->m_vm, module);
        }
    }

    WrenLoadModuleResult wren_manager::wren_load_module(WrenVM* vm, const char* name)
    {
        WrenLoadModuleResult result = { 0 };

        g_wren_manager->for_each_wren_script_file([&](const auto& module_name, const auto& file_path, const auto& dir_entry)
        {
            if (strcmp(module_name.c_str(), name) == 0)
            {
                std::ifstream file_path_ifstream(file_path);
                std::stringstream buffer;
                buffer << file_path_ifstream.rdbuf();
                const auto script = buffer.str();

                char* heap_source_text = new char[script.size()];
                memcpy(heap_source_text, script.data(), script.size());

                result.source = heap_source_text;
                result.onComplete = wren_manager::wren_load_module_complete;

                return;
            }
        });

        return result;
    }

    void wren_manager::for_each_wren_script_file(std::function<void(const std::string& module_name, const std::filesystem::path& file_path, const std::filesystem::directory_entry& dir_entry)> cb)
    {
        for (const auto& dir_entry : std::filesystem::recursive_directory_iterator(m_scripts_wren_folder))
        {
            if (dir_entry.is_regular_file())
            {
                const auto& file_path = dir_entry.path();
                if (file_path.extension() == ".wren" && file_path.has_stem())
                {
                    const auto module = file_path.stem().u8string();

                    cb(module, file_path, dir_entry);
                }
            }
        }
    }

    wren_manager::wren_manager() :
        m_scripts_folder(g_file_manager->get_project_folder("./scripts")),
        m_scripts_wren_folder(g_file_manager->get_project_folder("./scripts/wren").get_path())
    {
        wrenInitConfiguration(&m_config);
        m_config.writeFn = &wren_write;
        m_config.errorFn = &wren_error;
        m_config.bindForeignClassFn = &wren_bind_foreign_class;
        m_config.bindForeignMethodFn = &wren_bind_foreign_method;
        m_config.loadModuleFn = wren_load_module;

        m_vm = wrenNewVM(&m_config);

        g_fiber_pool->queue_job([this]
        {
            reload_scripts();
        });

        g_wren_manager = this;
    }

    void wren_manager::cleanup_memory()
    {
        if (m_has_tick_function)
        {
            wrenReleaseHandle(m_vm, m_script_internal_tick_fn_handle);
            wrenReleaseHandle(m_vm, m_script_internal_metaclass_handle);

            m_has_tick_function = false;
        }

        for (const auto& btn : m_imgui_buttons)
        {
            wrenReleaseHandle(m_vm, btn.fn_instance);
        }
        m_imgui_buttons.clear();

        if (m_has_func_internal_function)
        {
            wrenReleaseHandle(m_vm, m_func_internal_call_fn_handle);
            wrenReleaseHandle(m_vm, m_func_internal_metaclass_handle);

            m_has_func_internal_function = false;
        }

        // we call this there manually instead of letting the unique ptrs dctor trigger automatically
        // because freeing the VM should be the last thing we do. (see https://wren.io/embedding/ for the why)
        remove_all_scripts();

        wrenFreeVM(m_vm);

        m_has_any_error = false;
    }

    wren_manager::~wren_manager()
    {
        cleanup_memory();

        g_wren_manager = nullptr;
    }

    void wren_manager::remove_all_scripts()
    {
        m_wren_scripts.clear();
    }

    void wren_manager::restart_vm()
    {
        cleanup_memory();
        m_vm = wrenNewVM(&m_config);
    }

    void wren_manager::reload_scripts()
    {
        if (m_wren_scripts.size())
        {
            restart_vm();
        }

        for_each_wren_script_file([this](const auto& module_name, const auto& file_path, const auto& dir_entry)
        {
            compile_script(module_name, file_path);
        });

        LOG(INFO) << "Number of wren scripts loaded: " << m_wren_scripts.size();

        if (m_has_any_error)
        {
            restart_vm();

            g_fiber_pool->queue_job([]
            {
                notify::above_map("[Wren Scripting] Failed to compile. Fix the scripts errors and press the Reload Scripts button.");
            });

            return;
        }

        wrenEnsureSlots(m_vm, 1);

        m_has_func_internal_function = wrenHasModule(m_vm, wren_manager::natives_module_name) &&
            wrenHasVariable(m_vm, wren_manager::natives_module_name, wren_manager::func_internal_class_name);
        if (m_has_func_internal_function)
        {
            wrenGetVariable(m_vm, wren_manager::natives_module_name, wren_manager::func_internal_class_name, 0);
            m_func_internal_metaclass_handle = wrenGetSlotHandle(m_vm, 0);
            m_func_internal_call_fn_handle = wrenMakeCallHandle(m_vm, wren_manager::func_internal_call_method_name);
        }

        m_has_tick_function = wrenHasModule(m_vm, wren_manager::natives_module_name) &&
            wrenHasVariable(m_vm, wren_manager::natives_module_name, wren_manager::script_internal_class_name);
        if (m_has_tick_function)
        {
            wrenGetVariable(m_vm, wren_manager::natives_module_name, wren_manager::script_internal_class_name, 0);
            m_script_internal_metaclass_handle = wrenGetSlotHandle(m_vm, 0);
            m_script_internal_tick_fn_handle = wrenMakeCallHandle(m_vm, wren_manager::script_internal_tick_method_name);
        }
    }

    void wren_manager::compile_script(const std::string& module_name, const std::filesystem::path& file_path)
    {
        std::ifstream file_path_ifstream(file_path);
        std::stringstream buffer;
        buffer << file_path_ifstream.rdbuf();
        const auto script = buffer.str();

        WrenInterpretResult result = wrenInterpret(m_vm, module_name.c_str(), script.c_str());

        switch (result)
        {
        case WREN_RESULT_COMPILE_ERROR:
            LOG(INFO) << "Compile error for " << file_path;

            m_has_any_error = true;

            break;
        case WREN_RESULT_RUNTIME_ERROR:
            LOG(INFO) << "Runtime error for " << file_path;

            m_has_any_error = true;

            break;
        case WREN_RESULT_SUCCESS:
        {
            LOG(INFO) << "Successfully executed " << file_path;

            m_wren_scripts[module_name] = std::make_unique<wren_script>(m_vm, module_name);

            break;
        }
        default:
            break;
        }
    }

    void wren_manager::tick_all_scripts()
    {
        while (g_running)
        {
            if (g_wren_manager->m_has_tick_function)
            {
                wrenEnsureSlots(g_wren_manager->m_vm, 1);
                wrenSetSlotHandle(g_wren_manager->m_vm, 0, g_wren_manager->m_script_internal_metaclass_handle);
                wrenCall(g_wren_manager->m_vm, g_wren_manager->m_script_internal_tick_fn_handle);
            }

            script::get_current()->yield();
        }
    }

    void wren_manager::call_btn(const wren_imgui_button_data& btn)
    {
        wrenEnsureSlots(m_vm, 2);
        wrenSetSlotHandle(m_vm, 0, m_func_internal_metaclass_handle);
        wrenSetSlotHandle(m_vm, 1, btn.fn_instance);
        wrenCall(m_vm, m_func_internal_call_fn_handle);
    }
}
