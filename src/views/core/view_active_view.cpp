#include "views/view.hpp"

#include "core/settings/window.hpp"
#include "pointers.hpp"
#include "services/gui/gui_service.hpp"

namespace big
{
	void view::active_view()
	{
		const auto selected = g_gui_service->get_selected();

		if (selected->func == nullptr)
			return;

		constexpr float alpha = 1.f;

		ImGui::SetNextWindowPos({(300.f + 115.f) * g_window.gui_scale, 100.f * g_window.gui_scale}, ImGuiCond_Always);
		ImGui::SetNextWindowSize({0.f, 0.f});
		ImGui::SetNextWindowSizeConstraints({300.f, 100.f},
		    {(float)*g_pointers->m_gta.m_resolution_x - 270.f, (float)*g_pointers->m_gta.m_resolution_y - 110.f});


		if (ImGui::Begin("main", nullptr, window_flags))
		{
			ImGui::PushStyleVar(ImGuiStyleVar_Alpha, alpha);
			components::title(selected->name);
			ImGui::Separator();
			selected->func();
			ImGui::PopStyleVar();
		}
		ImGui::End();
	}
}
