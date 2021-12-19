#include "gui/window.hpp"
#include "imgui.h"
#include "main/main_tabs.hpp"

namespace big
{
	void window::main()
	{
		ImGui::SetNextWindowSize({ 800, 840 }, ImGuiCond_FirstUseEver);
		if (g.window.main && ImGui::Begin("Yimura's Mod Menu"))
		{
			ImGui::BeginTabBar("tabbar");
			tab_main::tab_self();
			tab_main::tab_spawn();
			tab_main::tab_tunables();
			tab_main::tab_teleport();
			lsc_tab::render_lsc_tab();
			tab_main::tab_vehicle();
			persist_car::do_presentation_layer();
			tab_main::tab_weapons();
			tab_main::tab_recovery();
			tab_main::tab_spoofing();
			tab_main::tab_settings();
			ImGui::EndTabBar();

			ImGui::End();
		}
	}
}