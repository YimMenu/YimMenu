#include "input_float.hpp"

namespace lua::gui
{
	input_float::input_float(std::string text) :
	    base_text_element(text)
	{
	}

	void input_float::draw()
	{
		ImGui::InputFloat(m_text.c_str(), &m_value);
	}

	float input_float::get_value()
	{
		return m_value;
	}

	void input_float::set_value(float val)
	{
		m_value = val;
	}
}