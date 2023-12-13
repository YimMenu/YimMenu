#include "interloper_reaction.hpp"

#include "backend/player_command.hpp"
#include "fiber_pool.hpp"
#include "hooking.hpp"
#include "pointers.hpp"
#include "script.hpp"
#include "util/notify.hpp"

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
			uint64_t rockstar_id = attacker->get_net_data() == nullptr ? 0 : attacker->get_net_data()->m_gamer_handle.m_rockstar_id;
			LOGF(WARNING,
			    "Received {} from {} ({}), victim is {}",
			    m_event_name,
			    attacker->get_name(),
			    rockstar_id,
			    victim->get_name());
		}

		if (announce_in_chat)
		{
			g_fiber_pool->queue_job([attacker, victim, this] {
				auto chat = std::format("{} {}", g.session.chat_output_prefix, g_translation_service.get_translation(m_announce_message));

				if (g_hooking->get_original<hooks::send_chat_message>()(*g_pointers->m_gta.m_send_chat_ptr,
				        g_player_service->get_self()->get_net_data(),
				        chat.data(),
				        is_team_only))
					notify::draw_chat(chat.c_str(), g_player_service->get_self()->get_name(), is_team_only);
			});
		}

		if (notify)
		{
			g_notification_service->push_warning("PROTECTIONS"_T.data(),
			    std::vformat(g_translation_service.get_translation(m_notify_message), std::make_format_args(attacker->get_name(), victim->get_name())));
		}

		process_common(attacker);
	}
}