#include "current_profile_tabs.hpp"

namespace big
{
	void tab_current_profile::tab_suspension()
	{
		if (ImGui::BeginTabItem("HANDLING_TAB_SUSPENSION"_T.data()))
		{
			ImGui::Text("HANDLING_SUSPENSION_FORCE"_T.data());
			ImGui::SliderFloat("##suspension force", &g_local_player->m_vehicle->m_handling_data->m_suspension_force, 0.f, 5.f);

			ImGui::Text("HANDLING_SUSPENSION_COMPRESSION_DAMP"_T.data());
			ImGui::SliderFloat("##suspension comp", &g_local_player->m_vehicle->m_handling_data->m_suspension_comp_damp, 0.f, 5.f);

			ImGui::Text("HANDLING_SUSPENSION_REBOUND_DAMP"_T.data());
			ImGui::SliderFloat("##suspension rebound", &g_local_player->m_vehicle->m_handling_data->m_suspension_rebound_damp, 0.f, 5.f);

			ImGui::Text("HANDLING_SUSPENSION_UPPER_LIMIT"_T.data());
			ImGui::SliderFloat("##suspension upper", &g_local_player->m_vehicle->m_handling_data->m_suspension_upper_limit, -1.f, 1.f);

			ImGui::Text("HANDLING_SUSPENSION_LOWER_LIMIT"_T.data());
			ImGui::SliderFloat("##suspension lower", &g_local_player->m_vehicle->m_handling_data->m_suspension_lower_limit, -1.f, 1.f);

			ImGui::Text("HANDLING_SUSPENSION_RAISE"_T.data());
			ImGui::SliderFloat("##suspension raise", &g_local_player->m_vehicle->m_handling_data->m_suspension_raise, -1.f, 1.f);

			ImGui::Text("HANDLING_SUSPENSION_BAIS_FRONT"_T.data());
			float fSuspensionBiasFront = g_local_player->m_vehicle->m_handling_data->m_suspension_bias_front / 2;
			if (ImGui::SliderFloat("##suspension bias", &fSuspensionBiasFront, 0.f, 1.f))
				g_local_player->m_vehicle->m_handling_data->m_suspension_bias_front = fSuspensionBiasFront * 2;

			ImGui::EndTabItem();
		}
	}
}