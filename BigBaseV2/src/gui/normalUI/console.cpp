#include "views/view.hpp"
#include "gta/array.hpp"
#include "CPedFactory.hpp"
#include "CNetworkPlayerMgr.hpp"
#include "gta/script_thread.hpp"
#include "gta/script_handler.hpp"
#include "gta/tls_context.hpp"
#include "pointers.hpp"
#include "natives.hpp"
#include "fiber_pool.hpp"
#include "util/scripts.hpp"
#include "util/session.hpp"
#include "script_global.hpp"
#include "core/data/explosion_types.hpp"

namespace big
{
    void view::debug_c()
    {
        if (g->window.debug)
        {
            if (ImGui::Begin("Debug"))
            {
                if (ImGui::CollapsingHeader("Script Monitor"))
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
                        if (ImGui::Button("Kill Script"))
                        {
                            QUEUE_JOB_BEGIN_CLAUSE()
                            {
                                SCRIPT::TERMINATE_THREAD(selected_thread->m_context.m_thread_id);
                            } QUEUE_JOB_END_CLAUSE
                        }
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
                                    } else 
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
                    
                    ImGui::Separator();
                }
				
                if (ImGui::CollapsingHeader("Custom Settings"))
                {
                    ImGui::Checkbox("Fast Join", &g->tunables.fast_join);
                    ImGui::SameLine();
                    ImGui::Checkbox("Phone Anim", &g->tunables.phone_anim);
                    ImGui::SameLine();
                    ImGui::Checkbox("Jump Ragdoll", &g->self.allow_ragdoll);
                    ImGui::SameLine();
                    ImGui::Checkbox("Fly Thru Windscreen", &g->tunables.fly_thru_windscreen);
                    ImGui::SameLine();
                    ImGui::Checkbox("Ambiant Ufos", &g->tunables.ambiant_ufos);
                    
                    ImGui::Checkbox("Ambiant Blimps", &g->tunables.ambiant_blimp);
                    ImGui::SameLine();
                    ImGui::Checkbox("Cable Cars", &g->tunables.cable_cars);
                    ImGui::SameLine();
                    ImGui::Checkbox("Always Controll", &g->tunables.always_controll);
                    ImGui::SameLine();
                    ImGui::Checkbox("Utility Wheel", &g->pie_menu.enabled);

                    ImGui::Checkbox("Vehicle Flares", &g->vehicle.flares);
                    ImGui::SameLine();
                    ImGui::Checkbox("Vehicle Chaff", &g->vehicle.chaff);
                    ImGui::SameLine();
                    ImGui::Checkbox("Vehicle Bombs", &g->vehicle.bombs);
                    ImGui::Text("Bomb Type:");
                    components::input_text_with_hint("###bomb_model", "", g->vehicle.bomb_type, 64);
                    //ImGui::Combo("###bomb_model", &g->vehicle.bomb_type, *weapon_types);

                    ImGui::Separator();

                    if (ImGui::Checkbox("No loading", &g->tunables.no_loading)) 
                    {
                        QUEUE_JOB_BEGIN_CLAUSE()
                        {
                            SCRIPT::SET_NO_LOADING_SCREEN(g->tunables.no_loading);
                            if (CAM::IS_SCREEN_FADED_OUT()) {
                                CAM::DO_SCREEN_FADE_IN(100);
                            }
                        } QUEUE_JOB_END_CLAUSE
                    }
                    
                    components::button("SP Map", [] {
                        DLC::ON_ENTER_SP();
                    });

                    ImGui::SameLine();

                    components::button("MP Map", [] {
                        DLC::ON_ENTER_MP();
                    });

                    ImGui::SameLine();

                    static bool prologue_map = false;
                    if (ImGui::Checkbox("Prologue Map", &prologue_map))
                    {
                        QUEUE_JOB_BEGIN_CLAUSE()
                        {
                            HUD::SET_MINIMAP_IN_PROLOGUE(prologue_map);
                        } QUEUE_JOB_END_CLAUSE
                    }
					
					ImGui::SameLine();

                    components::button("Speed limit", [] {
                        ENTITY::SET_ENTITY_MAX_SPEED(self::veh, 2000);
                        VEHICLE::SET_VEHICLE_MAX_SPEED_(self::veh, 2000);
                    });
                    /*static char phone_types{"franklin", "Traver", "Broken Michael"};
                    if (ImGui::Combo("Phone type", g->tunables.phone_type, &phone_types)) {
                        QUEUE_JOB_BEGIN_CLAUSE() {

                        } QUEUE_JOB_END_CLAUSE
                    }*/

                    static char message[255] = "";
                    components::input_text_with_hint("Message", "", message, sizeof(message), ImGuiInputTextFlags_EnterReturnsTrue, []
                    {
                        LOG(INFO) << g_pointers->m_send_chat_message(*g_pointers->m_send_chat_ptr + 0x78, (__int64)g_local_player->m_player_info + 0x88, message, false) << message;
                    });
                }

                ImGui::End();
            }
        }
    }
}
