#include "input_string.hpp"

namespace lua::gui
{
	input_string::input_string(std::string text) :
	    base_text_element(text)
	{
	}

	void input_string::draw()
	{
		ImGui::InputText(m_text.c_str(), m_value, sizeof(m_value));
	}

	std::string input_string::get_value()
	{
		return m_value;
	}

	void input_string::set_value(std::string val)
	{
		strncpy(m_value, val.c_str(), sizeof(m_value));
	}
}