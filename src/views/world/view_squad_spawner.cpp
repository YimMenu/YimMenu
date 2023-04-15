#include "services/squad_spawner/squad_spawner.hpp"
#include "views/view.hpp"

namespace big
{

	void view::squad_spawner()
	{
		const char* const spawn_distance_modes[5]{"Custom", "On target", "Closeby", "Moderately distanced", "Far away"};
		const char* const combat_ability_levels[3]{"Poor", "Average", "Professional"};


		static player_ptr victim = g_player_service->get_selected();

		static eSquadSpawnDistance spawn_distance_mode  = eSquadSpawnDistance::CLOSEBY;
		static eCombatAbilityLevel combat_ability_level = eCombatAbilityLevel::AVERAGE;

		static char name[32];
		static char ped_model[32];
		static char veh_model[32];
		static char weap_model[32];
		
		static float ped_accuracy = 50.f;
		static bool ped_invincibility;
		static bool veh_invincibility;

		static float ped_health;
		static float ped_armor;
	
		static float custom_spawn_distance;
		static int squad_size = 1;
		static bool ped_proofs[5];

		ImGui::SetNextItemWidth(200);
		if (ImGui::BeginCombo("Victim", victim->get_name()))
		{
			auto self = g_player_service->get_self();
			if (ImGui::Selectable(self->get_name(), self->id() == victim->id()))
					victim = self;
			for (auto p : g_player_service->players() | std::ranges::views::values)
			{
				if (ImGui::Selectable(p->get_name(), p->id() == victim->id()))
					victim = p;
			}
			ImGui::EndCombo();
		}
		ImGui::SameLine();
		if(ImGui::Button("Get selected")){
			victim = g_player_service->get_selected();
		}

		ImGui::Separator();

		ImGui::BeginGroup();//Main variables
		ImGui::SetNextItemWidth(200);
		if (ImGui::BeginCombo("", "Templates"))
		{
			
			for (auto temp : g_squad_spawner_service.m_templates)
			{
				if (ImGui::Selectable(temp.m_name)){

					

					spawn_distance_mode = temp.m_spawn_distance_mode;
					combat_ability_level = temp.m_combat_ability_level;
					strcpy(name, temp.m_name);
					strcpy(ped_model, temp.m_ped_model);
					strcpy(veh_model, temp.m_vehicle_model);
					strcpy(weap_model, temp.m_weapon_model);
					squad_size = temp.m_squad_size;
					ped_invincibility = temp.m_ped_invincibility;
					veh_invincibility = temp.m_veh_invincibility;
					ped_health = temp.m_ped_health;
					ped_armor = temp.m_ped_armor;
					ped_accuracy = temp.m_ped_accuracy;
					custom_spawn_distance = temp.m_spawn_distance;
					std::copy(std::begin(temp.m_ped_proofs), std::end(temp.m_ped_proofs), ped_proofs);
					//memcpy(ped_proofs, temp.m_ped_proofs, sizeof(temp.m_ped_proofs));
				}
			}
			ImGui::EndCombo();
		}

		ImGui::PushItemWidth(200);
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
		ImGui::PopItemWidth();

		ImGui::EndGroup();
		ImGui::SameLine();
		ImGui::BeginGroup();//General actions

		components::button("Terminate squads", []{
			g_squad_spawner_service.terminate_squads();
		});

		ImGui::EndGroup();

		if (ImGui::TreeNode("Advanced options"))
		{
			ImGui::BeginGroup(); //Toggleables

			ImGui::Checkbox("Ped god mode", &ped_invincibility);
			ImGui::Checkbox("Vehicle god mode", &veh_invincibility);
			ImGui::Checkbox("Headshot proof", &ped_proofs[0]);
			ImGui::Checkbox("Bullet proof", &ped_proofs[1]);
			ImGui::Checkbox("Flame proof", &ped_proofs[2]);
			ImGui::Checkbox("Melee proof", &ped_proofs[3]);
			ImGui::Checkbox("Explosion proof", &ped_proofs[4]);

			ImGui::EndGroup();
			ImGui::SameLine();
			ImGui::BeginGroup(); //Slideables
			ImGui::PushItemWidth(200);
			ImGui::Text("Ped health");
			ImGui::SliderFloat("##pedhealth", &ped_health, 100, 2000);
			ImGui::Text("Ped armor");
			ImGui::SliderFloat("##pedarmor", &ped_health, 0, 2000);
			ImGui::Text("Ped accuracy");
			ImGui::SliderFloat("##pedaccuracy", &ped_accuracy, 0, 100);
			ImGui::Text("Custom spawn distance");
			ImGui::SliderFloat("##customspawndistance", &custom_spawn_distance, 10, 500);
			ImGui::EndGroup();
			if(ImGui::IsItemHovered())
				ImGui::SetTooltip("Leave these values at 0 to default, except for accuracy");

			ImGui::SameLine();
			ImGui::BeginGroup(); //Chooseables
			ImGui::Text("Combat ability");
			if (ImGui::BeginCombo("##combatability", combat_ability_levels[(int)combat_ability_level]))
			{
				for (int i = 0; i < 3; i++)
				{
					if (ImGui::Selectable(combat_ability_levels[i], (int)combat_ability_level == i))
						combat_ability_level = (eCombatAbilityLevel)i;
				}
				ImGui::EndCombo();
			}
			ImGui::PopItemWidth();
			ImGui::EndGroup();

			ImGui::TreePop();
		}

		components::button("Spawn squad", [] {
			g_squad_spawner_service.spawn_squad({name, ped_model, weap_model, veh_model, squad_size, ped_invincibility, veh_invincibility, ped_proofs, ped_health, ped_armor, custom_spawn_distance, ped_accuracy, spawn_distance_mode, combat_ability_level},
			    victim,
			    false,
			    {});
		});
	}

}