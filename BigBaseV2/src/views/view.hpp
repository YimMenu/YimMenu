#pragma once
#include "gui/components/components.hpp"
#include "util/animator.hpp"
#include "views/esp/view_esp.hpp"


namespace big
{
	class view
	{
		inline static animator window_animator = animator();
		inline static ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoNav;

	public:
		static void active_view();
		static void debug();
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
		//static void player_navigation();
		static void notifications();
		static void root();
		static void self();
		static void session();
		static void settings();
		static void spawn();
		static void spoofing();
		static void teleport();
		static void vehicle();
		static void lsc();
		static void view_player();
		static void players();
		static void weapons();
		static void context_menu();

		static void always()
		{
			esp::draw();
			context_menu();
			notifications();
		}
	};
}