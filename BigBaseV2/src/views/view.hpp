#pragma once
#include "gui/components/components.hpp"
#include "util/animator.hpp"
#include "views/esp/view_esp.hpp"


namespace big
{
	class view
	{
		inline static animator window_animator = animator();
		inline static ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoCollapse;

	public:
		static void main_view();
		static void debug_scripts();
		static void debug_script_events();
		static void debug_globals();
		static void debug_ped_flags();
		static void debug_misc();
		static void debug_tabs();
		static void esp_settings();
		static void context_menu_settings();
		static void gui_settings();
		static void handling_tabs();
		static void handling_current_profile();
		static void handling_my_profiles();
		static void handling_saved_profiles();
		static void handling_search();
		static void notification_settings();
		static void protection_settings();
		static void heading();
		static void mobile();
		static void notifications();
		static void spinner();
		static void root();
		static void self_tabs();
		static void self();
		static void outfit_editor(Ped ped_to_edit);
		static void session();
		static void player_db();
		static void settings_tabs();
		static void settings();
		static void vehicle_tabs();
		static void vehicle();
		static void lsc();
		static void spawn_vehicle();
		static void pv();
		static void persist_car();
		static void fun_vehicle();
		static void spawn_ped();
		static void network_tabs();
		static void spoofing();
		static void teleport();
		static void view_player_tabs();
		static void view_player_info();
		static void view_player_ped();
		static void view_player_teleport();
		static void view_player_toxic();
		static void players();
		static void weapons();
		static void context_menu();
		static void menu_bar();
		static void overlay();
		static void pie_menu();
		static void score_controller();
		static void chat();

		static void always()
		{
			esp::draw();
			context_menu();
			notifications();
			spinner();
			chat();
			if (g->window.overlay)
				overlay();
			if (g->pie_menu.active)
				pie_menu();

		}
	};
}
