#include "gui/components/components.hpp"
#include "fonts/fonts.hpp"

namespace big
{
	void components::icon(const std::string_view text) {
		components::custom_text(text.data(), g.window.font_icon);
	}
}