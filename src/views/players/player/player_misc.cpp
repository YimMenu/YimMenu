#include "backend/commands/player/misc/clear_wanted_level.hpp"
#include "backend/commands/player/misc/enter_interior.hpp"
#include "backend/commands/player/misc/give_ammo.hpp"
#include "backend/commands/player/misc/give_armor.hpp"
#include "backend/commands/player/misc/give_health.hpp"
#include "backend/commands/player/misc/join_ceo.hpp"
#include "backend/commands/player/misc/steal_identity.hpp"
#include "backend/commands/player/misc/steal_outfit.hpp"
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
			components::player_command_button(&cmd::g_join_ceo);
			components::player_command_button(&cmd::g_enter_interior);
			components::player_command_button(&cmd::g_steal_outfit);
			ImGui::SameLine();
			components::player_command_button(&cmd::g_steal_identity);
			components::player_command_button(&cmd::g_clear_wanted_level);
			ImGui::SameLine();
			components::player_command_button(&cmd::g_give_health);
			ImGui::SameLine();
			components::player_command_button(&cmd::g_give_armor);
			ImGui::SameLine();
			components::player_command_button(&cmd::g_give_ammo);

			const auto target = g_player_service->get_selected();

			ImGui::Checkbox("OFF_THE_RADAR"_T.data(), &target->off_radar);
			ImGui::Checkbox("NEVER_WANTED"_T.data(), &target->never_wanted);
			ImGui::Checkbox("SEMI_GODMODE"_T.data(), &target->semi_godmode);

			components::button("Gooch Test", [] {
				*script_global(1890140).at(244).at(1).as<Player*>() = g_player_service->get_selected()->id();
				scripts::start_launcher_script(171);
			});

			ImGui::TreePop();
		}
	}
}
