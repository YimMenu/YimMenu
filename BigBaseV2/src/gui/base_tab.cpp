#include "common.hpp"
#include "base_tab.h"
#include "imgui.h"
#include "script.hpp"
#include "fiber_pool.hpp"
#include "natives.hpp"
#include "gta_util.hpp"
#include "imguibitfield.h"
#include "util/vehicle.hpp"

namespace big
{
	void base_tab::render_base_tab()
	{
		if (ImGui::BeginTabItem("Test"))
		{
			const char* const demo_combo[]
			{
				"One",
				"Two",
				"Three"
			};
			const double min = 0., max = 10.;

			//If you want to add a new option, you have to first declare it in settings.h's default_options, otherwise, this code will crash when trying to access an option that does not exist in memory.
			if (ImGui::Checkbox("Bool", g_settings.options["demo bool"].get<bool*>()))
				g_settings.save();
			if (ImGui::SliderInt("Int", (PINT)g_settings.options["demo int"].get<int64_t*>(), 0, 10))
				g_settings.save();
			if (ImGui::SliderScalar("Double", ImGuiDataType_Double, g_settings.options["demo double"].get<double*>(), &min, &max)) //JSON does not describe rational numbers as integer/float/double/etc types, it is just "number". See: https://nlohmann.github.io/json/features/types/
				g_settings.save();
			if (ImGui::Combo("Combo", (PINT)g_settings.options["demo combo"].get<int64_t*>(), demo_combo, sizeof(demo_combo) / sizeof(*demo_combo)))
				g_settings.save();
			if (ImGui::Bitfield("Bitfield", g_settings.options["demo bitset"].get<int64_t*>()))
				g_settings.save();
			
			if (ImGui::Button("Spawn an Adder"))
			{
				QUEUE_JOB_BEGIN_CLAUSE()
				{
					Ped player = PLAYER::GET_PLAYER_PED(PLAYER::GET_PLAYER_INDEX());
					Vector3 location = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(player, 0.f, 8.f, 0.5f);

					vehicle::spawn("adder", location, ENTITY::GET_ENTITY_HEADING(player) + 90.f);
				}
				QUEUE_JOB_END_CLAUSE
			}

			if (ImGui::Button("Test g3log crash within ImGui"))
			{
				*((PINT)nullptr) = 0xDEADBEEF;
			}
			ImGui::SameLine();
			if (ImGui::Button("Test g3log crash within GTA V Script"))
			{
				QUEUE_JOB_BEGIN_CLAUSE()
				{
					//PED::_0xB782F8238512BAD5(PLAYER::PLAYER_PED_ID(), nullptr); //This causes a crash at GTA5.exe+5845356 and nothing of value was in the log in the stack dump because of the context switch to GTA 5's memory. If you encounter something similar, you will have to figure out where the crash occured in the GTA 5 exe, and trace back that native, and figure out which function is calling the native that is crashing.
					*((PINT)nullptr) = 0xDEADBEEF;
				}
				QUEUE_JOB_END_CLAUSE
			}

			ImGui::Separator();

			if (ImGui::Button("Unload"))
			{
				g_running = false;
			}
			ImGui::EndTabItem();
		}
	}
}