#pragma once
#include "base_text_element.hpp"

namespace lua::gui
{
	class checkbox : public base_text_element
	{
		bool m_enabled = false;

	public:
		checkbox(std::string text);

		void draw() override;

		bool is_enabled();
		void set_enabled(bool enabled);
	};
}