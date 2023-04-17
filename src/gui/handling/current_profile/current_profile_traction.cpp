#include "current_profile_tabs.hpp"

namespace big
{
	void tab_current_profile::tab_traction()
	{
		if (ImGui::BeginTabItem("HANDLING_TAB_TRACTION"_T.data()))
		{
			ImGui::Text("HANDLING_MINIMUM_TRACTION"_T.data());
			ImGui::SliderFloat("##traction curve min", &g_local_player->m_vehicle->m_handling_data->m_traction_curve_min, 0.f, 7.f);

			ImGui::Text("HANDLING_PEAK_TRACTION"_T.data());
			ImGui::SliderFloat("##traction curve max", &g_local_player->m_vehicle->m_handling_data->m_traction_curve_max, 0.f, 7.f);

			ImGui::Text("HANDLING_TRACTION_CURVE"_T.data());
			ImGui::SliderAngle("##traction curve lateral", &g_local_player->m_vehicle->m_handling_data->m_traction_curve_lateral);

			ImGui::Text("HANDLING_TRACTION_HEIGHT_LOSS"_T.data());
			ImGui::SliderFloat("##traction spring delta max", &g_local_player->m_vehicle->m_handling_data->m_traction_spring_delta_max, 0.f, 2.f);

			ImGui::Text("HANDLING_BURNOUT_MULTIPLIER"_T.data());
			ImGui::SliderFloat("##low speed traction loss mult", &g_local_player->m_vehicle->m_handling_data->m_low_speed_traction_loss_mult, 0.f, 10.f);

			//ImGui::Text("Camber Stiffness (grip when drifting)");
			//ImGui::SliderFloat("##camber stiffness", &g_local_player->m_vehicle->m_handling_data->m_camber_stiffness, -1.f, 1.f);

			ImGui::Text("HANDLING_TRACTION_BIAS"_T.data());
			float fTractionBiasFront = g_local_player->m_vehicle->m_handling_data->m_traction_bias_front / 2;
			if (ImGui::SliderFloat("##traction bias front", &fTractionBiasFront, 0.01f, .99f))
				g_local_player->m_vehicle->m_handling_data->m_traction_bias_front = fTractionBiasFront * 2;

			ImGui::Text("HANDLING_OFF_ROAD_LOSS"_T.data());
			ImGui::SliderFloat("##traction loss mult", &g_local_player->m_vehicle->m_handling_data->m_traction_loss_mult, 0.f, 5.f);

			ImGui::EndTabItem();
		}
	}
}