#include "core/data/language_codes.hpp"
#include "core/data/region_codes.hpp"
#include "pointers.hpp"
#include "services/matchmaking/matchmaking_service.hpp"
#include "services/player_database/player_database_service.hpp"
#include "util/session.hpp"
#include "views/view.hpp"

namespace big
{
	static int selected_session_idx = -1;

	void view::session_browser()
	{
		static char name_buf[32];
		static char search[64];
		static char session_info[0x100]{};
		ImGui::Text(std::format("{}: {}", "VIEW_SESSION_TOTAL_SESSIONS_FOUND"_T.data(), g_matchmaking_service->get_num_found_sessions())
		                .c_str());

		ImGui::SetNextItemWidth(300.f);

		if (ImGui::BeginListBox("###sessions", {300, static_cast<float>(*g_pointers->m_gta.m_resolution_y - 400 - 38 * 4)}))
		{
			if (g_matchmaking_service->get_num_found_sessions())
			{
				for (int i = 0; i < g_matchmaking_service->get_num_found_sessions(); i++)
				{
					auto& session = g_matchmaking_service->get_found_sessions()[i];

					if (!session.is_valid)
						continue;

					std::string session_str;
					if (session.attributes.multiplex_count > 1)
						session_str = std::format("{:X} (x{})", session.info.m_session_token, session.attributes.multiplex_count);
					else
						session_str = std::format("{:X}", session.info.m_session_token);

					auto host_rid = session.info.m_net_player_data.m_gamer_handle.m_rockstar_id;
					auto player   = g_player_database_service->get_player_by_rockstar_id(host_rid);

					if ((g.session_browser.exclude_modder_sessions && player && player->block_join)
					    || (g.session_browser.filter_multiplexed_sessions && session.attributes.multiplex_count > 1))
						continue;

					if (components::selectable(session_str, i == selected_session_idx))
					{
						selected_session_idx = i;
						g_pointers->m_gta.m_encode_session_info(&session.info, session_info, 0xA9, nullptr);
					}

					if (ImGui::IsItemHovered())
					{
						auto tool_tip = std::format("{}: {}\n{}: {}\n{}: {}\n{}: {}\n{}: {:X}",
						    "SESSION_BROWSER_NUM_PLAYERS"_T,
						    session.attributes.player_count,
						    "REGION"_T,
						    regions[session.attributes.region].name,
						    "LANGUAGE"_T,
						    languages.at((eGameLanguage)session.attributes.language),
						    "SESSION_BROWSER_HOST_RID"_T,
						    session.info.m_net_player_data.m_gamer_handle.m_rockstar_id, // TODO: this is not accurate
						    "SESSION_BROWSER_DISCRIMINATOR"_T,
						    session.attributes.discriminator);
						ImGui::SetTooltip(tool_tip.c_str());
					}
				}
			}
			else
			{
				ImGui::Text("NO_SESSIONS"_T.data());
			}

			ImGui::EndListBox();
		}

		if (selected_session_idx != -1)
		{
			ImGui::SameLine();
			if (ImGui::BeginChild("###selected_session", {300, static_cast<float>(*g_pointers->m_gta.m_resolution_y - 388 - 38 * 4)}, false, ImGuiWindowFlags_NoBackground))
			{
				auto& session = g_matchmaking_service->get_found_sessions()[selected_session_idx];

				ImGui::Text(std::format("{}: {}", "SESSION_BROWSER_NUM_PLAYERS"_T, session.attributes.player_count).c_str());
				ImGui::Text(
				    std::format("{}: 0x{:X}", "SESSION_BROWSER_DISCRIMINATOR"_T, session.attributes.discriminator).c_str());
				ImGui::Text(std::format("{}: {}", "REGION"_T, regions[session.attributes.region].name).c_str());
				ImGui::Text(
				    std::format("{}: {}", "LANGUAGE"_T, languages.at((eGameLanguage)session.attributes.language)).c_str());

				auto& data = session.info.m_net_player_data;
				ImGui::Text(std::format("{}: {}", "SESSION_BROWSER_HOST_RID"_T, data.m_gamer_handle.m_rockstar_id).c_str());

				components::button("COPY_SESSION_INFO"_T, [] {
					ImGui::SetClipboardText(session_info);
				});
				//ImGui::SameLine();
				components::button("JOIN"_T, [session] {
					if (SCRIPT::GET_NUMBER_OF_THREADS_RUNNING_THE_SCRIPT_WITH_THIS_HASH("maintransition"_J) != 0 || STREAMING::IS_PLAYER_SWITCH_IN_PROGRESS())
					{
						g_notification_service.push_error("JOIN_SESSION"_T.data(), "PLAYER_SWITCH_IN_PROGRESS"_T.data());
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

				if (ImGui::BeginCombo("###language_select", languages.at(g.session_browser.language_filter).data()))
				{
					for (const auto& [id, language] : languages)
					{
						if (ImGui::Selectable(language.data(), g.session_browser.language_filter == id))
						{
							g.session_browser.language_filter = id;
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
				static const std::string pool_filter_options =
				    std::string("NORMAL"_T.data()) + '\0' + std::string("BAD_SPORT"_T.data());
				ImGui::Combo("###pooltype", &g.session_browser.pool_filter, pool_filter_options.c_str());
			}

			ImGui::Checkbox("FILTER_MULTIPLEXED_SESSIONS"_T.data(), &g.session_browser.filter_multiplexed_sessions);
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip("FILTER_MULTIPLEXED_SESSIONS_DESC"_T.data());

			ImGui::Checkbox("EXCLUDE_MODDER_SESSIONS"_T.data(), &g.session_browser.exclude_modder_sessions);
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip("EXCLUDE_MODDER_SESSIONS_DESC"_T.data());

			ImGui::TreePop();
		}

		if (ImGui::TreeNode("SORTING"_T.data()))
		{
			static const std::string sort_by_options = std::string("OFF"_T.data()) + '\0' + std::string("PLAYER_COUNT"_T.data());
			static const std::string sort_direction_options =
			    std::string("ASCENDING"_T.data()) + '\0' + std::string("DESCENDING"_T.data());
			ImGui::Combo("SORT_BY"_T.data(), &g.session_browser.sort_method, sort_by_options.c_str());
			if (g.session_browser.sort_method != 0)
				ImGui::Combo("DIRECTION"_T.data(), &g.session_browser.sort_direction, sort_direction_options.c_str());
			ImGui::TreePop();
		}

		ImGui::Checkbox("REPLACE_GAME_MATCHMAKING"_T.data(), &g.session_browser.replace_game_matchmaking);
		if (ImGui::IsItemHovered())
			ImGui::SetTooltip("REPLACE_GAME_MATCHMAKING_DESC"_T.data());

		components::button("REFRESH"_T, [] {
			selected_session_idx = -1;

			if (!g_matchmaking_service->matchmake())
				g_notification_service.push_error("MATCHMAKING"_T.data(), "MATCHMAKING_FAIL"_T.data());
		});
	}
}
