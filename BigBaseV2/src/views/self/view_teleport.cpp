#include "views/view.hpp"
#include "fiber_pool.hpp"
#include "util/globals.hpp"
#include "util/mobile.hpp"
#include "util/teleport.hpp"
#include "util/vehicle.hpp"

namespace big
{
	void view::teleport()
	{
		components::button("Waypoint", [] {
			teleport::to_waypoint();
		});

		ImGui::SameLine();

		components::button("Objective", [] {
			teleport::to_objective();
		});

		ImGui::Separator();

		components::sub_title("Property");


		static bool ready = true;
		static int update_ticks = 0;
		static std::map<std::string, Vector3> property_list;

		if (ready == true)
		{
			if (update_ticks == 0)
			{
				ready = false;

				g_fiber_pool->queue_job([] {
					property_list.clear();
					blip::get_property_list(property_list);

					ready = true;
				});
			}

			update_ticks++;

			if (update_ticks > 1000)
			{
				update_ticks = 0;
			}
		}

		if (ImGui::ListBoxHeader("##property_list", { 300, 300 }))
		{
			for (auto& it : property_list)
			{
				const auto& name = it.first;
				const auto& location = it.second;

				components::selectable(name, false, [&location] {
					teleport::to_coords(location);
				});
			}

			ImGui::ListBoxFooter();
		}
	}
}
