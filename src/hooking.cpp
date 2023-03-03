#include "hooking.hpp"

#include "common.hpp"
#include "function_types.hpp"
#include "gta/script_thread.hpp"
#include "gui.hpp"
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

		detour_hook_helper::add<hooks::check_chat_profanity>("CCP", g_pointers->m_check_chat_profanity);

		detour_hook_helper::add<hooks::write_player_game_state_data_node>("WPGSDN", g_pointers->m_write_player_game_state_data_node);

		detour_hook_helper::add<hooks::gta_thread_start>("GTS", g_pointers->m_gta_thread_start);
		detour_hook_helper::add<hooks::gta_thread_kill>("GTK", g_pointers->m_gta_thread_kill);
		detour_hook_helper::add<hooks::init_native_tables>("INT", g_pointers->m_init_native_tables);
		detour_hook_helper::add<hooks::script_vm>("SVM", g_pointers->m_script_vm);

		detour_hook_helper::add<hooks::network_player_mgr_init>("NPMI", g_pointers->m_network_player_mgr_init);
		detour_hook_helper::add<hooks::network_player_mgr_shutdown>("NPMS", g_pointers->m_network_player_mgr_shutdown);

		detour_hook_helper::add<hooks::received_event>("RE", g_pointers->m_received_event);

		detour_hook_helper::add<hooks::assign_physical_index>("API", g_pointers->m_assign_physical_index);

		detour_hook_helper::add<hooks::receive_net_message>("RNM", g_pointers->m_receive_net_message);

		detour_hook_helper::add<hooks::received_clone_create>("RCC", g_pointers->m_received_clone_create);
		detour_hook_helper::add<hooks::received_clone_sync>("RCS", g_pointers->m_received_clone_sync);
		detour_hook_helper::add<hooks::can_apply_data>("CAD", g_pointers->m_can_apply_data);

		detour_hook_helper::add<hooks::get_network_event_data>("GNED", g_pointers->m_get_network_event_data);
		detour_hook_helper::add<hooks::write_player_gamer_data_node>("WPGDN", g_pointers->m_write_player_gamer_data_node);

		detour_hook_helper::add<hooks::invalid_mods_crash_detour>("IMCD", g_pointers->m_invalid_mods_crash_detour);
		detour_hook_helper::add<hooks::constraint_attachment_crash>("CAC", g_pointers->m_constraint_attachment_crash);
		detour_hook_helper::add<hooks::invalid_decal>("IDC", g_pointers->m_invalid_decal_crash);
		detour_hook_helper::add<hooks::task_parachute_object_0x270>("TPO270", g_pointers->m_task_parachute_object_0x270);

		detour_hook_helper::add<hooks::update_presence_attribute_int>("UPAI", g_pointers->m_update_presence_attribute_int);
		detour_hook_helper::add<hooks::update_presence_attribute_string>("UPAS", g_pointers->m_update_presence_attribute_string);

		detour_hook_helper::add<hooks::serialize_ped_inventory_data_node>("SPIDN", g_pointers->m_serialize_ped_inventory_data_node);
		detour_hook_helper::add<hooks::serialize_vehicle_gadget_data_node>("SVGDN", g_pointers->m_serialize_vehicle_gadget_data_node);

		detour_hook_helper::add<hooks::handle_join_request>("HJR", g_pointers->m_handle_join_request);

		detour_hook_helper::add<hooks::sort_session_details>("SSD", g_pointers->m_sort_session_details);

		detour_hook_helper::add<hooks::add_player_to_session>("APTS", g_pointers->m_add_player_to_session);
		detour_hook_helper::add<hooks::send_chat_message>("SCM", g_pointers->m_send_chat_message);
		detour_hook_helper::add<hooks::send_chat_net_message>("SCNM", g_pointers->m_send_chat_net_message);

		detour_hook_helper::add<hooks::process_matchmaking_find_response>("PMFR", g_pointers->m_process_matchmaking_find_response);
		detour_hook_helper::add<hooks::serialize_player_data_msg>("SJPD", g_pointers->m_serialize_player_data_msg);

		detour_hook_helper::add<hooks::serialize_join_request_message>("SJRM", g_pointers->m_serialize_join_request_message);

		detour_hook_helper::add<hooks::start_matchmaking_find_sessions>("SMFS", g_pointers->m_start_matchmaking_find_sessions);

		detour_hook_helper::add<hooks::broadcast_net_array>("BNA", g_pointers->m_broadcast_net_array);

		detour_hook_helper::add<hooks::send_session_matchmaking_attributes>("SSMA", g_pointers->m_send_session_matchmaking_attributes);

		detour_hook_helper::add<hooks::serialize_take_off_ped_variation_task>("STOPVT", g_pointers->m_serialize_take_off_ped_variation_task);

		detour_hook_helper::add<hooks::create_script_handler>("CSH", g_pointers->m_create_script_handler);

		detour_hook_helper::add<hooks::queue_dependency>("QD", g_pointers->m_queue_dependency);
		detour_hook_helper::add<hooks::prepare_metric_for_sending>("PMFS", g_pointers->m_prepare_metric_for_sending);

		detour_hook_helper::add<hooks::fragment_physics_crash>("FPC", g_pointers->m_fragment_physics_crash);
		detour_hook_helper::add<hooks::fragment_physics_crash_2>("FPC2", g_pointers->m_fragment_physics_crash_2);

		detour_hook_helper::add<hooks::infinite_train_crash>("ITC", g_pointers->m_infinite_train_crash);

		detour_hook_helper::add<hooks::received_array_update>("RAU", g_pointers->m_received_array_update);

		detour_hook_helper::add<hooks::receive_pickup>("RPI", g_pointers->m_receive_pickup);

		detour_hook_helper::add<hooks::write_player_camera_data_node>("WPCDN", g_pointers->m_write_player_camera_data_node);

		detour_hook_helper::add<hooks::send_player_card_stats>("SPCS", g_pointers->m_send_player_card_stats);
		detour_hook_helper::add<hooks::serialize_stats>("SS", g_pointers->m_serialize_stats);

		detour_hook_helper::add<hooks::write_player_creation_data_node>("WPCDN", g_pointers->m_write_player_creation_data_node);
		detour_hook_helper::add<hooks::write_player_appearance_data_node>("WPADN", g_pointers->m_write_player_appearance_data_node);

		detour_hook_helper::add<hooks::get_model_info>("GMI", g_pointers->m_get_model_info);

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

		for (auto& thread : *g_pointers->m_script_threads)
		{
			if (thread->m_handler)
				hook_script_handler((CGameScriptHandler*)thread->m_handler);
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
		m_handler_hooks.clear();
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
