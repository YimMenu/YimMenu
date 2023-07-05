#include "gui.hpp"
#include "renderer.hpp"
#include "views/view.hpp"

namespace big
{
	void view::gui_settings()
	{
		components::sub_title("SETTINGS_UI_SCALE"_T);
		if (ImGui::SliderFloat("##gui-scale", &g.window.gui_scale, 0.75f, 1.5f, "%.2f"))
			g_renderer->rescale(g.window.gui_scale);

		components::sub_title("SETTINGS_UI_COLOR"_T);
		static ImVec4 col_gui = ImGui::ColorConvertU32ToFloat4(g.window.background_color);
		if (ImGui::ColorEdit4("SETTINGS_UI_COLOR_PICKER"_T.data(), (float*)&col_gui, ImGuiColorEditFlags_InputRGB | ImGuiColorEditFlags_NoSidePreview))
		{
			g.window.background_color = ImGui::ColorConvertFloat4ToU32(col_gui);
		}

		static ImVec4 col_text = ImGui::ColorConvertU32ToFloat4(g.window.text_color);
		if (ImGui::ColorEdit4("Text Color", (float*)&col_text, ImGuiColorEditFlags_InputRGB | ImGuiColorEditFlags_NoSidePreview))
		{
			g.window.text_color = ImGui::ColorConvertFloat4ToU32(col_text);
		}

		static ImVec4 col_button = ImGui::ColorConvertU32ToFloat4(g.window.button_color);
		if (ImGui::ColorEdit4("Button Color", (float*)&col_button, ImGuiColorEditFlags_InputRGB | ImGuiColorEditFlags_NoSidePreview))
		{
			g.window.button_color = ImGui::ColorConvertFloat4ToU32(col_button);
		}

		static ImVec4 col_frame = ImGui::ColorConvertU32ToFloat4(g.window.frame_color);
		if (ImGui::ColorEdit4("Frame Color", (float*)&col_frame, ImGuiColorEditFlags_InputRGB | ImGuiColorEditFlags_NoSidePreview))
		{
			g.window.frame_color = ImGui::ColorConvertFloat4ToU32(col_frame);
		}

		components::sub_title("In-Game Overlay");
		ImGui::Checkbox("Show Overlay", &g.window.ingame_overlay.opened);
		ImGui::SameLine();
		ImGui::Checkbox("Show When Menu Opened", &g.window.ingame_overlay.show_with_menu_opened);

		ImGui::BeginGroup();

		ImGui::Checkbox("Show FPS", &g.window.ingame_overlay.show_fps);
		ImGui::Checkbox("Show Players", &g.window.ingame_overlay.show_players);
		ImGui::Checkbox("Show Time", &g.window.ingame_overlay.show_time);
		if (ImGui::IsItemHovered())
			ImGui::SetTooltip("Show time is currently disabled as it caused problems for some users.");
		ImGui::Checkbox("Show Indicators", &g.window.ingame_overlay.show_indicators);

		ImGui::EndGroup();
		ImGui::SameLine();
		ImGui::BeginGroup();

		ImGui::Checkbox("Show Replay Interface", &g.window.ingame_overlay.show_replay_interface);
		ImGui::Checkbox("Show Position", &g.window.ingame_overlay.show_position);
		ImGui::Checkbox("Show Game Version", &g.window.ingame_overlay.show_game_versions);

		ImGui::EndGroup();

		if (g.window.ingame_overlay.show_indicators)
		{
			if (ImGui::TreeNode("Overlay Indicators"))
			{
				ImGui::BeginGroup();
				ImGui::Checkbox("Show Player Godmode", &g.window.ingame_overlay_indicators.show_player_godmode);
				ImGui::Checkbox("Show Off Radar", &g.window.ingame_overlay_indicators.show_off_radar);
				ImGui::Checkbox("Show Vehicle Godmode", &g.window.ingame_overlay_indicators.show_vehicle_godmode);
				ImGui::Checkbox("Show Never Wanted", &g.window.ingame_overlay_indicators.show_never_wanted);
				ImGui::EndGroup();

				ImGui::SameLine();

				ImGui::BeginGroup();
				ImGui::Checkbox("Show Infinite Ammo", &g.window.ingame_overlay_indicators.show_infinite_ammo);
				ImGui::Checkbox("Show Always Full Ammo", &g.window.ingame_overlay_indicators.show_always_full_ammo);
				ImGui::Checkbox("Show Infinite Magazine", &g.window.ingame_overlay_indicators.show_infinite_mag);
				ImGui::Checkbox("Show Aimbot", &g.window.ingame_overlay_indicators.show_aimbot);
				ImGui::Checkbox("Show Triggerbot", &g.window.ingame_overlay_indicators.show_triggerbot);
				ImGui::Checkbox("Show Invisibility", &g.window.ingame_overlay_indicators.show_invisibility);
				ImGui::EndGroup();

				ImGui::TreePop();
			}
		}
	}

}