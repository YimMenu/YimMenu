#pragma once
#include "common.hpp"
#include "gta/fwddec.hpp"
#include "gta/player.hpp"
#include "gta/natives.hpp"
#include "gta/replay.hpp"
#include "network/stubs.hpp"
#include "network/CNetComplaintMgr.hpp"
#include "network/Network.hpp"
#include "rage/rlSessionByGamerTaskResult.hpp"

namespace big::functions
{
	using run_script_threads = bool(*)(std::uint32_t ops_to_execute);
	using get_native_handler = rage::scrNativeHandler(*)(rage::scrNativeRegistrationTable* registration_table, rage::scrNativeHash hash);
	using fix_vectors = void(*)(rage::scrNativeCallContext* call_ctx);

	using get_net_game_player = CNetGamePlayer*(*)(Player player);

	using trigger_script_event = void(*)(int event_group, int64_t* args, int arg_count, int player_bits);

	using increment_stat_event = bool(*)(uint64_t net_event_struct, int64_t sender, int64_t a3);

	using ptr_to_handle = Entity(*)(void* entity);

	using get_gameplay_cam_coords = Vector3(*)();

	using get_screen_coords_for_world_coords = bool(*)(float* world_coords, float* out_x, float* out_y);

	using give_pickup_rewards = void(*)(int players, uint32_t hash);

	// Bitbuffer read/write START
	using read_bitbuf_dword = bool(*)(rage::datBitBuffer* buffer, PVOID read, int bits);
	using read_bitbuf_string = bool(*)(rage::datBitBuffer* buffer, char* read, int bits);
	using read_bitbuf_bool = bool(*)(rage::datBitBuffer* buffer, bool* read, int bits);
	using read_bitbuf_array = bool(*)(rage::datBitBuffer* buffer, PVOID read, int bits, int unk);
	using write_bitbuf_qword = bool(*)(rage::datBitBuffer* buffer, uint64_t val, int bits);
	using write_bitbuf_dword = bool(*)(rage::datBitBuffer* buffer, uint32_t val, int bits);
	using write_bitbuf_int64 = bool(*)(rage::datBitBuffer* buffer, int64_t val, int bits);
	using write_bitbuf_int32 = bool(*)(rage::datBitBuffer* buffer, int32_t val, int bits);
	using write_bitbuf_bool = bool(*)(rage::datBitBuffer* buffer, bool val, int bits);
	using write_bitbuf_array = bool(*)(rage::datBitBuffer* buffer, uint8_t* val, int bits, int unk);
	// Bitbuffer read/write END

	using register_file_t = uint32_t * (*)(int*, const char*, bool, const char*, bool);

	using get_script_handle_t = int64_t(*)(int64_t);

	using get_net_player_from_unk = CNetGamePlayer*(__int64);

	using send_chat_message = bool(__int64 ptr, __int64 peerId, const char* message, bool isTeam);

	using start_get_session_by_gamer_handle = bool(*)(int metric_manager, rage::rlGamerHandle* handles, int count, rage::rlSessionByGamerTaskResult* result, int unk, bool* success, int* state);
	using join_session_by_info = bool(*)(Network* network, rage::rlSessionInfo* info, int unk, int flags, rage::rlGamerHandle* handles, int handlecount);

	using get_connection_peer = rage::netConnectionPeer* (*)(rage::netConnectionManager* manager, uint64_t peer_id);

	using send_remove_gamer_cmd = void(*)(rage::netConnectionManager* net_connection_mgr, rage::netConnectionPeer* player, int connection_id, rage::snMsgRemoveGamersFromSessionCmd* cmd, int flags);

	using handle_remove_gamer_cmd = void* (*)(rage::snSession* session, rage::snPlayer* origin, rage::snMsgRemoveGamersFromSessionCmd* cmd);

	// Received Event Signatures START
	using send_event_ack = void(*)(rage::netEventMgr* event_manager, CNetGamePlayer* source_player, CNetGamePlayer* target_player, int event_index, int event_handled_bitset);
	// Received Event Signatures END

	//Sync signatures START
	using get_sync_type_info = const char*(*)(uint16_t sync_type, char a2);

	using get_sync_tree_for_type = int64_t(*)(CNetworkObjectMgr* mgr, uint16_t sync_type);

	using get_net_object = rage::netObject*(*)(CNetworkObjectMgr* mgr, int16_t id, bool unk3);
	//Sync signatures END

	using reset_network_complaints = void(*)(CNetComplaintMgr* mgr);
}