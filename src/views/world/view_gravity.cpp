#include "views/view.hpp"

namespace big
{
	void view::gravity()
	{
		components::command_checkbox<"modifygravity">();

		if (g.world.gravity.modify_gravity)
		{
			ImGui::SliderFloat("GRAVITY_LEVEL"_T.data(), &g.world.gravity.current_gravity, 0.f, 1000.f, "%.1f");

			ImGui::Separator();
			components::sub_title("GRAVITY_LUNAR_PRESETS"_T);

			// non-planets
			components::button("GRAVITY_MOON"_T, [] { g.world.gravity.current_gravity = 1.6f; });
			ImGui::SameLine();
			components::button("GRAVITY_SUN"_T, [] { g.world.gravity.current_gravity = 274.f; });
			ImGui::SameLine();
			components::button("GRAVITY_PLUTO"_T, [] { g.world.gravity.current_gravity = 0.6f; });
			ImGui::SameLine();
			components::button("GRAVITY_SPACE"_T, [] { g.world.gravity.current_gravity = 0.f; });
			
			// planets
			components::button("GRAVITY_MERCURY"_T, [] { g.world.gravity.current_gravity = 3.7f; });
			ImGui::SameLine();
			components::button("GRAVITY_VENUS"_T, [] { g.world.gravity.current_gravity = 8.9f; });
			ImGui::SameLine();
			components::button("GRAVITY_EARTH"_T, [] { g.world.gravity.current_gravity = 9.8f; });
			ImGui::SameLine();
			components::button("GRAVITY_MARS"_T, [] { g.world.gravity.current_gravity = 3.7f; });
			
			components::button("GRAVITY_JUPITER"_T, [] { g.world.gravity.current_gravity = 24.8f; });
			ImGui::SameLine();
			components::button("GRAVITY_SATURN"_T, [] { g.world.gravity.current_gravity = 10.5f; });
			ImGui::SameLine();
			components::button("GRAVITY_URANUS"_T, [] { g.world.gravity.current_gravity = 8.7f; });
			ImGui::SameLine();
			components::button("GRAVITY_NEPTUNE"_T, [] { g.world.gravity.current_gravity = 11.2f; });
		}
	}
}