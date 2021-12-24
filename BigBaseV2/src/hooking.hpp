#pragma once
#include "common.hpp"
#include "detour_hook.hpp"
#include "gta/fwddec.hpp"
#include "gta/net_game_event.hpp"
#include "gta/script_thread.hpp"
#include "script_hook.hpp"
#include "vmt_hook.hpp"

namespace big
{
	struct hooks
	{
		static bool run_script_threads(std::uint32_t ops_to_execute);
		static void *convert_thread_to_fiber(void *param);

		static constexpr auto swapchain_num_funcs = 19;
		static constexpr auto swapchain_present_index = 8;
		static constexpr auto swapchain_resizebuffers_index = 13;
		static HRESULT swapchain_present(IDXGISwapChain *this_, UINT sync_interval, UINT flags);
		static HRESULT swapchain_resizebuffers(IDXGISwapChain *this_, UINT buffer_count, UINT width, UINT height, DXGI_FORMAT new_format, UINT swapchain_flags);

		static LRESULT wndproc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
		static BOOL set_cursor_pos(int x, int y);

		static void set_warning_message_with_header(
			const char* entryHeader,
			const char* entryLine1,
			int instructionalKey,
			const char* entryLine2,
			bool p4,
			Any p5,
			Any* showBackground,
			Any* p7,
			bool p8,
			Any p9
		);

		static rage::eThreadState gta_thread_tick(GtaThread* a1, unsigned int a2);
		static rage::eThreadState gta_thread_kill(GtaThread* thread);

		static bool increment_stat_event(CNetworkIncrementStatEvent* net_event_struct, CNetGamePlayer* sender, int64_t a3);
		static bool is_dlc_present(Hash dlc_hash);

		static bool received_event(
			rage::netEventMgr* event_manager,
			CNetGamePlayer* source_player,
			CNetGamePlayer* target_player,
			uint16_t event_id,
			int event_index,
			int event_handled_bitset,
			int64_t bit_buffer_size,
			int64_t bit_buffer
		);

		static bool scripted_game_event(CScriptedGameEvent* scripted_game_event, CNetGamePlayer* player);
		static bool send_net_info_to_lobby(netPlayerData* player, int64_t a2, int64_t a3, DWORD* a4);
	};

	struct minhook_keepalive
	{
		minhook_keepalive();
		~minhook_keepalive();
	};

	class hooking
	{
		friend hooks;
	public:
		explicit hooking();
		~hooking();

		void enable();
		void disable();

		std::list<script_hook*> m_native_hooks;
		std::unordered_map<rage::scrNativeHash, rage::scrNativeHandler> m_natives;
	private:
		bool m_enabled{};
		minhook_keepalive m_minhook_keepalive;

		vmt_hook m_swapchain_hook;
		WNDPROC m_og_wndproc;
		detour_hook m_set_cursor_pos_hook;

		detour_hook m_run_script_threads_hook;
		detour_hook m_convert_thread_to_fiber_hook;

		detour_hook m_error_screen_hook;

		detour_hook m_gta_thread_tick_hook;
		detour_hook m_gta_thread_kill_hook;

		detour_hook m_increment_stat_hook;
		detour_hook m_is_dlc_present_hook;

		detour_hook m_received_event_hook;

		detour_hook m_scripted_game_event_hook;
		detour_hook m_send_net_info_to_lobby;
	};

	inline hooking *g_hooking{};
}
