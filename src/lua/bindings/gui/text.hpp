#pragma once
#include "base_text_element.hpp"
#include "lua/sol.hpp"

namespace lua::gui
{
	class text : public base_text_element
	{
		ImFont* m_font = nullptr;

	public:
		text(std::string text);

		void draw() override;
		void set_font(std::string font);
	};
}