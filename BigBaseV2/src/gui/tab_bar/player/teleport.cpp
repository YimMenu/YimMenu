#include "gui/tab_bar.hpp"
#include "features/teleport.hpp"

namespace big
{
	void tabbar::player_teleport()
	{
		if (ImGui::BeginTabItem("Teleport"))
		{
			if (ImGui::Button("Teleport to Player"))
			{
				QUEUE_JOB_BEGIN_CLAUSE()
				{
					teleport::teleport_to_player(g_selectedPlayer.id);
				}QUEUE_JOB_END_CLAUSE
			}

			if (ImGui::Button("Teleport into Vehicle"))
			{
				QUEUE_JOB_BEGIN_CLAUSE()
				{
					teleport::teleport_into_player_vehicle(g_selectedPlayer.id);
				}QUEUE_JOB_END_CLAUSE
			}

			ImGui::EndTabItem();
		}
	}
}