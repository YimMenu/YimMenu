#pragma once
#include "common.hpp"
#include "gta/fwddec.hpp"
#include "gta/enums.hpp"
#include "function_types.hpp"
#include "features/rid_joiner.hpp"

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

		functions::error_screen* m_error_screen{};
		functions::get_event_data* m_get_event_data{};
		functions::get_player_name* m_get_player_name{};
		functions::get_net_player* m_get_net_game_player{};
		functions::increment_stat_event* m_increment_stat_event{};
		functions::script_event_handler* m_script_event_handler{};
		functions::set_session_weather* m_set_session_weather{};
		functions::spectate_player* m_spectate_player{};
		functions::sync_local_time* m_sync_local_time{};
		functions::trigger_script_event* m_trigger_script_event{};

		rs_info *m_rs_info{};
		functions::get_session_info_from_gs* m_get_session_info_from_gs{};
		functions::join_player_via_session_info* m_join_player_via_session_info{};
		functions::read_session_response* m_read_session_response{};
		functions::send_session_info_request* m_send_session_info_request{};
	};

	inline pointers *g_pointers{};
}
