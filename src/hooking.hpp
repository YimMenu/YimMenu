#pragma once
#include "MinHook.h"
#include "common.hpp"
#include "detour_hook.hpp"
#include "gta/enums.hpp"
#include "gta/fwddec.hpp"
#include "gta/script_thread.hpp"
#include "vmt_hook.hpp"

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

	namespace netConnection
	{
		class InFrame;
	}
}

namespace big
{
	struct hooks
	{
		static bool run_script_threads(std::uint32_t ops_to_execute);

		static constexpr auto swapchain_num_funcs           = 19;
		static constexpr auto swapchain_present_index       = 8;
		static constexpr auto swapchain_resizebuffers_index = 13;
		static HRESULT swapchain_present(IDXGISwapChain* this_, UINT sync_interval, UINT flags);
		static HRESULT swapchain_resizebuffers(IDXGISwapChain* this_, UINT buffer_count, UINT width, UINT height, DXGI_FORMAT new_format, UINT swapchain_flags);

		static LRESULT wndproc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

		static const char* get_label_text(void* unk, const char* label);
		static int check_chat_profanity(__int64 chat_type, const char* input, const char** output);

		static GtaThread* gta_thread_start(unsigned int** a1, unsigned int a2);
		static rage::eThreadState gta_thread_kill(GtaThread* thread);
		static bool init_native_tables(rage::scrProgram* program);
		static rage::eThreadState script_vm(uint64_t* start_stack, uint64_t** scr_globals, rage::scrProgram* program, rage::scrThreadContext* ctx);

		static void network_player_mgr_init(CNetworkPlayerMgr* _this, std::uint64_t a2, std::uint32_t a3, std::uint32_t a4[4]);
		static void network_player_mgr_shutdown(CNetworkPlayerMgr* _this);

		static bool fragment_physics_crash(uintptr_t a1, uint32_t a2, uintptr_t a3, uintptr_t a4, uintptr_t a5);
		static bool fragment_physics_crash_2(float* a1, float* a2);

		static void received_event(rage::netEventMgr* event_manager, CNetGamePlayer* source_player, CNetGamePlayer* target_player, uint16_t event_id, int event_index, int event_handled_bitset, int unk, rage::datBitBuffer* bit_buffer);

		// these two aren't actually hooks, just helper functions for hooks
		static bool increment_stat_event(CNetworkIncrementStatEvent* net_event_struct, CNetGamePlayer* sender);
		static bool scripted_game_event(CScriptedGameEvent* scripted_game_event, CNetGamePlayer* player);

		static bool receive_net_message(void* netConnectionManager, void* a2, rage::netConnection::InFrame* frame);
		static void get_network_event_data(int64_t unk, rage::CEventNetwork* net_event);

		static void* assign_physical_index(CNetworkPlayerMgr* netPlayerMgr, CNetGamePlayer* player, uint8_t new_index);

		//SYNC
		static bool received_clone_create(CNetworkObjectMgr* mgr, CNetGamePlayer* src, CNetGamePlayer* dst, eNetObjType object_type, int32_t object_id, int32_t object_flag, rage::datBitBuffer* buffer, int32_t timestamp);
		static eAckCode received_clone_sync(CNetworkObjectMgr* mgr, CNetGamePlayer* src, CNetGamePlayer* dst, eNetObjType object_type, uint16_t object_id, rage::datBitBuffer* bufer, uint16_t unk, uint32_t timestamp);
		static bool can_apply_data(rage::netSyncTree* tree, rage::netObject* object);

		static void write_player_gamer_data_node(rage::netObject* player, CPlayerGamerDataNode* node);
		static bool write_player_game_state_data_node(rage::netObject* player, CPlayerGameStateDataNode* node);

		static void invalid_mods_crash_detour(int64_t a1, int64_t a2, int a3, char a4);
		static std::int64_t constraint_attachment_crash(std::uintptr_t a1);
		static uint64_t invalid_decal(uintptr_t a1, int a2);
		static uint64_t task_parachute_object_0x270(uint64_t _this, int a2, int a3);

		static bool update_presence_attribute_int(void* presence_data, int profile_index, char* attr, std::uint64_t value);
		static bool update_presence_attribute_string(void* presence_data, int profile_index, char* attr, char* value);

		static void serialize_ped_inventory_data_node(CPedInventoryDataNode* node, rage::CSyncDataBase* data);
		static void serialize_vehicle_gadget_data_node(CVehicleGadgetDataNode* node, rage::CSyncDataBase* data);

		static bool handle_join_request(Network* network, rage::snSession* session, rage::rlGamerInfo* player_info, CJoinRequestContext* ctx, BOOL is_transition_session);

		static bool sort_session_details(SessionSortEntry* e1, SessionSortEntry* e2);

		static bool add_player_to_session(rage::netConnectionManager* mgr, int receiver_msg_id, int* out_command_hndl, RemoteGamerInfoMsg* msg, int flags, void* unk);
		static bool send_chat_net_message(rage::netConnectionManager* mgr, int receiver_msg_id, CMsgTextMessage* msg, int flags, void* unk);
		static bool send_chat_message(void* team_mgr, rage::rlGamerInfo* local_gamer_info, char* message, bool is_team);

