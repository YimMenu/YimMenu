#include "views/view.hpp"
#include "util/teleport.hpp"
#include "util/toxic.hpp"
#include "util/ped.hpp"
#include "util/vehicle.hpp"
#include "core/data/apartment_names.hpp"
#include "core/data/warehouse_names.hpp"

namespace big
{
	void view::view_player_toxic()
	{
		std::string title = std::format("Player Toxic Options: {}", g_player_service->get_selected()->get_name());

		ImGui::Text(title.c_str());

		components::button("Kill Player", []
		{
			toxic::kill_player(g_player_service->get_selected(), g_player_service->get_self());
		});
		components::button("CEO Kick", [] { toxic::ceo_kick(g_player_service->get_selected()); });
		ImGui::SameLine();
		components::button("CEO Ban", [] { toxic::ceo_ban(g_player_service->get_selected()); });
		
		components::button("Ragdoll Player", [] { toxic::ragdoll_player(g_player_service->get_selected()); });
		ImGui::SameLine();
		components::button("Ragdoll Player Old", [] { toxic::ragdoll_player_old(g_player_service->get_selected()); });
		ImGui::SameLine(); components::help_marker("Spawns an invisible fire hydrant below player. \nBlocked by using 'no ragdoll' or 'godmode'.");

		components::button("Kick From Interior", [] { toxic::kick_player_from_interior(g_player_service->get_selected()); });
		components::button("Turn Into Animal", [] { toxic::turn_player_into_animal(g_player_service->get_selected()); });
		ImGui::SameLine(); components::help_marker("Gives player a lot of jack o lanterns and eventually turns them into a random animal. \nBlocked by most internal menus.");
		ImGui::SameLine();
		components::button("Turn Into Beast", [] { toxic::turn_player_into_beast(g_player_service->get_selected()); });
		components::button("Clear Tasks", [] 
		{
			TASK::CLEAR_PED_TASKS_IMMEDIATELY(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_player_service->get_selected()->id()));
		});
		ImGui::SameLine(); components::help_marker("Stops any task player ped is doing. \nBlocked by most internal menus.");
		static int wanted_level;
		ImGui::SliderInt("Wanted Level", &wanted_level, 0, 5);
		ImGui::SameLine();
		components::button("Set", [] { toxic::set_wanted_level(g_player_service->get_selected(), wanted_level); });
		
		if (ImGui::TreeNode("Teleports"))
		{
			if (ImGui::BeginCombo("##apartment", apartment_names[g->session.send_to_apartment_idx]))
			{
				for (int i = 1; i < apartment_names.size(); i++)
				{
					if (ImGui::Selectable(apartment_names[i], i == g->session.send_to_apartment_idx))
					{
						g->session.send_to_apartment_idx = i;
					}
					if (i == g->session.send_to_apartment_idx)
					{
						ImGui::SetItemDefaultFocus();
					}
				}
				ImGui::EndCombo();
			}
			ImGui::SameLine();
			components::button("TP To Apartment", [] { toxic::send_player_to_apartment(g_player_service->get_selected(), g->session.send_to_apartment_idx); });
			if (ImGui::BeginCombo("##warehouse", warehouse_names[g->session.send_to_warehouse_idx]))
			{
				for (int i = 1; i < warehouse_names.size(); i++)
				{
					if (ImGui::Selectable(warehouse_names[i], i == g->session.send_to_warehouse_idx))
					{
						g->session.send_to_warehouse_idx = i;
					}
					if (i == g->session.send_to_warehouse_idx)
					{
						ImGui::SetItemDefaultFocus();
					}
				}
				ImGui::EndCombo();
			}
			ImGui::SameLine();
			components::button("TP To Warehouse", [] { toxic::send_player_to_warehouse(g_player_service->get_selected(), g->session.send_to_warehouse_idx); });
			components::button("TP To Darts", [] { toxic::start_activity(g_player_service->get_selected(), eActivityType::Darts); });
			ImGui::SameLine();
			components::button("TP To Flight School", [] { toxic::start_activity(g_player_service->get_selected(), eActivityType::PilotSchool); });
			ImGui::SameLine();
			components::button("TP To Map Center", [] { toxic::start_activity(g_player_service->get_selected(), eActivityType::ArmWresling); });
			components::button("TP To Skydive", [] { toxic::start_activity(g_player_service->get_selected(), eActivityType::Skydive); });
			ImGui::SameLine();
			components::button("TP To Cayo Perico", [] { toxic::send_player_to_island(g_player_service->get_selected()); });
			ImGui::SameLine();
			components::button("TP To MOC", [] { toxic::send_player_to_interior(g_player_service->get_selected(), 81); });
			components::button("TP To Casino", [] { toxic::send_player_to_interior(g_player_service->get_selected(), 123); });
			ImGui::SameLine();
			components::button("TP To Penthouse", [] { toxic::send_player_to_interior(g_player_service->get_selected(), 124); });
			ImGui::SameLine();
			components::button("TP To Arcade", [] { toxic::send_player_to_interior(g_player_service->get_selected(), 128); });
			components::button("TP To Music Locker", [] { toxic::send_player_to_interior(g_player_service->get_selected(), 146); });
			ImGui::SameLine();
			components::button("TP To Record A Studios", [] { toxic::send_player_to_interior(g_player_service->get_selected(), 148); });
			ImGui::SameLine();
			components::button("TP To Custom Auto Shop", [] { toxic::send_player_to_interior(g_player_service->get_selected(), 149); });
			components::button("TP To Agency", [] { toxic::send_player_to_interior(g_player_service->get_selected(), 155); });
			ImGui::TreePop();
		}

