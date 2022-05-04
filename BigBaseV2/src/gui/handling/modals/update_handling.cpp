#include "../current_profile/current_profile_tabs.hpp"
#include "fiber_pool.hpp"
#include "thread_pool.hpp"
#include "natives.hpp"
#include "script.hpp"
#include "services/vehicle_service.hpp"

namespace big
{
	void modal_handling::modal_update_handling()
	{
		ImGui::SetNextWindowSize({ 520, 325 }, ImGuiCond_FirstUseEver);
		if (ImGui::BeginPopupModal("Update Handling"))
		{
			auto share_code = g_vehicle_service->get_active_profile(g_local_player->m_vehicle->m_handling->m_model_hash);
			if (share_code.empty())
			{
				// should be impossible to trigger but still

				return ImGui::EndPopup();
			}
			auto it = g_vehicle_service->m_handling_profiles.find(share_code);
			if (it == g_vehicle_service->m_handling_profiles.end())
				return ImGui::EndPopup();
			auto profile = it->second;

			static char name[32], description[256] = "No description.";

			strcpy(name, profile.name.c_str());
			strcpy(description, profile.description.c_str());

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
				ImGui::TextColored({ 255, 0, 0, 1 }, "Failed to update handling profile.");

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
			if (ImGui::Button("Update"))
			{
				g_thread_pool->push([&]
					{
						g_vehicle_service->publish_profile(name, description, profile.share_code);
					});
			}

			ImGui::EndPopup();
		}
	}
}