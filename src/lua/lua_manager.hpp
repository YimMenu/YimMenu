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

	private:
		std::vector<std::shared_ptr<lua_module>> m_modules;
	};

	inline lua_manager* g_lua_manager;
}