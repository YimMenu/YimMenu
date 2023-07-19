#pragma once
#include "base_text_element.hpp"

namespace lua::gui
{
	// Lua API: Class
	// Name: input_int
	// Inherit: base_text_element
	// Class for representing an input field for editing an integer value within the GUI.
	class input_int : public base_text_element
	{
		bool m_enabled = false;
		int m_value    = 0;

	public:
		input_int(std::string text);

		void draw() override;

		// Lua API: Function
		// Class: input_int
		// Name: get_value
		// Returns: integer: Get the value currently written inside the input field.
		int get_value();

		// Lua API: Function
		// Class: input_int
		// Name: set_value
		// Param: val: integer: Set the value currently written inside the input field.
		void set_value(int val);
	};
}