#include "friends_service.hpp"
#include "pointers.hpp"

namespace big
{
	friends_service::friends_service()
	{
		g_friends_service = this;
	}

	friends_service::~friends_service()
	{
		g_friends_service = nullptr;
	}

	bool friends_service::is_friend(const player_ptr& plyr)
	{
		const std::uint64_t rockstar_id = plyr->get_net_data()->m_rockstar_id2;
		for (std::uint32_t i = 0; i < g_pointers->m_friend_registry->m_friend_count; i++)
			if (rockstar_id == g_pointers->m_friend_registry->m_friends_list->m_data[i].m_rockstar_id)
				return true;
		return false;
	}

}