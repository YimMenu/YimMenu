#include "core/scr_globals.hpp"
#include "util/toxic.hpp"
#include "views/view.hpp"

#include <script/globals/GPBD_FM.hpp>

namespace big
{
	void view::player_attacker()
	{
		if (ImGui::TreeNode("Attackers"))
		{
			components::button("Send Lazer", [] {
				toxic::spawn_attackers(VEHICLE_LAZER, 500);
			});
			ImGui::SameLine();
			components::button("Send Hydra", [] {
				toxic::spawn_attackers(VEHICLE_HYDRA, 500);
			});

			components::button("Send RC Tank", [] {
				toxic::spawn_attackers(VEHICLE_MINITANK, 1);
			});
			ImGui::SameLine();
			components::button("Send Vigilante", [] {
				toxic::spawn_attackers(VEHICLE_VIGILANTE, 20);
			});

			components::button("Send Buzzard", [] {
				toxic::spawn_attackers(VEHICLE_BUZZARD, 100);
			});
			ImGui::SameLine();
			components::button("Send Tank", [] {
				toxic::spawn_attackers(VEHICLE_RHINO, 5);
			});

			components::button("Send Gooch", [] {
				*script_global(1890140).at(244).at(1).as<Player*>() = g_player_service->get_selected()->id();
				scripts::start_launcher_script(171);
			});
			ImGui::SameLine();
			components::button("Send Mugger", [] {
				scr_globals::gpbd_fm_1.as<GPBD_FM*>()->Entries[self::id].GangCallRequestedServices = 0;
				scr_globals::gpbd_fm_1.as<GPBD_FM*>()->Entries[self::id].GangCallTarget =
				    g_player_service->get_selected()->id();
			});

			ImGui::TreePop();
		}
	}
}