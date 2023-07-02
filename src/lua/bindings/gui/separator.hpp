#pragma once
#include "gui_element.hpp"

namespace lua::gui
{
	// Lua API: Class
	// Name: separator
	// Class for ImGui::Separator() - separator, generally horizontal. Inside a menu bar or in horizontal layout mode, this becomes a vertical separator.
	class separator : public gui_element
	{
	public:
		separator(){};

		void draw() override;
	};
}