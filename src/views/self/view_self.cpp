#include "core/data/hud_component_names.hpp"
#include "core/data/ptfx_effects.hpp"
#include "fiber_pool.hpp"
#include "services/orbital_drone/orbital_drone.hpp"
#include "util/entity.hpp"
#include "util/local_player.hpp"
#include "util/scripts.hpp"
#include "views/view.hpp"

#include <script/globals/GPBD_FM_3.hpp>

namespace big
{
	void view::self()
	{
		components::command_button<"suicide">();
		ImGui::SameLine();
		components::command_button<"heal">();
		ImGui::SameLine();
		components::command_button<"fillsnacks">();
		ImGui::SameLine();
		components::command_button<"skipcutscene">();
		ImGui::SameLine();
		components::command_button<"clean">();
		ImGui::SameLine();
		components::command_button<"fillammo">();

		ImGui::SeparatorText("GENERAL"_T.data());

		ImGui::BeginGroup();

		components::command_checkbox<"godmode">();
		components::command_checkbox<"otr">();
		if (g.self.off_radar && scr_globals::gpbd_fm_3.as<GPBD_FM_3*>()->Entries[self::id].BossGoon.Boss == self::id)
			components::command_checkbox<"ghostorg">();
		components::command_checkbox<"freecam">();
		components::command_checkbox<"nophone">();
		components::command_checkbox<"infoxy">();
		components::command_checkbox<"fastrespawn">();
		components::command_checkbox<"invis">();
		if (g.self.invisibility)
			components::command_checkbox<"localvis">(); // TODO: does nothing in SP

		ImGui::EndGroup();
		ImGui::SameLine();
		ImGui::BeginGroup();

		components::command_checkbox<"noclip">();
		components::options_modal("Noclip", [] {
			ImGui::Separator();

			ImGui::BeginGroup();
			ImGui::Text("NOCLIP_AIM_SPEED_MULTIPLIER"_T.data());
			ImGui::SliderFloat("##noclipaimspeedmult", &g.self.noclip_aim_speed_multiplier, 0.1f, 1.0f);
			ImGui::Text("NOCLIP_SPEED_MULTIPLIER"_T.data());
			ImGui::SliderFloat("##noclipspeedmult", &g.self.noclip_speed_multiplier, 1.f, 100.f);
			ImGui::EndGroup();
		});

		components::command_checkbox<"noragdoll">();
		components::command_checkbox<"fastrun">();
		components::command_checkbox<"noidlekick">();
		components::command_checkbox<"walkunder">();
		if (!g.self.super_jump)
			components::command_checkbox<"beastjump">();
		if (!g.self.beast_jump)
			components::command_checkbox<"superjump">();
		components::command_checkbox<"nocollision">();

		ImGui::EndGroup();
		ImGui::SameLine();
		ImGui::BeginGroup();

		components::command_checkbox<"cleanloop">();
		components::command_checkbox<"mobileradio">();
		components::command_checkbox<"superman">();

		ImGui::Checkbox("DANCE_MODE"_T.data(), &g.self.dance_mode);

		components::command_checkbox<"orbitaldrone">();
		components::options_modal("Orbital drone", [] {
			ImGui::Separator();
			ImGui::BeginGroup();
			ImGui::Text("ORBITAL_DRONE_USAGE_DESCR"_T.data());
			ImGui::EndGroup();
			ImGui::Separator();

			ImGui::BeginGroup();
			ImGui::Checkbox("ORBITAL_DRONE_AUTO_LOCK_ON_PLAYER"_T.data(), &g.world.orbital_drone.detect_player);
			if (ImGui::IsItemHovered())
			{
				ImGui::BeginTooltip();
				ImGui::Text("ORBITAL_DRONE_AUTO_LOCK_ON_PLAYER_TOOLTIP"_T.data());
				ImGui::EndTooltip();
			}
			ImGui::Text("ORBITAL_DRONE_HIGH_SPEED_MULTIPLIER"_T.data());
			ImGui::SliderFloat("##fastspeed", &g.world.orbital_drone.nav_ovverride_fast, 1.f, 10.f);
			ImGui::Text("ORBITAL_DRONE_LOW_SPEED_MULTIPLIER"_T.data());
			ImGui::SliderFloat("##slowspeed", &g.world.orbital_drone.nav_ovverride_slow, 0.f, 1.f);
			ImGui::EndGroup();
		});

		ImGui::Checkbox("SETTINGS_CONTEXT_MENU"_T.data(), &g.context_menu.enabled);
		components::options_modal("SETTINGS_CONTEXT_MENU"_T.data(), [] {
			ImGui::Text("SETTINGS_CONTEXT_MENU_ENTITY_TYPES"_T.data());
			ImGui::CheckboxFlags("SETTINGS_CONTEXT_MENU_ENTITY_TYPE_OBJECT"_T.data(),
			    reinterpret_cast<int*>(&g.context_menu.allowed_entity_types),
			    static_cast<int>(ContextEntityType::OBJECT));
			ImGui::SameLine();
			ImGui::CheckboxFlags("SETTINGS_CONTEXT_MENU_ENTITY_TYPE_PED"_T.data(),
			    reinterpret_cast<int*>(&g.context_menu.allowed_entity_types),
			    static_cast<int>(ContextEntityType::PED));
			ImGui::SameLine();
			ImGui::CheckboxFlags("SETTINGS_CONTEXT_MENU_ENTITY_TYPE_PLAYER"_T.data(),
			    reinterpret_cast<int*>(&g.context_menu.allowed_entity_types),
			    static_cast<int>(ContextEntityType::PLAYER));
			ImGui::SameLine();
			ImGui::CheckboxFlags("SETTINGS_CONTEXT_MENU_ENTITY_TYPE_VEHICLE"_T.data(),
			    reinterpret_cast<int*>(&g.context_menu.allowed_entity_types),
			    static_cast<int>(ContextEntityType::VEHICLE));

			static ImVec4 selected_option_color = ImGui::ColorConvertU32ToFloat4(g.context_menu.selected_option_color);
			ImGui::Text("SETTINGS_CONTEXT_MENU_COLOR"_T.data());
			if (ImGui::ColorEdit4("###BSelected Option Color##cm_picker", (float*)&selected_option_color, ImGuiColorEditFlags_InputRGB | ImGuiColorEditFlags_NoSidePreview))
			{
				g.context_menu.selected_option_color = ImGui::ColorConvertFloat4ToU32(selected_option_color);
			}

			ImGui::Checkbox("SETTINGS_CONTEXT_MENU_BOUNDING_BOX"_T.data(), &g.context_menu.bounding_box_enabled);

			if (g.context_menu.bounding_box_enabled)
			{
				static ImVec4 bounding_box_color = ImGui::ColorConvertU32ToFloat4(g.context_menu.bounding_box_color);
				ImGui::Text("SETTINGS_CONTEXT_MENU_BOUNDING_BOX_COLOR"_T.data());
				if (ImGui::ColorEdit4("###Bounding Box Color##cm_picker", (float*)&bounding_box_color, ImGuiColorEditFlags_InputRGB | ImGuiColorEditFlags_NoSidePreview))
				{
					g.context_menu.bounding_box_color = ImGui::ColorConvertFloat4ToU32(bounding_box_color);
				}
			}
		});

		components::command_checkbox<"ptfx">();
		components::options_modal("PTFX", [] {
			ImGui::SliderFloat("PTFX Size", &g.self.ptfx_effects.size, 0.1f, 2.f);
			if (ImGui::BeginCombo("Asset", ptfx_named[g.self.ptfx_effects.select].friendly_name))
			{
				for (int i = 0; i < IM_ARRAYSIZE(ptfx_named); i++)
				{
					if (ImGui::Selectable(ptfx_named[i].friendly_name, ptfx_named[i].asset_name == g.self.ptfx_effects.asset))
					{
						g.self.ptfx_effects.asset  = ptfx_named[i].asset_name; // Update our asset name to be used
						g.self.ptfx_effects.select = i;
						g.self.ptfx_effects.effect = ptfx_named[i].effect_names.at(0); // set the effect to the first instance in the vector
					}

					if (ptfx_named[i].asset_name == g.self.ptfx_effects.asset)
						ImGui::SetItemDefaultFocus();
				}

				ImGui::EndCombo();
			}

			if (ImGui::BeginCombo("Effect", g.self.ptfx_effects.effect))
			{
				for (const auto& ptfx_type : ptfx_named[g.self.ptfx_effects.select].effect_names)
				{
					if (ImGui::Selectable(ptfx_type, ptfx_type == g.self.ptfx_effects.effect))
						g.self.ptfx_effects.effect = ptfx_type; // Update our ptfx effect

					if (ptfx_type == g.self.ptfx_effects.effect)
						ImGui::SetItemDefaultFocus();
				}

				ImGui::EndCombo();
			}
		});

		ImGui::Checkbox("NEVER_WANTED"_T.data(), &g.self.never_wanted);
		components::options_modal("Police", [] {
			ImGui::Checkbox("NEVER_WANTED"_T.data(), &g.self.never_wanted);
			components::command_button<"clearwantedlvl">();
			if (!g.self.never_wanted)
			{
				ImGui::Checkbox("FORCE_WANTED_LVL"_T.data(), &g.self.force_wanted_level);
				if (ImGui::IsItemHovered())
					ImGui::SetTooltip("FORCE_WANTED_LVL_INFO"_T.data());
				ImGui::Text("WANTED_LVL"_T.data());
				if (ImGui::SliderInt("###wanted_level", &g.self.wanted_level, 0, 5) && !g.self.force_wanted_level && g_local_player != nullptr)
				{
					g_local_player->m_player_info->m_wanted_level = g.self.wanted_level;
				}
			}
		});

		ImGui::EndGroup();

		ImGui::SeparatorText("PROOFS"_T.data());

		if (ImGui::Button("CHECK_ALL"_T.data()))
		{
			g.self.proof_bullet    = true;
			g.self.proof_fire      = true;
			g.self.proof_collision = true;
			g.self.proof_melee     = true;
			g.self.proof_explosion = true;
			g.self.proof_steam     = true;
			g.self.proof_drown     = true;
			g.self.proof_water     = true;
		}

		ImGui::SameLine();

		if (ImGui::Button("UNCHECK_ALL"_T.data()))
		{
			g.self.proof_bullet    = false;
			g.self.proof_fire      = false;
			g.self.proof_collision = false;
			g.self.proof_melee     = false;
			g.self.proof_explosion = false;
			g.self.proof_steam     = false;
			g.self.proof_drown     = false;
			g.self.proof_water     = false;
		}

		ImGui::BeginGroup();

		ImGui::Checkbox("BULLET"_T.data(), &g.self.proof_bullet);
		ImGui::Checkbox("FIRE"_T.data(), &g.self.proof_fire);

		ImGui::EndGroup();
		ImGui::SameLine();
		ImGui::BeginGroup();

		ImGui::Checkbox("COLLISION"_T.data(), &g.self.proof_collision);
		ImGui::Checkbox("MELEE"_T.data(), &g.self.proof_melee);

		ImGui::EndGroup();
		ImGui::SameLine();
		ImGui::BeginGroup();

		ImGui::Checkbox("EXPLOSION"_T.data(), &g.self.proof_explosion);
		ImGui::Checkbox("STEAM"_T.data(), &g.self.proof_steam);

		ImGui::EndGroup();
		ImGui::SameLine();
		ImGui::BeginGroup();

		ImGui::Checkbox("DROWN"_T.data(), &g.self.proof_drown);
		ImGui::Checkbox("WATER"_T.data(), &g.self.proof_water);

		ImGui::EndGroup();

		ImGui::SeparatorText("HUD"_T.data());

		ImGui::BeginGroup();

		ImGui::Checkbox("HIDE_RADAR"_T.data(), &g.self.hud.hide_radar);

		ImGui::SameLine();

		ImGui::Checkbox("HIDE_AMMO"_T.data(), &g.self.hud.hide_ammo);

		ImGui::SameLine();

		ImGui::Checkbox("FORCE_SHOW_HUD"_T.data(), &g.self.hud.force_show_hud);

		ImGui::Combo("##hud_comp_combo", &g.self.hud.selected_hud_component, hud_component_names, (int)HudComponents::HUD_WEAPONS);
		ImGui::SameLine();
		components::button("HIDE"_T, [] {
			g.self.hud.hud_components_states[g.self.hud.selected_hud_component] = true;
		});
		ImGui::SameLine();
		components::button("SHOW"_T, [] {
			g.self.hud.hud_components_states[g.self.hud.selected_hud_component] = false;
		});

		components::button("HIDE_ALL"_T, [] {
			g.self.hud.hide_radar = true;
			g.self.hud.hide_ammo  = true;

			for (int i = 0; i < (int)HudComponents::HUD_WEAPONS; i++)
			{
				g.self.hud.hud_components_states[i] = true;
			}
		});
		ImGui::SameLine();
		components::button("SHOW_ALL"_T, [] {
			g.self.hud.hide_radar = false;
			g.self.hud.hide_ammo  = false;

			for (int i = 0; i < (int)HudComponents::HUD_WEAPONS; i++)
			{
				g.self.hud.hud_components_states[i] = false;
			}
		});
		ImGui::SameLine();
		ImGui::Checkbox("FORCE_SHOW_HUD_ELEMENT"_T.data(), &g.self.hud.force_show_hud_element);
		if (ImGui::IsItemHovered())
			ImGui::SetTooltip("FORCE_SHOW_HUD_ELEMENT_DESC"_T.data());

		ImGui::EndGroup();

		ImGui::BeginGroup();
		components::command_checkbox<"hudcolor">();
		static int color_select_index = 0;

		if (g.self.hud.color_override)
		{
			ImGui::Combo("Color Index", &color_select_index, hud_colors.data(), hud_colors.size());

			auto& ovr_color = g.self.hud.hud_color_overrides[color_select_index];

			float col[4]{};
			col[0] = ovr_color.r / 255.0f;
			col[1] = ovr_color.g / 255.0f;
			col[2] = ovr_color.b / 255.0f;
			col[3] = ovr_color.a / 255.0f;

			if (ImGui::ColorPicker4("Override Color", col))
			{
				ovr_color.r = (int)(col[0] * 255);
				ovr_color.g = (int)(col[1] * 255);
				ovr_color.b = (int)(col[2] * 255);
				ovr_color.a = (int)(col[3] * 255);

				g_fiber_pool->queue_job([] {
					auto& col = g.self.hud.hud_color_overrides[color_select_index];
					HUD::REPLACE_HUD_COLOUR_WITH_RGBA(color_select_index, col.r, col.g, col.b, col.a);
				});
			}

			components::button("Restore Default Color", [] {
				g.self.hud.hud_color_overrides[color_select_index] = g.self.hud.hud_color_defaults[color_select_index];

				auto& col = g.self.hud.hud_color_defaults[color_select_index];
				HUD::REPLACE_HUD_COLOUR_WITH_RGBA(color_select_index, col.r, col.g, col.b, col.a);
			});

			ImGui::SameLine();

			components::button("Restore All Defaults", [] {
				for (int i = 0; i < hud_colors.size(); i++)
				{
					auto& col                         = g.self.hud.hud_color_defaults[i];
					g.self.hud.hud_color_overrides[i] = col;
					HUD::REPLACE_HUD_COLOUR_WITH_RGBA(i, col.r, col.g, col.b, col.a);
				}
			});
		}

		ImGui::EndGroup();

		g.self.proof_mask = 0;
		if (g.self.god_mode)
		{
			g.self.proof_mask |= static_cast<int>(eEntityProofs::GOD);
		}
		if (g.self.proof_bullet)
		{
			g.self.proof_mask |= static_cast<int>(eEntityProofs::BULLET);
		}
		if (g.self.proof_fire)
		{
			g.self.proof_mask |= static_cast<int>(eEntityProofs::FIRE);
		}
		if (g.self.proof_collision)
		{
			g.self.proof_mask |= static_cast<int>(eEntityProofs::COLLISION);
		}
		if (g.self.proof_melee)
		{
			g.self.proof_mask |= static_cast<int>(eEntityProofs::MELEE);
		}
		if (g.self.proof_explosion)
		{
			g.self.proof_mask |= static_cast<int>(eEntityProofs::EXPLOSION);
		}
		if (g.self.proof_steam)
		{
			g.self.proof_mask |= static_cast<int>(eEntityProofs::STEAM);
		}
		if (g.self.proof_drown)
		{
			g.self.proof_mask |= static_cast<int>(eEntityProofs::DROWN);
		}
		if (g.self.proof_water)
		{
			g.self.proof_mask |= static_cast<int>(eEntityProofs::WATER);
		}
	}
}
