#include "fiber_pool.hpp"
#include "gui/window.hpp"
#include "imgui.h"
#include "script.hpp"
#include "util/notify.hpp"
#include "util/session.hpp"

namespace big
{
	void window::top_bar()
	{
		if (ImGui::BeginMainMenuBar())
		{
			if (ImGui::BeginMenu("Info"))
			{
				ImGui::MenuItem("Logged in as:", NULL, false, false);
				ImGui::MenuItem(g_local_player == nullptr || g_local_player->m_player_info == nullptr ? "unknown" : g_local_player->m_player_info->m_net_player_data.m_name, NULL, false, false);

				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Session"))
			{
				for (const SessionType &session_type : sessions)
				{
					if (ImGui::MenuItem(session_type.name))
					{
						QUEUE_JOB_BEGIN_CLAUSE(&)
						{
							session::join_type(session_type);
						}QUEUE_JOB_END_CLAUSE
					}
				}

				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Extra"))
			{
				if (ImGui::MenuItem("Skip Cutscene"))
				{
					QUEUE_JOB_BEGIN_CLAUSE()
					{
						CUTSCENE::STOP_CUTSCENE_IMMEDIATELY();
					}
					QUEUE_JOB_END_CLAUSE
				}

				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Windows"))
			{
				ImGui::MenuItem("Main", nullptr, &g.window.main);
				ImGui::MenuItem("Players", nullptr, &g.window.users);
				ImGui::MenuItem("Logs", nullptr, &g.window.log);

				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Quit"))
			{
				if (ImGui::MenuItem("Unload Menu"))
				{
					g_running = false;
				}

				if (ImGui::MenuItem("Rage Quit (hard crash)"))
				{
					__debugbreak();
				}

				ImGui::EndMenu();
			}

			ImGui::EndMainMenuBar();
		}
	}
}