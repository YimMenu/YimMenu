#include "gta/net_game_event.hpp"
#include "hooking.hpp"
#include "services/players/player_service.hpp"
#include "util/session.hpp"

#include <entities/CDynamicEntity.hpp>

namespace big
{
	void hooks::get_network_event_data(int64_t unk, rage::CEventNetwork* net_event)
	{
		switch (net_event->get_type())
		{
		case rage::eEventNetworkType::CEventNetworkRemovedFromSessionDueToComplaints:
		{
			g_notification_service->push_warning("KICKED"_T.data(), "USER_DESYNC_KICKED"_T.data());
			break;
		}
		case rage::eEventNetworkType::CEventNetworkEntityDamage:
		{
			rage::sEntityDamagedData damage_data;
			net_event->get_extra_information(&damage_data, sizeof(damage_data));

			if (damage_data.m_weapon_used == RAGE_JOAAT("weapon_explosion"))
				break;

			if (auto damager = g_pointers->m_handle_to_ptr(damage_data.m_damager_index);
			    damager && damager->m_entity_type == 4 && reinterpret_cast<CPed*>(damager)->m_player_info)
			{
				if (auto player = g_player_service->get_by_host_token(
				        reinterpret_cast<CPed*>(damager)->m_player_info->m_net_player_data.m_host_token))
				{
					if (auto victim = g_pointers->m_handle_to_ptr(damage_data.m_victim_index);
					    victim && victim->m_entity_type == 4 && reinterpret_cast<CPed*>(victim)->m_player_info)
					{
						if (reinterpret_cast<CPed*>(damager)->m_damage_bits & (1 << 8))
						{
							session::add_infraction(player, Infraction::ATTACKING_WITH_GODMODE);
						}
					}
				}
			}
			break;
		}
		}

		return g_hooking->get_original<get_network_event_data>()(unk, net_event);
	}
}
