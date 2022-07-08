#include "services/gui/gui_service.hpp"
#include "views/view.hpp"

namespace big
{
	void view::navigation() {

		if (ImGui::Begin("navigation", 0))
		{
			g_gui_service->reset_nav_size();
			for (std::pair<tabs, navigation_struct> navItem : g_gui_service->get_navigation()) {
				if (navItem.first == tabs::PLAYER) continue;
				components::nav_item(navItem, 0);
			}

			ImGui::End();
		}
	}
}
