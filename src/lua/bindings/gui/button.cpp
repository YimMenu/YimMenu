#include "button.hpp"

#include "fiber_pool.hpp"

namespace lua::gui
{
	button::button(std::string text, sol::function callback) :
	    base_text_element(text),
	    m_callback(callback)
	{
	}

	void button::draw()
	{
		if (ImGui::Button(m_text.data()))
		{
			if (m_execute_in_fiber_pool)
			{
				big::g_fiber_pool->queue_job([this] {
					m_callback();
				});
			}
			else
				m_callback();
		}
	}
}