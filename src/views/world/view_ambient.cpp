#include "views/view.hpp"

namespace big
{
	void view::ambient()
	{
		ImGui::Checkbox("Override Ped Population", &g->session.population_control.ped_enable);
		if(g->session.population_control.ped_enable)
			ImGui::SliderInt("Ped Population", &g->session.population_control.ped, 0, 3);

		ImGui::Checkbox("Override Vehicle Population", &g->session.population_control.vehicle_enable);
		if(g->session.population_control.vehicle_enable)
			ImGui::SliderInt("Vehicle Population", &g->session.population_control.vehicle, 0, 3);
	}
}
