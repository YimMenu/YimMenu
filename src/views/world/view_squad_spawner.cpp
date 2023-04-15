#include "services/squad_spawner/squad_spawner.hpp"
#include "views/view.hpp"

namespace big
{

	void view::squad_spawner()
	{
		const char* const spawn_distance_modes[5]{"Custom", "On target", "Closeby", "Moderately distanced", "Far away"};

		static eSquadSpawnDistance spawn_distance_mode = eSquadSpawnDistance::CLOSEBY;

		static char name[32];
		static char ped_model[32] = "a_m_m_eastsa_02";
		static char veh_model[32] = "kuruma";
		static char weap_model[32];
		static int squad_size = 1;
		static bool ped_proofs[5];

		components::input_text_with_hint("##name", "Squad name", name, IM_ARRAYSIZE(name));
		components::input_text_with_hint("##pedmodel", "Ped model", ped_model, IM_ARRAYSIZE(ped_model));
		components::input_text_with_hint("##vehmodel", "Vehicle model", veh_model, IM_ARRAYSIZE(veh_model));
		components::input_text_with_hint("##weapmodel", "Weapon model", weap_model, IM_ARRAYSIZE(weap_model));

		if (ImGui::BeginCombo("Spawn distance", spawn_distance_modes[(int)spawn_distance_mode]))
		{
			for (int i = 0; i < 5; i++)
			{
				if (ImGui::Selectable(spawn_distance_modes[i], (int)spawn_distance_mode == i))
					spawn_distance_mode = (eSquadSpawnDistance)i;
			}
			ImGui::EndCombo();
		}

		ImGui::SliderInt("Squad size", &squad_size, 1, 8);

		components::button("Spawn squad", [] {
			squad_spawner::spawn_squad({name, ped_model, weap_model, veh_model, squad_size, false, false, ped_proofs, 0, 0, 0, 50.f, spawn_distance_mode, eCombatAbilityLevel::AVERAGE},
			    g_player_service->get_selected(),
			    false,
			    {});
		});
	}

}