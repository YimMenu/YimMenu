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
		m_swapchain_hook(*g_pointers->m_swapchain, hooks::swapchain_num_funcs)
	{
		m_swapchain_hook.hook(hooks::swapchain_present_index, &hooks::swapchain_present);
		m_swapchain_hook.hook(hooks::swapchain_resizebuffers_index, &hooks::swapchain_resizebuffers);

		// The only instances in that vector at this point should only be the "lazy" hooks
		// aka the ones that still don't have their m_target assigned
		for (auto& detour_hook_helper : m_detour_hook_helpers)
		{
			detour_hook_helper->m_detour_hook->set_target_and_create_hook(detour_hook_helper->m_on_hooking_available());
		}

		detour_hook_helper::add<hooks::run_script_threads>("SH", g_pointers->m_run_script_threads);

		detour_hook_helper::add<hooks::get_label_text>("GLT", g_pointers->m_get_label_text);

		detour_hook_helper::add<hooks::multiplayer_chat_filter>("MCF", g_pointers->m_multiplayer_chat_filter);
    
        detour_hook_helper::add<hooks::write_player_game_state_data_node>("WPGSDN", g_pointers->m_write_player_game_state_data_node);

		detour_hook_helper::add<hooks::gta_thread_start>("GTS", g_pointers->m_gta_thread_start);
		detour_hook_helper::add<hooks::gta_thread_kill>("GTK", g_pointers->m_gta_thread_kill);
		detour_hook_helper::add<hooks::init_native_tables>("INT", g_pointers->m_init_native_tables);
		detour_hook_helper::add<hooks::script_vm>("SVM", g_pointers->m_script_vm);

		detour_hook_helper::add<hooks::network_player_mgr_init>("NPMI", g_pointers->m_network_player_mgr_init);
		detour_hook_helper::add<hooks::network_player_mgr_shutdown>("NPMS", g_pointers->m_network_player_mgr_shutdown);

		detour_hook_helper::add<hooks::network_group_override>("NGO", g_pointers->m_network_group_override);

		detour_hook_helper::add<hooks::received_event>("RE", g_pointers->m_received_event);

		detour_hook_helper::add<hooks::send_net_info_to_lobby>("SNITL", g_pointers->m_send_net_info_to_lobby);

		detour_hook_helper::add<hooks::assign_physical_index>("API", g_pointers->m_assign_physical_index);

		detour_hook_helper::add<hooks::receive_net_message>("RNM", g_pointers->m_receive_net_message);
		detour_hook_helper::add<hooks::received_clone_sync>("RCS", g_pointers->m_received_clone_sync);

		detour_hook_helper::add<hooks::get_network_event_data>("GNED", g_pointers->m_get_network_event_data);
		detour_hook_helper::add<hooks::write_player_gamer_data_node>("WPGDN", g_pointers->m_write_player_gamer_data_node);

		detour_hook_helper::add<hooks::format_metric_for_sending>("FMFS", g_pointers->m_format_metric_for_sending);

		detour_hook_helper::add<hooks::invalid_mods_crash_detour>("IMCD", g_pointers->m_invalid_mods_crash_detour);

		g_hooking = this;
	}

	hooking::~hooking()
	{
		if (m_enabled)
		{
			disable();
		}

		g_hooking = nullptr;
	}

	void hooking::enable()
	{
		m_swapchain_hook.enable();
		m_og_wndproc = WNDPROC(SetWindowLongPtrW(g_pointers->m_hwnd, GWLP_WNDPROC, LONG_PTR(&hooks::wndproc)));

		for (const auto& detour_hook_helper : m_detour_hook_helpers)
		{
			detour_hook_helper->m_detour_hook->enable();
		}

		MH_ApplyQueued();

		m_enabled = true;
	}

	void hooking::disable()
	{
		m_enabled = false;

		for (const auto& detour_hook_helper : m_detour_hook_helpers)
		{
			detour_hook_helper->m_detour_hook->disable();
		}

		SetWindowLongPtrW(g_pointers->m_hwnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(m_og_wndproc));
		m_swapchain_hook.disable();

		MH_ApplyQueued();

		for (const auto& detour_hook_helper : m_detour_hook_helpers)
		{
			delete detour_hook_helper;
		}
		m_detour_hook_helpers.clear();
	}

	hooking::detour_hook_helper::~detour_hook_helper()
	{
		delete m_detour_hook;
	}

	void hooking::detour_hook_helper::enable_hook_if_hooking_is_already_running()
	{
		if (g_hooking && g_hooking->m_enabled)
		{
			if (m_on_hooking_available)
			{
				m_detour_hook->set_target_and_create_hook(m_on_hooking_available());
			}

			m_detour_hook->enable();
			MH_ApplyQueued();
		}
	}

	bool hooks::run_script_threads(std::uint32_t ops_to_execute)
	{
		g_native_invoker.cache_handlers();

		if (g_running)
		{
			g_script_mgr.tick();
		}

		return g_hooking->get_original<run_script_threads>()(ops_to_execute);
	}
}
