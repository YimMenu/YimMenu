#include "services/gta_data/gta_data_service.hpp"
#include "services/orbital_drone/orbital_drone.hpp"
#include "services/squad_spawner/squad_spawner.hpp"
#include "services/vehicle/persist_car_service.hpp"
#include "views/view.hpp"

namespace big
{

	void view::squad_spawner()
	{
		const char* const spawn_distance_modes[5]{"CUSTOM"_T.data(),
		    "VIEW_SQUAD_SPAWNER_ON_TARGET"_T.data(),
		    "VIEW_SQUAD_SPAWNER_NEARBY"_T.data(),
		    "VIEW_SQUAD_SPAWNER_MODERATELY_DISTANCED"_T.data(),
		    "VIEW_SQUAD_SPAWNER_FAR_AWAY"_T.data()};
		const char* const combat_ability_levels[3]{"VIEW_SQUAD_SPAWNER_POOR"_T.data(),
		    "VIEW_SQUAD_SPAWNER_AVERAGE"_T.data(),
		    "VIEW_SQUAD_SPAWNER_PROFESSIONAL"_T.data()};

		static squad new_template{};
		static player_ptr victim = g_player_service->get_selected();


		ImGui::SeparatorText("VIEW_SQUAD_SPAWNER_VICTIM"_T.data());
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
			ImGui::Text("VIEW_SQUAD_SPAWNER_WARNING"_T.data());
			ImGui::PopStyleColor();
		}

		ImGui::Separator();

		static squad deletion_squad;

		if (!std::string(deletion_squad.m_name).empty())
			ImGui::OpenPopup("##deletesquad");

		if (ImGui::BeginPopupModal("##deletesquad"))
		{
			ImGui::Text("VIEW_SELF_ANIMATIONS_ARE_YOU_SURE_DELETE"_T.data(), deletion_squad.m_name);

			if (ImGui::Button("YES"_T.data()))
			{
				g_squad_spawner_service.delete_squad(deletion_squad);
				deletion_squad.m_name = "";
				ImGui::CloseCurrentPopup();
			}
			ImGui::SameLine();
			if (ImGui::Button("NO"_T.data()))
			{
				deletion_squad.m_name = "";
				ImGui::CloseCurrentPopup();
			}

			ImGui::EndPopup();
		}


		ImGui::SetNextItemWidth(200);
		if (ImGui::BeginCombo("VIEW_SQUAD_SPAWNER_CHOOSE_FROM_TEMPLATES"_T.data(), "VIEW_SQUAD_SPAWNER_TEMPLATES"_T.data()))
		{
			components::button("VIEW_SQUAD_SPAWNER_FETCH_CUSTOM_SQUADS"_T, [] {
				g_squad_spawner_service.fetch_squads();
			});

			for (auto& temp : g_squad_spawner_service.m_templates)
			{
				if (ImGui::Selectable(temp.m_name.data()))
				{
					if (GetAsyncKeyState(VK_SHIFT) & 0x8000)
					{
						deletion_squad = temp;
					}
					else
					{
						new_template = temp;
					}
				}
				if (ImGui::IsItemHovered() && temp.does_squad_have_description())
					ImGui::SetTooltip(temp.m_description.data());
			}
			ImGui::EndCombo();
		}
		if (ImGui::IsItemHovered())
			ImGui::SetTooltip("VIEW_SELF_ANIMATIONS_DOUBLE_SHIFT_CLICK_TO_DELETE"_T.data());

		ImGui::SeparatorText("VIEW_SQUAD_SPAWNER_SQUAD_DETAILS"_T.data());

		ImGui::BeginGroup(); //Main variables
		ImGui::Spacing();

		ImGui::PushItemWidth(250);

		components::input_text_with_hint("##name", "NAME"_T, new_template.m_name);
		components::input_text_with_hint("##pedmodel", "PED_MODEL"_T, new_template.m_ped_model);

		auto ped_found = std::find_if(g_gta_data_service.peds().begin(), g_gta_data_service.peds().end(), [=](const auto& pair) {
			return pair.second.m_name == new_template.m_ped_model;
		});

		if (!new_template.m_ped_model.empty() && ped_found == g_gta_data_service.peds().end())
		{
			if (ImGui::BeginListBox("##pedlist", ImVec2(250, 200)))
			{
				for (auto& p : g_gta_data_service.peds() | std::ranges::views::values)
				{
					std::string p_model = p.m_name;
					std::string filter  = new_template.m_ped_model;
					std::transform(p_model.begin(), p_model.end(), p_model.begin(), ::tolower);
					std::transform(filter.begin(), filter.end(), filter.begin(), ::tolower);
					if (p_model.find(filter) != std::string::npos && ImGui::Selectable(p.m_name))
					{
						new_template.m_ped_model = p.m_name;
					}
				}

				ImGui::EndListBox();
			}
		}

