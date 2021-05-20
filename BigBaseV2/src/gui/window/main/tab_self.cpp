#include "tabs.hpp"

namespace big
{
	void tab_main::tab_self()
	{
		if (ImGui::BeginTabItem("Self"))
		{
			ImGui::Checkbox("God Mode", &g.self.godmode);
			ImGui::Checkbox("Off Radar", &g.self.off_radar);
			ImGui::Checkbox("No Clip", &g.self.noclip);
			ImGui::Checkbox("No Ragdoll", &g.self.no_ragdoll);

			ImGui::EndTabItem();
		}
	}
}