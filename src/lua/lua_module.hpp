#pragma once
#include "lua_patch.hpp"
#include "sol.hpp"

namespace big
{
	class script;

	class lua_module
	{
		sol::state m_state;
		std::string m_module_name;

	public:
		std::vector<script*> m_registered_scripts;
		std::vector<std::shared_ptr<lua_patch>> m_registered_patches;

		lua_module(std::string module_name);
		~lua_module();
	};
}