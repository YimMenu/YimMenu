#include "common.hpp"
#include "logger.hpp"
#include "pointers.hpp"
#include "memory/all.hpp"

namespace big
{
	pointers::pointers()
	{
		memory::pattern_batch main_batch;

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
		main_batch.add("SP", "44 8B 0D ? ? ? ? 4C 8B 1D ? ? ? ? 48 8B 1D ? ? ? ? 41 83 F8 FF 74 3F 49 63 C0 42 0F B6 0C 18 81 E1", [this](memory::handle ptr)
		{
			m_script_program_table = ptr.add(17).rip().as<decltype(m_script_program_table)>();
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

		// Event Registry
		main_batch.add("ER", "48 83 EC 28 E8 ? ? ? ? 48 8B 0D ? ? ? ? 4C 8D 0D ? ? ? ? 4C 8D 05 ? ? ? ? BA 03", [this](memory::handle ptr)
		{
			m_event_register = ptr.as<char*>();

			if (m_event_register)
			{
				const char* pattern = "\x4C\x8D\x05";
				for (int i = 0, x = 0, found = 0, matches = 0; found < event_count; i++)
				{
					if (m_event_register[i] == pattern[x])
					{
						if (++matches == 3)
						{
							m_event_ptr.push_back((void*)(reinterpret_cast<uint64_t>(m_event_register + i - x) + *reinterpret_cast<int*>(m_event_register + i + 1) + 7));

							found++;
							x = matches = 0;
						}

						x++;

						continue;
					}

					x = matches = 0;
				}
			}
		});

		// Incompatible Version Fix
		main_batch.add("IVF", "48 89 5C 24 ? 55 56 57 41 54 41 55 41 56 41 57 48 8D AC 24 ? ? ? ? 48 81 EC ? ? ? ? 33 FF 48 8B DA", [this](memory::handle ptr)
		{
			 uint8_t* incompatible_version = ptr.add(0x365).as<uint8_t*>();

			 memset(incompatible_version, 0x90, 0x1E);
		});

		// Thread Thick
		main_batch.add("TT", "48 89 5C 24 ? 48 89 74 24 ? 57 48 83 EC 20 80 B9 ? ? ? ? ? 8B FA 48 8B D9 74 05", [this](memory::handle ptr)
		{
			m_gta_thread_tick = ptr.as<decltype(m_gta_thread_tick)>();
		});

		// Thread Kill
		main_batch.add("TK", "48 89 5C 24 ? 57 48 83 EC 20 48 83 B9 ? ? ? ? ? 48 8B D9 74 14", [this](memory::handle ptr)
		{
			m_gta_thread_kill = ptr.as<decltype(m_gta_thread_kill)>();
		});

		// Increment Stat Event
		main_batch.add("ISE", "48 89 5C 24 ? 48 89 74 24 ? 55 57 41 55 41 56 41 57 48 8B EC 48 83 EC 60 8B 79 30", [this](memory::handle ptr)
		{
			m_increment_stat_event = ptr.as<decltype(m_increment_stat_event)>();
		});

		// Error Screen Hook
		main_batch.add("ESH", "48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 57 41 56 41 57 48 83 EC 60 4C 8B F2 48 8B 94 24 ? ? ? ? 33 DB", [this](memory::handle ptr)
		{
			m_error_screen = ptr.as<decltype(m_error_screen)>();
		});

		// Trigger Script Event
		main_batch.add("TSE", "48 8B C4 48 89 58 08 48 89 68 10 48 89 70 18 48 89 78 20 41 56 48 81 EC ? ? ? ? 45 8B F0 41 8B F9", [this](memory::handle ptr)
		{
			m_trigger_script_event = ptr.as<decltype(m_trigger_script_event)>();
		});

		// Received Event Signatures START
		// Received Event Hook
		main_batch.add("REH", "66 41 83 F9 ? 0F 83 ? ? ? ?", [this](memory::handle ptr)
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
			PVOID spectator_check = ptr.add(0x11).as<PVOID>();

			memset(spectator_check, 0x90, 0x4);
		});

		// Spectate Player
		main_batch.add("SP", "48 89 5C 24 ? 57 48 83 EC 20 41 8A F8 84 C9", [this](memory::handle ptr)
		{
			m_spectate_player = ptr.as<decltype(m_spectate_player)>();
		});
		
		main_batch.run(memory::module(nullptr));

		m_hwnd = FindWindowW(L"grcWindow", nullptr);
		if (!m_hwnd)
			throw std::runtime_error("Failed to find the game's window.");

		g_pointers = this;
	}

	pointers::~pointers()
	{
		g_pointers = nullptr;
	}
}
