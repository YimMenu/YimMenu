#include "views/view.hpp"
#include "pointers.hpp"

namespace big
{
	void view::vehicle_tabs() {
		if (ImGui::BeginTabBar("vehicle_tabbar"))
		{
			if (ImGui::BeginTabItem("Vehicle")) 
			{
				view::vehicle();
				ImGui::EndTabItem();
			}
			if (ImGui::BeginTabItem("Handling"))
			{
				view::handling_tabs();
				ImGui::EndTabItem();
			}
			if (ImGui::BeginTabItem("LS Customs"))
			{
				view::lsc();
				ImGui::EndTabItem();
			}
			if (ImGui::BeginTabItem("Spawn Vehicle"))
			{
				view::spawn_vehicle();
				ImGui::EndTabItem();
			}
			if (ImGui::BeginTabItem("Personal Vehicle"))
			{
				view::pv();
				ImGui::EndTabItem();
			}
			if (ImGui::BeginTabItem("Persist Car"))
			{
				view::persist_car();
				ImGui::EndTabItem();
			}
			if (ImGui::BeginTabItem("Fun Features"))
			{
				view::fun_vehicle();
				ImGui::EndTabItem();
			}

			ImGui::EndTabBar();
		}
	}
}
