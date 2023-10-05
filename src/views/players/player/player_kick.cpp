#include "views/view.hpp"

namespace big
{
	void view::player_kick()
	{
		ImGui::BeginGroup();
		components::sub_title("Kick");
		if (ImGui::BeginListBox("##kick", get_listbox_dimensions()))
		{
			if (g_player_service->get_self()->is_host())
				components::player_command_button<"hostkick">(g_player_service->get_selected());
			else
			{
				components::player_command_button<"shkick">(g_player_service->get_selected());
				components::player_command_button<"nfkick">(g_player_service->get_selected());
				components::player_command_button<"endkick">(g_player_service->get_selected());
				components::player_command_button<"desync">(g_player_service->get_selected());

				components::player_command_button<"multikick">(g_player_service->get_selected());
			}

			ImGui::EndListBox();
		}

		ImGui::EndGroup();
	}
}