		static bool process_matchmaking_find_response(void* _this, void* unused, rage::JSONNode* node, int* unk);

		static bool serialize_player_data_msg(CNetGamePlayerDataMsg* msg, rage::datBitBuffer* buffer);
		static bool serialize_join_request_message(RemoteGamerInfoMsg* info, void* data, int size, int* bits_serialized);

		static bool start_matchmaking_find_sessions(int profile_index, int available_slots, NetworkGameFilterMatchmakingComponent* filter, unsigned int max_sessions, rage::rlSessionInfo* results, int* num_sessions_found, rage::rlTaskStatus* status);

		static unsigned int broadcast_net_array(rage::netArrayHandlerBase* _this, CNetGamePlayer* target, rage::datBitBuffer* bit_buffer, uint16_t counter, uint32_t* elem_start, bool silent);

		static bool send_session_matchmaking_attributes(void* a1, rage::rlSessionInfo* info, std::uint64_t session_id, bool use_session_id, MatchmakingAttributes* attributes);

		static void serialize_take_off_ped_variation_task(ClonedTakeOffPedVariationInfo* info, rage::CSyncDataBase* serializer);

		static CGameScriptHandler* create_script_handler(CGameScriptHandlerMgr* this_, void* unk);
		static bool script_handler_is_networked(CGameScriptHandler* this_);
		static bool script_handler_dtor(CGameScriptHandler* this_, bool free_memory);
		static void set_script_as_networked(void*, rage::scrThread* thread, int instance_id);

		static bool write_bitbuffer_gamer_handle(rage::datBitBuffer* buffer, rage::rlGamerHandle* handle);
		static bool read_bitbuffer_gamer_handle(rage::datBitBuffer* buffer, rage::rlGamerHandle* handle);

		static int nt_query_virtual_memory(void* _this, HANDLE handle, PVOID base_addr, int info_class, MEMORY_BASIC_INFORMATION* info, int size, size_t* return_len);
		static void queue_dependency(void* dependency);
		static void prepare_metric_for_sending(rage::datBitBuffer* bit_buffer, int unk, int time, rage::rlMetric* metric);

		static void* infinite_train_crash(void* carriage);

		static bool received_array_update(rage::netArrayHandlerBase* array, CNetGamePlayer* sender, rage::datBitBuffer* buffer, int size, std::int16_t cycle);

		static bool receive_pickup(rage::netObject* netobject, void* unk, CPed* ped);

		static bool write_player_camera_data_node(rage::netObject* player, CPlayerCameraDataNode* node);

		static rage::netGameEvent* send_player_card_stats(rage::netGameEvent* a1, CPlayerCardStats* stats);
		static void serialize_stats(CStatsSerializationContext* context, rage::joaat_t* stats, std::uint32_t stat_count);

		static void write_player_creation_data_node(rage::netObject* player, CPlayerCreationDataNode* node);
		static void write_player_appearance_data_node(rage::netObject* player, CPlayerAppearanceDataNode* node);

		static CBaseModelInfo* get_model_info(rage::joaat_t hash, uint32_t* a2);

		static int enumerate_audio_devices(CFoundDevice* found_devices, int count, int flags);
		static HRESULT direct_sound_capture_create(GUID* guid, IDirectSoundCapture** sound, void* unknown);

		static void write_vehicle_proximity_migration_data_node(rage::netObject* veh, CVehicleProximityMigrationDataNode* node);
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

			detour_hook* m_detour_hook = nullptr;

			~detour_hook_helper();

			void enable_hook_if_hooking_is_already_running();

			template<auto detour_function>
			struct hook_to_detour_hook_helper
			{
				static inline detour_hook* m_detour_hook;
			};

			template<auto detour_function>
			static detour_hook_helper* add_internal(detour_hook* dh)
			{
				auto d           = new detour_hook_helper();
				d->m_detour_hook = dh;

				m_detour_hook_helpers.push_back(d);
				hook_to_detour_hook_helper<detour_function>::m_detour_hook = dh;

				return d;
			}

		public:
			template<auto detour_function>
			static void add(const std::string& name, void* target)
			{
				auto d = add_internal<detour_function>(new detour_hook(name, target, detour_function));

				d->enable_hook_if_hooking_is_already_running();
			}

			template<auto detour_function>
			static void* add_lazy(const std::string& name, detour_hook_helper::ret_ptr_fn on_hooking_available)
			{
				auto d                    = add_internal<detour_function>(new detour_hook(name, detour_function));
				d->m_on_hooking_available = on_hooking_available;

				d->enable_hook_if_hooking_is_already_running();

				return nullptr;
			}
		};

		template<auto detour_function>
		static auto get_original()
		{
			return detour_hook_helper::hook_to_detour_hook_helper<detour_function>::m_detour_hook->get_original<decltype(detour_function)>();
		}

		void hook_script_handler(CGameScriptHandler* handler);
		std::unordered_map<CGameScriptHandler*, std::unique_ptr<vmt_hook>> m_handler_hooks;

	private:
		bool m_enabled{};
		minhook_keepalive m_minhook_keepalive;

		vmt_hook m_swapchain_hook;

		WNDPROC m_og_wndproc = nullptr;

		static inline std::vector<detour_hook_helper*> m_detour_hook_helpers;
	};

	inline hooking* g_hooking{};
}
