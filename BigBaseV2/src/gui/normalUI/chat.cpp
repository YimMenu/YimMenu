#include "views/view.hpp"
/*#include "natives.hpp"
#include "fiber_pool.hpp"
#include "hooks/chat/chat.hpp"
#include "pointers.hpp"
#include "services/players/player_service.hpp"*/

namespace big
{
	//static size_t iLastLogCount = 0;
    void view::chat()
    {
		/*if (!g->window.chat || !*g_pointers->m_is_session_started) return;
		
		ImGui::SetNextWindowSize({ 450, 525 }, ImGuiCond_FirstUseEver);
		ImGui::SetNextWindowPos({ 1470, 250 }, ImGuiCond_FirstUseEver);
		if (ImGui::Begin("Chat"))
		{
			ImGui::PushFont(g->window.font_chat);

			for (size_t i = 0; i < all_messages.size(); i++) {
				ImGui::TextWrapped(fmt::format("{}: {}", all_messages[i].player_name, all_messages[i].message).c_str());
			}

			if (iLastLogCount != all_messages.size())
			{
				iLastLogCount = all_messages.size();
				ImGui::SetScrollHereY(1.f);
			}
			ImGui::End();
		}
		if (ImGui::Begin("##text_input"))
		{
			static char message[255] = "";
			static bool local = false;
			components::input_text_with_hint("###Message", "Message", message, sizeof(message), ImGuiInputTextFlags_EnterReturnsTrue, []
			{
				g_pointers->m_send_chat_message(*g_pointers->m_send_chat_ptr + 0x78, (__int64)g_local_player->m_player_info + 0x88, message, local);
				all_messages.push_back({ message, g_player_service->get_self()->get_net_data()->m_name, 0 });
				LOG(INFO) << "NAME: " << g_player_service->get_self()->get_net_data()->m_name << ", RID: " << g_player_service->get_self()->get_net_data()->m_rockstar_id2 << ", MSG: " << message << ", LOCAL: " << local;
			});
			ImGui::SameLine();
			ImGui::Checkbox("Local", &local);

			ImGui::PopFont();

			ImGui::End();
		}*/
    }
}
