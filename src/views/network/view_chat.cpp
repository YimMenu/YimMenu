#include "core/settings/session.hpp"
#include "gta_util.hpp"
#include "gui.hpp"
#include "hooking.hpp"
#include "services/custom_chat_buffer.hpp"
#include "util/notify.hpp"
#include "views/view.hpp"

namespace big
{
	void view::chat()
	{
		static bool is_team;
		static char msg[256];

		ImGui::Checkbox("Log Messages (to file)", &g_session.log_chat_messages_to_file);
		ImGui::Checkbox("Log Messages (to textbox)", &g_session.log_chat_messages_to_textbox);

		ImGui::Spacing();

		ImGui::SetNextItemWidth(300);
		components::input_text_with_hint("##message", "Message", msg, sizeof(msg));
		ImGui::Checkbox("Is Team Message", &is_team);
		ImGui::SameLine();
		if (components::button("Send Message"))
		{
			g_gui->toggle(false); // trying to prevent game crash?
			g_fiber_pool->queue_job([] {
				if (const auto net_game_player = gta_util::get_network_player_mgr()->m_local_net_player)
					if (g_hooking->get_original<hooks::send_chat_message>()(*g_pointers->m_gta.m_send_chat_ptr,
					        net_game_player->get_net_data(),
					        msg,
					        is_team))
						notify::draw_chat(msg, net_game_player->get_name(), is_team);
			});
		};

		ImGui::Spacing();

		components::button("Reset Chat", [] {
			g_custom_chat_buffer.reset_buf();
		});
		ImGui::InputTextMultiline("##Text", g_custom_chat_buffer.buf, sizeof(g_custom_chat_buffer.buf), {600, 300}, ImGuiInputTextFlags_ReadOnly);
	}
}