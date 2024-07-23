#include "reaction.hpp"

#include "backend/player_command.hpp"
#include "fiber_pool.hpp"
#include "services/player_database/player_database_service.hpp"
#include "util/chat.hpp"

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
		if (add_to_player_db || block_joins)
		{
			auto entry = g_player_database_service->get_or_create_player(player);

			if (block_joins)
			{
				entry->block_join = true;
				entry->block_join_reason = block_join_reason;
				g_player_database_service->save();
			}
		}

		if (kick)
		{
			g_fiber_pool->queue_job([player] {
				player_command::get("smartkick"_J)->call(player, {});
			});
		}

		if (timeout)
		{
			player->block_net_events   = true;
			player->block_clone_sync   = true;
			player->block_clone_create = true;
			LOGF(WARNING, "{} has been timed out", player->get_name());
		}
	}


	void reaction::process(player_ptr player)
	{
		if (!player->is_valid())
			return;
		if ((player->is_friend() && g.session.trust_friends) || player->is_trusted || g.session.trust_session)
			return;

		if (log)
		{
			LOGF(WARNING, "Received {} from {} ({})", m_event_name, player->get_name(), player->get_rockstar_id());
		}

		if (announce_in_chat)
		{
			auto p_name = player->get_name();

			auto msg = std::format("{} {}",
       g.session.chat_output_prefix, std::vformat(g_translation_service.get_translation(m_announce_message), std::make_format_args(p_name)));

			chat::send_message(msg);
		}

		if (notify)
		{
			auto p_name = player->get_name();

			g_notification_service.push_warning("PROTECTIONS"_T.data(),
       std::vformat(g_translation_service.get_translation(m_notify_message), std::make_format_args(p_name)));
		}

		process_common(player);
	}

	// This function provides the same notification capabilities as process, but without further kick/timeout actions
	// Probably no point announcing to chat, either
	void reaction::only_notify(player_ptr player)
	{
		if (!player->is_valid())
			return;
		if ((player->is_friend() && g.session.trust_friends) || player->is_trusted || g.session.trust_session)
			return;

		if (log)
		{
			LOGF(WARNING, "Received {} from {} ({})", m_event_name, player->get_name(), player->get_rockstar_id());
		}

		if (notify)
		{
			auto p_name = player->get_name();

			// Use a different notification since the default start_script reaction is "Blocked Start Script"
			g_notification_service.push_warning("PROTECTIONS"_T.data(),
       std::vformat("REACTION_START_SCRIPT_ALLOWED"_T.data(), std::make_format_args(p_name)));
		}
	}
}
