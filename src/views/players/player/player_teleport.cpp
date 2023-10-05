#include "views/view.hpp"

namespace big
{
	void view::player_teleport()
	{
		ImGui::BeginGroup();

		components::sub_title("Teleport");

		if (ImGui::BeginListBox("##teleport", get_listbox_dimensions()))
		{
			components::player_command_button<"playertp">(g_player_service->get_selected());
			ImGui::SameLine();
			components::player_command_button<"playervehtp">(g_player_service->get_selected());
			ImGui::SameLine();
			components::player_command_button<"bring">(g_player_service->get_selected());

			ImGui::EndListBox();
		}
		ImGui::EndGroup();
	}
}
