#include "gui/components/components.hpp"
#include "pointers.hpp"

namespace big
{
	bool components::nav_button(const std::string_view text)
	{
		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.f, 0.f, 0.f, 0.f));
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.f, 0.f, 0.f, 0.f));
		ImGui::PushStyleVar(ImGuiStyleVar_ButtonTextAlign, { 0.f, 0.5f });
		ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, { 0, 5 });
		bool result = ImGui::Button(text.data(), {((float)*g_pointers->m_resolution_x * 0.15f) - 30, 0});
		ImGui::PopStyleVar(2);
		ImGui::PopStyleColor(2);

		return result;
	}
}