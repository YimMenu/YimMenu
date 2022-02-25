#include "gui/components/components.hpp"
#include "fonts/fonts.hpp"

namespace big
{
	void components::title(const char* text) {
		components::custom_text(text, g->window.font_title);
	}
}