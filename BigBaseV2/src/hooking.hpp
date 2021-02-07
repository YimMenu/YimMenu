#pragma once
#include "common.hpp"
#include "detour_hook.hpp"
//#include "gta/fwddec.hpp"
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

		// New Hook Definitions
		static bool get_event_data(int32_t eventGroup, int32_t eventIndex, int64_t* args, uint32_t argCount);
		static const char* get_label_text(void* unk, const char* label);
		static void error_screen(char* entryHeader, char* entryLine1, int instructionalKey, char* entryLine2, BOOL p4, Any p5, Any* p6, Any* p7, BOOL background);
		static bool increment_stat_event(uint64_t net_event_struct, CNetGamePlayer* sender, int64_t a3);
		static bool script_event_handler(std::int64_t NetEventStruct, CNetGamePlayer* net_game_player);
		static bool send_net_info_to_lobby(rage::netPlayerData* local_player, int64_t a2, int64_t a3, DWORD* a4);
		static bool received_event(rage::netEventMgr* event_manager, CNetGamePlayer* source_player, CNetGamePlayer* target_player, uint16_t event_id, int event_index, int event_handled_bitset, rage::datBitBuffer* buffer);
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

	private:
		bool m_enabled{};
		minhook_keepalive m_minhook_keepalive;

		vmt_hook m_swapchain_hook;
		WNDPROC m_og_wndproc;
		detour_hook m_set_cursor_pos_hook;

		detour_hook m_run_script_threads_hook;
		detour_hook m_convert_thread_to_fiber_hook;

		// New Detour Hook Definitions
		detour_hook m_get_event_data_hook;
		detour_hook m_get_label_text_hook;
		detour_hook m_error_screen_hook;
		detour_hook m_increment_stat_hook;
		detour_hook m_received_event_hook;
		detour_hook m_script_event_hook;
		detour_hook m_send_net_info_to_lobby_hook;
	};

	inline hooking *g_hooking{};
}
