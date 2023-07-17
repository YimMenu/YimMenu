#include "lua_module.hpp"

#include "bindings/command.hpp"
#include "bindings/event.hpp"
#include "bindings/global_table.hpp"
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
#include "bindings/imgui.hpp"
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

	lua_module::lua_module(std::string module_name) :
	    m_module_name(module_name),
	    m_module_id(rage::joaat(module_name))
	{
		m_state = std::make_unique<sol::state>();

		auto& state = *m_state;

		// clang-format off
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
		// clang-format on

		init_lua_api();

		state["!module_name"] = module_name;
		state["!this"]        = this;

		state.set_exception_handler(exception_handler);
		state.set_panic(sol::c_call<decltype(&panic_handler), &panic_handler>);

		const auto script_file_path = g_lua_manager->get_scripts_folder().get_file(module_name).get_path();
		m_last_write_time           = std::filesystem::last_write_time(script_file_path);

		auto result = state.safe_script_file(script_file_path.string(), &sol::script_pass_on_error, sol::load_mode::text);

		if (!result.valid())
		{
			LOG(FATAL) << module_name << " failed to load: " << result.get<sol::error>().what();
			Logger::FlushQueue();
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

		sandbox_os["clock"]    = os["clock"];
		sandbox_os["date"]     = os["date"];
		sandbox_os["difftime"] = os["difftime"];
		sandbox_os["time"]     = os["time"];

		state["os"] = sandbox_os;
	}

	template<size_t N>
	static constexpr auto not_supported_lua_function(const char (&function_name)[N])
	{
		return [function_name](sol::this_state current_state, sol::variadic_args args) {
			const auto module = sol::state_view(current_state)["!this"].get<big::lua_module*>();

			LOG(FATAL) << module->module_name() << " tried calling a currently not supported lua function: " << function_name;
			Logger::FlushQueue();
		};
	}

	void lua_module::sandbox_lua_loads()
	{
		auto& state = *m_state;

		// That's from lua base lib, luaB
		state["load"]       = not_supported_lua_function("load");
		state["loadstring"] = not_supported_lua_function("loadstring");
		state["loadfile"]   = not_supported_lua_function("loadfile");
		state["dofile"]     = not_supported_lua_function("dofile");

		// That's from lua package lib.
		// We only allow dependencies between .lua files, no DLLs.
		state["package"]["loadlib"] = not_supported_lua_function("package.loadlib");
		state["package"]["cpath"]   = "";

		// 1                   2               3            4
		// {searcher_preload, searcher_Lua, searcher_C, searcher_Croot, NULL};
		state["package"]["searchers"][3] = not_supported_lua_function("package.searcher C");
		state["package"]["searchers"][4] = not_supported_lua_function("package.searcher Croot");

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
		lua::imgui::bind(state, state.globals());
	}
}