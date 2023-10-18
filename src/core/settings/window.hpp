#pragma once
#include <imgui.h>

namespace big
{
	inline struct g_window_t
	{
		ImU32 background_color = 4278190080;
		ImU32 text_color       = 4292072403;
		ImU32 button_color     = 2936035029;
		ImU32 frame_color      = 2939170865;
		float gui_scale        = 0.75;

		ImFont* font_title     = nullptr;
		ImFont* font_sub_title = nullptr;
		ImFont* font_small     = nullptr;
		ImFont* font_icon      = nullptr;

		bool demo          = false;

		struct ingame_overlay
		{
			bool opened                = true;
			bool show_with_menu_opened = false;

			bool show_fps           = true;
			bool show_indicators    = true;
			bool show_game_versions = true;

			NLOHMANN_DEFINE_TYPE_INTRUSIVE(ingame_overlay, opened, show_with_menu_opened, show_fps, show_indicators, show_game_versions)
		} ingame_overlay{};

		struct ingame_overlay_indicators
		{
			bool show_player_godmode  = true;
			bool show_vehicle_godmode = true;
			bool show_ammo            = true;

			NLOHMANN_DEFINE_TYPE_INTRUSIVE(ingame_overlay_indicators, show_player_godmode, show_vehicle_godmode, show_ammo)
		} ingame_overlay_indicators{};

		NLOHMANN_DEFINE_TYPE_INTRUSIVE(g_window_t, background_color, text_color, button_color, frame_color, gui_scale, ingame_overlay, ingame_overlay_indicators)
	} g_window{};
}