		components::input_text_with_hint("##vehmodel", "NAME_VEHICLE_MODEL"_T, new_template.m_vehicle_model);
		if (ImGui::IsItemHovered())
			ImGui::SetTooltip("VIEW_SQUAD_SPAWNER_VEHICLE_TOOLTIP"_T.data());

		auto veh_found = std::find_if(g_gta_data_service.vehicles().begin(), g_gta_data_service.vehicles().end(), [=](const auto& pair) {
			return pair.second.m_name == new_template.m_vehicle_model;
		});

		if (!new_template.m_vehicle_model.empty() && veh_found == g_gta_data_service.vehicles().end())
		{
			if (ImGui::BeginListBox("##vehlist", ImVec2(250, 200)))
			{
				for (auto& p : g_gta_data_service.vehicles() | std::ranges::views::values)
				{
					std::string p_model = p.m_name;
					std::string filter  = new_template.m_vehicle_model;
					std::transform(p_model.begin(), p_model.end(), p_model.begin(), ::tolower);
					std::transform(filter.begin(), filter.end(), filter.begin(), ::tolower);
					if (p_model.find(filter) != std::string::npos && ImGui::Selectable(p.m_name))
					{
						new_template.m_vehicle_model = p.m_name;
					}
				}

				ImGui::EndListBox();
			}
		}

		components::input_text_with_hint("##weapmodel", "VIEW_SQUAD_SPAWNER_WEAPON_MODEL"_T.data(), new_template.m_weapon_model);
		if (ImGui::IsItemHovered())
			ImGui::SetTooltip("VIEW_SQUAD_SPAWNER_WEAPON_MODEL_TOOLTIP"_T.data());

		auto weap_found = std::find_if(g_gta_data_service.weapons().begin(), g_gta_data_service.weapons().end(), [=](const auto& pair) {
			return pair.second.m_name == new_template.m_weapon_model;
		});

		if (!new_template.m_weapon_model.empty() && weap_found == g_gta_data_service.weapons().end())
		{
			if (ImGui::BeginListBox("##weaplist", ImVec2(250, 200)))
			{
				for (auto& p : g_gta_data_service.weapons() | std::ranges::views::values)
				{
					std::string p_model = p.m_name;
					std::string filter  = new_template.m_weapon_model;
					std::transform(p_model.begin(), p_model.end(), p_model.begin(), ::tolower);
					std::transform(filter.begin(), filter.end(), filter.begin(), ::tolower);
					if (p_model.find(filter) != std::string::npos && ImGui::Selectable(p.m_name.c_str()))
					{
						new_template.m_weapon_model = p.m_name;
					}
				}

				ImGui::EndListBox();
			}
		}

		ImGui::Spacing();
		ImGui::Text("VIEW_SELF_CUSTOM_TELEPORT_DISTANCE"_T.data());
		if (ImGui::BeginCombo("##spawndistance", spawn_distance_modes[(int)new_template.m_spawn_distance_mode]))
		{
			for (int i = 0; i < 5; i++)
			{
				if (ImGui::Selectable(spawn_distance_modes[i], (int)new_template.m_spawn_distance_mode == i))
					new_template.m_spawn_distance_mode = (eSquadSpawnDistance)i;
			}
			ImGui::EndCombo();
		}
		ImGui::Text("VIEW_DEBUG_GLOBAL_SIZE"_T.data());
		ImGui::SliderInt("##squadsize", &new_template.m_squad_size, 1, 8);
		ImGui::PopItemWidth();

		ImGui::EndGroup();
		ImGui::SameLine();
		ImGui::BeginGroup(); //General actions

		ImGui::Text("VIEW_SQUAD_SPAWNER_ACTIONS"_T.data());
		ImGui::Spacing();
		components::button(
		    std::format("{} {} {}", "SETTINGS_NOTIFY_GTA_THREADS_TERMINATE"_T, g_squad_spawner_service.m_active_squads.size(), "VIEW_SQUAD_SPAWNER_SQUADS"_T),
		    [] {
			    g_squad_spawner_service.terminate_squads();
		    });

