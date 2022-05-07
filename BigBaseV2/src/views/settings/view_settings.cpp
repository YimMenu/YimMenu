#include "views/view.hpp"
#include "widgets/imgui_hotkey.hpp"

namespace big
{
	void view::settings() {
		components::small_text("Hotkeys");

		ImGui::PushItemWidth(350.f);

		if (ImGui::Hotkey("Menu Toggle", &g->settings.hotkeys.menu_toggle))
			g->settings.hotkeys.editing_menu_toggle = true; // make our menu reappear

		ImGui::Text("(Below hotkey is not implemented)");
		ImGui::Hotkey("Teleport to waypoint", &g->settings.hotkeys.teleport_waypoint);

		ImGui::PopItemWidth();
	}
}