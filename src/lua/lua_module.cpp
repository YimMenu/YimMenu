#include "lua_module.hpp"

#include "bindings/command.hpp"
#include "bindings/entities.hpp"
#include "bindings/event.hpp"
#include "bindings/global_table.hpp"
#include "bindings/globals.hpp"
#include "bindings/gui.hpp"
#include "bindings/imgui.hpp"
#include "bindings/locals.hpp"
#include "bindings/log.hpp"
#include "bindings/memory.hpp"
#include "bindings/native.hpp"
#include "bindings/network.hpp"
#include "bindings/script.hpp"
#include "bindings/stats.hpp"
#include "bindings/tunables.hpp"
#include "bindings/vector.hpp"
#include "file_manager.hpp"
#include "script_mgr.hpp"

namespace big
{
	// https://sol2.readthedocs.io/en/latest/exceptions.html
	int exception_handler(lua_State* L, sol::optional<const std::exception&> maybe_exception, sol::string_view description)
	{
		// L is the lua state, which you can wrap in a state_view if necessary
		// maybe_exception will contain exception, if it exists
		// description will either be the what() of the exception or a description saying that we hit the general-case catch(...)
		if (maybe_exception)
		{
			const std::exception& ex = *maybe_exception;
			LOG(FATAL) << ex.what();
		}
		else
		{
			LOG(FATAL) << description;
		}
		Logger::FlushQueue();

		// you must push 1 element onto the stack to be
		// transported through as the error object in Lua
		// note that Lua -- and 99.5% of all Lua users and libraries -- expects a string
		// so we push a single string (in our case, the description of the error)
		return sol::stack::push(L, description);
	}

	inline void panic_handler(sol::optional<std::string> maybe_msg)
	{
		LOG(FATAL) << "Lua is in a panic state and will now abort() the application";
		if (maybe_msg)
		{
			const std::string& msg = maybe_msg.value();
			LOG(FATAL) << "error message: " << msg;
		}
		Logger::FlushQueue();

		// When this function exits, Lua will exhibit default behavior and abort()
	}

	lua_module::lua_module(const std::filesystem::path& module_path, folder& scripts_folder) :
	    m_state(),
	    m_module_path(module_path),
	    m_module_name(module_path.filename().string()),
	    m_module_id(rage::joaat(m_module_name))
	{
		// clang-format off
		m_state.open_libraries(
			sol::lib::base,
			sol::lib::package,
			sol::lib::coroutine,
		    sol::lib::string,
		    sol::lib::os,
		    sol::lib::math,
			sol::lib::table,
			sol::lib::bit32,
			sol::lib::utf8
		);
		// clang-format on

		init_lua_api(scripts_folder);

		m_state["!module_name"] = m_module_name;
		m_state["!this"]        = this;

		m_state.set_exception_handler(exception_handler);
		m_state.set_panic(sol::c_call<decltype(&panic_handler), &panic_handler>);

		m_last_write_time = std::filesystem::last_write_time(m_module_path);
	}

	lua_module::~lua_module()
	{
		{
			std::lock_guard guard(m_registered_scripts_mutex);
			m_registered_scripts.clear();
		}

		for (const auto owned_tab : m_owned_tabs)
		{
			big::g_gui_service->remove_from_nav(owned_tab);
		}

		for (auto memory : m_allocated_memory)
			delete[] memory;
	}

	rage::joaat_t lua_module::module_id() const
	{
		return m_module_id;
	}

	const std::string& lua_module::module_name() const
	{
		return m_module_name;
	}

	const std::filesystem::path& lua_module::module_path() const
	{
		return m_module_path;
	}

	const std::chrono::time_point<std::chrono::file_clock> lua_module::last_write_time() const
	{
		return m_last_write_time;
	}

