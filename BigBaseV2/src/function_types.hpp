#pragma once
#include "common.hpp"
#include "gta/fwddec.hpp"
#include "gta/player.hpp"
#include "gta/natives.hpp"
#include "gta/replay.hpp"

namespace big::functions
{
	using run_script_threads_t = bool(*)(std::uint32_t ops_to_execute);
	using get_native_handler_t = rage::scrNativeHandler(*)(rage::scrNativeRegistrationTable*, rage::scrNativeHash);
	using fix_vectors_t = void(*)(rage::scrNativeCallContext*);

	using error_screen = void(char* entryHeader, char* entryLine1, int instructionalKey, char* entryLine2, BOOL p4, Any p5, Any* p6, Any* p7, BOOL background);

	using get_net_game_player = CNetGamePlayer*(Player player);

	using gta_thread_tick = __int64(GtaThread* a1, unsigned int a2);
	using gta_thread_kill = __int64(GtaThread* a1);

	using trigger_script_event = int(int unk0, int* args, int argCount, int bitFlags);

	using increment_stat_event = bool(uint64_t net_event_struct, int64_t sender, int64_t a3);

	using ptr_to_handle = Object(rage::CObject* object);

	// Received Event Signatures START
	using read_bitbuf_array = bool(rage::datBitBuffer* buffer, PVOID read, int bits, int);
	using read_bitbuf_dword = bool(rage::datBitBuffer* buffer, PVOID read, int bits);
	using received_event = bool(
		rage::netEventMgr* event_manager,
		CNetGamePlayer* source_player,
		CNetGamePlayer* target_player,
		uint16_t event_id,
		int event_index,
		int event_handled_bitset,
		int64_t bit_buffer_size,
		int64_t bit_buffer
	);
	using send_event_ack = void(rage::netEventMgr* event_manager, CNetGamePlayer* source_player, CNetGamePlayer* target_player, int event_index, int event_handled_bitset);
	// Received Event Signatures END

	using spectate_player = bool(bool toggle, Ped player);
}
