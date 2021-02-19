#include "gui/tab_bar.hpp"
#include "features/functions.hpp"
#include "features/notify.hpp"
#include "pointers.hpp"
#include "script_global.hpp"

namespace big
{
	void tabbar::player_griefing()
	{
		if (ImGui::BeginTabItem("Griefing"))
		{
			if (ImGui::Button("Cage"))
			{
				QUEUE_JOB_BEGIN_CLAUSE()
				{
					func::cage_ped(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_selectedPlayer.id));
				}QUEUE_JOB_END_CLAUSE
			}

			if (ImGui::TreeNode("General"))
			{
				if (ImGui::Button("Force Kick from vehicle"))
				{
					QUEUE_JOB_BEGIN_CLAUSE()
					{
						func::force_kick_from_vehicle(g_selectedPlayer.id);
					}QUEUE_JOB_END_CLAUSE
				}

				ImGui::TreePop();
			}

			if (ImGui::TreeNode("Lester"))
			{
				if (ImGui::Button("Bounty 10k"))
				{
					QUEUE_JOB_BEGIN_CLAUSE()
					{
						func::set_player_bounty(g_selectedPlayer.id);
					}QUEUE_JOB_END_CLAUSE
				}

				ImGui::TreePop();
			}

			if (ImGui::TreeNode("Kick"))
			{
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
							notify::above_map("You aren't the host");
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

				ImGui::TreePop();
			}

			if (ImGui::TreeNode("Script Events"))
			{
				if (ImGui::Button("Kick from Vehicle"))
				{
					QUEUE_JOB_BEGIN_CLAUSE()
					{
						int64_t args[2] = { RemoteEvents::VehicleKick, g_selectedPlayer.id };

						g_pointers->m_trigger_script_event(true, args, 2, 1 << g_selectedPlayer.id);
					}QUEUE_JOB_END_CLAUSE
				}

				if (ImGui::Button("Clear Wanted Level"))
				{
					QUEUE_JOB_BEGIN_CLAUSE()
					{
						int global = *script_global(1630317).at(g_selectedPlayer.id, 615).at(215).as<int*>();

						int64_t args[3] = { RemoteEvents::ClearWantedLevel, g_selectedPlayer.id, global };

						g_pointers->m_trigger_script_event(true, args, 3, 1 << g_selectedPlayer.id);
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
						int64_t args[9] = { RemoteEvents::Teleport, g_selectedPlayer.id, 1, -1, 1, locations[g_temp.teleport_location].id, 0,0,0 };
						g_pointers->m_trigger_script_event(true, args, 9, 1 << g_selectedPlayer.id);
					}QUEUE_JOB_END_CLAUSE
				}

				ImGui::TreePop();
			}

			ImGui::EndTabItem();
		}
	}
}