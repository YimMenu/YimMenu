#include "views/view.hpp"
#include "view_debug_misc.cpp"

namespace big
{
	void view::debug()
	{
		if (ImGui::Begin("Debug"))
		{
			ImGui::BeginTabBar("debug_tabbar");
			view_debug_misc();
			ImGui::EndTabBar();
		}
		ImGui::End();
	}
}