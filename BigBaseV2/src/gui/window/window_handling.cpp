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
			if (g_local_player == nullptr || g_local_player->m_vehicle == nullptr || g_local_player->m_in_vehicle == 0x10)
			{
				ImGui::Text("Please enter a vehicle.");

				return;
			}
			g_vehicle_service->attempt_save();

			ImGui::BeginTabBar("handling_tabbar");
			tab_handling::tab_general();
			tab_handling::tab_other();
			tab_handling::tab_brakes();
			tab_handling::tab_gearing();
			tab_handling::tab_traction();
			tab_handling::tab_steering();
			tab_handling::tab_suspension();
			tab_handling::tab_rollbars();
			tab_handling::tab_roll_centre_height();
			ImGui::EndTabBar();

			ImGui::End();
		}
	}
}