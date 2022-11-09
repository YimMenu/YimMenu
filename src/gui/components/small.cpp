#include "gui/components/components.hpp"
#include "fonts/fonts.hpp"

namespace big
{
	void components::small_text(const std::string_view text) {
		components::custom_text(text.data(), g->window.font_small);
	}
}