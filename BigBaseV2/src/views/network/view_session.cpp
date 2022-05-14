#include "fiber_pool.hpp"
#include "util/session.hpp"
#include "views/view.hpp"

namespace big
{
	void view::session() {
		
		for (const SessionType& session_type : sessions)
		{
			components::button(session_type.name, [session_type] {
				session::join_type(session_type);
				});
		}

		if (ImGui::TreeNode("RID Joiner"))
		{
			ImGui::Checkbox("Enable", &g->session.joiner);

			g_notification_service->push("Warning", "After setting RID go to ONLINE > CREWS > CREW MEMBERS, \nthen selected an random crew member, hit JOIN game ");
			ImGui::Text("Rockstar ID:");
			ImGui::InputScalar("##rockstar_id_input", ImGuiDataType_U64, &g->session.rid_to_join);

			ImGui::TreePop();

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
			if (ImGui::Button("Clear Override"))
			{
				g_fiber_pool->queue_job([]
				{
					MISC::CLEAR_OVERRIDE_WEATHER();
				});
			}

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