#pragma once
#include "gui_element.hpp"

namespace lua::gui
{
	// Lua API: Class
	// Name: base_text_element
	// Class representing a gui text element.

	class base_text_element : public gui_element
	{
	protected:
		std::string m_text;

	public:
		base_text_element(std::string text);

		// Lua API: Function
		// Class: base_text_element
		// Name: set_text
		// Param: new_text: string: The new text for that gui text element.
		void set_text(std::string new_text);

		// Lua API: Function
		// Class: base_text_element
		// Name: get_text
		// Returns: string: Returns the current text for that gui text element.
		std::string get_text();
	};
}