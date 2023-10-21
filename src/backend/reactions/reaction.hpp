#pragma once

namespace big
{
	class player;
	using player_ptr = std::shared_ptr<player>;

	class reaction
	{
	public:
		bool notify           = true;
		bool log              = true;
		bool kick             = false;
		bool timeout          = false;

		const char* m_event_name;
		const char* m_notify_message;
		const char* m_announce_message;

		NLOHMANN_DEFINE_TYPE_INTRUSIVE(reaction, notify, log, kick, timeout)

		reaction(const char* event_name, const char* notify_message, const char* announce_message);
		virtual void process(player_ptr player);
		virtual void process_common(player_ptr player);
	};
}