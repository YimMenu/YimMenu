#include "gui/components/components.hpp"
#include "fonts/fonts.hpp"

namespace big
{
	void components::custom_text(const char* text, ImFont* font) {
		ImGui::PushFont(font);
		ImGui::TextWrapped(text);
		ImGui::PopFont();
	}
}