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
		const float footer_height_to_reserve = ImGui::GetStyle().ItemSpacing.y + ImGui::GetFrameHeightWithSpacing();
		ImGui::BeginChild("##scrolling_region_chat", ImVec2(0, -footer_height_to_reserve), false, ImGuiWindowFlags_HorizontalScrollbar);

		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(4, 1)); // Tighten spacing

		ImGuiListClipper clipper;
		clipper.Begin((int)g_chat_service->get_msgs().size());
		while (clipper.Step())
		{
			for (int i = clipper.DisplayStart; i < clipper.DisplayEnd; i++)
			{
				CNetGamePlayer* net_player = g_chat_service->get_msgs()[i].player;
				std::string name = net_player->get_name();
				std::string msg = g_chat_service->get_msgs()[i].msg;
				bool is_team = g_chat_service->get_msgs()[i].is_team;
				ImGui::TextWrapped("%s [%s]  %s", name.c_str(), is_team ? "local" : "all", msg.c_str());
			}
		}

		ImGui::PopStyleVar();

		if (g->chat.auto_scroll && ImGui::GetScrollY() >= ImGui::GetScrollMaxY())
			ImGui::SetScrollHereY(1.0f);

		ImGui::EndChild();
		ImGui::Separator();

		bool reclaim_focus = false;
		ImGuiInputTextFlags input_text_flags = ImGuiInputTextFlags_EnterReturnsTrue | ImGuiInputTextFlags_CallbackCompletion | ImGuiInputTextFlags_CallbackHistory;
		components::input_text_with_hint("###Message", "Message", &g->chat.message, input_text_flags, [&reclaim_focus]
		{
			g_pointers->m_send_chat_message(*g_pointers->m_send_chat_ptr + 0x78, (__int64)g_local_player->m_player_info + 0x88, g->chat.message.c_str(), g->chat.local);
			g_chat_service->add_msg(g_player_service->get_self()->get_net_game_player(), g->chat.message, g->chat.local);
			LOG(INFO) << g_player_service->get_self()->get_net_game_player()->get_name() << (g->chat.local ? " [LOCAL] " : " [ALL] ") << g->chat.message;
			g->chat.message = "";
			reclaim_focus = true;
		});

		// Auto-focus on window apparition
		ImGui::SetItemDefaultFocus();
		if (reclaim_focus)
			ImGui::SetKeyboardFocusHere(-1); // Auto focus previous widget

		ImGui::SameLine();
		ImGui::Checkbox("Local", &g->chat.local);
    }
}
