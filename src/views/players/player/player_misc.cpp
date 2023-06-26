#include "script/globals/GPBD_FM_3.hpp"
#include "services/script_connection/script_connection_service.hpp"
#include "util/scripts.hpp"
#include "util/vehicle.hpp"
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
			components::player_command_button<"enterint">(g_player_service->get_selected());
			components::player_command_button<"copyoutfit">(g_player_service->get_selected());
			ImGui::SameLine();
			components::player_command_button<"copymodel">(g_player_service->get_selected());
			components::player_command_button<"clearwanted">(g_player_service->get_selected());
			ImGui::SameLine();
			components::player_command_button<"givehealth">(g_player_service->get_selected());
			ImGui::SameLine();
			components::player_command_button<"givearmor">(g_player_service->get_selected());
			components::player_command_button<"giveammo">(g_player_service->get_selected());
			ImGui::SameLine();
			components::player_command_button<"giveweaps">(g_player_service->get_selected(), {});

			ImGui::Checkbox("OFF_THE_RADAR"_T.data(), &g_player_service->get_selected()->off_radar);
			ImGui::Checkbox("NEVER_WANTED"_T.data(), &g_player_service->get_selected()->never_wanted);
			ImGui::Checkbox("SEMI_GODMODE"_T.data(), &g_player_service->get_selected()->semi_godmode);

			ImGui::EndListBox();
		}

		ImGui::EndGroup();
	}
}