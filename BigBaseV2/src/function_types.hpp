#pragma once
#include "common.hpp"
#include "gta/fwddec.hpp"
#include "gta/player.hpp"
#include "gta/natives.hpp"
#include "gta/replay.hpp"

namespace big::functions
{
	using run_script_threads_t = bool(*)(std::uint32_t ops_to_execute);
	using get_native_handler_t = rage::scrNativeHandler(*)(rage::scrNativeRegistrationTable* registration_table, rage::scrNativeHash hash);
	using fix_vectors_t = void(*)(rage::scrNativeCallContext* call_ctx);

	using get_net_game_player = CNetGamePlayer*(*)(Player player);

	using trigger_script_event = void(*)(int event_group, int64_t* args, int arg_count, int player_bits);

	using increment_stat_event = bool(*)(uint64_t net_event_struct, int64_t sender, int64_t a3);

	using ptr_to_handle = Entity(*)(void* entity);

	using get_screen_coords_for_world_coords = bool(*)(float* world_coords, float* out_x, float* out_y);

	using give_pickup_rewards = void(*)(int players, uint32_t hash);

	// Received Event Signatures START
	using read_bitbuf_array = bool(*)(rage::datBitBuffer* buffer, PVOID read, int bits, int unk);
	using read_bitbuf_dword = bool(*)(rage::datBitBuffer* buffer, PVOID read, int bits);

	using send_event_ack = void(*)(rage::netEventMgr* event_manager, CNetGamePlayer* source_player, CNetGamePlayer* target_player, int event_index, int event_handled_bitset);
	// Received Event Signatures END

	//Sync signatures START
	using get_sync_type_info = const char*(*)(uint16_t sync_type, char a2);

	using get_sync_tree_for_type = int64_t(*)(CNetworkObjectMgr* mgr, uint16_t sync_type);

	using get_net_object = rage::netObject*(*)(CNetworkObjectMgr* mgr, int16_t id, bool unk3);

	using get_net_object_for_player = rage::netObject*(*)(CNetworkObjectMgr*, int16_t, CNetGamePlayer*, bool);
	//Sync signatures END
}