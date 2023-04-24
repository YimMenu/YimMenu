#include "lua_module.hpp"

#include "bindings/command.hpp"
#include "bindings/globals.hpp"
#include "bindings/gui.hpp"
#include "bindings/log.hpp"
#include "bindings/memory.hpp"
#include "bindings/native.hpp"
#include "bindings/network.hpp"
#include "bindings/script.hpp"
#include "file_manager.hpp"
#include "script_mgr.hpp"

namespace big
{
	inline int exception_handler(lua_State* L, std::optional<const void*>, std::string_view what)
	{
		LOG(FATAL) << what;
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

		lua::log::bind(m_state);
		lua::globals::bind(m_state);
		lua::script::bind(m_state);
		lua::native::bind(m_state);
		lua::memory::bind(m_state);
		lua::gui::bind(m_state);
		lua::network::bind(m_state);
		lua::command::bind(m_state);

		m_state["!module_name"] = module_name;
		m_state["!this"]        = this;
		m_state["joaat"]        = rage::joaat;

		m_state.set_exception_handler((sol::exception_handler_function)exception_handler);
		m_state.set_panic(panic_handler);

		auto result = m_state.load_file(g_file_manager->get_project_folder("scripts").get_file(module_name).get_path().string());

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

		m_registered_scripts.clear();
		m_registered_patches.clear();
	}

	rage::joaat_t lua_module::module_id()
	{
		return m_module_id;
	}

	const std::string& lua_module::module_name()
	{
		return m_module_name;
	}
}