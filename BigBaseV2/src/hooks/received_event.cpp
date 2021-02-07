#include "hooking.hpp"
#include "gta/enums.hpp"
#include "gta/net_game_event.hpp"

namespace big
{
	bool hooks::received_event(
		rage::netEventMgr* event_manager,
		CNetGamePlayer* source_player,
		CNetGamePlayer* target_player,
		uint16_t event_id,
		int event_index,
		int event_handled_bitset,
		rage::datBitBuffer* buffer
	)
	{
		if (event_id > 91) return false;

		switch (event_id)
		{
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

			if (weather > 12 || !propagate)
			{
				g_pointers->m_send_event_ack(event_manager, source_player, target_player, event_index, event_handled_bitset);

				return false;
			}
			buffer->Seek(0);

			return true;
		}
		}

		return true;
	}
}