#pragma once
#include "base_text_element.hpp"

namespace lua::gui
{
	// Lua API: Class
	// Name: checkbox
	// Inherit: base_text_element
	// Class representing a gui checkbox.
	class checkbox : public base_text_element
	{
		bool m_enabled = false;

	public:
		checkbox(std::string text);

		void draw() override;

		// Lua API: Function
		// Class: checkbox
		// Name: is_enabled
		// Returns: boolean: Is the checkbox checked?
		bool is_enabled();

		// Lua API: Function
		// Class: checkbox
		// Name: set_enabled
		// Param: enabled: boolean: The desired enabled state of the checkbox.
		void set_enabled(bool enabled);
	};
}