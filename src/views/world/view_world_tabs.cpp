#include "views/view.hpp"
#include "pointers.hpp"

namespace big
{
	void view::world_tabs() {
		if (ImGui::BeginTabBar("world_tabbar"))
		{
			if (ImGui::BeginTabItem("Spawn Ped"))
			{
				view::spawn_ped();
				ImGui::EndTabItem();
			}
			if (ImGui::BeginTabItem("Time and Weather"))
			{
				view::time_and_weather();
				ImGui::EndTabItem();
			}
			if (ImGui::BeginTabItem("Embient Population"))
			{
				view::ambient();
				ImGui::EndTabItem();
			}
			ImGui::EndTabBar();
		}
	}
}
