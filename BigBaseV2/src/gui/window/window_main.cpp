#include "gui/window.hpp"
#include "imgui.h"
#include "gui/base_tab.h"
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
			ImGui::EndTabBar();
		}
		ImGui::End();
	}
}