#pragma once
#include "gui_element.hpp"

namespace lua::gui
{
	// Lua API: Class
	// Name: raw_imgui_callback
	// Inherit: gui_element
	// Class for representing a raw imgui callback.
	class raw_imgui_callback : public gui_element
	{
		sol::protected_function m_callback;

	public:
		raw_imgui_callback(sol::protected_function callback);

		void draw() override;
	};
}