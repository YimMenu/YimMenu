#pragma once
#include "gui_element.hpp"

namespace lua::gui
{
	// Lua API: Class
	// Name: sameline
	// Class for ImGui::SameLine() - Puts a sameline between widgets or groups to layout them horizontally.
	class sameline : public gui_element
	{
	public:
		sameline(){};

		void draw() override;
	};
}