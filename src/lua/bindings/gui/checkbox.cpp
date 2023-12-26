#include "checkbox.hpp"

namespace lua::gui
{
	checkbox::checkbox(std::string text) :
	    base_text_element(text)
	{
	}

	void checkbox::draw()
	{
		ImGui::Checkbox(m_text.data(), &m_enabled);
	}

	bool checkbox::is_enabled()
	{
		return m_enabled;
	}

	void checkbox::set_enabled(bool enabled)
	{
		m_enabled = enabled;
	}
}