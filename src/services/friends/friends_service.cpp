#include "friends_service.hpp"

#include <network/CNetGamePlayer.hpp>

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

	bool friends_service::is_friend(CNetGamePlayer* net_player)
	{
		if (net_player == nullptr)
			return false;

		if (auto net_data = net_player->get_net_data())
		{
			const auto rockstar_id = net_data->m_gamer_handle.m_rockstar_id;
			return is_friend(rockstar_id);
		}
		return false;
	}

}