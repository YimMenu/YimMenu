#include "backend/looped_command.hpp"
#include "gta/enums.hpp"
#include "natives.hpp"

namespace big
{
	class no_spread : looped_command
	{
		using looped_command::looped_command;

		CWeaponInfo* p_modified_weapon = nullptr;

		float og_accuracy_spread         = 0;
		uint32_t og_accuracy_offset_hash = 0;

		void reset_to_og()
		{
			p_modified_weapon->m_accuracy_spread            = og_accuracy_spread;
			p_modified_weapon->m_accuracy_offset_shake_hash = og_accuracy_offset_hash;
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
							og_accuracy_spread      = weapon_mgr->m_weapon_info->m_accuracy_spread;
							og_accuracy_offset_hash = weapon_mgr->m_weapon_info->m_accuracy_offset_shake_hash;
						}

						// Set to the good stuff
						{
							weapon_mgr->m_weapon_info->m_accuracy_spread            = 0;
							weapon_mgr->m_weapon_info->m_accuracy_offset_shake_hash = 0;
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

	no_spread
	    g_no_spread("nospread", "BACKEND_LOOPED_WEAPONS_NO_SPREAD", "BACKEND_LOOPED_WEAPONS_NO_SPREAD_DESC", g.weapons.no_spread);
}
