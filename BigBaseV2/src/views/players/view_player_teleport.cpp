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
	void view::view_player_teleport()
	{
		if (!*g_pointers->m_is_session_started && g_player_service->get_selected()->is_valid()) return;

		std::string title = std::format("Player Teleport Options: {}", g_player_service->get_selected()->get_name());

		ImGui::Text(title.c_str());

		components::button("Teleport", [] {
			teleport::to_player(g_player_service->get_selected()->id());
		});

		ImGui::SameLine();

		components::button("Bring", [] {
			teleport::bring_player(g_player_service->get_selected()->id());
		});

		components::button("Godmode kill", [] {
			teleport::teleport_player(g_player_service->get_selected()->id(), Vector3(8110, 20, 0));
			script::get_current()->yield(1s);
			entity::delete_entity_notp(PED::GET_VEHICLE_PED_IS_IN(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_player_service->get_selected()->id()), false));
		});

		ImGui::SameLine();

		components::button("Teleport into Vehicle", [] {
			Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_player_service->get_selected()->id()), false);

			teleport::into_vehicle(veh);
		});

		components::button("Send to Cayo Perico", [] {
			toxic::send_to_cayo_perico(g_player_service->get_selected()->id());
		});
	}
}