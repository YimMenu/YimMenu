#pragma once
#include "MinHook.h"
#include "common.hpp"
#include "detour_hook.hpp"
#include "gta/enums.hpp"
#include "gta/fwddec.hpp"
#include "gta/script_thread.hpp"
#include "vmt_hook.hpp"

#include <network/netConnection.hpp>

class CPlayerGamerDataNode;
class CPlayerGameStateDataNode;
class CPedInventoryDataNode;
class CDynamicEntityGameStateDataNode;
class CVehicleGadgetDataNode;
class CPlayerCameraDataNode;
class CJoinRequestContext;
class SessionSortEntry;
class RemoteGamerInfoMsg;
class CMsgTextMessage;
class CNetGamePlayerDataMsg;
class MatchmakingAttributes;
class CNetworkIncrementStatEvent;
class CScriptedGameEvent;
class NetworkGameFilterMatchmakingComponent;
class ClonedTakeOffPedVariationInfo;
class CPlayerCardStats;
class CStatsSerializationContext;
class CPlayerCreationDataNode;
class CPlayerAppearanceDataNode;
class CFoundDevice;
class IDirectSoundCapture;
class CVehicleProximityMigrationDataNode;
class CNonPhysicalPlayerData;
class TimecycleKeyframeData;

namespace rage
{
	class snSession;
	class JSONNode;
	class netArrayHandlerBase;
	class CEventNetwork;
	class CSyncDataBase;
	class rlGamerHandle;
	class netConnectionManager;
	class datBitBuffer;
	class rlMetric;
	class rlTaskStatus;
}

namespace big
{
	struct hooks
	{
		static bool run_script_threads(uint32_t ops_to_execute);

		static constexpr auto swapchain_num_funcs           = 19;
		static constexpr auto swapchain_present_index       = 8;
		static constexpr auto swapchain_resizebuffers_index = 13;
		static HRESULT swapchain_present(IDXGISwapChain* this_, UINT sync_interval, UINT flags);
		static HRESULT swapchain_resizebuffers(IDXGISwapChain* this_, UINT buffer_count, UINT width, UINT height, DXGI_FORMAT new_format, UINT swapchain_flags);

		static LRESULT wndproc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

		static const char* get_label_text(void* unk, const char* label);

		static GtaThread* gta_thread_start(unsigned int** a1, unsigned int a2);
		static rage::eThreadState gta_thread_kill(GtaThread* thread);
		static bool init_native_tables(rage::scrProgram* program);
		static rage::eThreadState script_vm(uint64_t* start_stack, uint64_t** scr_globals, rage::scrProgram* program, rage::scrThreadContext* ctx);

		static bool network_player_mgr_init(CNetworkPlayerMgr* _this, uint64_t a2, uint32_t a3, uint32_t a4[4]);
		static void network_player_mgr_shutdown(CNetworkPlayerMgr* _this);

		static bool fragment_physics_crash_2(float* a1, float* a2);

		static void received_event(rage::netEventMgr* event_manager, CNetGamePlayer* source_player, CNetGamePlayer* target_player, uint16_t event_id, int event_index, int event_handled_bitset, int unk, rage::datBitBuffer* bit_buffer);

		// these two aren't actually hooks, just helper functions for hooks
		static bool increment_stat_event(CNetworkIncrementStatEvent* net_event_struct, CNetGamePlayer* sender);
		static bool scripted_game_event(CScriptedGameEvent* scripted_game_event, CNetGamePlayer* player);

		static bool receive_net_message(void* netConnectionManager, void* a2, rage::netConnection::InFrame* frame);
		static rage::CEventNetwork* get_network_event_data(int64_t unk, rage::CEventNetwork* net_event);

		static void* assign_physical_index(CNetworkPlayerMgr* netPlayerMgr, CNetGamePlayer* player, uint8_t new_index);

		//SYNC
		static void received_clone_create(CNetworkObjectMgr* mgr, CNetGamePlayer* src, CNetGamePlayer* dst, eNetObjType object_type, int32_t object_id, int32_t object_flag, rage::datBitBuffer* buffer, int32_t timestamp);
		static eAckCode received_clone_sync(CNetworkObjectMgr* mgr, CNetGamePlayer* src, CNetGamePlayer* dst, eNetObjType object_type, uint16_t object_id, rage::datBitBuffer* bufer, uint16_t unk, uint32_t timestamp);
		static bool can_apply_data(rage::netSyncTree* tree, rage::netObject* object);

		static void write_player_gamer_data_node(rage::netObject* player, CPlayerGamerDataNode* node);
		static void write_player_game_state_data_node(rage::netObject* player, CPlayerGameStateDataNode* node);

		static void invalid_mods_crash_detour(int64_t a1, int64_t a2, int a3, char a4);
		static void invalid_decal(uintptr_t a1, int a2);
		static int task_parachute_object_0x270(uint64_t _this, int a2, int a3);

		static bool update_presence_attribute_int(void* presence_data, int profile_index, char* attr, uint64_t value);
		static bool update_presence_attribute_string(void* presence_data, int profile_index, char* attr, char* value);

		static bool handle_join_request(Network* network, rage::snSession* session, rage::rlGamerInfo* player_info, CJoinRequestContext* ctx, BOOL is_transition_session);

		static bool sort_session_details(SessionSortEntry* e1, SessionSortEntry* e2);

		static bool send_chat_message(void* team_mgr, rage::rlGamerInfo* local_gamer_info, char* message, bool is_team);

		static bool process_matchmaking_find_response(void* _this, void* unused, rage::JSONNode* node, int* unk);

