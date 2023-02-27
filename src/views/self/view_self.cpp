#include "core/data/hud_component_names.hpp"
#include "core/data/ptfx_effects.hpp"
#include "fiber_pool.hpp"
#include "util/entity.hpp"
#include "util/local_player.hpp"
#include "util/scripts.hpp"
#include "views/view.hpp"

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

		ImGui::Separator();

		components::sub_title("GENERAL"_T);

		ImGui::BeginGroup();

		components::command_checkbox<"godmode">();
		components::command_checkbox<"otr">();
		components::command_checkbox<"freecam">();
		components::command_checkbox<"nophone">();
		components::command_checkbox<"infoxy">();
		components::command_checkbox<"fastrespawn">();

		ImGui::EndGroup();
		ImGui::SameLine();
		ImGui::BeginGroup();

		components::command_checkbox<"noclip">();
		components::command_checkbox<"noragdoll">();
		components::command_checkbox<"fastrun">();
		ImGui::Checkbox("NO_IDLE_KICK"_T.data(), &g.tunables.no_idle_kick);
		components::command_checkbox<"walkunder">();
		if (!g.self.super_jump)
			components::command_checkbox<"beastjump">();
		if (!g.self.beast_jump)
			components::command_checkbox<"superjump">();
		ImGui::EndGroup();
		ImGui::SameLine();
		ImGui::BeginGroup();

		components::command_checkbox<"invis">();
		if (g.self.invisibility)
			components::command_checkbox<"localvis">();// TODO: does nothing in SP
		components::command_checkbox<"cleanloop">();
		components::command_checkbox<"nocollision">();
		components::command_checkbox<"mobileradio">();
		components::command_checkbox<"superman">();

		ImGui::Checkbox("DANCE_MODE"_T.data(), &g.self.dance_mode);

		ImGui::EndGroup();

		components::sub_title("PTFX Styles");

		components::command_checkbox<"ptfx">();
		if (g.self.ptfx_effects.show)
		{
			ImGui::SliderFloat("PTFX Size", &g.self.ptfx_effects.size, 0.1f, 2.f);
			if (ImGui::BeginCombo("Asset", ptfx_named[g.self.ptfx_effects.select].friendly_name))
			{
				for (int i = 0; i < IM_ARRAYSIZE(ptfx_named); i++)
				{
					if (ImGui::Selectable(ptfx_named[i].friendly_name, ptfx_named[i].asset_name == g.self.ptfx_effects.asset))
					{
						g.self.ptfx_effects.asset  = ptfx_named[i].asset_name;// Update our asset name to be used
						g.self.ptfx_effects.select = i;
						g.self.ptfx_effects.effect = ptfx_named[i].effect_names.at(0);// set the effect to the first instance in the vector
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
						g.self.ptfx_effects.effect = ptfx_type;// Update our ptfx effect

					if (ptfx_type == g.self.ptfx_effects.effect)
						ImGui::SetItemDefaultFocus();
				}

				ImGui::EndCombo();
			}
		}


		ImGui::Separator();

		components::sub_title("PROOFS"_T);

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

		ImGui::Separator();

		components::sub_title("POLICE"_T);

		ImGui::Checkbox("NEVER_WANTED"_T.data(), &g.self.never_wanted);

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

		ImGui::Separator();

		components::sub_title("HUD"_T);

		ImGui::BeginGroup();

		ImGui::Checkbox("HIDE_RADAR"_T.data(), &g.self.hide_radar);

		ImGui::SameLine();

		ImGui::Checkbox("HIDE_AMMO"_T.data(), &g.self.hide_ammo);

		ImGui::SameLine();

		ImGui::Checkbox("FORCE_SHOW_HUD"_T.data(), &g.self.force_show_hud);

		ImGui::Combo("##hud_comp_combo", &g.self.selected_hud_component, hud_component_names, (int)HudComponents::HUD_WEAPONS);
		ImGui::SameLine();
		components::button("HIDE"_T, [] {
			g.self.hud_components_states[g.self.selected_hud_component] = true;
		});
		ImGui::SameLine();
		components::button("SHOW"_T, [] {
			g.self.hud_components_states[g.self.selected_hud_component] = false;
		});

		components::button("HIDE_ALL"_T, [] {
			g.self.hide_radar = true;
			g.self.hide_ammo  = true;
			for (int i = 0; i < (int)HudComponents::HUD_WEAPONS; i++)
			{
				g.self.hud_components_states[i] = true;
			}
		});
		ImGui::SameLine();
		components::button("SHOW_ALL"_T, [] {
			g.self.hide_radar = false;
			g.self.hide_ammo  = false;
			for (int i = 0; i < (int)HudComponents::HUD_WEAPONS; i++)
			{
				g.self.hud_components_states[i] = false;
			}
		});
		ImGui::SameLine();
		ImGui::Checkbox("FORCE_SHOW_HUD_ELEMENT"_T.data(), &g.self.force_show_hud_element);
		if (ImGui::IsItemHovered())
			ImGui::SetTooltip("FORCE_SHOW_HUD_ELEMENT_DESC"_T.data());

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
