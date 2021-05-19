#include "tabs.hpp"
#include "core/globals.hpp"

namespace big
{
	void tab_main::tab_self()
	{
		if (ImGui::BeginTabItem("Self"))
		{
			ImGui::Checkbox("No Clip", &g.self.noclip);

			ImGui::EndTabItem();
		}
	}
}