#include "main_tabs.hpp"
#include "fiber_pool.hpp"
#include "util/teleport.hpp"

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

			if (ImGui::Button("Waypoint"))
			{
				QUEUE_JOB_BEGIN_CLAUSE()
				{
					teleport::to_blip(1, 5);
					teleport::to_blip(57, 5);
					teleport::to_blip(128, 5);
					teleport::to_blip(129, 5);
					teleport::to_blip(130, 5);
					teleport::to_blip(143, 5);
					teleport::to_blip(144, 5);
					teleport::to_blip(145, 5);
					teleport::to_blip(146, 5);
					teleport::to_blip(271, 5);
					teleport::to_blip(286, 5);
					teleport::to_blip(287, 5);
					teleport::to_blip(288, 5);
				}QUEUE_JOB_END_CLAUSE
			}

			ImGui::EndTabItem();
		}
	}
}