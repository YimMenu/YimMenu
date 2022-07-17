#include "fiber_pool.hpp"
#include "util/entity.hpp"
#include "util/player.hpp"
#include "views/view.hpp"
#include "services/gta_data/gta_data_service.hpp"
#include <imgui_internal.h>

namespace big
{
	void view::self()
	{
		components::button("Suicide", [] {
			ENTITY::SET_ENTITY_HEALTH(self::ped, 0, 0);
		});

		ImGui::SameLine();

		components::button("Heal", [] {
			ENTITY::SET_ENTITY_HEALTH(self::ped, PED::GET_PED_MAX_HEALTH(self::ped), 0);
			PED::SET_PED_ARMOUR(self::ped, PLAYER::GET_PLAYER_MAX_ARMOUR(self::id));
		});

		ImGui::SameLine();

		components::button("Fill Inventory", [] {
			std::string mpPrefix = player::get_mp_prefix();
			STATS::STAT_SET_INT(rage::joaat(mpPrefix + "NO_BOUGHT_YUM_SNACKS"), 30, true);
			STATS::STAT_SET_INT(rage::joaat(mpPrefix + "NO_BOUGHT_HEALTH_SNACKS"), 15, true);
			STATS::STAT_SET_INT(rage::joaat(mpPrefix + "NO_BOUGHT_EPIC_SNACKS"), 5, true);
			STATS::STAT_SET_INT(rage::joaat(mpPrefix + "MP_CHAR_ARMOUR_1_COUNT"), 10, true);
			STATS::STAT_SET_INT(rage::joaat(mpPrefix + "MP_CHAR_ARMOUR_2_COUNT"), 10, true);
			STATS::STAT_SET_INT(rage::joaat(mpPrefix + "MP_CHAR_ARMOUR_3_COUNT"), 10, true);
			STATS::STAT_SET_INT(rage::joaat(mpPrefix + "MP_CHAR_ARMOUR_4_COUNT"), 10, true);
			STATS::STAT_SET_INT(rage::joaat(mpPrefix + "MP_CHAR_ARMOUR_5_COUNT"), 10, true);
		});

		ImGui::SameLine();

		components::button("Skip Cutscene", [] {
			CUTSCENE::STOP_CUTSCENE_IMMEDIATELY();
		});

		ImGui::Separator();

		components::small_text("Player Model Changer");

		static int selected_player_ped_type = -1;
		static bool player_model_open = false;
		static char player_model_name[64];

		auto ped_type_arr = g_gta_data_service->get_ped_type_arr();
		auto ped_arr = g_gta_data_service->get_ped_arr();

		ImGui::SetNextItemWidth(300.f);
		if (ImGui::BeginCombo("Ped Type", selected_player_ped_type == -1 ? "ALL" : ped_type_arr[selected_player_ped_type].c_str()))
		{
			if (ImGui::Selectable("ALL", selected_player_ped_type == -1))
			{
				selected_player_ped_type = -1;
			}

			for (int i = 0; i < ped_type_arr.size(); i++)
			{
				if (ImGui::Selectable(ped_type_arr[i].c_str(), selected_player_ped_type == i))
				{
					selected_player_ped_type = i;
					player_model_name[0] = 0;
				}

				if (selected_player_ped_type == i)
				{
					ImGui::SetItemDefaultFocus();
				}
			}

			ImGui::EndCombo();
		}

		ImGui::SetNextItemWidth(300.f);
		components::input_text_with_hint("Model Name##player_model_name", "Model Name", player_model_name, sizeof(player_model_name), ImGuiInputTextFlags_EnterReturnsTrue, [] {
			player_model_open = false;
		});

		bool player_model_focused = ImGui::IsItemActive();

		if (ImGui::IsItemActivated())
		{
			player_model_open = true;
		}

		if (player_model_open)
		{
			bool is_open = true;

			std::string lower_search = player_model_name;
			std::transform(lower_search.begin(), lower_search.end(), lower_search.begin(), tolower);

			ImGui::SetNextWindowPos({ ImGui::GetItemRectMin().x, ImGui::GetItemRectMax().y });
			ImGui::SetNextWindowSize({ 300, 300 });
			if (ImGui::Begin("##player_model_popup", &is_open, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_Tooltip))
			{
				ImGui::BringWindowToDisplayFront(ImGui::GetCurrentWindow());
				player_model_focused |= ImGui::IsWindowFocused();

				for (auto& item : ped_arr)
				{
					std::string ped_type = item.ped_type;
					std::string name = item.name;

					std::transform(name.begin(), name.end(), name.begin(), tolower);

					if ((
						selected_player_ped_type == -1 || ped_type_arr[selected_player_ped_type] == ped_type
					) && (
						name.find(lower_search) != std::string::npos
					)) {

						bool selectable_highlighted = lower_search == name;
						bool selectable_clicked = ImGui::Selectable(item.name.c_str(), selectable_highlighted);
						player_model_focused |= ImGui::IsItemFocused();

						if (selectable_clicked)
						{
							strncpy(player_model_name, item.name.c_str(), 64);
							player_model_open = false;
							player_model_focused = false;
						}

						if (selectable_highlighted)
						{
							ImGui::SetItemDefaultFocus();
						}
					}
				}
				ImGui::End();
			}

			player_model_open = player_model_focused;
		}

		components::button("Change Player Model", [] {
			const Hash hash = rage::joaat(player_model_name);

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




		ImGui::Separator();

		components::small_text("General");

		ImGui::BeginGroup();

		ImGui::Checkbox("God Mode", &g->self.god_mode);
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
		if (g->self.invisibility) {
			ImGui::Checkbox("Locally Visible", &g->self.local_visibility);
		}

		ImGui::Checkbox("Keep Player Clean", &g->self.clean_player);

		components::button("Clean Player", [] {
			entity::clean_ped(self::ped);
		});

		ImGui::EndGroup();

		ImGui::Separator();

		components::small_text("Proofs");

		if (ImGui::Button("Check all"))
		{
			g->self.proof_bullet = true;
			g->self.proof_fire = true;
			g->self.proof_collision = true;
			g->self.proof_melee = true;
			g->self.proof_explosion = true;
			g->self.proof_steam = true;
			g->self.proof_drown = true;
			g->self.proof_water = true;
		}

		ImGui::SameLine();

		if (ImGui::Button("Uncheck all"))
		{
			g->self.proof_bullet = false;
			g->self.proof_fire = false;
			g->self.proof_collision = false;
			g->self.proof_melee = false;
			g->self.proof_explosion = false;
			g->self.proof_steam = false;
			g->self.proof_drown = false;
			g->self.proof_water = false;
		}

		ImGui::BeginGroup();

		ImGui::Checkbox("Bullet", &g->self.proof_bullet);
		ImGui::Checkbox("Fire", &g->self.proof_fire);

		ImGui::EndGroup();
		ImGui::SameLine();
		ImGui::BeginGroup();

		ImGui::Checkbox("Collision", &g->self.proof_collision);
		ImGui::Checkbox("Melee", &g->self.proof_melee);

		ImGui::EndGroup();
		ImGui::SameLine();
		ImGui::BeginGroup();

		ImGui::Checkbox("Explosion", &g->self.proof_explosion);
		ImGui::Checkbox("Steam", &g->self.proof_steam);

		ImGui::EndGroup();
		ImGui::SameLine();
		ImGui::BeginGroup();

		ImGui::Checkbox("Drown", &g->self.proof_drown);
		ImGui::Checkbox("Water", &g->self.proof_water);

		ImGui::EndGroup();

		ImGui::Separator();

		components::small_text("Police");

		ImGui::Checkbox("Never Wanted", &g->self.never_wanted);

		if (!g->self.never_wanted)
		{
			ImGui::Checkbox("Force Wanted Level", &g->self.force_wanted_level);
			ImGui::Text("Wanted Level");
			if (
				ImGui::SliderInt("###wanted_level", &g->self.wanted_level, 0, 5) &&
				!g->self.force_wanted_level &&
				g_local_player != nullptr
				) {
				g_local_player->m_player_info->m_wanted_level = g->self.wanted_level;
			}
		}

		g->self.proof_mask = 0;
		if (g->self.god_mode)
		{
			g->self.proof_mask |= static_cast<int>(eEntityProofs::GOD);
		}
		if (g->self.proof_bullet)
		{
			g->self.proof_mask |= static_cast<int>(eEntityProofs::BULLET);
		}
		if (g->self.proof_fire)
		{
			g->self.proof_mask |= static_cast<int>(eEntityProofs::FIRE);
		}
		if (g->self.proof_collision)
		{
			g->self.proof_mask |= static_cast<int>(eEntityProofs::COLLISION);
		}
		if (g->self.proof_melee)
		{
			g->self.proof_mask |= static_cast<int>(eEntityProofs::MELEE);
		}
		if (g->self.proof_explosion)
		{
			g->self.proof_mask |= static_cast<int>(eEntityProofs::EXPLOSION);
		}
		if (g->self.proof_steam)
		{
			g->self.proof_mask |= static_cast<int>(eEntityProofs::STEAM);
		}
		if (g->self.proof_drown)
		{
			g->self.proof_mask |= static_cast<int>(eEntityProofs::DROWN);
		}
		if (g->self.proof_water)
		{
			g->self.proof_mask |= static_cast<int>(eEntityProofs::WATER);
		}
	}
}
