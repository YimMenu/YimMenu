#include "views/view.hpp"
#include "fiber_pool.hpp"
#include "util/teleport.hpp"
#include "core/data/region_codes.hpp"
#include "core/data/language_codes.hpp"
#include <network/ClanData.hpp>

namespace big
{
	void view::spoofing()
	{
		components::small_text("To spoof any of the below credentials you need to reconnect with the lobby.\nAll spoofed details will be only visible by other players, your game will still show your actual name, ip, rid...");

		components::sub_title("Username");

		ImGui::Checkbox("Spoof Username", &g.spoofing.spoof_username);
		if (g.spoofing.spoof_username)
		{
			ImGui::SameLine();
			ImGui::Checkbox("Spoof Username Locally", &g.spoofing.spoof_local_username);
		}

		constexpr size_t name_size = RTL_FIELD_SIZE(rage::rlGamerInfo, m_name);
		static char name[name_size];
		strcpy_s(name, sizeof(name), g.spoofing.username.c_str());

		ImGui::Text("Username:");
		components::input_text("##username_input", name, sizeof(name));

		if (name != g.spoofing.username)
			g.spoofing.username = std::string(name);

		ImGui::Separator();

		components::sub_title("IP Address");

		ImGui::Checkbox("Spoof IP", &g.spoofing.spoof_ip);
		if (ImGui::IsItemHovered())
			ImGui::SetTooltip("Disable this feature if you're having trouble joining sessions.");

		ImGui::Text("IP Address:");
		ImGui::DragInt4("##ip_fields", g.spoofing.ip_address.data(), 0, 255);

		ImGui::Separator();

		components::sub_title("Rockstar ID");

		ImGui::Checkbox("Spoof Rockstar ID", &g.spoofing.spoof_rockstar_id);

		ImGui::Text("Rockstar ID:");
		ImGui::InputScalar("##rockstar_id_input", ImGuiDataType_U64, &g.spoofing.rockstar_id);

		components::sub_title("Hide Features");
		ImGui::Checkbox("Hide God Mode", &g.spoofing.spoof_hide_god);
		ImGui::Checkbox("Hide Spectate", &g.spoofing.spoof_hide_spectate);

		components::sub_title("Crew");

		ImGui::Checkbox("Spoof Crew", &g.spoofing.spoof_crew_data);

		constexpr size_t crew_tag_size = RTL_FIELD_SIZE(ClanData, m_clan_tag);
		static char crew_tag[crew_tag_size];
		strcpy_s(crew_tag, sizeof(crew_tag), g.spoofing.crew_tag.c_str());

		ImGui::Text("Crew Tag:");
		components::input_text("##crew_tag_input", crew_tag, sizeof(crew_tag));

		if (crew_tag != g.spoofing.crew_tag)
			g.spoofing.crew_tag = std::string(crew_tag);

		ImGui::Checkbox("Is Rockstar Crew", &g.spoofing.rockstar_crew);

		ImGui::Checkbox("Square Crew Tag", &g.spoofing.square_crew_tag);

		components::sub_title("Extra - Only work when Spoofed RID");

		ImGui::Checkbox("Is Cheater", &g.spoofing.spoof_cheater);
		ImGui::Checkbox("Is Rockstar Dev", &g.spoofing.spoof_rockstar_dev);
		ImGui::Checkbox("Is Rockstar QA", &g.spoofing.spoof_rockstar_qa);

		components::sub_title("Session Attributes");
		components::small_text("Only works when session host");

		ImGui::Checkbox("Region", &g.spoofing.spoof_session_region_type);
		if (g.spoofing.spoof_session_region_type)
		{
			ImGui::SameLine();
			if (ImGui::BeginCombo("###region_select", regions[g.spoofing.session_region_type].name))
			{
				for (const auto& region : regions)
				{
					if (ImGui::Selectable(region.name, g.spoofing.session_region_type == region.id))
					{
						g.spoofing.session_region_type = region.id;
					}
				}
				ImGui::EndCombo();
			}
		}
		ImGui::Checkbox("Language", &g.spoofing.spoof_session_language);
		if (g.spoofing.spoof_session_language)
		{
			ImGui::SameLine();

			if (ImGui::BeginCombo("###language_select", languages[g.spoofing.session_language].name))
			{
				for (const auto& language : languages)
				{
					if (ImGui::Selectable(language.name, g.spoofing.session_language == language.id))
					{
						g.spoofing.session_language = language.id;
					};
				}
				ImGui::EndCombo();
			}
		}

		ImGui::Checkbox("Player Count", &g.spoofing.spoof_session_player_count);
		if (g.spoofing.spoof_session_player_count)
		{
			ImGui::SameLine();
			ImGui::InputInt("###player_count", &g.spoofing.session_player_count);
		}
	}
}
