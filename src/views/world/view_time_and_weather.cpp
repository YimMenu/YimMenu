#include "views/view.hpp"
#include "fiber_pool.hpp"
#include "util/session.hpp"

namespace big
{
	void view::time_and_weather()
	{
		if (ImGui::TreeNode("Local Time"))
		{
			ImGui::Checkbox("Override Time", &g.session.override_time);

			if (g.session.override_time)
			{
				ImGui::SliderInt("Hour", &g.session.custom_time.hour, 0, 23);
				ImGui::SliderInt("Minute", &g.session.custom_time.minute, 0, 59);
				ImGui::SliderInt("Second", &g.session.custom_time.second, 0, 59);
			}

			ImGui::TreePop();
		}

		if (ImGui::TreeNode("Local Weather"))
		{
			components::button("Clear Override", []
			{
				MISC::CLEAR_OVERRIDE_WEATHER();
			});

			if (ImGui::ListBox("", &g.session.local_weather, session::weathers, 15))
			{
				g_fiber_pool->queue_job([]
				{
					session::local_weather();
				});

				ImGui::ListBoxFooter();
			}

			ImGui::TreePop();
		}
	}
}
