#include "gui/components/components.hpp"

namespace big
{
	/*
	Will provide an options button next to the previous element that opens up a popup to run the content of 'render_elements'
	*/
	void components::options_modal(const std::string_view element_name, std::function<void()> render_elements, bool sameline, std::string custom_button_name)
	{
		if (sameline)
			ImGui::SameLine();

		ImGui::PushID(element_name.data());
		if (ImGui::Button(custom_button_name.c_str()))
			ImGui::OpenPopup(element_name.data());

		ImGui::SetNextWindowPos(ImVec2(ImGui::GetIO().DisplaySize.x * 0.5f, ImGui::GetIO().DisplaySize.y * 0.5f), ImGuiCond_Always, ImVec2(0.5f, 0.5f));
		if (ImGui::BeginPopupModal(element_name.data(), nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_Modal | ImGuiWindowFlags_AlwaysAutoResize))
		{
			render_elements();
			ImGui::Spacing();
			if (components::button("CLOSE"_T) || ((!ImGui::IsWindowHovered() && !ImGui::IsAnyItemHovered()) && ImGui::IsMouseClicked(ImGuiMouseButton_Left)))
				ImGui::CloseCurrentPopup();

			ImGui::EndPopup();
		}
		ImGui::PopID();
	}
}