#include "gui/tab_bar.hpp"
#include "features/functions.hpp"
#include "features/notify.hpp"
#include "features/stats.hpp"
#include "gta/joaat.hpp"
#include "pointers.hpp"
#include "natives.hpp"

namespace big
{
	void tabbar::render_misc()
	{
		if (ImGui::BeginTabItem("Misc"))
		{
			static char player_model[20];
			if (
				ImGui::InputText("Player Model", player_model, sizeof(player_model), ImGuiInputTextFlags_EnterReturnsTrue) ||
				ImGui::Button("Set")
				) {
				QUEUE_JOB_BEGIN_CLAUSE(=)
				{
					Ped ped = PLAYER::PLAYER_PED_ID();
					int type = PED::GET_PED_TYPE(ped);

					Vector3 coords = ENTITY::GET_ENTITY_COORDS(ped, true);

					Hash model = rage::joaat(player_model);

					for (uint8_t i = 0; !STREAMING::HAS_MODEL_LOADED(model) && i < 100; i++)
					{
						STREAMING::REQUEST_MODEL(model);

						script::get_current()->yield();
					}
					if (!STREAMING::HAS_MODEL_LOADED(model))
					{
						notify::above_map("~r~Failed to load player model, did you give an incorrect model?");

						return;
					}

					*(unsigned short*)g_pointers->m_model_spawn_bypass = 0x9090;
					Ped new_ped = PED::CREATE_PED(type, model, coords.x, coords.y, coords.z + 1.f, 0.f, true, false);
					*(unsigned short*)g_pointers->m_model_spawn_bypass = 0x0574;

					script::get_current()->yield();

					PLAYER::CHANGE_PLAYER_PED(g_player.id, new_ped, false, false);

					STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(model);
					ENTITY::_SET_ENTITY_SOMETHING(new_ped, true);

					func::take_control_of_entity(ped);
					func::delete_entity(ped);
				}QUEUE_JOB_END_CLAUSE
			}

			ImGui::Text("Set Current Character Level:");
			ImGui::SliderInt("##input_levels_self", &g_temp.set_level, 0, 8000);
			if (ImGui::Button("Set Level"))
			{
				QUEUE_JOB_BEGIN_CLAUSE()
				{
					func::set_player_level(g_temp.set_level);
				}QUEUE_JOB_END_CLAUSE
			}

			if (ImGui::Button("Unlock Achievements"))
			{
				QUEUE_JOB_BEGIN_CLAUSE()
				{
					stats::unlock_achievements();
				}QUEUE_JOB_END_CLAUSE
			}

			if (ImGui::Button("Max Character Stats"))
			{
				QUEUE_JOB_BEGIN_CLAUSE()
				{
					int character_index;
					func::get_active_character_slot(&character_index);

					stats::max_stats(character_index);
				}QUEUE_JOB_END_CLAUSE
			}

			if (ImGui::Button("Unlock All Stats"))
			{
				QUEUE_JOB_BEGIN_CLAUSE()
				{
					stats::unlock_all();
				}QUEUE_JOB_END_CLAUSE
			}

			ImGui::EndTabItem();
		}
	}
}