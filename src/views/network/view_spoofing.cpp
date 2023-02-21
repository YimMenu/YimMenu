#include "core/data/blip_types.hpp"
#include "core/data/language_codes.hpp"
#include "core/data/region_codes.hpp"
#include "fiber_pool.hpp"
#include "util/teleport.hpp"
#include "views/view.hpp"

#include <network/ClanData.hpp>

namespace big
{
	void view::spoofing()
	{
		// requires translation

		ImGui::Checkbox("Hide From Player List", &g.spoofing.hide_from_player_list);

		components::script_patch_checkbox("Spoof Blip Type", &g.spoofing.spoof_blip);
		if (g.spoofing.spoof_blip)
		{
			ImGui::SameLine();
			if (ImGui::BeginCombo("###blip_type_select", blip_types[g.spoofing.blip_type]))
			{
				for (int i = 0; i < blip_types.size(); i++)
				{
					if (ImGui::Selectable(blip_types[i], g.spoofing.blip_type == i))
					{
						g.spoofing.blip_type = i;
					}
				}
				ImGui::EndCombo();
			}
		}

		ImGui::Checkbox("Spoof Rank", &g.spoofing.spoof_rank);
		if (g.spoofing.spoof_rank)
		{
			ImGui::SameLine();
			if (ImGui::InputInt("###rank", &g.spoofing.rank))
			{
				*g_pointers->m_force_player_card_refresh = true;
			}
		}

		ImGui::Checkbox("Spoof K/D Ratio", &g.spoofing.spoof_kd_ratio);
		if (g.spoofing.spoof_kd_ratio)
		{
			ImGui::SameLine();
			if (ImGui::InputFloat("###kd_ratio", &g.spoofing.kd_ratio))
			{
				*g_pointers->m_force_player_card_refresh = true;
			}
		}

		ImGui::Checkbox("Spoof Badsport State", &g.spoofing.spoof_bad_sport);
		if (g.spoofing.spoof_bad_sport)
		{
			ImGui::SameLine();
			if (ImGui::Combo("###badsport_select", &g.spoofing.badsport_type, "Clean Player\0Dirty Player\0Bad Sport"))
			{
				*g_pointers->m_force_player_card_refresh = true;
			}
		}

		ImGui::Checkbox("Spoof Job Points", &g.spoofing.spoof_job_points);
		if (g.spoofing.spoof_job_points)
		{
			ImGui::SameLine();
			ImGui::InputInt("###jp", &g.spoofing.job_points);
		}

		ImGui::Checkbox("Spoof Player Model", &g.spoofing.spoof_player_model);
		if (g.spoofing.spoof_player_model)
		{
			static char model[32];
			strcpy_s(model, sizeof(model), g.spoofing.player_model.c_str());

			ImGui::SameLine();
			components::input_text("##model_input", model, sizeof(model));

			if (model != g.spoofing.player_model)
				g.spoofing.player_model = std::string(model);
		}


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
