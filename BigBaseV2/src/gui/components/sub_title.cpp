#include "gui/components/components.hpp"
#include "fonts/fonts.hpp"

namespace big
{
	void components::sub_title(const char* text) {
		components::custom_text(text, g->window.font_sub_title);
	}
}