#pragma once

namespace big
{
	class player;
	using player_ptr = std::shared_ptr<player>;

	class reaction
	{
	protected:
		void process_common(player_ptr player);

	public:
		bool announce_in_chat = false;
		bool notify           = true;
		bool log              = true;
		bool add_to_player_db = false;
		bool block_joins      = false;
		bool kick             = false;

		const char* m_event_name;
		const char* m_notify_message;
		const char* m_announce_message;

		NLOHMANN_DEFINE_TYPE_INTRUSIVE(reaction, announce_in_chat, notify, log, add_to_player_db, block_joins, kick)

		reaction(const char* event_name, const char* notify_message, const char* announce_message);
		virtual void process(player_ptr player);
	};
}