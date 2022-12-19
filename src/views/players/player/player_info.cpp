#include "views/view.hpp"
#include "services/player_database/player_database_service.hpp"

namespace big
{
	void view::player_info()
	{
		if (ImGui::TreeNode("Info"))
		{

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

				ImGui::SameLine();

				if (ImGui::Button("Copy##rid")) ImGui::SetClipboardText(std::to_string(net_player_data->m_gamer_handle_2.m_rockstar_id).data());

				ImGui::Text(
					"IP Address: %d.%d.%d.%d:%d",
					net_player_data->m_external_ip.m_field1,
					net_player_data->m_external_ip.m_field2,
					net_player_data->m_external_ip.m_field3,
					net_player_data->m_external_ip.m_field4,
					net_player_data->m_external_port
				);

				ImGui::SameLine();

				if (ImGui::Button("Copy##ip")) ImGui::SetClipboardText(std::format("{}.{}.{}.{}:{}", net_player_data->m_external_ip.m_field1,
					net_player_data->m_external_ip.m_field2,
					net_player_data->m_external_ip.m_field3,
					net_player_data->m_external_ip.m_field4,
					net_player_data->m_external_port).data());
			}

			if (ImGui::Button("Add To Database"))
			{
				g_player_database_service->get_or_create_player(g_player_service->get_selected());
			}

			ImGui::TreePop();
		}
	}
}