		components::button("VIEW_SQUAD_RESET_FIELDS"_T, [] {
			new_template.m_spawn_distance_mode  = eSquadSpawnDistance::CLOSEBY;
			new_template.m_combat_ability_level = eCombatAbilityLevel::AVERAGE;
			new_template.m_name.clear();
			new_template.m_description.clear();
			new_template.m_ped_model.clear();
			new_template.m_vehicle_model.clear();
			new_template.m_weapon_model.clear();
			new_template.m_persistent_vehicle = "VIEW_SQUAD_SPAWN_PERSISTENT_VEHICLE_NONE"_T.data();
			new_template.m_squad_size         = 1;
			new_template.m_ped_invincibility  = 0;
			new_template.m_veh_invincibility  = 0;
			new_template.m_ped_health         = 0;
			new_template.m_ped_armor          = 0;
			new_template.m_ped_accuracy       = 50;
			new_template.m_spawn_distance     = 0;
			for (int i = 0; i < sizeof(new_template.m_ped_proofs) / sizeof(new_template.m_ped_proofs[0]); i++)
				new_template.m_ped_proofs[i] = false;
			new_template.m_stay_in_veh                = 0;
			new_template.m_spawn_behind_same_velocity = 0;
			new_template.m_disperse                   = 0;
			new_template.m_spawn_ahead                = 0;
			new_template.m_favour_roads               = 0;
			new_template.m_max_vehicle                = 0;
		});

		ImGui::EndGroup();
		ImGui::Spacing();
		if (ImGui::TreeNode("VIEW_SELF_ANIMATIONS_ADVANCED_OPTIONS"_T.data()))
		{
			ImGui::BeginGroup(); //Toggleables

			ImGui::Checkbox("VIEW_SQUAD_SPAWN_AHEAD"_T.data(), &new_template.m_spawn_ahead);
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip("VIEW_SQUAD_SPAWN_AHEAD_TOOLTIP"_T.data());
			ImGui::Checkbox("VIEW_SQUAD_SPAWN_FAVOR_ROADS"_T.data(), &new_template.m_favour_roads);
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip("VIEW_SQUAD_SPAWN_FAVOR_ROADS_TOOLTIP"_T.data());
			ImGui::Checkbox("VIEW_SQUAD_SPAWN_DISPERSE"_T.data(), &new_template.m_disperse);
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip("VIEW_SQUAD_SPAWN_DISPERSE_TOOLTIP"_T.data());
			ImGui::Checkbox("VIEW_SQUAD_SPAWN_VEHICLE_CATCH_UP"_T.data(), &new_template.m_spawn_behind_same_velocity);
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip("VIEW_SQUAD_SPAWN_VEHICLE_CATCH_UP_TOOLTIP"_T.data());
			ImGui::Checkbox("VIEW_SQUAD_SPAWN_STAY_IN_VEHICLE"_T.data(), &new_template.m_stay_in_veh);
			ImGui::Checkbox("MAX_VEHICLE"_T.data(), &new_template.m_max_vehicle);

			ImGui::EndGroup();
			ImGui::SameLine();
			ImGui::BeginGroup();

			ImGui::Checkbox("GOD_MODE"_T.data(), &new_template.m_ped_invincibility);
			ImGui::Checkbox("VEHICLE_GOD"_T.data(), &new_template.m_veh_invincibility);
			ImGui::Checkbox("VIEW_SQUAD_SPAWN_HEADSHOT_PROOF"_T.data(), &new_template.m_ped_proofs[0]);
			ImGui::Checkbox("VIEW_SQUAD_SPAWN_BULLET_PROOF"_T.data(), &new_template.m_ped_proofs[1]);
			ImGui::Checkbox("VIEW_SQUAD_SPAWN_FLAME_PROOF"_T.data(), &new_template.m_ped_proofs[2]);
			ImGui::Checkbox("VIEW_SQUAD_SPAWN_MELEE_PROOF"_T.data(), &new_template.m_ped_proofs[3]);
			ImGui::Checkbox("VIEW_SQUAD_SPAWN_EXPLOSION_PROOF"_T.data(), &new_template.m_ped_proofs[4]);

			ImGui::EndGroup();
			ImGui::SameLine();
			ImGui::BeginGroup(); //Slideables

			ImGui::PushItemWidth(200);
			ImGui::Text("VIEW_PLAYER_INFO_HEALTH"_T.data());
			ImGui::SliderFloat("##pedhealth", &new_template.m_ped_health, 0, 2000);
			ImGui::Text("VIEW_SQUAD_SPAWN_ARMOR"_T.data());
			ImGui::SliderFloat("##pedarmor", &new_template.m_ped_armor, 0, 2000);
			ImGui::Text("VIEW_SQUAD_SPAWN_ACCURACY"_T.data());
			ImGui::SliderFloat("##pedaccuracy", &new_template.m_ped_accuracy, 0, 100);
			ImGui::Text("VIEW_SELF_CUSTOM_TELEPORT_DISTANCE"_T.data());
			ImGui::SliderFloat("##customspawndistance", &new_template.m_spawn_distance, 0, 500);
			ImGui::EndGroup();
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip("VIEW_SQUAD_SPAWN_DEFAULT_TOOLTIP"_T.data());

			ImGui::SameLine();
			ImGui::BeginGroup(); //Chooseables
			ImGui::Text("VIEW_SQUAD_SPAWN_COMBAT_ABILITY"_T.data());
			if (ImGui::BeginCombo("##combatability", combat_ability_levels[(int)new_template.m_combat_ability_level]))
			{
				for (int i = 0; i < 3; i++)
				{
					if (ImGui::Selectable(combat_ability_levels[i], (int)new_template.m_combat_ability_level == i))
						new_template.m_combat_ability_level = (eCombatAbilityLevel)i;
				}
				ImGui::EndCombo();
			}

			ImGui::Text("VIEW_SQUAD_SPAWN_PERSISTENT_VEHICLE"_T.data());
			if (ImGui::BeginCombo("##persistent_vehicle", new_template.m_persistent_vehicle.data()))
			{
				if (ImGui::Selectable("VIEW_SQUAD_SPAWN_PERSISTENT_VEHICLE_NONE"_T.data(),
				        new_template.m_persistent_vehicle == "VIEW_SQUAD_SPAWN_PERSISTENT_VEHICLE_NONE"_T.data()))
					new_template.m_persistent_vehicle = "VIEW_SQUAD_SPAWN_PERSISTENT_VEHICLE_NONE"_T.data();
				for (auto& p : persist_car_service::list_files())
				{
					if (ImGui::Selectable(p.data(), p == new_template.m_persistent_vehicle))
						new_template.m_persistent_vehicle = p;
				}
				ImGui::EndCombo();
			}
			ImGui::PopItemWidth();
			ImGui::EndGroup();

			components::input_text_with_hint("##new_template.m_description",
			    "VIEW_SQUAD_SPAWN_DESCRIPTION"_T,
			    new_template.m_description);

			ImGui::TreePop();
		}

