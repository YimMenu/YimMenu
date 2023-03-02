#include "pointers.hpp"

#include "common.hpp"
#include "hooking.hpp"
#include "memory/all.hpp"
#include "rage/atSingleton.hpp"
#include "security/RageSecurity.hpp"

extern "C" void sound_overload_detour();
std::uint64_t g_sound_overload_ret_addr;

namespace big
{
	pointers::pointers()
	{
		memory::batch main_batch;

		main_batch.add("SCREEN_RESOLUTION", "66 0F 6E 0D ? ? ? ? 0F B7 3D", [this](memory::handle ptr) {
			m_resolution_x = ptr.sub(4).rip().as<int*>();
			m_resolution_y = ptr.add(4).rip().as<int*>();
		});

		// Region Code
		main_batch.add("RC", "48 83 EC 28 83 3D ? ? ? ? ? 75 10", [this](memory::handle ptr) {
			m_region_code = ptr.add(16).rip().add(1).as<uint32_t*>();
		});

		// Max Wanted Level
		main_batch.add("MWL", "8B 43 6C 89 05", [this](memory::handle ptr) {
			m_max_wanted_level   = memory::byte_patch::make(ptr.add(5).rip().as<uint32_t*>(), 0).get();
			m_max_wanted_level_2 = memory::byte_patch::make(ptr.add(14).rip().as<uint32_t*>(), 0).get();
		});

		// Game State
		main_batch.add("GS", "83 3D ? ? ? ? ? 75 17 8B 43 20 25", [this](memory::handle ptr) {
			m_game_state = ptr.add(2).rip().as<eGameState*>();
		});

		// Is Session Started
		main_batch.add("ISA", "40 38 35 ? ? ? ? 75 0E 4C 8B C3 49 8B D7 49 8B CE", [this](memory::handle ptr) {
			m_is_session_started = ptr.add(3).rip().as<bool*>();
		});

		// Ped Factory
		main_batch.add("PF", "48 8B 05 ? ? ? ? 48 8B 48 08 48 85 C9 74 52 8B 81", [this](memory::handle ptr) {
			m_ped_factory = ptr.add(3).rip().as<CPedFactory**>();
		});

		// Network Player Manager
		main_batch.add("NPM", "48 8B 0D ? ? ? ? 8A D3 48 8B 01 FF 50 ? 4C 8B 07 48 8B CF", [this](memory::handle ptr) {
			m_network_player_mgr = ptr.add(3).rip().as<CNetworkPlayerMgr**>();
		});

		// Init Native Tables & Native Handlers
		main_batch.add("NH", "48 8D 0D ? ? ? ? 48 8B 14 FA E8 ? ? ? ? 48 85 C0 75 0A", [this](memory::handle ptr) {
			m_init_native_tables        = ptr.sub(37).as<PVOID>();
			m_native_registration_table = ptr.add(3).rip().as<rage::scrNativeRegistrationTable*>();
			m_get_native_handler        = ptr.add(12).rip().as<functions::get_native_handler>();
		});

		// Fix Vectors
		main_batch.add("FV", "83 79 18 00 48 8B D1 74 4A FF 4A 18 48 63 4A 18 48 8D 41 04 48 8B 4C CA", [this](memory::handle ptr) {
			m_fix_vectors = ptr.as<functions::fix_vectors>();
		});

		// Script Threads
		main_batch.add("ST", "45 33 F6 8B E9 85 C9 B8", [this](memory::handle ptr) {
			m_script_threads     = ptr.sub(4).rip().sub(8).as<decltype(m_script_threads)>();
			m_run_script_threads = ptr.sub(0x1F).as<functions::run_script_threads>();
		});

		// Script Programs
		main_batch.add("SP", "48 8B 1D ? ? ? ? 41 83 F8 FF", [this](memory::handle ptr) {
			m_script_program_table = ptr.add(3).rip().as<decltype(m_script_program_table)>();
		});

		// Script Global
		main_batch.add("SG", "48 8D 15 ? ? ? ? 4C 8B C0 E8 ? ? ? ? 48 85 FF 48 89 1D", [this](memory::handle ptr) {
			m_script_globals = ptr.add(3).rip().as<std::int64_t**>();
		});

		// Game Script Handle Manager
		main_batch.add("CGSHM", "48 8B 0D ? ? ? ? 4C 8B CE E8 ? ? ? ? 48 85 C0 74 05 40 32 FF", [this](memory::handle ptr) {
			m_script_handler_mgr = ptr.add(3).rip().as<CGameScriptHandlerMgr**>();
		});

		// Swapchain
		main_batch.add("S", "48 8B 0D ? ? ? ? 48 8B 01 44 8D 43 01 33 D2 FF 50 40 8B C8", [this](memory::handle ptr) {
			m_swapchain = ptr.add(3).rip().as<IDXGISwapChain**>();
		});

		// World Model Spawn Bypass
		main_batch.add("WMSB", "48 85 C0 0F 84 ? ? ? ? 8B 48 50", [this](memory::handle ptr) {
			m_world_model_spawn_bypass = ptr.as<PVOID>();
		});

		// Native Return Spoofer
		main_batch.add("NRF", "FF E3", [this](memory::handle ptr) {
			m_native_return = ptr.add(0).as<PVOID>();
		});

		// GTA Thread Start
		main_batch.add("GTS", "48 89 5C 24 ? 48 89 74 24 ? 57 48 83 EC 20 8B FA 85 D2 75 2A 8B 15", [this](memory::handle ptr) {
			m_gta_thread_start = ptr.as<PVOID>();
		});

		// GTA Thread Kill
		main_batch.add("TK", "48 89 5C 24 ? 57 48 83 EC 20 48 83 B9 ? ? ? ? ? 48 8B D9 74 14", [this](memory::handle ptr) {
			m_gta_thread_kill = ptr.as<PVOID>();
		});

		// Trigger Script Event
		main_batch.add("TSE", "45 8B F0 41 8B F9 48 8B EA", [this](memory::handle ptr) {
			m_trigger_script_event = ptr.sub(0x1C).as<decltype(m_trigger_script_event)>();
		});

		// Received Event Signatures START

		// Received Event Hook
		main_batch.add("REH", "66 41 83 F9 ? 0F 83", [this](memory::handle ptr) {
			m_received_event = ptr.as<decltype(m_received_event)>();
		});

		// Send Event Acknowledge
		main_batch.add("SEA", "E8 ? ? ? ? 66 83 7B 08 5B", [this](memory::handle ptr) {
			m_send_event_ack = ptr.add(1).rip().as<decltype(m_send_event_ack)>();
		});

		// Received Event Signatures END

		// Read Bitbuffer WORD/DWORD
		main_batch.add("RBWD", "48 89 74 24 ? 57 48 83 EC 20 48 8B D9 33 C9 41 8B F0 8A", [this](memory::handle ptr) {
			m_read_bitbuf_dword = ptr.sub(5).as<decltype(m_read_bitbuf_dword)>();
		});

		// Read Bitbuffer Array
		main_batch.add("RBA", "48 89 5C 24 ? 57 48 83 EC 30 41 8B F8 4C", [this](memory::handle ptr) {
			m_read_bitbuf_array = ptr.as<decltype(m_read_bitbuf_array)>();
		});

		// Read Bitbuffer String
		main_batch.add("RBS", "E8 ? ? ? ? 48 8D 4F 3C", [this](memory::handle ptr) {
			m_read_bitbuf_string = ptr.add(1).rip().as<decltype(m_read_bitbuf_string)>();
		});

		// Read Bitbuffer Boolean
		main_batch.add("RBB", "E8 ? ? ? ? 84 C0 74 41 48 8D 56 2C", [this](memory::handle ptr) {
			m_read_bitbuf_bool = ptr.add(1).rip().as<decltype(m_read_bitbuf_bool)>();
		});

		// Write Bitbuffer WORD/DWORD
		main_batch.add("WBD", "48 8B C4 48 89 58 08 48 89 68 10 48 89 70 18 48 89 78 20 41 56 48 83 EC 20 8B EA BF 01", [this](memory::handle ptr) {
			m_write_bitbuf_dword = ptr.as<decltype(m_write_bitbuf_dword)>();
		});

		// Write Bitbuffer QWORD
		main_batch.add("WBQ", "48 89 5C 24 08 48 89 6C 24 10 48 89 74 24 18 57 48 83 EC 20 41 8B F0 48 8B EA 48 8B D9 41 83 F8 20", [this](memory::handle ptr) {
			m_write_bitbuf_qword = ptr.as<decltype(m_write_bitbuf_qword)>();
		});

		// Write Bitbuffer Int64
		main_batch.add("WBI64", "E8 ? ? ? ? 8A 53 39 48 8B CF", [this](memory::handle ptr) {
			m_write_bitbuf_int64 = ptr.add(1).rip().as<decltype(m_write_bitbuf_int64)>();
		});

		// Write Bitbuffer Int32
		main_batch.add("WBI32", "E8 ? ? ? ? 8A 53 74", [this](memory::handle ptr) {
			m_write_bitbuf_int32 = ptr.add(1).rip().as<decltype(m_write_bitbuf_int32)>();
		});

		// Write Bitbuffer Boolean
		main_batch.add("WBB", "E8 ? ? ? ? 8A 57 39", [this](memory::handle ptr) {
			m_write_bitbuf_bool = ptr.add(1).rip().as<decltype(m_write_bitbuf_bool)>();
		});

		// Write Bitbuffer Array
		main_batch.add("WBA", "E8 ? ? ? ? 01 7E 08", [this](memory::handle ptr) {
			m_write_bitbuf_array = ptr.add(1).rip().as<decltype(m_write_bitbuf_array)>();
		});

		// Write Player Game State Data Node
		main_batch.add("WPGSDN", "48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 57 41 54 41 55 41 56 41 57 48 83 EC 30 0F B7 81", [this](memory::handle ptr) {
			m_write_player_game_state_data_node = ptr.as<functions::write_player_game_state_data_node>();
		});

		// Replay Interface
		main_batch.add("RI", "0F B7 44 24 ? 66 89 44 4E", [this](memory::handle ptr) {
			m_replay_interface = ptr.add(0x1F).rip().as<rage::CReplayInterface**>();
		});

		// Ptr To Handle
		main_batch.add("PTH", "48 8B F9 48 83 C1 10 33 DB", [this](memory::handle ptr) {
			m_ptr_to_handle = ptr.sub(0x15).as<decltype(m_ptr_to_handle)>();
		});

		// Handle To Ptr
		main_batch.add("GSH", "83 F9 FF 74 31 4C 8B 0D", [this](memory::handle ptr) {
			m_handle_to_ptr = ptr.as<decltype(m_handle_to_ptr)>();
		});

		// Blame Explode
		main_batch.add("BE", "0F 85 ? ? ? ? 48 8B 05 ? ? ? ? 48 8B 48 08 E8", [this](memory::handle ptr) {
			m_blame_explode = memory::byte_patch::make(ptr.as<std::uint16_t*>(), 0xE990).get();
		});

		// CNetworkObjectMgr
		main_batch.add("CNOM", "48 8B 0D ? ? ? ? 45 33 C0 E8 ? ? ? ? 33 FF 4C 8B F0", [this](memory::handle ptr) {
			m_network_object_mgr = ptr.add(3).rip().as<CNetworkObjectMgr**>();
		});

		// Network Player Mgr Init
		main_batch.add("NPMI", "41 56 48 83 EC ? 48 8B F1 B9 ? ? ? ? 49 8B F9 41 8B E8 4C 8B F2 E8", [this](memory::handle ptr) {
			m_network_player_mgr_init = ptr.sub(0x13).as<decltype(m_network_player_mgr_init)>();
		});

		// Network Player Mgr Shutdown
		main_batch.add("NPMS", "48 8D 9F ? ? ? ? EB ? 48 8B 13 48 85 D2 74 ? 48 8B CB E8 ? ? ? ? 48 83 7B ? ? 75 ? 48 8D 9F", [this](memory::handle ptr) {
			m_network_player_mgr_shutdown = ptr.sub(0x1A).as<decltype(m_network_player_mgr_shutdown)>();
		});

		// FriendRegistry
		main_batch.add("FR", "3B 0D ? ? ? ? 73 17", [this](memory::handle ptr) {
			m_friend_registry = ptr.add(2).rip().as<FriendRegistry*>();
		});

		// GET_SCREEN_COORDS_FROM_WORLD_COORDS
		main_batch.add("GSCFWC", "E8 ? ? ? ? 84 C0 74 19 F3 0F 10 44 24", [this](memory::handle ptr) {
			m_get_screen_coords_for_world_coords = ptr.add(1).rip().as<functions::get_screen_coords_for_world_coords>();
		});

		// GET_GAMEPLAY_CAM_COORDS
		main_batch.add("GGCC", "8B 90 ? ? ? ? 89 13", [this](memory::handle ptr) {
			m_get_gameplay_cam_coords = ptr.sub(0xE).as<functions::get_gameplay_cam_coords>();
		});

		// Give Pickup Reward
		main_batch.add("GPR", "48 8B C8 33 C0 48 85 C9 74 0A 44 8B C3 8B D7 E8", [this](memory::handle ptr) {
			m_give_pickup_rewards = ptr.sub(0x28).as<decltype(m_give_pickup_rewards)>();
		});

		// Write Player Gamer Data Node
		main_batch.add("WPGDN", "48 89 5C 24 ? 48 89 74 24 ? 57 48 83 EC 20 48 81 C1 ? ? ? ? 48 8B DA E8", [this](memory::handle ptr) {
			m_write_player_gamer_data_node = ptr.as<PVOID>();
		});

		// Receive Net Message
		main_batch.add("RNM", "48 83 EC 20 4C 8B 71 50 33 ED", [this](memory::handle ptr) {
			m_receive_net_message = ptr.sub(0x19).as<PVOID>();
		});

		// Get Network Event Data
		main_batch.add("GNED", "53 43 52 49 50 54 5F 4E 45 54 57 4F 52 4B", [this](memory::handle ptr) {
			m_get_network_event_data = *ptr.sub(0x38).as<PVOID*>();
		});

		// Assign Physical Index
		main_batch.add("API", "48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 57 41 54 41 55 41 56 41 57 48 83 EC 20 41 8A E8", [this](memory::handle ptr) {
			m_assign_physical_index = ptr.as<PVOID>();
		});

		// Received Clone Create
		main_batch.add("RCC", "48 8B C4 66 44 89 48", [this](memory::handle ptr) {
			m_received_clone_create = ptr.as<PVOID>();
		});

		// Can Apply Data
		main_batch.add("CAD", "E8 ? ? ? ? 84 C0 0F 84 AF 01 00 00 48 8B 03", [this](memory::handle ptr) {
			m_can_apply_data = ptr.add(1).rip().as<PVOID>();
		});

		// Received clone sync & Get sync tree for type & Get net object for player & Get sync type info & Get net object
		main_batch.add("RCS/GSTFT/GNOFP/GNO/GSTI", "4C 8B FA 41 0F B7 D1", [this](memory::handle ptr) {
			m_received_clone_sync = ptr.sub(0x1D).as<decltype(m_received_clone_sync)>();
			m_get_sync_tree_for_type = ptr.add(0x14).rip().as<decltype(m_get_sync_tree_for_type)>(); // 0F B7 CA 83 F9 07 .as()
			m_get_net_object = ptr.add(0x76).rip().as<decltype(m_get_net_object)>(); // E8 ? ? ? ? 0F B7 53 7C .add(1).rip().as()
			m_get_sync_type_info = ptr.add(0x8C).rip().as<decltype(m_get_sync_type_info)>(); // 44 0F B7 C1 4C 8D 0D .as()
		});

		// Read Bitbuffer Into Sync Tree
		main_batch.add("RBIST", "E8 ? ? ? ? 48 8B BC 24 B0 00 00 00", [this](memory::handle ptr) {
			m_read_bitbuffer_into_sync_tree = ptr.add(1).rip().as<functions::read_bitbuffer_into_sync_tree>();
		});

		// Model Hash Table
		main_batch.add("MHT", "4C 03 05 ? ? ? ? EB 03", [this](memory::handle ptr) {
			m_model_table = ptr.add(3).rip().as<HashTable<CBaseModelInfo*>*>();
		});

		// Get Model Info
		main_batch.add("GMI", "41 3B 0A 74 54", [this](memory::handle ptr) {
			m_get_model_info = ptr.sub(46).as<PVOID>();
		});

		// Get Label Text
		main_batch.add("GLT", "75 ? E8 ? ? ? ? 8B 0D ? ? ? ? 65 48 8B 04 25 ? ? ? ? BA ? ? ? ? 48 8B 04 C8 8B 0C 02 D1 E9", [this](memory::handle ptr) {
			m_get_label_text = ptr.sub(19).as<PVOID>();
		});

		// Multiplayer chat filter
		main_batch.add("MCF", "E8 ? ? ? ? 83 F8 FF 75 B9", [this](memory::handle ptr) {
			m_check_chat_profanity = ptr.add(1).rip().as<decltype(m_check_chat_profanity)>();
		});

		// Network
		main_batch.add("N", "48 8B 0D ? ? ? ? 48 8B D7 E8 ? ? ? ? 84 C0 75 17 48 8B 0D ? ? ? ? 48 8B D7", [this](memory::handle ptr) {
			m_network = ptr.add(3).rip().as<Network**>();
		});

		// Reset Network Complaints
		main_batch.add("RENC", "E8 ? ? ? ? 8B 8B ? ? ? ? 03 CF", [this](memory::handle ptr) {
			m_reset_network_complaints = ptr.add(1).rip().as<functions::reset_network_complaints>();
		});

		// fiDevice Get Device
		main_batch.add("FDGD", "41 B8 07 00 00 00 48 8B F1 E8", [this](memory::handle ptr) {
			m_fidevice_get_device = ptr.sub(0x1F).as<functions::fidevice_get_device>();
		});

		// fiDevices
		main_batch.add("FDS", "74 1B 48 8D 0D ? ? ? ? 41 8B D6", [this](memory::handle ptr) {
			m_fidevices     = ptr.add(5).rip().as<uintptr_t>();
			m_fidevices_len = ptr.add(5).rip().add(8).as<uint16_t*>();
		});

		// fiPackfile ctor
		main_batch.add("FPFC", "44 89 41 28 4C 89 41 38 4C 89 41 50 48 8D", [this](memory::handle ptr) {
			m_fipackfile_ctor      = ptr.sub(0x1E).as<functions::fipackfile_ctor>();
			m_fipackfile_instances = ptr.add(26).rip().as<rage::fiPackfile**>();
		});

		// fiPackfile open archive
		main_batch.add("FPFOA", "48 8D 68 98 48 81 EC 40 01 00 00 41 8B F9", [this](memory::handle ptr) {
			m_fipackfile_open_archive = ptr.sub(0x18).as<functions::fipackfile_open_archive>();
		});

		// fiPackfile mount
		main_batch.add("FPFM", "84 C0 74 1D 48 85 DB 74 0F 48", [this](memory::handle ptr) {
			m_fipackfile_mount = ptr.sub(0x1E).as<functions::fipackfile_mount>();
		});

		// fiPackfile unmount
		main_batch.add("FPFUM", "E8 ? ? ? ? 84 C0 74 37 80 3D", [this](memory::handle ptr) {
			m_fipackfile_unmount = ptr.add(1).rip().as<functions::fipackfile_unmount>();
		});

		// game version + online version
		main_batch.add("GVOV", "8B C3 33 D2 C6 44 24 20", [this](memory::handle ptr) {
			m_game_version   = ptr.add(0x24).rip().as<const char*>();
			m_online_version = ptr.add(0x24).rip().add(0x20).as<const char*>();
		});

		// Invalid Mods Crash Detour
		main_batch.add("IMCD", "E8 ? ? ? ? 40 88 7C 24 ? 49 89 9C 24", [this](memory::handle ptr) {
			m_invalid_mods_crash_detour = ptr.add(1).rip().as<PVOID>();
		});

		// Send Chat Ptr
		main_batch.add("SCP", "83 7E 1C 01 48 8B 3D", [this](memory::handle ptr) {
			m_send_chat_ptr = ptr.add(7).rip().as<int64_t**>();
		});

		// Send Chat Message
		main_batch.add("SCM", "48 83 EC 20 48 8B F1 48 8B CA 41 8A E9", [this](memory::handle ptr) {
			m_send_chat_message = ptr.sub(21).as<functions::send_chat_message>();
		});

		// Start Get Session By Gamer Handle
		main_batch.add("SGSBGH", "E8 ? ? ? ? 84 C0 0F 84 ? ? ? ? 8B 05 ? ? ? ? 48 8D 4C 24", [this](memory::handle ptr) {
			m_start_get_session_by_gamer_handle = ptr.add(1).rip().as<functions::start_get_session_by_gamer_handle>();
		});

		// Start Matchmaking Find Sessions
		main_batch.add("SGSBGH", "E8 ? ? ? ? 84 C0 0F 84 F6 FE FF FF", [this](memory::handle ptr) {
			m_start_matchmaking_find_sessions = ptr.add(1).rip().as<functions::start_matchmaking_find_sessions>();
		});

		// Join Session By Info
		main_batch.add("JSBI", "E8 ? ? ? ? 0F B6 CB 84 C0 41 0F 44 CD", [this](memory::handle ptr) {
			m_join_session_by_info = ptr.add(1).rip().as<functions::join_session_by_info>();
		});

		// Script VM
		main_batch.add("VM", "E8 ? ? ? ? 48 85 FF 48 89 1D", [this](memory::handle ptr) {
			m_script_vm = ptr.add(1).rip().as<functions::script_vm>();
		});

		// Generate UUID
		main_batch.add("GU", "E8 ? ? ? ? 84 C0 74 0C 48 8B 44 24 ? 48 89 03", [this](memory::handle ptr) {
			m_generate_uuid = ptr.add(1).rip().as<functions::generate_uuid>();
		});

		// Host Token
		main_batch.add("HT", "48 8B 05 ? ? ? ? 48 83 F8 FF", [this](memory::handle ptr) {
			m_host_token = ptr.add(3).rip().as<std::uint64_t*>();
		});

		// Profile Gamer Info
		main_batch.add("PGI", "48 8D 05 ? ? ? ? 48 8B FE", [this](memory::handle ptr) {
			m_profile_gamer_info = ptr.add(3).rip().as<rage::rlGamerInfo*>();
		});

		// Player Info Gamer Info
		main_batch.add("PIGI", "E8 ? ? ? ? 48 8D 4D 20 48 8B D0 E8 ? ? ? ? 41 8A CF", [this](memory::handle ptr) {
			m_player_info_gamer_info = ptr.add(1).rip().add(3).rip().as<rage::rlGamerInfo*>();
		});

		// Communications
		main_batch.add("C", "48 8B 1D ? ? ? ? 48 8D 4C 24 30", [this](memory::handle ptr) {
			m_communications = ptr.add(3).rip().as<CCommunications**>();
		});

		// Serialize Ped Inventory Data Node
		main_batch.add("SPIDN", "48 8B C4 48 89 58 08 48 89 68 10 48 89 70 18 48 89 78 20 41 54 41 56 41 57 48 83 EC 20 48 8B 02 48 8B F1 48 8B CA 48 8B FA FF 90", [this](memory::handle ptr) {
			m_serialize_ped_inventory_data_node = ptr.as<PVOID>();
		});

		// Serialize Vehicle Gadget Data Node
		main_batch.add("SVGDN", "48 89 5C 24 08 48 89 6C 24 10 48 89 74 24 18 57 41 56 41 57 48 83 EC 30 48 8B 02 48 8D", [this](memory::handle ptr) {
			m_serialize_vehicle_gadget_data_node = ptr.as<PVOID>();
		});

		// Get Vehicle Gadget Array Size
		main_batch.add("GVGAS", "40 53 48 83 EC 40 33 DB E8", [this](memory::handle ptr) {
			m_get_vehicle_gadget_array_size = ptr.as<functions::get_vehicle_gadget_array_size>();
		});

		// Handle Join Request
		main_batch.add("HJR", "48 8B C4 48 89 58 08 4C 89 48 20 4C 89 40 18 48 89 50 10 55 56 57 41 54 41 55 41 56 41 57 48 8D A8 E8", [this](memory::handle ptr) {
			m_handle_join_request = ptr.as<PVOID>();
		});

		// Write Join Response Data
		main_batch.add("WJRD", "E8 ?? ?? ?? ?? 41 8B DF 84 C0", [this](memory::handle ptr) {
			m_write_join_response_data = ptr.add(1).rip().as<functions::write_join_response_data>();
		});

		// Queue Packet
		main_batch.add("QP", "E8 ? ? ? ? 84 C0 74 4D B3 01", [this](memory::handle ptr) {
			m_queue_packet = ptr.add(1).rip().as<functions::queue_packet>();
		});

		// Sort Session Details
		main_batch.add("SGS", "C3 0F 2E 42 0C", [this](memory::handle ptr) {
			m_sort_session_details = ptr.sub(0x10).as<PVOID>();
		});

		// Add Player To Session
		main_batch.add("APTS", "E8 ?? ?? ?? ?? 48 8D 8D F0 01 00 00 8A D8", [this](memory::handle ptr) {
			m_add_player_to_session = ptr.add(1).rip().as<PVOID>();
		});

		// Send Chat Net Message
		main_batch.add("SCNM", "E8 ? ? ? ? 41 FF C4 48 83 C5 08", [this](memory::handle ptr) {
			m_send_chat_net_message = ptr.add(1).rip().as<PVOID>();
		});

		// Process Matchmaking Find Response
		main_batch.add("PMFR", "48 89 5C 24 08 48 89 74 24 10 57 48 81 EC F0 00 00 00 41 83", [this](memory::handle ptr) {
			m_process_matchmaking_find_response = ptr.as<PVOID>();
		});

		// Serialize Player Data Message
		main_batch.add("SPDM", "48 89 5C 24 08 48 89 74 24 10 48 89 7C 24 18 41 56 48 83 EC 20 BF 01 00 00 00", [this](memory::handle ptr) {
			m_serialize_player_data_msg = ptr.as<PVOID>();
		});

		// Serialize Join Request Message
		main_batch.add("SJRM", "E8 ?? ?? ?? ?? 84 C0 0F 84 9B 00 00 00 49 8D 8F 50 11 00 00", [this](memory::handle ptr) {
			m_serialize_join_request_message = ptr.add(1).rip().as<PVOID>();
		});

		// Is Matchmaking Session Valid
		main_batch.add("IMSV", "48 89 5C 24 08 48 89 6C 24 10 48 89 74 24 18 57 41 54 41 55 41 56 41 57 48 83 EC 20 45 0F", [this](memory::handle ptr) {
			memory::byte_patch::make(ptr.as<void*>(), std::to_array({0xB0, 0x01, 0xC3}))->apply(); // has no observable side effects
		});

		// Send Network Damage
		main_batch.add("SND", "E8 ? ? ? ? E9 E9 01 00 00 48 8B CB", [this](memory::handle ptr) {
			m_send_network_damage = ptr.add(1).rip().as<functions::send_network_damage>();
		});

		// Request Ragdoll
		main_batch.add("RR", "E8 ? ? ? ? 09 B3 ? ? ? ? 48 8B 5C 24", [this](memory::handle ptr) {
			m_request_ragdoll = ptr.add(1).rip().as<functions::request_ragdoll>();
		});

		// Request Control
		main_batch.add("RC", "E8 ? ? ? ? EB 3E 48 8B D3", [this](memory::handle ptr) {
			m_request_control = ptr.add(1).rip().as<functions::request_control>();
		});

		// Get Connection Peer & Send Remove Gamer Command
		main_batch.add("GCP&SRGC", "8D 42 FF 83 F8 FD 77 3D", [this](memory::handle ptr) {
			m_get_connection_peer   = ptr.add(23).rip().as<functions::get_connection_peer>();
			m_send_remove_gamer_cmd = ptr.add(65).rip().as<functions::send_remove_gamer_cmd>();
		});

		// Handle Remove Gamer Command
		main_batch.add("HRGC", "41 FF C6 FF C7", [this](memory::handle ptr) {
			m_handle_remove_gamer_cmd = ptr.sub(0x6E).as<functions::handle_remove_gamer_cmd>();
		});

		// Broadcast Net Array
		main_batch.add("BNA", "48 89 5C 24 ? 48 89 54 24 ? 55 56 57 41 54 41 55 41 56 41 57 48 83 EC 40 48 8B 05 ? ? ? ? 66 44 89 4C 24", [this](memory::handle ptr) {
			m_broadcast_net_array = ptr.as<PVOID>();
		});

		// Broadcast Net Array Patch
		main_batch.add("BP", "74 73 FF 90 ? ? ? ? 8B D5 4C 8B 00 48 8B C8 41 FF 50 30", [this](memory::handle ptr) {
			m_broadcast_patch = memory::byte_patch::make(ptr.as<uint8_t*>(), 0xEB).get();
		});

		// Rage Security
		main_batch.add("RS", "48 8B 1D ? ? ? ? 33 F6 BD C3 9E 26 00", [this](memory::handle ptr) {
			m_security = ptr.add(3).rip().as<rage::atSingleton<rage::RageSecurity>*>();
		});

		// Send Session Matchmaking Attributes
		main_batch.add("SSMA", "48 8B C4 48 89 58 08 48 89 68 10 48 89 70 18 48 89 78 20 41 56 48 81 EC D0 00 00 00 49 8B", [this](memory::handle ptr) {
			m_send_session_matchmaking_attributes = ptr.as<PVOID>();
		});

		// Serialize Take Off Ped Variation Task
		main_batch.add("STOPVT", "40 55 53 57 41 56 48 8B EC 48 83 EC 68", [this](memory::handle ptr) {
			m_serialize_take_off_ped_variation_task = ptr.as<PVOID>();
		});

		// Chat Data
		main_batch.add("CD", "48 8B 05 ? ? ? ? 0F 45 DF", [this](memory::handle ptr) {
			m_chat_data = ptr.add(3).rip().as<ChatData**>();
		});

		// Social Club Info
		main_batch.add("SCI", "48 8B D3 48 8D 4C 24 ? 48 69 D2", [this](memory::handle ptr) {
			m_sc_info = ptr.sub(4).rip().as<ScInfo*>();
		});

		// Create Script Handler
		main_batch.add("CSH", "48 8D 05 ? ? ? ? 4C 8D 0D ? ? ? ? 41 83 C8 FF 48 89 03 89 53 70 88 53 74 4C 89 4B 68 48 89 93", [this](memory::handle ptr) {
			m_create_script_handler = *(ptr.add(3).rip().as<std::uint64_t**>() + 8);
		});

		// Creator Warp Cheat Triggered Patch
		main_batch.add("CW", "74 44 E8 ? ? ? ? 80 65 2B F8 48 8D 0D ? ? ? ? 48 89 4D 17 48 89 7D 1F 89 7D 27 C7 45", [](memory::handle ptr) {
			memory::byte_patch::make(ptr.as<uint8_t*>(), 0xEB)->apply();
		});

		// Constraint Attachment Crash
		main_batch.add("CAC", "40 53 48 83 EC 20 48 8B D9 48 8B 49 38 48 8B 01", [this](memory::handle ptr) {
			m_constraint_attachment_crash = ptr.as<PVOID>();
		});

		// Invalid Decal Crash
		main_batch.add("IDC", "E8 ? ? ? ? 8B 9C 24 B8 00 00 00 4C 8B AC 24 A8 00 00 00", [this](memory::handle ptr) {
			m_invalid_decal_crash = ptr.add(1).rip().as<PVOID>();
		});

		// Task Parachute Object 0x270
		main_batch.add("TPO270", "0F 88 ? ? ? ? 75 34", [this](memory::handle ptr) {
			m_task_parachute_object_0x270
				= ptr.sub(6).as<PVOID>();
		});

		// Encode Session Info
		main_batch.add("ESI", "E8 ? ? ? ? C6 83 94 01 00 00 01", [this](memory::handle ptr) {
			m_encode_session_info = ptr.add(1).rip().as<functions::encode_session_info>();
		});

		// Decode Session Info
		main_batch.add("DSI", "E8 ?? ?? ?? ?? 84 C0 74 16 48 8B 4B 60", [this](memory::handle ptr) {
			m_decode_session_info = ptr.add(1).rip().as<functions::decode_session_info>();
		});

		// Decode Peer Info
		main_batch.add("DPI", "48 89 5C 24 08 48 89 74 24 10 57 48 81 EC C0 00 00 00 48 8B F1 49", [this](memory::handle ptr) {
			m_decode_peer_info = ptr.as<functions::decode_peer_info>();
		});

		// NTQVM Caller
		main_batch.add("NTQVMC", "66 0F 6F 0D ? ? ? ? 66 0F 6F 05 ? ? ? ? 66 0F 66 C4", [this](memory::handle ptr) {
			memory::byte_patch::make(ptr.add(4).rip().sub(32).as<uint64_t*>(), (uint64_t)&hooks::nt_query_virtual_memory)
			    ->apply();
		});

		// Main File Object
		main_batch.add("MFO", "48 8D 05 ? ? ? ? 48 8D 1C D0 EB 03", [this](memory::handle ptr) {
			m_main_file_object = ptr.add(3).rip().as<datafile_commands::SveFileObject*>();
		});

		// Load Cloud File
		main_batch.add("LCF", "48 89 5C 24 08 48 89 74 24 10 57 48 83 EC 40 48 8B F2 48 8B D9 41 8B D0", [this](memory::handle ptr) {
			m_load_cloud_file = ptr.as<functions::load_cloud_file>();
		});

		// Set As Active Cloud File
		main_batch.add("SAACF", "48 83 EC 28 45 33 C0 4C 39", [this](memory::handle ptr) {
			m_set_as_active_cloud_file = ptr.as<functions::set_as_active_cloud_file>();
		});

		// Save JSON Data
		main_batch.add("SJD", "48 89 5C 24 08 57 48 83 EC 30 33 DB 48 8B FA 48", [this](memory::handle ptr) {
			m_save_json_data = ptr.as<functions::save_json_data>();
		});

		// Network Time
		main_batch.add("NT", "48 8B 0D ? ? ? ? E8 ? ? ? ? 33 DB 84 C0 74 41", [this](memory::handle ptr) {
			m_network_time = ptr.add(3).rip().as<rage::netTime**>();
		});

		// Sync Network Time
		main_batch.add("SNT", "E8 ? ? ? ? 8B 43 5C", [this](memory::handle ptr) {
			m_sync_network_time = ptr.add(1).rip().as<functions::sync_network_time>();
		});

		// Queue Dependency
		main_batch.add("QD", "48 89 5C 24 ? 57 48 83 EC ? 0F B6 99", [this](memory::handle ptr) {
			m_queue_dependency = ptr.as<PVOID>();
		});

		// Interval Check Function
		main_batch.add("ICF", "48 8D 0D ? ? ? ? 88 05 ? ? ? ? 48 8D 05", [this](memory::handle ptr) {
			m_interval_check_func = ptr.add(3).rip().as<PVOID>();
		});

		// Sound Overload Detour
		main_batch.add("SOD", "66 45 3B C1 74 38", [this](memory::handle ptr) {
			g_sound_overload_ret_addr = ptr.add(13 + 15).as<decltype(g_sound_overload_ret_addr)>();
			std::vector<byte> bytes = {0xFF, 0x25, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x90}; // far jump opcode + a nop opcode
			*(void**)(bytes.data() + 6) = sound_overload_detour;
			memory::byte_patch::make(ptr.add(13).as<void*>(), bytes)->apply();
		});

		// Prepare Metric For Sending
		main_batch.add("PMFS", "48 8B C4 48 89 58 08 48 89 68 10 48 89 70 18 48 89 78 20 41 56 48 83 EC 30 49 8B E8 4C 8D 40 EC 49 8B F1 48 8B D9 40 32 FF E8", [this](memory::handle ptr) {
			m_prepare_metric_for_sending = ptr.as<PVOID>();
		});

		// Send Packet
		main_batch.add("SP", "48 8B C4 48 89 58 08 48 89 70 10 48 89 78 18 4C 89 48 20 55 41 54 41 55 41 56 41 57 48 8D A8 98", [this](memory::handle ptr) {
			m_send_packet = ptr.as<functions::send_packet>();
		});

		// Connect To Peer
		main_batch.add("CTP", "48 89 5C 24 08 4C 89 4C 24 20 48 89 54 24 10 55 56 57 41 54 41 55 41 56 41 57 48 83 EC 60 4D", [this](memory::handle ptr) {
			m_connect_to_peer = ptr.as<functions::connect_to_peer>();
		});

		// Fragment Physics Crash
		main_batch.add("FPC", "E8 ? ? ? ? 44 8B 4D 1C", [this](memory::handle ptr) {
			m_fragment_physics_crash = ptr.add(1).rip().as<PVOID>();
		});

		// Fragment Physics Crash 2
		main_batch.add("FPC2", "E8 ? ? ? ? 84 C0 75 0B 41 FF CF", [this](memory::handle ptr) {
			m_fragment_physics_crash_2 = ptr.add(1).rip().as<PVOID>();
		});

		// Clear Ped Tasks Network
		main_batch.add("CPTN", "E8 ? ? ? ? EB 28 48 8B 8F A0 10 00 00", [this](memory::handle ptr) {
			m_clear_ped_tasks_network = ptr.add(1).rip().as<functions::clear_ped_tasks_network>();
		});

		// Infinite Train Crash
		main_batch.add("ITC", "E8 ? ? ? ? F3 44 0F 10 93 90 03 00 00", [this](memory::handle ptr) {
			m_infinite_train_crash = ptr.add(1).rip().as<PVOID>();
			m_get_next_carriage    = ptr.add(1).rip().add(0xF).rip().as<functions::get_next_carriage>();
		});

		// Get Entity Attached To
		main_batch.add("GEAT", "48 83 EC 28 48 8B 51 50 48 85 D2 74 04", [this](memory::handle ptr) {
			m_get_entity_attached_to = ptr.as<functions::get_entity_attached_to>();
		});

		// Received Array Update
		main_batch.add("RAU", "48 89 5C 24 10 55 56 57 41 54 41 55 41 56 41 57 48 8B EC 48 83 EC 30 48 8B 05", [this](memory::handle ptr) {
			m_received_array_update = ptr.as<PVOID>();
		});

		// Receive Pickup
		main_batch.add("RPI", "49 8B 80 ? ? ? ? 48 85 C0 74 0C F6 80 ? ? ? ? ? 75 03 32 C0 C3", [this](memory::handle ptr) {
			m_receive_pickup = ptr.as<PVOID>();
		});

		// Write Player Camera Data Node
		main_batch.add("WPCDN", "48 8B C4 48 89 58 20 55 56 57 41 54 41 55 41 56 41 57 48 8D 6C 24 B0 48 81 EC 50 01 00 00 4C", [this](memory::handle ptr) {
			m_write_player_camera_data_node = ptr.as<PVOID>();
		});

		// Send Player Card Stats
		main_batch.add("SPCS", "48 89 5C 24 08 57 48 83 EC 30 48 83 64 24 20 00 48 8B DA 41", [this](memory::handle ptr) {
			m_send_player_card_stats = ptr.as<PVOID>();
		});

		// Force Player Card Refresh
		main_batch.add("FPCR", "44 38 2D ? ? ? ? 74 1D 44 00 A6 BB 07 00 00", [this](memory::handle ptr) {
			m_force_player_card_refresh = ptr.add(3).rip().as<bool*>();
		});

		// Serialize Stats
		main_batch.add("SS", "48 89 5C 24 08 48 89 74 24 10 48 89 7C 24 20 55 41 54 41 55 41 56 41 57 48 8B EC 48 83 EC 50 45", [this](memory::handle ptr) {
			m_serialize_stats = ptr.as<PVOID>();
		});

		// Write Player Creation Data Node
		main_batch.add("WPCDN", "48 83 EC 38 48 8B 81 F0", [this](memory::handle ptr) {
			m_write_player_creation_data_node = ptr.as<PVOID>();
		});

		// Write Player Appearance Data Node
		main_batch.add("WPADN", "48 8B C4 48 89 50 10 48 89 48 08 53", [this](memory::handle ptr) {
			m_write_player_appearance_data_node = ptr.as<PVOID>();
		});

		// DC
		main_batch.add("DC", "48 8B D1 49 8B CA ? ? ? ? ? 48 8B D1 49 8B CA", [this](memory::handle ptr) {
			m_disable_collision = memory::byte_patch::make(ptr.sub(2).as<uint8_t*>(), 0xEB).get();
		});

		// AWIV
		main_batch.add("AWIV", "49 3B C9 7C F0 ? ? C3", [this](memory::handle ptr) {
			m_allow_weapons_in_vehicle = memory::byte_patch::make(ptr.add(5).as<uint16_t*>(), 0x01B0).get(); //In order for the second xref loop not to stop
		});

		auto mem_region = memory::module("GTA5.exe");
		if (!main_batch.run(mem_region))
		{
			throw std::runtime_error("Failed to find some patterns.");
		}

		memory::batch socialclub_batch;

		// Presence Data
		socialclub_batch.add("PD", "48 8D 05 ? ? ? ? 48 8B F1 48 89 01 48 8D 99 90 00 00 00", [this](memory::handle ptr) {
			auto presence_data_vft             = ptr.add(3).rip().as<PVOID*>();
			m_update_presence_attribute_int    = presence_data_vft[1];
			m_update_presence_attribute_string = presence_data_vft[3];
		});

		// Start Get Presence Attributes
		socialclub_batch.add("SGPA", "48 8B C4 48 89 58 08 48 89 68 10 48 89 70 18 48 89 78 20 41 54 41 56 41 57 48 83 EC 40 33 DB 41", [this](memory::handle ptr) {
			m_start_get_presence_attributes = ptr.as<functions::start_get_presence_attributes>();
		});

		auto sc_module = memory::module("socialclub.dll");
		if (sc_module.wait_for_module())
		{
			socialclub_batch.run(sc_module);
		}
		else
			LOG(WARNING) << "socialclub.dll module was not loaded within the time limit.";

		/**
		 * Freemode thread restorer through VM patch
		 */
		if (auto pat1 = mem_region.scan("3b 0a 0f 83 ? ? ? ? 48 ff c7"))
		{
			memory::byte_patch::make(pat1.add(2).as<uint32_t*>(), 0xc9310272)->apply();
			memory::byte_patch::make(pat1.add(6).as<uint16_t*>(), 0x9090)->apply();
		}

		if (auto pat2 = mem_region.scan("3b 0a 0f 83 ? ? ? ? 49 03 fa"))
		{
			memory::byte_patch::make(pat2.add(2).as<uint32_t*>(), 0xc9310272)->apply();
			memory::byte_patch::make(pat2.add(6).as<uint16_t*>(), 0x9090)->apply();
		}

		auto pat3 = mem_region.scan_all("3b 11 0f 83 ? ? ? ? 48 ff c7");
		for (auto& handle : pat3)
		{
			memory::byte_patch::make(handle.add(2).as<uint32_t*>(), 0xd2310272)->apply();
			memory::byte_patch::make(handle.add(6).as<uint16_t*>(), 0x9090)->apply();
		}

		auto pat4 = mem_region.scan_all("3b 11 0f 83 ? ? ? ? 49 03 fa");
		for (auto& handle : pat4)
		{
			memory::byte_patch::make(handle.add(2).as<uint32_t*>(), 0xd2310272)->apply();
			memory::byte_patch::make(handle.add(6).as<uint16_t*>(), 0x9090)->apply();
		}

		m_hwnd = FindWindowW(L"grcWindow", nullptr);

		if (!m_hwnd)
			throw std::runtime_error("Failed to find the game's window.");

		g_pointers = this;
	}

	pointers::~pointers()
	{
		memory::byte_patch::restore_all();

		g_pointers = nullptr;
	}
}
