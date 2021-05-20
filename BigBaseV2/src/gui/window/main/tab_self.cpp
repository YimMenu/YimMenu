#include "tabs.hpp"

namespace big
{
	void tab_main::tab_self()
	{
		if (ImGui::BeginTabItem("Self"))
		{
			ImGui::Checkbox("God Mode", &g.self.godmode);
			ImGui::Checkbox("No Clip", &g.self.noclip);

			ImGui::EndTabItem();
		}
	}
}