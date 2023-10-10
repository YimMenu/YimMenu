
#include "core/settings.hpp"
#include "gta/joaat.hpp"
#include "natives.hpp"
#include "services/gta_data/gta_data_service.hpp"
#include "services/persist_weapons/persist_weapons.hpp"
#include "views/view.hpp"

namespace big
{
	void view::weapons()
	{
		components::command_button<"fillammo">();

		ImGui::SeparatorText("General");
		{
			ImGui::BeginGroup();
			{
				components::command_checkbox<"infammo">();
				components::command_checkbox<"infclip">();
			}
			ImGui::EndGroup();
			ImGui::SameLine();
			ImGui::BeginGroup();
			{
				components::command_checkbox<"rapidfire">();
			}
			ImGui::EndGroup();
		}

		ImGui::SeparatorText("Misc");
		{
			components::command_checkbox<"aimbot">();
			ImGui::SetNextItemWidth(350);
			ImGui::SliderFloat("Distance", &g.weapons.aimbot.distance, 1.f, 1000.f, "%.0f");
			ImGui::Spacing();
			components::button("Get All Weapons", [] {
				for (const auto& [_, weapon] : g_gta_data_service->weapons())
				{
					WEAPON::GIVE_DELAYED_WEAPON_TO_PED(self::ped, weapon.m_hash, 9999, false);
				}

				constexpr auto parachute_hash = RAGE_JOAAT("GADGET_PARACHUTE");
				WEAPON::GIVE_DELAYED_WEAPON_TO_PED(self::ped, parachute_hash, 0, true);
			});
			ImGui::SameLine();
			components::button("Remove Current Weapon", [] {
				Hash weaponHash;
				WEAPON::GET_CURRENT_PED_WEAPON(self::ped, &weaponHash, 1);
				if (weaponHash != RAGE_JOAAT("WEAPON_UNARMED"))
				{
					WEAPON::REMOVE_WEAPON_FROM_PED(self::ped, weaponHash);
				}
			});
		}

		ImGui::Spacing();

		if (ImGui::CollapsingHeader("Ammunation"))
		{
			static Hash selected_weapon_hash, selected_weapon_attachment_hash{};
			static std::string selected_weapon, selected_weapon_attachment;
			ImGui::PushItemWidth(300);
			if (ImGui::BeginCombo("Weapons", selected_weapon.c_str()))
			{
				for (auto& weapon : g_gta_data_service->weapons())
				{
					bool is_selected = weapon.second.m_hash == selected_weapon_hash;
					if (weapon.second.m_display_name != "NULL" && ImGui::Selectable(weapon.second.m_display_name.c_str(), is_selected, ImGuiSelectableFlags_None))
					{
						selected_weapon                 = weapon.second.m_display_name;
						selected_weapon_hash            = weapon.second.m_hash;
						selected_weapon_attachment_hash = {};
						selected_weapon_attachment.clear();
					}
					if (is_selected)
					{
						ImGui::SetItemDefaultFocus();
					}
				}
				ImGui::EndCombo();
			}
			ImGui::PopItemWidth();
			ImGui::SameLine();
			components::button("Give Weapon", [] {
				WEAPON::GIVE_WEAPON_TO_PED(self::ped, selected_weapon_hash, 9999, false, true);
			});
			ImGui::SameLine();
			components::button("Remove Weapon", [] {
				WEAPON::REMOVE_WEAPON_FROM_PED(self::ped, selected_weapon_hash);
			});

			ImGui::PushItemWidth(250);
			if (ImGui::BeginCombo("Attachments", selected_weapon_attachment.c_str()))
			{
				weapon_item weapon = g_gta_data_service->weapon_by_hash(selected_weapon_hash);
				if (!weapon.m_attachments.empty())
				{
					for (std::string attachment : weapon.m_attachments)
					{
						weapon_component attachment_component = g_gta_data_service->weapon_component_by_name(attachment);
						std::string attachment_name = attachment_component.m_display_name;
						Hash attachment_hash        = attachment_component.m_hash;
						if (attachment_hash == NULL)
						{
							attachment_name = attachment;
							attachment_hash = rage::joaat(attachment);
						}
						bool is_selected         = attachment_hash == selected_weapon_attachment_hash;
						std::string display_name = attachment_name.append("##").append(std::to_string(attachment_hash));
						if (ImGui::Selectable(display_name.c_str(), is_selected, ImGuiSelectableFlags_None))
						{
							selected_weapon_attachment      = attachment_name;
							selected_weapon_attachment_hash = attachment_hash;
						}
						if (is_selected)
						{
							ImGui::SetItemDefaultFocus();
						}
					}
				}

				ImGui::EndCombo();
			}
			ImGui::PopItemWidth();
			ImGui::SameLine();
			components::button("Add to Weapon", [] {
				WEAPON::GIVE_WEAPON_COMPONENT_TO_PED(self::ped, selected_weapon_hash, selected_weapon_attachment_hash);
			});
			ImGui::SameLine();
			components::button("Remove from Weapon", [] {
				WEAPON::REMOVE_WEAPON_COMPONENT_FROM_PED(self::ped, selected_weapon_hash, selected_weapon_attachment_hash);
			});
		}

		ImGui::Spacing();

		if (ImGui::CollapsingHeader("Persist Weapons"))
		{
			static std::string selected_loadout = g.persist_weapons.weapon_loadout_file;
			ImGui::PushItemWidth(250);
			if (ImGui::BeginListBox("Saved Loadouts", ImVec2(200, 200)))
			{
				for (std::string filename : persist_weapons::list_weapon_loadouts())
				{
					if (components::selectable(filename, filename == selected_loadout))
					{
						selected_loadout = filename;
					}
				}
				ImGui::EndListBox();
			}
			ImGui::SameLine();
			ImGui::BeginGroup();
			static std::string input_file_name;
			components::input_text_with_hint("Weapon Loadout Filename", "Loadout Name", input_file_name);
			components::button("Save Loadout", [] {
				persist_weapons::save_weapons(input_file_name);
				input_file_name.clear();
			});
			ImGui::SameLine();
			components::button("Load Loadout", [] {
				persist_weapons::give_player_loadout(selected_loadout);
			});
			ImGui::SameLine();
			ImGui::Text(std::format("Current Loadout: {}:", g.persist_weapons.weapon_loadout_file).data());
			ImGui::EndGroup();
			ImGui::PopItemWidth();
		}
	}
}
