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
        if (ImGui::ListBoxHeader("##scripts", ImVec2(250, -ImGui::GetFrameHeight())))
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
                if (auto host = net_component->m_host)
                    if (auto host_net_player = host->m_net_game_player)
                        ImGui::Text("Host: %s", host_net_player->get_name());
            if (ImGui::Button(std::format("Script Pointer: 0x{:X}", (DWORD64)selected_thread).c_str()))
                ImGui::SetClipboardText(std::format("0x{:X}", (DWORD64)selected_thread).c_str());
            if (ImGui::Button(std::format("m_stack: 0x{:X}", (DWORD64)selected_thread->m_stack).c_str()))
                ImGui::SetClipboardText(std::format("0x{:X}", (DWORD64)selected_thread->m_stack).c_str());
            ImGui::Text("m_exit_message: %s", (selected_thread->m_exit_message) ? selected_thread->m_exit_message : "");
            if (ImGui::Button(std::format("m_handler: 0x{:X}", (DWORD64)selected_thread->m_handler).c_str()))
                ImGui::SetClipboardText(std::format("0x{:X}", (DWORD64)selected_thread->m_handler).c_str());
            if (selected_thread->m_net_component != nullptr && ImGui::Button(std::format("m_net_component: 0x{:X}", (DWORD64)selected_thread->m_net_component).c_str()))
                ImGui::SetClipboardText(std::format("0x{:X}", (DWORD64)selected_thread->m_net_component).c_str());
            ImGui::Text("m_thread_id: %u", selected_thread->m_context.m_thread_id);
            ImGui::Text("m_instance_id: %i", selected_thread->m_instance_id);
            ImGui::Text("m_flag1: %X", selected_thread->m_flag1);
            ImGui::Text("m_safe_for_network_game: %s", selected_thread->m_safe_for_network_game ? "Yes" : "No");
            ImGui::Text("m_is_minigame_script: %s", selected_thread->m_is_minigame_script ? "Yes" : "No");
            ImGui::Text("m_can_be_paused: %s", selected_thread->m_can_be_paused ? "Yes" : "No");
            ImGui::Text("m_can_remove_blips_from_other_scripts: %s", selected_thread->m_can_remove_blips_from_other_scripts ? "Yes" : "No");
            components::button("Kill Script", []
            {
                SCRIPT::TERMINATE_THREAD(selected_thread->m_context.m_thread_id);
            });
        }

        ImGui::Separator();

        ImGui::Text("Start Script");

        static char script_name[64];
        static int buffer_size = 3600;
        static int* args;
		static int arg_count = 3;
		static int previous_arg_count;

        ImGui::Checkbox("With args", &g->debug.with_args);
        components::input_text_with_hint("###scipt_name", "Script Name", script_name, sizeof(script_name), ImGuiInputTextFlags_EnterReturnsTrue, []
            {
                if (const Hash hash = rage::joaat(script_name); hash)
                {
                    scripts::request_script(hash);
                    if (scripts::wait_till_loaded(hash))
                    {
                        if (g->debug.with_args)
                        {
                            scripts::start_script_with_args(hash, args, arg_count, buffer_size);
                        }
                        else
                        {
                            scripts::start_script(hash, buffer_size);
                        }
                        scripts::wait_till_running(hash);
                    }
                }
            });
        ImGui::InputInt("Buffer Size", &buffer_size);

        if(g->debug.with_args)
        {
		    ImGui::Text("Script Argument Count:");
		    ImGui::InputInt("###script_arg_count", &arg_count);
		    if (arg_count > 32)
		    	arg_count = 32;
		    else if (arg_count < 1)
		    	arg_count = 1;

		    if (arg_count != previous_arg_count)
		    {
		    	int* temp_args = new int[arg_count]{ 0 };
		    	memcpy(temp_args, args, sizeof(int) * std::min(arg_count, previous_arg_count));

		    	delete[] args;
		    	args = temp_args;

		    	previous_arg_count = arg_count;
		    }

		    ImGui::Separator();

		    for (int i = 0; i < arg_count; i++)
		    {
		    	ImGui::PushID(i);
		    	ImGui::Text("Arg[%d]", i);
		    	ImGui::SameLine();
		    	ImGui::InputScalar("###input_dynamic_arg", ImGuiDataType_S32, &args[i]);

		    	ImGui::PopID();
		    }
        }

    }
}