		if (ImGui::TreeNode("Vehicle")) 
		{
			components::button("Kick From Vehicle", [] { toxic::kick_player_from_vehicle(g_player_service->get_selected()); });

			components::button("Full Acceleration", [] { toxic::full_acceleration(g_player_service->get_selected()); });
			ImGui::SameLine(); components::help_marker("Accelerates players vehicle to max speed. \nRequires entity control. \nBlacked by most internal menus.");

			components::button("Launch Vehicle Up", [] { toxic::flying_vehicle(g_player_service->get_selected()); });
			ImGui::SameLine(); components::help_marker("Launches players vehicle up. \nRequires entity control. \nBlacked by most internal menus.\nUses max sync speed on other players, uses INT32_MAX on local player.");

			components::button("Repair Vehicle", [] {
				Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(g_player_service->get_selected()->id(), false);
				vehicle::repair(veh);
			});
			ImGui::SameLine(); components::help_marker("Repairs players vehicle. \nRequires entity control. \nBlacked by most internal menus.");
			ImGui::TreePop();
		}

		if (ImGui::TreeNode("Spawns")) // TODO: Clean this up.
		{
			components::button("Spawn Griefer Jesus", [] {
				Ped player_ped = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_player_service->get_selected()->id());
				Vector3 pos = ENTITY::GET_ENTITY_COORDS(player_ped, true) + Vector3(0, 0, 10);
				ped::spawn_griefer_jesus(pos, player_ped);
			});
			ImGui::SameLine(); components::help_marker("Spawns 'Griefer Jesus' just like in ChaosMod.");
			ImGui::SameLine();

			components::button("Spawn Extreme Griefer Jesus", [] {
				Ped player_ped = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_player_service->get_selected()->id());
				Vector3 pos = ENTITY::GET_ENTITY_COORDS(player_ped, true) + Vector3(0, 0, 10);

				ped::spawn_extrime_griefer_jesus(pos, player_ped);
			});
			ImGui::SameLine(); components::help_marker("Spawns 'Extreme Griefer Jesus' just like in ChaosMod.");

			components::button("Spawn Griefer Lazer", [] {
				Ped player_ped = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_player_service->get_selected()->id());
				Vector3 pos = ENTITY::GET_ENTITY_COORDS(player_ped, true) + Vector3(0, 0, 500);
				Hash jet_hash RAGE_JOAAT("lazer");
				ped::spawn_griefer_jet(pos, player_ped, jet_hash);
			});
			ImGui::SameLine(); components::help_marker("Spawns a lazer with Griefer Jesus in it.");

			ImGui::TreePop();
		}

		components::button("Give All Weapons", [] { toxic::give_all_weapons(g_player_service->get_selected()); });
		ImGui::SameLine();
		components::button("Remove All Weapons", [] { toxic::remove_all_weapons(g_player_service->get_selected()); });
	}
}