#pragma once
#include "common.hpp"
#include "gta/fwddec.hpp"
#include "gta/enums.hpp"
#include "gta/replay.hpp"
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

		CPedFactory **m_ped_factory{};
		CNetworkPlayerMgr **m_network_player_mgr{};
		rage::CReplayInterface **m_replay_interface{};

		rage::scrNativeRegistrationTable *m_native_registration_table{};
		functions::get_native_handler_t m_get_native_handler{};
		functions::fix_vectors_t m_fix_vectors{};

		rage::atArray<GtaThread*> *m_script_threads{};
		rage::scrProgramTable *m_script_program_table{};
		functions::run_script_threads_t m_run_script_threads{};
		std::int64_t **m_script_globals{};

		CGameScriptHandlerMgr **m_script_handler_mgr{};

		IDXGISwapChain **m_swapchain{};

		PVOID m_model_spawn_bypass;
		PVOID m_send_net_info_to_lobby;

		functions::error_screen* m_error_screen{};
		functions::get_event_data* m_get_event_data{};
		functions::get_label_text* m_get_label_text{};
		functions::get_player_name* m_get_player_name{};
		functions::get_net_player* m_get_net_game_player{};
		functions::increment_stat_event* m_increment_stat_event{};
		functions::read_bitbuf_dword* m_read_bitbuf_dword{};
		functions::received_event* m_received_event{};
		functions::script_event_handler* m_script_event_handler{};
		functions::set_session_weather* m_set_session_weather{};
		functions::send_event_ack* m_send_event_ack{};
		functions::spectate_player* m_spectate_player{};
		functions::sync_local_time* m_sync_local_time{};
		functions::trigger_script_event* m_trigger_script_event{};

		functions::ptr_to_handle* m_ptr_to_handle{};
	};

	inline pointers *g_pointers{};
}
