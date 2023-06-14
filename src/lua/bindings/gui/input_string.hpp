#pragma once
#include "base_text_element.hpp"

namespace lua::gui
{
	class input_string : public base_text_element
	{
		bool m_enabled    = false;
		char m_value[255] = {};

	public:
		input_string(std::string text);

		void draw() override;

		std::string get_value();
		void set_value(std::string val);
	};
}