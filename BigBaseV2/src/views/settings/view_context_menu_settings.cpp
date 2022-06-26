#include "views/view.hpp"

namespace big
{
	void view::context_menu_settings()
	{
		ImGui::Checkbox("Context Menu Enabled", &g->context_menu.enabled);
	}
}
