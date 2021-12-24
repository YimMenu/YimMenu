#include "main_tabs.hpp"
#include "util/system.hpp"

namespace big
{
	void tab_main::tab_settings()
	{
		if (ImGui::BeginTabItem("Settings"))
		{
			if (ImGui::Button("Dump entrypoints"))
			{
				system::dump_entry_points();
			}

			ImGui::EndTabItem();
		}
	}
}