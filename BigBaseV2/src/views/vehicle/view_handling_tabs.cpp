#include "views/view.hpp"
#include "pointers.hpp"

namespace big
{
	void view::handling_tabs() {
		if (ImGui::BeginTabBar("handling_tabbar"))
		{
			if (ImGui::BeginTabItem("Current Profile")) 
			{
				view::handling_current_profile();
				ImGui::EndTabItem();
			}
			if (ImGui::BeginTabItem("My Profiles"))
			{
				view::handling_my_profiles();
				ImGui::EndTabItem();
			}
			if (ImGui::BeginTabItem("Saved Profiles"))
			{
				view::handling_saved_profiles();
				ImGui::EndTabItem();
			}
			if (ImGui::BeginTabItem("Search Handling"))
			{
				view::handling_search();
				ImGui::EndTabItem();
			}

			ImGui::EndTabBar();
		}
	}
}
