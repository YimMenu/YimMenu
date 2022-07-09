#include "components.hpp"
#include "services/gui/gui_service.hpp"

namespace big
{
	void components::nav_item(std::pair<tabs, navigation_struct>& navItem, int nested)
	{
		const bool curTab = !g_gui_service->get_selected_tab().empty() && g_gui_service->get_selected_tab().size() > nested && navItem.first == g_gui_service->get_selected_tab().at(nested);
		if (curTab)
			ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.29f, 0.45f, 0.69f, 1.f));

		if (components::nav_button(navItem.second.name))
			g_gui_service->set_selected(navItem.first);

		if (curTab)
			ImGui::PopStyleColor();

		if (curTab && !navItem.second.sub_nav.empty())
		{
			ImDrawList* dl = ImGui::GetForegroundDrawList();
			
			for (std::pair<tabs, navigation_struct> item : navItem.second.sub_nav)
			{
				nav_item(item, nested + 1);
			}
		}

		g_gui_service->increment_nav_size();
	}
}
