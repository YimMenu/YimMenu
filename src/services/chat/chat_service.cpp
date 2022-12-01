#pragma 
#include "chat_service.hpp"
#include "network/CNetGamePlayer.hpp"
#include "gta/enums.hpp"
#include "pointers.hpp"
#include "natives.hpp"
#include "script.hpp"

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

	void chat_service::add_msg(CNetGamePlayer* player, std::string msg, bool is_team, bool is_spam)
	{
		m_msgs.push_back({ player->get_net_data()->m_gamer_handle_2.m_rockstar_id, is_team, is_spam, player->get_name(), msg });
	}
	void chat_service::add_msg(uint64_t rid, std::string name, std::string msg, bool is_team, bool is_spam)
	{
		m_msgs.push_back({ rid, is_team, is_spam, name, msg });
	}
}