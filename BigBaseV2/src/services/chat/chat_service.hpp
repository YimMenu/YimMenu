#pragma once
#include "natives.hpp"
#include "gta/joaat.hpp"
#include "services/players/player_service.hpp"

namespace big
{
	struct chat_msg {
		CNetGamePlayer* player;
		bool is_team;
		std::string msg;
	};
	using msgs = std::vector<chat_msg>;

	using chat_callback = std::function<const char* (const char*)>;
	class chat_service final
	{
		msgs m_msgs;

	public:
		chat_service();
		~chat_service();

		chat_service(const chat_service&) = delete;
		chat_service(chat_service&&) noexcept = delete;
		chat_service& operator=(const chat_service&) = delete;
		chat_service& operator=(chat_service&&) noexcept = delete;

		bool did_player_use_chat(Player player_id);
		void add_msg(CNetGamePlayer* player, std::string msg, bool is_team);

		static void chat_menu();

		msgs& get_msgs()
		{
			return m_msgs;
		}
	};

	inline chat_service* g_chat_service;
}