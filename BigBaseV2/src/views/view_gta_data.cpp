#include "view.hpp"
#include "gui.hpp"
#include "pointers.hpp"
#include "services/gta_data/gta_data_service.hpp"

namespace big
{
	void view::gta_data()
	{
		if (!g_gta_data_service)
			return;

		if (g_gta_data_service->cache_needs_update())
		{
			g_gui.m_opened = true;
			ImGui::OpenPopup("Game Cache");
		}

		ImGui::SetNextWindowSize({ 800, 210 }, ImGuiCond_FirstUseEver);
		ImGui::SetNextWindowPos({ 200, 200 }, ImGuiCond_FirstUseEver);
		if (ImGui::BeginPopupModal("Game Cache"))
		{
			switch (g_gta_data_service->state())
			{
			case eGtaDataUpdateState::NEEDS_UPDATE:
			{
				ImGui::Text("YimMenu requires a rebuild of the game cache. This may take up to one minute to generate.");

				if (*g_pointers->m_is_session_started)
				{
					if (ImGui::Button("Update Cache"))
					{
						g_gta_data_service->update_now();
					}
				}
				else
				{
					ImGui::TextWrapped("You are currently in single player, you can force build the cache in single player but risk crashing when going into multiplayer or load online and cache.");

					if (ImGui::Button("I don't care, update in single player!"))
					{
						g_gta_data_service->update_now();
					}

					if (ImGui::Button("Update cache in online."))
					{
						g_gta_data_service->update_in_online();
					}
				}

				break;
			}
			case eGtaDataUpdateState::WAITING_FOR_ONLINE:
			{
				ImGui::Text("Waiting for online to start cache update...");

				break;
			}
			case eGtaDataUpdateState::UPDATING:
			{
				ImGui::Text("Updating cache, please wait...");

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
