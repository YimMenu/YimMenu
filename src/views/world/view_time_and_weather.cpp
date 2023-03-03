#include "fiber_pool.hpp"
#include "util/session.hpp"
#include "views/view.hpp"

namespace big
{
	void view::time_and_weather()
	{
		if (ImGui::TreeNode("LOCAL_TIME"_T.data()))
		{
			ImGui::Checkbox("OVERRIDE_TIME"_T.data(), &g.session.override_time);

			if (g.session.override_time)
			{
				ImGui::SliderInt("HOUR"_T.data(), &g.session.custom_time.hour, 0, 23);
				ImGui::SliderInt("MINUTE"_T.data(), &g.session.custom_time.minute, 0, 59);
				ImGui::SliderInt("SECOND"_T.data(), &g.session.custom_time.second, 0, 59);
			}

			ImGui::TreePop();
		}

		if (ImGui::TreeNode("LOCAL_WEATHER"_T.data()))
		{
			components::button("CLEAR_OVERRIDE"_T, [] {
				MISC::CLEAR_OVERRIDE_WEATHER();
			});

			if (ImGui::ListBox("##weather-listbox", &g.session.local_weather, session::weathers, 15))
			{
				g_fiber_pool->queue_job([] {
					session::local_weather();
				});

				ImGui::ListBoxFooter();
			}

			ImGui::TreePop();
		}
	}
}
