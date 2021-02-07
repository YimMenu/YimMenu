#pragma once
#include "common.hpp"
#include "gta/fwddec.hpp"
#include "gta/replay.hpp"
#include "gta/natives.hpp"

namespace big::functions
{
	using run_script_threads_t = bool(*)(std::uint32_t ops_to_execute);
	using get_native_handler_t = rage::scrNativeHandler(*)(rage::scrNativeRegistrationTable*, rage::scrNativeHash);
	using fix_vectors_t = void(*)(rage::scrNativeCallContext*);

	using error_screen = void(char* entryHeader, char* entryLine1, int instructionalKey, char* entryLine2, BOOL p4, Any p5, Any* p6, Any* p7, BOOL background);
	using get_event_data = bool(int32_t eventGroup, int32_t eventIndex, int64_t* args, uint32_t argCount);
	using get_label_text = const char*(void* unk, const char* label);
	using get_player_name = char*(Player player);
	using get_net_player = int(Player player);
	using increment_stat_event = bool(uint64_t net_event_struct, int64_t sender, int64_t a3);

	using read_bitbuf_dword = bool(rage::datBitBuffer* buffer, uint32_t* read, int bits);
	using received_event = bool(rage::netEventMgr* event_manager, CNetGamePlayer* source_player, CNetGamePlayer* target_player, uint16_t event_id, int event_index, int event_handled_bitset, rage::datBitBuffer* buffer);
	using send_event_ack = void(rage::netEventMgr* event_manager, CNetGamePlayer* source_player, CNetGamePlayer* target_player, int event_index, int event_handled_bitset);

	using script_event_handler = bool(void* events, CNetGamePlayer* sourcePlayer, CNetGamePlayer* targetPlayer);
	using set_session_weather = void(char a1, int a2, int a3, int64_t a4);
	using spectate_player = bool(bool toggle, Ped player);
	using sync_local_time = void(int h, int m);
	using trigger_script_event = int(bool unk0, int64_t* args, int argCount, int bitFlags);

	using ptr_to_handle = int(rage::CObject* a1);
}
