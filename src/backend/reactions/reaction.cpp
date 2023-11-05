#include "reaction.hpp"

#include "backend/player_command.hpp"
#include "fiber_pool.hpp"
#include "hooking.hpp"
#include "pointers.hpp"
#include "script.hpp"
#include "services/player_database/player_database_service.hpp"
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
		if (add_to_player_db)
		{
			auto entry = g_player_database_service->get_or_create_player(player);

			if (block_joins)
			{
				entry->block_join = true;
				g_player_database_service->save();
			}
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
			uint64_t rockstar_id = player->get_net_data() == nullptr ? 0 : player->get_net_data()->m_gamer_handle.m_rockstar_id;
			LOGF(WARNING, "Received {} from {} ({})", m_event_name, player->get_name(), rockstar_id);
		}

		if (announce_in_chat)
		{
			g_fiber_pool->queue_job([player, this] {
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
			    std::vformat(g_translation_service.get_translation(m_notify_message), std::make_format_args(player->get_name())));
		}

		process_common(player);
	}
}
