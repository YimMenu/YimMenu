#include "script/globals/GPBD_FM_3.hpp"
#include "util/scripts.hpp"
#include "util/vehicle.hpp"
#include "views/view.hpp"

namespace big
{
	void view::player_misc()
	{
		if (ImGui::TreeNode("MISC"_T.data()))
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

			ImGui::Checkbox("OFF_THE_RADAR"_T.data(), &g_player_service->get_selected()->off_radar);
			ImGui::Checkbox("NEVER_WANTED"_T.data(), &g_player_service->get_selected()->never_wanted);
			ImGui::Checkbox("SEMI_GODMODE"_T.data(), &g_player_service->get_selected()->semi_godmode);

			components::button("Gooch Test", [] {
				*script_global(1890140).at(244).at(1).as<Player*>() = g_player_service->get_selected()->id();
				scripts::start_launcher_script(171);
			});

			components::button("Car Test", [] {
				using migrate_object_t          = void (*)(CNetGamePlayer * player, rage::netObject * object, int type);
				migrate_object_t migrate_object = (migrate_object_t)((__int64)GetModuleHandleA(0) + 0x11b27dc);
			});

			ImGui::TreePop();
		}
	}
}