		static auto check_validity = [=](bool save) -> bool {
			if (!victim->is_valid() && !save)
			{
				g_notification_service.push_error("GUI_TAB_SQUAD_SPAWNER"_T.data(), "VIEW_SQUAD_SPAWN_CHOOSE_FIRST"_T.data());
				return false;
			}
			if (std::string(new_template.m_ped_model).empty())
			{
				g_notification_service.push_error("GUI_TAB_SQUAD_SPAWNER"_T.data(), "VIEW_SQUAD_SPAWN_MODEL_REQUIRED"_T.data());
				return false;
			}

			return true;
		};

		static auto check_if_exists = [=](std::string squad_name) -> bool {
			bool exists = false;

			for (auto& s : g_squad_spawner_service.m_templates)
			{
				if (s.m_name.compare(squad_name) == 0)
				{
					exists = true;
					break;
				}
			}

			return exists;
		};

		components::button("VIEW_SQUAD_SPAWN_SPAWN_SQUAD"_T, [] {
			try
			{
				if (check_validity(false))
					g_squad_spawner_service.spawn_squad({new_template.m_name,
					                                        new_template.m_ped_model,
					                                        new_template.m_weapon_model,
					                                        new_template.m_vehicle_model,
					                                        new_template.m_squad_size,
					                                        new_template.m_ped_invincibility,
					                                        new_template.m_veh_invincibility,
					                                        new_template.m_ped_proofs,
					                                        new_template.m_ped_health,
					                                        new_template.m_ped_armor,
					                                        new_template.m_spawn_distance,
					                                        new_template.m_ped_accuracy,
					                                        new_template.m_spawn_distance_mode,
					                                        new_template.m_combat_ability_level,
					                                        new_template.m_stay_in_veh,
					                                        new_template.m_spawn_behind_same_velocity,
					                                        new_template.m_description,
					                                        new_template.m_disperse,
					                                        new_template.m_spawn_ahead,
					                                        new_template.m_favour_roads,
					                                        new_template.m_max_vehicle,
					                                        new_template.m_persistent_vehicle},
					    victim,
					    new_template.m_spawn_distance_mode == eSquadSpawnDistance::CUSTOM,
					    g_orbital_drone_service.m_ground_pos);
			}
			catch (std::exception e)
			{
				LOG(WARNING) << "Exception while spawning squad " << e.what();
			}
		});

		ImGui::SameLine();
		components::button("SAVE"_T, [] {
			if (check_validity(true) && !check_if_exists(new_template.m_name))
				g_squad_spawner_service.save_squad(new_template);
		});
	}
}
