#include "gui/window.hpp"
#include "features/functions.hpp"
#include "features/notify.hpp"
#include "natives.hpp"
#include "script.hpp"
#include "fiber_pool.hpp"

namespace big
{
	void window::render_top_bar()
	{
		if (ImGui::BeginMainMenuBar())
		{
			if (ImGui::BeginMenu("Info"))
			{
				ImGui::MenuItem("Logged in as:", NULL, false, false);
				ImGui::MenuItem(g_player.name, NULL, false, false);

				if (ImGui::MenuItem("Am I lobby host?"))
				{
					QUEUE_JOB_BEGIN_CLAUSE()
					{
						notify::above_map(NETWORK::NETWORK_IS_HOST() ? "~g~Yes you are the host." : "You aren't the host.");
					}
					QUEUE_JOB_END_CLAUSE

				}

				if (ImGui::MenuItem("Flagged Account?"))
				{
					QUEUE_JOB_BEGIN_CLAUSE()
					{
						notify::above_map(NETWORK::NETWORK_PLAYER_IS_BADSPORT() ? "You have been ~r~reported multiple times!" : "Your account is in good standing.");
					}
					QUEUE_JOB_END_CLAUSE
				}

				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Extra"))
			{
				if (ImGui::MenuItem("Skip Cutscene"))
				{
					QUEUE_JOB_BEGIN_CLAUSE()
					{
						if (CUTSCENE::IS_CUTSCENE_ACTIVE())
							CUTSCENE::STOP_CUTSCENE_IMMEDIATELY();
						else
							notify::above_map("There's no cutscene active at the moment.");
					}
					QUEUE_JOB_END_CLAUSE
				}

				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Session"))
			{
				for (uint8_t i = 0; i < IM_ARRAYSIZE(sessions); i++)
				{
					if (ImGui::MenuItem(sessions[i].descr))
					{
						auto session = sessions[i];

						QUEUE_JOB_BEGIN_CLAUSE(&)
						{
							func::join_session_type(session);
						}QUEUE_JOB_END_CLAUSE
					}
				}

				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Quit"))
			{
				if (ImGui::MenuItem("Unload Menu (may crash)"))
				{
					g_running = false;
				}

				if (ImGui::MenuItem("Rage Quit (hard crash)"))
				{
					exit(0);
				}

				ImGui::EndMenu();
			}

			ImGui::EndMainMenuBar();
		}
	}
}