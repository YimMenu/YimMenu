#include "services/context_menu/context_menu_service.hpp"
#include "views/view.hpp"

namespace big
{
	void view::context_menu_settings()
	{
		ImGui::Checkbox("SETTINGS_CONTEXT_MENU"_T.data(), &g.context_menu.enabled);

		if (g.context_menu.enabled)
		{
			ImGui::Text("SETTINGS_CONTEXT_MENU_ENTITY_TYPES"_T.data());
			ImGui::CheckboxFlags("SETTINGS_CONTEXT_MENU_ENTITY_TYPE_OBJECT"_T.data(),
			    reinterpret_cast<int*>(&g.context_menu.allowed_entity_types),
			    static_cast<int>(ContextEntityType::OBJECT));
			ImGui::SameLine();
			ImGui::CheckboxFlags("SETTINGS_CONTEXT_MENU_ENTITY_TYPE_PED"_T.data(),
			    reinterpret_cast<int*>(&g.context_menu.allowed_entity_types),
			    static_cast<int>(ContextEntityType::PED));
			ImGui::SameLine();
			ImGui::CheckboxFlags("SETTINGS_CONTEXT_MENU_ENTITY_TYPE_PLAYER"_T.data(),
			    reinterpret_cast<int*>(&g.context_menu.allowed_entity_types),
			    static_cast<int>(ContextEntityType::PLAYER));
			ImGui::SameLine();
			ImGui::CheckboxFlags("SETTINGS_CONTEXT_MENU_ENTITY_TYPE_VEHICLE"_T.data(),
			    reinterpret_cast<int*>(&g.context_menu.allowed_entity_types),
			    static_cast<int>(ContextEntityType::VEHICLE));

			static ImVec4 selected_option_color = ImGui::ColorConvertU32ToFloat4(g.context_menu.selected_option_color);
			ImGui::Text("SETTINGS_CONTEXT_MENU_COLOR"_T.data());
			if (ImGui::ColorEdit4("###BSelected Option Color##cm_picker", (float*)&selected_option_color, ImGuiColorEditFlags_InputRGB | ImGuiColorEditFlags_NoSidePreview))
			{
				g.context_menu.selected_option_color = ImGui::ColorConvertFloat4ToU32(selected_option_color);
			}

			ImGui::Checkbox("SETTINGS_CONTEXT_MENU_BOUNDING_BOX"_T.data(), &g.context_menu.bounding_box_enabled);

			if (g.context_menu.bounding_box_enabled)
			{
				static ImVec4 bounding_box_color = ImGui::ColorConvertU32ToFloat4(g.context_menu.bounding_box_color);
				ImGui::Text("SETTINGS_CONTEXT_MENU_BOUNDING_BOX_COLOR"_T.data());
				if (ImGui::ColorEdit4("###Bounding Box Color##cm_picker", (float*)&bounding_box_color, ImGuiColorEditFlags_InputRGB | ImGuiColorEditFlags_NoSidePreview))
				{
					g.context_menu.bounding_box_color = ImGui::ColorConvertFloat4ToU32(bounding_box_color);
				}
			}
		}
	}
}
