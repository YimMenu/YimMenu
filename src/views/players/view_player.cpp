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
			if (ImGui::TreeNode("Misc"))
			{
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

				if (auto vehicle = g_player_service->get_selected()->get_current_vehicle(); vehicle != nullptr)
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

				if (auto net_player_data = g_player_service->get_selected()->get_net_data(); net_player_data != nullptr)
				{
					ImGui::Text("Rockstar ID: %d", net_player_data->m_gamer_handle_2.m_rockstar_id);
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

			if (ImGui::TreeNode("Teleport"))
			{
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
		}
	}
}