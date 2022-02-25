#include "gui/components/components.hpp"
#include "fonts/fonts.hpp"

namespace big
{
	void components::title(const char* text) {
		ImGui::PushFont(g->window.font_title);
		ImGui::Text(text);
		ImGui::PopFont();
	}
}