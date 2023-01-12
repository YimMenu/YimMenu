#include "views/view.hpp"
#include "pointers.hpp"
#include "services/console/console_service.hpp"
#include "backend/context/default_command_context.hpp"

namespace big
{
    void view::quicksearch()
    {
        if (g.quicksearch.enabled)
        {
            const auto quicksearch_width = static_cast<float>(*g_pointers->m_resolution_x) * 0.5f;
            ImGui::SetNextWindowPos({ quicksearch_width - (quicksearch_width * 0.5f), 80.f });
            if (ImGui::Begin("quicksearch", nullptr, window_flags | ImGuiWindowFlags_NoBackground))
            {   
                static char command_buffer[255];
                ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, { 10.f, 15.f });
                ImGui::SetNextItemWidth(quicksearch_width);
                ImGui::SetKeyboardFocusHere(0);
                components::input_text_with_hint("", "Type your command", command_buffer, sizeof(command_buffer), ImGuiInputTextFlags_EnterReturnsTrue, [] {
                    if (command::process(command_buffer, std::make_shared<default_command_context>()))
                    {
                        command_buffer[0] = 0;
                        g.quicksearch.enabled = false;
                    }
                });
                auto possible_commands = g_console_service->get_suggestions(command_buffer);

                ImGui::PopStyleVar();
            }
            ImGui::End();
        }
    }

    bool_command g_quicksearch("quicksearch", "Toggle quicksearch", "Toggles the quicksearch on or off", g.quicksearch.enabled);
}