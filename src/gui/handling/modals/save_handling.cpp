#include "../current_profile/current_profile_tabs.hpp"
#include "fiber_pool.hpp"
#include "thread_pool.hpp"
#include "script.hpp"
#include "services/vehicle/handling_service.hpp"
#include "views/view.hpp"

namespace big
{
	void modal_handling::modal_save_handling()
	{
		ImGui::SetNextWindowSize({ 520, 325 }, ImGuiCond_FirstUseEver);
		if (ImGui::BeginPopupModal("Save Handling"))
		{
			static char name[32];

			components::input_text_with_hint("Name", "Name", name, sizeof(name));

			if (components::button("Cancel"))
			{
				strcpy(name, "");

				ImGui::CloseCurrentPopup();
			}
			ImGui::SameLine();
			if (components::button("Save"))
			{
				g_thread_pool->push([&]
				{
					g_handling_service->save_profile(name);
				});
				ImGui::CloseCurrentPopup();
			}

			ImGui::EndPopup();
		}
	}
}