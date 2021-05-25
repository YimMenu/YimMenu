#include "gta/enums.hpp"
#include "gta/net_game_event.hpp"
#include "hooking.hpp"
#include "natives.hpp"
#include "util/notify.hpp"

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
		rage::datBitBuffer* buffer = new rage::datBitBuffer((void*)bit_buffer, (uint32_t)bit_buffer_size);

		if (event_id > 90) return false;

		const char* event_name = *(char**)((DWORD64)event_manager + 8i64 * event_id + 241328);
		if (event_name == nullptr || source_player == nullptr || source_player->player_id < 0 || source_player->player_id >= 32)
		{
			g_pointers->m_send_event_ack(event_manager, source_player, target_player, event_index, event_handled_bitset);
			return false;
		}

		switch ((RockstarEvent)event_id)
		{
		case RockstarEvent::NETWORK_CLEAR_PED_TASKS_EVENT:
		{
			if (source_player->player_id < 32)
			{
				g_pointers->m_send_event_ack(event_manager, source_player, target_player, event_index, event_handled_bitset);

				notify::blocked_event(event_name, source_player->player_id);

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
				notify::blocked_event(event_name, source_player->player_id);

				// player is spawning modded cash
			}

			break;
		}
		case RockstarEvent::NETWORK_CHECK_CODE_CRCS_EVENT:
		case RockstarEvent::REPORT_MYSELF_EVENT:
		{
			notify::blocked_event(event_name, source_player->player_id);
			// player sending this event is a modder

			break;
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
		case RockstarEvent::GAME_CLOCK_EVENT:
		{
			uint32_t hour, min, sec;
			buffer->Seek(21);
			buffer->ReadDword(&hour, 6);
			buffer->ReadDword(&min, 7);
			buffer->ReadDword(&sec, 7);

			if (hour > 23 || min > 59 || sec > 59)
			{
				g_pointers->m_send_event_ack(event_manager, source_player, target_player, event_index, event_handled_bitset);

				notify::blocked_event(event_name, source_player->player_id);

				return false;
			}
			buffer->Seek(0);

			return true;
		}
		case RockstarEvent::GAME_WEATHER_EVENT:
		{
			uint32_t propagate, target, weather;

			buffer->ReadDword(&propagate, 1);
			buffer->ReadDword(&weather, 5);
			if (!propagate)
				buffer->ReadDword(&target, 9);

			if (weather > 12)
			{
				g_pointers->m_send_event_ack(event_manager, source_player, target_player, event_index, event_handled_bitset);

				notify::blocked_event(event_name, source_player->player_id);

				return false;
			}
			buffer->Seek(0);

			return true;
		}
		}

		//LOG(INFO) << "Received Event: " << event_name;

		return g_hooking->m_received_event_hook.get_original<decltype(&received_event)>()(event_manager, source_player, target_player, event_id, event_index, event_handled_bitset, bit_buffer_size, bit_buffer);
	}
}