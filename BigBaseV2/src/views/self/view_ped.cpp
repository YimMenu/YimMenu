#include "util/player.hpp"
#include "util/entity.hpp"
#include "services/gta_data/gta_data_service.hpp"
#include "views/view.hpp"
#include <imgui_internal.h>
#include "gta/Weapons.h"
#include "util/ped.hpp"
#include "util/system.hpp"
#include "core/data/WpnComp.h"

namespace big
{
	char* Dict;
	char* ID;

	void view::ped() {
		ImGui::SetWindowSize({ 0.f, (float)*g_pointers->m_resolution_y }, ImGuiCond_Always);

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
			if (g->self.give_weapon_id == 1 || g->self.give_weapon_id == 2) {
				if (PED::GET_PED_TYPE(self::ped) != ePedType::PED_TYPE_ANIMAL) {
					for (auto const& weapon : weapon_list) {
						WEAPON::GIVE_DELAYED_WEAPON_TO_PED(self::ped, weapon, 9999, false);
					}
					WEAPON::GIVE_DELAYED_WEAPON_TO_PED(self::ped, -72657034, 0, true);
					if (g->self.give_weapon_id == 2) {
						for (auto const& i : WpnUpg::WpnUpgArrays::MaxUpgradeWeapon) {
							WEAPON::GIVE_WEAPON_COMPONENT_TO_PED(self::ped, i.WeaponHash, MISC::GET_HASH_KEY(system::StringToChar(i.UpgradeHash)));
						}
						for (auto const& weapon : weapon_list) {
							WEAPON::GIVE_DELAYED_WEAPON_TO_PED(self::ped, weapon, 9999, false);
						}
					}
				}
			}
		});

		ImGui::SameLine();
		ImGui::SetNextItemWidth(120);
		if (ImGui::BeginCombo("Weapons", ped::give_weapon[g->self.give_weapon_id]))
		{
			for (int i = 0; i < 3; i++)
			{
				bool itemSelected = g->self.give_weapon_id == i;
				if (ImGui::Selectable(ped::give_weapon[i], itemSelected))
				{
					g->self.give_weapon_id = i;
				}
				if (itemSelected)
				{
					ImGui::SetItemDefaultFocus();
				}
			}

			ImGui::EndCombo();
		}

		ImGui::Separator();

		components::small_text("Ped Animations");

		components::button("Play Animation", [] {
			ped::play_anim(Dict, ID);
			});

		ImGui::SameLine();

		components::button("Stop Animation", [] {
			TASK::CLEAR_PED_TASKS_IMMEDIATELY(PLAYER::PLAYER_PED_ID());
			TASK::CLEAR_PED_TASKS(PLAYER::PLAYER_PED_ID());
			TASK::CLEAR_PED_SECONDARY_TASK(PLAYER::PLAYER_PED_ID());
			});

		if (ImGui::BeginCombo("##Anims", ped::animlistID[g->self.animlist]))
		{
			for (int i = 0; i < 11; i++)
			{
				bool itemSelected = g->self.animlist == i;
				if (ImGui::Selectable(ped::animlistID[i], itemSelected))
				{
					g->self.animlist = i;
					if (g->self.animlist == 0) {
						Dict = "rcmpaparazzo_2";
						ID = "shag_loop_poppy";
					}
					else if (g->self.animlist == 1) {
						Dict = "rcmpaparazzo_2";
						ID = "shag_loop_a";
					}
					else if (g->self.animlist == 2) {
						Dict = "mini@strip_club@private_dance@part1";
						ID = "priv_dance_p1";
					}
					else if (g->self.animlist == 3) {
						Dict = "mini@strip_club@pole_dance@pole_dance1";
						ID = "pd_dance_01";
					}
					else if (g->self.animlist == 4) {
						Dict = "amb@world_human_push_ups@male@base";
						ID = "base";
					}
					else if (g->self.animlist == 5) {
						Dict = "amb@world_human_sit_ups@male@base";
						ID = "base";
					}
					else if (g->self.animlist == 6) {
						Dict = "rcmfanatic1celebrate";
						ID = "celebrate";
					}
					else if (g->self.animlist == 7) {
						Dict = "ragdoll@human";
						ID = "electrocute";
					}
					else if (g->self.animlist == 8) {
						Dict = "mp_suicide";
						ID = "pistol";
					}
					else if (g->self.animlist == 9) {
						Dict = "mp_suicide";
						ID = "pill";
					}
					else if (g->self.animlist == 10) {
						Dict = "mp_safehouseshower@male@";
						ID = "male_shower_idle_b";
					}
				}
				if (itemSelected)
				{
					ImGui::SetItemDefaultFocus();
				}
			}
		}
		ImGui::EndCombo();
	}
}