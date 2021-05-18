#include "common.hpp"
#include "base_tab.h"
#include "imgui.h"
#include "script.hpp"
#include "fiber_pool.hpp"
#include "natives.hpp"
#include "gta_util.hpp"
#include "ImGuiBitfield.h"

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
					constexpr auto hash = RAGE_JOAAT("adder");
					while (!STREAMING::HAS_MODEL_LOADED(hash))
					{
						STREAMING::REQUEST_MODEL(hash);
						script::get_current()->yield();
					}

					auto pos = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), true);
					*(unsigned short*)g_pointers->m_model_spawn_bypass = 0x9090;
					Vehicle vehicle = VEHICLE::CREATE_VEHICLE(hash, pos.x, pos.y, pos.z, 0.f, TRUE, FALSE, FALSE);
					*(unsigned short*)g_pointers->m_model_spawn_bypass = 0x0574; //By writing the "old" bypass to the function, running CREATE_VEHICLE, then restoring it, the anti-cheat does not have enough time to catch the function in a dirty state.

					script::get_current()->yield();
					STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(hash);
					if (*g_pointers->m_is_session_started)
					{
						DECORATOR::DECOR_SET_INT(vehicle, "MPBitset", 0);
						ENTITY::_SET_ENTITY_SOMETHING(vehicle, TRUE); //True means it can be deleted by the engine when switching lobbies/missions/etc, false means the script is expected to clean it up.
						auto networkId = NETWORK::VEH_TO_NET(vehicle);
						if (NETWORK::NETWORK_GET_ENTITY_IS_NETWORKED(vehicle))
							NETWORK::SET_NETWORK_ID_EXISTS_ON_ALL_MACHINES(networkId, true);
						VEHICLE::SET_VEHICLE_IS_STOLEN(vehicle, FALSE);
					}
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