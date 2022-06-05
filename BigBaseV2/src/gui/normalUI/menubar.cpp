#include "views/view.hpp"
#include "natives.hpp"
#include "fiber_pool.hpp"

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
                        SCRIPT::SHUTDOWN_LOADING_SCREEN();
                    }
                    QUEUE_JOB_END_CLAUSE
                }
                ImGui::EndMenu();
            }

            if (ImGui::BeginMenu("Windows"))
            {
                ImGui::MenuItem("Main", nullptr, &g->window.main);
                ImGui::MenuItem("DockerSpace", nullptr, &g->window.docker_space);
                ImGui::MenuItem("Overlay", nullptr, &g->window.overlay);
                ImGui::MenuItem("Debug", nullptr, &g->window.debug);

                ImGui::EndMenu();
            }


            ImGui::EndMainMenuBar();
            if (g->window.docker_space) 
            {
                if (ImGui::Begin("DockSpace"))
                {
                    // Submit the DockSpace
                    ImGuiIO& io = ImGui::GetIO();
                    if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
                    {
                        ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
                        ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f));
                    }
                }
            }
        }
    }
}
