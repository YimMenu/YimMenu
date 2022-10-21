#include "views/view.hpp"
#include "natives.hpp"
#include "fiber_pool.hpp"
#include "util/session.hpp"

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
                    exit(0);
                    g_running = false;

                    TerminateProcess(GetCurrentProcess(), 0);
                }
                ImGui::EndMenu();
            }

            if (ImGui::BeginMenu("Session"))
            {
                for (const SessionType& session_type : sessions)
                {
                    components::menu_item(session_type.name, [session_type]
                    {
                        session::join_type(session_type.id);
                    });
                }

                ImGui::EndMenu();
            }

            if (ImGui::BeginMenu("Extra"))
            {
                components::menu_item("Skip Cutscene", []
                {
                    CUTSCENE::STOP_CUTSCENE_IMMEDIATELY();
                });
                components::menu_item("Clear Tasks", []
                {
                    TASK::CLEAR_PED_TASKS_IMMEDIATELY(PLAYER::PLAYER_PED_ID());
                });

                ImGui::Separator();

                components::menu_item("Stop Player Switch", []
                {
                    STREAMING::STOP_PLAYER_SWITCH();
                });
                components::menu_item("Stop Loading", []
                {
                    if (CAM::IS_SCREEN_FADED_OUT())
                    {
                        CAM::DO_SCREEN_FADE_IN(0);
                    }
                    SCRIPT::SHUTDOWN_LOADING_SCREEN();
                });
                ImGui::EndMenu();
            }

            if (ImGui::BeginMenu("Windows"))
            {
                ImGui::MenuItem("Main", nullptr, &g->window.main);
                ImGui::MenuItem("Player", nullptr, &g->window.player);
                ImGui::MenuItem("Players", nullptr, &g->window.users);
                ImGui::MenuItem("Overlay", nullptr, &g->window.overlay);
                ImGui::MenuItem("Chat WIP", nullptr, &g->window.chat);
                ImGui::MenuItem("Demo", nullptr, &g->window.demo);

                ImGui::EndMenu();
            }

            ImGui::EndMainMenuBar();
        }
    }
}
