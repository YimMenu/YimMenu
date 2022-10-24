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

		std::string title = std::format("Player Ped Options: {}", g_player_service->get_selected()->get_name());

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

		components::button("Give All Weapons", [] {
			g_pickup_service->give_player_weapons(g_player_service->get_selected()->id());
		});

		std::string weapon_name;
		components::input_text_with_hint("###weapon_name", "Weapon Name. EG: weapon_unarmed", &weapon_name);

		components::button("Give Selected Weapon", [weapon_name] {
			Hash weaponHash = rage::joaat(weapon_name);
			WEAPON::GIVE_DELAYED_WEAPON_TO_PED(g_player_service->get_selected()->id(), weaponHash, 9999, false);
		});

		ImGui::SameLine();

		components::button("Remove Selected Weapon", [weapon_name] {
			Hash weaponHash = rage::joaat(weapon_name);
			WEAPON::REMOVE_WEAPON_FROM_PED(g_player_service->get_selected()->id(), weaponHash);
		});

		components::button("Turn Into Animal", [] {
			toxic::turn_player_into_animal(g_player_service->get_selected()->id());
		});
	}
}