#include "gta_util.hpp"
#include "services/pickups/pickup_service.hpp"
#include "services/players/player_service.hpp"
#include "util/globals.hpp"
#include "util/toxic.hpp"
#include "util/misc.hpp"
#include "util/ped.hpp"
#include "util/vehicle.hpp"
#include "util/teleport.hpp"
#include "util/entity.hpp"
#include "views/view.hpp"
#include "gta/VehicleValues.h"

namespace big
{
	void view::view_player() {

		std::string title = fmt::format("Player Options: {}", g_player_service->get_selected()->get_name());
		ImGui::Text(title.c_str());
		if (g_player_service->get_selected()->is_valid())		
		{
			ImGui::Checkbox("Spectate", &g->player.spectating);

			ImGui::SameLine();
			ImGui::Checkbox("Freeze", &g->player.freezeplayer);

			ImGui::Checkbox("Shaky Booty", &g->player.shakecam);

			ImGui::SameLine();
			ImGui::Checkbox("Freeze All", &g->player.freezeallplayers);

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
					toxic::clear_wanted_player(g_player_service->get_selected()->id());
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

				components::button("Spawn Bodyguard", [] {
					toxic::bodyguard(g_player_service->get_selected()->id());
					});

				ImGui::SameLine();				
				
				components::button("Chase", [] {
					if (!self::veh) 
					{
						g->player.chase = false;
						g_notification_service->push_warning("Warning", "Please be in a vehicle first then try again.");
					}
					else
						g->player.chase = true;
				});

				ImGui::TreePop();
			}

			if (ImGui::TreeNode("Info")) {

				ImGui::Text("Player ID: %d", g_player_service->get_selected()->id());
				
				ImGui::SameLine();

				ImGui::Text("         Session Host: %s", g_player_service->get_selected()->is_host() ? "Yes" : "No");

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
					bool comma1 = false;
					if (ped_damage_bits & (uint32_t)eEntityProofs::BULLET)
					{
						mode_str += "Bullet";
						comma1 = true;
					}
					if (ped_damage_bits & (uint32_t)eEntityProofs::EXPLOSION)
					{
						if (comma1) {
							mode_str += ", ";
						}
						mode_str += "Explosion";
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
						bool comma2 = false;
						if (veh_damage_bits & (uint32_t)eEntityProofs::COLLISION)
						{
							mode_str += "Collision";
							comma2 = true;
						}
						if (veh_damage_bits & (uint32_t)eEntityProofs::EXPLOSION)
						{
							if (comma2) {
								mode_str += ", ";
							}
							mode_str += "Explosion";
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
				}

				ImGui::TreePop();
			}

			if (ImGui::TreeNode("Teleport")) {

				components::button("Teleport", [] {
					teleport::to_player(g_player_service->get_selected()->id());
					});

				ImGui::SameLine();
				
				components::button("Teleport in Vehicle", [] {
					Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_player_service->get_selected()->id()), false);

					teleport::into_vehicle(veh);
					});
				
				components::button("Bring", [] {
					teleport::bring_player(g_player_service->get_selected()->id());
					});
				
				ImGui::SameLine();
				
				components::button("Teleport with Paracute", [] {
					Hash parachute = RAGE_JOAAT("GADGET_PARACHUTE");
					Ped SelectedPlayer = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_player_service->get_selected()->id());
					WEAPON::GIVE_WEAPON_TO_PED(self::ped, parachute, 0, false, true);
					Vector3 TargetCoords = teleport::GetEntityCoords(SelectedPlayer);
					TargetCoords.z += 80.f;
					teleport::TPtoCoords(self::ped, TargetCoords, false, true);
					});

