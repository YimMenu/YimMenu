#pragma once
#include "gui_element.hpp"

namespace lua::gui
{
	class sameline : public gui_element
	{
	public:
		sameline(){};

		void draw() override;
	};
}