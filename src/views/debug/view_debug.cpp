#include "view_debug.hpp"

#include "services/gui/gui_service.hpp"

namespace big
{
	void debug::main()
	{
		if (strcmp(g_gui_service->get_selected()->name, "GUI_TAB_DEBUG"))
			return;

		if (ImGui::Begin("DEBUG_WINDOW"_T.data()))
		{
			ImGui::BeginTabBar("debug_tabbar");
			misc();
			logs();
			tunables();
			globals();
			locals();
			script_events();
			scripts();
			threads();
		}
		ImGui::End();
	}
}