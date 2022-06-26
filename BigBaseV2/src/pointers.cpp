#include "common.hpp"
#include "pointers.hpp"
#include "memory/all.hpp"

namespace big
{
	pointers::pointers()
	{
		memory::pattern_batch main_batch;

		main_batch.add("SCREEN_RESOLUTION", "66 0F 6E 0D ? ? ? ? 0F B7 3D", [this](memory::handle ptr)
		{
			m_resolution_x = ptr.sub(4).rip().as<int*>();
			m_resolution_y = ptr.add(4).rip().as<int*>();
		});

		// Game State
		main_batch.add("GS", "83 3D ? ? ? ? ? 75 17 8B 43 20 25", [this](memory::handle ptr)
		{
			m_game_state = ptr.add(2).rip().as<eGameState*>();
		});

		// Is session active
		main_batch.add("ISA", "40 38 35 ? ? ? ? 75 0E 4C 8B C3 49 8B D7 49 8B CE", [this](memory::handle ptr)
		{
			m_is_session_started = ptr.add(3).rip().as<bool*>();
		});

		// Ped Factory
		main_batch.add("PF", "48 8B 05 ? ? ? ? 48 8B 48 08 48 85 C9 74 52 8B 81", [this](memory::handle ptr)
		{
			m_ped_factory = ptr.add(3).rip().as<CPedFactory**>();
		});

		// Network Player Manager
		main_batch.add("NPM", "48 8B 0D ? ? ? ? 8A D3 48 8B 01 FF 50 ? 4C 8B 07 48 8B CF", [this](memory::handle ptr)
		{
			m_network_player_mgr = ptr.add(3).rip().as<CNetworkPlayerMgr**>();
		});

		// Native Handlers
		main_batch.add("NH", "48 8D 0D ? ? ? ? 48 8B 14 FA E8 ? ? ? ? 48 85 C0 75 0A", [this](memory::handle ptr)
		{
			m_native_registration_table = ptr.add(3).rip().as<rage::scrNativeRegistrationTable*>();
			m_get_native_handler = ptr.add(12).rip().as<functions::get_native_handler_t>();
		});

		// Fix Vectors
		main_batch.add("FV", "83 79 18 00 48 8B D1 74 4A FF 4A 18 48 63 4A 18 48 8D 41 04 48 8B 4C CA", [this](memory::handle ptr)
		{
			m_fix_vectors = ptr.as<functions::fix_vectors_t>();
		});

		// Script Threads
		main_batch.add("ST", "45 33 F6 8B E9 85 C9 B8", [this](memory::handle ptr)
		{
			m_script_threads = ptr.sub(4).rip().sub(8).as<decltype(m_script_threads)>();
			m_run_script_threads = ptr.sub(0x1F).as<functions::run_script_threads_t>();
		});

		// Script Programs
		main_batch.add("SP", "48 8B 1D ? ? ? ? 41 83 F8 FF", [this](memory::handle ptr)
		{
			m_script_program_table = ptr.add(3).rip().as<decltype(m_script_program_table)>();
		});

		// Script Global
		main_batch.add("SG", "48 8D 15 ? ? ? ? 4C 8B C0 E8 ? ? ? ? 48 85 FF 48 89 1D", [this](memory::handle ptr)
		{
			m_script_globals = ptr.add(3).rip().as<std::int64_t**>();
		});

		// Game Script Handle Manager
		main_batch.add("CGSHM", "48 8B 0D ? ? ? ? 4C 8B CE E8 ? ? ? ? 48 85 C0 74 05 40 32 FF", [this](memory::handle ptr)
		{
			m_script_handler_mgr = ptr.add(3).rip().as<CGameScriptHandlerMgr**>();
		});

		// Swapchain
		main_batch.add("S", "48 8B 0D ? ? ? ? 48 8B 01 44 8D 43 01 33 D2 FF 50 40 8B C8", [this](memory::handle ptr)
		{
			m_swapchain = ptr.add(3).rip().as<IDXGISwapChain**>();
		});

		// Model Spawn Bypass
		main_batch.add("MSB", "48 8B C8 FF 52 30 84 C0 74 05 48", [this](memory::handle ptr)
		{
			m_model_spawn_bypass = ptr.add(8).as<PVOID>();
		});

		// new pointers
		// Native Return Spoofer
		main_batch.add("NRF", "FF E3", [this](memory::handle ptr)
		{
			m_native_return = ptr.add(0).as<PVOID>();
		});

		// GTA Thread Start
		main_batch.add("GTS", "48 89 5C 24 ? 48 89 74 24 ? 57 48 83 EC 20 8B FA 85 D2 75 2A 8B 15", [this](memory::handle ptr)
		{
			m_gta_thread_start = ptr.as<PVOID>();
		});

		// GTA Thread Kill
		main_batch.add("TK", "48 89 5C 24 ? 57 48 83 EC 20 48 83 B9 ? ? ? ? ? 48 8B D9 74 14", [this](memory::handle ptr)
		{
			m_gta_thread_kill = ptr.as<PVOID>();
		});

		// Increment Stat Event
		main_batch.add("ISE", "48 83 EC 60 8B 79 30 4C 8B F1", [this](memory::handle ptr)
		{
			m_increment_stat_event = ptr.sub(0x15).as<decltype(m_increment_stat_event)>();
		});

		// Trigger Script Event
		main_batch.add("TSE", "45 8B F0 41 8B F9 48 8B EA", [this](memory::handle ptr)
		{
			m_trigger_script_event = ptr.sub(0x1C).as<decltype(m_trigger_script_event)>();
		});

		// Received Event Signatures START
		// Received Event Hook
		main_batch.add("REH", "66 41 83 F9 ? 0F 83", [this](memory::handle ptr)
		{
			m_received_event = ptr.as<decltype(m_received_event)>();
		});

		// Read Bitbugger WORD/DWORD
		main_batch.add("RBWD", "48 89 74 24 ? 57 48 83 EC 20 48 8B D9 33 C9 41 8B F0 8A", [this](memory::handle ptr)
		{
			m_read_bitbuf_dword = ptr.sub(5).as<decltype(m_read_bitbuf_dword)>();
		});

		// Read Bitbuffer Array
		main_batch.add("RBA", "48 89 5C 24 ? 57 48 83 EC 30 41 8B F8 4C", [this](memory::handle ptr)
		{
			m_read_bitbuf_array = ptr.as<decltype(m_read_bitbuf_array)>();
		});

		// Send Event Acknowledge
		main_batch.add("SEA", "48 89 6C 24 ? 48 89 74 24 ? 57 48 83 EC 20 80 7A", [this](memory::handle ptr)
		{
			m_send_event_ack = ptr.sub(5).as<decltype(m_send_event_ack)>();
		});
		// Received Event Signatures END

		// Request Control of Entity PATCH
		main_batch.add("RCOE-Patch", "48 89 5C 24 ? 57 48 83 EC 20 8B D9 E8 ? ? ? ? ? ? ? ? 8B CB", [this](memory::handle ptr)
		{
			m_spectator_check = ptr.add(0x13).as<PUSHORT>();
			*m_spectator_check = 0x9090;
		});

		// Replay Interface
		main_batch.add("RI", "0F B7 44 24 ? 66 89 44 4E", [this](memory::handle ptr)
		{
			m_replay_interface = ptr.add(0x1F).rip().as<decltype(m_replay_interface)>();
		});

		// Pointer to Handle
		main_batch.add("PTH", "48 8B F9 48 83 C1 10 33 DB", [this](memory::handle ptr)
		{
			m_ptr_to_handle = ptr.sub(0x15).as<decltype(m_ptr_to_handle)>();
		});

		// Blame Explode
		main_batch.add("BE", "0F 85 ? ? ? ? 48 8B 05 ? ? ? ? 48 8B 48 08 E8", [this](memory::handle ptr)
		{
			m_blame_explode = ptr.as<decltype(m_blame_explode)>();
		});

		// Is DLC Present
		main_batch.add("IDP", "48 89 5C 24 ? 57 48 83 EC ? 81 F9", [this](memory::handle ptr)
		{
			m_is_dlc_present = ptr.as<decltype(m_is_dlc_present)>();
		});

		// Send NET Info to Lobby
		main_batch.add("SNITL", "33 DB 48 83 C1 68 45 8B F0 ", [this](memory::handle ptr)
		{
			m_send_net_info_to_lobby = ptr.sub(0x26).as<decltype(m_send_net_info_to_lobby)>();
		});

		// CNetworkObjectMgr
		main_batch.add("CNOM", "48 8B 0D ? ? ? ? 45 33 C0 E8 ? ? ? ? 33 FF 4C 8B F0", [this](memory::handle ptr)
		{
			m_network_object_mgr = ptr.add(3).rip().as<CNetworkObjectMgr**>();
		});

		// Player Has Joined
		main_batch.add("PHJ", "48 8B CA 48 8B F2 FF 50 18 4C 8D 05", [this](memory::handle ptr)
		{
			m_player_has_joined = ptr.sub(0x26).as<PVOID>();
		});

		// Player Has Left
		main_batch.add("PHL", "4C 8B F1 48 8B CA 48 8B EA FF 50 18 4C 8D 05", [this](memory::handle ptr)
		{
			m_player_has_left = ptr.sub(0x26).as<PVOID>();
		});

		// Network Player Mgr Init
		main_batch.add("NPMI", "41 56 48 83 EC ? 48 8B F1 B9 ? ? ? ? 49 8B F9 41 8B E8 4C 8B F2 E8", [this](memory::handle ptr)
		{
			m_network_player_mgr_init = ptr.sub(0x13).as<decltype(m_network_player_mgr_init)>();
		});

		// Network Player Mgr Shutdown
		main_batch.add("NPMS", "48 8D 9F ? ? ? ? EB ? 48 8B 13 48 85 D2 74 ? 48 8B CB E8 ? ? ? ? 48 83 7B ? ? 75 ? 48 8D 9F", [this](memory::handle ptr)
		{
			m_network_player_mgr_shutdown = ptr.sub(0x1A).as<decltype(m_network_player_mgr_shutdown)>();
		});

		// FriendRegistry
		main_batch.add("FR", "3B 0D ? ? ? ? 73 13 48 63 C9", [this](memory::handle ptr)
		{
			m_friend_registry = ptr.add(2).rip().as<FriendRegistry*>();
		});

		// GET_SCREEN_COORDS_FROM_WORLD_COORDS
		main_batch.add("GSCFWC", "E8 ? ? ? ? 84 C0 74 19 F3 0F 10 44 24", [this](memory::handle ptr)
		{
			m_get_screen_coords_for_world_coords = ptr.add(1).rip().as<functions::get_screen_coords_for_world_coords*>();
		});

		// Get Gameplay Cam Coords
		main_batch.add("GGCC", "8B 90 ? ? ? ? 89 13", [this](memory::handle ptr)
		{
			m_get_gamplay_cam_coords = ptr.sub(0xE).as<functions::get_gameplay_cam_coords*>();
		});

		// net array handler - version mismatch patch
		main_batch.add("NAH", "44 8B E0 89 45 F4 48 8B 03 48 8B CB FF 90", [this](memory::handle ptr)
		{
			m_net_array_handler = ptr.sub(0x3C).as<PVOID>();
		});

		// Network Group Override
		main_batch.add("NGO", "44 89 81 ? ? ? ? 89 91 ? ? ? ? C6 05", [this](memory::handle ptr)
		{
			m_network_group_override = ptr.as<PVOID>();
		});

		//Receive Net Message
		main_batch.add("RNM", "48 83 EC 20 4C 8B 71 50 33 ED", [this](memory::handle ptr)
		{
			m_receive_net_message = ptr.sub(0x19).as<PVOID>();
		});

		//Get Network Event Data
		main_batch.add("GNED", "E9 ? ? ? ? E9 ? ? ? ? E9 ? ? ? ? E9 ? ? ? ? E9 ? ? ? ? CC FF 50 28", [this](memory::handle ptr)
		{
			m_get_network_event_data = ptr.as<PVOID>();
		});

		//Received clone sync & Get sync tree for type & Get net object for player & Get sync type info & Get net object
		main_batch.add("RCS/GSTFT/GNOFP/GNO/GSTI", "4C 8B F2 41 0F B7 D1 45 0F B7 E1", [this](memory::handle ptr)
		{
			m_received_clone_sync = ptr.sub(0x1D).as<decltype(m_received_clone_sync)>();
			m_get_sync_tree_for_type = ptr.add(0x14).rip().as<decltype(m_get_sync_tree_for_type)>(); // 0F B7 CA 83 F9 07 .as()
			m_get_net_object_for_player = ptr.add(0x4C).rip().as<decltype(m_get_net_object_for_player)>(); // 41 80 78 ? FF 74 2D 41 0F B6 40 .as()
			m_get_net_object = ptr.add(0x62).rip().as<decltype(m_get_net_object)>(); // E8 ? ? ? ? 0F B7 53 7C .add(1).rip().as()
			m_get_sync_type_info = ptr.add(0x78).rip().as<decltype(m_get_sync_type_info)>(); // 44 0F B7 C1 4C 8D 0D .as()
		});

		auto mem_region = memory::module(nullptr);
		main_batch.run(mem_region);

		/**
		 * Freemode thread restorer through VM patch
		 */
		if (auto pat1 = mem_region.scan("3b 0a 0f 83 ? ? ? ? 48 ff c7"))
		{
			*pat1.add(2).as<uint32_t*>() = 0xc9310272;
			*pat1.add(6).as<uint16_t*>() = 0x9090;
		}

		if (auto pat2 = mem_region.scan("3b 0a 0f 83 ? ? ? ? 49 03 fa"))
		{
			*pat2.add(2).as<uint32_t*>() = 0xc9310272;
			*pat2.add(6).as<uint16_t*>() = 0x9090;
		}

		auto pat3 = mem_region.scan_all("3b 11 0f 83 ? ? ? ? 48 ff c7");
		for (auto& handle : pat3)
		{
			*handle.add(2).as<uint32_t*>() = 0xd2310272;
			*handle.add(6).as<uint16_t*>() = 0x9090;
		}

		auto pat4 = mem_region.scan_all("3b 11 0f 83 ? ? ? ? 49 03 fa");
		for (auto& handle : pat4)
		{
			*handle.add(2).as<uint32_t*>() = 0xd2310272;
			*handle.add(6).as<uint16_t*>() = 0x9090;
		}

		m_hwnd = FindWindowW(L"grcWindow", nullptr);
		if (!m_hwnd)
			throw std::runtime_error("Failed to find the game's window.");

		g_pointers = this;
	}

	pointers::~pointers()
	{
		*m_spectator_check = 0x6A75;

		g_pointers = nullptr;
	}
}
