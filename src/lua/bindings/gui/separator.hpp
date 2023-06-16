#pragma once
#include "gui_element.hpp"

namespace lua::gui
{
	class separator : public gui_element
	{
	public:
		separator(){};

		void draw() override;
	};
}