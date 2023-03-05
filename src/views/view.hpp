#pragma once
#include "debug/view_debug.hpp"
#include "esp/view_esp.hpp"
#include "gui/components/components.hpp"
#include "util/animator.hpp"


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
		static void stat_editor();
		static void gui_settings();
		static void hotkey_settings();
		static void handling_current_profile();
		static void handling_saved_profiles();
		static void reaction_settings();
		static void protection_settings();
		static void translation_settings();
		static void heading();
		static void mobile();
		static void navigation();
		static void notifications();
		static void overlay();
		static void root();
		static void self();
		static void session();
		static void missions();
		static void player_database();
		static void session_browser();
		static void settings();
		static void vehicle();
		static void lsc();
		static void spawn_vehicle();
		static void pv();
		static void persist_car();
		static void fun_vehicle();
		static void spawn_ped();
		static void time_and_weather();
		static void spoofing();
		static void teleport();
		static void view_player();
		static void players();
		static void weapons();
		static void context_menu();
		static void gta_data();
		static void creator();
		static void train();
		static void water();
		static void blackhole();
		static void model_swapper();
		static void nearby();

		static void player_info();
		static void player_troll();
		static void player_kick();
		static void player_toxic();
		static void player_misc();
		static void cmd_executor();
		static void player_vehicle();
	};
}
