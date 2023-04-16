#pragma once
#include <memory/handle.hpp>

class CCommunications;
class FriendRegistry;
class CNetworkPlayerMgr;
class Network;
class ChatData;
class ScInfo;
class GenericPool;
class VehiclePool;

namespace rage
{
	template<typename T>
	class atSingleton;
	class RageSecurity;
	class netTime;
	class rlGamerInfo;
}

namespace big
{
	// needed for serialization of the pointers cache
#pragma pack(push, 1)
	struct gta_pointers
	{
		memory::handle m_max_wanted_level;

		memory::handle m_blame_explode;

		memory::handle m_explosion_patch;

		memory::handle m_is_matchmaking_session_valid;

		memory::handle m_broadcast_patch;

		memory::handle m_creator_warp_cheat_triggered_patch;

		memory::handle m_ntqvm_caller;

		memory::handle m_sound_overload_detour;

		memory::handle m_disable_collision;

		memory::handle m_crash_trigger;

		eGameState* m_game_state{};
		bool* m_is_session_started{};

		CPedFactory** m_ped_factory{};
		CNetworkPlayerMgr** m_network_player_mgr{};
		CNetworkObjectMgr** m_network_object_mgr{};
		rage::CReplayInterface** m_replay_interface{};

		functions::ptr_to_handle m_ptr_to_handle{};
		functions::handle_to_ptr m_handle_to_ptr{};
		rage::scrNativeRegistrationTable* m_native_registration_table{};
		functions::get_native_handler m_get_native_handler{};
		functions::fix_vectors m_fix_vectors{};

		rage::atArray<GtaThread*>* m_script_threads{};
		rage::scrProgramTable* m_script_program_table{};
		functions::run_script_threads m_run_script_threads{};
		std::int64_t** m_script_globals{};

		CGameScriptHandlerMgr** m_script_handler_mgr{};

		IDXGISwapChain** m_swapchain{};

		int* m_resolution_x;
		int* m_resolution_y;

		uint32_t* m_region_code;

		PVOID m_world_model_spawn_bypass;
		PVOID m_native_return;
		PVOID m_get_label_text;
		functions::check_chat_profanity* m_check_chat_profanity{};
		functions::write_player_game_state_data_node m_write_player_game_state_data_node{};

		ChatData** m_chat_data;
		ScInfo* m_sc_info;
		FriendRegistry* m_friend_registry{};

		functions::get_screen_coords_for_world_coords m_get_screen_coords_for_world_coords{};

		HashTable<CBaseModelInfo*>* m_model_table;
		PVOID m_get_model_info;

		PVOID m_gta_thread_start{};
		PVOID m_gta_thread_kill{};

		PVOID m_network_player_mgr_init;
		PVOID m_network_player_mgr_shutdown;

		functions::get_gameplay_cam_coords m_get_gameplay_cam_coords;

		PVOID m_write_player_gamer_data_node{};

		functions::trigger_script_event m_trigger_script_event{};

		// Bitbuffer Read/Write START
		functions::read_bitbuf_dword m_read_bitbuf_dword{};
		functions::read_bitbuf_string m_read_bitbuf_string{};
		functions::read_bitbuf_bool m_read_bitbuf_bool{};
		functions::read_bitbuf_array m_read_bitbuf_array{};
		functions::write_bitbuf_qword m_write_bitbuf_qword{};
		functions::write_bitbuf_dword m_write_bitbuf_dword{};
		functions::write_bitbuf_int64 m_write_bitbuf_int64{};
		functions::write_bitbuf_int32 m_write_bitbuf_int32{};
		functions::write_bitbuf_bool m_write_bitbuf_bool{};
		functions::write_bitbuf_array m_write_bitbuf_array{};
		// Bitbuffer Read/Write END

		// Received Event Signatures START
		PVOID m_received_event{};
		functions::send_event_ack m_send_event_ack{};
		// Received Event Signatures END

		//Sync Signatures START
		PVOID m_received_clone_create;
		PVOID m_received_clone_sync;
		PVOID m_can_apply_data;
		functions::get_sync_tree_for_type m_get_sync_tree_for_type{};
		functions::get_sync_type_info m_get_sync_type_info{};
		functions::get_net_object m_get_net_object{};
		functions::read_bitbuffer_into_sync_tree m_read_bitbuffer_into_sync_tree{};
		//Sync Signatures END

		PVOID m_receive_net_message{};
		PVOID m_get_network_event_data{};
		PVOID m_assign_physical_index{};

		Network** m_network;

		functions::start_get_session_by_gamer_handle m_start_get_session_by_gamer_handle;
		functions::start_matchmaking_find_sessions m_start_matchmaking_find_sessions;
		functions::join_session_by_info m_join_session_by_info;

