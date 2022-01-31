#include "fiber_pool.hpp"
#include "gta/enums.hpp"
#include "gta_util.hpp"
#include "player_tabs.hpp"
#include "natives.hpp"
#include "script.hpp"
#include "util/toxic.hpp"

namespace big
{
	void tab_player::tab_toxic()
	{
		if (ImGui::BeginTabItem("Toxic"))
		{
			if (ImGui::Button("Explode Self"))
			{
				QUEUE_JOB_BEGIN_CLAUSE()
				{
					toxic::blame_explode_player(
						g_player_service->m_selected_player->id(),
						g_player_service->m_selected_player->id(),
						eExplosionType::PLANE, 1000, false, true, 0.f
					);
				}QUEUE_JOB_END_CLAUSE
			}

			ImGui::EndTabItem();
		}
	}
}