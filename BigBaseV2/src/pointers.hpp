#pragma once
#include "common.hpp"
#include "base/HashTable.hpp"
#include "function_types.hpp"
#include "gta/fwddec.hpp"
#include "gta/replay.hpp"
#include "network/CNetworkPlayerMgr.hpp"
#include "socialclub/FriendRegistry.hpp"

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

		PVOID m_blame_explode;
		PVOID m_model_spawn_bypass;
		PVOID m_native_return;
		PVOID m_is_dlc_present;
		PVOID m_network_group_override;
		PUSHORT m_spectator_check;
		PVOID m_get_label_text;

		FriendRegistry* m_friend_registry{};

		functions::get_screen_coords_for_world_coords m_get_screen_coords_for_world_coords{};

		HashTable<CBaseModelInfo*>* m_model_table;

		PVOID m_gta_thread_start{};
		PVOID m_gta_thread_kill{};

		PVOID m_network_player_mgr_init;
		PVOID m_network_player_mgr_shutdown;

		functions::get_gameplay_cam_coords m_get_gameplay_cam_coords;

		functions::give_pickup_rewards m_give_pickup_rewards{};
		
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
		//Sync Signatures END

		PVOID m_send_net_info_to_lobby{};

		PVOID m_receive_net_message{};
		PVOID m_get_network_event_data{};
		PVOID m_assign_physical_index{};
	};

	inline pointers* g_pointers{};
}
