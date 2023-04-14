#include "services/gui/gui_service.hpp"
#include "views/view.hpp"

namespace big
{
	void view::navigation()
	{
		ImGui::SetNextWindowPos({10.f, 100.f * g.window.gui_scale}, ImGuiCond_Always);
		ImGui::SetNextWindowSize({300.f * g.window.gui_scale, 0.f}, ImGuiCond_Always);

		if (ImGui::Begin("navigation", 0, window_flags))
		{
			g_gui_service->reset_nav_size();
			for (std::pair<tabs, navigation_struct> navItem : g_gui_service->get_navigation())
			{
				switch (navItem.first)
				{
				case tabs::PLAYER:
				case tabs::DEBUG: continue;
				default: components::nav_item(navItem, 0);
				}
			}
		}
		ImGui::End();
	}
}
