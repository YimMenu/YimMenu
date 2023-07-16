#pragma once
#include "gui/button.hpp"
#include "gui/checkbox.hpp"
#include "gui/gui_element.hpp"
#include "gui/input_float.hpp"
#include "gui/input_int.hpp"
#include "gui/input_string.hpp"
#include "gui/sameline.hpp"
#include "gui/separator.hpp"
#include "gui/text.hpp"
#include "lua/lua_module.hpp"
#include "services/gui/gui_service.hpp"

namespace lua::gui
{
	static void add_element(lua_State* state, std::uint32_t hash, std::shared_ptr<lua::gui::gui_element> element)
	{
		auto module = sol::state_view(state)["!this"].get<big::lua_module*>();

		if (!module->m_gui.contains(hash))
			module->m_gui[hash] = {};

		module->m_gui[hash].push_back(std::move(element));
	}

	// Lua API: Class
	// Name: tab
	// Class for representing a tab within the GUI.
	class tab
	{
		big::tabs m_id;
		rage::joaat_t m_tab_hash;

	public:
		inline big::tabs id() const
		{
			return m_id;
		}

		inline rage::joaat_t hash() const
		{
			return m_tab_hash;
		}

		bool check_if_existing_tab_and_fill_id(const std::map<big::tabs, big::navigation_struct>& nav)
		{
			for (const auto& nav_item : nav)
			{
				if (nav_item.second.hash == m_tab_hash)
				{
					m_id = nav_item.first;
					return true;
				}
				
				if (check_if_existing_tab_and_fill_id(nav_item.second.sub_nav))
				{
					return true;
				}
			}

			return false;
		}

		static void add_to_existing_tab(std::map<big::tabs, big::navigation_struct>& nav, const rage::joaat_t existing_tab_hash, const std::pair<big::tabs, big::navigation_struct>& new_tab, const sol::this_state& state)
		{
			for (auto& nav_item : nav)
			{
				if (nav_item.second.hash == existing_tab_hash)
				{
					auto module = sol::state_view(state)["!this"].get<big::lua_module*>();
					module->m_tab_to_sub_tabs[nav_item.first].push_back(new_tab.first);

					nav_item.second.sub_nav.emplace(new_tab);
					return;
				}

				add_to_existing_tab(nav_item.second.sub_nav, existing_tab_hash, new_tab, state);
			}
		}

		std::pair<big::tabs, big::navigation_struct> make_tab_nav(const std::string& name, const rage::joaat_t tab_hash, const sol::this_state& state)
		{
			static size_t custom_tab_count = size_t(big::tabs::RUNTIME_CUSTOM);
			m_id = big::tabs(custom_tab_count);

			custom_tab_count++;

			big::navigation_struct new_navigation_struct{};
			strcpy(new_navigation_struct.name, name.c_str());
			new_navigation_struct.hash = tab_hash;

			return std::make_pair(m_id, new_navigation_struct);
		}

		tab(const std::string& name, const sol::this_state& state) :
		    m_tab_hash(rage::joaat(name))
		{
			auto& nav = big::g_gui_service->get_navigation();

			if (check_if_existing_tab_and_fill_id(nav))
			{
				return;
			}

			// add top tab
			nav.emplace(make_tab_nav(name, m_tab_hash, state));

			auto module = sol::state_view(state)["!this"].get<big::lua_module*>();
			module->m_owned_tabs.push_back(id());
		}

		tab(const std::string& name, const rage::joaat_t parent_tab_hash, const sol::this_state& state) :
		    m_tab_hash(rage::joaat(name))
		{
			auto& nav = big::g_gui_service->get_navigation();

			if (check_if_existing_tab_and_fill_id(nav))
			{
				return;
			}

			const auto sub_tab = make_tab_nav(name, m_tab_hash, state);
			add_to_existing_tab(nav, parent_tab_hash, sub_tab, state);

			auto module = sol::state_view(state)["!this"].get<big::lua_module*>();
			module->m_owned_tabs.push_back(id());
		}

