#include "core/data/apartment_names.hpp"
#include "core/data/command_access_levels.hpp"
#include "core/data/region_codes.hpp"
#include "core/data/warehouse_names.hpp"
#include "fiber_pool.hpp"
#include "gta_util.hpp"
#include "hooking.hpp"
#include "util/notify.hpp"
#include "util/scripts.hpp"
#include "util/session.hpp"
#include "util/toxic.hpp"
#include "views/view.hpp"

#include <network/Network.hpp>
#include <script/globals/GPBD_FM_3.hpp>
#include <script/globals/GlobalPlayerBD.hpp>

//Percentage of window space
constexpr auto listbox_width  = 0.5f;
constexpr auto listbox_height = 0.2f;

namespace big
{
	static ImVec2 get_listbox_dimensions()
	{
		return {750 * listbox_width, ImGui::GetWindowHeight() * listbox_height};
	}

	void render_rid_joiner()
	{
		ImGui::BeginGroup();
		components::sub_title("Rid joiner");
		if (ImGui::ListBoxHeader("##ridjoiner", get_listbox_dimensions()))
		{
			static uint64_t rid = 0;
			static char username[20];
			static char base64[500]{};

			ImGui::PushItemWidth(ImGui::GetWindowWidth() * 0.5);

			ImGui::InputScalar("##inputrid", ImGuiDataType_U64, &rid);
			ImGui::SameLine();
			components::button("JOIN_BY_RID"_T, [] {
				session::join_by_rockstar_id(rid);
			});

			components::input_text_with_hint("##usernameinput", "INPUT_USERNAME"_T, username, sizeof(username));
			ImGui::SameLine();
			if (components::button("JOIN_BY_USERNAME"_T))
			{
				session::join_by_username(username);
			};

			components::input_text_with_hint("##sessioninfoinput", "SESSION_INFO"_T, base64, sizeof(base64));
			ImGui::SameLine();
			components::button("JOIN_SESSION_INFO"_T, [] {
				rage::rlSessionInfo info;
				g_pointers->m_gta.m_decode_session_info(&info, base64, nullptr);
				session::join_session(info);
			});

			components::button("COPY_SESSION_INFO"_T, [] {
				char buf[0x100]{};
				g_pointers->m_gta.m_encode_session_info(&gta_util::get_network()->m_game_session.m_rline_session.m_session_info, buf, 0xA9, nullptr);
				ImGui::SetClipboardText(buf);
			});

			ImGui::PopItemWidth();
			ImGui::ListBoxFooter();
		}
		ImGui::EndGroup();
	}

	void render_session_switcher()
	{
		ImGui::BeginGroup();
		components::sub_title("SESSION_SWITCHER"_T);
		if (ImGui::ListBoxHeader("###session_switch", get_listbox_dimensions()))
		{
			if (ImGui::BeginCombo("##regionswitcher", "Regions"))
			{
				for (const auto& region_type : regions)
				{
					components::selectable(region_type.name, *g_pointers->m_gta.m_region_code == region_type.id, [&region_type] {
						*g_pointers->m_gta.m_region_code = region_type.id;
					});
				}
				ImGui::EndCombo();
			}

			ImGui::Spacing();

			for (const auto& session_type : sessions)
			{
				components::selectable(session_type.name, false, [&session_type] {
					session::join_type(session_type.id);
				});
			}
			ImGui::EndListBox();
		}

		ImGui::EndGroup();
	}

	void render_misc()
	{
		ImGui::BeginGroup();

		components::sub_title("Misc");
		if (ImGui::ListBoxHeader("##miscsession", get_listbox_dimensions()))
		{
			ImGui::Checkbox("Join Sctv", &g.session.join_in_sctv_slots); //CHANGE TRANSLATION JOIN_IN_SCTV
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip("JOIN_IN_SCTV_DESC"_T.data());

			ImGui::Checkbox("PLAYER_MAGNET"_T.data(), &g.session.player_magnet_enabled);
			if (g.session.player_magnet_enabled)
			{
				ImGui::Text("PLAYER_COUNT"_T.data());
				ImGui::InputInt("##playercount", &g.session.player_magnet_count);
			}

			ImGui::BeginDisabled(!g_player_service->get_self()->is_host());

			ImGui::Checkbox("Lobby Lock", &g.session.lock_session);
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip("Blocks all players from joining. May not work on some modders.");

			ImGui::EndDisabled();

			components::script_patch_checkbox("REVEAL_OTR_PLAYERS"_T, &g.session.decloak_players);

			ImGui::ListBoxFooter();
		}

		ImGui::EndGroup();
	}

