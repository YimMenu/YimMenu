#pragma 
#include "chat_service.hpp"
#include "network/CNetGamePlayer.hpp"

namespace big
{
	chat_service::chat_service()
	{
		g_chat_service = this;
	}

	chat_service::~chat_service()
	{
		g_chat_service = nullptr;
	}

	bool chat_service::did_player_use_chat(Player player_id)
	{
		for (const auto& [player, msg, is_team] : m_msgs)
		{
			if (player != nullptr)
			{
				if (player->m_player_id == player_id)
				{
					return true;
				}
			}
		}
		return false;
	}

	void chat_service::add_msg(CNetGamePlayer* player, std::string msg, bool is_team)
	{
		m_msgs.push_back({ player, is_team, msg });
	}
}