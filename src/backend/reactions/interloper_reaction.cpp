#include "interloper_reaction.hpp"
#include "util/chat.hpp"

namespace big
{
	interloper_reaction::interloper_reaction(const char* event_name, const char* notify_message, const char* announce_message, bool blockable, bool karmaable) :
	    reaction(event_name, notify_message, announce_message),
	    m_blockable(blockable),
	    m_karmaable(karmaable)
	{
	}

	void interloper_reaction::process(player_ptr attacker, player_ptr victim)
	{
		if (!attacker->is_valid() || !victim->is_valid())
			return;
		if ((attacker->is_friend() && g.session.trust_friends) || attacker->is_trusted || g.session.trust_session)
			return;

		if (log)
		{
			LOGF(WARNING,
			    "Received {} from {} ({}), victim is {}",
			    m_event_name,
			    attacker->get_name(),
			    attacker->get_rockstar_id(),
			    victim->get_name());
		}

		if (announce_in_chat)
		{
			auto msg = std::format("{} {}", g.session.chat_output_prefix, g_translation_service.get_translation(m_announce_message));
			chat::send_message(msg);
		}

		if (notify)
		{
			auto a_name = attacker->get_name();
			auto v_name = victim->get_name();

			g_notification_service.push_warning("PROTECTIONS"_T.data(),
			    std::vformat(g_translation_service.get_translation(m_notify_message), std::make_format_args(a_name, v_name)));
		}

		process_common(attacker);
	}
}
