#include "views/view.hpp"
#include "util/teleport.hpp"
#include "core/scr_globals.hpp"
#include "util/ped.hpp"
#include "util/vehicle.hpp"
#include "util/globals.hpp"
#include "services/pickups/pickup_service.hpp"
#include "gta/net_object_mgr.hpp"
#include "util/scripts.hpp"
#include "util/session.hpp"
#include "script_function.hpp"

namespace big
{
	void view::player_misc()
	{
		if (ImGui::TreeNode("Misc"))
		{
			components::player_command_button<"joinceo">(g_player_service->get_selected());
			components::player_command_button<"enterint">(g_player_service->get_selected());
			components::player_command_button<"copyoutfit">(g_player_service->get_selected());
			ImGui::SameLine();
			components::player_command_button<"copymodel">(g_player_service->get_selected());
			components::player_command_button<"clearwanted">(g_player_service->get_selected());
			ImGui::SameLine();
			components::player_command_button<"givehealth">(g_player_service->get_selected());
			ImGui::SameLine();
			components::player_command_button<"givearmor">(g_player_service->get_selected());
			ImGui::SameLine();
			components::player_command_button<"giveammo">(g_player_service->get_selected());

			ImGui::Checkbox("Off The Radar", &g_player_service->get_selected()->off_radar);
			ImGui::Checkbox("Never Wanted", &g_player_service->get_selected()->never_wanted);
			ImGui::Checkbox("Semi Godmode", &g_player_service->get_selected()->semi_godmode);
			ImGui::TreePop();
		}
	}
}