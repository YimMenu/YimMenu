#include "views/view.hpp"

namespace big
{
	void view::player_misc()
	{
		ImGui::BeginGroup();
		components::sub_title("Misc");
		if (ImGui::BeginListBox("##misc", get_listbox_dimensions()))
		{
			components::player_command_button<"joinceo">(g_player_service->get_selected());
			ImGui::SameLine();
			components::player_command_button<"copyoutfit">(g_player_service->get_selected());
			ImGui::SameLine();
			components::player_command_button<"clearwanted">(g_player_service->get_selected());

			components::player_command_button<"givehealth">(g_player_service->get_selected());
			ImGui::SameLine();
			components::player_command_button<"givearmor">(g_player_service->get_selected());
			ImGui::SameLine();
			components::player_command_button<"giveammo">(g_player_service->get_selected());

			ImGui::EndListBox();
		}

		ImGui::EndGroup();
	}
}