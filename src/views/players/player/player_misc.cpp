#include "views/view.hpp"
#include "services/players/player_service.hpp"
#include "util/scripts.hpp"

namespace big
{
	void view::player_misc()
	{ 
		ImGui::SeparatorText("DEBUG_TAB_MISC"_T.data());

		ImGui::BeginGroup();
		components::player_command_button<"joinceo">(g_player_service->get_selected());
		components::player_command_button<"enterint">(g_player_service->get_selected());
		components::player_command_button<"copyoutfit">(g_player_service->get_selected());
		components::player_command_button<"copymodel">(g_player_service->get_selected());
		components::player_command_button<"clearwanted">(g_player_service->get_selected());
		ImGui::EndGroup();

		ImGui::SameLine();

		ImGui::BeginGroup();
		components::player_command_button<"givehealth">(g_player_service->get_selected());
		components::player_command_button<"givearmor">(g_player_service->get_selected());
		components::player_command_button<"giveammo">(g_player_service->get_selected());
		components::player_command_button<"giveweaps">(g_player_service->get_selected(), {});
		ImGui::EndGroup();

		ImGui::SameLine();

		ImGui::BeginGroup();
		ImGui::Checkbox("OFF_THE_RADAR"_T.data(), &g_player_service->get_selected()->off_radar);
		ImGui::Checkbox("NEVER_WANTED"_T.data(), &g_player_service->get_selected()->never_wanted);
		ImGui::Checkbox("SEMI_GODMODE"_T.data(), &g_player_service->get_selected()->semi_godmode);
		ImGui::Checkbox("VIEW_NET_SESSION_FIX_VEHICLE"_T.data(), &g_player_service->get_selected()->fix_vehicle);

		components::button("Trigger UFO Abduction", [] {
			scripts::force_host("freemode"_J);
			g_player_service->get_selected()->script_host_mission = 9999;
			scripts::force_script_on_player(g_player_service->get_selected(), "fm_content_ufo_abduction"_J, g_player_service->get_selected()->id());
			for (int i = 0; i < 10; i++)
			{
				memset(scr_globals::gsbd_fm_events.at(11).at(143).as<void*>(), __rdtsc(), sizeof(std::uint64_t) * 4);
				script::get_current()->yield(30ms);
			}
		});

		// Broken
		components::button("Trigger Pizza Delivery", [] {
			scripts::force_host("freemode"_J);
			g_player_service->get_selected()->script_host_mission = 9999;
			scripts::force_script_on_player(g_player_service->get_selected(), "fm_content_pizza_delivery"_J);
			for (int i = 0; i < 10; i++)
			{
				memset(scr_globals::gsbd_fm_events.at(11).at(143).as<void*>(), __rdtsc(), sizeof(std::uint64_t) * 4);
				script::get_current()->yield(30ms);
			}
		});

		ImGui::EndGroup();
	}
}