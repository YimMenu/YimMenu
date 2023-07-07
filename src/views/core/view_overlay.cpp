#include "gta/pools.hpp"
#include "gta_util.hpp"
#include "gui.hpp"
#include "pointers.hpp"
#include "views/view.hpp"

namespace big
{
	void view::overlay()
	{
		if (!g.window.ingame_overlay.opened || (g_gui->is_open() && !g.window.ingame_overlay.show_with_menu_opened))
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

			if (g.window.ingame_overlay.show_fps)
				ImGui::Text("%.0f FPS", ImGui::GetIO().Framerate / 2);

			if (CNetworkPlayerMgr* network_player_mgr = gta_util::get_network_player_mgr(); g.window.ingame_overlay.show_players)
				ImGui::Text(std::format("Players: {}/{}", network_player_mgr->m_player_count, network_player_mgr->m_player_limit)
				                .c_str());

			if (g.window.ingame_overlay.show_indicators)
			{
				ImGui::Separator();

				if (g.window.ingame_overlay_indicators.show_player_godmode)
					components::overlay_indicator("Player Godmode", g.self.god_mode);

				if (g.window.ingame_overlay_indicators.show_off_radar)
					components::overlay_indicator("Off Radar", g.self.off_radar);

				if (g.window.ingame_overlay_indicators.show_vehicle_godmode)
					components::overlay_indicator("Vehicle Godmode", g.vehicle.god_mode);

				if (g.window.ingame_overlay_indicators.show_never_wanted)
					components::overlay_indicator("Never Wanted", g.self.never_wanted);

				if (g.window.ingame_overlay_indicators.show_infinite_ammo)
					components::overlay_indicator("Infinite Ammo", g.weapons.infinite_ammo);

				if (g.window.ingame_overlay_indicators.show_always_full_ammo)
					components::overlay_indicator("Always Full Ammo", g.weapons.always_full_ammo);

				if (g.window.ingame_overlay_indicators.show_infinite_mag)
					components::overlay_indicator("Infinite Magazine", g.weapons.infinite_mag);

				if (g.window.ingame_overlay_indicators.show_aimbot)
					components::overlay_indicator("Aimbot", g.weapons.aimbot.enable);

				if (g.window.ingame_overlay_indicators.show_triggerbot)
					components::overlay_indicator("Triggerbot", g.weapons.triggerbot);

				if (g.window.ingame_overlay_indicators.show_invisibility)
					components::overlay_indicator("Invisibility", g.self.invisibility);
			}

			if (g.window.ingame_overlay.show_position && g_local_player)
			{
				ImGui::Separator();

				auto& pos = *g_local_player->get_position();

				ImGui::Text("Pos: %.2f, %.2f, %.2f", pos.x, pos.y, pos.z);
			}

			if (g.window.ingame_overlay.show_replay_interface)
			{
				if (*g_pointers->m_gta.m_ped_pool || (*g_pointers->m_gta.m_vehicle_pool && **g_pointers->m_gta.m_vehicle_pool)
				    || *g_pointers->m_gta.m_prop_pool)
					ImGui::Separator();

				if (*g_pointers->m_gta.m_ped_pool)
					ImGui::Text(std::format("Ped Pool: {}/{}",
					    (*g_pointers->m_gta.m_ped_pool)->get_item_count(),
					    (*g_pointers->m_gta.m_ped_pool)->m_size)
					                .c_str());

				if (*g_pointers->m_gta.m_vehicle_pool && **g_pointers->m_gta.m_vehicle_pool)
					ImGui::Text(std::format("Vehicle Pool: {}/{}",
					    (**g_pointers->m_gta.m_vehicle_pool)->m_item_count,
					    (**g_pointers->m_gta.m_vehicle_pool)->m_size)
					                .c_str());

				if (*g_pointers->m_gta.m_prop_pool)
					ImGui::Text(std::format("Object Pool: {}/{}",
					    (*g_pointers->m_gta.m_prop_pool)->get_item_count(),
					    (*g_pointers->m_gta.m_prop_pool)->m_size)
					                .c_str());
			}

			if (g.window.ingame_overlay.show_game_versions)
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
