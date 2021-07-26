#include "main_tabs.hpp"
#include "fiber_pool.hpp"
#include "script.hpp"
#include "script_global.hpp"
#include "util/player.hpp"

namespace big
{
	void tab_main::tab_self()
	{
		if (ImGui::BeginTabItem("Self"))
		{
			if (ImGui::Button("Suicide"))
			{
				QUEUE_JOB_BEGIN_CLAUSE()
				{
					ENTITY::SET_ENTITY_HEALTH(PLAYER::PLAYER_PED_ID(), 0, 0);
				}QUEUE_JOB_END_CLAUSE
			}

			ImGui::Checkbox("God Mode", &g.self.godmode);
			ImGui::Checkbox("Off Radar", &g.self.off_radar);
			ImGui::Checkbox("No Clip", &g.self.noclip);
			ImGui::Checkbox("No Ragdoll", &g.self.no_ragdoll);

			if (ImGui::TreeNode("Frame Flags"))
			{
				ImGui::Checkbox("Explosive Ammo", &g.self.frame_flags.explosive_ammo);
				ImGui::SameLine();
				ImGui::Checkbox("Fire Ammo", &g.self.frame_flags.fire_ammo);

				ImGui::Checkbox("Explosive Melee", &g.self.frame_flags.explosive_melee);
				ImGui::SameLine();
				ImGui::Checkbox("Super Jump", &g.self.frame_flags.super_jump);

				ImGui::TreePop();
			}

			ImGui::EndTabItem();
		}
	}
}