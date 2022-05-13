#include "fiber_pool.hpp"
#include "util/entity.hpp"
#include "views/view.hpp"
#include "services/ped_list_service.hpp"

namespace big
{
	bool does_search_match_ped_list(std::string& input, const std::string& search)
	{
		std::transform(input.begin(), input.end(), input.begin(), ::tolower);

		return input.find(search) != std::string::npos;
	}

	void view::self() {
		components::button("Suicide", [] {
			ENTITY::SET_ENTITY_HEALTH(PLAYER::PLAYER_PED_ID(), 0, 0);
		});

		ImGui::SameLine();

		components::button("Skip Cutscene", [] {
			CUTSCENE::STOP_CUTSCENE_IMMEDIATELY();
		});

		static char model[32];
		components::input_text_with_hint("Model Name##player_ped_model", "Search", model, sizeof(model), ImGuiInputTextFlags_EnterReturnsTrue, []
		{
			const Hash hash = rage::joaat(model);

			for (uint8_t i = 0; !STREAMING::HAS_MODEL_LOADED(hash) && i < 100; i++)
			{
				STREAMING::REQUEST_MODEL(hash);

				script::get_current()->yield();
			}
			if (!STREAMING::HAS_MODEL_LOADED(hash))
			{
				g_notification_service->push_error("Self", "Failed to spawn model, did you give an incorrect model ? ");

				return;
			}

			PLAYER::SET_PLAYER_MODEL(PLAYER::GET_PLAYER_INDEX(), hash);
			PED::SET_PED_DEFAULT_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID());
			script::get_current()->yield();
			STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(hash);
		});
		if (ImGui::ListBoxHeader("###ped_list"))
		{
			if (!g_ped_list_service->get_ped_list().is_null())
			{
				for (auto& item : g_ped_list_service->get_ped_list())
				{
					if (item["Name"].is_null())
						continue;

					std::string name = item["Name"];

					std::string search = model;
					std::transform(search.begin(), search.end(), search.begin(), ::tolower);

					if (search.empty() ||
						does_search_match_ped_list(name, search))
					{
						components::selectable(item["Name"], item["Name"] == search, [&item]
						{
							const Hash hash = rage::joaat(item["Name"]);

							for (uint8_t i = 0; !STREAMING::HAS_MODEL_LOADED(hash) && i < 100; i++)
							{
								STREAMING::REQUEST_MODEL(hash);

								script::get_current()->yield();
							}
							if (!STREAMING::HAS_MODEL_LOADED(hash))
							{
								g_notification_service->push_error("Self", "Failed to spawn model, did you give an incorrect model ? ");

								return;
							}

							PLAYER::SET_PLAYER_MODEL(PLAYER::GET_PLAYER_INDEX(), hash);
							PED::SET_PED_DEFAULT_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID());
							script::get_current()->yield();
							STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(hash);
						});
					}
				}
			}
			ImGui::ListBoxFooter();
		}

		ImGui::Separator();

		components::small_text("General");

		ImGui::BeginGroup();

		ImGui::Checkbox("God Mode", &g->self.godmode);
		ImGui::Checkbox("Off Radar", &g->self.off_radar);
		ImGui::Checkbox("Free Cam", &g->self.free_cam);
		ImGui::Checkbox("Disable Phone", &g->tunables.disable_phone);

		ImGui::EndGroup();
		ImGui::SameLine();
		ImGui::BeginGroup();

		ImGui::Checkbox("No Clip", &g->self.noclip);
		ImGui::Checkbox("No Ragdoll", &g->self.no_ragdoll);
		ImGui::Checkbox("Super Run", &g->self.super_run);
		ImGui::Checkbox("No Idle Kick", &g->tunables.no_idle_kick);

		ImGui::EndGroup();
		ImGui::SameLine();
		ImGui::BeginGroup();

		ImGui::Checkbox("Invisibility", &g->self.invisibility);
		if (g->self.invisibility)
		{
			ImGui::Checkbox("Locally Visible", &g->self.local_visibility);
		}

		ImGui::Checkbox("Keep Player Clean", &g->self.clean_player);
		if (ImGui::Button("Clean Player"))
		{
			QUEUE_JOB_BEGIN_CLAUSE()
			{
				entity::clean_ped(PLAYER::PLAYER_PED_ID());
			}
			QUEUE_JOB_END_CLAUSE
		}

		ImGui::EndGroup();

		ImGui::Separator();

		components::small_text("Police");

		ImGui::Checkbox("Never Wanted", &g->self.never_wanted);

		if (!g->self.never_wanted)
		{
			ImGui::Checkbox("Force Wanted Level", &g->self.force_wanted_level);
			ImGui::Text("Wanted Level");
			if (ImGui::SliderInt("###wanted_level", &g->self.wanted_level, 0, 5) && !g->self.force_wanted_level)
				g_local_player->m_player_info->m_wanted_level = g->self.wanted_level;
		}
	}
}