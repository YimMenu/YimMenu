#include "fiber_pool.hpp"
#include "gta/enums.hpp"
#include "gta_util.hpp"
#include "player_tabs.hpp"
#include "natives.hpp"
#include "script.hpp"
#include "util/toxic.hpp"
#include "util/vehicle.hpp"
#include "script_local.hpp"

namespace big
{
	void tab_player::tab_toxic()
	{
		if (ImGui::BeginTabItem("Toxic"))
		{
			if (ImGui::Button("Explode Self"))
			{
				QUEUE_JOB_BEGIN_CLAUSE()
				{
					toxic::blame_explode_player(
						g_player_service->get_selected()->id(),
						g_player_service->get_selected()->id(),
						eExplosionType::PLANE, 1000, false, true, 0.f
					);
				}QUEUE_JOB_END_CLAUSE
			}

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
				QUEUE_JOB_BEGIN_CLAUSE(){
					int64_t args[3] = {
			(int)eRemoteEvent::SendToIsland, 0, g_player_service->get_selected()->id()};
					g_pointers->m_trigger_script_event(1, args, 3, 1 << g_player_service->get_selected()->id());
				}QUEUE_JOB_END_CLAUSE
			}

			if (ImGui::Button("Desync Kick"))
			{
				QUEUE_JOB_BEGIN_CLAUSE(){
					gta_util::get_network_player_mgr()->RemovePlayer(g_player_service->get_selected()->get_net_game_player());
				}QUEUE_JOB_END_CLAUSE
			}

			if (ImGui::Button("Send Network Bail"))
			{
				QUEUE_JOB_BEGIN_CLAUSE() {
					int64_t args[3] = {
			(int)eRemoteEvent::NetworkBail, g_player_service->get_selected()->id(),* script_global(1893548).at(1).at(g_player_service->get_selected()->id() * 600).at(511).as<int*>() };
					g_pointers->m_trigger_script_event(1, args, 3, 1 << g_player_service->get_selected()->id());
				}QUEUE_JOB_END_CLAUSE
			}

			if (ImGui::Button("Steal Outfit"))
			{
				g_fiber_pool->queue_job([]
					{
						Ped ped = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_player_service->get_selected()->id());
						Ped player_ped = PLAYER::PLAYER_PED_ID();
						PED::SET_PED_COMPONENT_VARIATION(player_ped, 1, PED::GET_PED_DRAWABLE_VARIATION(ped, 1), PED::GET_PED_TEXTURE_VARIATION(ped, 1), 0);
						//PED::SET_PED_COMPONENT_VARIATION(player_ped, 3, PED::GET_PED_DRAWABLE_VARIATION(ped, 3), 1, 0);
						PED::SET_PED_COMPONENT_VARIATION(player_ped, 4, PED::GET_PED_DRAWABLE_VARIATION(ped, 4), PED::GET_PED_TEXTURE_VARIATION(ped, 4), 0);
						//PED::SET_PED_COMPONENT_VARIATION(player_ped, 5, PED::GET_PED_DRAWABLE_VARIATION(ped, 5), 1, 0);
						PED::SET_PED_COMPONENT_VARIATION(player_ped, 6, PED::GET_PED_DRAWABLE_VARIATION(ped, 6), PED::GET_PED_TEXTURE_VARIATION(ped, 6), 0);
						PED::SET_PED_COMPONENT_VARIATION(player_ped, 7, PED::GET_PED_DRAWABLE_VARIATION(ped, 7), PED::GET_PED_TEXTURE_VARIATION(ped, 7), 0);
						PED::SET_PED_COMPONENT_VARIATION(player_ped, 8, PED::GET_PED_DRAWABLE_VARIATION(ped, 8), PED::GET_PED_TEXTURE_VARIATION(ped, 8), 0);
						PED::SET_PED_COMPONENT_VARIATION(player_ped, 9, PED::GET_PED_DRAWABLE_VARIATION(ped, 9), PED::GET_PED_TEXTURE_VARIATION(ped, 9), 0);
						PED::SET_PED_COMPONENT_VARIATION(player_ped, 10, PED::GET_PED_DRAWABLE_VARIATION(ped, 10), PED::GET_PED_TEXTURE_VARIATION(ped, 10), 0);
						PED::SET_PED_COMPONENT_VARIATION(player_ped, 11, PED::GET_PED_DRAWABLE_VARIATION(ped, 11), PED::GET_PED_TEXTURE_VARIATION(ped, 11), 0);
						PED::SET_PED_PROP_INDEX(player_ped, 0, PED::GET_PED_PROP_INDEX(ped, 0), PED::GET_PED_PROP_TEXTURE_INDEX(ped, 0), true);
						PED::SET_PED_PROP_INDEX(player_ped, 1, PED::GET_PED_PROP_INDEX(ped, 1), PED::GET_PED_PROP_TEXTURE_INDEX(ped, 1), true);
					});


			}

			ImGui::EndTabItem();
		}
	}
}