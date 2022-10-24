#include "views/view.hpp"
#include "fiber_pool.hpp"
#include "services/pickups/pickup_service.hpp"
#include "services/players/player_service.hpp"
#include "services/anti_cheat/anti_cheat_service.hpp"
#include "util/globals.hpp"
#include "util/misc.hpp"
#include "util/ped.hpp"
#include "util/vehicle.hpp"
#include "util/teleport.hpp"
#include "util/toxic.hpp"
#include "util/player.hpp"
#include "gta/joaat.hpp"
#include "core/enums.hpp"
#include "core/data/game_states.hpp"
#include "gta_util.hpp"

namespace big
{
	void view::view_player_info()
	{
		std::string title = std::format("Player Info: {}", g_player_service->get_selected()->get_name());
		CPlayerInfo* player_info = g_player_service->get_selected()->get_player_info();
		CPed* cped = g_player_service->get_selected()->get_ped();

		ImGui::Text(title.c_str());
		ImGui::Checkbox("Spectate", &g->player.spectating);

		ImGui::Text("Player ID: %d", g_player_service->get_selected()->id());

		ImGui::Text("Session Host: %s", g_player_service->get_selected()->is_host() ? "Yes" : "No");

		ImGui::Separator();

		if (player_info != nullptr)
		{
			ImGui::Text("Host token: %u", player_info->m_net_player_data.m_host_token);
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

		if (rage::rlGamerInfo* net_player_data = g_player_service->get_selected()->get_net_data(); net_player_data != nullptr)
		{
			if (ImGui::TreeNode("Net Info"))
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

				ImGui::Text("Game State: %s", game_states[(int32_t)player_info->m_game_state]);

				components::button("Open SC Overlay", [] {
					int gamerHandle;
					NETWORK::NETWORK_HANDLE_FROM_PLAYER(g_player_service->get_selected()->id(), &gamerHandle, 13);
					NETWORK::NETWORK_SHOW_PROFILE_UI(&gamerHandle);
				});
				ImGui::TreePop();
			}

			if (g_anti_cheat_service->is_player_in_moddb(net_player_data->m_gamer_handle_2.m_rockstar_id)) {
				if (ImGui::TreeNode("AC Info"))
				{
					int moddb_player = g_anti_cheat_service->get_moddb_player_from_rid(net_player_data->m_gamer_handle_2.m_rockstar_id);
					ImGui::Text("AC Score: %d", g_anti_cheat_service->modders()[moddb_player].score);
					std::string detections = g_anti_cheat_service->modders()[moddb_player].detections;
					detections.pop_back(); detections.pop_back();
					ImGui::Text("Detections: %s", detections.c_str());
					ImGui::TreePop();
				}
			}
		}
		if (cped != nullptr)
		{
			if (ImGui::TreeNode("Ped Info"))
			{
				ImGui::Text("Health: %f / %f", cped->m_health, cped->m_maxhealth);
				ImGui::SameLine();
				ImGui::Text("Armor: %f", cped->m_armor);
				ImGui::Text("Pos X: %f, Y: %f, Z: %f", cped->m_position.x,
					cped->m_position.y,
					cped->m_position.z);

				ImGui::Text("Distance: %f", math::distance_between_vectors(misc::fvector3_to_Vector3(cped->m_position), misc::fvector3_to_Vector3(cped->m_position)));
				ImGui::Text("Run Speed: %f", player_info->m_run_speed);
				ImGui::TreePop();
			}
		}

		if (player_info != nullptr && cped != nullptr)
		{
			if (ImGui::TreeNode("Weapon Info"))
			{
				ImGui::Text("Weapon Hash: %u", cped->m_weapon_manager->m_selected_weapon_hash);
				ImGui::Text("Weapon Damage: %f", cped->m_weapon_manager->m_weapon_info->m_damage);
				ImGui::Text("Weapon Damage Mult: %f", cped->m_weapon_manager->m_weapon_info->m_network_player_damage_modifier);
				ImGui::Text("Mele Damage Mult: %f", player_info->m_melee_weapon_damage_mult);
				ImGui::TreePop();
			}
		}

		if (ImGui::TreeNode("Global Stats"))
		{
			ImGui::Text("RP: %d", util::player::get_player_stat<int64_t*>(g_player_service->get_selected()->id(), ePlayerStatType::RP));
			ImGui::SameLine();
			ImGui::Text("Rank: %d", util::player::get_player_stat<int64_t*>(g_player_service->get_selected()->id(), ePlayerStatType::Rank));
			ImGui::Text("Global RP: %d", util::player::get_player_stat<int64_t*>(g_player_service->get_selected()->id(), ePlayerStatType::GlobalRP));

			ImGui::Text("Money Cash: %u", util::player::get_player_stat<uint64_t*>(g_player_service->get_selected()->id(), ePlayerStatType::MoneyCash));
			ImGui::SameLine();
			ImGui::Text("Money Bank: %u", util::player::get_player_stat<uint64_t*>(g_player_service->get_selected()->id(), ePlayerStatType::MoneyAll));

			ImGui::Text("Kills: %d", util::player::get_player_stat<int64_t*>(g_player_service->get_selected()->id(), ePlayerStatType::Kills));
			ImGui::SameLine();
			ImGui::Text("Deaths: %d", util::player::get_player_stat<int64_t*>(g_player_service->get_selected()->id(), ePlayerStatType::Deaths));
			ImGui::Text("K/D Ratio: %f", util::player::get_player_stat<float*>(g_player_service->get_selected()->id(), ePlayerStatType::KDRatio));

			ImGui::Text("Allows Spectating: %s", util::player::get_player_stat<int*>(g_player_service->get_selected()->id(), ePlayerStatType::CanSpectate) ? "Yes" : "No");

			ImGui::TreePop();
		}
	}
}