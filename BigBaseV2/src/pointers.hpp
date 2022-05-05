#pragma once
#include "common.hpp"
#include "CNetworkPlayerMgr.hpp"
#include "FriendRegistry.hpp"
#include "gta/fwddec.hpp"
#include "gta/enums.hpp"
#include "gta/replay.hpp"
#include "gta/script_program.hpp"
#include "function_types.hpp"

namespace big
{
	class pointers
	{
	public:
		explicit pointers();
		~pointers();
	public:
		HWND m_hwnd{};

		eGameState *m_game_state{};
		bool *m_is_session_started{};

		CPedFactory** m_ped_factory{};
		CNetworkPlayerMgr** m_network_player_mgr{};
		CNetworkObjectMgr** m_network_object_mgr{};

		rage::CReplayInterface** m_replay_interface{};
		functions::ptr_to_handle* m_ptr_to_handle{};

		rage::scrNativeRegistrationTable *m_native_registration_table{};
		functions::get_native_handler_t m_get_native_handler{};
		functions::fix_vectors_t m_fix_vectors{};

		rage::atArray<GtaThread*> *m_script_threads{};
		rage::scrProgramTable *m_script_program_table{};
		functions::run_script_threads_t m_run_script_threads{};
		std::int64_t **m_script_globals{};

		CGameScriptHandlerMgr **m_script_handler_mgr{};

		IDXGISwapChain **m_swapchain{};

		int* m_resolution_x;
		int* m_resolution_y;

		PVOID m_blame_explode;
		PVOID m_model_spawn_bypass;
		PVOID m_native_return;
		PVOID m_is_dlc_present;

		PVOID m_error_screen{};

		FriendRegistry* m_friend_registry{};

		functions::get_screen_coords_for_world_coords* m_get_screen_coords_for_world_coords{};

		functions::get_net_game_player* m_get_net_game_player{};

		PVOID m_gta_thread_start{};
		PVOID m_gta_thread_tick{};
		PVOID m_gta_thread_kill{};

		PVOID m_network_player_mgr_shutdown;
		PVOID m_net_array_handler;

		PVOID m_player_has_joined{};
		PVOID m_player_has_left{};

		functions::get_gameplay_cam_coords* m_get_gamplay_cam_coords;

		functions::increment_stat_event* m_increment_stat_event{};

		PVOID m_scripted_game_event{};
		functions::trigger_script_event* m_trigger_script_event{};

		// Received Event Signatures START
		functions::read_bitbuf_array* m_read_bitbuf_array{};
		functions::read_bitbuf_dword* m_read_bitbuf_dword{};
		functions::received_event* m_received_event{};
		functions::send_event_ack* m_send_event_ack{};
		// Received Event Signatures END

		PVOID m_send_net_info_to_lobby{};

		PVOID m_chat_receive{};
		PVOID m_censor_chat_text{};
	};

	inline pointers *g_pointers{};
}
