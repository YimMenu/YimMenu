#include "reaction.hpp"

#include "backend/player_command.hpp"
#include "fiber_pool.hpp"
#include "hooking.hpp"
#include "pointers.hpp"
#include "script.hpp"
#include "util/notify.hpp"

namespace big
{
	reaction::reaction(const char* event_name, const char* notify_message, const char* announce_message) :
	    m_event_name(event_name),
	    m_notify_message(notify_message),
	    m_announce_message(announce_message)
	{
	}

	void reaction::process_common(player_ptr player)
	{
		if (log)
		{
			uint64_t rockstar_id = player->get_net_data() == nullptr ? 0 : player->get_net_data()->m_gamer_handle.m_rockstar_id;
			LOG(WARNING) << std::format("Received {} from {} ({})", m_event_name, player->get_name(), rockstar_id);
		}

		if (kick)  
		{
			g_fiber_pool->queue_job([player] {
				
				dynamic_cast<player_command*>(command::get(RAGE_JOAAT("multikick")))->call(player, {});
			});
		}

		if (timeout)
		{
			    player->block_net_events   = true;
			    player->block_clone_sync   = true;
			    player->block_clone_create = true;
			    LOG(WARNING) << std::format("{} has been timed out", player->get_name());
		}
	}


	void reaction::process(player_ptr player)
	{
		if (!player->is_valid())
			return;

		if (notify)
		{
			char notification[500]{}; // I don't like using sprintf but there isn't an alternative afaik
			snprintf(notification, sizeof(notification), m_notify_message, player->get_name());
			g_notification_service->push_warning("Protections", notification);
		}

		process_common(player);
	}
}
