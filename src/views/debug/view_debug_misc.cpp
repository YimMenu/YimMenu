#include "gta/joaat.hpp"
#include "gta_util.hpp"
#include "gui/components/components.hpp"
#include "natives.hpp"
#include "network/Network.hpp"
#include "script.hpp"
#include "script_global.hpp"
#include "util/misc.hpp"
#include "util/system.hpp"
#include "view_debug.hpp"

namespace big
{
	void debug::misc()
	{
		if (ImGui::BeginTabItem("DEBUG_TAB_MISC"_T.data()))
		{
			ImGui::Text("Fiber Pool Usage %d/%d", g_fiber_pool->get_used_fibers(), g_fiber_pool->get_total_fibers());

			ImGui::SameLine();

			if (components::button("Reset"))
			{
				g_fiber_pool->reset();
			}

			if (components::button("Dump entrypoints"))
			{
				system::dump_entry_points();
			}

			components::button("Network Bail", [] {
				NETWORK::NETWORK_BAIL(16, 0, 0);
			});

			components::button("DEBUG_REMOVE_FROM_BAD_SPORT"_T, [] {
				STATS::STAT_SET_FLOAT(RAGE_JOAAT("mpply_overall_badsport"), 0.0f, TRUE);
				STATS::STAT_SET_BOOL(RAGE_JOAAT("mpply_was_i_bad_sport"), FALSE, TRUE);
			});

			components::button("Load MP Map", [] {
				DLC::ON_ENTER_MP();
			});

			ImGui::SameLine();

			components::button("Load SP Map", [] {
				DLC::ON_ENTER_SP();
			});

			components::button("Skip Cutscene", [] {
				CUTSCENE::STOP_CUTSCENE_IMMEDIATELY();
			});

			components::button("Refresh Interior", [] {
				Interior interior = INTERIOR::GET_INTERIOR_AT_COORDS(self::pos.x, self::pos.y, self::pos.z);
				INTERIOR::REFRESH_INTERIOR(interior);
			});

			components::button("Network Shutdown And Launch Single Player Game", [] {
				NETWORK::SHUTDOWN_AND_LAUNCH_SINGLE_PLAYER_GAME();
			});

			components::button("Network Shutdown And Load Most Recent Save", [] {
				NETWORK::SHUTDOWN_AND_LOAD_MOST_RECENT_SAVE();
			});

			components::command_button<"fastquit">();

			if (ImGui::TreeNode("Addresses"))
			{
				uint64_t local_cped = (uint64_t)g_local_player;
				ImGui::InputScalar("Local CPed", ImGuiDataType_U64, &local_cped, NULL, NULL, "%p", ImGuiInputTextFlags_CharsHexadecimal);

				if (g_local_player)
				{
					uint64_t local_playerinfo = (uint64_t)g_local_player->m_player_info;
					ImGui::InputScalar("Local CPlayerInfo", ImGuiDataType_U64, &local_playerinfo, NULL, NULL, "%p", ImGuiInputTextFlags_CharsHexadecimal);

					uint64_t local_vehicle = (uint64_t)g_local_player->m_vehicle;
					ImGui::InputScalar("Local CAutomobile", ImGuiDataType_U64, &local_vehicle, NULL, NULL, "%p", ImGuiInputTextFlags_CharsHexadecimal);
				}

				if (auto mgr = *g_pointers->m_network_player_mgr)
				{
					uint64_t local_netplayer = (uint64_t)mgr->m_local_net_player;
					ImGui::InputScalar("Local CNetGamePlayer", ImGuiDataType_U64, &local_netplayer, NULL, NULL, "%p", ImGuiInputTextFlags_CharsHexadecimal);

					if (mgr->m_local_net_player)
					{
						uint64_t local_netplayer = (uint64_t)mgr->m_local_net_player->get_net_data();
						ImGui::InputScalar("Local netPlayerData", ImGuiDataType_U64, &local_netplayer, NULL, NULL, "%p", ImGuiInputTextFlags_CharsHexadecimal);
					}
				}

				if (auto network = *g_pointers->m_network)
				{
					uint64_t nw = (uint64_t)network;
					ImGui::InputScalar("Network", ImGuiDataType_U64, &nw, NULL, NULL, "%p", ImGuiInputTextFlags_CharsHexadecimal);
				}

				if (auto omgr = *g_pointers->m_network_object_mgr)
				{
					uint64_t nw = (uint64_t)omgr;
					ImGui::InputScalar("Network Object Mgr", ImGuiDataType_U64, &nw, NULL, NULL, "%p", ImGuiInputTextFlags_CharsHexadecimal);
				}

				ImGui::TreePop();
			}

			ImGui::EndTabItem();
		}
	}
}