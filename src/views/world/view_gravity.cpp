#include "views/view.hpp"
#include "core/data/gravity_presets.hpp"

namespace big
{
	void view::gravity()
	{
		components::command_checkbox<"modifygravity">();

		if (g.world.gravity.modify_gravity)
		{
			ImGui::SliderFloat("GRAVITY_LEVEL"_T.data(), &g.world.gravity.current_gravity, 0.f, 1000.f, "%.1f");

			static int selected_lunar_preset = 0;

			if (ImGui::Combo("GRAVITY_LUNAR_PRESETS"_T.data(), &selected_lunar_preset, gravity_presets.data(), gravity_presets.size()))
			{
				g.world.gravity.current_gravity = gravity_preset_values[selected_lunar_preset];
			}
		}
	}
}