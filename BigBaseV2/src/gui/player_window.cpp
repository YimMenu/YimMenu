#include "gui.hpp"
#include "imgui.h"
#include "features.hpp"
#include "pointers.hpp"

namespace big
{
	void gui::render_player_window()
	{
		if (g_selectedPlayer.id != g_selectedPlayerId || !g_selectedPlayer.is_online) return;

		if (ImGui::Begin("Player Options"))
		{
			ImGui::Text("Selected player:");
			ImGui::SameLine(); ImGui::TextColored({ 25,180,38,255 }, g_selectedPlayer.name);

			if (ImGui::Button("Close"))
			{
				g_selectedPlayerId = -2;
			}

			ImGui::Separator();

			ImGui::Checkbox("Spectate Player", &g_temp.spectate_player);

			ImGui::Separator();


			if (ImGui::Button("Bounty 10k"))
			{
				QUEUE_JOB_BEGIN_CLAUSE()
				{
					features::functions::set_player_bounty(g_selectedPlayer.id);
				}QUEUE_JOB_END_CLAUSE
			}

			ImGui::Separator();

			if (ImGui::Button("Teleport to Player"))
			{
				QUEUE_JOB_BEGIN_CLAUSE()
				{
					features::teleport::teleport_to_player(g_selectedPlayer.id);
				}QUEUE_JOB_END_CLAUSE
			}

			if (ImGui::Button("Teleport into Vehicle"))
			{
				QUEUE_JOB_BEGIN_CLAUSE()
				{
					features::teleport::teleport_into_player_vehicle(g_selectedPlayer.id);
				}QUEUE_JOB_END_CLAUSE
			}

			ImGui::Separator();

			if (ImGui::Button("Kick (Host) - Permanently Blacklisted"))
			{
				QUEUE_JOB_BEGIN_CLAUSE()
				{
					if (NETWORK::NETWORK_IS_HOST())
					{
						NETWORK::NETWORK_SESSION_KICK_PLAYER(g_selectedPlayer.id);
					}
					else
					{
						features::notify::above_map("You aren't the host");
					}
				}QUEUE_JOB_END_CLAUSE
			}

			if (ImGui::Button("Kick (Non-Host)"))
			{
				QUEUE_JOB_BEGIN_CLAUSE()
				{
					int64_t args[4] = { 0, PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_selectedPlayer.id), 0, 0 };

					for (int64_t kick_hash : kick_hashes)
					{
						args[0] = kick_hash;

						g_pointers->m_trigger_script_event(true, args, 4, 1 << g_selectedPlayer.id);
					}
				}QUEUE_JOB_END_CLAUSE
			}

			if (ImGui::Button("Kick from Vehicle"))
			{
				QUEUE_JOB_BEGIN_CLAUSE()
				{
					int64_t args[2] = { RemoteEvents::VehicleKick, g_selectedPlayer.id };

					g_pointers->m_trigger_script_event(true, args, 2, 1 << g_selectedPlayer.id);
				}QUEUE_JOB_END_CLAUSE
			}

			if (ImGui::Button("CEO Kick"))
			{
				QUEUE_JOB_BEGIN_CLAUSE()
				{
					int64_t ceokick[4] = { RemoteEvents::CeoKick, PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_selectedPlayer.id), 0, 0 };

					g_pointers->m_trigger_script_event(true, ceokick, 4, 1 << g_selectedPlayer.id);
				}QUEUE_JOB_END_CLAUSE
			}

			if (ImGui::Button("CEO Ban"))
			{
				QUEUE_JOB_BEGIN_CLAUSE()
				{
					int64_t ceoban[4] = { RemoteEvents::CeoBan, PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_selectedPlayer.id), 1, 5 };

					g_pointers->m_trigger_script_event(true, ceoban, 4, 1 << g_selectedPlayer.id);
				}QUEUE_JOB_END_CLAUSE
			}

			if (ImGui::Button("Send to Job"))
			{
				QUEUE_JOB_BEGIN_CLAUSE()
				{
					int64_t args[2] = { RemoteEvents::ForceMission, PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_selectedPlayer.id) };

					g_pointers->m_trigger_script_event(true, args, 2, 1 << g_selectedPlayer.id);
				}QUEUE_JOB_END_CLAUSE
			}

			ImGui::Text("Force TP Location:");
			if (ImGui::BeginCombo("##teleport_location", locations[g_temp.teleport_location].name))
			{
				for (uint8_t i = 0; i < IM_ARRAYSIZE(locations); i++)
				{
					bool is_selected = (g_temp.teleport_location == i);
					if (ImGui::Selectable(locations[i].name, is_selected))
						g_temp.teleport_location = i;
					if (is_selected)
						ImGui::SetItemDefaultFocus();
				}

				ImGui::EndCombo();
			}
			if (ImGui::Button("Teleport to selected location."))
			{
				QUEUE_JOB_BEGIN_CLAUSE()
				{
					int64_t args[9] = { RemoteEvents::Teleport, g_selectedPlayer.id, 1, -1, 1, locations[g_temp.teleport_location].id, 0,0,0 }; // 1097312011
					g_pointers->m_trigger_script_event(true, args, 9, 1 << g_selectedPlayer.id);
				}QUEUE_JOB_END_CLAUSE
			}

			ImGui::Separator();

			if (ImGui::Button("Drop Money (!)"))
			{
				QUEUE_JOB_BEGIN_CLAUSE()
				{
					Vector3 coords = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_selectedPlayer.id), true);

					features::functions::create_ambient_money(coords, rand() % 500 + 2000);
				}QUEUE_JOB_END_CLAUSE
			}

			ImGui::End();
		}
	}
}