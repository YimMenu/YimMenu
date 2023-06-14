#pragma once
#include "gui_element.hpp"

namespace lua::gui
{
	class base_text_element : public gui_element
	{
	protected:
		std::string m_text;

	public:
		base_text_element(std::string text);

		void set_text(std::string new_text);
		std::string get_text();
	};
}