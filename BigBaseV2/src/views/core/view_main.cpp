#include "views/view.hpp"
#include "pointers.hpp"

namespace big
{
	void view::main_view() 
	{
		if (ImGui::Begin("Main"))
		{
			if (ImGui::BeginTabBar("tabbar"))
			{
				if (ImGui::BeginTabItem("Self"))
				{
					view::self_tabs();
					ImGui::EndTabItem();
				}
				if (ImGui::BeginTabItem("Vehicle"))
				{
					view::vehicle_tabs();
					ImGui::EndTabItem();
				}
				if (ImGui::BeginTabItem("World"))
				{
					view::spawn_ped();
					ImGui::EndTabItem();
				}
				if (ImGui::BeginTabItem("Network"))
				{
					view::network_tabs();
					ImGui::EndTabItem();
				}
				if (ImGui::BeginTabItem("Settings"))
				{
					view::settings_tabs();
					ImGui::EndTabItem();
				}
				if (ImGui::BeginTabItem("Debug"))
				{
					view::debug_tabs();
					ImGui::EndTabItem();
				}

				ImGui::EndTabBar();
			}
		}
	}
}
