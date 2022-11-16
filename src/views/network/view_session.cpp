#include "views/view.hpp"
#include "fiber_pool.hpp"
#include "util/session.hpp"
#include "core/data/region_codes.hpp"
#include "gta_util.hpp"
#include "util/notify.hpp"

namespace big
{
	void view::session()
	{
		static uint64_t rid = 0;
		ImGui::InputScalar("Input RID", ImGuiDataType_U64, &rid);
		components::button("Join RID", []
		{
			session::join_by_rockstar_id(rid);
		});

		components::sub_title("Session Switcher");
		if (ImGui::ListBoxHeader("###session_switch"))
		{
			for (const auto& session_type : sessions)
			{
				components::selectable(session_type.name, false, [&session_type]
				{
					session::join_type(session_type.id);
				});
			}
			ImGui::EndListBox();
		}
		
		components::sub_title("Region Switcher");
		if (ImGui::ListBoxHeader("###region_switch"))
		{
			for (const auto& region_type : regions)
			{
				components::selectable(region_type.name, *g_pointers->m_region_code == region_type.id, [&region_type]
				{
					*g_pointers->m_region_code = region_type.id;
				});
			}
			ImGui::EndListBox();
		}

		components::sub_title("Player Magnet");
		ImGui::Checkbox("Enabled", &g->session.player_magnet_enabled);
		if (g->session.player_magnet_enabled)
		{
			ImGui::InputInt("Player Count", &g->session.player_magnet_count);
		}

		components::sub_title("Chat");
		ImGui::Checkbox("Disable Filter", &g->session.disable_chat_filter);
		ImGui::Checkbox("Log Chat Messages", &g->session.log_chat_messages);
		ImGui::Checkbox("Log Text Messages", &g->session.log_text_messages);
		static char msg[256];
		ImGui::InputText("##message", msg, sizeof(msg));
		ImGui::SameLine();
		ImGui::Checkbox("Is Team", &g->session.is_team);
		ImGui::SameLine();
		components::button("Send", []
		{
            if(const auto net_game_player = gta_util::get_network_player_mgr()->m_local_net_player; net_game_player)
			{
                if(g_pointers->m_send_chat_message(*g_pointers->m_send_chat_ptr, net_game_player->get_net_data(), msg, g->session.is_team))
					notify::draw_chat(msg, net_game_player->get_name(), g->session.is_team);
			}
		});

		components::sub_title("Decloak");
		components::script_patch_checkbox("Reveal OTR Players", &g->session.decloak_players);

		components::sub_title("Force Host");
		ImGui::Checkbox("Force Session Host", &g->session.force_session_host);
		if (ImGui::IsItemHovered())
			ImGui::SetTooltip("Join another session to apply changes. The original host of the session must leave or be kicked. This feature is easily detectable by other mod menus, use with caution");
	}
}
