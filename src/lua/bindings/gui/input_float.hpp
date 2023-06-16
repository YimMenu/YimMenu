#pragma once
#include "base_text_element.hpp"

namespace lua::gui
{
	class input_float : public base_text_element
	{
		bool m_enabled = false;
		float m_value  = 0;

	public:
		input_float(std::string text);

		void draw() override;

		int get_value();
		void set_value(float val);
	};
}