#include "view_debug.hpp"
#include "gui/components/components.hpp"
#include "natives.hpp"

namespace big
{
	void debug::locals()
	{
		if (ImGui::BeginTabItem("Locals"))
		{
			if (components::button("Load MP Map"))
				DLC::ON_ENTER_MP();
			ImGui::SameLine();
			if (components::button("Load SP Map"))
				DLC::ON_ENTER_SP();
			if (components::button("Skip Cutscene"))
				CUTSCENE::STOP_CUTSCENE_IMMEDIATELY();
			if (components::button("Refresh Interior"))
			{
				Interior interior = INTERIOR::GET_INTERIOR_AT_COORDS(self::pos.x, self::pos.y, self::pos.z);
				INTERIOR::REFRESH_INTERIOR(interior);
			}
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip("You Will Have To Refresh Again When Exiting Interior.");
			ImGui::EndTabItem();
		}
	}
}