	void lua_module::set_folder_for_lua_require(folder& scripts_folder)
	{
		std::string scripts_search_path = scripts_folder.get_path().string() + "/?.lua;";

		for (const auto& entry : std::filesystem::recursive_directory_iterator(scripts_folder.get_path(), std::filesystem::directory_options::skip_permission_denied))
		{
			if (!entry.is_directory())
				continue;

			scripts_search_path += entry.path().string() + "/?.lua;";
		}
		// Remove final ';'
		scripts_search_path.pop_back();

		m_state["package"]["path"] = scripts_search_path;
	}

	void lua_module::sandbox_lua_os_library()
	{
		const auto& os = m_state["os"];
		sol::table sandbox_os(m_state, sol::create);

		sandbox_os["clock"]    = os["clock"];
		sandbox_os["date"]     = os["date"];
		sandbox_os["difftime"] = os["difftime"];
		sandbox_os["time"]     = os["time"];

		m_state["os"] = sandbox_os;
	}

	template<size_t N>
	static constexpr auto not_supported_lua_function(const char (&function_name)[N])
	{
		return [function_name](sol::this_state state, sol::variadic_args args) {
			big::lua_module* module = sol::state_view(state)["!this"];

			LOG(FATAL) << module->module_name() << " tried calling a currently not supported lua function: " << function_name;
			Logger::FlushQueue();
		};
	}

	void lua_module::sandbox_lua_loads(folder& scripts_folder)
	{
		// That's from lua base lib, luaB
		m_state["load"]       = not_supported_lua_function("load");
		m_state["loadstring"] = not_supported_lua_function("loadstring");
		m_state["loadfile"]   = not_supported_lua_function("loadfile");
		m_state["dofile"]     = not_supported_lua_function("dofile");

		// That's from lua package lib.
		// We only allow dependencies between .lua files, no DLLs.
		m_state["package"]["loadlib"] = not_supported_lua_function("package.loadlib");
		m_state["package"]["cpath"]   = "";

		// 1                   2               3            4
		// {searcher_preload, searcher_Lua, searcher_C, searcher_Croot, NULL};
		m_state["package"]["searchers"][3] = not_supported_lua_function("package.searcher C");
		m_state["package"]["searchers"][4] = not_supported_lua_function("package.searcher Croot");

		set_folder_for_lua_require(scripts_folder);
	}

	void lua_module::init_lua_api(folder& scripts_folder)
	{
		// https://blog.rubenwardy.com/2020/07/26/sol3-script-sandbox/
		// https://www.lua.org/manual/5.4/manual.html#pdf-require
		sandbox_lua_os_library();
		sandbox_lua_loads(scripts_folder);

		lua::log::bind(m_state);
		lua::globals::bind(m_state);
		lua::script::bind(m_state);
		lua::native::bind(m_state);
		lua::memory::bind(m_state);
		lua::gui::bind(m_state);
		lua::network::bind(m_state);
		lua::command::bind(m_state);
		lua::tunables::bind(m_state);
		lua::locals::bind(m_state);
		lua::event::bind(m_state);
		lua::vector::bind(m_state);
		lua::global_table::bind(m_state);
		lua::imgui::bind(m_state, m_state.globals());
		lua::entities::bind(m_state);
		lua::stats::bind(m_state);
	}

	void lua_module::load_and_call_script()
	{
		auto result = m_state.safe_script_file(m_module_path.string(), &sol::script_pass_on_error, sol::load_mode::text);

		if (!result.valid())
		{
			LOG(FATAL) << m_module_name << " failed to load: " << result.get<sol::error>().what();
			Logger::FlushQueue();
		}
		else
		{
			LOG(INFO) << "Loaded " << m_module_name;
		}
	}

	void lua_module::tick_scripts()
	{
		std::lock_guard guard(m_registered_scripts_mutex);

		for (auto& script : m_registered_scripts)
		{
			if (script->is_enabled())
			{
				script->tick();
			}
		}
	}

	void lua_module::cleanup_done_scripts()
	{
		std::lock_guard guard(m_registered_scripts_mutex);

		std::erase_if(m_registered_scripts, [](auto& script) {
			return script->is_done();
		});
	}
}