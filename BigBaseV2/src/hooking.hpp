#pragma once
#include "common.hpp"
#include "detour_hook.hpp"
#include "gta/fwddec.hpp"
#include "gta/net_game_event.hpp"
#include "gta/script_thread.hpp"
#include "script_hook.hpp"
#include "vmt_hook.hpp"
#include "MinHook.h"
#include "gta/enums.hpp"
#include "datanodes/player/CPlayerGamerDataNode.hpp"
#include "rage/rlMetric.hpp"

namespace big
{
	struct hooks
	{
		static bool run_script_threads(std::uint32_t ops_to_execute);

		static constexpr auto swapchain_num_funcs = 19;
		static constexpr auto swapchain_present_index = 8;
		static constexpr auto swapchain_resizebuffers_index = 13;
		static HRESULT swapchain_present(IDXGISwapChain *this_, UINT sync_interval, UINT flags);
		static HRESULT swapchain_resizebuffers(IDXGISwapChain *this_, UINT buffer_count, UINT width, UINT height, DXGI_FORMAT new_format, UINT swapchain_flags);

		static LRESULT wndproc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

		static const char* get_label_text(void* unk, const char* label);
		static int multiplayer_chat_filter(__int64 chat_type, const char* input, const char** output);

		static GtaThread* gta_thread_start(unsigned int** a1, unsigned int a2);
		static rage::eThreadState gta_thread_kill(GtaThread* thread);

		static void network_player_mgr_init(CNetworkPlayerMgr* _this, std::uint64_t a2, std::uint32_t a3, std::uint32_t a4[4]);
		static void network_player_mgr_shutdown(CNetworkPlayerMgr* _this);

		static void network_group_override(std::int64_t a1, std::int64_t a2, std::int64_t a3);

		static void received_event(
			rage::netEventMgr* event_manager,
			CNetGamePlayer* source_player,
			CNetGamePlayer* target_player,
			uint16_t event_id,
			int event_index,
			int event_handled_bitset,
			int unk,
			rage::datBitBuffer* bit_buffer
		);

		// these two aren't actually hooks, just helper functions for hooks
		static bool increment_stat_event(CNetworkIncrementStatEvent* net_event_struct, CNetGamePlayer* sender);
		static bool scripted_game_event(CScriptedGameEvent* scripted_game_event, CNetGamePlayer* player);

		static bool send_net_info_to_lobby(rage::rlGamerInfo *player, int64_t a2, int64_t a3, DWORD* a4);
		static bool receive_net_message(void* netConnectionManager, void* a2, rage::netConnection::InFrame* frame);
		static void get_network_event_data(int64_t unk, rage::CEventNetwork* net_event);

		static void* assign_physical_index(CNetworkPlayerMgr* netPlayerMgr, CNetGamePlayer* player, uint8_t new_index);

		static void format_metric_for_sending(int a1, int64_t a2, int64_t a3, rage::rlMetric* metric);

		//SYNC
		static int64_t received_clone_sync(CNetworkObjectMgr* mgr, CNetGamePlayer* src, CNetGamePlayer* dst, eObjType sync_type, uint16_t obj_id, rage::datBitBuffer* bufer, uint16_t unk, uint32_t timestamp);

		static void write_player_gamer_data_node(rage::netObject* player, CPlayerGamerDataNode* node);
	};

	class minhook_keepalive
	{
	public:
		minhook_keepalive()
		{
			MH_Initialize();
		}
		~minhook_keepalive()
		{
			MH_Uninitialize();
		}
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

		WNDPROC m_og_wndproc = nullptr;

		detour_hook m_run_script_threads_hook;

		detour_hook m_get_label_text;
		detour_hook m_multiplayer_chat_filter;

		detour_hook m_gta_thread_start_hook;
		detour_hook m_gta_thread_kill_hook;

		detour_hook m_network_player_mgr_init_hook;
		detour_hook m_network_player_mgr_shutdown_hook;

		detour_hook m_network_group_override;

		detour_hook m_assign_physical_index_hook;

		detour_hook m_received_event_hook;
		detour_hook m_received_clone_sync_hook;

		detour_hook m_send_net_info_to_lobby;
		detour_hook m_receive_net_message_hook;
		detour_hook m_get_network_event_data_hook;

		detour_hook m_format_metric_for_sending;

		detour_hook m_write_player_gamer_data_node_hook;

	};

	inline hooking *g_hooking{};
}
