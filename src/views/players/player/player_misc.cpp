#include "views/view.hpp"
#include "util/teleport.hpp"
#include "core/scr_globals.hpp"
#include "util/ped.hpp"
#include "util/vehicle.hpp"
#include "util/globals.hpp"
#include "services/pickups/pickup_service.hpp"
#include "gta/net_object_mgr.hpp"
#include "util/scripts.hpp"

namespace big
{
	void view::player_misc()
	{
		if (ImGui::TreeNode("Misc"))
		{
			components::button("Join CEO/MC", []
			{
				*scr_globals::gpbd_fm_3.at(self::id, scr_globals::size::gpbd_fm_3).at(10).as<int*>() = g_player_service->get_selected()->id();
				*scr_globals::gpbd_fm_3.at(self::id, scr_globals::size::gpbd_fm_3).at(10).at(26).as<int*>() = g_player_service->get_selected()->id();
			});

			components::button("Steal Outfit", []
			{
				ped::steal_outfit(
					PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_player_service->get_selected()->id())
				);
			});

			ImGui::SameLine();

			components::button("Steal Identity", []
			{
				ped::steal_identity(
					PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_player_service->get_selected()->id())
				);
			});

			components::button("Clear Wanted Level", []
			{
				globals::clear_wanted_player(g_player_service->get_selected()->id());
			});

			ImGui::SameLine();

			components::button("Give Health", []
			{
				g_pickup_service->give_player_health(g_player_service->get_selected()->id());
			});

			ImGui::SameLine();

			components::button("Give Armour", []
			{
				g_pickup_service->give_player_armour(g_player_service->get_selected()->id());
			});

			components::button("Give Ammo", []
			{
				g_pickup_service->give_player_ammo(g_player_service->get_selected()->id());
			});

			ImGui::Checkbox("Off The Radar", &g_player_service->get_selected()->off_radar);
			ImGui::Checkbox("Never Wanted", &g_player_service->get_selected()->never_wanted);
			ImGui::Checkbox("Semi Godmode", &g_player_service->get_selected()->semi_godmode);
			ImGui::TreePop();
		}
	}
}