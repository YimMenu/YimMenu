#include "views/view.hpp"

namespace big
{
	void view::active_view() {
		static float tabs_open_animation = -(float)g->window.x * 0.15f;
		static float alpha = 0.f;
		if (g->window.switched_view) {
			g->window.switched_view = false;
			window_animator.reset();
		}
		window_animator.animate(600, [](const float& progress)
		{
			alpha = progress;
			switch (current_tab->tab)
			{
			case tabs::NONE:
				if (tabs_open_animation >= (float)g->window.x * 0.15f)
					tabs_open_animation = (float)g->window.x * 0.15f;
				else
					tabs_open_animation = (((float)g->window.x * 0.30f) * progress - (float)g->window.x * 0.15f);
				break;
			default:
				if (tabs_open_animation <= -(float)g->window.x * 0.15f)
					tabs_open_animation = -(float)g->window.x * 0.15f;
				else
					tabs_open_animation = (float)g->window.x * 0.15f - (((float)g->window.x * 0.30f) * progress);
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