#include "main_tabs.hpp"
#include "script.hpp"
#include "script_global.hpp"
#include "script_local.hpp"
#include "common.hpp"
#include "fiber_pool.hpp"
#include "gta/player.hpp"
#include "gta_util.hpp"

namespace big
{
	void tab_main::tab_tunables()
	{
		if (ImGui::BeginTabItem("Tunables"))
		{
			ImGui::Checkbox("Disable Phone", &g->tunables.disable_phone);
			ImGui::Checkbox("No Idle Kick", &g->tunables.no_idle_kick);
			ImGui::Checkbox("Always Jackpot in Slot Machines", &g->tunables.rig_casino);

			ImGui::EndTabItem();
		}
	}
}