#include "gui.hpp"
#include "pointers.hpp"
#include "services/gta_data/gta_data_service.hpp"
#include "view.hpp"

namespace big
{
	void view::gta_data()
	{
		if (!g_gta_data_service)
			return;

		if (g_gta_data_service->cache_needs_update())
		{
			g_gui->toggle(true);
			ImGui::OpenPopup("GAME_CACHE"_T.data());
		}

		ImGui::SetNextWindowSize({800, 210}, ImGuiCond_FirstUseEver);
		ImGui::SetNextWindowPos({200, 200}, ImGuiCond_FirstUseEver);
		if (ImGui::BeginPopupModal("GAME_CACHE"_T.data()))
		{
			switch (g_gta_data_service->state())
			{
			case eGtaDataUpdateState::NEEDS_UPDATE:
			{
				ImGui::Text("GAME_CACHE_UPDATE"_T.data());

				if (*g_pointers->m_is_session_started)
				{
					if (ImGui::Button("GAME_CACHE_UPDATE_CACHE"_T.data()))
					{
						g_gta_data_service->update_now();
					}
				}
				else
				{
					ImGui::TextWrapped("GAME_CACHE_SINGLE_PLAYER_DESCRIPTION"_T.data());

					if (ImGui::Button("GAME_CACHE_DONT_CARE"_T.data()))
					{
						g_gta_data_service->update_now();
					}

					if (ImGui::Button("GAME_CACHE_GO_ONLINE"_T.data()))
					{
						g_gta_data_service->update_in_online();
					}
				}

				break;
			}
			case eGtaDataUpdateState::WAITING_FOR_SINGLE_PLAYER:
			{
				ImGui::Text("GAME_CACHE_WAITING_FOR_SINGLE_PLAYER"_T.data());

				break;
			}
			case eGtaDataUpdateState::WAITING_FOR_ONLINE:
			{
				ImGui::Text("GAME_CACHE_WAITING_FOR_ONLINE"_T.data());

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
