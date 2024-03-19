#include "views/view.hpp"

namespace big
{
	void view::esp_settings()
	{
		ImGui::Checkbox("SETTINGS_ESP"_T.data(), &g.esp.enabled);

		if (g.esp.enabled)
		{
			ImGui::Text("SETTINGS_ESP_GLOBAL_RENDER_DISTANCE"_T.data());
			ImGui::SliderFloat2("###Global Render Distance", g.esp.global_render_distance, 0.f, 1500.f);

			ImGui::Checkbox("SETTINGS_ESP_TRACER"_T.data(), &g.esp.tracer);
			if (g.esp.tracer)
			{
				ImGui::Text("SETTINGS_ESP_TRACER_POSITION"_T.data());
				ImGui::SliderFloat2("###Draw Position", g.esp.tracer_draw_position, 0.f, 1.f);
				ImGui::Text("SETTINGS_ESP_TRACER_RENDER_DISTANCE"_T.data());
				ImGui::SliderFloat2("###Tracer Render Distance",
				    g.esp.tracer_render_distance,
				    g.esp.global_render_distance[0],
				    g.esp.global_render_distance[1]);
			}

			ImGui::Checkbox("SETTINGS_ESP_BOX"_T.data(), &g.esp.box);
			if (g.esp.box)
			{
				ImGui::Text("SETTINGS_ESP_BOX_RENDER_DISTANCE"_T.data());
				ImGui::SliderFloat2("###Box Render Distance",
				    g.esp.box_render_distance,
				    g.esp.global_render_distance[0],
				    g.esp.global_render_distance[1]);
			}

			ImGui::Checkbox("SETTINGS_ESP_PLAYER_NAME"_T.data(), &g.esp.name);
			ImGui::Checkbox("SETTINGS_ESP_PLAYER_DISTANCE"_T.data(), &g.esp.distance);
			ImGui::Checkbox("SETTINGS_ESP_PLAYER_GOD_MODE"_T.data(), &g.esp.god);
			ImGui::Checkbox("SETTINGS_ESP_PLAYER_HEALTH"_T.data(), &g.esp.health);
			ImGui::Checkbox("SETTINGS_ESP_PLAYER_ARMOR"_T.data(), &g.esp.armor);

			ImGui::Checkbox("SETTINGS_ESP_COLOR_W_DISTANCE"_T.data(), &g.esp.change_esp_color_from_dist);
			if (g.esp.health)
				ImGui::Checkbox("SETTINGS_ESP_SCALE_HEALTH"_T.data(), &g.esp.scale_health_from_dist);

			if (g.esp.armor)
				ImGui::Checkbox("SETTINGS_ESP_SCALE_ARMOR"_T.data(), &g.esp.scale_armor_from_dist);

			static ImVec4 col_enemy      = ImGui::ColorConvertU32ToFloat4(g.esp.enemy_color);
			static ImVec4 col_enemy_near = ImGui::ColorConvertU32ToFloat4(g.esp.enemy_near_color);
			static ImVec4 col_default    = ImGui::ColorConvertU32ToFloat4(g.esp.default_color);
			static ImVec4 col_friend     = ImGui::ColorConvertU32ToFloat4(g.esp.friend_color);

			ImGui::Text("SETTINGS_ESP_DISTANCE_THRESHOLD"_T.data());
			ImGui::SliderFloat2("###Distance threshold",
			    g.esp.distance_threshold,
			    g.esp.global_render_distance[0],
			    g.esp.global_render_distance[1]);

			if (ImGui::TreeNode("SETTINGS_ESP_COLORS"_T.data()))
			{
				if (g.esp.change_esp_color_from_dist)
				{
					ImGui::Text("SETTINGS_ESP_ENEMY_CLOSE_COLOR"_T.data());
					if (ImGui::ColorEdit4("###Enemy ESP Color##esp_picker", (float*)&col_enemy, ImGuiColorEditFlags_InputRGB | ImGuiColorEditFlags_NoSidePreview))
					{
						g.esp.enemy_color = ImGui::ColorConvertFloat4ToU32(col_enemy);
					}

					ImGui::Text("SETTINGS_ESP_ENEMY_NEAR_COLOR"_T.data());
					if (ImGui::ColorEdit4("###Enemy Near ESP Color##esp_picker", (float*)&col_enemy_near, ImGuiColorEditFlags_InputRGB | ImGuiColorEditFlags_NoSidePreview))
					{
						g.esp.enemy_near_color = ImGui::ColorConvertFloat4ToU32(col_enemy_near);
					}
				}

				ImGui::Text("SETTINGS_ESP_ENEMY_DEFAULT_COLOR"_T.data());
				if (ImGui::ColorEdit4("###Default ESP Color##esp_picker", (float*)&col_default, ImGuiColorEditFlags_InputRGB | ImGuiColorEditFlags_NoSidePreview))
				{
					g.esp.default_color = ImGui::ColorConvertFloat4ToU32(col_default);
				}

				ImGui::Text("SETTINGS_ESP_FRIENDLY_COLOR"_T.data());
				if (ImGui::ColorEdit4("###Friend ESP Color##friend_picker", (float*)&col_friend, ImGuiColorEditFlags_InputRGB | ImGuiColorEditFlags_NoSidePreview))
				{
					g.esp.friend_color = ImGui::ColorConvertFloat4ToU32(col_friend);
				}
			}
		}
	}
}