				ImGui::TreePop();
			}

			if (ImGui::TreeNode("Vehicle"))
			{
				components::button("Slingshot", [] {
					Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_player_service->get_selected()->id()), false);
					if (entity::take_control_of(veh))
						VEHICLE::SET_VEHICLE_FORWARD_SPEED(veh, VEHICLE::GET_VEHICLE_MODEL_ESTIMATED_MAX_SPEED(ENTITY::GET_ENTITY_MODEL(veh)) * 2);
					});

				ImGui::SameLine();

				components::button("Burst Tires", [] {
					int Handle = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_player_service->get_selected()->id());
					if (PED::IS_PED_IN_ANY_VEHICLE(Handle, 0))
					{
						toxic::BurstTires(Handle);
					}
					else
					{
						g_notification_service->push_warning("Warning", "Player is not in a Vehicle.");
					}
					});

				ImGui::SameLine();

				components::button("Flying Vehicle", [] {
					toxic::flying_vehicle(g_player_service->get_selected()->id());
					});

				components::button("Destroy vehicle", [] {
					toxic::destroyveh(g_player_service->get_selected()->id());
					});

				ImGui::SameLine();

				components::button("Kick From Vehicle", [] {
					toxic::kick_from_vehicle(g_player_service->get_selected()->id());
					});
				ImGui::TreePop();
			}

			if (ImGui::TreeNode("Toxic")) {
				components::button("Explode Self", [] {
					toxic::blame_explode_player(
						g_player_service->get_selected()->id(),
						g_player_service->get_selected()->id(),
						eExplosionType::PLANE, 1000, false, true, 10000.f
					);
					});

				ImGui::SameLine();

				components::button("Taze", [] {
					toxic::taze_player(g_player_service->get_selected()->id());
					});

				ImGui::SameLine();

				components::button("Kick to SP", [] {
					toxic::KICK_TO_SP(g_player_service->get_selected()->id());
					});

				components::button("Ragdoll", [] {
					TASK::CLEAR_PED_TASKS_IMMEDIATELY(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_player_service->get_selected()->id()));
					auto pos = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_player_service->get_selected()->id()), true);
					FIRE::ADD_EXPLOSION(pos.x, pos.y, pos.z, 13, 1, false, true, 0, false);
					});

				ImGui::SameLine();

				components::button("Airstrike", [] {
					toxic::airstrike(g_player_service->get_selected()->id());
					});

				ImGui::SameLine();


				components::button("Send to APT", [] {
					toxic::Apartment(g_player_service->get_selected()->id());
					});

				/*components::button("Crash Script", [] {
					toxic::crash(g_player_service->get_selected()->id());
				});*/

				components::button("Send to Cayo", [] {
					toxic::send_to_cayo_perico(g_player_service->get_selected()->id());
					});
				
				ImGui::SameLine();

				components::button("Bitching", [] {
					toxic::bitching(g_player_service->get_selected()->id());
					});

				ImGui::SameLine();
				
				components::button("Chal BSDK", [] { gta_util::get_network_player_mgr()->RemovePlayer(g_player_service->get_selected()->get_net_game_player());
					});


				components::button("CEO Kick", [] {
					toxic::CEO_KICK(g_player_service->get_selected()->id());
					g_notification_service->push_warning("Warning", "Player has been CEO Kicked");
					});

				ImGui::SameLine();

				components::button("EMP", [] {
					toxic::emp_player(g_player_service->get_selected()->id());
					});

				ImGui::SameLine();

				components::button("CEO Ban", [] {
					toxic::CEO_BAN(g_player_service->get_selected()->id());
					g_notification_service->push_warning("Warning", "Player has been CEO Banned");
					});

				ImGui::SameLine();

				components::button("Send Jet", [] {              //2Take1 wala
					Ped ply = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_player_service->get_selected()->id());
					Vector3 pos = ENTITY::GET_ENTITY_COORDS(ply, true) + Vector3(0, 0, 500);
					float heading = ENTITY::GET_ENTITY_HEADING(PED::IS_PED_IN_ANY_VEHICLE(ply, false) ? PED::GET_VEHICLE_PED_IS_IN(ply, false) : ply);
					Hash plane = VEHICLE_LAZER;

					Vehicle veh = vehicle::spawn(plane, pos, heading, true);
					VEHICLE::SET_VEHICLE_ENGINE_ON(veh, true, true, false);
					VEHICLE::CONTROL_LANDING_GEAR(veh, 3);

					static const Hash playerGroup = rage::joaat("PLAYER");
					static const Hash civGroup = rage::joaat("CIVMALE");
					static const Hash femCivGroup = rage::joaat("CIVFEMALE");

					Hash relationshipGroup;
					PED::ADD_RELATIONSHIP_GROUP("_HOSTILE_JESUS", &relationshipGroup);
					PED::SET_RELATIONSHIP_BETWEEN_GROUPS(5, relationshipGroup, playerGroup);
					PED::SET_RELATIONSHIP_BETWEEN_GROUPS(5, relationshipGroup, civGroup);
					PED::SET_RELATIONSHIP_BETWEEN_GROUPS(5, relationshipGroup, femCivGroup);

					Ped ped = ped::spawn_in_vehicle("u_m_m_jesus_01", veh, true);

					PED::SET_PED_RELATIONSHIP_GROUP_HASH(ped, relationshipGroup);
					PED::SET_PED_HEARING_RANGE(ped, 9999.f);
					PED::SET_PED_CONFIG_FLAG(ped, 281, true);


					TASK::TASK_PLANE_MISSION(ped, veh, 0, ply, 0, 0, 0, 6, 0.0, 0.0, 0.0, 2500.0, -1500.0, 0);

					WEAPON::GIVE_WEAPON_TO_PED(ped, rage::joaat("WEAPON_RAILGUN"), 9999, true, true);
					TASK::TASK_COMBAT_PED(ped, ply, 0, 16);

					PED::SET_PED_FIRING_PATTERN(ped, 0xC6EE6B4C);
					});

				ImGui::TreePop();				
			}
		}
	}
}