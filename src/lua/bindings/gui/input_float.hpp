#pragma once
#include "base_text_element.hpp"

namespace lua::gui
{
	// Lua API: Class
	// Name: input_float
	// Inherit: base_text_element
	// Class for representing an input field for editing a float value within the GUI.
	class input_float : public base_text_element
	{
		bool m_enabled = false;
		float m_value  = 0;

	public:
		input_float(std::string text);

		void draw() override;

		// Lua API: Function
		// Class: input_float
		// Name: get_value
		// Returns: float: Get the value currently written inside the input field.
		float get_value();

		// Lua API: Function
		// Class: input_float
		// Name: set_value
		// Param: val: float: Set the value currently written inside the input field.
		void set_value(float val);
	};
}