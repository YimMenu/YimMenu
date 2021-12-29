#include "main_tabs.hpp"
#include "fiber_pool.hpp"
#include "util/teleport.hpp"
#include <vector>

namespace big
{
	void tab_main::tab_teleport()
	{
		if (ImGui::BeginTabItem("Teleport"))
		{
			if (ImGui::Button("Waypoint"))
			{
				QUEUE_JOB_BEGIN_CLAUSE()
				{
					teleport::to_waypoint();
				}QUEUE_JOB_END_CLAUSE
			}

			if (ImGui::Button("Objective"))
			{
				QUEUE_JOB_BEGIN_CLAUSE()
				{
					static const int blips[] = {1, 57, 128, 129, 130, 143, 144, 145, 146, 271, 286, 287, 288};
					for (int i = 0; i < (sizeof(blips)/sizeof(*blips)); i++) {
						if (teleport::to_blip(blips[i], 5)) {
							break;
						}

					}
				}QUEUE_JOB_END_CLAUSE
			}

			ImGui::EndTabItem();
		}
	}
}