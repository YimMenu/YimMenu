#include "main_tabs.hpp"
#include "fiber_pool.hpp"
#include "natives.hpp"
#include "script.hpp"
#include "util/vehicle.hpp"
#include "persist/PersistCar.h" 

namespace big
{
	static char model[12];
	static int CommercialListPos = 0;
	static int BoatListPos = 0;
	const char* category[] = { "Boats", "Commercials", "Compacts", "Coupes" , "Cycles" , "Emergency" , "Helicopters" , "Industrial" , "Military" , "Motorcycles" , "Muscle" , "Off-Road" ,
		"Open Wheel" , "Planes" , "SUVs", "Sedans" , "Service" , "Sports" , "Sports Classic" , "Super" , "Trailer" , "Trains", "Utility", "Vans" , "Beach Bum" , "Valentine's Day" 
	, "Business" , "High Life" , "Hipster" , "Independence Day" , "Festive Surprise", "Next Gen", "LTS", "Flight School", "Lowriders", "Ill-Gotten Gains", "Powerful"
	, "Finance & Felony" , "Custom Classics" , "Be My Valentine" , "January 2016" , "Festive Surprise 2015", "Executive Vehicles", "Halloween", "Cunning Stunts",
		"Import/Export", "Bikers Business", "Circuit Vehicle", "Gunrunning", "Smuggler's Run", "The Doomsday Heist" , "Southern SA Super Sport" , "After Hours"
		, "Arena War" , "Casino Resort" , "Casino Heist" , "Summer Special" , "Cayo Perico", "Contract DLC"};

	const char* Boats[] = {
		"dinghy", "dinghy2", "dinghy3", "dinghy4", "jetmax", "marquis",
		 "seashark", "seashark2", "seashark3", "speeder", "speeder2", "squalo",
		  "submersible", "submersible2", "suntrap", "toro", "toro2", "tropic", "tropic2",
			"tug", "avisa", "dinghy5", "kosatka", "longfin", "patrolboat"
	};

	const char* Commercials[] = {
				"benson", "biff", "cerberus", "cerberus2", "cerberus3", "hauler",
				 "hauler2", "mule", "mule2", "mule3", "mule4", "packer", "phantom",
				  "phantom2", "phantom3", "pounder", "pounder2", "stockade", "stockade3",
				   "terbyte"
	};

	void tab_main::tab_spawn()
	{
		if (ImGui::BeginTabItem("Spawn"))
		{
			QUEUE_JOB_BEGIN_CLAUSE()
			{
				PAD::DISABLE_ALL_CONTROL_ACTIONS(0);
			}QUEUE_JOB_END_CLAUSE

			if (
				ImGui::InputText("Model Name", model, sizeof(model), ImGuiInputTextFlags_EnterReturnsTrue) ||
				ImGui::Button("Spawn")
				)
			{
				QUEUE_JOB_BEGIN_CLAUSE(= )
				{
					Ped player = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(PLAYER::GET_PLAYER_INDEX());
					Vector3 location = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(player, .0, 8.0, .5);

					vehicle::spawn((const char*)model, location, ENTITY::GET_ENTITY_HEADING(player) + 90.f);
				}QUEUE_JOB_END_CLAUSE
			}
			
			ImGui::Separator();
			persist_car::do_presentation_layer();
			ImGui::Separator();
			static int combo_pos = 0;
			ImGui::Combo("Vehicle Category", &combo_pos, category, sizeof(category) / sizeof(*category));
			if (combo_pos != -1)
			{
				switch (combo_pos) {
				case 0:
							ImGui::Combo("", &BoatListPos, Boats, sizeof(Boats) / sizeof(*Boats));
					break;
				case 1:
							ImGui::Combo("", &CommercialListPos, Commercials, sizeof(Commercials) / sizeof(*Commercials));
					break;
				}
			}

			ImGui::EndTabItem();
		}
	}
}