		static bool serialize_player_data_msg(CNetGamePlayerDataMsg* msg, rage::datBitBuffer* buffer);
		static bool serialize_join_request_message(RemoteGamerInfoMsg* info, void* data, int size, int* bits_serialized);

		static bool start_matchmaking_find_sessions(int profile_index, int available_slots, NetworkGameFilterMatchmakingComponent* filter, unsigned int max_sessions, rage::rlSessionInfo* results, int* num_sessions_found, rage::rlTaskStatus* status);

		static unsigned int broadcast_net_array(rage::netArrayHandlerBase* _this, CNetGamePlayer* target, rage::datBitBuffer* bit_buffer, uint16_t counter, uint32_t* elem_start, bool silent);

		static bool send_session_matchmaking_attributes(void* a1, rage::rlSessionInfo* info, uint64_t session_id, bool use_session_id, MatchmakingAttributes* attributes);

		static void serialize_take_off_ped_variation_task(ClonedTakeOffPedVariationInfo* info, rage::CSyncDataBase* serializer);

		static int nt_query_virtual_memory(void* _this, HANDLE handle, PVOID base_addr, int info_class, MEMORY_BASIC_INFORMATION* info, int size, size_t* return_len);
		static void queue_dependency(void* dependency);
		static bool prepare_metric_for_sending(rage::datBitBuffer* bit_buffer, int unk, int time, rage::rlMetric* metric);

		static bool received_array_update(rage::netArrayHandlerBase* array, CNetGamePlayer* sender, rage::datBitBuffer* buffer, int size, int16_t cycle);

		static bool receive_pickup(rage::netObject* netobject, void* unk, CPed* ped);

		static void write_player_camera_data_node(rage::netObject* player, CPlayerCameraDataNode* node);

		static rage::netGameEvent* send_player_card_stats(rage::netGameEvent* a1, CPlayerCardStats* stats);
		static void serialize_stats(CStatsSerializationContext* context, rage::joaat_t* stats, uint32_t stat_count);

		static void write_player_creation_data_node(rage::netObject* player, CPlayerCreationDataNode* node);
		static void write_player_appearance_data_node(rage::netObject* player, CPlayerAppearanceDataNode* node);

		static __int64 task_jump_constructor(uint64_t a1, int a2);

		static CBaseModelInfo* get_model_info(rage::joaat_t hash, uint32_t* a2);

		static int enumerate_audio_devices(CFoundDevice* found_devices, int count, int flags);
		static HRESULT direct_sound_capture_create(GUID* guid, IDirectSoundCapture** sound, void* unknown);

		static void write_vehicle_proximity_migration_data_node(rage::netObject* veh, CVehicleProximityMigrationDataNode* node);

		static int netfilter_handle_message(__int64 filter, char* message, int flags);

		static void log_error_message_box(rage::joaat_t joaated_error_code, bool a2);

		static bool send_non_physical_player_data(CNetGamePlayer* player, __int64 message, int flags, void* a4, CNetGamePlayer* a5);

		static void update_timecycle_keyframe_data(int64_t timecycleManager, TimecycleKeyframeData* timecycleKeyframeData);

		static void* allocate_memory_reliable(rage::netConnection* cxn, int required_memory);

		static void* render_ped(__int64 renderer, CPed* ped, __int64 a3, __int64 a4);
		static void render_entity(__int64 renderer, rage::fwEntity* entity, int unk, bool a4);
		static __int64 render_big_ped(__int64 renderer, CPed* ped, __int64 a3, __int64 a4);
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

		class detour_hook_helper
		{
			friend hooking;

			using ret_ptr_fn = std::function<void*()>;

			ret_ptr_fn m_on_hooking_available = nullptr;

			detour_hook* m_detour_hook;

			void enable_hook_if_hooking_is_already_running();

			template<auto detour_function>
			struct hook_to_detour_hook_helper
			{
				static inline detour_hook m_detour_hook;
			};

		public:
			template<auto detour_function>
			static void add(const std::string& name, void* target)
			{
				hook_to_detour_hook_helper<detour_function>::m_detour_hook.set_instance(name, target, detour_function);

				detour_hook_helper d{};
				d.m_detour_hook = &hook_to_detour_hook_helper<detour_function>::m_detour_hook;

				d.enable_hook_if_hooking_is_already_running();

				m_detour_hook_helpers.push_back(d);
			}

			template<auto detour_function>
			static void* add_lazy(const std::string& name, detour_hook_helper::ret_ptr_fn on_hooking_available)
			{
				hook_to_detour_hook_helper<detour_function>::m_detour_hook.set_instance(name, detour_function);

				detour_hook_helper d{};
				d.m_detour_hook          = &hook_to_detour_hook_helper<detour_function>::m_detour_hook;
				d.m_on_hooking_available = on_hooking_available;

				d.enable_hook_if_hooking_is_already_running();

				m_detour_hook_helpers.push_back(d);

				return nullptr;
			}

			~detour_hook_helper();
		};

		template<auto detour_function>
		static auto get_original()
		{
			return detour_hook_helper::hook_to_detour_hook_helper<detour_function>::m_detour_hook.get_original<decltype(detour_function)>();
		}

	private:
		bool m_enabled{};
		minhook_keepalive m_minhook_keepalive;

		vmt_hook m_swapchain_hook;

		WNDPROC m_og_wndproc = nullptr;

		static inline std::vector<detour_hook_helper> m_detour_hook_helpers;
	};

	inline hooking* g_hooking{};
}
