#include "views/view.hpp"
#include "gta_util.hpp"
#include "services/pickups/pickup_service.hpp"
#include "services/players/player_service.hpp"
#include "services/anti_cheat/anti_cheat_service.hpp"
#include "util/globals.hpp"
#include "util/misc.hpp"
#include "util/ped.hpp"
#include "util/vehicle.hpp"
#include "util/teleport.hpp"
#include "util/toxic.hpp"
#include "gta/joaat.hpp"
#include "core/enums.hpp"

namespace big
{
	void view::view_player() {

		std::string title = fmt::format("Player Options: {}", g_player_service->get_selected()->get_name());
		
		ImGui::Text(title.c_str());
		ImGui::Checkbox("Spectate", &g->player.spectating);
		
		if (g_player_service->get_selected()->is_valid())
		{
			if (ImGui::TreeNode("Misc")) {
				components::button("Steal Outfit", [] {
					ped::steal_outfit(
						PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_player_service->get_selected()->id())
					);
				});

				ImGui::SameLine();

				components::button("Steal Identity", [] {
					ped::steal_identity(
						PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_player_service->get_selected()->id())
					);
				});

				components::button("Clear Wanted Level", [] {
					globals::clear_wanted_player(g_player_service->get_selected()->id());
				});

				ImGui::SameLine();

				ImGui::Checkbox("Never Wanted", &g_player_service->get_selected()->never_wanted);

				components::button("Give Health", [] {
					g_pickup_service->give_player_health(g_player_service->get_selected()->id());
				});

				ImGui::SameLine();

				components::button("Give Armour", [] {
					g_pickup_service->give_player_armour(g_player_service->get_selected()->id());
				});

				components::button("Give Ammo", [] {
					g_pickup_service->give_player_ammo(g_player_service->get_selected()->id());
				});

				ImGui::SameLine();

				components::button("Give Weapons", [] {
					g_pickup_service->give_player_weapons(g_player_service->get_selected()->id());
				});

				ImGui::TreePop();
			}

			if (ImGui::TreeNode("Info")) {

				ImGui::Text("Player ID: %d", g_player_service->get_selected()->id());

				ImGui::Text("Session Host: %s", g_player_service->get_selected()->is_host() ? "Yes" : "No");

				ImGui::Separator();

				if (CPlayerInfo* player_info = g_player_service->get_selected()->get_player_info(); player_info != nullptr)
				{
					ImGui::Text("Wanted Level: %d", player_info->m_wanted_level);
				}

				uint32_t ped_damage_bits = 0;
				uint32_t ped_task_flag = 0;
				uint32_t veh_damage_bits = 0;
				std::string mode_str = "";

				if (CPed* ped = g_player_service->get_selected()->get_ped(); ped != nullptr)
				{
					ped_damage_bits = ped->m_damage_bits;
					ped_task_flag = ped->m_ped_task_flag;
				}

				if (ped_damage_bits & (uint32_t)eEntityProofs::GOD)
				{
					mode_str = "God";
				}
				else
				{
					if (ped_damage_bits & (uint32_t)eEntityProofs::BULLET)
					{
						mode_str += "Bullet, ";
					}
					if (ped_damage_bits & (uint32_t)eEntityProofs::EXPLOSION)
					{
						mode_str += "Explosion, ";
					}
				}

				if (mode_str.empty())
				{
					mode_str = "No";
				}

				ImGui::Text("Player God Mode: %s", mode_str.c_str());

				mode_str = "";

				if (CAutomobile* vehicle = g_player_service->get_selected()->get_current_vehicle(); vehicle != nullptr)
				{
					veh_damage_bits = vehicle->m_damage_bits;
				}

				if (ped_task_flag & (uint8_t)ePedTask::TASK_DRIVING)
				{
					if (veh_damage_bits & (uint32_t)eEntityProofs::GOD)
					{
						mode_str = "God";
					}
					else
					{
						if (veh_damage_bits & (uint32_t)eEntityProofs::COLLISION)
						{
							mode_str += "Collision, ";
						}
						if (veh_damage_bits & (uint32_t)eEntityProofs::EXPLOSION)
						{
							mode_str += "Explosion, ";
						}
					}

					if (mode_str.empty())
					{
						mode_str = "No";
					}
				}
				else
				{
					mode_str = "No vehicle detected";
				}

				ImGui::Text("Vehicle God Mode: %s", mode_str.c_str());

				ImGui::Separator();

				if (rage::netPlayerData* net_player_data = g_player_service->get_selected()->get_net_data(); net_player_data != nullptr)
				{
					ImGui::Text("Rockstar ID: %d", net_player_data->m_rockstar_id);
					ImGui::Text(
						"IP Address: %d.%d.%d.%d:%d",
						net_player_data->m_external_ip.m_field1,
						net_player_data->m_external_ip.m_field2,
						net_player_data->m_external_ip.m_field3,
						net_player_data->m_external_ip.m_field4,
						net_player_data->m_external_port
					);

					if (g_anti_cheat_service->is_player_in_moddb(net_player_data->m_rockstar_id2)) {
						ImGui::Text("AC Score: %d", g_anti_cheat_service->modders()[g_anti_cheat_service->get_moddb_player_from_rid(net_player_data->m_rockstar_id2)].score);
					}
				}

				ImGui::Text("Level: %d", *script_global(1853348).at(g_player_service->get_selected()->id(), 834).at(205).at(6).as<int*>());

				ImGui::Text("Money Bank: %d", *script_global(1853348).at(g_player_service->get_selected()->id(), 834).at(205).at(56).as<int64_t*>());

				ImGui::Text("K/D Ratio: %f", *script_global(1853348).at(g_player_service->get_selected()->id(), 834).at(205).at(26).as<float*>());

				components::button("Open SC Overlay", [] {
					int gamerHandle;
					NETWORK::NETWORK_HANDLE_FROM_PLAYER(g_player_service->get_selected()->id(), &gamerHandle, 13);
					NETWORK::NETWORK_SHOW_PROFILE_UI(&gamerHandle);
				});

				ImGui::TreePop();
			}

