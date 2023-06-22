#include "gta/joaat.hpp"
#include "gta_util.hpp"
#include "gui/components/components.hpp"
#include "natives.hpp"
#include "network/Network.hpp"
#include "script.hpp"
#include "script_global.hpp"
#include "util/misc.hpp"
#include "util/pathfind.hpp"
#include "util/ped.hpp"
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

			if (components::button("RESET"_T.data()))
			{
				g_fiber_pool->reset();
			}

			if (components::button("DUMP_ENTRYPOINTS"_T.data()))
			{
				system::dump_entry_points();
			}

			components::button("NETWORK_BAIL"_T.data(), [] {
				NETWORK::NETWORK_BAIL(16, 0, 0);
			});

			components::button("DEBUG_REMOVE_FROM_BAD_SPORT"_T, [] {
				STATS::STAT_SET_INT(RAGE_JOAAT("MPPLY_BADSPORT_MESSAGE"), 0, 1);
				STATS::STAT_SET_INT(RAGE_JOAAT("MPPLY_BECAME_BADSPORT_NUM"), 0, 1);
				STATS::STAT_SET_FLOAT(RAGE_JOAAT("MPPLY_OVERALL_BADSPORT"), 0, true);
				STATS::STAT_SET_BOOL(RAGE_JOAAT("MPPLY_CHAR_IS_BADSPORT"), false, true);
			});

			components::button("LOAD_MP_MAP"_T.data(), [] {
				DLC::ON_ENTER_MP();
			});

			ImGui::SameLine();

			components::button("LOAD_SP_MAP"_T.data(), [] {
				DLC::ON_ENTER_SP();
			});

			components::button("SKIP_CUTSCENE"_T.data(), [] {
				CUTSCENE::STOP_CUTSCENE_IMMEDIATELY();
			});

			components::button("REFRESH_INTERIOR"_T.data(), [] {
				Interior interior = INTERIOR::GET_INTERIOR_AT_COORDS(self::pos.x, self::pos.y, self::pos.z);
				INTERIOR::REFRESH_INTERIOR(interior);
			});

			components::button("NET_SHUTDOWN_AND_LOAD_SP"_T.data(), [] {
				NETWORK::SHUTDOWN_AND_LAUNCH_SINGLE_PLAYER_GAME();
			});

			components::button("NET_SHUTDOWN_AND_LOAD_SAVE"_T.data(), [] {
				NETWORK::SHUTDOWN_AND_LOAD_MOST_RECENT_SAVE();
			});

			components::button("REMOVE_BLACKSCREEN"_T.data(), [] {
				CAM::DO_SCREEN_FADE_IN(0);
			});

			components::button("TP_TO_SAFE_POS"_T.data(), [] {
				Vector3 safepos{};
				float heading;
				if (pathfind::find_closest_vehicle_node(self::pos, safepos, heading, 0))
					ENTITY::SET_ENTITY_COORDS(self::ped, safepos.x, safepos.y, safepos.z, 0, 0, 0, false);
				else
					g_notification_service->push_error("Find safe pos", "Failed to find a safe position");
			});

			components::command_button<"fastquit">();

			if (ImGui::TreeNode("ADDRESSES"_T.data()))
			{
				uint64_t local_cped = (uint64_t)g_local_player;
				ImGui::InputScalar("Local_CPED"_T.data(), ImGuiDataType_U64, &local_cped, NULL, NULL, "%p", ImGuiInputTextFlags_CharsHexadecimal);

				if (g_local_player)
				{
					uint64_t local_playerinfo = (uint64_t)g_local_player->m_player_info;
					ImGui::InputScalar("LOCAL_CPLAYERINFO"_T.data(), ImGuiDataType_U64, &local_playerinfo, NULL, NULL, "%p", ImGuiInputTextFlags_CharsHexadecimal);

					uint64_t local_vehicle = (uint64_t)g_local_player->m_vehicle;
					ImGui::InputScalar("LOCAL_CAUTOMOBILE"_T.data(), ImGuiDataType_U64, &local_vehicle, NULL, NULL, "%p", ImGuiInputTextFlags_CharsHexadecimal);
				}

				if (auto mgr = *g_pointers->m_gta.m_network_player_mgr)
				{
					uint64_t local_netplayer = (uint64_t)mgr->m_local_net_player;
					ImGui::InputScalar("LOCAL_CNETGAMEPLAYER"_T.data(), ImGuiDataType_U64, &local_netplayer, NULL, NULL, "%p", ImGuiInputTextFlags_CharsHexadecimal);

					if (mgr->m_local_net_player)
					{
						uint64_t local_netplayer = (uint64_t)mgr->m_local_net_player->get_net_data();
						ImGui::InputScalar("LOCAL_NETPLAYERDATA"_T.data(), ImGuiDataType_U64, &local_netplayer, NULL, NULL, "%p", ImGuiInputTextFlags_CharsHexadecimal);
					}
				}

				if (auto network = *g_pointers->m_gta.m_network)
				{
					uint64_t nw = (uint64_t)network;
					ImGui::InputScalar("NETWORK"_T.data(), ImGuiDataType_U64, &nw, NULL, NULL, "%p", ImGuiInputTextFlags_CharsHexadecimal);
				}

				if (auto omgr = *g_pointers->m_gta.m_network_object_mgr)
				{
					uint64_t nw = (uint64_t)omgr;
					ImGui::InputScalar("NETWORK_OBJ_MGR"_T.data(), ImGuiDataType_U64, &nw, NULL, NULL, "%p", ImGuiInputTextFlags_CharsHexadecimal);
				}

				ImGui::TreePop();
			}

			if (ImGui::TreeNode("ANIMATION_PLAYER"_T.data()))
			{
				static char dict[100], anim[100];

				ImGui::PushItemWidth(200);
				components::input_text_with_hint("##dictionary", "DICT"_T.data(), dict, IM_ARRAYSIZE(dict));
				components::input_text_with_hint("##animation", "ANIMATION"_T.data(), anim, IM_ARRAYSIZE(anim));
				if (ImGui::Button("PLAY_ANIMATION"_T.data()))
					g_fiber_pool->queue_job([=] {
						ped::ped_play_animation(self::ped, dict, anim);
					});
				ImGui::PopItemWidth();
				ImGui::TreePop();
			}

			ImGui::EndTabItem();
		}
	}
}
