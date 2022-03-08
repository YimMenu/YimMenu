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

	using get_net_game_player = CNetGamePlayer*(Player player);

	using trigger_script_event = void(int event_group, int64_t* args, int arg_count, int player_bits);

	using increment_stat_event = bool(uint64_t net_event_struct, int64_t sender, int64_t a3);

	using ptr_to_handle = Object(rage::CObject* object);

	using get_screen_coords_for_world_coords = bool(float* world_coords, float* out_x, float* out_y);

	using get_gameplay_cam_coords = Vector3();

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
}
