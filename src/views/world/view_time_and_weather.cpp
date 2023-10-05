#include "views/view.hpp"
#include "core/settings.hpp"

namespace big
{
	void view::time_and_weather()
	{
		components::command_checkbox<"timeoverride">();

		if (g.world.custom_time.override_time)
		{
			ImGui::SliderInt("Hour", &g.world.custom_time.hour, 0, 23);
			ImGui::SliderInt("Minute", &g.world.custom_time.minute, 0, 59);
			ImGui::SliderInt("Second", &g.world.custom_time.second, 0, 59);
		}
	}
}
