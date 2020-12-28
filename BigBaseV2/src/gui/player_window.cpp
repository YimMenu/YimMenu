#include "gui.hpp"
#include "imgui.h"
#include "features.hpp"
#include "pointers.hpp"

namespace big
{
	void gui::render_player_window()
	{
		if (g_selectedPlayer == -1) return;

		player player = g_players[g_selectedPlayer];
		if (!player.is_online)
		{
			g_selectedPlayer = -1;

			return;
		}

		if (ImGui::Begin("Player Options"))
		{
			ImGui::Text("Selected player:");
			ImGui::SameLine(); ImGui::TextColored({ 25,180,38,255 }, player.name);

			if (ImGui::Button("Close"))
			{
				g_selectedPlayer = -1;
			}

			ImGui::Separator();

			if (ImGui::Button("Teleport to Player"))
			{
				QUEUE_JOB_BEGIN_CLAUSE()
				{
					Ped player = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_playerId);
					Ped target = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_selectedPlayer);

					Vector3 location = ENTITY::GET_ENTITY_COORDS(target, true);

					PED::SET_PED_COORDS_KEEP_VEHICLE(player, location.x, location.y, location.z + 1.f);
				}QUEUE_JOB_END_CLAUSE
			}



			ImGui::Separator();

			if (ImGui::Button("Kick (Host) - Permanently Blacklisted"))
			{
				QUEUE_JOB_BEGIN_CLAUSE()
				{
					if (NETWORK::NETWORK_IS_HOST())
					{
						NETWORK::NETWORK_SESSION_KICK_PLAYER(g_selectedPlayer);
					}
					else
					{
						features::notify::above_map("You aren't the host");
					}
				}QUEUE_JOB_END_CLAUSE
			}

			if (ImGui::Button("Kick (Non-Host)"))
			{
				uint64_t args[4] = { 1317868303, (uint64_t)PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_selectedPlayer), 0, 0 };

				g_pointers->m_trigger_script_event(1, args, 4, 1 << g_selectedPlayer);
			}

			if (ImGui::Button("Kick from Vehicle"))
			{
				QUEUE_JOB_BEGIN_CLAUSE()
				{
					uint64_t args[2] = { -1333236192, (uint64_t)g_selectedPlayer };

					g_pointers->m_trigger_script_event(1, args, 2, 1 << g_selectedPlayer);
				}QUEUE_JOB_END_CLAUSE
			}

			if (ImGui::Button("CEO Kick"))
			{
				QUEUE_JOB_BEGIN_CLAUSE()
				{
					uint64_t ceokick[4] = { -1648921703, PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_selectedPlayer), 0, 0 };

					g_pointers->m_trigger_script_event(1, ceokick, 4, 1 << g_selectedPlayer);
				}QUEUE_JOB_END_CLAUSE
			}

			if (ImGui::Button("CEO Ban"))
			{
				QUEUE_JOB_BEGIN_CLAUSE()
				{
					uint64_t ceoban[4] = { -738295409, PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_selectedPlayer), 1, 5 };

					g_pointers->m_trigger_script_event(1, ceoban, 4, 1 << g_selectedPlayer);
				}QUEUE_JOB_END_CLAUSE
			}

			if (ImGui::Button("Send to Job"))
			{
				QUEUE_JOB_BEGIN_CLAUSE()
				{
					uint64_t args[2] = { -545396442, PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_selectedPlayer) };

					g_pointers->m_trigger_script_event(true, args, 2, 1 << g_selectedPlayer);
				}QUEUE_JOB_END_CLAUSE
			}

			if (ImGui::BeginCombo("Invite Location:", location_names[g_temp.teleport_location]))
			{
				for (uint8_t i = 0; i < IM_ARRAYSIZE(location_names); i++)
				{
					bool is_selected = (g_temp.teleport_location == i);
					if (ImGui::Selectable(location_names[i], is_selected))
						g_temp.teleport_location = i;
					if (is_selected)
						ImGui::SetItemDefaultFocus();
				}

				ImGui::EndCombo();
			}
			if (ImGui::Button("Send Invite"))
			{
				QUEUE_JOB_BEGIN_CLAUSE()
				{
					uint64_t args[9] = { -171207973, g_selectedPlayer, 1, -1, 1, location_ids[g_temp.teleport_location], 0,0,0 }; // 1097312011
					g_pointers->m_trigger_script_event(1, args, 9, 1 << g_selectedPlayer);
				}QUEUE_JOB_END_CLAUSE
			}

			ImGui::Separator();

			if (ImGui::Button("Drop Money (!)"))
			{
				QUEUE_JOB_BEGIN_CLAUSE()
				{
					Vector3 coords = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_selectedPlayer), true);

					OBJECT::CREATE_AMBIENT_PICKUP(0x1E9A99F8, coords.x, coords.y, coords.z + 0.5f, 0, rand() % 500 + 2000, (Hash)-1666779307, false, true);
					STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED((Hash)-1666779307);
				}QUEUE_JOB_END_CLAUSE

			}

			ImGui::End();
		}
	}
}