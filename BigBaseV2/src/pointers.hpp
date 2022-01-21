#pragma once
#include "common.hpp"
#include "gta/fwddec.hpp"
#include "gta/enums.hpp"
#include "gta/replay.hpp"
#include "gta/script_program.hpp"
#include "function_types.hpp"

#include "ASI Loader/Pools.h"

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

		CPedFactory **m_ped_factory{};
		CNetworkPlayerMgr **m_network_player_mgr{};

		rage::CReplayInterface** m_replay_interface{};
		functions::ptr_to_handle_t m_ptr_to_handle{};

		rage::scrNativeRegistrationTable *m_native_registration_table{};
		functions::get_native_handler_t m_get_native_handler{};
		functions::fix_vectors_t m_fix_vectors{};

		rage::atArray<GtaThread*> *m_script_threads{};
		rage::scrProgramTable *m_script_program_table{};
		functions::run_script_threads_t m_run_script_threads{};
		//OPENVHOOK
		functions::register_file_t m_register_file{};
		functions::get_script_handle_t m_get_script_handle{};
		std::int64_t **m_script_globals{};

		//OPENVHOOK
		rage::GenericPool* m_ped_pool{};
		rage::VehiclePool * m_vehicle_pool{};
		rage::GenericPool * m_prop_pool{};
		rage::GenericPool * m_pickup_pool{};
		rage::GenericPool * m_camera_pool{};

		CGameScriptHandlerMgr **m_script_handler_mgr{};

		IDXGISwapChain **m_swapchain{};

		PVOID m_blame_explode;
		PVOID m_model_spawn_bypass;
		PVOID m_native_return;
		PVOID m_is_dlc_present;

		PVOID m_error_screen{};

		functions::get_net_game_player* m_get_net_game_player{};

		PVOID m_gta_thread_start{};
		PVOID m_gta_thread_tick{};
		PVOID m_gta_thread_kill{};

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

		functions::spectate_player* m_spectate_player{};
	};

	inline pointers *g_pointers{};
}
