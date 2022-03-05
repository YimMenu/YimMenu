#include "gui/components/components.hpp"
#include "fonts/fonts.hpp"

namespace big
{
	void components::custom_text(const std::string_view text, ImFont* font) {
		ImGui::PushFont(font);
		ImGui::TextWrapped(text.data());
		ImGui::PopFont();
	}
}