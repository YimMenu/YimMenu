#include "views/view.hpp"
#include "services/gui_service.hpp"

namespace big
{
	void view::active_view() {
		if (g_gui_service->get_selected().func == nullptr) return;

		static float alpha = 1.f;

		ImGui::SetNextWindowPos({ (g->window.x / 2554.f) * 250.f + 20.f, 100.f }, ImGuiCond_Always);
		ImGui::SetNextWindowSize({ (float)g->window.x * 0.3f, 0.f }, ImGuiCond_Always);
		if (ImGui::Begin("main", nullptr, window_flags))
		{
			ImGui::PushStyleVar(ImGuiStyleVar_Alpha, alpha);
			components::sub_title(g_gui_service->get_selected().name);
			g_gui_service->get_selected().func();
			ImGui::PopStyleVar();
		}
	}
}
