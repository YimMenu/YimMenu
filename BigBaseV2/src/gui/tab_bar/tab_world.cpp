#include "tab_bar.hpp"

namespace big
{
	static int clock[3];

	void tabbar::render_world()
	{
		if (ImGui::BeginTabItem("World"))
		{
			ImGui::Text("Set Local Time:");
			if (ImGui::InputInt3(": H:M:s", clock))
			{
				QUEUE_JOB_BEGIN_CLAUSE()
				{
					CLOCK::SET_CLOCK_TIME(clock[0], clock[1], clock[2]);
				}QUEUE_JOB_END_CLAUSE
			}

			ImGui::Text("Set Local Weather:");
			if (ImGui::BeginCombo("##set_local_weather", weather_names[g_temp.weather_type]))
			{
				for (uint8_t i = 0; i < IM_ARRAYSIZE(weather_names); i++)
				{
					bool is_selected = (g_temp.weather_type == i);
					if (ImGui::Selectable(weather_names[i], is_selected))
						g_temp.weather_type = i;
					if (is_selected)
						ImGui::SetItemDefaultFocus();
				}

				ImGui::EndCombo();
			}
			if (ImGui::Button("Set Weather"))
			{
				QUEUE_JOB_BEGIN_CLAUSE(=)
				{
					MISC::SET_WEATHER_TYPE_NOW(weather_types[g_temp.weather_type]);
				}QUEUE_JOB_END_CLAUSE
			}

			ImGui::EndTabItem();
		}
	}
}