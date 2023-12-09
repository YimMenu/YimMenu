#pragma once
#include "base_text_element.hpp"

namespace lua::gui
{
	// Lua API: Class
	// Name: text
	// Inherit: base_text_element
	// Class representing an imgui text element.
	class text : public base_text_element
	{
		ImFont* m_font = nullptr;

	public:
		text(std::string text);

		void draw() override;

		// Lua API: Function
		// Class: text
		// Name: set_font
		// Param: font: string: The new font name for that imgui text element.
		void set_font(std::string font);
	};
}