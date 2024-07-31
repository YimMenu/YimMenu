#include "core/data/all_script_names.hpp"
#include "core/data/stack_sizes.hpp"
#include "fiber_pool.hpp"
#include "gui/components/components.hpp"
#include "natives.hpp"
#include "script.hpp"
#include "util/scripts.hpp"
#include "view_debug.hpp"

static rage::scrThread* selected_thread;

static int selected_stack_size             = 128;
static int free_stacks                     = -1;
static const char* selected_stack_size_str = "MULTIPLAYER_MISSION";
static const char* selected_script         = "";

static std::chrono::high_resolution_clock::time_point last_stack_update_time{};

namespace
{
	static void update_free_stacks_count()
	{
		free_stacks = MISC::GET_NUMBER_OF_FREE_STACKS_OF_THIS_SIZE(selected_stack_size);
	}
}

namespace big
{
	void debug::threads()
	{
		if (ImGui::BeginTabItem("VIEW_DEBUG_THREADS"_T.data()))
		{
			if (!g_pointers->m_gta.m_script_threads)
			{
				selected_thread = nullptr;
				ImGui::EndTabItem();
				return;
			}

			ImGui::SeparatorText("VIEW_DEBUG_THREADS"_T.data());

			if (ImGui::BeginCombo("VIEW_DEBUG_THREADS_THREAD"_T.data(), selected_thread ? selected_thread->m_name : "VIEW_DEBUG_THREADS_SELECTED_NONE"_T.data()))
			{
				for (auto script : *g_pointers->m_gta.m_script_threads)
				{
					if (script)
					{
						if (script->m_context.m_state != rage::eThreadState::killed && script->m_context.m_stack_size == 0)
							continue;

						ImGui::PushID(script->m_context.m_thread_id);

						if (script->m_context.m_state == rage::eThreadState::killed)
							ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 0.1f, 0.1f, 1.f));

						if (ImGui::Selectable(script->m_name, selected_thread == script))
						{
							selected_thread = script;
						}

						if (selected_thread == script)
							ImGui::SetItemDefaultFocus();

						if (script->m_context.m_state == rage::eThreadState::killed)
							ImGui::PopStyleColor();

						ImGui::PopID();
					}
				}
				ImGui::EndCombo();
			}

			if (selected_thread)
			{
				static const std::string thread_states = std::string("VIEW_DEBUG_THREADS_STATE_0"_T.data()) + '\0'
				    + std::string("VIEW_DEBUG_THREADS_STATE_1"_T.data()) + '\0'
				    + std::string("VIEW_DEBUG_THREADS_STATE_2"_T.data()) + '\0'
				    + std::string("VIEW_DEBUG_THREADS_STATE_3"_T.data()) + '\0'
				    + std::string("VIEW_DEBUG_THREADS_STATE_4"_T.data()) + '\0';
				ImGui::Combo("VIEW_DEBUG_THREADS_STATE"_T.data(), (int*)&selected_thread->m_context.m_state, thread_states.c_str());

				auto net_handler = reinterpret_cast<CGameScriptHandlerNetComponent*>(selected_thread->m_net_component);

				if (net_handler)
				{
					auto host = net_handler->get_host();
					if (host)
					{
						ImGui::Text(std::format("{}: {}", "VIEW_DEBUG_THREADS_SCRIPT_HOST"_T, host->get_name()).c_str());

						if (!net_handler->is_local_player_host())
						{
							ImGui::SameLine();
							if (ImGui::SmallButton("VIEW_DEBUG_THREADS_TAKE_CONTROL"_T.data()))
							{
								g_fiber_pool->queue_job([net_handler] {
									net_handler->send_host_migration_event(g_player_service->get_self()->get_net_game_player());				
								});
							}
						}
					}
				}

				ImGui::Text(std::format("{}: 0x{:X}", "VIEW_DEBUG_THREADS_SCRIPT_POINTER"_T, (DWORD64)selected_thread).c_str());
				ImGui::SameLine();
				if (ImGui::SmallButton(std::format("{}##script_ptr", "COPY"_T).c_str()))
					ImGui::SetClipboardText(std::format("0x{:X}", (DWORD64)selected_thread).c_str());
				ImGui::Text(std::format("{}: 0x{:X}", "VIEW_DEBUG_THREADS_STACK_POINTER"_T, (DWORD64)selected_thread->m_stack).c_str());
				ImGui::SameLine();
				if (ImGui::SmallButton(std::format("{}##stack_ptr", "COPY"_T).c_str()))
					ImGui::SetClipboardText(std::format("0x{:X}", (DWORD64)selected_thread->m_stack).c_str());
				ImGui::Text(std::format("{}: {}", "VIEW_DEBUG_THREADS_INTERNAL_STACK_POINTER"_T, selected_thread->m_context.m_stack_pointer).c_str());
				ImGui::Text(std::format("{}: 0x{:X}", "VIEW_DEBUG_THREADS_INSTRUCTION_POINTER"_T, selected_thread->m_context.m_instruction_pointer).c_str());
				ImGui::Text(std::format("{}: {}", "VIEW_DEBUG_THREADS_STACK_SIZE"_T, selected_thread->m_context.m_stack_size).c_str());

				if (selected_thread->m_context.m_state == rage::eThreadState::killed)
				{
					ImGui::Text(std::format("{}: {}","VIEW_DEBUG_THREADS_EXIT_REASON"_T, selected_thread->m_exit_message).c_str());
				}
				else
				{
					if (ImGui::Button("VIEW_DEBUG_THREADS_KILL"_T.data()))
					{
						if (selected_thread->m_context.m_stack_size != 0)
							selected_thread->kill();

						selected_thread->m_context.m_state = rage::eThreadState::killed;
					}
				}
			}

