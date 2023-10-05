#include "fonts/fonts.hpp"
#include "gui/components/components.hpp"
#include "core/settings.hpp"

namespace big
{
	void components::title(const std::string_view text)
	{
		components::custom_text(text.data(), g.window.font_title);
	}
}