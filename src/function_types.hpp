#pragma once
#include <rage/rlTaskStatus.hpp>

class CMsgJoinResponse;
class NetworkGameFilterMatchmakingComponent;
class sCloudFile;
class CPlayerGameStateDataNode;
class CVehicleGadgetDataNode;
enum eVehicleGadgetType : uint32_t;

namespace rage
{
	class netConnectionManager;
	class netConnectionPeer;
	class snMsgRemoveGamersFromSessionCmd;
	class snSession;
	class snPlayer;
	class CDynamicEntity;
	class netTimeSyncMsg;
	class snConnectToPeerTaskData;
	class snConnectToPeerTaskResult;
	class rlScHandle;
	class rlQueryPresenceAttributesContext;
}

namespace datafile_commands
{
	class SveFileObject;
}

namespace big::functions
{
	using run_script_threads = bool (*)(std::uint32_t ops_to_execute);
	using get_native_handler = rage::scrNativeHandler (*)(rage::scrNativeRegistrationTable* registration_table, rage::scrNativeHash hash);
	using fix_vectors = void (*)(rage::scrNativeCallContext* call_ctx);

	using get_net_game_player = CNetGamePlayer* (*)(Player player);

	using trigger_script_event = void (*)(int event_group, int64_t* args, int arg_count, int player_bits);


	using increment_stat_event = bool (*)(uint64_t net_event_struct, int64_t sender, int64_t a3);

	using ptr_to_handle = Entity (*)(void*);
	using handle_to_ptr = rage::CDynamicEntity* (*)(Entity);

	using check_chat_profanity              = int(__int64 chat_type, const char* input, const char** output);
	using write_player_game_state_data_node = bool (*)(rage::netObject* plr, CPlayerGameStateDataNode* node);

	using get_gameplay_cam_coords = Vector3 (*)();

	using get_screen_coords_for_world_coords = bool (*)(float* world_coords, float* out_x, float* out_y);

	using give_pickup_rewards = void (*)(int players, uint32_t hash);

	// Bitbuffer read/write START
	using read_bitbuf_dword  = bool (*)(rage::datBitBuffer* buffer, PVOID read, int bits);
	using read_bitbuf_string = bool (*)(rage::datBitBuffer* buffer, char* read, int bits);
	using read_bitbuf_bool   = bool (*)(rage::datBitBuffer* buffer, bool* read, int bits);
	using read_bitbuf_array  = bool (*)(rage::datBitBuffer* buffer, PVOID read, int bits, int unk);
	using write_bitbuf_qword = bool (*)(rage::datBitBuffer* buffer, uint64_t val, int bits);
	using write_bitbuf_dword = bool (*)(rage::datBitBuffer* buffer, uint32_t val, int bits);
	using write_bitbuf_int64 = bool (*)(rage::datBitBuffer* buffer, int64_t val, int bits);
	using write_bitbuf_int32 = bool (*)(rage::datBitBuffer* buffer, int32_t val, int bits);
	using write_bitbuf_bool  = bool (*)(rage::datBitBuffer* buffer, bool val, int bits);
	using write_bitbuf_array = bool (*)(rage::datBitBuffer* buffer, void* val, int bits, int unk);

	// Bitbuffer read/write END
	// Received Event Signatures START
	using send_event_ack = void (*)(rage::netEventMgr* event_manager, CNetGamePlayer* source_player, CNetGamePlayer* target_player, int event_index, int event_handled_bitset);
	// Received Event Signatures END

	//Sync signatures START
	using get_sync_type_info = const char* (*)(uint16_t sync_type, char a2);

	using get_sync_tree_for_type = rage::netSyncTree* (*)(CNetworkObjectMgr* mgr, uint16_t sync_type);

	using get_net_object = rage::netObject* (*)(CNetworkObjectMgr* mgr, int16_t id, bool can_delete_be_pending);

	using get_net_object_for_player = rage::netObject* (*)(CNetworkObjectMgr*, int16_t, CNetGamePlayer*, bool);

	using read_bitbuffer_into_sync_tree = void (*)(rage::netSyncTree* tree, uint64_t flag, uint32_t flag2, rage::datBitBuffer* buffer, uint64_t netLogStub);
	//Sync signatures END

	using reset_network_complaints = void (*)(CNetComplaintMgr* mgr);

