#include "services/gui/gui_service.hpp"
#include "view_debug.hpp"

namespace big
{
	void debug::main()
	{
		if (strcmp(g_gui_service->get_selected()->name, "Debug"))
			return;

		if (ImGui::Begin("Debug"))
		{
			ImGui::BeginTabBar("debug_tabbar");
			misc();
			logs();
			globals();
			locals();
			script_events();
			ImGui::EndTabBar();
		}
		ImGui::End();
	}
}