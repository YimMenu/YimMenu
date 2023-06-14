#pragma once
#include "base_text_element.hpp"

namespace lua::gui
{
	class input_int : public base_text_element
	{
		bool m_enabled = false;
		int m_value    = 0;

	public:
		input_int(std::string text);

		void draw() override;

		int get_value();
		void set_value(int val);
	};
}