#include "core/data/weathers.hpp"
#include "views/view.hpp"

namespace big
{
	void view::time_and_weather()
	{
		components::command_checkbox<"timeoverride">();

		if (g.world.custom_time.override_time)
		{
			ImGui::SliderInt("HOUR"_T.data(), &g.world.custom_time.hour, 0, 23);
			ImGui::SliderInt("MINUTE"_T.data(), &g.world.custom_time.minute, 0, 59);
			ImGui::SliderInt("SECOND"_T.data(), &g.world.custom_time.second, 0, 59);
		}

		components::command_checkbox<"weatheroverride">();

		if (g.world.override_weather)
		{
			if (ImGui::BeginCombo("VIEW_TIME_AND_WEATHER_WEATHER"_T.data(), weathers[g.world.local_weather]))
			{
				for (int i = 0; i < weathers.size(); i++)
				{
					if (ImGui::Selectable(weathers[i], g.world.local_weather == i))
					{
						g.world.local_weather = i;
					}

					if (g.world.local_weather == i)
					{
						ImGui::SetItemDefaultFocus();
					}
				}

				ImGui::EndCombo();
			}
		}

		components::command_checkbox<"blackout">();
	}
}
