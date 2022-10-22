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

        if (strcmp(class_name, wren_vector3::class_name) == 0)
        {
            methods.allocate = wren_vector3::allocate;
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
            if (const auto res = wren_script::bind_foreign_method(class_name, signature); res)
            {
                return res;
            }
            else if (const auto res = wren_imgui::bind_foreign_method(class_name, signature); res)
            {
                return res;
            }
            else if (const auto res = wren_vector3::bind_foreign_method(class_name, signature); res)
            {
                return res;
            }
        }

        return nullptr;
    }

    void wren_manager::wren_load_module_complete(WrenVM* vm, const char* module, WrenLoadModuleResult result)
    {
        if (result.source)
        {
            delete[] result.source;

            g_wren_manager->m_wren_modules[module] = std::make_unique<wren_module>(g_wren_manager->m_vm, module);

            if (strcmp(module, natives_module_name) == 0)
            {
                g_wren_manager->on_native_module_loaded();
            }
        }
    }

    WrenLoadModuleResult wren_manager::wren_load_module(WrenVM* vm, const char* name)
    {
        WrenLoadModuleResult result = { 0 };

        g_wren_manager->for_each_wren_module_file([&](const auto& module_name, const auto& file_path, const auto& dir_entry)
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

    void wren_manager::on_native_module_loaded()
    {
        // native module is loaded, we can get the WrenHandles

        wrenEnsureSlots(m_vm, 1);

        m_script = wren_script(m_vm);

        m_has_func_internal_function = wrenHasModule(m_vm, wren_manager::natives_module_name) &&
            wrenHasVariable(m_vm, wren_manager::natives_module_name, wren_manager::func_internal_class_name);
        if (m_has_func_internal_function)
        {
            wrenGetVariable(m_vm, wren_manager::natives_module_name, wren_manager::func_internal_class_name, 0);
            m_func_internal_metaclass_handle = wrenGetSlotHandle(m_vm, 0);
            m_func_internal_call_fn_handle = wrenMakeCallHandle(m_vm, wren_manager::func_internal_call_method_name);
        }

        m_imgui = wren_imgui(m_vm);
    }

    void wren_manager::for_each_wren_module_file(std::function<void(const std::string& module_name, const std::filesystem::path& file_path, const std::filesystem::directory_entry& dir_entry)> cb)
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
            reload_modules();
        });

        g_wren_manager = this;
    }

    void wren_manager::cleanup_memory()
    {
        m_imgui.cleanup_memory();

        if (m_has_func_internal_function)
        {
            wrenReleaseHandle(m_vm, m_func_internal_call_fn_handle);
            wrenReleaseHandle(m_vm, m_func_internal_metaclass_handle);

            m_has_func_internal_function = false;
        }

        m_script.cleanup_memory();

        // we call this there manually instead of letting the unique ptrs dctor trigger automatically
        // because freeing the VM should be the last thing we do. (see https://wren.io/embedding/ for the why)
        remove_all_modules();

        wrenFreeVM(m_vm);

        m_has_any_error = false;
    }

    wren_manager::~wren_manager()
    {
        cleanup_memory();

        g_wren_manager = nullptr;
    }

    void wren_manager::remove_all_modules()
    {
        m_wren_modules.clear();
    }

    void wren_manager::restart_vm()
    {
        cleanup_memory();
        m_vm = wrenNewVM(&m_config);
    }

    void wren_manager::reload_modules()
    {
        if (m_wren_modules.size())
        {
            restart_vm();
        }

        for_each_wren_module_file([this](const auto& module_name, const auto& file_path, const auto& dir_entry)
        {
            compile_module(module_name, file_path);
        });

        if (m_has_any_error)
        {
            restart_vm();

            g_fiber_pool->queue_job([]
            {
                notify::above_map("[Wren Scripting] Failed to compile. Fix the scripts errors and press the Reload Scripts button.");
            });

            return;
        }

        LOG(INFO) << "Number of wren modules loaded: " << m_wren_modules.size();
    }

    void wren_manager::compile_module(const std::string& module_name, const std::filesystem::path& file_path)
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

            m_wren_modules[module_name] = std::make_unique<wren_module>(m_vm, module_name);

            if (strcmp(module_name.c_str(), natives_module_name) == 0)
            {
                g_wren_manager->on_native_module_loaded();
            }

            break;
        }
        default:
            break;
        }
    }

    void wren_manager::tick_all_modules()
    {
        while (g_running)
        {
            g_wren_manager->m_script.tick_all_modules();

            script::get_current()->yield();
        }
    }

    void wren_manager::call_fn_callback(WrenHandle* fn_instance)
    {
        wrenEnsureSlots(m_vm, 2);
        wrenSetSlotHandle(m_vm, 0, m_func_internal_metaclass_handle);
        wrenSetSlotHandle(m_vm, 1, fn_instance);
        wrenCall(m_vm, m_func_internal_call_fn_handle);
    }
}
