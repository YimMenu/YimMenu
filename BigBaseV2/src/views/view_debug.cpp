#include "views/view.hpp"

namespace big
{
	void view::debug() {
		ImGui::BeginTabBar("dev_tabbar");
		//tab_debug::_tab_debug();
		//tab_debug::tab_globals();
		//tab_debug::tab_script_events();
		ImGui::EndTabBar();
	}
}