			ImGui::SeparatorText("VIEW_DEBUG_THREADS_NEW"_T.data());

			static std::string search_script = "";

			components::input_text_with_hint("VIEW_DEBUG_THREADS_SCRIPT"_T, "SEARCH"_T, search_script, ImGuiInputTextFlags_None);

			if (ImGui::BeginCombo("VIEW_DEBUG_THREADS_STACK_SIZE"_T.data(), selected_stack_size_str))
			{
				for (auto& p : stack_sizes)
				{
					if (ImGui::Selectable(std::format("{} ({})", p.first, p.second).data(), selected_stack_size == p.second))
					{
						selected_stack_size_str = p.first;
						selected_stack_size     = p.second;

						g_fiber_pool->queue_job([] {
							update_free_stacks_count();
						});
					}

					if (p.second == selected_stack_size)
						ImGui::SetItemDefaultFocus();
				}
				ImGui::EndCombo();
			}

			if (ImGui::BeginListBox("##scripts"))
			{
				std::string lower_search = search_script;
				std::transform(lower_search.begin(), lower_search.end(), lower_search.begin(), ::tolower);

				for (auto& script : all_script_names)
				{
					std::string lower_script = script;
					std::transform(lower_script.begin(), lower_script.end(), lower_script.begin(), ::tolower);

					if (lower_script.find(lower_search) != std::string::npos)
					{
						if (ImGui::Selectable(script, selected_script == script))
						{
							selected_script = script;
							search_script   = script;
						}
					}
				}
				ImGui::EndListBox();
			}

			ImGui::Text(std::format("{}: {}", "VIEW_DEBUG_THREADS_FREE_STACKS"_T, free_stacks).c_str());

			components::button("SETTINGS_NOTIFY_GTA_THREADS_START"_T, [] {
				auto hash = rage::joaat(selected_script);

				if (!SCRIPT::DOES_SCRIPT_WITH_NAME_HASH_EXIST(hash))
				{
					return;
				}

				if (MISC::GET_NUMBER_OF_FREE_STACKS_OF_THIS_SIZE(selected_stack_size) == 0)
				{
					g_notification_service.push_warning("VIEW_DEBUG_THREADS"_T.data(), "VIEW_DEBUG_THREADS_NO_FREE_STACKS"_T.data());
				}

				while (!SCRIPT::HAS_SCRIPT_WITH_NAME_HASH_LOADED(hash))
				{
					SCRIPT::REQUEST_SCRIPT_WITH_NAME_HASH(hash);
					script::get_current()->yield();
				}

				SYSTEM::START_NEW_SCRIPT_WITH_NAME_HASH(hash, selected_stack_size);

				SCRIPT::SET_SCRIPT_WITH_NAME_HASH_AS_NO_LONGER_NEEDED(hash);

				update_free_stacks_count();
			});

			ImGui::SameLine();

			components::button("VIEW_DEBUG_THREADS_START_WITH_LAUNCHER"_T, [] {
				auto hash = rage::joaat(selected_script);
				auto idx  = scripts::launcher_index_from_hash(hash);

				if (idx == -1)
				{
					g_notification_service.push_warning("VIEW_DEBUG_THREADS"_T.data(), "VIEW_DEBUG_THREADS_FAILED_WITH_LAUNCHER"_T.data());
					return;
				}

				scripts::start_launcher_script(hash);
			});

			if (*g_pointers->m_gta.m_game_state != eGameState::Invalid && std::chrono::high_resolution_clock::now() - last_stack_update_time > 100ms)
			{
				last_stack_update_time = std::chrono::high_resolution_clock::now();
				g_fiber_pool->queue_job([] {
					update_free_stacks_count();
				});
			}

			ImGui::EndTabItem();
		}
	}
}
