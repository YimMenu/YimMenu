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

namespace big
{
	void view::session()
	{
		static uint64_t rid = 0;
		ImGui::InputScalar("INPUT_RID"_T.data(), ImGuiDataType_U64, &rid);
		components::button("JOIN_BY_RID"_T, [] {
			session::join_by_rockstar_id(rid);
		});

		static char username[20];
		components::input_text("INPUT_USERNAME"_T, username, sizeof(username));
		if (components::button("JOIN_BY_USERNAME"_T))
		{
			session::join_by_username(username);
		};

		static char base64[500]{};
		components::input_text("SESSION_INFO"_T, base64, sizeof(base64));
		components::button("JOIN_SESSION_INFO"_T, [] {
			rage::rlSessionInfo info;
			g_pointers->m_decode_session_info(&info, base64, nullptr);
			session::join_session(info);
		});
		ImGui::SameLine();
		components::button("COPY_SESSION_INFO"_T, [] {
			char buf[0x100]{};
			g_pointers->m_encode_session_info(&gta_util::get_network()->m_game_session.m_rline_session.m_session_info, buf, 0xA9, nullptr);
			ImGui::SetClipboardText(buf);
		});

		components::sub_title("SESSION_SWITCHER"_T);
		if (ImGui::ListBoxHeader("###session_switch"))
		{
			for (const auto& session_type : sessions)
			{
				components::selectable(session_type.name, false, [&session_type] {
					session::join_type(session_type.id);
				});
			}
			ImGui::EndListBox();
		}

		components::sub_title("REGION_SWITCHER"_T);
		if (ImGui::ListBoxHeader("###region_switch"))
		{
			for (const auto& region_type : regions)
			{
				components::selectable(region_type.name, *g_pointers->m_region_code == region_type.id, [&region_type] {
					*g_pointers->m_region_code = region_type.id;
				});
			}
			ImGui::EndListBox();
		}

		ImGui::Checkbox("JOIN_IN_SCTV"_T.data(), &g.session.join_in_sctv_slots);
		if (ImGui::IsItemHovered())
			ImGui::SetTooltip("JOIN_IN_SCTV_DESC"_T.data());

		components::sub_title("PLAYER_MAGNET"_T);
		ImGui::Checkbox("ENABLED"_T.data(), &g.session.player_magnet_enabled);
		if (g.session.player_magnet_enabled)
		{
			ImGui::InputInt("PLAYER_COUNT"_T.data(), &g.session.player_magnet_count);
		}
		components::sub_title("Chat");
		ImGui::Checkbox("AUTO_KICK_CHAT_SPAMMERS"_T.data(), &g.session.kick_chat_spammers);
		ImGui::Checkbox("DISABLE_FILTER"_T.data(), &g.session.chat_force_clean);
		if (ImGui::IsItemHovered())
			ImGui::SetTooltip("Your sent chat messages will not be censored to the receivers");// TODO: add translation
		ImGui::Checkbox("LOG_CHAT_MSG"_T.data(), &g.session.log_chat_messages);
		ImGui::Checkbox("LOG_TXT_MSG"_T.data(), &g.session.log_text_messages);
		static char msg[256];
		components::input_text("##message", msg, sizeof(msg));
		ImGui::SameLine();
		ImGui::Checkbox("IS_TEAM"_T.data(), &g.session.is_team);
		ImGui::SameLine();
		components::button("SEND"_T, [] {
			if (const auto net_game_player = gta_util::get_network_player_mgr()->m_local_net_player; net_game_player)
			{
				if (g_hooking->get_original<hooks::send_chat_message>()(*g_pointers->m_send_chat_ptr,
				        net_game_player->get_net_data(),
				        msg,
				        g.session.is_team))
					notify::draw_chat(msg, net_game_player->get_name(), g.session.is_team);
			}
		});

		ImGui::Checkbox("CHAT_COMMANDS"_T.data(), &g.session.chat_commands);
		if (g.session.chat_commands)
		{
			if (ImGui::BeginCombo("DEFAULT_CMD_PERMISSIONS"_T.data(), COMMAND_ACCESS_LEVELS[g.session.chat_command_default_access_level]))
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

		components::sub_title("DECLOAK"_T);
		components::script_patch_checkbox("REVEAL_OTR_PLAYERS"_T, &g.session.decloak_players);

		components::sub_title("FORCE_HOST"_T);
		ImGui::Checkbox("FORCE_SESSION_HOST"_T.data(), &g.session.force_session_host);
		if (ImGui::IsItemHovered())
			ImGui::SetTooltip("FORCE_SESSION_HOST_DESC"_T.data());
		ImGui::SameLine();
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

		components::sub_title("REMOTE_NAME_SPOOFING"_T);
		ImGui::Checkbox("SPOOF_PLAYER_NAMES"_T.data(), &g.session.name_spoof_enabled);
		if (ImGui::IsItemHovered())
			ImGui::SetTooltip("SPOOF_PLAYER_NAMES_DESC"_T.data());

		if (g.session.name_spoof_enabled)
		{
			ImGui::Checkbox("ADVERTISE_YIMMENU"_T.data(), &g.session.advertise_menu);
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip("ADVERTISE_YIMMENU_DESC"_T.data());

			if (!g.session.advertise_menu)
			{
				constexpr size_t name_size = RTL_FIELD_SIZE(rage::rlGamerInfo, m_name);
				static char name[name_size];
				strcpy_s(name, sizeof(name), g.session.spoofed_name.c_str());

				ImGui::Text("PLAYER_SPOOFED_NAME"_T.data());
				components::input_text("##username_input", name, sizeof(name));

				if (name != g.session.spoofed_name)
					g.session.spoofed_name = std::string(name);
			}
		}

		components::sub_title("ALL_PLAYERS"_T);
		ImGui::Checkbox("OFF_THE_RADAR"_T.data(), &g.session.off_radar_all);
		ImGui::SameLine();
		ImGui::Checkbox("NEVER_WANTED"_T.data(), &g.session.never_wanted_all);
		ImGui::SameLine();
		ImGui::Checkbox("SEMI_GODMODE"_T.data(), &g.session.semi_godmode_all);

		ImGui::Checkbox("EXPLOSION_KARMA"_T.data(), &g.session.explosion_karma);
		ImGui::SameLine();
		ImGui::Checkbox("DAMAGE_KARMA"_T.data(), &g.session.damage_karma);

		static int global_wanted_level = 0;

		if (ImGui::SliderInt("WANTED_LVL"_T.data(), &global_wanted_level, 0, 5))
		{
			*scr_globals::globalplayer_bd.at(self::id, scr_globals::size::globalplayer_bd).at(213).as<int*>() = global_wanted_level;
		}

		ImGui::SameLine();
		if (ImGui::Checkbox("FORCE"_T.data(), &g.session.wanted_level_all))
		{
			*scr_globals::globalplayer_bd.at(self::id, scr_globals::size::globalplayer_bd).at(212).as<Player*>() = __rdtsc() + 32;
			*scr_globals::globalplayer_bd.at(self::id, scr_globals::size::globalplayer_bd).at(213).as<int*>() = global_wanted_level;
		}

		components::command_button<"killall">({}, "KILL_ALL"_T);
		ImGui::SameLine();
		components::command_button<"explodeall">({}, "EXPLODE_ALL"_T);

		ImGui::SameLine();

		components::command_button<"beastall">({});
		if (ImGui::IsItemHovered())
			ImGui::SetTooltip("INCLUDING_YOU"_T.data());

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

		components::command_button<"sextall">({}, "Send Sexts");
		ImGui::SameLine();
		components::command_button<"fakebanall">({}, "Send Fake Ban Messages");

		components::small_text("TELEPORTS"_T);

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

		ImGui::Checkbox("DISABLE_PEDS"_T.data(), &g.session.disable_peds);
		ImGui::SameLine();
		ImGui::Checkbox("DISABLE_TRAFFIC"_T.data(), &g.session.disable_traffic);
		ImGui::SameLine();
		ImGui::Checkbox("FORCE_THUNDER"_T.data(), &g.session.force_thunder);

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
