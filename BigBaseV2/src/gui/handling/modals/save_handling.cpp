#include "../current_profile/current_profile_tabs.hpp"
#include "fiber_pool.hpp"
#include "thread_pool.hpp"
#include "natives.hpp"
#include "script.hpp"
#include "services/vehicle_service.hpp"

namespace big
{
	void modal_handling::modal_save_handling()
	{
		ImGui::SetNextWindowSize({ 520, 325 }, ImGuiCond_FirstUseEver);
		if (ImGui::BeginPopupModal("Save Handling"))
		{
			static char name[32], description[256] = "No description.";

			switch (g_vehicle_service->publish_status())
			{
			case PublishStatus::SAVING:
				ImGui::Text("Saving...");

				return ImGui::EndPopup();
			case PublishStatus::SAVED:
				strcpy(name, "");
				strcpy(description, "No description.");

				g_vehicle_service->publish_status(PublishStatus::IDLE);
				g_vehicle_service->update_mine(true);

				ImGui::CloseCurrentPopup();

				return ImGui::EndPopup();
			case PublishStatus::FAILED:
				ImGui::TextColored({ 255, 0, 0, 1 }, "Failed to save handling profile.");

				ImGui::Separator();
			}

			QUEUE_JOB_BEGIN_CLAUSE()
			{
				PAD::DISABLE_ALL_CONTROL_ACTIONS(0);
			}QUEUE_JOB_END_CLAUSE

				ImGui::BeginGroup();

			ImGui::Text("Name:");
			ImGui::Text("Description:");

			ImGui::EndGroup();
			ImGui::SameLine();
			ImGui::BeginGroup();

			ImGui::InputText("##modal_handling_name", name, sizeof(name));
			ImGui::InputTextMultiline("##modal_handling_description", description, sizeof(description));

			ImGui::EndGroup();

			if (ImGui::Button("Cancel"))
			{
				strcpy(name, "");
				strcpy(description, "No description.");

				ImGui::CloseCurrentPopup();
			}
			ImGui::SameLine();
			if (ImGui::Button("Save"))
			{
				g_thread_pool->push([&]
					{
						g_vehicle_service->publish_profile(name, description);
					});
			}

			ImGui::EndPopup();
		}
	}
}