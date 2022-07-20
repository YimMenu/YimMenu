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
	char* Scene;

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

		if (ImGui::BeginCombo("Anims##Anims", ped::animlistID[g->self.animlist]))
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
			ImGui::EndCombo();
		}
		

		ImGui::Separator();

		components::small_text("Scenarios");

		components::button("Play Scenario", [] {
			TASK::CLEAR_PED_TASKS_IMMEDIATELY(PLAYER::PLAYER_PED_ID());
			ped::play_scenario(Scene);
		});

		ImGui::SameLine();

		components::button("Stop Scenario", [] {
			TASK::CLEAR_PED_TASKS_IMMEDIATELY(PLAYER::PLAYER_PED_ID());
			TASK::CLEAR_PED_TASKS(PLAYER::PLAYER_PED_ID());
			TASK::CLEAR_PED_SECONDARY_TASK(PLAYER::PLAYER_PED_ID());
		});

		if (ImGui::BeginCombo("Scenes##Scenes", ped::scenelist[g->self.scenelist]))
		{
			for (int i = 0; i < 81; i++)
			{
				bool itemSelected1 = g->self.scenelist == i;
				if (ImGui::Selectable(ped::scenelist[i], itemSelected1))
				{
					g->self.scenelist = i;
					if (g->self.scenelist == 0) {
						Scene = "WORLD_HUMAN_AA_COFFEE";
					}
					else if (g->self.scenelist == 1) {
						Scene = "WORLD_HUMAN_AA_SMOKE";
					}
					else if (g->self.scenelist == 2) {
						Scene = "WORLD_HUMAN_BINOCULARS";
					}
					else if (g->self.scenelist == 3) {
						Scene = "WORLD_HUMAN_BUM_FREEWAY";
					}
					else if (g->self.scenelist == 4) {
						Scene = "WORLD_HUMAN_BUM_SLUMPED";
					}
					else if (g->self.scenelist == 5) {
						Scene = "WORLD_HUMAN_BUM_STANDING";
					}
					else if (g->self.scenelist == 6) {
						Scene = "WORLD_HUMAN_BUM_WASH";
					}
					else if (g->self.scenelist == 7) {
						Scene = "WORLD_HUMAN_CAR_PARK_ATTENDANT";
					}
					else if (g->self.scenelist == 8) {
						Scene = "WORLD_HUMAN_CHEERING";
					}
					else if (g->self.scenelist == 9) {
						Scene = "WORLD_HUMAN_CLIPBOARD";
					}
					else if (g->self.scenelist == 10) {
						Scene = "WORLD_HUMAN_CONST_DRILL";
					}
					else if (g->self.scenelist == 11) {
						Scene = "WORLD_HUMAN_COP_IDLES";
					}
					else if (g->self.scenelist == 12) {
						Scene = "WORLD_HUMAN_DRINKING";
					}
					else if (g->self.scenelist == 13) {
						Scene = "WORLD_HUMAN_DRUG_DEALER";
					}
					else if (g->self.scenelist == 14) {
						Scene = "WORLD_HUMAN_DRUG_DEALER_HARD";
					}
					else if (g->self.scenelist == 15) {
						Scene = "WORLD_HUMAN_MOBILE_FILM_SHOCKING";
					}
					else if (g->self.scenelist == 16) {
						Scene = "WORLD_HUMAN_GARDENER_LEAF_BLOWER";
					}
					else if (g->self.scenelist == 17) {
						Scene = "WORLD_HUMAN_GARDENER_PLANT";
					}
					else if (g->self.scenelist == 18) {
						Scene = "WORLD_HUMAN_GOLF_PLAYER";
					}
					else if (g->self.scenelist == 19) {
						Scene = "WORLD_HUMAN_GUARD_PATROL";
					}
					else if (g->self.scenelist == 20) {
						Scene = "WORLD_HUMAN_GUARD_STAND";
					}
					else if (g->self.scenelist == 21) {
						Scene = "WORLD_HUMAN_GUARD_STAND_ARMY";
					}
					else if (g->self.scenelist == 22) {
						Scene = "WORLD_HUMAN_HAMMERING";
					}
					else if (g->self.scenelist == 23) {
						Scene = "WORLD_HUMAN_HANG_OUT_STREET";
					}
					else if (g->self.scenelist == 24) {
						Scene = "WORLD_HUMAN_HIKER";
					}
					else if (g->self.scenelist == 25) {
						Scene = "WORLD_HUMAN_HIKER_STANDING";
					}
					else if (g->self.scenelist == 26) {
						Scene = "WORLD_HUMAN_HUMAN_STATUE";
					}
					else if (g->self.scenelist == 27) {
						Scene = "WORLD_HUMAN_JANITOR";
					}
					else if (g->self.scenelist == 28) {
						Scene = "WORLD_HUMAN_JOG";
					}
					else if (g->self.scenelist == 29) {
						Scene = "WORLD_HUMAN_JOG_STANDING";
					}
					else if (g->self.scenelist == 30) {
						Scene = "WORLD_HUMAN_LEANING";
					}
					else if (g->self.scenelist == 31) {
						Scene = "WORLD_HUMAN_MAID_CLEAN";
					}
					else if (g->self.scenelist == 32) {
						Scene = "WORLD_HUMAN_MUSCLE_FLEX";
					}
					else if (g->self.scenelist == 33) {
						Scene = "WORLD_HUMAN_MUSCLE_FREE_WEIGHTS";
					}
					else if (g->self.scenelist == 34) {
						Scene = "WORLD_HUMAN_MUSICIAN";
					}
					else if (g->self.scenelist == 35) {
						Scene = "WORLD_HUMAN_PAPARAZZI";
					}
					else if (g->self.scenelist == 36) {
						Scene = "WORLD_HUMAN_PARTYING";
					}
					else if (g->self.scenelist == 37) {
						Scene = "WORLD_HUMAN_PICNIC";
					}
					else if (g->self.scenelist == 38) {
						Scene = "WORLD_HUMAN_PROSTITUTE_HIGH_CLASS";
					}
					else if (g->self.scenelist == 39) {
						Scene = "WORLD_HUMAN_PROSTITUTE_LOW_CLASS";
					}
					else if (g->self.scenelist == 40) {
						Scene = "WORLD_HUMAN_PUSH_UPS";
					}
					else if (g->self.scenelist == 41) {
						Scene = "WORLD_HUMAN_SEAT_LEDGE";
					}
					else if (g->self.scenelist == 42) {
						Scene = "WORLD_HUMAN_SEAT_LEDGE_EATING";
					}
					else if (g->self.scenelist == 43) {
						Scene = "WORLD_HUMAN_SEAT_STEPS";
					}
					else if (g->self.scenelist == 44) {
						Scene = "WORLD_HUMAN_SEAT_WALL";
					}
					else if (g->self.scenelist == 45) {
						Scene = "WORLD_HUMAN_SEAT_WALL_EATING";
					}
					else if (g->self.scenelist == 46) {
						Scene = "WORLD_HUMAN_SECURITY_SHINE_TORCH";
					}
					else if (g->self.scenelist == 47) {
						Scene = "WORLD_HUMAN_SIT_UPS";
					}
					else if (g->self.scenelist == 48) {
						Scene = "WORLD_HUMAN_SMOKING";
					}
					else if (g->self.scenelist == 49) {
						Scene = "WORLD_HUMAN_SMOKING_POT";
					}
					else if (g->self.scenelist == 50) {
						Scene = "WORLD_HUMAN_STAND_FIRE";
					}
					else if (g->self.scenelist == 51) {
						Scene = "WORLD_HUMAN_STAND_FISHING";
					}
					else if (g->self.scenelist == 52) {
						Scene = "WORLD_HUMAN_STAND_IMPATIENT";
					}
					else if (g->self.scenelist == 53) {
						Scene = "WORLD_HUMAN_STAND_IMPATIENT_UPRIGHT";
					}
					else if (g->self.scenelist == 54) {
						Scene = "WORLD_HUMAN_STAND_MOBILE";
					}
					else if (g->self.scenelist == 55) {
						Scene = "WORLD_HUMAN_STAND_MOBILE_UPRIGHT";
					}
					else if (g->self.scenelist == 56) {
						Scene = "WORLD_HUMAN_STRIP_WATCH_STAND";
					}
					else if (g->self.scenelist == 57) {
						Scene = "WORLD_HUMAN_STUPOR";
					}
					else if (g->self.scenelist == 58) {
						Scene = "WORLD_HUMAN_SUNBATHE";
					}
					else if (g->self.scenelist == 59) {
						Scene = "WORLD_HUMAN_SUNBATHE_BACK";
					}
					else if (g->self.scenelist == 60) {
						Scene = "WORLD_HUMAN_TENNIS_PLAYER";
					}
					else if (g->self.scenelist == 61) {
						Scene = "WORLD_HUMAN_TOURIST_MAP";
					}
					else if (g->self.scenelist == 62) {
						Scene = "WORLD_HUMAN_TOURIST_MOBILE";
					}
					else if (g->self.scenelist == 63) {
						Scene = "WORLD_HUMAN_WELDING";
					}
					else if (g->self.scenelist == 64) {
						Scene = "WORLD_HUMAN_WINDOW_SHOP_BROWSE";
					}
					else if (g->self.scenelist == 65) {
						Scene = "WORLD_HUMAN_YOGA";
					}
					else if (g->self.scenelist == 66) {
						Scene = "PROP_HUMAN_ATM";
					}
					else if (g->self.scenelist == 67) {
						Scene = "PROP_HUMAN_BBQ";
					}
					else if (g->self.scenelist == 68) {
						Scene = "PROP_HUMAN_BUM_BIN";
					}
					else if (g->self.scenelist == 69) {
						Scene = "PROP_HUMAN_BUM_SHOPPING_CART";
					}
					else if (g->self.scenelist == 70) {
						Scene = "PROP_HUMAN_MUSCLE_CHIN_UPS_ARMY";
					}
					else if (g->self.scenelist == 71) {
						Scene = "PROP_HUMAN_PARKING_METER";
					}
					else if (g->self.scenelist == 72) {
						Scene = "PROP_HUMAN_SEAT_BAR";
					}
					else if (g->self.scenelist == 73) {
						Scene = "PROP_HUMAN_SEAT_BENCH";
					}
					else if (g->self.scenelist == 74) {
						Scene = "PROP_HUMAN_SEAT_MUSCLE_BENCH_PRESS";
					}
					else if (g->self.scenelist == 75) {
						Scene = "PROP_HUMAN_SEAT_STRIP_WATCH";
					}
					else if (g->self.scenelist == 76) {
						Scene = "CODE_HUMAN_MEDIC_KNEEL";
					}
					else if (g->self.scenelist == 77) {
						Scene = "CODE_HUMAN_MEDIC_TEND_TO_DEAD";
					}
					else if (g->self.scenelist == 78) {
						Scene = "CODE_HUMAN_MEDIC_TIME_OF_DEATH";
					}
					else if (g->self.scenelist == 79) {
						Scene = "CODE_HUMAN_POLICE_CROWD_CONTROL";
					}
					else if (g->self.scenelist == 80) {
						Scene = "CODE_HUMAN_POLICE_INVESTIGATE";
					}
				}
				if (itemSelected1)
				{
					ImGui::SetItemDefaultFocus();
				}
			}
			ImGui::EndCombo();
		}
	}
}