	void render_chat()
	{
		ImGui::BeginGroup();

		components::sub_title("Chat");
		if (ImGui::ListBoxHeader("##chat", get_listbox_dimensions()))
		{
			static char msg[256];
			ImGui::Checkbox("AUTO_KICK_CHAT_SPAMMERS"_T.data(), &g.session.kick_chat_spammers);
			ImGui::Checkbox("DISABLE_FILTER"_T.data(), &g.session.chat_force_clean);
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip("Your sent chat messages will not be censored to the receivers"); // TODO: add translation
			ImGui::Checkbox("LOG_CHAT_MSG"_T.data(), &g.session.log_chat_messages);
			ImGui::Checkbox("LOG_TXT_MSG"_T.data(), &g.session.log_text_messages);
			components::input_text_with_hint("##message", "Chat message", msg, sizeof(msg));

			ImGui::Checkbox("IS_TEAM"_T.data(), &g.session.is_team);
			ImGui::SameLine();
			components::button("SEND"_T, [] {
				if (const auto net_game_player = gta_util::get_network_player_mgr()->m_local_net_player; net_game_player)
				{
					if (g_hooking->get_original<hooks::send_chat_message>()(*g_pointers->m_gta.m_send_chat_ptr,
					        net_game_player->get_net_data(),
					        msg,
					        g.session.is_team))
						notify::draw_chat(msg, net_game_player->get_name(), g.session.is_team);
				}
			});

			ImGui::Separator();

			ImGui::Checkbox("CHAT_COMMANDS"_T.data(), &g.session.chat_commands);
			if (g.session.chat_commands)
			{
				components::small_text("DEFAULT_CMD_PERMISSIONS"_T.data());
				if (ImGui::BeginCombo("##defualtchatcommands", COMMAND_ACCESS_LEVELS[g.session.chat_command_default_access_level]))
				{
					for (const auto& [type, name] : COMMAND_ACCESS_LEVELS)
					{
						if (ImGui::Selectable(name, type == g.session.chat_command_default_access_level))
						{
							g.session.chat_command_default_access_level = type;
						}

						if (type == g.session.chat_command_default_access_level)
						{
							ImGui::SetItemDefaultFocus();
						}
					}

					ImGui::EndCombo();
				}
			}

			ImGui::ListBoxFooter();
		}

		ImGui::EndGroup();
	}

	void render_session_globals()
	{
		ImGui::BeginGroup();

		components::sub_title("Globals");
		if (ImGui::ListBoxHeader("##globals", get_listbox_dimensions()))
		{
			static int global_wanted_level = 0;

			ImGui::Checkbox("OFF_THE_RADAR"_T.data(), &g.session.off_radar_all);
			ImGui::Checkbox("NEVER_WANTED"_T.data(), &g.session.never_wanted_all);
			ImGui::Checkbox("SEMI_GODMODE"_T.data(), &g.session.semi_godmode_all);
			ImGui::Checkbox("EXPLOSION_KARMA"_T.data(), &g.session.explosion_karma);
			ImGui::Checkbox("DAMAGE_KARMA"_T.data(), &g.session.damage_karma);
			ImGui::Checkbox("DISABLE_PEDS"_T.data(), &g.session.disable_peds);
			ImGui::Checkbox("DISABLE_TRAFFIC"_T.data(), &g.session.disable_traffic);
			ImGui::Checkbox("FORCE_THUNDER"_T.data(), &g.session.force_thunder);

			components::small_text("WANTED_LVL"_T.data());
			ImGui::SetNextItemWidth(150);
			if (ImGui::SliderInt("##wantedlevel", &global_wanted_level, 0, 5))
			{
				scr_globals::globalplayer_bd.as<GlobalPlayerBD*>()->Entries[self::id].RemoteWantedLevelAmount = global_wanted_level;
			}

			ImGui::SameLine();
			if (ImGui::Checkbox("FORCE"_T.data(), &g.session.wanted_level_all))
			{
				scr_globals::globalplayer_bd.as<GlobalPlayerBD*>()->Entries[self::id].RemoteWantedLevelPlayer = __rdtsc() + 32;
				scr_globals::globalplayer_bd.as<GlobalPlayerBD*>()->Entries[self::id].RemoteWantedLevelAmount = global_wanted_level;
			}

			ImGui::ListBoxFooter();
		}

		ImGui::EndGroup();
	}

