#pragma once
#include "common.hpp"
#include "base/HashTable.hpp"
#include "function_types.hpp"
#include "gta/fwddec.hpp"
#include "gta/replay.hpp"
#include "memory/byte_patch.hpp"

class CCommunications;
class FriendRegistry;
class CNetworkPlayerMgr;
class Network;

namespace big
{
	class pointers
	{
	public:
		explicit pointers();
		~pointers();
	public:
		HWND m_hwnd{};

		eGameState* m_game_state{};
		bool* m_is_session_started{};

		CPedFactory** m_ped_factory{};
		CNetworkPlayerMgr** m_network_player_mgr{};
		CNetworkObjectMgr** m_network_object_mgr{};
		rage::CReplayInterface** m_replay_interface{};

		functions::ptr_to_handle m_ptr_to_handle{};
		functions::get_script_handle_t m_get_script_handle{};
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

		memory::byte_patch* m_max_wanted_level;
		memory::byte_patch* m_max_wanted_level_2;

		PVOID m_blame_explode;
		PVOID m_model_spawn_bypass;
		PVOID m_world_model_spawn_bypass;
		PVOID m_native_return;
		PVOID m_get_label_text;
		functions::multiplayer_chat_filter* m_multiplayer_chat_filter{};
		functions::write_player_game_state_data_node m_write_player_game_state_data_node{};

		FriendRegistry* m_friend_registry{};

		functions::get_screen_coords_for_world_coords m_get_screen_coords_for_world_coords{};

		HashTable<CBaseModelInfo*>* m_model_table;

		PVOID m_gta_thread_start{};
		PVOID m_gta_thread_kill{};

		PVOID m_network_player_mgr_init;
		PVOID m_network_player_mgr_shutdown;

		functions::get_gameplay_cam_coords m_get_gameplay_cam_coords;

		functions::give_pickup_rewards m_give_pickup_rewards{};

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
		PVOID m_received_clone_sync;
		functions::get_sync_tree_for_type m_get_sync_tree_for_type{};
		functions::get_sync_type_info m_get_sync_type_info{};
		functions::get_net_object m_get_net_object{};
		functions::get_net_object_for_player m_get_net_object_for_player{};
		functions::read_bitbuffer_into_sync_tree m_read_bitbuffer_into_sync_tree{};
		//Sync Signatures END

		PVOID m_send_net_info_to_lobby{};

		PVOID m_receive_net_message{};
		PVOID m_get_network_event_data{};
		PVOID m_assign_physical_index{};

		PVOID m_format_metric_for_sending;

		Network** m_network;

		functions::start_get_session_by_gamer_handle m_start_get_session_by_gamer_handle;
		functions::join_session_by_info m_join_session_by_info;

		uint8_t* m_bypass_max_count_of_active_sticky_bombs;

		functions::reset_network_complaints m_reset_network_complaints{};

		functions::fidevice_get_device m_fidevice_get_device{};
		uintptr_t m_fidevices{};
		uint16_t* m_fidevices_len{};
		functions::fipackfile_ctor m_fipackfile_ctor{};
		rage::fiPackfile** m_fipackfile_instances{};
		functions::fipackfile_open_archive m_fipackfile_open_archive{};
		functions::fipackfile_mount m_fipackfile_mount{};
		functions::fipackfile_unmount m_fipackfile_unmount{};

		const char* m_game_version;
		const char* m_online_version;

		PVOID m_invalid_mods_crash_detour{};

		int64_t** m_send_chat_ptr{};
		functions::send_chat_message m_send_chat_message{};

		PVOID m_init_native_tables{};
		PVOID m_script_vm{};

		functions::generate_uuid m_generate_uuid{};
		std::uint64_t* m_host_token{};
		rage::rlGamerInfo* m_profile_gamer_info{}; // per profile gamer info
		rage::rlGamerInfo* m_player_info_gamer_info{}; // the gamer info that is applied to CPlayerInfo
		CCommunications** m_communications{};

		PVOID m_update_presence_attribute_int{};
		PVOID m_update_presence_attribute_string{};
	};

	inline pointers* g_pointers{};
}
