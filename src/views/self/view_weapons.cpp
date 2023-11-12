#include "core/data/weapons.hpp"
#include "gta/weapons.hpp"
#include "natives.hpp"
#include "rage/joaat.hpp"
#include "services/gta_data/gta_data_service.hpp"
#include "services/gta_data/weapon_item.hpp"
#include "services/persist_weapons/persist_weapons.hpp"
#include "util/strings.hpp"
#include "views/view.hpp"

inline std::map<std::string, big::weapon_item> filter_weapons_map(const std::map<std::string, big::weapon_item>& inputMap, const std::string& searchString)
{
	std::map<std::string, big::weapon_item> filteredMap;
	std::string lowercaseSearchString = toLowercase(searchString);
	for (auto pair : inputMap)
		if (std::string lowercaseStr = toLowercase(pair.second.m_display_name); lowercaseStr.find(lowercaseSearchString) != std::string::npos)
			filteredMap[pair.first] = pair.second;
	return filteredMap;
}

namespace big
{
	static inline void render_general()
	{
		ImGui::BeginGroup();
		{
			ImGui::BeginDisabled(g_weapons.rapid_fire);
			components::command_checkbox<"infammo">();

			components::command_checkbox<"infclip">();
			ImGui::EndDisabled();

			ImGui::BeginDisabled(g_weapons.infinite_ammo || g_weapons.infinite_mag);
			components::command_checkbox<"rapidfire">();
			ImGui::EndDisabled();
		}
		ImGui::EndGroup();
		ImGui::SameLine();
		ImGui::BeginGroup();
		{
			components::command_checkbox<"norecoil">();

			components::command_checkbox<"nospread">();

			components::command_checkbox<"damage_modifier">();
			if (g_weapons.damage_modifier)
			{
				ImGui::SetNextItemWidth(200);
				ImGui::SliderInt("###damage_modifier_v", &g_weapons.damage_modifier_v, 2, 8);
			}
		}
		ImGui::EndGroup();
	}

	static inline void render_misc()
	{
		components::command_checkbox<"aimbot">();
		ImGui::SetNextItemWidth(350);
		ImGui::SliderFloat("Distance", &g_weapons.aimbot.distance, 1.f, 1000.f, "%.0f");

		ImGui::Spacing();

		components::button("Give Parachute", [] {
			WEAPON::GIVE_DELAYED_WEAPON_TO_PED(self::ped, GADGET_PARACHUTE, 0, true);
		});
		ImGui::SameLine();
		components::button("Remove Current Weapon", [] {
			Hash weaponHash;
			WEAPON::GET_CURRENT_PED_WEAPON(self::ped, &weaponHash, 1);
			if (weaponHash != RAGE_JOAAT("WEAPON_UNARMED"))
				WEAPON::REMOVE_WEAPON_FROM_PED(self::ped, weaponHash);
		});
	}

	static inline void render_ammunation()
	{
		if (ImGui::CollapsingHeader("Ammunation"))
		{
			static Hash selected_weapon_hash;
			static std::string selected_weapon, search_weapon_name;
			static std::map<std::string, big::weapon_item> searched_weapons;

			ImGui::SetNextItemWidth(300);
			if (components::input_text_with_hint("###search_weapon_name", "search name", search_weapon_name))
				searched_weapons.clear();

			if (ImGui::BeginListBox("###weaponsList", {300, 100}))
			{
				std::map<std::string, big::weapon_item> temp_objs;

				if (searched_weapons.size())
					temp_objs = searched_weapons;
				else if (search_weapon_name.length() > 0)
					temp_objs = searched_weapons = filter_weapons_map(g_gta_data_service->weapons(), search_weapon_name);

				for (auto& weapon : (search_weapon_name.length() > 0 ? temp_objs : g_gta_data_service->weapons()))
				{
					if (weapon.second.m_display_name != "NULL"
					    && ImGui::Selectable(weapon.second.m_display_name.c_str(), weapon.second.m_hash == selected_weapon_hash))
					{
						selected_weapon      = weapon.second.m_display_name;
						selected_weapon_hash = weapon.second.m_hash;
					}
				}
				ImGui::EndListBox();
			}
			ImGui::SameLine();
			components::button("Give Weapon", [] {
				WEAPON::GIVE_WEAPON_TO_PED(self::ped, selected_weapon_hash, 9999, false, true);
			});
			ImGui::SameLine();
			components::button("Remove Weapon", [] {
				WEAPON::REMOVE_WEAPON_FROM_PED(self::ped, selected_weapon_hash);
			});
		}
	}

	static inline void render_persist_weapons()
	{
		if (ImGui::CollapsingHeader("Persist Weapons"))
		{
			static std::string selected_loadout;

			if (ImGui::BeginListBox("###SavedLoadouts", ImVec2(200, 100)))
			{
				for (std::string filename : persist_weapons::list_weapon_loadouts())
					if (components::selectable(filename, filename == selected_loadout))
						selected_loadout = filename;
				ImGui::EndListBox();
			}
			ImGui::SameLine();
			ImGui::BeginGroup();
			{
				components::button("Load Selected Loadout", [] {
					persist_weapons::give_player_loadout(selected_loadout);
				});

				ImGui::Spacing();

				static std::string input_file_name;

				ImGui::SetNextItemWidth(200);
				components::input_text_with_hint("###loadoutFilename", "Loadout Name", input_file_name);
				ImGui::SameLine();
				components::button("Save Loadout", [] {
					persist_weapons::save_weapons(input_file_name);
					input_file_name.clear();
				});
			}
			ImGui::EndGroup();
		}
	}

	void view::weapons()
	{
		components::command_button<"fillammo">();

		ImGui::SeparatorText("General");

		render_general();

		ImGui::SeparatorText("Misc");

		render_misc();

		ImGui::Spacing();

		render_ammunation();

		ImGui::Spacing();

		render_persist_weapons();
	}
}
