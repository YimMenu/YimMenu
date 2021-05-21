#include "gui/window.hpp"
#include "imgui.h"
#include "fiber_pool.hpp"
#include "script.hpp"
#include "util/notify.hpp"

namespace big
{
	void window::top_bar()
	{
		if (ImGui::BeginMainMenuBar())
		{
			if (ImGui::BeginMenu("Info"))
			{
				ImGui::MenuItem("Logged in as:", NULL, false, false);
				ImGui::MenuItem("unknown", NULL, false, false);

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
						CUTSCENE::STOP_CUTSCENE_IMMEDIATELY();
					}
					QUEUE_JOB_END_CLAUSE
				}

				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Windows"))
			{
				ImGui::MenuItem("Main Window", nullptr, &g.window.main);

				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Quit"))
			{
				if (ImGui::MenuItem("Unload Menu (may crash)"))
				{
					QUEUE_JOB_BEGIN_CLAUSE(&)
					{
						g_running = false;

						notify::above_map("Thanks for using Yim's Mod Menu");
					}QUEUE_JOB_END_CLAUSE
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