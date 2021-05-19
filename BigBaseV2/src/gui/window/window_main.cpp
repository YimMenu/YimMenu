#include "gui/window.hpp"
#include "imgui.h"
#include "gui/window/main/tabs.hpp"

namespace big
{
	void window::main()
	{
		ImGui::SetNextWindowSize({ 800, 840 }, ImGuiCond_FirstUseEver);
		if (ImGui::Begin("Yimura's Mod Menu"))
		{
			ImGui::BeginTabBar("tabbar");
			tab_main::tab_self();
			tab_main::tab_spawn();
			tab_main::tab_weapons();
			ImGui::EndTabBar();
		}
		ImGui::End();
	}
}