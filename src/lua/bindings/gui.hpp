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

namespace lua::gui
{
	static void add_element(lua_State* state, std::uint32_t hash, std::shared_ptr<lua::gui::gui_element> element)
	{
		auto module = sol::state_view(state)["!this"].get<big::lua_module*>();

		if (!module->m_gui.contains(hash))
			module->m_gui[hash] = {};

		module->m_gui[hash].push_back(std::move(element));
	}

	class tab
	{
		rage::joaat_t m_tab_hash;

	public:
		tab(rage::joaat_t hash) :
		    m_tab_hash(hash)
		{
		}

		std::shared_ptr<lua::gui::button> add_button(const std::string& name, sol::function callback, sol::this_state state)
		{
			auto element = std::make_shared<lua::gui::button>(name, callback);
			add_element(state, m_tab_hash, element);
			return element;
		}

		std::shared_ptr<lua::gui::text> add_text(const std::string& name, sol::this_state state)
		{
			auto element = std::make_shared<lua::gui::text>(name);
			add_element(state, m_tab_hash, element);
			return element;
		}

		std::shared_ptr<lua::gui::checkbox> add_checkbox(const std::string& name, sol::this_state state)
		{
			auto element = std::make_shared<lua::gui::checkbox>(name);
			add_element(state, m_tab_hash, element);
			return element;
		}

		std::shared_ptr<lua::gui::sameline> add_sameline(sol::this_state state)
		{
			auto element = std::make_shared<lua::gui::sameline>();
			add_element(state, m_tab_hash, element);
			return element;
		}

		std::shared_ptr<lua::gui::separator> add_separator(sol::this_state state)
		{
			auto element = std::make_shared<lua::gui::separator>();
			add_element(state, m_tab_hash, element);
			return element;
		}

		std::shared_ptr<lua::gui::input_int> add_input_int(const std::string& name, sol::this_state state)
		{
			auto element = std::make_shared<lua::gui::input_int>(name);
			add_element(state, m_tab_hash, element);
			return element;
		}

		std::shared_ptr<lua::gui::input_float> add_input_float(const std::string& name, sol::this_state state)
		{
			auto element = std::make_shared<lua::gui::input_float>(name);
			add_element(state, m_tab_hash, element);
			return element;
		}

		std::shared_ptr<lua::gui::input_string> add_input_string(const std::string& name, sol::this_state state)
		{
			auto element = std::make_shared<lua::gui::input_string>(name);
			add_element(state, m_tab_hash, element);
			return element;
		}
	};

	static tab get_tab(const std::string& tab_name)
	{
		return tab(rage::joaat(tab_name));
	}

	static void show_message(const std::string& title, const std::string& message)
	{
		big::g_notification_service->push(title, message);
	}

	static void show_warning(const std::string& title, const std::string& message)
	{
		big::g_notification_service->push_warning(title, message);
	}

	static void show_error(const std::string& title, const std::string& message)
	{
		big::g_notification_service->push_error(title, message);
	}

	bool is_open();

	static void bind(sol::state& state)
	{
		auto ns            = state["gui"].get_or_create<sol::table>();
		ns["get_tab"]      = get_tab;
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