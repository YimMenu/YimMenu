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
		static char description[500];
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
		static bool stay_in_veh                = false;
		static bool spawn_behind_same_velocity = false;

		ImGui::Text("Victim");
		ImGui::SetNextItemWidth(200);
		if (ImGui::BeginCombo("##victim", victim->get_name()))
		{
			auto self = g_player_service->get_self();
			if (ImGui::Selectable(self->get_name(), self->id() == victim->id()))
				victim = self;
			for (auto p : g_player_service->players() | std::ranges::views::values)
			{
				if (ImGui::Selectable(p->get_name(), p->id() == victim->id()))
				{
					victim = p;
					if (g.player.spectating)
						g_player_service->set_selected(victim);
				}
			}
			ImGui::EndCombo();
		}

		ImGui::SameLine();

		if (ImGui::Checkbox("SPECTATE"_T.data(), &g.player.spectating))
		{
			g_player_service->set_selected(victim);
		};

		if (victim->id() != g_player_service->get_selected()->id() && victim->is_valid())
		{
			ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 0.5f, 0.3f, 1.0f));
			ImGui::Text("Warning: Victim and selected player are not the same");
			ImGui::PopStyleColor();
			ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.0f, 0.5f, 0.0f, 1.0f));
			if (ImGui::Button("Victim = selected"))
			{
				victim = g_player_service->get_selected();
			}
			ImGui::PopStyleColor();
			ImGui::SameLine();
			ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.0f, 0.0f, 0.5f, 1.0f));
			if (ImGui::Button("Selected = victim"))
			{
				g_player_service->set_selected(victim);
			}
			ImGui::PopStyleColor();
		}

		ImGui::Separator();

		static squad deletion_squad;

		if (!std::string(deletion_squad.m_name).empty())
			ImGui::OpenPopup("##deletesquad");

		if (ImGui::BeginPopupModal("##deletesquad"))
		{
			ImGui::Text("Are you sure you want to delete %s?", deletion_squad.m_name);

			if (ImGui::Button("Yes"))
			{
				g_squad_spawner_service.delete_squad(deletion_squad);
				strcpy(deletion_squad.m_name, "");
				ImGui::CloseCurrentPopup();
			}
			ImGui::SameLine();
			if (ImGui::Button("No"))
			{
				strcpy(deletion_squad.m_name, "");
				ImGui::CloseCurrentPopup();
			}

			ImGui::EndPopup();
		}


		ImGui::SetNextItemWidth(200);
		if (ImGui::BeginCombo("Choose from templates", "Templates"))
		{
			components::button("Fetch custom squads", [] {
				g_squad_spawner_service.fetch_squads();
			});

			for (auto& temp : g_squad_spawner_service.m_templates)
			{
				if (ImGui::Selectable(temp.m_name))
				{
					if (GetAsyncKeyState(VK_SHIFT) & 0x8000)
					{
						deletion_squad = temp;
					}
					else
					{
						spawn_distance_mode  = temp.m_spawn_distance_mode;
						combat_ability_level = temp.m_combat_ability_level;
						strcpy(name, temp.m_name);
						strcpy(description, temp.m_description);
						strcpy(ped_model, temp.m_ped_model);
						strcpy(veh_model, temp.m_vehicle_model);
						strcpy(weap_model, temp.m_weapon_model);
						squad_size            = temp.m_squad_size;
						ped_invincibility     = temp.m_ped_invincibility;
						veh_invincibility     = temp.m_veh_invincibility;
						ped_health            = temp.m_ped_health;
						ped_armor             = temp.m_ped_armor;
						ped_accuracy          = temp.m_ped_accuracy;
						custom_spawn_distance = temp.m_spawn_distance;
						std::copy(std::begin(temp.m_ped_proofs), std::end(temp.m_ped_proofs), ped_proofs);
						stay_in_veh                = temp.m_stay_in_veh;
						spawn_behind_same_velocity = temp.m_spawn_behind_same_velocity;
					}
				}
				if (ImGui::IsItemHovered() && temp.does_squad_have_description())
					ImGui::SetTooltip(temp.m_description);
			}
			ImGui::EndCombo();
		}

		ImGui::Separator();

		ImGui::BeginGroup(); //Main variables

		ImGui::Text("Squad Details");
		ImGui::Spacing();


		ImGui::PushItemWidth(200);
		components::input_text_with_hint("##name", "Squad name", name, IM_ARRAYSIZE(name));
		components::input_text_with_hint("##pedmodel", "Ped model", ped_model, IM_ARRAYSIZE(ped_model));
		components::input_text_with_hint("##vehmodel", "Vehicle model", veh_model, IM_ARRAYSIZE(veh_model));
		if (ImGui::IsItemHovered())
			ImGui::SetTooltip("Leave empty to spawn on foot");

		components::input_text_with_hint("##weapmodel", "Weapon model", weap_model, IM_ARRAYSIZE(weap_model));

		ImGui::Spacing();
		ImGui::Text("Spawn distance");
		if (ImGui::BeginCombo("##spawndistance", spawn_distance_modes[(int)spawn_distance_mode]))
		{
			for (int i = 0; i < 5; i++)
			{
				if (ImGui::Selectable(spawn_distance_modes[i], (int)spawn_distance_mode == i))
					spawn_distance_mode = (eSquadSpawnDistance)i;
			}
			ImGui::EndCombo();
		}
		ImGui::Text("Squad size");
		ImGui::SliderInt("##squadsize", &squad_size, 1, 8);
		ImGui::PopItemWidth();

		ImGui::EndGroup();
		ImGui::SameLine();
		ImGui::BeginGroup(); //General actions

		ImGui::Text("Actions");
		ImGui::Spacing();
		components::button(std::string("Terminate squads"), [] {
			g_squad_spawner_service.terminate_squads();
		});

		ImGui::EndGroup();
		ImGui::Spacing();
		if (ImGui::TreeNode("Advanced options"))
		{
			ImGui::BeginGroup(); //Toggleables

			ImGui::Checkbox("Vehicle catch up", &spawn_behind_same_velocity);
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip("Will spawn the mobile squad behind the target with identical velocity if applicable.\nOnly for squads with a vehicle.");
			ImGui::Checkbox("Stay in vehicle", &stay_in_veh);
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
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip("Leave these values at 0 to default, except for accuracy.");

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

			components::input_text_with_hint("##description", "Squad description", description, IM_ARRAYSIZE(description));

			ImGui::TreePop();
		}

		static auto check_validity = [=](bool save) -> bool {
			if (!victim->is_valid() && !save)
			{
				g_notification_service->push_error("Squad spawner", "Choose a victim first");
				return false;
			}
			if (std::string(ped_model).empty())
			{
				g_notification_service->push_error("Squad spawner", "A ped model is required");
				return false;
			}

			return true;
		};

		static auto check_if_exists = [=](const char* squad_name) -> bool {
			bool exists = false;

			for (auto& s : g_squad_spawner_service.m_templates)
			{
				if (strcmp(squad_name, s.m_name) == 0)
				{
					exists = true;
					break;
				}
			}

			return exists;
		};

		components::button("Spawn squad", [] {
			if (check_validity(false))
				g_squad_spawner_service.spawn_squad({name, ped_model, weap_model, veh_model, squad_size, ped_invincibility, veh_invincibility, ped_proofs, ped_health, ped_armor, custom_spawn_distance, ped_accuracy, spawn_distance_mode, combat_ability_level, stay_in_veh, spawn_behind_same_velocity, description}, victim, false, {});
		});
		ImGui::SameLine();
		components::button("Save", [] {
			if (check_validity(true) && !check_if_exists(name))
				g_squad_spawner_service.save_squad({name, ped_model, weap_model, veh_model, squad_size, ped_invincibility, veh_invincibility, ped_proofs, ped_health, ped_armor, custom_spawn_distance, ped_accuracy, spawn_distance_mode, combat_ability_level, stay_in_veh, spawn_behind_same_velocity, description});
		});
	}

}