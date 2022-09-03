#include "views/view.hpp"
#include "pointers.hpp"

namespace big
{
	void view::network_tabs() {
		if (ImGui::BeginTabBar("network_tabbar"))
		{
			if (ImGui::BeginTabItem("Spoofing"))
			{
				view::spoofing();
				ImGui::EndTabItem();
			}
			if (ImGui::BeginTabItem("Session"))
			{
				view::session();
				ImGui::EndTabItem();
			}

			if (ImGui::BeginTabItem("Player DB"))
			{
				view::player_db();
				ImGui::EndTabItem();
			}

			ImGui::EndTabBar();
		}
	}
}
