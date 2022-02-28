#include "views/view.hpp"

namespace big
{
	void view::active_view() {
		static float tabs_open_animation = -(float)g->window.x * 0.15f;
		static float alpha = 0.f;

		const float max_position = (float)g->window.x * 0.15f;

		if (g->window.switched_view) {
			g->window.switched_view = false;
			window_animator.reset();
		}
		window_animator.animate(600, [max_position](const float& progress)
		{
			alpha = progress;
			switch (current_tab->tab)
			{
			case tabs::NONE:
				tabs_open_animation = tabs_open_animation <= -max_position ? -max_position : max_position - (((float)g->window.x * 0.30f) * progress);
				break;
			default:
				tabs_open_animation = tabs_open_animation >= max_position ? max_position : (((float)g->window.x * 0.30f) * progress) - max_position;
				break;
			}
		});


		ImGui::SetNextWindowPos({ tabs_open_animation, 0.f }, ImGuiCond_Always);
		ImGui::SetNextWindowSize({ (float)g->window.x * 0.3f, (float)g->window.y }, ImGuiCond_Always);
		ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.10f, 0.09f, 0.12f, 1.00f));
		if (ImGui::Begin("main", 0, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoNav))
		{
			ImGui::PushStyleVar(ImGuiStyleVar_Alpha, alpha);
			if (current_tab->tab != tabs::NONE)
			{
				ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4(0.06f, 0.05f, 0.07f, 1.00f));
				components::sub_title(current_tab->name);
				current_tab->func();
				ImGui::PopStyleColor();
			}
			ImGui::PopStyleVar();
			ImGui::End();
		}
		ImGui::PopStyleColor();
	}
}