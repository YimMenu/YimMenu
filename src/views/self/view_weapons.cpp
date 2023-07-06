#include "core/data/bullet_impact_types.hpp"
#include "core/data/custom_weapons.hpp"
#include "core/data/special_ammo_types.hpp"
#include "fiber_pool.hpp"
#include "gta/joaat.hpp"
#include "natives.hpp"
#include "pointers.hpp"
#include "services/gta_data/gta_data_service.hpp"
#include "views/view.hpp"

namespace big
{
	void view::weapons()
	{
		ImGui::SeparatorText("AMMO"_T.data());

		ImGui::BeginGroup();

		components::command_checkbox<"infammo">();
		components::command_checkbox<"alwaysfullammo">();
		components::command_checkbox<"infclip">();
		components::command_checkbox<"infrange">();
		ImGui::Checkbox("Allow Weapons In Interiors", &g.weapons.interior_weapon);

		ImGui::EndGroup();
		ImGui::SameLine();
		ImGui::BeginGroup();

		ImGui::Checkbox("Increase C4 Limit (Max = 50)", &g.weapons.increased_c4_limit);
		ImGui::Checkbox("Increase Flare Limit (Max = 50)", &g.weapons.increased_flare_limit);

		components::command_checkbox<"rapidfire">();

		ImGui::Checkbox("ENABLE_SPECIAL_AMMO"_T.data(), &g.weapons.ammo_special.toggle);
		components::options_modal("Special ammo", [] {
			eAmmoSpecialType selected_ammo   = g.weapons.ammo_special.type;
			eExplosionTag selected_explosion = g.weapons.ammo_special.explosion_tag;

			if (ImGui::BeginCombo("SPECIAL_AMMO"_T.data(), SPECIAL_AMMOS[(int)selected_ammo].name))
			{
				for (const auto& special_ammo : SPECIAL_AMMOS)
				{
					if (ImGui::Selectable(special_ammo.name, special_ammo.type == selected_ammo))
					{
						g.weapons.ammo_special.type = special_ammo.type;
					}

					if (special_ammo.type == selected_ammo)
					{
						ImGui::SetItemDefaultFocus();
					}
				}
				ImGui::EndCombo();
			}

			if (ImGui::BeginCombo("BULLET_IMPACT"_T.data(), BULLET_IMPACTS[selected_explosion]))
			{
				for (const auto& [type, name] : BULLET_IMPACTS)
				{
					if (ImGui::Selectable(name, type == selected_explosion))
					{
						g.weapons.ammo_special.explosion_tag = type;
					}

					if (type == selected_explosion)
					{
						ImGui::SetItemDefaultFocus();
					}
				}

				ImGui::EndCombo();
			}
		});

		ImGui::EndGroup();

		ImGui::SeparatorText("MISC"_T.data());

		components::command_checkbox<"norecoil">();
		ImGui::SameLine();
		components::command_checkbox<"nospread">();

		components::button("GET_ALL_WEAPONS"_T, [] {
			for (const auto& [_, weapon] : g_gta_data_service->weapons())
			{
				WEAPON::GIVE_DELAYED_WEAPON_TO_PED(self::ped, weapon.m_hash, 9999, false);
			}

			constexpr auto parachute_hash = RAGE_JOAAT("GADGET_PARACHUTE");
			WEAPON::GIVE_DELAYED_WEAPON_TO_PED(self::ped, parachute_hash, 0, true);
		});
		ImGui::SameLine();
		components::button("REMOVE_CUR_WEAPON"_T, [] {
			Hash weaponHash;
			WEAPON::GET_CURRENT_PED_WEAPON(self::ped, &weaponHash, 1);
			if (weaponHash != RAGE_JOAAT("WEAPON_UNARMED"))
			{
				WEAPON::REMOVE_WEAPON_FROM_PED(self::ped, weaponHash);
			}
		});

		components::command_checkbox<"incrdamage">();
		ImGui::InputFloat("Damage", &g.weapons.increased_damage, .1, 10, "%.1f");

		ImGui::SeparatorText("CUSTOM_WEAPONS"_T.data());

		ImGui::Checkbox("Custom Gun only fires when weapon is out", &g.self.custom_weapon_stop);
		CustomWeapon selected = g.weapons.custom_weapon;

		if (ImGui::BeginCombo("WEAPON"_T.data(), custom_weapons[(int)selected].name))
		{
			for (const custom_weapon& weapon : custom_weapons)
			{
				if (ImGui::Selectable(weapon.name, weapon.id == selected))
				{
					g.weapons.custom_weapon = weapon.id;
				}

				if (weapon.id == selected)
				{
					ImGui::SetItemDefaultFocus();
				}
			}

			ImGui::EndCombo();
		}

		switch (selected)
		{
		case CustomWeapon::GRAVITY_GUN:
			ImGui::Checkbox("Launch on release", &g.weapons.gravity_gun.launch_on_release);
			break;
		case CustomWeapon::VEHICLE_GUN:
			// this some ugly ass looking code
			static char vehicle_gun[12];
			std::memcpy(vehicle_gun, g.weapons.vehicle_gun_model.c_str(), 12);
			if (ImGui::InputTextWithHint("SHOOTING_MODEL"_T.data(), "NAME_VEHICLE_MODEL"_T.data(), vehicle_gun, sizeof(vehicle_gun)))
			{
				g.weapons.vehicle_gun_model = vehicle_gun;
			}
			if (ImGui::IsItemActive())
			{
				g_fiber_pool->queue_job([] {
					PAD::DISABLE_ALL_CONTROL_ACTIONS(0);
				});
			}

			break;
		}

		ImGui::SeparatorText("Aim Assistance");
		components::command_checkbox<"triggerbot">();
		ImGui::SameLine();
		components::command_checkbox<"aimbot">();

		if (g.weapons.aimbot.enable)
		{
			components::command_checkbox<"aimatplayer">();
			ImGui::SameLine();
			components::command_checkbox<"aimatnpc">();
			ImGui::SameLine();
			components::command_checkbox<"aimatpolice">();
			ImGui::SameLine();
			components::command_checkbox<"aimatenemy">();

			components::command_checkbox<"smoothing">();
			if (g.weapons.aimbot.smoothing)
			{
				ImGui::SameLine();
				ImGui::PushItemWidth(220);
				ImGui::SliderFloat("Speed", &g.weapons.aimbot.smoothing_speed, 1.f, 12.f, "%.1f");
				ImGui::PopItemWidth();
			}
			ImGui::PushItemWidth(350);
			ImGui::SliderFloat("FOV", &g.weapons.aimbot.fov, 1.f, 360.f, "%.0f");
			ImGui::SliderFloat("Distance", &g.weapons.aimbot.distance, 1.f, 1000.f, "%.0f");
			ImGui::PopItemWidth();
		}

		ImGui::SeparatorText("Ammunation");
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
					selected_weapon					= weapon.second.m_display_name;
					selected_weapon_hash			= weapon.second.m_hash;
					selected_weapon_attachment_hash = {};
					selected_weapon_attachment.clear();
				}
				if (is_selected)
					ImGui::SetItemDefaultFocus();
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
			auto weapon = g_gta_data_service->weapon_by_hash(selected_weapon_hash);
			if (!weapon.m_attachments.empty())
			{
				for (std::string attachment : weapon.m_attachments)
				{
					auto attachment_component   = g_gta_data_service->weapon_component_by_name(attachment);
					std::string attachment_name = attachment_component.m_display_name;
					Hash attachment_hash        = attachment_component.m_hash;
					if (attachment_hash == NULL)
					{
						attachment_name = attachment;
						attachment_hash = rage::joaat(attachment);
					}
					bool is_selected = attachment_hash == selected_weapon_attachment_hash;
					std::string display_name = attachment_name.append("##").append(std::to_string(attachment_hash));
					if (ImGui::Selectable(display_name.c_str(), is_selected, ImGuiSelectableFlags_None))
					{
						selected_weapon_attachment      = attachment_name;
						selected_weapon_attachment_hash = attachment_hash;
					}
					if (is_selected)
						ImGui::SetItemDefaultFocus();
				}
			}

