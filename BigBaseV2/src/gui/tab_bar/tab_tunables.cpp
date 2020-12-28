#include "tab_bar.hpp"
#include "pointers.hpp"
#include "script_global.hpp"

namespace big
{
	void tabbar::render_tunables()
	{
		if (ImGui::BeginTabItem("Tunables"))
		{
			if (ImGui::Checkbox("No Idle Kick", g_settings.options["no_idle_kick"].get<bool*>()))
				g_settings.save();

			if (ImGui::Button("Set Car Sell Value at $25.000.000"))
			{
				*script_global(99007).at(970).as<int*>() = (int)25e6;
			}

			ImGui::EndTabItem();
		}
	}
}