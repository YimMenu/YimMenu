#include "raw_imgui_callback.hpp"

namespace lua::gui
{
	raw_imgui_callback::raw_imgui_callback(sol::protected_function callback) :
		m_callback(callback)
	{

	}

	void raw_imgui_callback::draw()
	{
		m_callback();
	}
}