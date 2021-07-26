#include "gui/window.hpp"
#include "handling/handling_tabs.hpp"
#include "imgui.h"

namespace big
{
	void window::handling()
	{
		ImGui::SetNextWindowSize({ 500, 250 }, ImGuiCond_FirstUseEver);
		ImGui::SetNextWindowPos({ 50, 50 }, ImGuiCond_FirstUseEver);
		if (g.window.handling && ImGui::Begin("Handling", &g.window.handling))
		{
			if (g_local_player == nullptr || g_local_player->m_vehicle == nullptr)
			{
				ImGui::Text("Please enter a vehicle to modify handling.");

				return;
			}

			ImGui::BeginTabBar("handling_tabbar");
			tab_handling::tab_phyics();
			tab_handling::tab_braking();
			tab_handling::tab_steering();
			tab_handling::tab_traction();
			tab_handling::tab_suspension();
			// rollbars
			// misc
			ImGui::EndTabBar();

			ImGui::End();
		}
	}
}