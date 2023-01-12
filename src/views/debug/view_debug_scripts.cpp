#include "view_debug.hpp"
#include "gui/components/components.hpp"
#include "script_mgr.hpp"

namespace big
{
	void debug::scripts()
	{
		if (ImGui::BeginTabItem("DEBUG_TAB_SCRIPTS"_T.data()))
		{
            ImGui::BeginGroup();
            components::sub_title("SETTINGS_SCRIPTS"_T);
            ImGui::SameLine(ImGui::GetWindowWidth() - 100);
            if (ImGui::Button("CLOSE"_T.data())) ImGui::CloseCurrentPopup();
            ImGui::Spacing();
            components::sub_title("SETTINGS_SCRIPTS_SUB_TITLE"_T);

            for (const auto& script : g_script_mgr.scripts())
            {
                if (script->is_toggleable())
                {
                    if (ImGui::Checkbox(script->name(), script->toggle_ptr()))
                    {
                        g_notification_service->push(std::string(script->name()).append(" script"), script->is_enabled() ? "Resumed" : "Halted");
                    }
                }
            }
			ImGui::EndTabItem();
		}
	}
}