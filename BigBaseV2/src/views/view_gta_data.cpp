#include "view.hpp"
#include "services/gta_data/gta_data_service.hpp"
#include "pointers.hpp"

namespace big
{
	void view::gta_data()
	{
		static bool show_popup = true;

		if (g_gta_data_service && g_gta_data_service->cache_need_update && !*g_pointers->m_is_session_started && show_popup)
		{
			if (show_popup)
			{
				ImGui::OpenPopup("Game Cache");
			}

			ImGui::SetNextWindowSize(ImVec2(800, 0), ImGuiCond_FirstUseEver);
			if (ImGui::BeginPopupModal("Game Cache"))
			{
				ImGui::Text("Please go in any GTA Online session so that the vehicle, ped and weapon cache build itself.\nYou can force the cache to be built by clicking the Force Cache Update In SinglePlayer button below,\nbut beware: the game will crash if you go to GTA Online afterward.");

				if (ImGui::Button("Force Cache Update In SinglePlayer"))
				{
					show_popup = false;
					ImGui::CloseCurrentPopup();

					g_gta_data_service->force_cache_update = true;
				}

				if (ImGui::Button("Ok I'll go to GTA Online"))
				{
					show_popup = false;
					ImGui::CloseCurrentPopup();
				}

				ImGui::EndPopup();
			}
		}
	}
}
