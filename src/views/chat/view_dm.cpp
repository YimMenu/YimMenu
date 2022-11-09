 
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
			for (const auto& [_, player] : g_player_service->players())
			{
				if (components::selectable(player->get_name(), g->chat.dm_player_id == player->id()))
				{
					g->chat.dm_player_id = player->id();
				}
			}
			ImGui::EndChild();
		}
		ImGui::SameLine();
		{
			ImGui::BeginGroup();
			const float footer_height_to_reserve = ImGui::GetStyle().ItemSpacing.y + ImGui::GetFrameHeightWithSpacing();
			ImGui::BeginChild("##scrolling_region_dm", ImVec2(0, -footer_height_to_reserve), false, ImGuiWindowFlags_HorizontalScrollbar);

			ImGui::Text("Sends a phone message, requires voice chat to be on. \nTODO: DM History.");

			ImGui::EndChild();

			ImGui::Separator();

			ImGuiInputTextFlags input_text_flags = ImGuiInputTextFlags_EnterReturnsTrue | ImGuiInputTextFlags_CallbackCompletion | ImGuiInputTextFlags_CallbackHistory;
			components::input_text_with_hint("###Message", "Message", &g->chat.dm_message, input_text_flags, [&]
			{
				int handle;
				NETWORK::NETWORK_HANDLE_FROM_PLAYER(g->chat.dm_player_id, &handle, 13);
				if (NETWORK::NETWORK_IS_HANDLE_VALID(&handle, 13))
					NETWORK::NETWORK_SEND_TEXT_MESSAGE(g->chat.dm_message.c_str(), &handle);
				g->chat.dm_message = "";
			});

			ImGui::EndGroup();
		}
	}
}
