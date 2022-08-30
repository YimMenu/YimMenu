#include "fiber_pool.hpp"
#include "natives.hpp"
#include "pointers.hpp"
#include "services/globals/globals_service.hpp"
#include "gta/script_thread.hpp"
#include "gta/script_handler.hpp"
#include "gta/tls_context.hpp"
#include "thread_pool.hpp"
#include "util/system.hpp"
#include "util/scripts.hpp"
#include "util/session.hpp"
#include "views/view.hpp"

namespace big
{
	void view::debug_scripts()
    {
        static GtaThread* selected_thread{};
        if (ImGui::ListBoxHeader("##scripts", ImVec2(250, 500)))
        {
            if (g->debug.sort_scripts)
            {
                std::map<std::string, GtaThread*> sorted_threads;
                for (auto thread : *g_pointers->m_script_threads)
                    if (thread && thread->m_context.m_thread_id && thread->m_handler)
                        sorted_threads[thread->m_name] = thread;
                for (auto thread : sorted_threads)
                    if (ImGui::Selectable(thread.second->m_name, thread.second == selected_thread))
                        selected_thread = thread.second;
            }
            else
            {
                for (auto thread : *g_pointers->m_script_threads)
                    if (thread && thread->m_context.m_thread_id && thread->m_handler)
                        if (ImGui::Selectable(thread->m_name, thread == selected_thread))
                            selected_thread = thread;
            }
            ImGui::ListBoxFooter();
        }
        ImGui::SameLine();
        ImGui::BeginGroup();
        ImGui::Checkbox("Sorted?", &g->debug.sort_scripts);
        ImGui::TextColored(ImVec4(0.5f, 0.5f, 0.5f, 1.0f), "Script Info:");
        if (selected_thread)
        {
            if (auto net_component = selected_thread->m_net_component)
                if (auto owner_list = net_component->m_owner_list)
                    if (auto owner = owner_list->m_owner)
                        ImGui::Text(fmt::format("Host: {}", owner->get_name()).c_str());
            if (ImGui::Button(fmt::format("Script Pointer: 0x{:X}", (DWORD64)selected_thread).c_str()))
                ImGui::SetClipboardText(fmt::format("0x{:X}", (DWORD64)selected_thread).c_str());
            if (ImGui::Button(fmt::format("m_stack: 0x{:X}", (DWORD64)selected_thread->m_stack).c_str()))
                ImGui::SetClipboardText(fmt::format("0x{:X}", (DWORD64)selected_thread->m_stack).c_str());
            ImGui::Text(fmt::format("m_exit_message: {}", (selected_thread->m_exit_message) ? selected_thread->m_exit_message : "").c_str());
            if (ImGui::Button(fmt::format("m_handler: 0x{:X}", (DWORD64)selected_thread->m_handler).c_str()))
                ImGui::SetClipboardText(fmt::format("0x{:X}", (DWORD64)selected_thread->m_handler).c_str());
            if (selected_thread->m_net_component != nullptr && ImGui::Button(fmt::format("m_net_component: 0x{:X}", (DWORD64)selected_thread->m_net_component).c_str()))
                ImGui::SetClipboardText(fmt::format("0x{:X}", (DWORD64)selected_thread->m_net_component).c_str());
            ImGui::Text(fmt::format("m_thread_id: {}", selected_thread->m_context.m_thread_id).c_str());
            ImGui::Text(fmt::format("m_instance_id: {}", selected_thread->m_instance_id).c_str());
            ImGui::Text(fmt::format("m_flag1: {:X}", selected_thread->m_flag1).c_str());
            ImGui::Text(fmt::format("m_safe_for_network_game: {}", selected_thread->m_safe_for_network_game).c_str());
            ImGui::Text(fmt::format("m_is_minigame_script: {}", selected_thread->m_is_minigame_script).c_str());
            ImGui::Text(fmt::format("m_can_be_paused: {}", selected_thread->m_can_be_paused).c_str());
            ImGui::Text(fmt::format("m_can_remove_blips_from_other_scripts: {}", selected_thread->m_can_remove_blips_from_other_scripts).c_str());
            components::button("Kill Script", []
            {
                SCRIPT::TERMINATE_THREAD(selected_thread->m_context.m_thread_id);
            });
        }

        ImGui::Separator();

        ImGui::Text("Start Script");

        static char script_name[64];
        static int args[] = { 45, 0, 9 };
        static int buffer_size = 3600;
        static int args_how = 3;

        ImGui::Checkbox("Args?", &g->debug.with_args);
        components::input_text_with_hint("###scipt_name", "Script Name", script_name, 64, ImGuiInputTextFlags_EnterReturnsTrue, []
            {
                if (const Hash hash = rage::joaat(script_name); hash)
                {
                    scripts::request_script(hash);
                    if (scripts::wait_till_loaded(hash))
                    {
                        if (g->debug.with_args)
                        {
                            scripts::start_script_with_args(hash, args, args_how, buffer_size);
                        }
                        else
                        {
                            scripts::start_script(hash, buffer_size);
                        }
                        scripts::wait_till_running(hash);
                    }
                }
            });
        if (g->debug.with_args)
        {
            ImGui::InputInt4("Args", args);
            ImGui::InputInt("Ammount of args", &args_how);
        }
        ImGui::InputInt("Buffer Size", &buffer_size);

    }
}