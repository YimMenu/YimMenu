#include "views/view.hpp"
#include "natives.hpp"
#include "fiber_pool.hpp"
#include "pointers.hpp"
#include "services/players/player_service.hpp"
#include "services/chat/chat_service.hpp"
#include "util/notify.hpp"
#include "util/spam.hpp"

namespace big
{
	static size_t iLastLogCount = 0;
    void view::chat()
    {
		ImGui::Checkbox("Auto Scroll", &g->chat.auto_scroll);
		ImGui::SameLine();
		ImGui::Checkbox("Show spam", &g->chat.show_spam);

		const float footer_height_to_reserve = ImGui::GetStyle().ItemSpacing.y + ImGui::GetFrameHeightWithSpacing();
		ImGui::BeginChild("##scrolling_region_chat", ImVec2(0, -footer_height_to_reserve), false, ImGuiWindowFlags_HorizontalScrollbar);

		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(4, 1)); // Tighten spacing

		ImGuiListClipper clipper;
		clipper.Begin((int)g_chat_service->get_chat_msgs().size());
		while (clipper.Step())
		{
			for (int i = clipper.DisplayStart; i < clipper.DisplayEnd; i++)
			{
				chat_msg current_msg = g_chat_service->get_chat_msgs()[i];
				ImGui::Text(
					"%s [%s]  %s",
					current_msg.name.c_str(),
					current_msg.is_team ? "local" : "all",
					current_msg.msg.c_str()
				);
			}
		}

		if (g->chat.auto_scroll && ImGui::GetScrollY() >= ImGui::GetScrollMaxY())
			ImGui::SetScrollHereY(1.0f);

		ImGui::PopStyleVar();
		ImGui::EndChild();

		ImGui::Separator();

		components::input_text_with_hint("###Message", "Message", &g->chat.message, ImGuiInputTextFlags_EnterReturnsTrue, []
		{
			const auto net_game_player = g_player_service->get_self()->get_net_game_player();
			if(g_pointers->m_send_chat_message(*g_pointers->m_send_chat_ptr, net_game_player->get_net_data(), (char*)g->chat.message.c_str(), g->chat.local))
				notify::draw_chat((char*)g->chat.message.c_str(), net_game_player->get_name(), g->chat.local);

			g_chat_service->add_msg(net_game_player, g->chat.message, g->chat.local);
			spam::log_chat((char*)g->chat.message.c_str(), g_player_service->get_self(), false);
			
			g->chat.message = "";
		});

		ImGui::SameLine();
		ImGui::Checkbox("Local", &g->chat.local);
    }
}
