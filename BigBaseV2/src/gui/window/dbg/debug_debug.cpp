#include "debug_tabs.hpp"
#include "util/system.hpp"

namespace big
{
	void tab_debug::_tab_debug()
	{
		if (ImGui::BeginTabItem("Debug"))
		{
			ImGui::Checkbox("Script Event Logging", &g->debug.script_event_logging);

			if (ImGui::Button("Dump entrypoints"))
			{
				system::dump_entry_points();
			}

			ImGui::EndTabItem();
		}
	}
}