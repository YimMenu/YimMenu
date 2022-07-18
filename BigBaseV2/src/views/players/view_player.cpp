#include "gta_util.hpp"
#include "services/pickups/pickup_service.hpp"
#include "services/players/player_service.hpp"
#include "util/globals.hpp"
#include "util/misc.hpp"
#include "util/ped.hpp"
#include "util/teleport.hpp"
#include "views/view.hpp"

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
					g_fiber_pool->queue_job([]
						{
						int Handle = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_player_service->get_selected()->id());
						TASK::CLEAR_PED_TASKS_IMMEDIATELY(Handle);
						});

				}

				if (ImGui::Button("Crash them while in car"))
				{
					g_fiber_pool->queue_job([]
						{
						int Handle = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_player_service->get_selected()->id());
						Vehicle vehicle = PED::GET_VEHICLE_PED_IS_IN(Handle, false);
						TASK::TASK_VEHICLE_TEMP_ACTION(Handle, vehicle, 18, 600);
						});

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
				ImGui::TreePop();
			}
		}
	}
}