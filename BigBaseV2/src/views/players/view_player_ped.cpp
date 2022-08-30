#include "views/view.hpp"
#include "gta_util.hpp"
#include "services/pickups/pickup_service.hpp"
#include "services/players/player_service.hpp"
#include "services/anti_cheat/anti_cheat_service.hpp"
#include "util/globals.hpp"
#include "util/misc.hpp"
#include "util/ped.hpp"
#include "util/vehicle.hpp"
#include "util/teleport.hpp"
#include "util/toxic.hpp"
#include "gta/joaat.hpp"
#include "core/enums.hpp"

namespace big
{
	void view::view_player_ped()
	{
		if (!*g_pointers->m_is_session_started && g_player_service->get_selected()->is_valid()) return;

		std::string title = fmt::format("Player Ped Options: {}", g_player_service->get_selected()->get_name());

		ImGui::Text(title.c_str());

		components::button("Steal Outfit", [] {
			ped::steal_outfit(
				PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_player_service->get_selected()->id())
			);
		});

		ImGui::SameLine();

		components::button("Steal Identity", [] {
			ped::steal_identity(
				PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_player_service->get_selected()->id())
			);
		});

		components::button("Clear Wanted Level", [] {
			globals::clear_wanted_player(g_player_service->get_selected()->id());
		});

		ImGui::SameLine();

		ImGui::Checkbox("Never Wanted", &g_player_service->get_selected()->never_wanted);

		components::button("Give Health", [] {
			g_pickup_service->give_player_health(g_player_service->get_selected()->id());
		});

		ImGui::SameLine();

		components::button("Give Armour", [] {
			g_pickup_service->give_player_armour(g_player_service->get_selected()->id());
		});

		components::button("Give Ammo", [] {
			g_pickup_service->give_player_ammo(g_player_service->get_selected()->id());
		});

		ImGui::SameLine();

		components::button("Give Weapons", [] {
			g_pickup_service->give_player_weapons(g_player_service->get_selected()->id());
		});
	}
}