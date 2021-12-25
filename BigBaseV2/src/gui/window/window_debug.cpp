#include "gui/window.hpp"
#include "dbg/debug_tabs.hpp"

namespace big
{
	void window::debug()
	{
		if (g.window.debug && ImGui::Begin("Dev"))
		{
			ImGui::BeginTabBar("dev_tabbar");
			tab_debug::_tab_debug();
			tab_debug::tab_globals();
			tab_debug::tab_script_events();
			ImGui::EndTabBar();

			ImGui::End();
		}
	}
}