		// Lua API: Function
		// Class: tab
		// Name: clear
		// Clear the tab of all its custom lua content that you own.
		void clear(sol::this_state state)
		{
			auto module = sol::state_view(state)["!this"].get<big::lua_module*>();

			if (module->m_gui.contains(m_tab_hash))
				module->m_gui[m_tab_hash] = {};

			for (auto sub_tab : module->m_tab_to_sub_tabs[id()])
			{
				for (const auto owned_tab : module->m_owned_tabs)
				{
					if (sub_tab == owned_tab)
					{
						big::g_gui_service->remove_from_nav(sub_tab);
					}
				}
			}
		}

		// Lua API: Function
		// Class: tab
		// Name: add_tab
		// Add a sub tab to this tab.
		tab add_tab(const std::string& name, sol::this_state state)
		{
			const auto sub_tab = tab(name, m_tab_hash, state);

			return sub_tab;
		}

		// Lua API: Function
		// Class: tab
		// Name: add_button
		// Param: name: string: Text written inside the button.
		// Param: callback: function: function that will be called when the button is clicked.
		// Add a button to the gui tab.
		std::shared_ptr<lua::gui::button> add_button(const std::string& name, sol::protected_function callback, sol::this_state state)
		{
			auto element = std::make_shared<lua::gui::button>(name, callback);
			add_element(state, m_tab_hash, element);
			return element;
		}

		// Lua API: Function
		// Class: tab
		// Name: add_text
		// Param: name: string: Text that will be written.
		// Returns: text: The text object instance.
		// Add text to the gui tab.
		std::shared_ptr<lua::gui::text> add_text(const std::string& name, sol::this_state state)
		{
			auto element = std::make_shared<lua::gui::text>(name);
			add_element(state, m_tab_hash, element);
			return element;
		}

		// Lua API: Function
		// Class: tab
		// Name: add_checkbox
		// Param: name: string: Text that will be written next to the checkbox.
		// Returns: checkbox: The checkbox object instance.
		// Add a checkbox widget to the gui tab.
		std::shared_ptr<lua::gui::checkbox> add_checkbox(const std::string& name, sol::this_state state)
		{
			auto element = std::make_shared<lua::gui::checkbox>(name);
			add_element(state, m_tab_hash, element);
			return element;
		}

		// Lua API: Function
		// Class: tab
		// Name: add_sameline
		// Returns: sameline: The sameline object instance.
		// Add a ImGui::SameLine.
		std::shared_ptr<lua::gui::sameline> add_sameline(sol::this_state state)
		{
			auto element = std::make_shared<lua::gui::sameline>();
			add_element(state, m_tab_hash, element);
			return element;
		}

		// Lua API: Function
		// Class: tab
		// Name: add_separator
		// Returns: separator: The separator object instance.
		// Add a ImGui::Separator.
		std::shared_ptr<lua::gui::separator> add_separator(sol::this_state state)
		{
			auto element = std::make_shared<lua::gui::separator>();
			add_element(state, m_tab_hash, element);
			return element;
		}

		// Lua API: Function
		// Class: tab
		// Name: add_input_int
		// Param: name: string: Text that will be written next to the input field.
		// Returns: input_int: The input_int object instance.
		// Add a ImGui::InputInt.
		std::shared_ptr<lua::gui::input_int> add_input_int(const std::string& name, sol::this_state state)
		{
			auto element = std::make_shared<lua::gui::input_int>(name);
			add_element(state, m_tab_hash, element);
			return element;
		}

		// Lua API: Function
		// Class: tab
		// Name: add_input_float
		// Param: name: string: Text that will be written next to the input field.
		// Returns: input_float: The input_float object instance.
		// Add a ImGui::InputFloat.
		std::shared_ptr<lua::gui::input_float> add_input_float(const std::string& name, sol::this_state state)
		{
			auto element = std::make_shared<lua::gui::input_float>(name);
			add_element(state, m_tab_hash, element);
			return element;
		}

		// Lua API: Function
		// Class: tab
		// Name: add_input_string
		// Param: name: string: Text that will be written next to the input field.
		// Returns: input_string: The input_string object instance.
		// Add a ImGui::InputText.
		std::shared_ptr<lua::gui::input_string> add_input_string(const std::string& name, sol::this_state state)
		{
			auto element = std::make_shared<lua::gui::input_string>(name);
			add_element(state, m_tab_hash, element);
			return element;
		}
	};

	// Lua API: Table
	// Name: gui
	// Table containing functions for modifying the menu GUI.

