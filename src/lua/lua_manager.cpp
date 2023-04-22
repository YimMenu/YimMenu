#include "lua_manager.hpp"

#include "file_manager.hpp"

namespace big
{
	lua_manager::lua_manager()
	{
		for (const auto& entry : std::filesystem::directory_iterator(g_file_manager->get_project_folder("scripts").get_path()))
			if (entry.is_regular_file())
				if (entry.path().filename().string() != "natives.lua")
					m_modules.push_back(std::make_shared<lua_module>(entry.path().filename().string()));

		g_lua_manager = this;
	}

	lua_manager::~lua_manager()
	{
		g_lua_manager = nullptr;
	}
}