		functions::reset_network_complaints m_reset_network_complaints{};

		functions::fidevice_get_device m_fidevice_get_device{};
		functions::fipackfile_ctor m_fipackfile_ctor{};
		rage::fiPackfile** m_fipackfile_instances{};
		functions::fipackfile_open_archive m_fipackfile_open_archive{};
		functions::fipackfile_mount m_fipackfile_mount{};
		functions::fipackfile_unmount m_fipackfile_unmount{};

		PVOID m_invalid_mods_crash_detour{};
		PVOID m_constraint_attachment_crash{};
		PVOID m_invalid_decal_crash{};
		PVOID m_task_parachute_object_0x270{};

		int64_t** m_send_chat_ptr{};
		functions::send_chat_message m_send_chat_message{};

		PVOID m_init_native_tables{};
		functions::script_vm m_script_vm{};

		functions::generate_uuid m_generate_uuid{};
		std::uint64_t* m_host_token{};
		rage::rlGamerInfo* m_profile_gamer_info{};     // per profile gamer info
		rage::rlGamerInfo* m_player_info_gamer_info{}; // the gamer info that is applied to CPlayerInfo
		CCommunications** m_communications{};

		PVOID m_serialize_ped_inventory_data_node;
		PVOID m_serialize_vehicle_gadget_data_node;
		functions::get_vehicle_gadget_array_size m_get_vehicle_gadget_array_size;

		PVOID m_handle_join_request;
		functions::write_join_response_data m_write_join_response_data;

		functions::queue_packet m_queue_packet;

		PVOID m_sort_session_details;

		PVOID m_add_player_to_session;
		PVOID m_send_chat_net_message;

		PVOID m_process_matchmaking_find_response;
		PVOID m_serialize_player_data_msg;

		PVOID m_serialize_join_request_message;

		functions::give_pickup_rewards m_give_pickup_rewards{};
		functions::send_network_damage m_send_network_damage;
		functions::request_ragdoll m_request_ragdoll;
		functions::request_control m_request_control;
		functions::clear_ped_tasks_network m_clear_ped_tasks_network;

		functions::get_connection_peer m_get_connection_peer{};
		functions::send_remove_gamer_cmd m_send_remove_gamer_cmd{};
		functions::handle_remove_gamer_cmd m_handle_remove_gamer_cmd{};

		PVOID m_broadcast_net_array{};

		rage::atSingleton<rage::RageSecurity>* m_security;
		PVOID m_prepare_metric_for_sending;

		PVOID m_queue_dependency;
		PVOID m_interval_check_func;

		PVOID m_send_session_matchmaking_attributes;

		PVOID m_serialize_take_off_ped_variation_task;

		PVOID m_create_script_handler;

		functions::encode_session_info m_encode_session_info;
		functions::decode_session_info m_decode_session_info;
		functions::decode_peer_info m_decode_peer_info;

		datafile_commands::SveFileObject* m_main_file_object;
		functions::load_cloud_file m_load_cloud_file;
		functions::set_as_active_cloud_file m_set_as_active_cloud_file;
		functions::save_json_data m_save_json_data;

		rage::netTime** m_network_time;
		functions::sync_network_time m_sync_network_time;

		functions::send_packet m_send_packet;
		functions::connect_to_peer m_connect_to_peer;

		PVOID m_fragment_physics_crash;
		PVOID m_fragment_physics_crash_2;

		PVOID m_infinite_train_crash;
		functions::get_next_carriage m_get_next_carriage;

		functions::get_entity_attached_to m_get_entity_attached_to;

		PVOID m_received_array_update;

		PVOID m_receive_pickup{};

		PVOID m_write_player_camera_data_node{};

		PVOID m_send_player_card_stats{};
		bool* m_force_player_card_refresh{};

		PVOID m_serialize_stats{};

		PVOID m_write_player_creation_data_node{};
		PVOID m_write_player_appearance_data_node{};

		PVOID m_enumerate_audio_devices{};
		PVOID m_direct_sound_capture_create{};
		bool* m_refresh_audio_input{};

		PVOID m_allow_weapons_in_vehicle{};

		PVOID m_taskjump_constructor{};

		PVOID m_write_vehicle_proximity_migration_data_node{};
		functions::migrate_object m_migrate_object{};

		const char* m_game_version{};
		const char* m_online_version{};

		GenericPool** m_ped_pool{};
		GenericPool** m_prop_pool{};
		VehiclePool*** m_vehicle_pool{};
	};
#pragma pack(pop)
	static_assert(sizeof(gta_pointers) % 8 == 0, "Pointers are not properly aligned");
}