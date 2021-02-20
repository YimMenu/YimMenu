#include "gui/tab_bar.hpp"

namespace big
{
	void tabbar::render_self()
	{
		if (ImGui::BeginTabItem("Self"))
		{
			if (ImGui::Button("Heal Self"))
			{
				QUEUE_JOB_BEGIN_CLAUSE()
				{
					Entity player = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_player.id);

					ENTITY::SET_ENTITY_HEALTH(player, ENTITY::GET_ENTITY_MAX_HEALTH(player), 0);
				}QUEUE_JOB_END_CLAUSE
			}

			if (ImGui::Button("Suicide (Health)"))
			{
				QUEUE_JOB_BEGIN_CLAUSE()
				{
					ENTITY::SET_ENTITY_HEALTH(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_player.id), 0, 0);
				}QUEUE_JOB_END_CLAUSE
			}

			ImGui::Separator();

			if (ImGui::TreeNode("Frame Flags"))
			{
				auto& frame_flags = g_settings.options["frame_flags"];

				ImGui::Checkbox("Explosive Ammo",	frame_flags["explosive_ammo"].get<bool*>());
				ImGui::Checkbox("Explosive Melee",	frame_flags["explosive_melee"].get<bool*>());
				ImGui::Checkbox("Fire Ammo",	frame_flags["fire_ammo"].get<bool*>());
				ImGui::Checkbox("Super Jump",		frame_flags["super_jump"].get<bool*>());

				ImGui::TreePop();
			}

			if (ImGui::TreeNode("No Clip"))
			{
				if (ImGui::Checkbox("No Clip", g_settings.options["noclip"]["enabled"].get<bool*>()))
					g_settings.save();

				const double min = 0.0, max = 10.0;
				if (ImGui::SliderScalar("Horizontal Multiplier", ImGuiDataType_Double, g_settings.options["noclip"]["horizontal"].get<double*>(), &min, &max))
					g_settings.save();
				if (ImGui::SliderScalar("Vertical Multiplier", ImGuiDataType_Double, g_settings.options["noclip"]["vertical"].get<double*>(), &min, &max))
					g_settings.save();

				ImGui::TreePop();
			}

			if (ImGui::Checkbox("God Mode", g_settings.options["god_mode"].get<bool*>()) || ImGui::Checkbox("No Ragdoll", g_settings.options["ragdoll"].get<bool*>()))
				g_settings.save();

			ImGui::Separator();

			if (ImGui::Checkbox("Super Sprint", g_settings.options["super_sprint"].get<bool*>()))
				g_settings.save();

			ImGui::Separator();

			if (ImGui::Button("Clean Player Model"))
			{
				QUEUE_JOB_BEGIN_CLAUSE()
				{
					Ped pedPlayer = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(PLAYER::PLAYER_ID());

					PED::CLEAR_PED_BLOOD_DAMAGE(pedPlayer);
					PED::RESET_PED_VISIBLE_DAMAGE(pedPlayer);
				}QUEUE_JOB_END_CLAUSE
			}
			if (ImGui::Button("Clear Badsport"))
			{
				QUEUE_JOB_BEGIN_CLAUSE()
				{
					STATS::STAT_SET_FLOAT(MISC::GET_HASH_KEY("MPPLY_OVERALL_BADSPORT"), 0.0f, true);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MPPLY_DESTROYED_PVEHICLES"), 0, true);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MPPLY_BADSPORT_MESSAGE"), 0, true);
					// STATS::STAT_SET_FLOAT(MISC::GET_HASH_KEY("MP_PLAYER_MENTAL_STATE"), 0.0f, true);
				}QUEUE_JOB_END_CLAUSE
			}


			ImGui::Separator();

			if (ImGui::Button("Clear Wanted Level"))
			{
				QUEUE_JOB_BEGIN_CLAUSE()
				{
					PLAYER::CLEAR_PLAYER_WANTED_LEVEL(g_player.id);
				}QUEUE_JOB_END_CLAUSE
			}
			if (ImGui::Button("Cops Ignore"))
			{
				QUEUE_JOB_BEGIN_CLAUSE()
				{
					if (PLAYER::GET_PLAYER_WANTED_LEVEL(g_player.id) > 0)
					{
						PLAYER::CLEAR_PLAYER_WANTED_LEVEL(g_player.id);
					}
					PLAYER::SET_POLICE_IGNORE_PLAYER(g_player.id, true);
				}QUEUE_JOB_END_CLAUSE
			}

			if (ImGui::Checkbox("Never Wanted", g_settings.options["never_wanted"].get<bool*>()))
				g_settings.save();

			if (!g_settings.options["never_wanted"].get<bool>())
			{
				if (ImGui::SliderInt("Wanted Level", &g_temp.wanted_level, 0, 5))
				{
					QUEUE_JOB_BEGIN_CLAUSE(= )
					{
						PLAYER::SET_PLAYER_WANTED_LEVEL(g_player.id, g_temp.wanted_level, true);
						PLAYER::SET_PLAYER_WANTED_LEVEL_NOW(g_player.id, true);
					}QUEUE_JOB_END_CLAUSE
				}
			}
			else
			{
				g_temp.wanted_level = 0;
			}

			ImGui::EndTabItem();
		}
	}
}