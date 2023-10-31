#pragma once
#include "pointers.hpp"

#include <network/CNetGamePlayer.hpp>
#include <socialclub/FriendRegistry.hpp>

namespace big
{
	class friends_service final
	{
	public:
		static inline bool is_friend(uint64_t rockstar_id)
		{
			for (uint32_t i = 0; i < g_pointers->m_gta.m_friend_registry->m_friend_count; i++)
				if (rockstar_id == g_pointers->m_gta.m_friend_registry->get(i)->m_rockstar_id)
					return true;
			return false;
		}
		[[nodiscard]] static inline bool is_friend(CNetGamePlayer* net_player)
		{
			if (net_player == nullptr)
				return false;

			const auto rockstar_id = net_player->get_net_data()->m_gamer_handle.m_rockstar_id;
			return is_friend(rockstar_id);
		}
	};
}