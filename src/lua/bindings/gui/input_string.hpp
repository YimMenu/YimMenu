#pragma once
#include "base_text_element.hpp"

namespace lua::gui
{
	// Lua API: Class
	// Name: input_string
	// Inherit: base_text_element
	// Class for representing an input field for editing a string value within the GUI.
	class input_string : public base_text_element
	{
		bool m_enabled    = false;
		char m_value[255] = {};

	public:
		input_string(std::string text);

		void draw() override;

		// Lua API: Function
		// Class: input_string
		// Name: get_value
		// Returns: string: Get the value currently written inside the input field.
		std::string get_value();

		// Lua API: Function
		// Class: input_string
		// Name: set_value
		// Param: val: string: Set the value currently written inside the input field.
		void set_value(std::string val);
	};
}