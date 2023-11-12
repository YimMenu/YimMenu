#include "core/data/network.hpp"
#include "core/data/region_codes.hpp"
#include "core/data/session_types.hpp"
#include "core/settings/session.hpp"
#include "fiber_pool.hpp"
#include "gta_util.hpp"
#include "services/bad_players/bad_players.hpp"
#include "util/scripts.hpp"
#include "util/session.hpp"
#include "views/view.hpp"

namespace big
{
	static inline void ver_Space()
	{
		ImGui::Dummy(ImVec2(0.0f, ImGui::GetTextLineHeight()));
	}

	static inline void render_rid_joiner()
	{
		static uint64_t rid = 0;
		static char username[20];
		static char base64[500]{};

		ImGui::BeginGroup();
		{
			components::sub_title("Rid Joiner");

			ImGui::PushItemWidth(200);

			ImGui::InputScalar("##inputrid", ImGuiDataType_U64, &rid);
			ImGui::SameLine();
			components::button("Join##RID", [] {
				session::join_by_rockstar_id(rid);
			});
			if (*g_pointers->m_gta.m_is_session_started)
			{
				ImGui::SameLine();
				components::button("Invite##RID", [] {
					session::invite_by_rockstar_id(rid);
				});
			}
			components::input_text_with_hint("##usernameinput", "Input Username", username, sizeof(username));
			ImGui::SameLine();
			if (components::button("Join##Username"))
				session::join_by_username(username);
			if (*g_pointers->m_gta.m_is_session_started)
			{
				ImGui::SameLine();
				if (components::button("Invite##Username"))
					g_thread_pool->push([] {
						uint64_t rockstar_id;

						if (!g_api_service->get_rid_from_username(username, rockstar_id))
							g_notification_service->push_error("Player Invite", "User could not be found.");
						else
						{
							rid = rockstar_id;
							g_fiber_pool->queue_job([rockstar_id] {
								session::invite_by_rockstar_id(rockstar_id);
							});
						}
					});
			}

			components::input_text_with_hint("##sessioninfoinput", "Session Info", base64, sizeof(base64));
			ImGui::SameLine();
			components::button("Join##Session", [] {
				rage::rlSessionInfo info;
				if (g_pointers->m_gta.m_decode_session_info(&info, base64, nullptr))
					session::join_session(info);
				else
					g_notification_service->push_error("Join", "Session info is invalid");
			});

			ImGui::PopItemWidth();

			components::button("Copy Session Info", [] {
				char buf[0x100]{};
				g_pointers->m_gta.m_encode_session_info(&gta_util::get_network()->m_last_joined_session.m_session_info, buf, 0xA9, nullptr);
				ImGui::SetClipboardText(buf);
			});

			ImGui::Spacing();

			components::button("Join Last session", [] {
				session::join_session(gta_util::get_network()->m_last_joined_session.m_session_info);
			});
		}
		ImGui::EndGroup();
	}

	static inline void render_misc()
	{
		ImGui::BeginGroup();
		{
			components::sub_title("Misc");

			ImGui::BeginDisabled(!g_player_service->get_self()->is_host());
			ImGui::Checkbox("Lock Session", &g_session.lock_session);
			ImGui::EndDisabled();

			components::script_patch_checkbox("Reveal OTR Players", &g_session.decloak_players, "Reveals players that are off the radar");

			ImGui::Checkbox("Force Thunder globally", &g_session.force_thunder);

			ImGui::Checkbox("Spoof god mod", &g_session.spoof_hide_god);

			ImGui::Checkbox("Spoof spectate", &g_session.spoof_hide_spectate);
		}
		ImGui::EndGroup();
	}

	static inline void render_session_switcher()
	{
		ImGui::BeginGroup();
		{
			components::sub_title("Session Switcher");

			ImGui::SetNextItemWidth(300);
			if (ImGui::BeginCombo("##regionswitcher", "Regions"))
			{
				for (const auto& region_type : regions)
					components::selectable(region_type.name, *g_pointers->m_gta.m_region_code == region_type.id, [&region_type] {
						*g_pointers->m_gta.m_region_code = region_type.id;
					});
				ImGui::EndCombo();
			}

			ImGui::Spacing();

			if (ImGui::BeginListBox("###session_types", {300, 100}))
			{
				for (const auto& session_type : sessions)
					components::selectable(session_type.name, false, [&session_type] {
						session::join_type(session_type.id);
					});

				ImGui::EndListBox();
			}

			if (*g_pointers->m_gta.m_is_session_started)
			{
				ImGui::Spacing();
				components::button("Leave GTA Online", [] {
					session::join_type(eSessionType::LEAVE_ONLINE);
				});
			}
		}
		ImGui::EndGroup();
	}

	static inline void render_hosting()
	{
		ImGui::BeginGroup();
		{
			components::sub_title("Hosting");

			ImGui::Checkbox("Spoof Host Token", &g_session.force_session_host);
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip("Join another session to apply changes. The original host of the session must leave or be kicked");

			if (ImGui::Checkbox("Force Script Host", &g_session.force_script_host))
				g_fiber_pool->queue_job([] {
					scripts::force_script_host(g_session.force_script_host);
				});
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip("This might break freemode missions and interiors. Use with caution");

			ImGui::Checkbox("Auto kick host (defence)", &g_network.auto_kick_host_when_attacked);
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip("This will try to auto kick host when someone try to crash/kick you.");

			ImGui::Spacing();

			static std::string script_host_player_name = "";
			components::button("Identify Script Host", [] {
				if (auto launcher = gta_util::find_script_thread(RAGE_JOAAT("freemode")); launcher && launcher->m_net_component)
					if (auto host = ((CGameScriptHandlerNetComponent*)launcher->m_net_component)->get_host(); host)
						script_host_player_name = host->get_name();
			});
			ImGui::SameLine();
			ImGui::Text(script_host_player_name.c_str());

			if (g_player_service->get_self()->is_host())
			{
				ImGui::Spacing();
				components::button("Kick all blocked players", [] {
					g_player_service->iterate([](const player_entry& player) {
						if (player.second->is_blocked)
							dynamic_cast<player_command*>(command::get(RAGE_JOAAT("hostkick")))->call(player.second, {});
					});
				});
			}
		}
		ImGui::EndGroup();
	}

	void view::network()
	{
		ImGui::BeginGroup();
		{
			render_rid_joiner();
			ver_Space();
			render_misc();
		}
		ImGui::EndGroup();
		ImGui::SameLine(0, 2.0f * ImGui::GetTextLineHeight());
		ImGui::BeginGroup();
		{
			render_session_switcher();
			ver_Space();
			render_hosting();
		}
		ImGui::EndGroup();
	}
}
