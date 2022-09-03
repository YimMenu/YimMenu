#include "pointers.hpp"
#include "views/view.hpp"
#include "widgets/imgui_spinner.hpp"
#include "services/spinner/spinner_service.hpp"

namespace big
{
	void view::spinner()
	{
		if (g_spinner_service->spinner.active)
		{
			ImGui::SetNextWindowSize({ 380, 90 });
			ImGui::SetNextWindowPos( { (float)*g_pointers->m_resolution_x - 400.f, (float)*g_pointers->m_resolution_y - 100.f } );

			if (ImGui::Begin("spinner", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoNav | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoMouseInputs | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoBringToFrontOnFocus))
			{
				ImGui::Spinner("##spinner_", 10.f, 4.f, g_spinner_service->spinner_colors[g_spinner_service->spinner.type]);
				ImGui::SameLine();
				ImGui::Text(g_spinner_service->spinner.text.c_str());
				if (g_spinner_service->spinner.progress_bar && g_spinner_service->spinner.progress <= 1.f)
				{
					ImGui::BufferingBar("##progress", g_spinner_service->spinner.progress, ImVec2(380, 7), ImColor(87, 87, 87, 255), g_spinner_service->spinner_colors[g_spinner_service->spinner.type]);
				}
				ImGui::End();
			}
		}
	}
}