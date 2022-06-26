#include "fiber_pool.hpp"
#include "util/entity.hpp"
#include "views/view.hpp"

namespace big
{
	void view::self() {
		components::button("Suicide", [] {
			ENTITY::SET_ENTITY_HEALTH(self::ped, 0, 0);
		});
		
		ImGui::SameLine();

		components::button("Heal", [] {
			ENTITY::SET_ENTITY_HEALTH(self::ped, PED::GET_PED_MAX_HEALTH(self::ped), 0);
			PED::SET_PED_ARMOUR(self::ped, PLAYER::GET_PLAYER_MAX_ARMOUR(self::id));
		});

		ImGui::SameLine();

		components::button("Skip Cutscene", [] {
			CUTSCENE::STOP_CUTSCENE_IMMEDIATELY();
		});

		static char model[32];
		components::input_text_with_hint("Model Name###player_ped_model", "Player Model Name", model, sizeof(model), ImGuiInputTextFlags_EnterReturnsTrue, []
		{
			g_fiber_pool->queue_job([] {
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
				PED::SET_PED_DEFAULT_COMPONENT_VARIATION(self::ped);
				script::get_current()->yield();
				STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(hash);
			});
		});

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

		components::button("Clean Player", [] {
			entity::clean_ped(self::ped);
		});

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
