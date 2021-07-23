#include "main_tabs.hpp"
#include "script_global.hpp"
#include "util/player.hpp"

namespace big
{
	void tab_main::tab_self()
	{
		if (ImGui::BeginTabItem("Self"))
		{
			if (ImGui::Button("Easy Way Out"))
			{
				*script_global(262145 + 27907).as<int*>() = 0;
				*script_global(262145 + 27908).as<int*>() = 0;
			}

			if (ImGui::Button("Suicide"))
			{

			}

			ImGui::Checkbox("God Mode", &g.self.godmode);
			ImGui::Checkbox("Off Radar", &g.self.off_radar);
			ImGui::Checkbox("No Clip", &g.self.noclip);
			ImGui::Checkbox("No Ragdoll", &g.self.no_ragdoll);

			ImGui::EndTabItem();
		}
	}
}