#include "core/data/language_codes.hpp"
#include "core/data/region_codes.hpp"
#include "fiber_pool.hpp"
#include "pointers.hpp"
#include "script.hpp"
#include "services/matchmaking/matchmaking_service.hpp"
#include "util/session.hpp"
#include "views/view.hpp"

#include <network/Network.hpp>

namespace big
{
	static int selected_session_idx = -1;

	void view::session_browser()
	{
		static char name_buf[32];
		static char search[64];
		static char session_info[255];

		ImGui::Text(std::format("Total sessions found: {}", g_matchmaking_service->get_num_found_sessions()).data());

		ImGui::SetNextItemWidth(300.f);

		if (ImGui::ListBoxHeader("###sessions", {300, static_cast<float>(*g_pointers->m_resolution_y - 400 - 38 * 4)}))
		{
			if (g_matchmaking_service->get_num_found_sessions())
			{
				for (int i = 0; i < g_matchmaking_service->get_num_found_sessions(); i++)
				{
					auto& session = g_matchmaking_service->get_found_sessions()[i];

					if (!session.is_valid)
						continue;

					if (components::selectable(std::to_string(session.info.m_session_token), i == selected_session_idx))
					{
						selected_session_idx = i;
						g_pointers->m_encode_session_info(&session.info, session_info, 0x7D, nullptr);
					}

					if (ImGui::IsItemHovered())
					{
						ImGui::SetTooltip(std::format("Num Players: {}\nRegion: {}\nLanguage: {}\nHost: {}",
						    session.attributes.player_count,
						    regions[session.attributes.region].name,
						    languages[session.attributes.language].name,
						    session.info.m_net_player_data.m_gamer_handle.m_rockstar_id)
						                      .c_str());
					}
				}
			}
			else
			{
				ImGui::Text("NO_SESSIONS"_T.data());
			}

			ImGui::ListBoxFooter();
		}

		if (selected_session_idx != -1)
		{
			ImGui::SameLine();
			if (ImGui::BeginChild("###selected_session", {300, static_cast<float>(*g_pointers->m_resolution_y - 388 - 38 * 4)}, false, ImGuiWindowFlags_NoBackground))
			{
				auto& session = g_matchmaking_service->get_found_sessions()[selected_session_idx];

				ImGui::Text("SESSION_BROWSER_NUM_PLAYERS"_T.data(), session.attributes.player_count);
				ImGui::Text("SESSION_BROWSER_DISCRIMINATOR"_T.data(), session.attributes.discriminator);
				ImGui::Text("SESSION_BROWSER_REGION"_T.data(), regions[session.attributes.region].name);
				ImGui::Text("SESSION_BROWSER_LANGUAGE"_T.data(), languages[session.attributes.language].name);

				auto& data = session.info.m_net_player_data;
				ImGui::Text("SESSION_BROWSER_HOST_RID"_T.data(), data.m_gamer_handle.m_rockstar_id);

				components::button("COPY_SESSION_INFO"_T, [] {
					ImGui::SetClipboardText(session_info);
				});
				ImGui::SameLine();
				components::button("JOIN"_T, [session] {
					if (SCRIPT::GET_NUMBER_OF_THREADS_RUNNING_THE_SCRIPT_WITH_THIS_HASH(RAGE_JOAAT("maintransition")) != 0 || STREAMING::IS_PLAYER_SWITCH_IN_PROGRESS())
					{
						g_notification_service->push_error("JOIN_SESSION"_T.data(), "PLAYER_SWITCH_IN_PROGRESS"_T.data());
						return;
					}

					bool is_session_free_aim = session.attributes.discriminator & (1 << 17);
					bool is_local_free_aim   = PAD::GET_LOCAL_PLAYER_GAMEPAD_AIM_STATE() > 1;

					if (is_session_free_aim != is_local_free_aim)
						PLAYER::SET_PLAYER_TARGETING_MODE(is_session_free_aim ? 3 : 1);

					session::join_session(session.info);
				});
			}
			ImGui::EndChild();
		}

		if (ImGui::TreeNode("FILTERS"_T.data()))
		{
			ImGui::Checkbox("REGION"_T.data(), &g.session_browser.region_filter_enabled);

			if (ImGui::IsItemHovered())
				ImGui::SetTooltip("REGION_FILTER_DESC"_T.data());

			if (g.session_browser.region_filter_enabled)
			{
				ImGui::SameLine();

				if (ImGui::BeginCombo("###region_select", regions[g.session_browser.region_filter].name))
				{
					for (const auto& region : regions)
					{
						if (ImGui::Selectable(region.name, g.session_browser.region_filter == region.id))
						{
							g.session_browser.region_filter = region.id;
						}
					}
					ImGui::EndCombo();
				}
			}

			ImGui::Checkbox("LANGUAGE"_T.data(), &g.session_browser.language_filter_enabled);

			if (ImGui::IsItemHovered())
				ImGui::SetTooltip("LANGUAGE_FILTER_DESC"_T.data());

			if (g.session_browser.language_filter_enabled)
			{
				ImGui::SameLine();

				if (ImGui::BeginCombo("###language_select", languages[g.session_browser.language_filter].name))
				{
					for (const auto& language : languages)
					{
						if (ImGui::Selectable(language.name, g.session_browser.language_filter == language.id))
						{
							g.session_browser.language_filter = language.id;
						};
					}
					ImGui::EndCombo();
				}
			}

			ImGui::Checkbox("PLAYERS"_T.data(), &g.session_browser.player_count_filter_enabled);

			if (g.session_browser.player_count_filter_enabled)
			{
				ImGui::InputInt("MIN"_T.data(), &g.session_browser.player_count_filter_minimum);
				ImGui::InputInt("MAX"_T.data(), &g.session_browser.player_count_filter_maximum);
			}

			ImGui::Checkbox("POOL_TYPE"_T.data(), &g.session_browser.pool_filter_enabled);
			if (g.session_browser.pool_filter_enabled)
			{
				ImGui::SameLine();
				ImGui::Combo("###pooltype", &g.session_browser.pool_filter, "Normal\0Bad Sport");
			}

			ImGui::TreePop();
		}

		if (ImGui::TreeNode("SORTING"_T.data()))
		{
			ImGui::Combo("SORT_BY"_T.data(), &g.session_browser.sort_method, "Off\0Player Count");
			if (g.session_browser.sort_method != 0)
				ImGui::Combo("DIRECTION"_T.data(), &g.session_browser.sort_direction, "Ascending\0Descending");
			ImGui::TreePop();
		}

		if (ImGui::Checkbox("REPLACE_GAME_MATCHMAKING"_T.data(), &g.session_browser.replace_game_matchmaking))
			;

		if (ImGui::IsItemHovered())
			ImGui::SetTooltip("REPLACE_GAME_MATCHMAKING_DESC"_T.data());

		components::button("REFRESH"_T, [] {
			selected_session_idx = -1;

			if (!g_matchmaking_service->matchmake())
				g_notification_service->push_error("MATCHMAKING"_T.data(), "MATCHMAKING_FAIL"_T.data());
		});
	}
}
