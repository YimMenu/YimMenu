#include "services/gui_service.hpp"
#include "views/view.hpp"
#include "services/player_service.hpp"

namespace big
{
	void view::navigation() {

		if (ImGui::Begin("navigation", 0))
		{
			for (std::pair<tabs, navigation_struct> navItem : g_gui_service->get_navigation()) {
				if (navItem.first == tabs::PLAYER) continue;
				components::nav_item(navItem, 0);
			}

			ImGui::End();
		}
	}
}