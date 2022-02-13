#include "main_tabs.hpp"
#include "fiber_pool.hpp"
#include "script.hpp"
#include "script_global.hpp"
#include "util/entity.hpp"
#include "util/player.hpp"
#include "util/notify.hpp"

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

			if (ImGui::TreeNode("General"))
			{
				ImGui::BeginGroup();

				ImGui::Checkbox("God Mode", &g.self.godmode);
				ImGui::Checkbox("Off Radar", &g.self.off_radar);
				ImGui::Checkbox("Free Cam", &g.self.free_cam);

				ImGui::EndGroup();
				ImGui::SameLine();
				ImGui::BeginGroup();

				ImGui::Checkbox("No Clip", &g.self.noclip);
				ImGui::Checkbox("No Ragdoll", &g.self.no_ragdoll);
				ImGui::Checkbox("Super Run", &g.self.super_run);
				ImGui::EndGroup();

				if (ImGui::TreeNode("Aimbot"))
				{
					ImGui::Checkbox("ESP", &g.self.esp);
					ImGui::Checkbox("AIM", &g.self.aim);


					ImGui::TreePop();
				}
				
				ImGui::TreePop();
			}

			if (ImGui::TreeNode("Frame Flags"))
			{
				ImGui::BeginGroup();

				ImGui::Checkbox("Explosive Ammo", &g.self.frame_flags.explosive_ammo);
				ImGui::Checkbox("Fire Ammo", &g.self.frame_flags.fire_ammo);

				ImGui::EndGroup();
				ImGui::SameLine();
				ImGui::BeginGroup();

				ImGui::Checkbox("Explosive Melee", &g.self.frame_flags.explosive_melee);
				ImGui::Checkbox("Super Jump", &g.self.frame_flags.super_jump);
				
				ImGui::EndGroup();

				ImGui::TreePop();
			}

			if (ImGui::TreeNode("Player Model"))
			{
				static char model[32];

				QUEUE_JOB_BEGIN_CLAUSE()
				{
					PAD::DISABLE_ALL_CONTROL_ACTIONS(0);
				}QUEUE_JOB_END_CLAUSE

					if (
						ImGui::InputText("Model Name###player_ped_model", model, sizeof(model), ImGuiInputTextFlags_EnterReturnsTrue) ||
						ImGui::Button("Set Player Model###spawn_player_ped_model")
						)
					{
						QUEUE_JOB_BEGIN_CLAUSE(= )
						{
							Hash hash = rage::joaat(model);

							for (uint8_t i = 0; !STREAMING::HAS_MODEL_LOADED(hash) && i < 100; i++)
							{
								STREAMING::REQUEST_MODEL(hash);

								script::get_current()->yield();
							}
							if (!STREAMING::HAS_MODEL_LOADED(hash))
							{
								notify::above_map("~r~Failed to spawn model, did you give an incorrect model?");

								return;
							}

							PLAYER::SET_PLAYER_MODEL(PLAYER::GET_PLAYER_INDEX(), hash);
							PED::SET_PED_DEFAULT_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID());
							script::get_current()->yield();
							STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(hash);
						}QUEUE_JOB_END_CLAUSE
					}

				ImGui::TreePop();
			}

			if (ImGui::TreeNode("Police"))
			{
				ImGui::Checkbox("Never Wanted", &g.self.never_wanted);

				if (!g.self.never_wanted)
				{
					ImGui::Checkbox("Force Wanted Level", &g.self.force_wanted_level);
					ImGui::Text("Wanted Level");
					if (ImGui::SliderInt("###wanted_level", &g.self.wanted_level, 0, 5) && !g.self.force_wanted_level)
						g_local_player->m_player_info->m_wanted_level = g.self.wanted_level;
				}

				ImGui::TreePop();
			}

			ImGui::EndTabItem();
		}
	}
}
