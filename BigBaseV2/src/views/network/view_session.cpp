#include "fiber_pool.hpp"
#include "util/session.hpp"
#include "views/view.hpp"

namespace big
{
	void view::session()
	{
		components::sub_title("Session Switcher");
		if (ImGui::ListBoxHeader("###session_switch"))
		{
			for (const auto& session_type : sessions)
			{
				components::selectable(session_type.name, false, [&session_type] 
				{
					session::join_type(session_type.id);
				});
			}
			ImGui::EndListBox();
		}
		if (ImGui::TreeNode("Local Time"))
		{
			ImGui::Checkbox("Override Time", &g->session.override_time);

			if (g->session.override_time)
			{
				ImGui::SliderInt("Hour", &g->session.custom_time.hour, 0, 23);
				ImGui::SliderInt("Minute", &g->session.custom_time.minute, 0, 59);
				ImGui::SliderInt("Second", &g->session.custom_time.second, 0, 59);
			}

			ImGui::TreePop();
		}
		if (ImGui::TreeNode("Local Weather"))
		{
			components::button("Clear Override", []
			{
				MISC::CLEAR_OVERRIDE_WEATHER();
			});

			if(ImGui::ListBox("", &g->session.local_weather, session::weathers, 15))
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