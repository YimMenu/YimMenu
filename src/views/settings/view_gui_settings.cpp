#include "gui.hpp"
#include "renderer.hpp"
#include "views/view.hpp"
#include "core/settings/window.hpp"

namespace big
{
	void view::gui_settings()
	{
		components::sub_title("UI Scale");
		if (ImGui::SliderFloat("##gui-scale", &g_window.gui_scale, 0.75f, 1.5f, "%.2f"))
			g_renderer->rescale(g_window.gui_scale);

		components::sub_title("Colors");
		static ImVec4 col_gui = ImGui::ColorConvertU32ToFloat4(g_window.background_color);
		if (ImGui::ColorEdit4("Gui Color", (float*)&col_gui, ImGuiColorEditFlags_InputRGB | ImGuiColorEditFlags_NoSidePreview))
		{
			g_window.background_color = ImGui::ColorConvertFloat4ToU32(col_gui);
		}

		static ImVec4 col_text = ImGui::ColorConvertU32ToFloat4(g_window.text_color);
		if (ImGui::ColorEdit4("Text Color", (float*)&col_text, ImGuiColorEditFlags_InputRGB | ImGuiColorEditFlags_NoSidePreview))
		{
			g_window.text_color = ImGui::ColorConvertFloat4ToU32(col_text);
		}

		static ImVec4 col_button = ImGui::ColorConvertU32ToFloat4(g_window.button_color);
		if (ImGui::ColorEdit4("Button Color", (float*)&col_button, ImGuiColorEditFlags_InputRGB | ImGuiColorEditFlags_NoSidePreview))
		{
			g_window.button_color = ImGui::ColorConvertFloat4ToU32(col_button);
		}

		static ImVec4 col_frame = ImGui::ColorConvertU32ToFloat4(g_window.frame_color);
		if (ImGui::ColorEdit4("Frame Color", (float*)&col_frame, ImGuiColorEditFlags_InputRGB | ImGuiColorEditFlags_NoSidePreview))
		{
			g_window.frame_color = ImGui::ColorConvertFloat4ToU32(col_frame);
		}

		components::sub_title("In-Game Overlay");
		ImGui::Checkbox("Show Overlay", &g_window.ingame_overlay.opened);
		ImGui::SameLine();
		ImGui::Checkbox("Show When Menu Opened", &g_window.ingame_overlay.show_with_menu_opened);

		ImGui::BeginGroup();

		ImGui::Checkbox("Show FPS", &g_window.ingame_overlay.show_fps);
		ImGui::Checkbox("Show Indicators", &g_window.ingame_overlay.show_indicators);

		ImGui::EndGroup();
		ImGui::SameLine();
		ImGui::BeginGroup();

		ImGui::Checkbox("Show Game Version", &g_window.ingame_overlay.show_game_versions);

		ImGui::EndGroup();

		if (g_window.ingame_overlay.show_indicators)
		{
			if (ImGui::TreeNode("Overlay Indicators"))
			{
				ImGui::BeginGroup();
				ImGui::Checkbox("Show Player Godmode", &g_window.ingame_overlay_indicators.show_player_godmode);
				ImGui::Checkbox("Show Vehicle Godmode", &g_window.ingame_overlay_indicators.show_vehicle_godmode);
				ImGui::Checkbox("Show Ammo Details", &g_window.ingame_overlay_indicators.show_ammo);
				ImGui::EndGroup();

				ImGui::TreePop();
			}
		}
	}

}