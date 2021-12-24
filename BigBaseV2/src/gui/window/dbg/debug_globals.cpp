#include "debug_tabs.hpp"

namespace big
{
	void tab_debug::tab_globals()
	{
		if (ImGui::BeginTabItem("Globals"))
		{
			ImGui::Text("Coming soon...");

			ImGui::EndTabItem();
		}
	}
}