	using fidevice_get_device = rage::fiDevice* (*)(const char* path, bool allow_root);
	using fipackfile_ctor     = rage::fiPackfile* (*)(rage::fiPackfile* this_);
	using fipackfile_open_archive = bool (*)(rage::fiPackfile* this_, const char* archive, bool b_true, int type, intptr_t very_false);
	using fipackfile_mount   = bool (*)(rage::fiPackfile* this_, const char* mount_point);
	using fipackfile_unmount = bool (*)(const char* mount_point);

	using start_get_session_by_gamer_handle = bool (*)(int profile_index, rage::rlGamerHandle* handles, int count, rage::rlSessionByGamerTaskResult* result, int unk, bool* success, rage::rlTaskStatus* state);
	using start_matchmaking_find_sessions = bool (*)(int profile_index, int available_slots, NetworkGameFilterMatchmakingComponent* m_filter, unsigned int max_sessions, rage::rlSessionInfo* result_sessions, int* result_session_count, rage::rlTaskStatus* state);
	using start_get_presence_attributes = bool (*)(int profile_index, rage::rlScHandle* handle, rage::rlQueryPresenceAttributesContext* contexts, int count, rage::rlTaskStatus* state);
	using join_session_by_info = bool (*)(Network* network, rage::rlSessionInfo* info, int unk, int flags, rage::rlGamerHandle* handles, int handlecount);

	using generate_uuid = bool (*)(std::uint64_t* uuid);

	using get_vehicle_gadget_array_size = int (*)(eVehicleGadgetType type);

	using write_join_response_data = bool (*)(CMsgJoinResponse* response, void* data, int size, uint32_t* size_used);

	using queue_packet = bool (*)(rage::netConnectionManager* mgr, int msg_id, void* data, int size, int flags, void* unk);

	using generate_uuid = bool (*)(std::uint64_t* uuid);

	using send_chat_message = bool (*)(int64_t* send_chat_ptr, rage::rlGamerInfo* gamer_info, char* message, bool is_team);

	using send_network_damage = void (*)(CEntity* source, CEntity* target, rage::fvector3* position, int hit_component, bool override_default_damage, int weapon_type, float override_damage, int tire_index, int suspension_index, int flags, std::uint32_t action_result_hash, std::int16_t action_result_id, int action_unk, bool hit_weapon, bool hit_weapon_ammo_attachment, bool silenced, bool unk, rage::fvector3* impact_direction);
	using request_ragdoll = void (*)(uint16_t object_id);
	using request_control = void (*)(rage::netObject* net_object);

	using get_connection_peer = rage::netConnectionPeer* (*)(rage::netConnectionManager* manager, int peer_id);
	using send_remove_gamer_cmd = void (*)(rage::netConnectionManager* net_connection_mgr, rage::netConnectionPeer* player, int connection_id, rage::snMsgRemoveGamersFromSessionCmd* cmd, int flags);
	using handle_remove_gamer_cmd = void* (*)(rage::snSession* session, rage::snPlayer* origin, rage::snMsgRemoveGamersFromSessionCmd* cmd);

	using script_vm = int (*)(uint64_t* stack, int64_t** scr_globals, rage::scrProgram* program, rage::scrThreadContext* ctx);

	using encode_session_info = bool (*)(rage::rlSessionInfo* info, char* buffer, int buffer_size, int* bytes_written);
	using decode_session_info = bool (*)(rage::rlSessionInfo* out_info, char* buffer, int* bytes_read);
	using decode_peer_info    = bool (*)(rage::rlGamerInfoBase* info, char* buffer, int* bytes_read);

	using load_cloud_file          = void (*)(sCloudFile** out_cloud_file, char* buffer, int size, const char* reason);
	using set_as_active_cloud_file = void (*)(datafile_commands::SveFileObject* object, sCloudFile** file);
	using save_json_data = char* (*)(datafile_commands::SveFileObject* object, int* out_length, const char* reason);

	using sync_network_time = bool (*)(rage::netConnectionManager* mgr, rage::netConnectionPeer* peer, int connection_id, rage::netTimeSyncMsg* msg, int flags);
	using send_packet = bool (*)(rage::netConnectionManager* mgr, rage::netConnectionPeer* peer, int connection_id, void* data, int size, int flags);
	using connect_to_peer = bool (*)(rage::netConnectionManager* mgr, rage::rlGamerInfoBase* gamer_info, rage::snConnectToPeerTaskData* data, rage::snConnectToPeerTaskResult* result, rage::rlTaskStatus* status);

	using clear_ped_tasks_network = void (*)(CPed* ped, bool immediately);

	using get_next_carriage      = void* (*)(void* carriage);
	using get_entity_attached_to = rage::CDynamicEntity* (*)(rage::CDynamicEntity* entity);
}
