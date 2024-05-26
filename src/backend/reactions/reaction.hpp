#pragma once

namespace big
{
	class player;
	using player_ptr = std::shared_ptr<player>;

	class reaction
	{
	public:
		bool announce_in_chat = false;
		bool is_team_only     = false;
		bool notify           = true;
		bool log              = true;
		bool add_to_player_db = false;
		bool block_joins      = false;
		int block_join_reason = 1;
		bool kick             = false;
		bool timeout          = false;

		const char* m_event_name;
		const char* m_notify_message;
		const char* m_announce_message;

		NLOHMANN_DEFINE_TYPE_INTRUSIVE(reaction, announce_in_chat, is_team_only, notify, log, add_to_player_db, block_joins, block_join_reason, kick, timeout)

		reaction(const char* event_name, const char* notify_message, const char* announce_message);
		virtual void process(player_ptr player);
		virtual void only_notify(player_ptr player);
		virtual void process_common(player_ptr player);
	};
}