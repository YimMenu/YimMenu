#include "gui/components/components.hpp"
#include "network/Network.hpp"
#include "util/pathfind.hpp"
#include "services/notifications/notification_service.hpp"
#include "core/settings.hpp"

namespace big
{
	inline void view_debug_misc()
	{
		if (ImGui::BeginTabItem("Misc"))
		{
			components::button("Network Bail", [] {
				NETWORK::NETWORK_BAIL(16, 0, 0);
			});

			components::button("Refresh Interior", [] {
				Interior interior = INTERIOR::GET_INTERIOR_AT_COORDS(self::pos.x, self::pos.y, self::pos.z);
				INTERIOR::REFRESH_INTERIOR(interior);
			});

			components::button("Network Shutdown and Load Most Recent Save", [] {
				NETWORK::SHUTDOWN_AND_LOAD_MOST_RECENT_SAVE();
			});

			components::button("Remove Black Screen", [] {
				CAM::DO_SCREEN_FADE_IN(0);
			});

			components::button("TP to Safe Position", [] {
				Vector3 safepos{};
				float heading;
				if (pathfind::find_closest_vehicle_node(self::pos, safepos, heading, 0))
					ENTITY::SET_ENTITY_COORDS(self::ped, safepos.x, safepos.y, safepos.z, 0, 0, 0, false);
				else
					g_notification_service->push_error("Find safe pos", "Failed to find a safe position");
			});

			ImGui::Checkbox("ImGui Demo", &g.window.demo);

			components::command_button<"fastquit">();

			ImGui::EndTabItem();
		}
	}
}