	void view::session()
	{
		render_rid_joiner();
		ImGui::SameLine();
		render_session_switcher();

		render_misc();
		ImGui::SameLine();
		render_chat();

		render_session_globals();

		ImGui::SameLine();

		ImGui::BeginGroup();
		components::sub_title("FORCE_HOST"_T);
		ImGui::Checkbox("FORCE_SESSION_HOST"_T.data(), &g.session.force_session_host);
		if (ImGui::IsItemHovered())
			ImGui::SetTooltip("FORCE_SESSION_HOST_DESC"_T.data());

		if (g.session.force_session_host)
		{
			ImGui::SameLine();
			ImGui::Checkbox("KICK_HOST_ON_JOIN"_T.data(), &g.session.kick_host_when_forcing_host);
		}

		if (ImGui::Checkbox("FORCE_SCRIPT_HOST"_T.data(), &g.session.force_script_host))
		{
			if (g.session.force_script_host)
				g_fiber_pool->queue_job([] {
					scripts::force_host(RAGE_JOAAT("freemode"));
					if (auto script = gta_util::find_script_thread(RAGE_JOAAT("freemode")); script && script->m_net_component)
						script->m_net_component->block_host_migration(true);

					scripts::force_host(RAGE_JOAAT("fmmc_launcher"));
					if (auto script = gta_util::find_script_thread(RAGE_JOAAT("fmmc_launcher")); script && script->m_net_component)
						script->m_net_component->block_host_migration(true);
				});
		}

		ImGui::Spacing();

		components::sub_title("Players");
		components::options_modal(
		    "Griefing",
		    [] {
			    components::command_button<"killall">({}, "KILL_ALL"_T);
			    ImGui::SameLine();
			    components::command_button<"explodeall">({}, "EXPLODE_ALL"_T);

			    ImGui::SameLine();

			    components::command_button<"beastall">({});
			    if (ImGui::IsItemHovered())
				    ImGui::SetTooltip("INCLUDING_YOU"_T.data());


			    components::command_button<"bringall">({});
			    ImGui::SameLine();
			    components::command_button<"giveweapsall">({});
			    ImGui::SameLine();
			    components::command_button<"remweapsall">({});

			    components::command_button<"ceokickall">({});
			    ImGui::SameLine();
			    components::command_button<"vehkickall">({});


			    components::command_button<"ragdollall">({}, "RAGDOLL_PLAYERS"_T);
			    ImGui::SameLine();
			    components::command_button<"intkickall">({}, "KICK_ALL_FROM_INTERIORS"_T);

			    components::command_button<"missionall">({});
			    ImGui::SameLine();
			    components::command_button<"errorall">({});

			    components::command_button<"ceoraidall">({});
			    ImGui::SameLine();
			    components::button("Trigger MC Raid", [] {
				    g_player_service->iterate([](auto& plyr) {
					    toxic::start_activity(plyr.second, eActivityType::BikerDefend);
				    });
			    });
			    ImGui::SameLine();
			    components::button("Trigger Bunker Raid", [] {
				    g_player_service->iterate([](auto& plyr) {
					    toxic::start_activity(plyr.second, eActivityType::GunrunningDefend);
				    });
			    });
		    },
		    false,
		    "Griefing");

		components::options_modal(
		    "Teleport",
		    [] {
			    if (ImGui::BeginCombo("##apartment", apartment_names[g.session.send_to_apartment_idx]))
			    {
				    for (int i = 1; i < apartment_names.size(); i++)
				    {
					    if (ImGui::Selectable(apartment_names[i], i == g.session.send_to_apartment_idx))
					    {
						    g.session.send_to_apartment_idx = i;
					    }

					    if (i == g.session.send_to_apartment_idx)
					    {
						    ImGui::SetItemDefaultFocus();
					    }
				    }

				    ImGui::EndCombo();
			    }

			    ImGui::SameLine();

			    components::command_button<"apartmenttpall">({(uint64_t)g.session.send_to_apartment_idx}, "TP_ALL_TO_APARTMENT"_T);

			    if (ImGui::BeginCombo("##warehouse", warehouse_names[g.session.send_to_warehouse_idx]))
			    {
				    for (int i = 1; i < warehouse_names.size(); i++)
				    {
					    if (ImGui::Selectable(warehouse_names[i], i == g.session.send_to_warehouse_idx))
					    {
						    g.session.send_to_warehouse_idx = i;
					    }

					    if (i == g.session.send_to_warehouse_idx)
					    {
						    ImGui::SetItemDefaultFocus();
					    }
				    }

				    ImGui::EndCombo();
			    }

			    ImGui::SameLine();

			    components::command_button<"warehousetpall">({(uint64_t)g.session.send_to_warehouse_idx}, "TP_ALL_TO_WAREHOUSE"_T);

			    components::button("TP_ALL_TO_DARTS"_T, [] {
				    g_player_service->iterate([](auto& plyr) {
					    toxic::start_activity(plyr.second, eActivityType::Darts);
				    });
			    });
			    ImGui::SameLine();
			    components::button("TP_ALL_TO_FLIGHT_SCHOOL"_T, [] {
				    g_player_service->iterate([](auto& plyr) {
					    toxic::start_activity(plyr.second, eActivityType::PilotSchool);
				    });
			    });
			    ImGui::SameLine();
			    components::button("TP_ALL_TO_MAP_CENTER"_T, [] {
				    g_player_service->iterate([](auto& plyr) {
					    toxic::start_activity(plyr.second, eActivityType::ArmWresling);
				    });
			    });

			    components::button("TP_ALL_TO_SKYDIVE"_T, [] {
				    g_player_service->iterate([](auto& plyr) {
					    toxic::start_activity(plyr.second, eActivityType::Skydive);
				    });
			    });
			    ImGui::SameLine();

			    components::command_button<"interiortpall">({81}, "TP_ALL_TO_MOC"_T);

			    ImGui::SameLine();
			    components::command_button<"interiortpall">({123}, "TP_ALL_TO_CASINO"_T);
			    ImGui::SameLine();
			    components::command_button<"interiortpall">({124}, "TP_ALL_TO_PENTHOUSE"_T);
			    ImGui::SameLine();
			    components::command_button<"interiortpall">({128}, "TP_ALL_TO_ARCADE"_T);

			    components::command_button<"interiortpall">({146}, "TP_ALL_TO_MUSIC_LOCKER"_T);
			    ImGui::SameLine();
			    components::command_button<"interiortpall">({148}, "TP_ALL_TO_RECORD_A_STUDIOS"_T);
			    ImGui::SameLine();
			    components::command_button<"interiortpall">({149}, "TP_ALL_TO_CUSTOM_AUTO_SHOP"_T);

			    components::command_button<"interiortpall">({155}, "TP_ALL_TO_AGENCY"_T);
			    ImGui::SameLine();
			    components::command_button<"interiortpall">({160}, "TP_ALL_TO_FREAKSHOP"_T);
			    ImGui::SameLine();
			    components::command_button<"interiortpall">({161}, "TP_ALL_TO_MULTI_FLOOR_GARAGE"_T);

			    components::command_button<"tutorialall">();
			    ImGui::SameLine();
			    components::command_button<"golfall">();
			    ImGui::SameLine();
			    components::command_button<"flightschoolall">();
			    ImGui::SameLine();
			    components::command_button<"dartsall">();

			    components::command_button<"badlandsall">();
			    ImGui::SameLine();
			    components::command_button<"spacemonkeyall">();
			    ImGui::SameLine();
			    components::command_button<"wizardall">();

			    components::command_button<"qub3dall">();
			    ImGui::SameLine();
			    components::command_button<"camhedzall">();
		    },
		    true,
		    "Teleport");

		ImGui::EndGroup();


		components::command_button<"sextall">({}, "Send Sexts");
		ImGui::SameLine();
		components::command_button<"fakebanall">({}, "Send Fake Ban Messages");

		components::small_text("WARP_TIME"_T.data());

		components::button("PLUS_1_MINUTE"_T, [] {
			toxic::warp_time_forward_all(60 * 1000);
		});
		ImGui::SameLine();
		components::button("PLUS_5_MINUTES"_T, [] {
			toxic::warp_time_forward_all(5 * 60 * 1000);
		});
		ImGui::SameLine();
		components::button("PLUS_48_MINUTES"_T, [] {
			toxic::warp_time_forward_all(48 * 60 * 1000);
		});
		ImGui::SameLine();
		components::button("PLUS_96_MINUTES"_T, [] {
			toxic::warp_time_forward_all(96 * 60 * 1000);
		});
		ImGui::SameLine();
		components::button("PLUS_200_MINUTES"_T, [] {
			toxic::warp_time_forward_all(200 * 60 * 1000);
		});
		ImGui::SameLine();
		components::button("STOP_TIME"_T, [] {
			toxic::set_time_all(INT_MAX - 3000);
		});
		if (ImGui::IsItemHovered())
			ImGui::SetTooltip("STOP_TIME_DESC"_T.data());

		components::sub_title("SCRIPT_HOST_FEATURES"_T);
		ImGui::Checkbox("DISABLE_CEO_MONEY"_T.data(), &g.session.block_ceo_money);
		if (ImGui::IsItemHovered())
			ImGui::SetTooltip("DISABLE_CEO_MONEY_DESC"_T.data());
		ImGui::SameLine();
		ImGui::Checkbox("RANDOMIZE_CEO_COLORS"_T.data(), &g.session.randomize_ceo_colors);
		ImGui::Checkbox("Block Jobs", &g.session.block_jobs);
		if (ImGui::IsItemHovered())
			ImGui::SetTooltip("Prevents remote players from starting jobs while in your session");
		ImGui::SameLine();
		components::script_patch_checkbox("Block Muggers", &g.session.block_muggers, "For the entire session");
		ImGui::SameLine();
		components::script_patch_checkbox("Block CEO Raids", &g.session.block_ceo_raids, "For the entire session");
	}
}
