#include "backend/looped_command.hpp"
#include "gta/enums.hpp"
#include "natives.hpp"

namespace big
{
	class no_recoil : looped_command
	{
		using looped_command::looped_command;

		CWeaponInfo* p_modified_weapon = nullptr;

		float og_bullet_speed = 0;

		float og_recoil_shake_amplitude = 0;

		uint32_t og_recoil_hash    = 0;
		uint32_t og_recoil_hash_fp = 0;

		void reset_to_og()
		{
			p_modified_weapon->m_speed = og_bullet_speed;

			p_modified_weapon->m_recoil_shake_amplitude = og_recoil_shake_amplitude;

			p_modified_weapon->m_recoil_shake_hash              = og_recoil_hash;
			p_modified_weapon->m_recoil_shake_hash_first_person = og_recoil_hash_fp;
		}

		virtual void on_tick() override
		{
			if (!g_local_player)
			{
				return;
			}

			auto* const weapon_mgr = g_local_player->m_weapon_manager;
			if (weapon_mgr)
			{
				if (p_modified_weapon != weapon_mgr->m_weapon_info)
				{
					if (p_modified_weapon)
					{
						reset_to_og();
					}

					p_modified_weapon = weapon_mgr->m_weapon_info;

					if (weapon_mgr->m_weapon_info)
					{
						// Backup
						{
							og_bullet_speed = weapon_mgr->m_weapon_info->m_speed;

							og_recoil_shake_amplitude = weapon_mgr->m_weapon_info->m_recoil_shake_amplitude;

							og_recoil_hash    = weapon_mgr->m_weapon_info->m_recoil_shake_hash;
							og_recoil_hash_fp = weapon_mgr->m_weapon_info->m_recoil_shake_hash_first_person;
						}

						// Set to the good stuff
						{
							weapon_mgr->m_weapon_info->m_speed = 9999999999.0f;

							weapon_mgr->m_weapon_info->m_recoil_shake_amplitude = 0;

							weapon_mgr->m_weapon_info->m_recoil_shake_hash              = 0;
							weapon_mgr->m_weapon_info->m_recoil_shake_hash_first_person = 0;
						}
					}
				}
			}
		}

		virtual void on_disable() override
		{
			if (g_local_player && p_modified_weapon)
			{
				reset_to_og();

				p_modified_weapon = nullptr;
			}
		}
	};

	no_recoil
	    g_no_recoil("norecoil", "BACKEND_LOOPED_WEAPONS_NO_RECOIL", "BACKEND_LOOPED_WEAPONS_NO_RECOIL_DESC", g.weapons.no_recoil);
}
