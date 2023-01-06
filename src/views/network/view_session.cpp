#include "views/view.hpp"
#include "fiber_pool.hpp"
#include "util/session.hpp"
#include "core/data/region_codes.hpp"
#include "gta_util.hpp"
#include "util/notify.hpp"
#include "util/scripts.hpp"
#include "util/toxic.hpp"
#include "core/data/apartment_names.hpp"
#include "core/data/warehouse_names.hpp"
#include "core/data/command_access_levels.hpp"
#include "hooking.hpp"

#include <network/Network.hpp>
#include <script/globals/GPBD_FM_3.hpp>

namespace big
{
	void view::session()
	{
		static uint64_t rid = 0;
		ImGui::InputScalar("Input RID", ImGuiDataType_U64, &rid);
		components::button("Join by RID", []
		{
			session::join_by_rockstar_id(rid);
		});
		ImGui::SameLine();
		components::button("Kick by RID", []
		{
			session::kick_by_rockstar_id(rid);
		});

		static char username[20];
		ImGui::InputText("Input Username", username, sizeof(username));
		if (components::button("Join by Username"))
		{
			session::join_by_username(username);
		};
		ImGui::SameLine();
		if (components::button("Kick by Username"))
		{
			session::kick_by_username(username);
		};

		static char base64[500]{};
		ImGui::InputText("Session Info", base64, sizeof(base64));
		components::button("Join Session Info", []
		{
			rage::rlSessionInfo info;
			g_pointers->m_decode_session_info(&info, base64, nullptr);
			session::join_session(info);
		});
		ImGui::SameLine();
		components::button("Copy Current Session Info", []
		{
			char buf[0x100];
			g_pointers->m_encode_session_info(&gta_util::get_network()->m_game_session.m_rline_session.m_session_info, buf, 0x7D, nullptr);
			ImGui::SetClipboardText(buf);
		});

		components::sub_title("Session Switcher");
		if (ImGui::ListBoxHeader("###session_switch"))
		{
			for (const auto& session_type : sessions)
			{
				components::selectable(session_type.name, false, [&session_type]
				{
					session::join_type(session_type.id);
				});
			}
			ImGui::EndListBox();
		}
		
		components::sub_title("Region Switcher");
		if (ImGui::ListBoxHeader("###region_switch"))
		{
			for (const auto& region_type : regions)
			{
				components::selectable(region_type.name, *g_pointers->m_region_code == region_type.id, [&region_type]
				{
					*g_pointers->m_region_code = region_type.id;
				});
			}
			ImGui::EndListBox();
		}

		ImGui::Checkbox("Join in SCTV slots", &g.session.join_in_sctv_slots);
		if (ImGui::IsItemHovered())
			ImGui::SetTooltip("Allows you to join full and solo sessions but can be detected by other modders");

		components::sub_title("Player Magnet");
		ImGui::Checkbox("Enabled", &g.session.player_magnet_enabled);
		if (g.session.player_magnet_enabled)
		{
			ImGui::InputInt("Player Count", &g.session.player_magnet_count);
		}

		components::sub_title("Chat");
		ImGui::Checkbox("Auto-kick Chat Spammers", &g.session.kick_chat_spammers);
		ImGui::Checkbox("Disable Filter", &g.session.disable_chat_filter);
		ImGui::Checkbox("Log Chat Messages", &g.session.log_chat_messages);
		ImGui::Checkbox("Log Text Messages", &g.session.log_text_messages);
		static char msg[256];
		ImGui::InputText("##message", msg, sizeof(msg));
		ImGui::SameLine();
		ImGui::Checkbox("Is Team", &g.session.is_team);
		ImGui::SameLine();
		components::button("Send", []
		{
            if (const auto net_game_player = gta_util::get_network_player_mgr()->m_local_net_player; net_game_player)
			{
                if (g_hooking->get_original<hooks::send_chat_message>()(*g_pointers->m_send_chat_ptr, net_game_player->get_net_data(), msg, g.session.is_team))
					notify::draw_chat(msg, net_game_player->get_name(), g.session.is_team);
			}
		});

		ImGui::Checkbox("Chat Commands", &g.session.chat_commands);
		if (g.session.chat_commands)
		{
			if (ImGui::BeginCombo("Default Command Permissions", COMMAND_ACCESS_LEVELS[g.session.chat_command_default_access_level]))
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

		components::sub_title("Decloak");
		components::script_patch_checkbox("Reveal OTR Players", &g.session.decloak_players);

		components::sub_title("Force Host");
		ImGui::Checkbox("Force Session Host", &g.session.force_session_host);
		if (ImGui::IsItemHovered())
			ImGui::SetTooltip("Join another session to apply changes. The original host of the session must leave or be kicked. This feature is easily detectable by other mod menus, use with caution");
		ImGui::SameLine();
		if (g.session.force_session_host)
		{
			ImGui::SameLine();
			ImGui::Checkbox("Kick Host During Join", &g.session.kick_host_when_forcing_host);
		}

		if (ImGui::Checkbox("Force Script Host", &g.session.force_script_host))
		{
			if (g.session.force_script_host)
				g_fiber_pool->queue_job([]
			{
				scripts::force_host(RAGE_JOAAT("freemode"));
				if (auto script = gta_util::find_script_thread(RAGE_JOAAT("freemode")); script && script->m_net_component)
					script->m_net_component->block_host_migration(true);
			});
		}

		components::sub_title("Remote Name Spoofing");
		ImGui::Checkbox("Spoof Other Players' Names", &g.session.name_spoof_enabled);
		if (ImGui::IsItemHovered())
			ImGui::SetTooltip("Requires session host. Spoofed names will not visible locally nor to the player that had their name spoofed. Requires players to join after becoming host");

		if (g.session.name_spoof_enabled)
		{
			ImGui::Checkbox("Advertise YimMenu", &g.session.advertise_menu);
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip("Advertise YimMenu by spoofing player names to differently colored variants of 'YimMenu'. You will not be able to customize the name with this option enabled");

			if (!g.session.advertise_menu)
			{
				constexpr size_t name_size = RTL_FIELD_SIZE(rage::rlGamerInfo, m_name);
				static char name[name_size];
				strcpy_s(name, sizeof(name), g.session.spoofed_name.c_str());

				ImGui::Text("Name: ");
				ImGui::InputText("##username_input", name, sizeof(name));

				if (name != g.session.spoofed_name)
					g.session.spoofed_name = std::string(name);
			}
		}

		components::sub_title("All Players");
		ImGui::Checkbox("Off The Radar", &g.session.off_radar_all);
		ImGui::SameLine();
		ImGui::Checkbox("Never Wanted", &g.session.never_wanted_all);
		ImGui::SameLine();
		ImGui::Checkbox("Semi Godmode", &g.session.semi_godmode_all);

		ImGui::Checkbox("Explosion Karma", &g.session.explosion_karma);
		ImGui::SameLine();
		ImGui::Checkbox("Damage Karma", &g.session.damage_karma);

		static int global_wanted_level = 0;

		if (ImGui::SliderInt("Wanted Level", &global_wanted_level, 0, 5))
		{
			*scr_globals::globalplayer_bd.at(self::id, scr_globals::size::globalplayer_bd).at(213).as<int*>() = global_wanted_level;
		}

		ImGui::SameLine();
		if (ImGui::Checkbox("Force", &g.session.wanted_level_all))
		{
			*scr_globals::globalplayer_bd.at(self::id, scr_globals::size::globalplayer_bd).at(212).as<Player*>() = __rdtsc() + 32;
			*scr_globals::globalplayer_bd.at(self::id, scr_globals::size::globalplayer_bd).at(213).as<int*>() = global_wanted_level;
		}

		components::command_button<"killall">({ }, "Kill Everyone");
		ImGui::SameLine();
		components::command_button<"explodeall">({ }, "Explode Everyone");

		ImGui::SameLine();


		components::command_button<"beastall">({ });
		if (ImGui::IsItemHovered())
			ImGui::SetTooltip("Including you");

		components::command_button<"giveweapsall">({ });
		ImGui::SameLine();
		components::command_button<"remweapsall">({ });

		components::command_button<"ceokickall">( { });
		ImGui::SameLine();
		components::command_button<"vehkickall">({ });

		components::command_button<"ragdollall">({ }, "Ragdoll Players");
		components::command_button<"intkickall">({ }, "Kick Everyone From Interiors");

		components::small_text("Teleports");

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

		components::command_button<"apartmenttpall">({ (uint64_t)g.session.send_to_apartment_idx }, "TP All To Apartment");

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

		components::command_button<"warehousetpall">({ (uint64_t)g.session.send_to_warehouse_idx }, "TP All To Warehouse");

		components::button("TP All To Darts", [] { g_player_service->iterate([](auto& plyr) { toxic::start_activity(plyr.second, eActivityType::Darts); }); });
		ImGui::SameLine();
		components::button("TP All To Flight School", [] { g_player_service->iterate([](auto& plyr) { toxic::start_activity(plyr.second, eActivityType::PilotSchool); }); });
		ImGui::SameLine();
		components::button("TP All To Map Center", [] { g_player_service->iterate([](auto& plyr) { toxic::start_activity(plyr.second, eActivityType::ArmWresling); }); });

		components::button("TP All To Skydive", [] { g_player_service->iterate([](auto& plyr) { toxic::start_activity(plyr.second, eActivityType::Skydive); }); });
		ImGui::SameLine();

		components::command_button<"interiortpall">({ 81 }, "TP All To MOC");

		ImGui::SameLine();
		components::command_button<"interiortpall">({ 123 }, "TP All To Casino");
		ImGui::SameLine();
		components::command_button<"interiortpall">({ 124 }, "TP All To Penthouse");
		ImGui::SameLine();
		components::command_button<"interiortpall">({ 128 }, "TP All To Arcade");

		components::command_button<"interiortpall">({ 146 }, "TP All To Music Locker");
		ImGui::SameLine();
		components::command_button<"interiortpall">({ 148 }, "TP All To Record A Studios");
		ImGui::SameLine();
		components::command_button<"interiortpall">({ 149 }, "TP All To Custom Auto Shop");

		components::command_button<"interiortpall">({ 155 }, "TP All To Agency");
		ImGui::SameLine();
		components::command_button<"interiortpall">({ 160 }, "TP All To Freakshop");
		ImGui::SameLine();
		components::command_button<"interiortpall">({ 161 }, "TP All To Multi Floor Garage");

		components::sub_title("Event Starter");
		
		ImGui::BeginGroup();
		components::button("Hot Target", [] { scripts::start_launcher_script(36); });
		components::button("Kill List", [] { scripts::start_launcher_script(37); });
		components::button("Checkpoints", [] { scripts::start_launcher_script(39); });
		components::button("Challenges", [] { scripts::start_launcher_script(40); });
		components::button("Penned In", [] { scripts::start_launcher_script(41); });
		ImGui::EndGroup();

		ImGui::SameLine();

		ImGui::BeginGroup();
		components::button("Hot Property", [] { scripts::start_launcher_script(43); });
		components::button("King Of The Castle", [] { scripts::start_launcher_script(45); });
		components::button("Criminal Damage", [] { scripts::start_launcher_script(46); });
		components::button("Hunt The Beast", [] { scripts::start_launcher_script(47); });
		components::button("Business Battles", [] { scripts::start_launcher_script(114); });
		ImGui::EndGroup();

		ImGui::SameLine();

		ImGui::BeginGroup();
		components::button("One-On-One Deathmatch", [] { scripts::start_launcher_script(197); });
		components::button("Impromptu Race", [] { scripts::start_launcher_script(16); });
		components::button("Flight School", [] { scripts::start_launcher_script(196); });
		components::button("Golf", [] { scripts::start_launcher_script(193); });
		components::button("Tutorial", [] { scripts::start_launcher_script(20); });
		if (ImGui::IsItemHovered())
			ImGui::SetTooltip("Only works on joining players");
		ImGui::EndGroup();

		ImGui::SameLine();

		ImGui::BeginGroup();
		components::button("Gunslinger", [] { scripts::start_launcher_script(211); });
		components::button("Space Monkey", [] { scripts::start_launcher_script(216); });
		components::button("Wizard", [] { scripts::start_launcher_script(212); });
		components::button("QUB3D", [] { scripts::start_launcher_script(217); });
		components::button("Camhedz", [] { scripts::start_launcher_script(218); });
		ImGui::EndGroup();

		ImGui::Checkbox("Disable Pedestrians", &g.session.disable_peds);
		ImGui::SameLine();
		ImGui::Checkbox("Disable Traffic", &g.session.disable_traffic);
		ImGui::SameLine();
		ImGui::Checkbox("Force Thunder", &g.session.force_thunder);

		components::small_text("Warp Time (requires session host)");

		components::button("+1 Minute", [] { toxic::warp_time_forward_all(60 * 1000); });
		ImGui::SameLine();
		components::button("+5 Minutes", [] { toxic::warp_time_forward_all(5 * 60 * 1000); });
		ImGui::SameLine();
		components::button("+48 Minutes", [] { toxic::warp_time_forward_all(48 * 60 * 1000); });
		ImGui::SameLine();
		components::button("+96 Minutes", [] { toxic::warp_time_forward_all(96 * 60 * 1000); });
		ImGui::SameLine();
		components::button("+200 Minutes", [] { toxic::warp_time_forward_all(200 * 60 * 1000); });
		ImGui::SameLine();
		components::button("Stop Time", [] { toxic::set_time_all(INT_MAX - 3000); });
		if (ImGui::IsItemHovered())
			ImGui::SetTooltip("This cannot be reversed. Use with caution");

		components::sub_title("Script Host Features");
		ImGui::Checkbox("Disable CEO Money", &g.session.block_ceo_money);
		if (ImGui::IsItemHovered())
			ImGui::SetTooltip("Blocks CEO money drops across the entire session. This can also break other stuff, use with caution");
		ImGui::SameLine();
		ImGui::Checkbox("Randomize CEO Colors", &g.session.randomize_ceo_colors);
	}
}
