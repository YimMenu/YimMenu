#include "gui/tab_bar.hpp"

namespace big
{
	void tabbar::player_info()
	{
		if (ImGui::BeginTabItem("Info"))
		{
			ImGui::Checkbox("Spectate Player", &g_temp.is_spectating);

			ImGui::EndTabItem();
		}
	}
}