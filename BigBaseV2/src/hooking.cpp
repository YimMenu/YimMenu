#include "common.hpp"
#include "function_types.hpp"
#include "logger.hpp"
#include "gta/array.hpp"
#include "gta/player.hpp"
#include "gta/script_thread.hpp"
#include "gui.hpp"
#include "hooking.hpp"
#include "memory/module.hpp"
#include "natives.hpp"
#include "pointers.hpp"
#include "renderer.hpp"
#include "script_mgr.hpp"

#include <MinHook.h>

namespace big
{
	hooking::hooking() :
		// Swapchain
		m_swapchain_hook(*g_pointers->m_swapchain, hooks::swapchain_num_funcs),

		// Script Hook
		m_run_script_threads_hook("SH", g_pointers->m_run_script_threads, &hooks::run_script_threads),

		// Get Label Text
		m_get_label_text("GLT", g_pointers->m_get_label_text, &hooks::get_label_text),

		// GTA Thead Start
		m_gta_thread_start_hook("GTS", g_pointers->m_gta_thread_start, &hooks::gta_thread_start),
		// GTA Thread Kill
		m_gta_thread_kill_hook("GTK", g_pointers->m_gta_thread_kill, &hooks::gta_thread_kill),

		// Network Player Mgr Init
		m_network_player_mgr_init_hook("NPMI", g_pointers->m_network_player_mgr_init, &hooks::network_player_mgr_init),
		// Network Player Mgr Shutdown
		m_network_player_mgr_shutdown_hook("NPMS", g_pointers->m_network_player_mgr_shutdown, &hooks::network_player_mgr_shutdown),

		// Network Group Override
		m_network_group_override("NGO", g_pointers->m_network_group_override, &hooks::network_group_override),
		
		// Is DLC Present
		m_is_dlc_present_hook("IDP", g_pointers->m_is_dlc_present, &hooks::is_dlc_present),

		// Received Event
		m_received_event_hook("RE", g_pointers->m_received_event, &hooks::received_event),

		// Send NET Info to Lobby
		m_send_net_info_to_lobby("SNITL", g_pointers->m_send_net_info_to_lobby, &hooks::send_net_info_to_lobby),

		// Assign Physical Index
		m_assign_physical_index_hook("API", g_pointers->m_assign_physical_index, &hooks::assign_physical_index),
		// Receive Net Message
		m_receive_net_message_hook("RNM", g_pointers->m_receive_net_message, &hooks::receive_net_message),
		// Received clone sync
		m_received_clone_sync_hook("RCS", g_pointers->m_received_clone_sync, &hooks::received_clone_sync),
		//Get Network Event Data
		m_get_network_event_data_hook("GNED", g_pointers->m_get_network_event_data, &hooks::get_network_event_data)
	{
		m_swapchain_hook.hook(hooks::swapchain_present_index, &hooks::swapchain_present);
		m_swapchain_hook.hook(hooks::swapchain_resizebuffers_index, &hooks::swapchain_resizebuffers);

		g_hooking = this;
	}

	hooking::~hooking()
	{
		if (m_enabled)
			disable();

		g_hooking = nullptr;
	}

	void hooking::enable()
	{
		m_swapchain_hook.enable();
		m_og_wndproc = WNDPROC(SetWindowLongPtrW(g_pointers->m_hwnd, GWLP_WNDPROC, LONG_PTR(&hooks::wndproc)));

		m_run_script_threads_hook.enable();
		m_get_label_text.enable();
		m_gta_thread_start_hook.enable();
		m_gta_thread_kill_hook.enable();
		m_network_group_override.enable();
		m_network_player_mgr_init_hook.enable();
		m_network_player_mgr_shutdown_hook.enable();
		m_assign_physical_index_hook.enable();
		m_received_event_hook.enable();
		m_is_dlc_present_hook.enable();
		m_send_net_info_to_lobby.enable();
		m_receive_net_message_hook.enable();
		m_get_network_event_data_hook.enable();
		m_received_clone_sync_hook.enable();

		MH_ApplyQueued();

		m_enabled = true;
	}

	void hooking::disable()
	{
		m_enabled = false;

		m_received_clone_sync_hook.disable();
		m_get_network_event_data_hook.disable();
		m_receive_net_message_hook.disable();
		m_send_net_info_to_lobby.disable();
		m_received_event_hook.disable();
		m_is_dlc_present_hook.disable();
		m_assign_physical_index_hook.disable();
		m_network_player_mgr_init_hook.disable();
		m_network_player_mgr_shutdown_hook.disable();
		m_network_group_override.disable();
		m_gta_thread_kill_hook.disable();
		m_gta_thread_start_hook.disable();
		m_get_label_text.disable();
		m_run_script_threads_hook.disable();

		MH_ApplyQueued();

		SetWindowLongPtrW(g_pointers->m_hwnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(m_og_wndproc));
		m_swapchain_hook.disable();
	}

	bool hooks::run_script_threads(std::uint32_t ops_to_execute)
	{
		TRY_CLAUSE
		{
			if (g_running)
				g_script_mgr.tick();
			return g_hooking->m_run_script_threads_hook.get_original<functions::run_script_threads>()(ops_to_execute);
		} EXCEPT_CLAUSE
		return false;
	}
}
