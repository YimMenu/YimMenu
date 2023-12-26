#include "input_int.hpp"

namespace lua::gui
{
	input_int::input_int(std::string text) :
	    base_text_element(text)
	{
	}

	void input_int::draw()
	{
		ImGui::InputInt(m_text.c_str(), &m_value);
	}

	int input_int::get_value()
	{
		return m_value;
	}

	void input_int::set_value(int val)
	{
		m_value = val;
	}
}