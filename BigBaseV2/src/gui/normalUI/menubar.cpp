#include "views/view.hpp"
#include "natives.hpp"
#include "fiber_pool.hpp"
#include "util/session.hpp"
#include "asi_loader/asi_scripts.h"
#include "shv_runner.h"

namespace big
{
    void view::menu_bar()
    {
        if (ImGui::BeginMainMenuBar())
        {
            if (ImGui::BeginMenu("File"))
            {
                if (ImGui::MenuItem("Unload Menu"))
                {
                    g_running = false;
                }

                if (ImGui::MenuItem("Rage Quit (hard crash)"))
                {
                    __debugbreak();
                    g_running = false;

                    TerminateProcess(GetCurrentProcess(), 0);
                }
                ImGui::EndMenu();
            }

            if (ImGui::BeginMenu("Session"))
            {
                for (const SessionType& session_type : sessions)
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
                if (ImGui::MenuItem("Clear Tasks"))
                {
                    QUEUE_JOB_BEGIN_CLAUSE()
                    {
                        TASK::CLEAR_PED_TASKS_IMMEDIATELY(PLAYER::PLAYER_PED_ID());
                    }
                    QUEUE_JOB_END_CLAUSE
                }

                ImGui::Separator();

                if (ImGui::MenuItem("Stop Player Switch"))
                {
                    QUEUE_JOB_BEGIN_CLAUSE()
                    {
                        STREAMING::STOP_PLAYER_SWITCH();
                    }
                    QUEUE_JOB_END_CLAUSE
                }
                if (ImGui::MenuItem("Stop Loading"))
                {
                    QUEUE_JOB_BEGIN_CLAUSE()
                    {
                        if (CAM::IS_SCREEN_FADED_OUT())
                        {
                            CAM::DO_SCREEN_FADE_IN(0);
                        }
                        SCRIPT::SHUTDOWN_LOADING_SCREEN();
                    }
                    QUEUE_JOB_END_CLAUSE
                }
                ImGui::EndMenu();
            }

            if (ImGui::BeginMenu("Windows"))
            {
                ImGui::MenuItem("Main", nullptr, &g->window.main);
                ImGui::MenuItem("Player", nullptr, &g->window.player);
                ImGui::MenuItem("Players", nullptr, &g->window.users);
                ImGui::MenuItem("Score Controller", nullptr, &g->window.score_controller);
                ImGui::MenuItem("Overlay", nullptr, &g->window.overlay);
                ImGui::MenuItem("Chat", nullptr, &g->window.chat);
                ImGui::MenuItem("Demo", nullptr, &g->window.demo);

                ImGui::EndMenu();
            }

            ImGui::EndMainMenuBar();
        }
    }
}
