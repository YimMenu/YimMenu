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

	void chat_service::add_msg(uint64_t rid, std::string name, std::string msg, bool is_team, bool is_spam)
	{
		m_chat_msgs.push_back({
			rid,
			is_team,
			is_spam,
			name,
			msg
		});
	}
	void chat_service::add_msg(CNetGamePlayer* player, std::string msg, bool is_team, bool is_spam)
	{
		m_chat_msgs.push_back({
			player->get_net_data()->m_gamer_handle_2.m_rockstar_id,
			is_team,
			is_spam,
			player->get_name(),
			msg
		});
	}

	void chat_service::add_direct_msg(uint64_t rid_sender, uint64_t rid_receiver, std::string name_sender, std::string name_receiver, std::string msg, bool is_spam)
	{
		m_direct_msgs.push_back({
			rid_sender,
			rid_receiver,
			is_spam,
			name_sender,
			name_receiver,
			msg
		});
	}
	void chat_service::add_direct_msg(CNetGamePlayer* player_sender, CNetGamePlayer* player_receiver, std::string msg, bool is_spam)
	{
		m_direct_msgs.push_back({
			player_sender->get_net_data()->m_gamer_handle_2.m_rockstar_id,
			player_receiver->get_net_data()->m_gamer_handle_2.m_rockstar_id, // TODO: Use real rid.
			is_spam,
			player_sender->get_name(),
			player_receiver->get_name(),
			msg
		});
	}
}