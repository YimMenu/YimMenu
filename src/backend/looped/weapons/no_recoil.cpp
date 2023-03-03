#include "backend/looped_command.hpp"
#include "gta/enums.hpp"
#include "natives.hpp"

namespace big
{
	class no_recoil : looped_command
	{
		using looped_command::looped_command;

		CWeaponInfo* p_modified_weapon = nullptr;
		float og_recoil_value          = 0.0f;

		virtual void on_tick() override
		{
			if (!g_local_player)
			{
				return;
			}

			auto* const weapon_mgr = g_local_player->m_weapon_manager;
			if (weapon_mgr)
			{
				if (p_modified_weapon != weapon_mgr->m_weapon_info && weapon_mgr->m_weapon_info)
				{
					if (p_modified_weapon)
						p_modified_weapon->m_explosion_shake_amplitude = og_recoil_value;

					og_recoil_value   = weapon_mgr->m_weapon_info->m_explosion_shake_amplitude;
					p_modified_weapon = weapon_mgr->m_weapon_info;
					weapon_mgr->m_weapon_info->m_explosion_shake_amplitude = 0.0f;
				}
			}
		}

		virtual void on_disable() override
		{
			if (g_local_player && p_modified_weapon)
			{
				p_modified_weapon->m_explosion_shake_amplitude = og_recoil_value;
				p_modified_weapon                              = nullptr;
			}
		}
	};

	no_recoil g_no_recoil("norecoil", "No Recoil", "Removes weapon recoil when shooting", g.weapons.no_recoil);
}
