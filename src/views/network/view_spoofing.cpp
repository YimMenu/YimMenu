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
		components::small_text("SPOOFING_DESCRIPTION"_T);

		ImGui::Checkbox("Hide From Player List", &g.spoofing.hide_from_player_list);

		components::sub_title("SPOOFING_HIDE_FEATURES"_T);
		ImGui::Checkbox("SPOOFING_HIDE_GOD_MODE"_T.data(), &g.spoofing.spoof_hide_god);
		ImGui::Checkbox("SPOOFING_HIDE_SPECTATE"_T.data(), &g.spoofing.spoof_hide_spectate);

		components::sub_title("CREW"_T);

		ImGui::Checkbox("SPOOFING_CREW"_T.data(), &g.spoofing.spoof_crew_data);

		constexpr size_t crew_tag_size = RTL_FIELD_SIZE(ClanData, m_clan_tag);
		static char crew_tag[crew_tag_size];
		strcpy_s(crew_tag, sizeof(crew_tag), g.spoofing.crew_tag.c_str());

		ImGui::Text("SPOOFING_CREW_TAG"_T.data());
		components::input_text("##crew_tag_input", crew_tag, sizeof(crew_tag));

		if (crew_tag != g.spoofing.crew_tag)
			g.spoofing.crew_tag = std::string(crew_tag);

		ImGui::Checkbox("SPOOFING_CREW_ROCKSTAR"_T.data(), &g.spoofing.rockstar_crew);

		ImGui::Checkbox("SPOOFING_CREW_SQUARE_TAG"_T.data(), &g.spoofing.square_crew_tag);

		components::sub_title("SPOOFING_SESSION_ATTRIBUTES"_T);
		components::small_text("SPOOFING_ONLY_WORKS_AS_HOST"_T);

		ImGui::Checkbox("SPOOFING_ATTRIBUTE_REGION"_T.data(), &g.spoofing.spoof_session_region_type);
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
		ImGui::Checkbox("SPOOFING_ATTRIBUTE_LANGUAGE"_T.data(), &g.spoofing.spoof_session_language);
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

		ImGui::Checkbox("SPOOFING_ATTRIBUTE_PLAYER_COUNT"_T.data(), &g.spoofing.spoof_session_player_count);
		if (g.spoofing.spoof_session_player_count)
		{
			ImGui::SameLine();
			ImGui::InputInt("###player_count", &g.spoofing.session_player_count);
		}
	}
}
