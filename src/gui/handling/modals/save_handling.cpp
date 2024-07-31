#include "../current_profile/current_profile_tabs.hpp"
#include "services/vehicle/handling_service.hpp"
#include "thread_pool.hpp"
#include "views/view.hpp"

namespace big
{
	void modal_handling::modal_save_handling()
	{
		ImGui::SetNextWindowSize({520, 325}, ImGuiCond_FirstUseEver);
		if (ImGui::BeginPopupModal("HANDLING_SAVE_HANDLING"_T.data()))
		{
			static char name[32];

			components::input_text_with_hint("NAME"_T, "NAME"_T, name, sizeof(name));

			if (components::button("CANCEL"_T))
			{
				strcpy(name, "");

				ImGui::CloseCurrentPopup();
			}
			ImGui::SameLine();
			if (components::button("SAVE"_T))
			{
				g_thread_pool->push([&] {
					g_handling_service->save_profile(name);
				});
				ImGui::CloseCurrentPopup();
			}

			ImGui::EndPopup();
		}
	}
}