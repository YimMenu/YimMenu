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

		if (announce_in_chat)
		{
			g_fiber_pool->queue_job([attacker, victim, this] {
				std::string chat = std::format("{} {} {}",
					g.session.chat_output_prefix, 
					m_announce_message,
					attacker->get_name(),
					victim->get_name());

				if (g_hooking->get_original<hooks::send_chat_message>()(
					*g_pointers->m_gta.m_send_chat_ptr,
					g_player_service->get_self()->get_net_data(),
					chat.c_str(),
					false))
				{
					notify::draw_chat(chat, g_player_service->get_self()->get_name(), false);
				}
			});
		}

		if (notify)
		{
			std::string notification = std::format("{} {} {}",
				m_notify_message,
				attacker->get_name(),
				victim->get_name());
			g_notification_service->push_warning("Protections", notification.c_str());
		}

    	process_common(attacker);
	}

}