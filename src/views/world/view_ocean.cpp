#include "views/view.hpp"

namespace big
{
	void view::ocean()
	{
		components::command_checkbox<"modifyocean">();

		if (g.world.ocean.modify_ocean)
		{
			components::command_checkbox<"disableocean">();

			ImGui::SliderInt("OCEAN_OPACITY"_T.data(), &g.world.ocean.ocean_opacity, 0, 100);
		}
	}
}