#include "gui/window.hpp"
#include "gui/tab_bar.hpp"
#include "features.hpp"

namespace big
{
	void window::render_handling_window()
	{
		ImGui::SetNextWindowSize({ 500, 780 }, ImGuiCond_FirstUseEver);
		if (g_handling_window && ImGui::Begin("Handling", &g_handling_window))
		{
			if (g_in_vehicle && g_vehicle != nullptr)
			{
				ImGui::BeginTabBar("handling_tabbar");
				tabbar::handling_physics();
				tabbar::handling_brakes();
				tabbar::handling_suspension();
				tabbar::handling_traction();
				tabbar::handling_transmission();
				ImGui::EndTabBar();
			}
			else ImGui::Text("You're not in a vehicle right now.");

			ImGui::End();
		}
	}
}