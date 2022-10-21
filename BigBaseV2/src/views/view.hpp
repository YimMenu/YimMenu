#pragma once
#include "gui/components/components.hpp"
#include "util/animator.hpp"
#include "esp/view_esp.hpp"
#include "debug/view_debug.hpp"


namespace big
{
	class view
	{
		inline static animator window_animator = animator();
		inline static ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoNav;

	public:
		static void active_view();
		static void esp_settings();
		static void context_menu_settings();
		static void gui_settings();
		static void handling_current_profile();
		static void handling_my_profiles();
		static void handling_saved_profiles();
		static void handling_search();
		static void notification_settings();
		static void protection_settings();
		static void heading();
		static void mobile();
		static void navigation();
		static void notifications();
		static void root();
		static void self();
		static void session();
		static void settings();
		static void vehicle();
		static void lsc();
		static void spawn_vehicle();
		static void pv();
		static void persist_car();
		static void fun_vehicle();
		static void spawn_ped();
		static void spoofing();
		static void teleport();
		static void view_player();
		static void players();
		static void weapons();
		static void context_menu();
		static void gta_data();

		// later calls will be drawn over earlier calls
		static void always()
		{
			esp::draw();
			context_menu();

			gta_data();

			notifications();
		}
	};
}
