#include "fonts/fonts.hpp"
#include "gui/components/components.hpp"
#include "core/settings/window.hpp"

namespace big
{
	void components::sub_title(const std::string_view text)
	{
		components::custom_text(text.data(), g_window.font_sub_title);
	}
}