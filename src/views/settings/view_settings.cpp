#include "views/view.hpp"
#include "script_mgr.hpp"

namespace big
{
	void scripts_popupmodal()
	{
		ImGui::BeginGroup();
		components::sub_title("Scripts");
		ImGui::SameLine(ImGui::GetWindowWidth() - 100);
		if (ImGui::Button("Close")) ImGui::CloseCurrentPopup();
		ImGui::Spacing();
		components::sub_title("These scripts are responsible for all looped features.\nOnly disable if you know what you are doing.");

		for (const auto& script : g_script_mgr.scripts())
		{
			if (script->is_toggleable())
				if (ImGui::Checkbox(script->name(), script->toggle_ptr()))
					g_notification_service->push(std::string(script->name()).append(" script"), script->is_enabled() ? "Resumed" : "Halted");
		}

		ImGui::EndGroup();
	}

	void view::settings()
	{
		components::sub_title("Misc");
		ImGui::Checkbox("Enable Dev DLC", &g.settings.dev_dlc);

		ImGui::Separator();

		if (ImGui::Button("Manage scripts"))
			ImGui::OpenPopup("Scripts");
		
		ImGui::SetNextWindowPos({ 780,228 }, ImGuiCond_FirstUseEver);
		if (ImGui::BeginPopupModal("Scripts", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
		{
			scripts_popupmodal();

			ImGui::EndPopup();
		}
		
	}
}