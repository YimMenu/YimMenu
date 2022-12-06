#pragma once
#include "natives.hpp"
#include "gta/joaat.hpp"
#include "services/players/player_service.hpp"

namespace big
{
	struct chat_msg {
		uint64_t rid;
		bool is_team;
		bool is_spam;
		std::string name;
		std::string msg;
	};

	struct direct_msg {
		uint64_t rid_sender;
		uint64_t rid_receiver;
		// TODO: Different send methods ex. Script event, Script event enc, NETWORK_SEND_TEXT_MESSAGE.
		bool is_spam;
		std::string name_sender;
		std::string name_receiver;
		std::string msg;
	};

	using chat_msgs = std::vector<chat_msg>;
	using direct_msgs = std::vector<direct_msg>;

	using chat_callback = std::function<const char* (const char*)>;
	class chat_service final
	{
		chat_msgs m_chat_msgs;
		direct_msgs m_direct_msgs;

	public:
		chat_service();
		~chat_service();

		chat_service(const chat_service&) = delete;
		chat_service(chat_service&&) noexcept = delete;
		chat_service& operator=(const chat_service&) = delete;
		chat_service& operator=(chat_service&&) noexcept = delete;

		void add_msg(CNetGamePlayer* player, std::string msg, bool is_team = false, bool is_spam = false);
		void add_msg(uint64_t rid, std::string name, std::string msg, bool is_team = false, bool is_spam = false);

		void add_direct_msg(uint64_t rid_sender, uint64_t rid_receiver, std::string name_sender, std::string name_receiver, std::string msg, bool is_spam = false);
		void add_direct_msg(CNetGamePlayer* player_sender, CNetGamePlayer* player_receiver, std::string msg, bool is_spam = false);

		chat_msgs& get_chat_msgs()
		{ return m_chat_msgs; }

		direct_msgs& get_direct_msgs()
		{ return m_direct_msgs; }
	};

	inline chat_service* g_chat_service;
}