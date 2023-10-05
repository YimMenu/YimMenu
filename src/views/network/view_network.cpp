#include "core/data/region_codes.hpp"
#include "fiber_pool.hpp"
#include "function_types.hpp"
#include "gta_util.hpp"
#include "hooking.hpp"
#include "util/notify.hpp"
#include "util/scripts.hpp"
#include "util/session.hpp"
#include "views/view.hpp"

namespace big
{
	void render_rid_joiner()
	{
		ImGui::BeginGroup();
		components::sub_title("Rid Joiner");
		if (ImGui::BeginListBox("##ridjoiner", get_listbox_dimensions()))
		{
			static uint64_t rid = 0;
			static char username[20];
			static char base64[500]{};

			ImGui::PushItemWidth(ImGui::GetWindowWidth() * 0.5);

			ImGui::InputScalar("##inputrid", ImGuiDataType_U64, &rid);
			ImGui::SameLine();
			components::button("Join by RID", [] {
				session::join_by_rockstar_id(rid);
			});

			components::input_text_with_hint("##usernameinput", "Input Username", username, sizeof(username));
			ImGui::SameLine();
			if (components::button("Join by Username"))
			{
				session::join_by_username(username);
			};

			components::input_text_with_hint("##sessioninfoinput", "Session Info", base64, sizeof(base64));
			ImGui::SameLine();
			components::button("Join Session Info", [] {
				rage::rlSessionInfo info;
				if (g_pointers->m_gta.m_decode_session_info(&info, base64, nullptr))
					session::join_session(info);
				else
					g_notification_service->push_error("Join", "Session info is invalid");
			});

			components::button("Copy Session Info", [] {
				char buf[0x100]{};
				g_pointers->m_gta.m_encode_session_info(&gta_util::get_network()->m_last_joined_session.m_session_info, buf, 0xA9, nullptr);
				ImGui::SetClipboardText(buf);
			});

			ImGui::PopItemWidth();
			ImGui::EndListBox();
		}
		ImGui::EndGroup();
	}

	void render_session_switcher()
	{
		ImGui::BeginGroup();
		components::sub_title("Session Switcher");
		if (ImGui::BeginListBox("###session_switch", get_listbox_dimensions()))
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
		if (ImGui::BeginListBox("##miscsession", get_listbox_dimensions()))
		{
			ImGui::BeginDisabled(!g_player_service->get_self()->is_host());
			ImGui::Checkbox("Lobby Lock", &g.session.lock_session);
			if (g.session.lock_session)
			{
				ImGui::Checkbox("Allow Friends Into Locked Lobby", &g.session.allow_friends_into_locked_session);
				if (ImGui::IsItemHovered())
					ImGui::SetTooltip("Allows Friends to Join Lobby While Locked");
			}
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip("Blocks all players from joining. May not work on some modders.");
			ImGui::EndDisabled();

			components::script_patch_checkbox("Reveal OTR Players",
			    &g.session.decloak_players,
			    "Reveals players that are off the radar");

			ImGui::EndListBox();
		}

		ImGui::EndGroup();
	}

	void render_chat()
	{
		ImGui::BeginGroup();

		components::sub_title("Chat");
		if (ImGui::BeginListBox("##chat", get_listbox_dimensions()))
		{
			static bool log_chat_messages, is_team;
			static char msg[256];

			ImGui::Checkbox("Log Messages (to file)", &g.session.log_chat_messages);

			components::input_text_with_hint("##message", "Message", msg, sizeof(msg));

			ImGui::Checkbox("Is Team Message", &is_team);
			ImGui::SameLine();
			components::button("Send Message", [] {
				if (const auto net_game_player = gta_util::get_network_player_mgr()->m_local_net_player; net_game_player)
				{
					if (g_hooking->get_original<hooks::send_chat_message>()(*g_pointers->m_gta.m_send_chat_ptr,
					        net_game_player->get_net_data(),
					        msg,
					        is_team))
						notify::draw_chat(msg, net_game_player->get_name(), is_team);
				}
			});

			ImGui::EndListBox();
		}

		ImGui::EndGroup();
	}

	void render_session_globals()
	{
		ImGui::BeginGroup();

		components::sub_title("Globals");
		if (ImGui::BeginListBox("##globals", get_listbox_dimensions()))
		{
			ImGui::Checkbox("Force Thunder", &g.session.force_thunder);
	
			ImGui::EndListBox();
		}

		ImGui::EndGroup();
	}

	void view::network()
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
		components::sub_title("Force Host");
		ImGui::Checkbox("Force Session Host", &g.session.force_session_host);
		if (ImGui::IsItemHovered())
			ImGui::SetTooltip("Join another session to apply changes. The original host of the session must leave or be kicked. This feature is easily detectable by other mod menus, use with caution");

		if (ImGui::Checkbox("Force Script Host", &g.session.force_script_host))
		{
			if (g.session.force_script_host)
				g_fiber_pool->queue_job([] {
					scripts::force_host(RAGE_JOAAT("freemode"));
					if (auto script = gta_util::find_script_thread(RAGE_JOAAT("freemode")); script && script->m_net_component)
						((CGameScriptHandlerNetComponent*)script->m_net_component)->block_host_migration(true);

					scripts::force_host(RAGE_JOAAT("fmmc_launcher"));
					if (auto script = gta_util::find_script_thread(RAGE_JOAAT("fmmc_launcher")); script && script->m_net_component)
						((CGameScriptHandlerNetComponent*)script->m_net_component)->block_host_migration(true);
				});
		}
		if (ImGui::IsItemHovered())
			ImGui::SetTooltip("This might break freemode missions and interiors. Use with caution");

		ImGui::EndGroup();
	}
}
