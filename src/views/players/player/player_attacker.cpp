#include "util/toxic.hpp"
#include "views/view.hpp"


namespace big
{
	void view::player_attacker()
	{
		if (ImGui::TreeNode("Attackers"))
		{
			components::button("Send Lazer", [] {
				toxic::Spawn_Attackers(VEHICLE_LAZER, 500);
			});
			ImGui::SameLine();
			components::button("Send Hydra", [] {
				toxic::Spawn_Attackers(VEHICLE_HYDRA, 500);
			});

			components::button("Send RC Tank", [] {
				toxic::Spawn_Attackers(VEHICLE_MINITANK, 1);
			});
			ImGui::SameLine();
			components::button("Send Vigilante", [] {
				toxic::Spawn_Attackers(VEHICLE_VIGILANTE, 20);
			});

			components::button("Send Buzzard", [] {
				toxic::Spawn_Attackers(VEHICLE_BUZZARD, 100);
			});
			ImGui::SameLine();
			components::button("Send Tank", [] {
				toxic::Spawn_Attackers(VEHICLE_RHINO, 5);
			});

			components::button("Gooch Test", [] {
				*script_global(1890140).at(244).at(1).as<Player*>() = g_player_service->get_selected()->id();
				scripts::start_launcher_script(171);
			});
			ImGui::SameLine();
			components::button("Mugger Test", [] {
				*script_global(1853348).at(834).at(1).as<Player*>() = g_player_service->get_selected()->id();
				scripts::start_launcher_script(141);
			});

			ImGui::TreePop();
		}
	}
}