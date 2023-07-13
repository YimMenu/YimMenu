#include "lua_module.hpp"

#include "bindings/command.hpp"
#include "bindings/event.hpp"
#include "bindings/globals.hpp"
#include "bindings/gui.hpp"
#include "bindings/locals.hpp"
#include "bindings/log.hpp"
#include "bindings/memory.hpp"
#include "bindings/native.hpp"
#include "bindings/network.hpp"
#include "bindings/script.hpp"
#include "bindings/tunables.hpp"
#include "bindings/vector.hpp"
#include "bindings/global_table.hpp"
#include "file_manager.hpp"
#include "script_mgr.hpp"

namespace big
{
	inline int exception_handler(lua_State* L, sol::optional<const std::exception&> exception, std::string_view what)
	{
		if (exception)
			LOG(WARNING) << exception->what();
		else
			LOG(WARNING) << what;

		lua_pushlstring(L, what.data(), what.size());
		return 1;
	}

	inline int panic_handler(lua_State* L)
	{
		size_t messagesize;
		const char* message = lua_tolstring(L, -1, &messagesize);
		if (message)
		{
			std::string err(message, messagesize);
			lua_settop(L, 0);
			LOG(FATAL) << err;
		}
		lua_settop(L, 0);
		LOG(FATAL) << "An unexpected error occurred and panic has been invoked";
		return 1;
	}

	lua_module::lua_module(std::string module_name) :
	    m_module_name(module_name),
	    m_module_id(rage::joaat(module_name))
	{
		m_state = std::make_unique<sol::state>();

		auto& state = *m_state;

		state.open_libraries(
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

		init_lua_api();

		state["!module_name"] = module_name;
		state["!this"]        = this;

		state.set_exception_handler((sol::exception_handler_function)exception_handler);
		state.set_panic(panic_handler);

		const auto script_file_path = g_lua_manager->get_scripts_folder().get_file(module_name).get_path();
		m_last_write_time           = std::filesystem::last_write_time(script_file_path);
		auto result                 = state.load_file(script_file_path.string());

		if (!result.valid())
		{
			LOG(WARNING) << module_name << " failed to load: " << result.get<sol::error>().what();
		}
		else
		{
			result();
		}
	}

	lua_module::~lua_module()
	{
		for (const auto owned_tab : m_owned_tabs)
		{
			big::g_gui_service->remove_from_nav(owned_tab);
		}

		for (auto script : m_registered_scripts)
		{
			g_script_mgr.remove_script(script);
		}

		// the lua state is about to be destroyed,
		// but we need to keep it around a little bit longer
		// until the script manager properly finish executing any potential lua script.
		// There are most likely much better ways of doing all this, feel free to refactor I guess.
		std::shared_ptr<sol::state> lua_state_shared = std::shared_ptr<sol::state>(std::move(m_state));
		g_script_mgr.add_on_script_batch_removed([lua_state_shared] {
		});

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

	const std::chrono::time_point<std::chrono::file_clock> lua_module::last_write_time() const
	{
		return m_last_write_time;
	}

	void lua_module::set_folder_for_lua_require()
	{
		auto& state = *m_state;

		const auto scripts_search_path = g_lua_manager->get_scripts_folder().get_path() / "?.lua";
		state["package"]["path"]       = scripts_search_path.string();
	}

	void lua_module::sandbox_lua_os_library()
	{
		auto& state = *m_state;

		const auto& os = state["os"];
		sol::table sandbox_os(state, sol::create);

		sandbox_os["clock"]     = os["clock"];
		sandbox_os["date"]      = os["date"];
		sandbox_os["difftime"]	= os["difftime"];
		sandbox_os["time"]      = os["time"];

		state["os"] = sandbox_os;
	}

	void lua_module::sandbox_lua_loads()
	{
		auto& state = *m_state;

		// That's from lua base lib, luaB
		state.set_function("load", nullptr);
		state.set_function("loadstring", nullptr);
		state.set_function("loadfile", nullptr);
		state.set_function("dofile", nullptr);

		// That's from lua package lib.
		// We only allow dependencies between .lua files, no DLLs.
		state["package"]["loadlib"] = nullptr;
		state["package"]["cpath"]   = "";

		// 1                   2               3            4
		// {searcher_preload, searcher_Lua, searcher_C, searcher_Croot, NULL};
		state["package"]["searchers"][3]   = nullptr;
		state["package"]["searchers"][4] = nullptr;

		set_folder_for_lua_require();
	}

	void lua_module::init_lua_api()
	{
		auto& state = *m_state;

		// https://blog.rubenwardy.com/2020/07/26/sol3-script-sandbox/
		// https://www.lua.org/manual/5.4/manual.html#pdf-require
		sandbox_lua_os_library();
		sandbox_lua_loads();

		lua::log::bind(state);
		lua::globals::bind(state);
		lua::script::bind(state);
		lua::native::bind(state);
		lua::memory::bind(state);
		lua::gui::bind(state);
		lua::network::bind(state);
		lua::command::bind(state);
		lua::tunables::bind(state);
		lua::locals::bind(state);
		lua::event::bind(state);
		lua::vector::bind(state);
		lua::global_table::bind(state);
	}
}