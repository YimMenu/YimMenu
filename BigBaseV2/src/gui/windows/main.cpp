#include "gui/window.hpp"
#include "gui/tab_bar.hpp"

namespace big
{
	void window::render_main_window()
	{
		ImGui::SetNextWindowSize({ 800, 840 }, ImGuiCond_FirstUseEver);
		if (ImGui::Begin("Yimura's Mod Menu"))
		{
			ImGui::BeginTabBar("tabbar");
			tabbar::render_self();
			tabbar::render_weapons();
			tabbar::render_tunables();
			tabbar::render_teleport();
			tabbar::render_vehicle();
			tabbar::render_world();
			tabbar::render_online();
			tabbar::render_misc();
			tabbar::render_spawn();
			tabbar::render_settings();
			ImGui::EndTabBar();
		}
		ImGui::End();
	}
}