			ImGui::EndCombo();
		}
		ImGui::SameLine();
		components::button("Add to Weapon", [] {
			WEAPON::GIVE_WEAPON_COMPONENT_TO_PED(self::ped, selected_weapon_hash, selected_weapon_attachment_hash);
		});
		ImGui::SameLine();
		components::button("Remove from Weapon", [] {
			WEAPON::REMOVE_WEAPON_COMPONENT_FROM_PED(self::ped, selected_weapon_hash, selected_weapon_attachment_hash);
		});
		ImGui::PopItemWidth();

		static const char* default_tints[]{"Black tint", "Green tint", "Gold tint", "Pink tint", "Army tint", "LSPD tint", "Orange tint", "Platinum tint"};
		static const char* mk2_tints[]{"Classic Black", "Classic Grey", "Classic Two - Tone", "Classic White", "Classic Beige", "Classic Green", "Classic Blue", "Classic Earth", "Classic Brown & Black", "Red Contrast", "Blue Contrast", "Yellow Contrast", "Orange Contrast", "Bold Pink", "Bold Purple & Yellow", "Bold Orange", "Bold Green & Purple", "Bold Red Features", "Bold Green Features", "Bold Cyan Features", "Bold Yellow Features", "Bold Red & White", "Bold Blue & White", "Metallic Gold", "Metallic Platinum", "Metallic Grey & Lilac", "Metallic Purple & Lime", "Metallic Red", "Metallic Green", "Metallic Blue", "Metallic White & Aqua", "Metallic Red & Yellow"};
		static int tint;

		if (selected_weapon.ends_with("Mk II"))
		{
			ImGui::Combo("Tints", &tint, mk2_tints, IM_ARRAYSIZE(mk2_tints));
		}
		else
		{
			ImGui::Combo("Tints", &tint, default_tints, IM_ARRAYSIZE(default_tints));
		}
		ImGui::SameLine();
		if (ImGui::Button("Apply"))
		{
			g_fiber_pool->queue_job([] {
				WEAPON::SET_PED_WEAPON_TINT_INDEX(self::ped, selected_weapon_hash, tint);
			});
		}
	}
}
