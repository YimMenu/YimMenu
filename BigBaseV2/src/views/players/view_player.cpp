#include "views/view.hpp"
#include "services/player_service.hpp"
#include "gta_util.hpp"
#include "util/misc.hpp"
#include "util/globals.hpp"
#include "util/ped.hpp"
#include "util/vehicle.hpp"
#include "util/teleport.hpp"
#include "util/toxic.hpp"

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

				ImGui::Checkbox("Never Wanted", &g->player.player_never_wanted);

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

				if (CPed* ped = g_player_service->get_selected()->get_ped(); ped != nullptr)
				{
					ImGui::Text("Player God Mode: %s",
						misc::has_bit_set((int*)&ped->m_damage_bits, 8) ? "Yes" : "No"
					);
				}

				CAutomobile* vehicle = g_player_service->get_selected()->get_current_vehicle();
				ImGui::Text("Vehicle God Mode: %s",
					vehicle == nullptr ? "No vehicle detected" :
					misc::has_bit_set((int*)&vehicle->m_damage_bits, 8) ? "Yes" : "No"
				);

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

				components::button("Open Profile", [] {
					int Handle;
					int Handle_size;

					NETWORK::NETWORK_HANDLE_FROM_PLAYER(g_player_service->get_selected()->id(), &Handle, Handle_size);
					NETWORK::NETWORK_SHOW_PROFILE_UI(&Handle);
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
					entity::delete_entity(PED::GET_VEHICLE_PED_IS_IN(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_player_service->get_selected()->id()), false));
				});

				components::button("Teleport into Vehicle", [] {
					Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_player_service->get_selected()->id()), false);

					teleport::into_vehicle(veh);
				});

				ImGui::TreePop();
			}

			if (ImGui::TreeNode("Toxic")) {

				if (ImGui::TreeNode("Shit")) {
					components::button("Desync", [] { toxic::desync_kick(g_player_service->get_selected()->get_net_game_player()); });

					ImGui::SameLine();

					components::button("Host Kick", [] {
						NETWORK::NETWORK_SESSION_KICK_PLAYER(g_player_service->get_selected()->id());
					});

					components::button("Ped Crash", [] {
						Ped ped = ped::spawn("slod_human", ENTITY::GET_ENTITY_COORDS(g_player_service->get_selected()->id(), false), 0);
						script::get_current()->yield(3s);
						entity::delete_entity(ped);
					});

					ImGui::SameLine();

					components::button("Vehicle Crash", [] {
						Vehicle veh = vehicle::spawn("arbitergt", ENTITY::GET_ENTITY_COORDS(g_player_service->get_selected()->id(), false), 0);
						script::get_current()->yield(3s);
						entity::delete_entity(veh);
					});

					ImGui::SameLine();

					components::button("TSE Crash", [] {
						constexpr size_t arg_count = 2;
						int64_t args[arg_count] = {
							static_cast<int64_t>(eRemoteEvent::Crash),
							self::id,
						};

						g_pointers->m_trigger_script_event(1, args, arg_count, 1 << g_player_service->get_selected()->id());
					});
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

				}

				if (ImGui::TreeNode("Spawns")) {
					//code from https://github.com/gta-chaos-mod/ChaosModV
					components::button("Spawn Grifer Gesus", [] {
						Ped ply = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_player_service->get_selected()->id());
						Vector3 pos = ENTITY::GET_ENTITY_COORDS(ply, true);

						static const Hash playerGroup = rage::joaat("PLAYER");
						static const Hash civGroup = rage::joaat("CIVMALE");
						static const Hash femCivGroup = rage::joaat("CIVFEMALE");

						Hash relationshipGroup;
						PED::ADD_RELATIONSHIP_GROUP("_HOSTILE_JESUS", &relationshipGroup);
						PED::SET_RELATIONSHIP_BETWEEN_GROUPS(5, relationshipGroup, playerGroup);
						PED::SET_RELATIONSHIP_BETWEEN_GROUPS(5, relationshipGroup, civGroup);
						PED::SET_RELATIONSHIP_BETWEEN_GROUPS(5, relationshipGroup, femCivGroup);

						Ped ped = ped::spawn("u_m_m_jesus_01", pos, 0, true);

						if (PED::IS_PED_IN_ANY_VEHICLE(ply, false))
						{
							PED::SET_PED_INTO_VEHICLE(ped, PED::GET_VEHICLE_PED_IS_IN(ply, false), -2);
						}

						PED::SET_PED_RELATIONSHIP_GROUP_HASH(ped, relationshipGroup);
						PED::SET_PED_HEARING_RANGE(ped, 9999.f);
						PED::SET_PED_CONFIG_FLAG(ped, 281, true);

						ENTITY::SET_ENTITY_PROOFS(ped, false, true, true, false, false, false, false, false);

						PED::SET_PED_COMBAT_ATTRIBUTES(ped, 5, true);
						PED::SET_PED_COMBAT_ATTRIBUTES(ped, 46, true);

						PED::SET_PED_CAN_RAGDOLL_FROM_PLAYER_IMPACT(ped, false);
						PED::SET_RAGDOLL_BLOCKING_FLAGS(ped, 5);
						PED::SET_PED_SUFFERS_CRITICAL_HITS(ped, false);

						WEAPON::GIVE_WEAPON_TO_PED(ped, rage::joaat("WEAPON_RAILGUN"), 9999, true, true);
						TASK::TASK_COMBAT_PED(ped, ply, 0, 16);

						PED::SET_PED_FIRING_PATTERN(ped, 0xC6EE6B4C);
					});
					ImGui::SameLine();
					components::button("Spawn Extrime Grifer Gesus", [] {
						Ped ply = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_player_service->get_selected()->id());
						Vector3 pos = ENTITY::GET_ENTITY_COORDS(ply, true);
						float heading = ENTITY::GET_ENTITY_HEADING(PED::IS_PED_IN_ANY_VEHICLE(ply, false) ? PED::GET_VEHICLE_PED_IS_IN(ply, false) : ply);

						Vehicle veh = vehicle::spawn("oppressormk2", pos, heading, true);
						VEHICLE::SET_VEHICLE_ENGINE_ON(veh, true, true, false);
						vehicle::max_vehicle(veh);
						ENTITY::SET_ENTITY_PROOFS(veh, false, true, true, false, false, false, false, false);

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

						PED::SET_PED_COMBAT_ATTRIBUTES(ped, 3, false);
						PED::SET_PED_COMBAT_ATTRIBUTES(ped, 5, true);
						PED::SET_PED_COMBAT_ATTRIBUTES(ped, 46, true);

						ENTITY::SET_ENTITY_PROOFS(ped, false, true, true, false, false, false, false, false);

						PED::SET_PED_COMBAT_ATTRIBUTES(ped, 5, true);
						PED::SET_PED_COMBAT_ATTRIBUTES(ped, 46, true);

						PED::SET_PED_CAN_BE_KNOCKED_OFF_VEHICLE(ped, 1);
						PED::SET_PED_CAN_RAGDOLL_FROM_PLAYER_IMPACT(ped, false);
						PED::SET_RAGDOLL_BLOCKING_FLAGS(ped, 5);
						PED::SET_PED_SUFFERS_CRITICAL_HITS(ped, false);

						WEAPON::GIVE_WEAPON_TO_PED(ped, rage::joaat("WEAPON_RAILGUN"), 9999, true, true);
						TASK::TASK_COMBAT_PED(ped, ply, 0, 16);

						PED::SET_PED_FIRING_PATTERN(ped, 0xC6EE6B4C);
					});
					ImGui::SameLine();
					components::button("Spawn Grifer Lazer", [] {
						Ped ply = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_player_service->get_selected()->id());
						Vector3 pos = ENTITY::GET_ENTITY_COORDS(ply, true) + Vector3(0,0, 500);
						float heading = ENTITY::GET_ENTITY_HEADING(PED::IS_PED_IN_ANY_VEHICLE(ply, false) ? PED::GET_VEHICLE_PED_IS_IN(ply, false) : ply);

						Vehicle veh = vehicle::spawn("lazer", pos, heading, true, false);
						VEHICLE::SET_VEHICLE_ENGINE_ON(veh, true, true, false);
						VEHICLE::CONTROL_LANDING_GEAR(veh, 3);

						Blip blip = HUD::ADD_BLIP_FOR_ENTITY(veh);
						HUD::SET_BLIP_SPRITE(blip, 424);

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
				}

				ImGui::TreePop();
			}
		}
	}
}