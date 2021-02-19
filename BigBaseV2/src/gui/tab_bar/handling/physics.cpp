#include "gui/tab_bar.hpp"

namespace big
{
	void tabbar::handling_physics()
	{
		if (ImGui::BeginTabItem("Physics"))
		{
			ImGui::Text("Gravity");
			ImGui::SliderFloat("##Gravity", &g_vehicle->m_gravity, -50.f, 50.f);

			ImGui::Text("Mass");
			ImGui::SliderFloat("##Mass", &g_vehicle->m_handling->m_mass, 0.f, 50000.f);

			ImGui::Text("Centre of mass");
			float fCenterOfMass[3];
			fCenterOfMass[0] = g_vehicle->m_handling->m_centre_of_mass.x;
			fCenterOfMass[1] = g_vehicle->m_handling->m_centre_of_mass.y;
			fCenterOfMass[2] = g_vehicle->m_handling->m_centre_of_mass.z;
			if (ImGui::SliderFloat3("##centre_of_mass", fCenterOfMass, -10.f, 10.f))
			{
				g_vehicle->m_handling->m_centre_of_mass.x = fCenterOfMass[0];
				g_vehicle->m_handling->m_centre_of_mass.y = fCenterOfMass[1];
				g_vehicle->m_handling->m_centre_of_mass.z = fCenterOfMass[2];
			}

			ImGui::Text("Inertia Multiplier");
			float fInertiaMult[3];
			fInertiaMult[0] = g_vehicle->m_handling->m_inertia_multiplier.x;
			fInertiaMult[1] = g_vehicle->m_handling->m_inertia_multiplier.y;
			fInertiaMult[2] = g_vehicle->m_handling->m_inertia_multiplier.z;
			if (ImGui::SliderFloat3("##inertia_multiplier", fInertiaMult, -10.f, 10.f))
			{
				g_vehicle->m_handling->m_inertia_multiplier.x = fInertiaMult[0];
				g_vehicle->m_handling->m_inertia_multiplier.y = fInertiaMult[1];
				g_vehicle->m_handling->m_inertia_multiplier.z = fInertiaMult[2];
			}

			ImGui::Text("Buoyancy");
			ImGui::SliderFloat("##buoyancy", &g_vehicle->m_handling->m_buoyancy, .01f, 99.f);

			ImGui::EndTabItem();
		}
	}
}