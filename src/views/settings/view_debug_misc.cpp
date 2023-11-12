#include "gui/components/components.hpp"
#include "network/Network.hpp"
#include "util/session.hpp"

namespace big
{
	inline void view_debug_misc()
	{
		if (ImGui::BeginTabItem("Misc"))
		{
			static bool imGui_demo = false;

			ImGui::Spacing();
			components::button("Network Bail", [] {
				NETWORK::NETWORK_BAIL(16, 0, 0);
			});
			ImGui::Spacing();
			components::button("Refresh Interior", [] {
				Interior interior = INTERIOR::GET_INTERIOR_AT_COORDS(self::pos.x, self::pos.y, self::pos.z);
				INTERIOR::REFRESH_INTERIOR(interior);
			});
			ImGui::Spacing();
			components::button("Network Shutdown and Load Most Recent Save", [] {
				NETWORK::SHUTDOWN_AND_LOAD_MOST_RECENT_SAVE();
			});
			ImGui::Spacing();
			components::button("Remove Black Screen", [] {
				CAM::DO_SCREEN_FADE_IN(0);
			});
			ImGui::Spacing();
			components::command_button<"fastquit">();
			ImGui::Spacing();
			ImGui::Checkbox("ImGui Demo", &imGui_demo);

			if (imGui_demo)
				ImGui::ShowDemoWindow(&imGui_demo);

			ImGui::EndTabItem();
		}
	}
}