	// Lua API: Function
	// Table: gui
	// Name: get_tab
	// Param: tab_name: string: Name of the tab to get.
	// Returns: tab: A tab instance which corresponds to the tab in the GUI.
	static tab get_tab(const std::string& tab_name, sol::this_state state)
	{
		return tab(tab_name, state);
	}

	// Lua API: Function
	// Table: gui
	// Name: add_tab
	// Param: tab_name: string: Name of the tab to add.
	// Returns: tab: A tab instance which corresponds to the new tab in the GUI.
	static tab add_tab(const std::string& tab_name, sol::this_state state)
	{
		const auto new_tab = tab(tab_name, state);

		return new_tab;
	}

	// Lua API: Function
	// Table: gui
	// Name: show_message
	// Param: title: string
	// Param: message: string
	// Shows a message to the user with the given title and message.
	static void show_message(const std::string& title, const std::string& message)
	{
		big::g_notification_service->push(title, message);
	}

	// Lua API: Function
	// Table: gui
	// Name: show_warning
	// Param: title: string
	// Param: message: string
	// Shows a warning to the user with the given title and message.
	static void show_warning(const std::string& title, const std::string& message)
	{
		big::g_notification_service->push_warning(title, message);
	}

	// Lua API: Function
	// Table: gui
	// Name: show_error
	// Param: title: string
	// Param: message: string
	// Shows an error to the user with the given title and message.
	static void show_error(const std::string& title, const std::string& message)
	{
		big::g_notification_service->push_error(title, message);
	}

	// Lua API: Function
	// Table: gui
	// Name: is_open
	// Returns: bool: Returns true if the GUI is open.
	bool is_open();

	static void bind(sol::state& state)
	{
		auto ns            = state["gui"].get_or_create<sol::table>();
		ns["get_tab"]      = get_tab;
		ns["add_tab"]      = add_tab;
		ns["show_message"] = show_message;
		ns["show_warning"] = show_warning;
		ns["show_error"]   = show_error;
		ns["is_open"]      = is_open;

		// clang-format off
		ns.new_usertype<lua::gui::button>("button",
			"set_text", &lua::gui::button::set_text,
			"get_text", &lua::gui::button::get_text
		);

		ns.new_usertype<lua::gui::text>("text",
			"set_text", &lua::gui::text::set_text,
			"get_text", &lua::gui::text::get_text,
			"set_font", &lua::gui::text::set_font
		);

		ns.new_usertype<lua::gui::checkbox>("checkbox",
			"set_text", &lua::gui::checkbox::set_text,
			"get_text", &lua::gui::checkbox::get_text,
			"is_enabled", &lua::gui::checkbox::is_enabled,
			"set_enabled", &lua::gui::checkbox::set_enabled
		);

		ns.new_usertype<lua::gui::sameline>("sameline");
		ns.new_usertype<lua::gui::separator>("separator");

		ns.new_usertype<lua::gui::input_int>("input_int",
			"set_text", &lua::gui::input_int::set_text,
			"get_text", &lua::gui::input_int::get_text,
			"get_value", &lua::gui::input_int::get_value,
			"set_value", &lua::gui::input_int::set_value
		);

		ns.new_usertype<lua::gui::input_float>("input_float",
			"set_text", &lua::gui::input_float::set_text,
			"get_text", &lua::gui::input_float::get_text,
			"get_value", &lua::gui::input_float::get_value,
			"set_value", &lua::gui::input_float::set_value
		);

		ns.new_usertype<lua::gui::input_string>("input_string",
			"set_text", &lua::gui::input_string::set_text,
			"get_text", &lua::gui::input_string::get_text,
			"get_value", &lua::gui::input_string::get_value,
			"set_value", &lua::gui::input_string::set_value
		);

		ns.new_usertype<tab>("tab",
			"clear", &tab::clear,
			"add_tab", &tab::add_tab,
			"add_button", &tab::add_button,
			"add_text", &tab::add_text,
			"add_checkbox", &tab::add_checkbox,
			"add_sameline", &tab::add_sameline,
			"add_separator", &tab::add_separator,
			"add_input_int", &tab::add_input_int,
			"add_input_float", &tab::add_input_float,
			"add_input_string", &tab::add_input_string
		);
		// clang-format on
	}
}