			if (ImGui::TreeNode("Teleport")) {

				components::button("Teleport", [] {
					teleport::to_player(g_player_service->get_selected()->id());
				});

				ImGui::SameLine();

				components::button("Bring", [] {
					teleport::bring_player(g_player_service->get_selected()->id());
				});

				components::button("Godmode kill", [] {
					teleport::teleport_player(g_player_service->get_selected()->id(), Vector3(8110, 20, 0));
					script::get_current()->yield(1s);
					entity::delete_entity_notp(PED::GET_VEHICLE_PED_IS_IN(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_player_service->get_selected()->id()), false));
				});

				ImGui::SameLine();

				components::button("Teleport into Vehicle", [] {
					Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_player_service->get_selected()->id()), false);

					teleport::into_vehicle(veh);
				});

				components::button("Send to Cayo Perico", [] {
					toxic::send_to_cayo_perico(g_player_service->get_selected()->id());
				});

				ImGui::TreePop();
			}

			if (ImGui::TreeNode("Toxic")) {

				if (ImGui::TreeNode("Kicks and Crashes (Shit)")) {
					components::button("Desync", [] { toxic::desync_kick(g_player_service->get_selected()->get_net_game_player()); });

					ImGui::SameLine();

					components::button("Host Kick", [] {
						NETWORK::NETWORK_SESSION_KICK_PLAYER(g_player_service->get_selected()->id());
					});

					components::button("Ped Crash", [] {
						Ped ped = ped::spawn(ePedType::PED_TYPE_PROSTITUTE, rage::joaat("slod_human"), 0, ENTITY::GET_ENTITY_COORDS(g_player_service->get_selected()->id(), false), 0);
						script::get_current()->yield(3s);
						entity::delete_entity_notp(ped);
					});

					ImGui::SameLine();

					components::button("Vehicle Crash", [] {
						Vehicle veh = vehicle::spawn(rage::joaat("arbitergt"), ENTITY::GET_ENTITY_COORDS(g_player_service->get_selected()->id(), false), 0);
						script::get_current()->yield(3s);
						entity::delete_entity_notp(veh);
					});

					ImGui::SameLine();

					components::button("TSE Crash", [] {
						toxic::tse_crash(g_player_service->get_selected()->id());
					});

					ImGui::TreePop();
				}
				

				if (ImGui::TreeNode("Ped")) {
					components::button("Clear Tasks", [] {
						TASK::CLEAR_PED_TASKS_IMMEDIATELY(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_player_service->get_selected()->id()));
					});

					ImGui::SameLine();

					components::button("Ragdoll", [] {
						TASK::CLEAR_PED_TASKS_IMMEDIATELY(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_player_service->get_selected()->id()));
						auto pos = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_player_service->get_selected()->id()), true);
						FIRE::ADD_EXPLOSION(pos.x, pos.y, pos.z, 13, 1, false, true, 0, false);
					});

					ImGui::TreePop();
				}

				if (ImGui::TreeNode("Vehicle")) {

					components::button("Full Acceleration", [] {
						Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_player_service->get_selected()->id()), false);
						if (entity::take_control_of(veh))
							VEHICLE::SET_VEHICLE_FORWARD_SPEED(veh, VEHICLE::GET_VEHICLE_MODEL_ESTIMATED_MAX_SPEED(ENTITY::GET_ENTITY_MODEL(veh)) * 2);
					});

					ImGui::SameLine();

					components::button("Repair Vehicle", [] {
						Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(g_player_service->get_selected()->id(), false);
						vehicle::repair(veh);
					});

					ImGui::TreePop();
				}

				if (ImGui::TreeNode("Spawns")) {
					components::button("Spawn Grifer Gesus", [] {
						Ped player_ped = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_player_service->get_selected()->id());
						Vector3 pos = ENTITY::GET_ENTITY_COORDS(player_ped, true) + Vector3(0, 0, 500);

						ped::spawn_grifer_jesus(pos, player_ped);
					});

					ImGui::SameLine();

					components::button("Spawn Extrime Grifer Gesus", [] {
						Ped player_ped = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_player_service->get_selected()->id());
						Vector3 pos = ENTITY::GET_ENTITY_COORDS(player_ped, true) + Vector3(0, 0, 10);

						ped::spawn_extrime_grifer_jesus(pos, player_ped);
					});

					ImGui::SameLine();

					components::button("Spawn Grifer Lazer", [] {
						Ped player_ped = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_player_service->get_selected()->id());
						Vector3 pos = ENTITY::GET_ENTITY_COORDS(player_ped, true) + Vector3(0, 0, 500);
						Hash jet_hash RAGE_JOAAT("lazer");
						
						ped::spawn_grifer_jet(pos, player_ped, jet_hash);
					});

					ImGui::TreePop();
				}

				ImGui::TreePop();
			}
		}
	}
}