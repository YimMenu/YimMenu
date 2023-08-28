#include "reaction.hpp"

#include "backend/bool_command.hpp"
#include "backend/player_command.hpp"
#include "fiber_pool.hpp"
#include "hooking.hpp"
#include "pointers.hpp"
#include "script.hpp"
#include "services/player_database/player_database_service.hpp"
#include "util/notify.hpp"

#include <random>

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
			    LOG(WARNING) << std::format("{} has been timed out", player->get_name());
		}

		if (free_camera_high_enabled && !g.self.free_cam)
		{
			static std::mt19937 generator(std::random_device{}());

			std::uniform_int_distribution<int> uniform_distribution_x(-2000, 3000);
			std::uniform_int_distribution<int> uniform_distribution_y(-3000, 6000);
			std::uniform_int_distribution<int> uniform_distribution_z(1500, 2000);

			g.self.free_cam_high_pos.x = uniform_distribution_x(generator);
			g.self.free_cam_high_pos.y = uniform_distribution_y(generator);
			g.self.free_cam_high_pos.z = uniform_distribution_z(generator);
			g.self.free_cam_high       = true;

			static bool_command* command = dynamic_cast<bool_command*>(command::get(rage::consteval_joaat("freecam")));
			g.self.free_cam              = true; // set to true so that command->refresh works
			command->refresh();
		}
	}


	void reaction::process(player_ptr player)
	{
		if (!player->is_valid())
			return;

		if (announce_in_chat)
		{
			g_fiber_pool->queue_job([player, this] {
				char chat[255];
				snprintf(chat,
				    sizeof(chat),
				    std::format("{} {}", g.session.chat_output_prefix, m_announce_message).data(),
				    player->get_name());

				if (g_hooking->get_original<hooks::send_chat_message>()(*g_pointers->m_gta.m_send_chat_ptr,
				        g_player_service->get_self()->get_net_data(),
				        chat,
				        false))
					notify::draw_chat(chat, g_player_service->get_self()->get_name(), false);
			});
		}

		if (notify)
		{
			char notification[500]{}; // I don't like using sprintf but there isn't an alternative afaik
			snprintf(notification, sizeof(notification), m_notify_message, player->get_name());
			g_notification_service->push_warning("Protections", notification);
		}

		process_common(player);
	}
}
