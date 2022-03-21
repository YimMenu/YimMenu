#include "gta/enums.hpp"
#include "gta/net_game_event.hpp"
#include "hooking.hpp"

namespace big
{
	bool hooks::received_event(
		rage::netEventMgr* event_manager,
		CNetGamePlayer* source_player,
		CNetGamePlayer* target_player,
		uint16_t event_id,
		int event_index,
		int event_handled_bitset,
		int64_t bit_buffer_size,
		int64_t bit_buffer
	)
	{
		auto buffer = std::make_unique<rage::datBitBuffer>((void*)bit_buffer, (uint32_t)bit_buffer_size);

		if (event_id > 90u) return false;

		const char* event_name = *(char**)((DWORD64)event_manager + 8i64 * event_id + 243376);
		if (event_name == nullptr || source_player == nullptr || source_player->m_player_id < 0 || source_player->m_player_id >= 32)
		{
			g_pointers->m_send_event_ack(event_manager, source_player, target_player, event_index, event_handled_bitset);
			return false;
		}

		switch ((RockstarEvent)event_id)
		{
		case RockstarEvent::NETWORK_CLEAR_PED_TASKS_EVENT:
		{
			if (source_player->m_player_id < 32)
			{
				g_pointers->m_send_event_ack(event_manager, source_player, target_player, event_index, event_handled_bitset);
				
				g_notification_service->push_warning("Protection",
					fmt::format("{} possible attempt at freezing entity.", source_player->get_name())
				);

				return false;
			}

			break;
		}
		// Don't block this event, we still want to report this player
		// because if we still report others, our account seems less fishy
		case RockstarEvent::REPORT_CASH_SPAWN_EVENT:
		{
			uint32_t money;

			buffer->Seek(64);
			buffer->ReadDword(&money, 32);
			buffer->Seek(0);

			if (money >= 2000)
			{
				g_notification_service->push_warning("Protection",
					fmt::format("{} is spawning cash.", source_player->get_name())
				);
			}

			break;
		}
		// player sending this event is a modder
		case RockstarEvent::NETWORK_CHECK_CODE_CRCS_EVENT:
		case RockstarEvent::REPORT_MYSELF_EVENT:
		{
			g_notification_service->push_warning("Protection",
				fmt::format("Detected {} as cheating.", source_player->get_name())
			);

			break;
		}
		case RockstarEvent::REQUEST_CONTROL_EVENT:
		{
			g_pointers->m_send_event_ack(event_manager, source_player, target_player, event_index, event_handled_bitset);
			
			g_notification_service->push_warning("Protection",
				fmt::format("Denied player control request from {}", source_player->get_name())
			);

			return false;
		}
		//case RockstarEvent::GIVE_PICKUP_REWARDS_EVENT:
		//{
		//	uint32_t amount, hash;
		//	buffer->ReadDword(&amount, 3);
		//	buffer->ReadDword(&hash, 32);

		//	if (func::is_crash_reward(hash) && func::is_crash_pickup(hash))
		//	{
		//		g_pointers->m_send_event_ack(event_manager, source_player, target_player, event_index, event_handled_bitset);

		//		notify::blocked_event(event_name, source_player->player_id);

		//		return false;
		//	}
		//	buffer->Seek(0);

		//	return true;
		//}
		}

		return g_hooking->m_received_event_hook.get_original<decltype(&received_event)>()(event_manager, source_player, target_player, event_id, event_index, event_handled_bitset, bit_buffer_size, bit_buffer);
	}
}