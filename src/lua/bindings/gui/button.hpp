#pragma once
#include "base_text_element.hpp"
#include "lua/sol.hpp"

namespace lua::gui
{
	class button : public base_text_element
	{
		sol::function m_callback;
		bool m_execute_in_fiber_pool = true;

	public:
		button(std::string text, sol::function callback);

		void draw() override;
	};
}