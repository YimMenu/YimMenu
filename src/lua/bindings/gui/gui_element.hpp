#pragma once

namespace lua::gui
{
	class gui_element
	{
	public:
		virtual void draw() = 0;
	};
}