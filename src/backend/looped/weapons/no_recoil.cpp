#include "backend/looped_command.hpp"
#include "gta/enums.hpp"
#include "natives.hpp"

namespace big
{
	class no_recoil : looped_command
	{
		using looped_command::looped_command;

		CWeaponInfo* p_modified_weapon = nullptr;
		uint32_t og_recoil_hash        = 0;
		uint32_t og_recoil_hash_fp     = 0;

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
						p_modified_weapon->m_recoil_shake_hash              = og_recoil_hash;
						p_modified_weapon->m_recoil_shake_hash_first_person = og_recoil_hash_fp;
					}

					p_modified_weapon = weapon_mgr->m_weapon_info;

					if (weapon_mgr->m_weapon_info)
					{
						og_recoil_hash    = weapon_mgr->m_weapon_info->m_recoil_shake_hash;
						og_recoil_hash_fp = weapon_mgr->m_weapon_info->m_recoil_shake_hash_first_person;
						weapon_mgr->m_weapon_info->m_recoil_shake_hash              = 0;
						weapon_mgr->m_weapon_info->m_recoil_shake_hash_first_person = 0;
					}
				}
			}
		}

		virtual void on_disable() override
		{
			if (g_local_player && p_modified_weapon)
			{
				p_modified_weapon->m_recoil_shake_hash              = og_recoil_hash;
				p_modified_weapon->m_recoil_shake_hash_first_person = og_recoil_hash_fp;
				p_modified_weapon                                   = nullptr;
			}
		}
	};

	no_recoil g_no_recoil("norecoil", "No Recoil", "Removes weapon recoil when shooting", g.weapons.no_recoil);
}
