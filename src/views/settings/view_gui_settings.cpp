#include "renderer.hpp"
#include "views/view.hpp"

namespace big
{
	void view::gui_settings()
	{
		components::sub_title("SETTINGS_UI_SCALE"_T);
		if (ImGui::SliderFloat("##gui-scale", &g.window.gui_scale, 1.f, 1.5f, "%.2f"))
			g_renderer->rescale(g.window.gui_scale);

		components::sub_title("SETTINGS_UI_COLOR"_T);
		static ImVec4 col_gui = ImGui::ColorConvertU32ToFloat4(g.window.color);
		if (ImGui::ColorEdit4("SETTINGS_UI_COLOR_PICKER"_T.data(), (float*)&col_gui, ImGuiColorEditFlags_InputRGB | ImGuiColorEditFlags_NoSidePreview))
		{
			g.window.color = ImGui::ColorConvertFloat4ToU32(col_gui);
		}

		components::sub_title("Ingame Overlay");
		ImGui::Checkbox("Show Overlay", &g.window.ingame_overlay.opened);
		ImGui::SameLine();
		ImGui::Checkbox("Show when Menu opened", &g.window.ingame_overlay.show_with_menu_opened);

		ImGui::BeginGroup();

		ImGui::Checkbox("Show FPS", &g.window.ingame_overlay.show_fps);
		ImGui::Checkbox("Show Players", &g.window.ingame_overlay.show_players);
		ImGui::Checkbox("Show Time", &g.window.ingame_overlay.show_time);
		if (ImGui::IsItemHovered())
			ImGui::SetTooltip("Show time is currently disabled as it caused problems for some users.");

		ImGui::EndGroup();
		ImGui::SameLine();
		ImGui::BeginGroup();

		ImGui::Checkbox("Show Replay Interface", &g.window.ingame_overlay.show_replay_interface);
		ImGui::Checkbox("Show Game Version", &g.window.ingame_overlay.show_game_versions);

		ImGui::EndGroup();
	}

}