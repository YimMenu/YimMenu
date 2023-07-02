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
	    m_state(),
	    m_module_name(module_name),
	    m_module_id(rage::joaat(module_name))
	{
		m_state.open_libraries();

		const auto scripts_folder = g_file_manager->get_project_folder("scripts");

		add_folder_to_require_available_paths(scripts_folder);

		init_lua_api();

		m_state["!module_name"] = module_name;
		m_state["!this"]        = this;

		m_state.set_exception_handler((sol::exception_handler_function)exception_handler);
		m_state.set_panic(panic_handler);

		const auto script_file_path = scripts_folder.get_file(module_name).get_path();
		m_last_write_time           = std::filesystem::last_write_time(script_file_path);
		auto result                 = m_state.load_file(script_file_path.string());

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
		for (auto script : m_registered_scripts)
			g_script_mgr.remove_script(script);

		for (auto& patch : m_registered_patches)
			patch.reset();

		for (auto memory : m_allocated_memory)
			delete[] memory;

		m_registered_scripts.clear();
		m_registered_patches.clear();
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

	void lua_module::add_folder_to_require_available_paths(const big::folder& scripts_folder)
	{
		const std::string package_path = m_state["package"]["path"];
		const auto scripts_search_path = scripts_folder.get_path() / "?.lua";
		m_state["package"]["path"] = package_path + (!package_path.empty() ? ";" : "") + scripts_search_path.string();
	}

	void lua_module::init_lua_api()
	{
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
	}
}