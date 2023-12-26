#include "button.hpp"

#include "fiber_pool.hpp"
#include "lua/lua_manager.hpp"

namespace lua::gui
{
	button::button(std::string text, sol::protected_function callback) :
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
					auto res = m_callback();
					if (!res.valid())
						big::g_lua_manager->handle_error(res, res.lua_state());
				});
			}
			else
			{
				auto res = m_callback();
				if (!res.valid())
					big::g_lua_manager->handle_error(res, res.lua_state());
			}
		}
	}
}