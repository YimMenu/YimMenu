#pragma once
#include "gui_element.hpp"

namespace lua::gui
{
	// Lua API: Class
	// Name: sameline
	// Class for ImGui::SameLine() - Puts a sameline between widgets or groups to layout them horizontally.
	// Refer to the tab class documentation for more info (tab:add_sameline())
	class sameline : public gui_element
	{
	public:
		sameline(){};

		void draw() override;
	};
}