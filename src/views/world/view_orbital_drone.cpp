#include "views/view.hpp"

namespace big
{
	void view::orbital_drone()
	{
        components::command_checkbox<"orbitaldrone">();

		if (g.world.orbital_drone.enabled)
		{
			ImGui::Separator();
			ImGui::BeginGroup();
			ImGui::Text("ORBITAL_DRONE_USAGE_DESCR"_T.data());
			ImGui::EndGroup();
			ImGui::Separator();

			ImGui::BeginGroup();
			ImGui::Checkbox("ORBITAL_DRONE_AUTO_LOCK_ON_PLAYER"_T.data(), &g.world.orbital_drone.detect_player);
			if (ImGui::IsItemHovered())
			{
				ImGui::BeginTooltip();
				ImGui::Text("ORBITAL_DRONE_AUTO_LOCK_ON_PLAYER_TOOLTIP"_T.data());
				ImGui::EndTooltip();
			}
			ImGui::Text("ORBITAL_DRONE_HIGH_SPEED_MULTIPLIER"_T.data());
			ImGui::SliderFloat("##fastspeed", &g.world.orbital_drone.nav_ovverride_fast, 1.f, 10.f);
			ImGui::Text("ORBITAL_DRONE_LOW_SPEED_MULTIPLIER"_T.data());
			ImGui::SliderFloat("##slowspeed", &g.world.orbital_drone.nav_ovverride_slow, 0.f, 1.f);
			ImGui::EndGroup();
		}

	}
}