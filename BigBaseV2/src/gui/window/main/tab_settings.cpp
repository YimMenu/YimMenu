#include "main_tabs.hpp"

namespace big
{
	void tab_main::tab_settings()
	{
		if (ImGui::BeginTabItem("Settings"))
		{
			ImGui::Text("No settings to be modified as of now");

			ImGui::EndTabItem();
		}
	}
}