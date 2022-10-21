#include "views/view.hpp"
#include "natives.hpp"
#include "fiber_pool.hpp"
#include "pointers.hpp"
#include "services/players/player_service.hpp"
#include "services/chat/chat_service.hpp"

namespace big
{
	static size_t iLastLogCount = 0;
    void view::chat()
    {
		if (!g->window.chat || !*g_pointers->m_is_session_started) return;
		
		ImGui::SetNextWindowSize({ 450, 525 }, ImGuiCond_FirstUseEver);
		ImGui::SetNextWindowPos({ 1470, 250 }, ImGuiCond_FirstUseEver);
		if (ImGui::Begin("Chat"))
		{
			ImGui::PushFont(g->window.font_chat);

			ImGuiListClipper clipper;
			clipper.Begin((int)g_chat_service->get_msgs().size());
			while (clipper.Step())
				for (int i = clipper.DisplayStart; i < clipper.DisplayEnd; i++)
					ImGui::TextWrapped("%s [%s]  %s", g_chat_service->get_msgs()[i].player->get_name(), g_chat_service->get_msgs()[i].is_team ? "local" : "all", g_chat_service->get_msgs()[i].msg);


			if (iLastLogCount != g_chat_service->get_msgs().size())
			{
				iLastLogCount = g_chat_service->get_msgs().size();
				ImGui::SetScrollHereY(1.f);
			}

			components::input_text_with_hint("###Message", "Message", &g->chat.message, ImGuiInputTextFlags_EnterReturnsTrue, []
			{
				g_pointers->m_send_chat_message(*g_pointers->m_send_chat_ptr + 0x78, (__int64)g_local_player->m_player_info + 0x88, g->chat.message.c_str(), g->chat.local);
				g_chat_service->add_msg(g_player_service->get_self()->get_net_game_player(), g->chat.message, g->chat.local);
				LOG(INFO) << "NAME: " << g_player_service->get_self()->get_net_data()->m_name << ", RID: " << g_player_service->get_self()->get_net_data()->m_gamer_handle_2.m_rockstar_id << ", MSG: " << g->chat.message << ", LOCAL: " << g->chat.local;
			});
			ImGui::SameLine();
			ImGui::Checkbox("Local", &g->chat.local);

			ImGui::PopFont();

			ImGui::End();
		}
    }
}
