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
		static void quicksearch();
		static void context_menu_settings();
		static void context_menu();
		static void creator();
		static void esp_settings();
		static void fun_vehicle();
		static void gta_data();
		static void gui_settings();
		static void handling_current_profile();
		static void handling_saved_profiles();
		static void heading();
		static void hotkey_settings();
		static void lsc();
		static void mobile();
		static void navigation();
		static void notifications();
		static void persist_car();
		static void player_database();
		static void players();
		static void protection_settings();
		static void pv();
		static void reaction_settings();
		static void root();
		static void self();
		static void session_browser();
		static void session();
		static void settings();
		static void spawn_ped();
		static void spawn_vehicle();
		static void spoofing();
		static void teleport();
		static void time_and_weather();
		static void train();
		static void vehicle();
		static void view_player();
		static void weapons();

		static void player_info();
		static void player_troll();
		static void player_kick();
		static void player_toxic();
		static void player_misc();
	};
}
