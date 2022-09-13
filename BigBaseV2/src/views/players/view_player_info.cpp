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
	void view::view_player_info()
	{
		std::string title = fmt::format("Player Info: {}", g_player_service->get_selected()->get_name());

		ImGui::Text(title.c_str());
		ImGui::Checkbox("Spectate", &g->player.spectating);

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

		if (CVehicle* vehicle = g_player_service->get_selected()->get_current_vehicle(); vehicle != nullptr)
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

		if (rage::rlGamerInfo* net_player_data = g_player_service->get_selected()->get_net_data(); net_player_data != nullptr)
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

			if (g_anti_cheat_service->is_player_in_moddb(net_player_data->m_gamer_handle_2.m_rockstar_id)) {
				int moddb_player = g_anti_cheat_service->get_moddb_player_from_rid(net_player_data->m_gamer_handle_2.m_rockstar_id);
				ImGui::Text("AC Score: %d", g_anti_cheat_service->modders()[moddb_player].score);
				std::string detections = g_anti_cheat_service->modders()[moddb_player].detections.c_str();
				detections.pop_back(); detections.pop_back();
				ImGui::Text("Detections: %s", detections.c_str());
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
	}
}