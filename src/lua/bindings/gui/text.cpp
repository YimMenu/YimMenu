#include "text.hpp"

namespace lua::gui
{
	text::text(std::string text) :
	    base_text_element(text)
	{
	}

	void text::draw()
	{
		if (m_font)
			ImGui::PushFont(m_font);
		ImGui::Text(m_text.data());
		if (m_font)
			ImGui::PopFont();
	}

	void text::set_font(std::string font)
	{
		auto hash = rage::joaat(font);

		switch (hash)
		{
		case RAGE_JOAAT("title"): m_font = big::g.window.font_title; break;
		case RAGE_JOAAT("subtitle"): m_font = big::g.window.font_sub_title; break;
		case RAGE_JOAAT("small"): m_font = big::g.window.font_small; break;
		case RAGE_JOAAT("icon"): m_font = big::g.window.font_icon; break;
		default: m_font = nullptr; break;
		}
	}
}