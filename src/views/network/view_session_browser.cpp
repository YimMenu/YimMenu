#include "views/view.hpp"
#include "fiber_pool.hpp"
#include "pointers.hpp"
#include "script.hpp"
#include <network/Network.hpp>
#include "util/session.hpp"
#include "core/data/region_codes.hpp"
#include "core/data/language_codes.hpp"

namespace
{
	using session = decltype(big::g->session_browser.found_sessions[0]);
	using session_ptr = decltype(&big::g->session_browser.found_sessions[0]);
}

namespace big
{
	static int selected_session_idx = -1;

	void view::session_browser()
	{
		static char name_buf[32];
		static char search[64];

		ImGui::SetNextItemWidth(300.f);

		if (ImGui::ListBoxHeader("###sessions", { 300, static_cast<float>(*g_pointers->m_resolution_y - 400 - 38 * 4) }))
		{
			if (g->session_browser.num_sessions_found)
			{
				for (int i = 0; i < g->session_browser.num_sessions_found; i++)
				{
					if (!g->session_browser.found_sessions[i].is_valid)
						continue;

					if (components::selectable(std::to_string(g->session_browser.found_sessions[i].info.m_session_token), i == selected_session_idx))
					{
						selected_session_idx = i;
					}
				}
			}
			else
			{
				ImGui::Text("No sessions");
			}

			ImGui::ListBoxFooter();
		}

		if (selected_session_idx != -1)
		{
			ImGui::SameLine();
			if (ImGui::BeginChild("###selected_session", { 300, static_cast<float>(*g_pointers->m_resolution_y - 388 - 38 * 4) }, false, ImGuiWindowFlags_NoBackground))
			{
				ImGui::Text("Num Players: %d", g->session_browser.found_sessions[selected_session_idx].attributes.player_count);
				ImGui::Text("Discriminator: 0x%X", g->session_browser.found_sessions[selected_session_idx].attributes.discriminator);
				ImGui::Text("Region: %s", regions[g->session_browser.found_sessions[selected_session_idx].attributes.region].name);
				ImGui::Text("Language: %s", languages[g->session_browser.found_sessions[selected_session_idx].attributes.language].name);

				auto& data = g->session_browser.found_sessions[selected_session_idx].info.m_net_player_data;
				ImGui::Text("Host Rockstar ID: %d", data.m_gamer_handle.m_rockstar_id);

				components::button("Join", []
				{
					if (SCRIPT::GET_NUMBER_OF_THREADS_RUNNING_THE_SCRIPT_WITH_THIS_HASH(RAGE_JOAAT("maintransition")) != 0 ||
						STREAMING::IS_PLAYER_SWITCH_IN_PROGRESS())
					{
						g_notification_service->push_error("RID Joiner", "Player switch in progress, wait a bit.");
						return;
					}

					bool is_session_free_aim = g->session_browser.found_sessions[selected_session_idx].attributes.discriminator & (1 << 17);
					bool is_local_free_aim = PAD::GET_LOCAL_PLAYER_GAMEPAD_AIM_STATE() > 1;

					if (is_session_free_aim != is_local_free_aim)
						PLAYER::SET_PLAYER_TARGETING_MODE(is_session_free_aim ? 3 : 1);

					session::join_session(g->session_browser.found_sessions[selected_session_idx].info);
				});
			}
			ImGui::EndChild();
		}

		if (ImGui::TreeNode("Filters"))
		{
			ImGui::Checkbox("Region", &g->session_browser.region_filter_enabled);

			if (ImGui::IsItemHovered())
				ImGui::SetTooltip("It is highly recommended to keep this filter enabled");

			if (g->session_browser.region_filter_enabled)
			{
				ImGui::SameLine();

				if (ImGui::BeginCombo("###region_select", regions[g->session_browser.region_filter].name))
				{
					for (const auto& region : regions)
					{
						if (ImGui::Selectable(region.name, g->session_browser.region_filter == region.id))
						{
							g->session_browser.region_filter = region.id;
						}
					}
					ImGui::EndCombo();
				}

			}

			ImGui::Checkbox("Language", &g->session_browser.language_filter_enabled);

			if (ImGui::IsItemHovered())
				ImGui::SetTooltip("Setting a correct region filter for the language will help tremendously");

			if (g->session_browser.language_filter_enabled)
			{
				ImGui::SameLine();

				if (ImGui::BeginCombo("###language_select", languages[g->session_browser.language_filter].name))
				{
					for (const auto& language : languages)
					{
						if (ImGui::Selectable(language.name, g->session_browser.language_filter == language.id))
						{
							g->session_browser.language_filter = language.id;
						};
					}
					ImGui::EndCombo();
				}
			}

			ImGui::Checkbox("Players", &g->session_browser.player_count_filter_enabled);

			if (g->session_browser.player_count_filter_enabled)
			{
				ImGui::InputInt("Minimum", &g->session_browser.player_count_filter_minimum);
				ImGui::InputInt("Maximum", &g->session_browser.player_count_filter_maximum);
			}

			ImGui::TreePop();
		}

		if (ImGui::TreeNode("Sorting"))
		{
			ImGui::Combo("Sort By", &g->session_browser.sort_method, "Off\0Player Count");
			if (g->session_browser.sort_method != 0)
				ImGui::Combo("Direction", &g->session_browser.sort_direction, "Ascending\0Descending");
			ImGui::TreePop();
		}

		components::button("Refresh", []
		{
			for (auto& session : g->session_browser.found_sessions)
			{
				session.is_valid = true;
			}

			if (g->session_browser.active)
				return;

			selected_session_idx = -1;

			NetworkGameFilterMatchmakingComponent component{};
			strcpy(component.m_filter_name, "Group");
			component.m_num_parameters = 0;

			if (g->session_browser.region_filter_enabled)
			{
				component.SetParameter("MMATTR_REGION", 0, g->session_browser.region_filter);
			}

			int state;
			static rage::rlSessionInfo result_sessions[MAX_SESSIONS_TO_FIND];

			g->session_browser.active = true;
			if (g_pointers->m_start_matchmaking_find_sessions(0, 1, &component, MAX_SESSIONS_TO_FIND, result_sessions, &g->session_browser.num_sessions_found, &state))
			{
				while (state == 1)
					script::get_current()->yield();

				if (state != 3)
				{
					g_notification_service->push_error("Session Browser", "Matchmaking failed");
				}
				else
				{
					for (int i = 0; i < g->session_browser.num_sessions_found; i++)
					{
						g->session_browser.found_sessions[i].info = result_sessions[i];

						if (g->session_browser.language_filter_enabled && g->session_browser.found_sessions[i].attributes.language != g->session_browser.language_filter)
							g->session_browser.found_sessions[i].is_valid = false;

						if (g->session_browser.player_count_filter_enabled && (g->session_browser.found_sessions[i].attributes.player_count < g->session_browser.player_count_filter_minimum ||
							g->session_browser.found_sessions[i].attributes.player_count > g->session_browser.player_count_filter_maximum))
						{
							g->session_browser.found_sessions[i].is_valid = false;
						}
					}

					if (g->session_browser.sort_method != 0)
					{
						std::qsort(g->session_browser.found_sessions, g->session_browser.num_sessions_found, sizeof(::session), [](const void* a1, const void* a2) -> int
						{
							std::strong_ordering result;

							if (g->session_browser.sort_method == 1)
							{
								result = (((::session_ptr)(a1))->attributes.player_count <=> ((::session_ptr)(a2))->attributes.player_count);
							}

							if (result == 0)
								return 0;

							if (result > 0)
								return g->session_browser.sort_direction ? -1 : 1;

							if (result < 0)
								return g->session_browser.sort_direction ? 1 : -1;

							
							std::unreachable();
						});
					}
				}
			}
			else
			{
				g_notification_service->push_error("Session Browser", "Matchmaking could not begin");
			}

			g->session_browser.active = false;
		});
	}
}
