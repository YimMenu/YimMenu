#include "views/view.hpp"

namespace big
{
	void view::esp_settings()
	{
		ImGui::Checkbox("ESP Enabled", &g.esp.enabled);

		if (g.esp.enabled)
		{
			ImGui::Checkbox("Hide Self", &g.esp.hide_self);

			ImGui::Text("Global Render Distance (min, max)");
			ImGui::SliderFloat2("###Global Render Distance", g.esp.global_render_distance, 0.f, 1500.f);

			ImGui::Checkbox("Tracer", &g.esp.tracer);
			if (g.esp.tracer) {
				ImGui::Text("Tracer Draw Position (x, y)");
				ImGui::SliderFloat2("###Draw Position", g.esp.tracer_draw_position, 0.f, 1.f);
				ImGui::Text("Tracer Render Distance (min, max)");
				ImGui::SliderFloat2("###Tracer Render Distance", g.esp.tracer_render_distance, g.esp.global_render_distance[0], g.esp.global_render_distance[1]);
			}

			ImGui::Checkbox("Box ESP", &g.esp.box);
			if (g.esp.box) {
				ImGui::Text("Box Render Distance (min, max)");
				ImGui::SliderFloat2("###Box Render Distance", g.esp.box_render_distance, g.esp.global_render_distance[0], g.esp.global_render_distance[1]);
			}

			ImGui::Checkbox("Show Player Name", &g.esp.name);
			ImGui::Checkbox("Show Player Distance", &g.esp.distance);
			ImGui::Checkbox("Show Player Godmode", &g.esp.god);
			ImGui::Checkbox("Show Player Health", &g.esp.health);
			ImGui::Checkbox("Show Player Armor", &g.esp.armor);

			ImGui::Checkbox("Should ESP Color Change with Distance", &g.esp.change_esp_color_from_dist);
			if (g.esp.health)
				ImGui::Checkbox("Should Healthbar Scale with Distance", &g.esp.scale_health_from_dist);

			if (g.esp.armor)
				ImGui::Checkbox("Should Armorbar Scale with Distance", &g.esp.scale_armor_from_dist);

			static ImVec4 col_enemy = ImGui::ColorConvertU32ToFloat4(g.esp.enemy_color);
			static ImVec4 col_enemy_near = ImGui::ColorConvertU32ToFloat4(g.esp.enemy_near_color);
			static ImVec4 col_default = ImGui::ColorConvertU32ToFloat4(g.esp.default_color);
			static ImVec4 col_friend = ImGui::ColorConvertU32ToFloat4(g.esp.friend_color);

			ImGui::Text("Distance threshold (min, max)");
			ImGui::SliderFloat2("###Distance threshold", g.esp.distance_threshold, g.esp.global_render_distance[0], g.esp.global_render_distance[1]);

			if (ImGui::TreeNode("ESP Colors (RGBA)"))
			{
				if (g.esp.change_esp_color_from_dist) {
					ImGui::Text("Enemy Close Color:");
					if (ImGui::ColorEdit4("###Enemy ESP Color##esp_picker", (float*)&col_enemy, ImGuiColorEditFlags_InputRGB | ImGuiColorEditFlags_NoSidePreview))
					{
						g.esp.enemy_color = ImGui::ColorConvertFloat4ToU32(col_enemy);
					}

					ImGui::Text("Enemy Near Color:");
					if (ImGui::ColorEdit4("###Enemy Near ESP Color##esp_picker", (float*)&col_enemy_near, ImGuiColorEditFlags_InputRGB | ImGuiColorEditFlags_NoSidePreview))
					{
						g.esp.enemy_near_color = ImGui::ColorConvertFloat4ToU32(col_enemy_near);
					}
				}

				ImGui::Text("Default Color:");
				if (ImGui::ColorEdit4("###Default ESP Color##esp_picker", (float*)&col_default, ImGuiColorEditFlags_InputRGB | ImGuiColorEditFlags_NoSidePreview))
				{
					g.esp.default_color = ImGui::ColorConvertFloat4ToU32(col_default);
				}

				ImGui::Text("Friendly Color:");
				if (ImGui::ColorEdit4("###Friend ESP Color##friend_picker", (float*)&col_friend, ImGuiColorEditFlags_InputRGB | ImGuiColorEditFlags_NoSidePreview))
				{
					g.esp.friend_color = ImGui::ColorConvertFloat4ToU32(col_friend);
				}
			}
		}
	}
}
