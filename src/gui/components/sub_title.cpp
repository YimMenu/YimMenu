#include "gui/components/components.hpp"

namespace big
{
	void components::sub_title(const std::string_view text)
	{
		components::custom_text(text.data(), g.window.font_sub_title);
	}
}