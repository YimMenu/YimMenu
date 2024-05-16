#pragma once
#include "pointers.hpp"

#include <socialclub/FriendRegistry.hpp>

namespace big
{
	class friends_service final
	{
	public:
		friends_service();
		~friends_service();

		friends_service(const friends_service&)                = delete;
		friends_service(friends_service&&) noexcept            = delete;
		friends_service& operator=(const friends_service&)     = delete;
		friends_service& operator=(friends_service&&) noexcept = delete;

		[[nodiscard]] static inline bool is_friend(int64_t rockstar_id)
		{
			for (uint32_t i = 0; i < g_pointers->m_gta.m_friend_registry->m_friend_count; i++)
				if (rockstar_id == g_pointers->m_gta.m_friend_registry->get(i)->m_rockstar_id)
					return true;

			return false;
		}

		[[nodiscard]] static bool is_friend(CNetGamePlayer* net_player);
	};

	inline friends_service* g_friends_service{};
}