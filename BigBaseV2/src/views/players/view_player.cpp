#include "views/view.hpp"
#include "util/toxic.hpp"
#include "services/player_service.hpp"
#include "gta_util.hpp"
#include "util/misc.hpp"
#include "util/ped.hpp"
#include "util/teleport.hpp"
#include "features.hpp"

namespace big
{
	void view::view_player() {

		std::string title = fmt::format("Player Options: {}", g_player_service->get_selected()->get_name());
		
		ImGui::Text(title.c_str());
		ImGui::Checkbox("Spectate", &g->player.spectating);
		
		if (g_player_service->get_selected()->is_valid())
		{
			//components::button("Desync", [] { gta_util::get_network_player_mgr()->RemovePlayer(g_player_service->get_selected()->get_net_game_player()); });

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

				components::button("Teleport into Vehicle", [] {
					Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_player_service->get_selected()->id()), false);

					teleport::into_vehicle(veh);
				});

				ImGui::TreePop();
			}

			if (ImGui::TreeNode("Vehicle"))
			{
				if (ImGui::Button("Kick out of car"))
				{
					QUEUE_JOB_BEGIN_CLAUSE()
					{
						int Handle = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_player_service->get_selected()->id());
						TASK::CLEAR_PED_TASKS_IMMEDIATELY(Handle);
					}QUEUE_JOB_END_CLAUSE

				}

				if (ImGui::Button("Crash them while in car"))
				{
					QUEUE_JOB_BEGIN_CLAUSE()
					{
						int Handle = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_player_service->get_selected()->id());
						Vehicle vehicle = PED::GET_VEHICLE_PED_IS_IN(Handle, false);
						TASK::TASK_VEHICLE_TEMP_ACTION(Handle, vehicle, 18, 600);
					}QUEUE_JOB_END_CLAUSE

				}

				if (ImGui::Button("Gift vehicle"))
				{
					g_fiber_pool->queue_job([]
						{
							Vehicle vehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), true);
							ENTITY::SET_ENTITY_AS_MISSION_ENTITY(vehicle, TRUE, TRUE);
							NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(vehicle);

							while (!NETWORK::NETWORK_HAS_CONTROL_OF_ENTITY(vehicle))
								script::get_current()->yield(10ms);

							DECORATOR::DECOR_REGISTER("PV_Slot", 3);
							DECORATOR::DECOR_REGISTER("Player_Vehicle", 3);
							DECORATOR::DECOR_SET_BOOL(vehicle, "IgnoredByQuickSave", FALSE);
							DECORATOR::DECOR_SET_INT(vehicle, "Player_Vehicle", NETWORK::NETWORK_HASH_FROM_PLAYER_HANDLE(g_player_service->get_selected()->id()));
							VEHICLE::SET_VEHICLE_IS_STOLEN(vehicle, FALSE);
							notify::above_map("Vehicle Gifted");
						});
				}

				if (ImGui::Button("Clone Vehicle"))
				{
					QUEUE_JOB_BEGIN_CLAUSE()
					{
						int Handle = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_player_service->get_selected()->id());
						Vehicle cloned = features::ClonePedVehicle(Handle);
						features::BoostStats(cloned);
					}QUEUE_JOB_END_CLAUSE


				}
				ImGui::TreePop();
			}

			if (ImGui::TreeNode("Toxic")) {
				components::button("Explode Self", [] {
					toxic::blame_explode_player(
						g_player_service->get_selected()->id(),
						g_player_service->get_selected()->id(),
						eExplosionType::PLANE, 1000, false, true, 0.f
					);
					});
				if (ImGui::Button("Host Kick"))
				{
					QUEUE_JOB_BEGIN_CLAUSE()
					{
						NETWORK::NETWORK_SESSION_KICK_PLAYER(g_player_service->get_selected()->id());
					}
					QUEUE_JOB_END_CLAUSE
				}

				if (ImGui::Button("Bounty player"))
				{
					QUEUE_JOB_BEGIN_CLAUSE() {
						toxic::bounty_player(g_player_service->get_selected()->id(), 10000);
					}QUEUE_JOB_END_CLAUSE
				}

				if (ImGui::Button("Send to island"))
				{
					QUEUE_JOB_BEGIN_CLAUSE() {
						int64_t args[3] = {
				(int)eRemoteEvent::SendToIsland, 0, g_player_service->get_selected()->id() };
						g_pointers->m_trigger_script_event(1, args, 3, 1 << g_player_service->get_selected()->id());
					}QUEUE_JOB_END_CLAUSE
				}

				if (ImGui::Button("Desync Kick"))
				{
					QUEUE_JOB_BEGIN_CLAUSE() {
						gta_util::get_network_player_mgr()->RemovePlayer(g_player_service->get_selected()->get_net_game_player());
					}QUEUE_JOB_END_CLAUSE
				}

				if (ImGui::Button("Send Network Bail"))
				{
					QUEUE_JOB_BEGIN_CLAUSE() {
						int64_t args[3] = {
				(int)eRemoteEvent::NetworkBail, g_player_service->get_selected()->id(),*script_global(1893548).at(1).at(g_player_service->get_selected()->id() * 600).at(511).as<int*>() };
						g_pointers->m_trigger_script_event(1, args, 3, 1 << g_player_service->get_selected()->id());
					}QUEUE_JOB_END_CLAUSE
				}
				components::button("Taze", [] {
					toxic::taze_player(g_player_service->get_selected()->id());
				});
				
				components::button("Kick From Vehicle", [] {
					toxic::kick_from_vehicle(g_player_service->get_selected()->id());
				});
        
				components::button("Flying Vehicle", [] {
					toxic::flying_vehicle(g_player_service->get_selected()->id());
				});

				ImGui::TreePop();
			}
		}
	}
}