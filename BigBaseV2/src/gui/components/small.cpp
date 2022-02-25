#include "gui/components/components.hpp"
#include "fonts/fonts.hpp"

namespace big
{
	void components::small_text(const char* text) {
		components::custom_text(text, g->window.font_small);
	}
}