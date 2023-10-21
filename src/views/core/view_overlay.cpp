#include "core/settings/self.hpp"
#include "core/settings/vehicle.hpp"
#include "core/data/weapons.hpp"
#include "core/settings/window.hpp"
#include "gta/pools.hpp"
#include "gta_util.hpp"
#include "gui.hpp"
#include "pointers.hpp"
#include "views/view.hpp"

namespace big
{
	void view::overlay()
	{
		if (!g_window.ingame_overlay.opened || (g_gui->is_open() && !g_window.ingame_overlay.show_with_menu_opened))
			return;

		g_gui->push_theme_colors();

		ImGui::SetNextWindowPos(ImVec2(10.0f, 10.0f), ImGuiCond_FirstUseEver, ImVec2(0.0f, 0.0f));
		ImGui::SetNextWindowBgAlpha(0.5f);

		auto window_flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav;
		if (!g_gui->is_open())
		{
			window_flags |= ImGuiWindowFlags_NoMouseInputs;
		}
		if (ImGui::Begin("overlay", nullptr, window_flags))
		{
			ImGui::Text("YimMenu");

			ImGui::Separator();

			if (g_window.ingame_overlay.show_fps)
				ImGui::Text("%.0f FPS", ImGui::GetIO().Framerate);

			if (g_window.ingame_overlay.show_indicators)
			{
				ImGui::Separator();

				if (g_window.ingame_overlay_indicators.show_player_godmode)
					components::overlay_indicator("Player Godmode", g_self.god_mode);

				if (g_window.ingame_overlay_indicators.show_vehicle_godmode)
					components::overlay_indicator("Vehicle Godmode", g_vehicle.god_mode);

				if (g_window.ingame_overlay_indicators.show_ammo)
				{
					components::overlay_indicator("Infinite Ammo", g_weapons.infinite_ammo);
					components::overlay_indicator("Infinite Magazine", g_weapons.infinite_mag);
				}
			}

			if (g_window.ingame_overlay.show_game_versions)
			{
				ImGui::Separator();
				ImGui::Text(std::format("Game Version: {}", g_pointers->m_gta.m_game_version).c_str());
				ImGui::Text(std::format("Online Version: {}", g_pointers->m_gta.m_online_version).c_str());
			}
		}
		ImGui::End();

		g_gui->pop_theme_colors();
	}
}
