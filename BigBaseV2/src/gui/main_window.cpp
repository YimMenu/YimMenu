#include "common.hpp"
#include "gui.hpp"
#include "imgui.h"
#include "tab_bar/tab_bar.hpp"

namespace big
{
	void gui::render_main_window()
	{
		if (ImGui::Begin("Yimura's Mod Menu"))
		{
			ImGui::BeginTabBar("tabbar");
			tabbar::render_self();
			tabbar::render_tunables();
			tabbar::render_teleport();
			tabbar::render_vehicle();
			tabbar::render_network();
			ImGui::EndTabBar();
		}
		ImGui::End();
	}
}