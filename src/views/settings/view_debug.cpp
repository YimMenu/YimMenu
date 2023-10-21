#include "view_debug_misc.cpp"
#include "views/view.hpp"

namespace big
{
	void view::debug()
	{
		ImGui::BeginTabBar("debug_tabbar");
		view_debug_misc();
		ImGui::EndTabBar();
	}
}