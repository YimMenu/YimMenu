#include "fiber_pool.hpp"
#include "util/session.hpp"
#include "views/view.hpp"

namespace big
{
	void view::session() {

		if (ImGui::TreeNode("Session Switcher"))
		{
			for (const SessionType& session_type : sessions)
			{
				components::button(session_type.name, [session_type] {
					session::join_type(session_type);
					});
			}

			ImGui::TreePop();

		}

		if (ImGui::TreeNode("ESP Settings"))
		{
			ImGui::Checkbox("ESP Enabled", &g->esp.enabled);

			if (g->esp.enabled)
			{
				ImGui::SliderFloat2("Global Render Distance", g->esp.global_render_distance, 0.f, 1500.f);

				ImGui::Checkbox("Tracer", &g->esp.tracer);
				if (g->esp.tracer)
					ImGui::SliderFloat2("Tracer Render Distance", g->esp.tracer_render_distance, g->esp.global_render_distance[0], g->esp.global_render_distance[1]);

				ImGui::Checkbox("Box ESP", &g->esp.box);
				if (g->esp.box)
					ImGui::SliderFloat2("Box Render Distance", g->esp.box_render_distance, g->esp.global_render_distance[0], g->esp.global_render_distance[1]);

				ImGui::Checkbox("Show Player Distance", &g->esp.distance);
				ImGui::Checkbox("Show Player Godmode", &g->esp.god);
				ImGui::Checkbox("Show Player Health", &g->esp.health);
				ImGui::Checkbox("Show Player Name", &g->esp.name);

				static ImVec4 col_esp = ImGui::ColorConvertU32ToFloat4(g->esp.color);
				static ImVec4 col_friend = ImGui::ColorConvertU32ToFloat4(g->esp.friend_color);
				if (ImGui::ColorEdit4("ESP Color##esp_picker", (float*)&col_esp, ImGuiColorEditFlags_InputRGB | ImGuiColorEditFlags_NoSidePreview))
				{
					g->esp.color = ImGui::ColorConvertFloat4ToU32(col_esp);
				}
				if (ImGui::ColorEdit4("Friend ESP Color##friend_picker", (float*)&col_friend, ImGuiColorEditFlags_InputRGB | ImGuiColorEditFlags_NoSidePreview))
				{
					g->esp.friend_color = ImGui::ColorConvertFloat4ToU32(col_friend);
				}
			}
			ImGui::TreePop();
		}

		if (ImGui::TreeNode("Local Time"))
		{
			ImGui::Checkbox("Override Time", &g->session.override_time);

			if (g->session.override_time)
			{
				ImGui::SliderInt("Hour", &g->session.custom_time.hour, 0, 23);
				ImGui::SliderInt("Minute", &g->session.custom_time.minute, 0, 59);
				ImGui::SliderInt("Second", &g->session.custom_time.second, 0, 59);
			}

			ImGui::TreePop();
		}
		if (ImGui::TreeNode("Local Weather"))
		{
			if (ImGui::Button("Clear Override"))
			{
				g_fiber_pool->queue_job([]
				{
					MISC::CLEAR_OVERRIDE_WEATHER();
				});
			}

			if (ImGui::ListBox("", &g->session.local_weather, session::weathers, 15))
			{
				g_fiber_pool->queue_job([]
				{
					session::local_weather();
				});
			}

			ImGui::TreePop();
		}
	}
}