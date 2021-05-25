#pragma once
#include "common.hpp"
#include "gta/fwddec.hpp"
#include "gta/enums.hpp"
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
		PVOID m_native_return;

		static const int event_count = 87;
		std::vector<PVOID> m_event_ptr;
		unsigned char m_event_restore[event_count];
		char* m_event_register;

		functions::error_screen* m_error_screen{};

		functions::gta_thread_tick* m_gta_thread_tick{};
		functions::gta_thread_kill* m_gta_thread_kill{};

		functions::trigger_script_event* m_trigger_script_event{};

		// Received Event Signatures START
		functions::read_bitbuf_array* m_read_bitbuf_array{};
		functions::read_bitbuf_dword* m_read_bitbuf_dword{};
		functions::received_event* m_received_event{};
		functions::send_event_ack* m_send_event_ack{};
		// Received Event Signatures END
	};

	inline pointers *g_pointers{};
}
