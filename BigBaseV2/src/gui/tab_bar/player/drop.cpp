#include "gui/tab_bar.hpp"

namespace big
{
	void tabbar::player_drop()
	{
		if (ImGui::BeginTabItem("Drop"))
		{
			if (ImGui::Button("Drop RP"))
			{
				QUEUE_JOB_BEGIN_CLAUSE()
				{
					Vector3 coords = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_selectedPlayer.id), true);

					features::functions::create_ambient_rp(coords);
				}QUEUE_JOB_END_CLAUSE
			}

			if (ImGui::Button("Drop Money (!)"))
			{
				QUEUE_JOB_BEGIN_CLAUSE()
				{
					Vector3 coords = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_selectedPlayer.id), true);

					features::functions::create_ambient_money(coords, rand() % 500 + 2000);
				}QUEUE_JOB_END_CLAUSE
			}

			ImGui::EndTabItem();
		}
	}
}