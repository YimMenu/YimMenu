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
	}
}