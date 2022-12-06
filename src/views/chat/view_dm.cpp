 
#include "views/view.hpp"
#include "natives.hpp"
#include "fiber_pool.hpp"
#include "pointers.hpp"
#include "services/players/player_service.hpp"
#include "services/chat/chat_service.hpp"

namespace big
{
	void view::chat_dm()
	{
		{
			ImGui::BeginChild("##dm_player_selector", ImVec2(150, 0), true);
			g_player_service->iterate([](const player_entry& entry)
			{
				if (components::selectable(entry.first, g->chat.dm_player_id == entry.second->id()))
				{
					g->chat.dm_player_id = entry.second->id();
					g->chat.dm_player_rid = entry.second->get_net_data()->m_gamer_handle_2.m_rockstar_id; // TODO: Use real rid.
				}
			});
			ImGui::EndChild();
		}
		ImGui::SameLine();
		{
			ImGui::BeginGroup();
			const float footer_height_to_reserve = ImGui::GetStyle().ItemSpacing.y + ImGui::GetFrameHeightWithSpacing();
			ImGui::BeginChild("##scrolling_region_dm", ImVec2(0, -footer_height_to_reserve), false, ImGuiWindowFlags_HorizontalScrollbar);

			ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(4, 1)); // Tighten spacing

			ImGui::Text("Sends a phone message, requires voice chat to be on.\nCarefull this feature sends metrics.");

			ImGuiListClipper clipper;
			clipper.Begin((int)g_chat_service->get_direct_msgs().size());
			while (clipper.Step())
			{
				for (int i = clipper.DisplayStart; i < clipper.DisplayEnd; i++)
				{
					direct_msg current_msg = g_chat_service->get_direct_msgs()[i];
					uint64_t rid_sender = current_msg.rid_sender;
					uint64_t rid_receiver = current_msg.rid_receiver;
					if(
						(g->chat.dm_player_rid == rid_sender) || 
						(rid_sender == g_player_service->get_self()->get_net_data()->m_gamer_handle_2.m_rockstar_id && rid_receiver == g->chat.dm_player_rid)
					)
					{
						ImGui::Text(
							"%s: %s",
							current_msg.name_sender.c_str(),
							current_msg.msg.c_str()
						);
					}
				}
			}

			if (g->chat.auto_scroll && ImGui::GetScrollY() >= ImGui::GetScrollMaxY())
				ImGui::SetScrollHereY(1.0f);

			ImGui::PopStyleVar();

			ImGui::EndChild();

			ImGui::Separator();
			

			ImGuiInputTextFlags input_text_flags = ImGuiInputTextFlags_EnterReturnsTrue | ImGuiInputTextFlags_CallbackCompletion | ImGuiInputTextFlags_CallbackHistory;
			components::input_text_with_hint("###Message", "Message", &g->chat.dm_message, input_text_flags, [&]
			{
				int handle;
				NETWORK::NETWORK_HANDLE_FROM_PLAYER(g->chat.dm_player_id, &handle, 13);
				if (NETWORK::NETWORK_IS_HANDLE_VALID(&handle, 13))
					NETWORK::NETWORK_SEND_TEXT_MESSAGE(g->chat.dm_message.c_str(), &handle);
				g_chat_service->add_direct_msg(
					g_player_service->get_self()->get_net_game_player(),
					g_player_service->get_by_id(g->chat.dm_player_id)->get_net_game_player(),
					g->chat.dm_message,
					false
				);
				g->chat.dm_message = "";
			});

			ImGui::EndGroup();
		}
	}
}
