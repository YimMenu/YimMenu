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

			if (ImGui::Checkbox("Disable Phone Calls", g_settings.options["disable_phone"].get<bool*>()))
				g_settings.save();

			ImGui::EndTabItem();
		}
	}
}