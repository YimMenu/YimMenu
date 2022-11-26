#include "views/view.hpp"
#include "fiber_pool.hpp"
#include "util/session.hpp"
#include "core/data/region_codes.hpp"
#include "gta_util.hpp"
#include "util/notify.hpp"
#include "util/scripts.hpp"
#include "util/toxic.hpp"

namespace big
{
	void view::session()
	{
		static uint64_t rid = 0;
		ImGui::InputScalar("Input RID", ImGuiDataType_U64, &rid);
		components::button("Join RID", []
		{
			session::join_by_rockstar_id(rid);
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

		ImGui::Checkbox("Join in SCTV slots", &g->session.join_in_sctv_slots);
		if (ImGui::IsItemHovered())
			ImGui::SetTooltip("Allows you to join full and solo sessions but can be detected by other modders");

		components::sub_title("Player Magnet");
		ImGui::Checkbox("Enabled", &g->session.player_magnet_enabled);
		if (g->session.player_magnet_enabled)
		{
			ImGui::InputInt("Player Count", &g->session.player_magnet_count);
		}

		components::sub_title("Chat");
		ImGui::Checkbox("Disable Filter", &g->session.disable_chat_filter);
		ImGui::Checkbox("Log Chat Messages", &g->session.log_chat_messages);
		ImGui::Checkbox("Log Text Messages", &g->session.log_text_messages);
		static char msg[256];
		ImGui::InputText("##message", msg, sizeof(msg));
		ImGui::SameLine();
		ImGui::Checkbox("Is Team", &g->session.is_team);
		ImGui::SameLine();
		components::button("Send", []
		{
            if(const auto net_game_player = gta_util::get_network_player_mgr()->m_local_net_player; net_game_player)
			{
                if(g_pointers->m_send_chat_message(*g_pointers->m_send_chat_ptr, net_game_player->get_net_data(), msg, g->session.is_team))
					notify::draw_chat(msg, net_game_player->get_name(), g->session.is_team);
			}
		});

		components::sub_title("Decloak");
		components::script_patch_checkbox("Reveal OTR Players", &g->session.decloak_players);

		components::sub_title("Force Host");
		ImGui::Checkbox("Force Session Host", &g->session.force_session_host);
		if (ImGui::IsItemHovered())
			ImGui::SetTooltip("Join another session to apply changes. The original host of the session must leave or be kicked. This feature is easily detectable by other mod menus, use with caution");

		components::sub_title("Remote Name Spoofing");
		ImGui::Checkbox("Spoof Other Players' Names", &g->session.name_spoof_enabled);
		if (ImGui::IsItemHovered())
			ImGui::SetTooltip("Requires session host. Spoofed names will not visible locally nor to the player that had their name spoofed. Requires players to join after becoming host");

		if (g->session.name_spoof_enabled)
		{
			ImGui::Checkbox("Advertise YimMenu", &g->session.advertise_menu);
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip("Advertise YimMenu by spoofing player names to differently colored variants of 'YimMenu'. You will not be able to customize the name with this option enabled");

			if (!g->session.advertise_menu)
			{
				constexpr size_t name_size = RTL_FIELD_SIZE(rage::rlGamerInfo, m_name);
				static char name[name_size];
				strcpy_s(name, sizeof(name), g->session.spoofed_name.c_str());

				ImGui::Text("Name: ");
				ImGui::InputText("##username_input", name, sizeof(name));

				if (name != g->session.spoofed_name)
					g->session.spoofed_name = std::string(name);
			}
		}

		components::sub_title("All Players");
		ImGui::Checkbox("Off The Radar", &g->session.off_radar_all);
		ImGui::Checkbox("Never Wanted", &g->session.never_wanted_all);
		ImGui::Checkbox("Semi Godmode", &g->session.semi_godmode_all);

		static int global_wanted_level = 0;

		if (ImGui::SliderInt("Wanted Level", &global_wanted_level, 0, 5))
		{
			*scr_globals::globalplayer_bd.at(self::id, scr_globals::size::globalplayer_bd).at(213).as<int*>() = global_wanted_level;
		}

		ImGui::SameLine();
		if (ImGui::Checkbox("Force", &g->session.wanted_level_all))
		{
			*scr_globals::globalplayer_bd.at(self::id, scr_globals::size::globalplayer_bd).at(212).as<Player*>() = __rdtsc() + 32;
			*scr_globals::globalplayer_bd.at(self::id, scr_globals::size::globalplayer_bd).at(213).as<int*>() = global_wanted_level;
		}

		components::button("Kill Everyone", [] { g_player_service->iterate([](auto& plyr) { toxic::kill_player(plyr.second); }); });

		components::button("Turn Everyone Into Beast", [] { toxic::turn_everyone_into_beast(); });
		if (ImGui::IsItemHovered())
			ImGui::SetTooltip("Including you");

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
		components::button("One-On-One Deathmatch", [] { scripts::start_launcher_script(187); });
		components::button("Impromptu Race", [] { scripts::start_launcher_script(16); });
		components::button("Flight School", [] { scripts::start_launcher_script(186); });
		components::button("Golf", [] { scripts::start_launcher_script(183); });
		components::button("Tutorial", [] { scripts::start_launcher_script(20); });
		if (ImGui::IsItemHovered())
			ImGui::SetTooltip("Only works on joining players");
		ImGui::EndGroup();

		ImGui::SameLine();

		ImGui::BeginGroup();
		components::button("Gunslinger", [] { scripts::start_launcher_script(201); });
		components::button("Space Monkey", [] { scripts::start_launcher_script(206); });
		components::button("Wizard", [] { scripts::start_launcher_script(202); });
		components::button("QUB3D", [] { scripts::start_launcher_script(207); });
		components::button("Camhedz", [] { scripts::start_launcher_script(208); });
		ImGui::EndGroup();

		ImGui::Checkbox("Disable Pedestrians", &g->session.disable_peds);
		ImGui::SameLine();
		ImGui::Checkbox("Disable Traffic", &g->session.disable_traffic);
		ImGui::SameLine();
		ImGui::Checkbox("Force Thunder", &g->session.force_thunder);
	}
}
