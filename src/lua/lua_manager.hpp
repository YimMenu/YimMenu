#pragma once
#include "lua_module.hpp"

namespace big
{
	class lua_manager
	{
	public:
		lua_manager();
		~lua_manager();

		void draw_gui(rage::joaat_t tab_hash);
		void unload_module(rage::joaat_t module_id);
		void load_module(const std::string& module_name);
		std::weak_ptr<lua_module> get_module(rage::joaat_t module_id);
		const std::vector<std::shared_ptr<lua_module>>& get_modules();
		void reload_all_modules();

	private:
		void load_all_modules();
		void unload_all_modules();

		std::vector<std::shared_ptr<lua_module>> m_modules;
	};

	inline lua_manager* g_lua_manager;
}