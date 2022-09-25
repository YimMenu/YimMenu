#include "views/view.hpp"
#include "pointers.hpp"

namespace big
{
	void view::debug_tabs() {
		if (ImGui::BeginTabBar("debug_tabbar"))
		{
			if (ImGui::BeginTabItem("Scripts"))
			{
				view::debug_scripts();
				ImGui::EndTabItem();
			}
			if (ImGui::BeginTabItem("Script Events"))
			{
				view::debug_script_events();
				ImGui::EndTabItem();
			}
			if (ImGui::BeginTabItem("Globals"))
			{
				view::debug_globals();
				ImGui::EndTabItem();
			}
			if (ImGui::BeginTabItem("Ped Flags"))
			{
				view::debug_ped_flags();
				ImGui::EndTabItem();
			}

			if (ImGui::BeginTabItem("Misc"))
			{
				view::debug_misc();
				ImGui::EndTabItem();
			}
			
			ImGui::EndTabBar();
		}
	}
}
