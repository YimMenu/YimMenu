#include "views/view.hpp"
#include "services/gui_service.hpp"

namespace big
{
	void view::active_view() {
		if (g_gui_service->get_selected()->func == nullptr) return;

		static float alpha = 1.f;

		ImGui::SetNextWindowPos({ 250.f + 20.f, 100.f }, ImGuiCond_Always);
		ImGui::SetNextWindowSize({ 0.f, 0.f });
		ImGui::SetNextWindowSizeConstraints({ 250.f, 100.f }, { (float)*g_pointers->m_resolution_x - 270.f, (float)*g_pointers->m_resolution_y - 110.f });
		if (ImGui::Begin("main", nullptr, window_flags))
		{
			ImGui::PushStyleVar(ImGuiStyleVar_Alpha, alpha);
			components::sub_title(g_gui_service->get_selected()->name);
			g_gui_service->get_selected()->func();
			ImGui::PopStyleVar();
		}
	}
}
