#include "gui/components/components.hpp"

namespace big
{
	void components::help_marker(const std::string_view text) 
    {
        ImGui::TextDisabled("(?)");
        if (ImGui::IsItemHovered())
        {
            ImGui::BeginTooltip();
            ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
            ImGui::TextUnformatted(text.data());
            ImGui::PopTextWrapPos();
            ImGui::EndTooltip();
        }
	}
} 
