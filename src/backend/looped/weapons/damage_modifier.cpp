#include "backend/looped_command.hpp"
#include "core/data/weapons.hpp"
#include "gta/enums.hpp"
#include "natives.hpp"

namespace big
{
	class damage_modifier : looped_command
	{
		using looped_command::looped_command;

		CWeaponInfo* p_modified_weapon = nullptr;

		float m_hit_limbs_damage_modifier;         // 0.5
		float m_network_hit_limbs_damage_modifier; // 0.8
		float m_lightly_armoured_damage_modifier;  // 0.75
		float m_vehicle_damage_modifier;           // 1
		float m_headshot_damage_modifier_player;   // 18
		float m_network_player_damage_modifier;    // 1
		float m_network_ped_damage_modifier;       // 1

		float m_max_headshot_distance_player; // 40

		int damage_modifier_v;

		void restore()
		{
			if (p_modified_weapon)
			{
				p_modified_weapon->m_hit_limbs_damage_modifier         = m_hit_limbs_damage_modifier;
				p_modified_weapon->m_network_hit_limbs_damage_modifier = m_network_hit_limbs_damage_modifier;
				p_modified_weapon->m_lightly_armoured_damage_modifier  = m_lightly_armoured_damage_modifier;
				p_modified_weapon->m_vehicle_damage_modifier           = m_vehicle_damage_modifier;
				p_modified_weapon->m_max_headshot_distance_player      = m_max_headshot_distance_player;
				p_modified_weapon->m_headshot_damage_modifier_player   = m_headshot_damage_modifier_player;
				p_modified_weapon->m_network_player_damage_modifier    = m_network_player_damage_modifier;
				p_modified_weapon->m_network_ped_damage_modifier       = m_network_ped_damage_modifier;
				p_modified_weapon                                      = nullptr;
			}
		}

		void set_modifier(float value)
		{
			damage_modifier_v                                      = value;
			p_modified_weapon->m_hit_limbs_damage_modifier         = m_hit_limbs_damage_modifier * value;
			p_modified_weapon->m_network_hit_limbs_damage_modifier = m_network_hit_limbs_damage_modifier * value;
			p_modified_weapon->m_lightly_armoured_damage_modifier  = m_lightly_armoured_damage_modifier * value;
			p_modified_weapon->m_vehicle_damage_modifier           = m_vehicle_damage_modifier * value;
			p_modified_weapon->m_max_headshot_distance_player      = 1000.f;
			p_modified_weapon->m_headshot_damage_modifier_player   = m_headshot_damage_modifier_player * value;
			p_modified_weapon->m_network_player_damage_modifier    = m_network_player_damage_modifier * value;
			p_modified_weapon->m_network_ped_damage_modifier       = m_network_ped_damage_modifier * value;
		}

		virtual void on_tick() override
		{
			if (!g_local_player)
				return;

			if (auto* const weapon_mgr = g_local_player->m_weapon_manager; weapon_mgr)
			{
				if (p_modified_weapon != weapon_mgr->m_weapon_info)
				{
					restore();

					if (weapon_mgr->m_weapon_info)
					{
						p_modified_weapon = weapon_mgr->m_weapon_info;
						m_hit_limbs_damage_modifier = weapon_mgr->m_weapon_info->m_hit_limbs_damage_modifier;
						m_network_hit_limbs_damage_modifier = weapon_mgr->m_weapon_info->m_network_hit_limbs_damage_modifier;
						m_lightly_armoured_damage_modifier = weapon_mgr->m_weapon_info->m_lightly_armoured_damage_modifier;
						m_vehicle_damage_modifier      = weapon_mgr->m_weapon_info->m_vehicle_damage_modifier;
						m_max_headshot_distance_player = weapon_mgr->m_weapon_info->m_max_headshot_distance_player;
						m_headshot_damage_modifier_player = weapon_mgr->m_weapon_info->m_headshot_damage_modifier_player;
						m_network_player_damage_modifier = weapon_mgr->m_weapon_info->m_network_player_damage_modifier;
						m_network_ped_damage_modifier    = weapon_mgr->m_weapon_info->m_network_ped_damage_modifier;

						set_modifier(g_weapons.damage_modifier_v);
					}
				}
				else if (damage_modifier_v != g_weapons.damage_modifier_v)
					set_modifier(g_weapons.damage_modifier_v);
			}
		}

		virtual void on_disable() override
		{
			if (g_local_player && p_modified_weapon)
				restore();
		}
	};

	damage_modifier g_damage_modifier("damage_modifier", "Damage Modifier", "Increase the damage", g_weapons.damage_modifier);
}
