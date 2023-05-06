#pragma once
#include "bindings/gui/gui_element.hpp"
#include "lua_patch.hpp"
#include "sol.hpp"

namespace big
{
	class script;

	class lua_module
	{
		sol::state m_state;
		std::string m_module_name;
		rage::joaat_t m_module_id;

	public:
		std::vector<script*> m_registered_scripts;
		std::vector<std::shared_ptr<lua_patch>> m_registered_patches;
		std::unordered_map<rage::joaat_t, std::vector<std::shared_ptr<lua::gui::gui_element>>> m_gui;
		std::unordered_map<rage::joaat_t, std::vector<sol::function>> m_event_callbacks;
		std::vector<void*> m_allocated_memory;

		lua_module(std::string module_name);
		~lua_module();
		rage::joaat_t module_id();
		const std::string& module_name();
	};
}