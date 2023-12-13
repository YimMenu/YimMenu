#include "base_text_element.hpp"

namespace lua::gui
{
	base_text_element::base_text_element(std::string text) :
	    m_text(text)
	{
	}

	void base_text_element::set_text(std::string new_text)
	{
		m_text = new_text;
	}

	std::string base_text_element::get_text()
	{
		return m_text;
	}
}