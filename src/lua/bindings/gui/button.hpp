#pragma once
#include "base_text_element.hpp"

namespace lua::gui
{
	// Lua API: Class
	// Name: button
	// Inherit: base_text_element
	// Class representing a gui button.
	// Refer to the tab class documentation for more info (tab:add_button(name, callback))
	class button : public base_text_element
	{
		sol::protected_function m_callback;
		bool m_execute_in_fiber_pool = true;

	public:
		button(std::string text, sol::protected_function callback);

		void draw() override;
	};
}