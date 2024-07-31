#include "gui.hpp"
#include "services/gta_data/gta_data_service.hpp"
#include "view.hpp"

namespace big
{
	void view::gta_data()
	{
		if (!g.settings.onboarding_complete)
			return;

		if (g_gta_data_service.cache_needs_update())
		{
			g_gui->toggle(true);
			ImGui::OpenPopup("GAME_CACHE"_T.data());
		}

		ImGui::SetNextWindowSize({800, 210}, ImGuiCond_FirstUseEver);
		ImGui::SetNextWindowPos({200, 200}, ImGuiCond_FirstUseEver);
		if (ImGui::BeginPopupModal("GAME_CACHE"_T.data()))
		{
			switch (g_gta_data_service.state())
			{
			case eGtaDataUpdateState::NEEDS_UPDATE:
			{
				ImGui::Text("GAME_CACHE_UPDATE"_T.data());

				if (ImGui::Button("GAME_CACHE_UPDATE_CACHE"_T.data()))
				{
					g_gta_data_service.update_now();
				}

				break;
			}
			case eGtaDataUpdateState::WAITING_FOR_SINGLE_PLAYER:
			{
				ImGui::Text("GAME_CACHE_WAITING_FOR_SINGLE_PLAYER"_T.data());

				break;
			}
			case eGtaDataUpdateState::UPDATING:
			{
				ImGui::Text("GAME_CACHE_UPDATING"_T.data());

				break;
			}
			case eGtaDataUpdateState::IDLE:
			{
				ImGui::CloseCurrentPopup();

				break;
			}
			}

			ImGui::EndPopup();
		}
	}
}
