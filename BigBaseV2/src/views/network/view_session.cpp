#include "fiber_pool.hpp"
#include "util/session.hpp"
#include "views/view.hpp"
#include "logger.hpp"
#include "services/player_database/player_database_service.hpp"

namespace big
{
	void view::session()
	{
		if (ImGui::TreeNode("Session Switcher"))
		{
			if (ImGui::ListBoxHeader("###session_switch"))
			{
				for (const auto& session_type : sessions)
				{
					components::selectable(session_type.name, false, [session_type] {
						session::join_type(session_type);
					});
				}
				ImGui::EndListBox();
			}
		}

		if (ImGui::TreeNode("RID Joiner"))
		{
			static int rid = 0;
			ImGui::InputInt("RID", &rid);
			components::button("Join", [] {
				session::join_by_rockstar_id(rid);
			});

			/*components::button("INFO_D", [] {
				rage::rlGamerHandle player_handle(rid);
				rage::rlSessionByGamerTaskResult result;
				bool success = false;
				int state = 0;
				if (g_pointers->m_start_get_session_by_gamer_handle(0, &player_handle, 1, &result, 1, &success, &state))
				{
					while (state == 1)
						script::get_current()->yield();

					if (state == 3 && success)
					{
						g->session.session_info = result.m_session_info;
						LOG(G3LOG_DEBUG) << "Session host RID: " << g->session.session_info.m_rockstar_id;
						return;
					}
				}
			});*/

			ImGui::TreePop();
		}

		if (ImGui::TreeNode("Settings"))
		{
			ImGui::Checkbox("Fast Join", &g->tunables.fast_join);
			
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
			components::button("Clear Override", [] {
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