#pragma once
#include "fwddec.hpp"
#include "script/dataList.hpp"
#include "script/scriptIdBase.hpp"
#include "script/scriptResource.hpp"
#include "script/scriptHandler.hpp"
#include "script/scriptHandlerNetComponent.hpp"

#include <cstdint>

#pragma pack(push, 1)
namespace rage
{
	class scriptResourceEntry
	{
	public:
		scriptResource* m_data;     // 0x00
		uint32_t m_unk;             // 0x04
		char m_padding[0x0C];       // 0x0C
		scriptResourceEntry* m_next;// 0x18
	};

	class scriptHandlerMgr
	{
	public:
		virtual ~scriptHandlerMgr() = default;

		// Initializes some scripting-related pools.
		virtual bool initialize() = 0;// 1 (0x08)

		// Called every tick.
		virtual void _0x10() = 0;// 2 (0x10)

		// Frees some scripting-related pools.
		virtual void shutdown() = 0;// 3 (0x18)

		virtual void _0x20() = 0;// 4 (0x20)
		virtual void _0x28() = 0;// 5 (0x28)
		virtual void _0x30() = 0;// 6 (0x30)

		// Generates a rage::scriptId from the thread and copies it over to a global structure.
		virtual void _0x38(scrThread*) = 0;// 7 (0x38)

		// Allocates and constructs a script handler.
		virtual scriptHandler* create_script_handler() = 0;// 8 (0x40)

		// Finds the script handler for a given script id.
		virtual scriptHandler* get_script_handler(scriptId*) = 0;// 9 (0x48)

		// Attaches a script thread.
		virtual void attach_thread(scrThread*) = 0;// 10 (0x50)

		// Detaches a script thread.
		virtual void detach_thread(scrThread*) = 0;// 11 (0x58)

		// Called when a player joins.
		virtual void on_player_join(netPlayer*) = 0;// 12 (0x60)

		// Called when a player leaves.
		virtual void on_player_left(netPlayer*) = 0;// 13 (0x68)

		virtual std::int32_t _0x70() = 0;// 14 (0x70)
		virtual void* _0x78()        = 0;// 15 (0x78)
	public:
		char pad_0008[104];
	};
}

class CGameScriptHandler : public rage::scriptHandler
{
public:
	CGameScriptId m_script_id;// 0x60
};

class CGameScriptHandlerNetwork : public CGameScriptHandler
{
public:
	uint8_t m_0xA0;       // 0xA0
	uint8_t m_0xA1;       // 0xA1
	uint8_t m_0xA2;       // 0xA2
	uint8_t m_0xA3;       // 0xA3
	uint8_t m_num_players;// 0xA4
	uint8_t m_0xA5;       // 0xA5
	uint8_t m_0xA6;       // 0xA6
	uint8_t m_0xA7;       // 0xA7
	uint8_t m_0xA8;       // 0xA8
	uint8_t m_0xA9;       // 0xA9
	uint8_t m_0xAA;       // 0xAA
	uint8_t m_0xAB;       // 0xAB
	uint8_t m_0xAC;       // 0xAC
	uint8_t m_0xAD;       // 0xAD
	uint8_t m_0xAE;       // 0xAE
	uint8_t m_0xAF;       // 0xAF
};

#pragma pack(push, 8)
struct CScriptParticipant
{
	CScriptParticipant* m_next;
	CScriptParticipant* m_prev;
	CNetGamePlayer* m_net_game_player;
	uint16_t m_participant_id;
	uint16_t m_participant_index; // or "slot number"
	int m_join_time;
	char gap20[8];
};

class CGameScriptHandlerNetComponent
{
public:
	virtual ~CGameScriptHandlerNetComponent() = default;

	virtual bool _0x08(void*) = 0;

	virtual void _0x10(CNetGamePlayer*) = 0;// creates a scriptId?

	virtual void* player_left(CNetGamePlayer* player) = 0;

	virtual void* send_host_migration_event(CNetGamePlayer* player) = 0;

	virtual void player_joined(void**, void* msg_ctx) = 0;

	virtual void player_joined_ack(void**, void* msg_ctx) = 0;

	virtual void player_joined_host_ack(void*, void*) = 0;

	virtual void* _0x40(void*, void*) = 0;

	virtual void* _0x48(void*, void*, void*) = 0;

	virtual void* _0x50(void*, void*) = 0;

	virtual void* _0x58(void*, void*) = 0;

	virtual void* _0x60(void*, void*) = 0;

	virtual void* _0x68(void*, void*) = 0;

	virtual void _0x70(void*, void*) = 0;

	virtual void _0x78(void*, void*) = 0;

	virtual short _0x80(void*, void*) = 0;

	virtual void* _0x88(void*, void*) = 0;

	virtual void* _0x90(void*, void*) = 0;

	virtual bool _0x98(void*, void*) = 0;

	virtual void* _0xA0(void*, void*) = 0;

	virtual void* _0xA8(void*, void*) = 0;

	virtual short _0xB0(void*, void*) = 0;

	virtual bool register_host_broadcast_data(void* data, int size, char* a3) = 0;

	virtual bool register_player_broadcast_data(int a1, int size, bool a3) = 0;

	virtual bool _0xC8() = 0;

	virtual bool _0xD0() = 0;

	virtual bool add_player_to_script(CNetGamePlayer* player, short* out_participant_id, short* out_slot_number, int* out_fail_reason) = 0;

	virtual bool add_player_to_script_internal(CNetGamePlayer* player, short participant_id, short slot_number) = 0;

	virtual bool remove_player_from_script(CNetGamePlayer* player) = 0;

	virtual void* player_left_impl(CNetGamePlayer*, bool) = 0;

	virtual bool do_host_migration(CNetGamePlayer* player, short host_token, bool unk) = 0;

	virtual void* leave_from_script() = 0;

	virtual bool _0x108() = 0;

	virtual void* _0x110() = 0;

	virtual bool _0x118() = 0;// related to above function

	CGameScriptHandler* m_script_handler;
	int m_state;
	int m_join_msg_ack_pending_players;
	CScriptParticipant* m_first_participant;
	char gap20[16];
	CScriptParticipant* m_host;
	__int16 m_local_participant_index;
	char pad_003A[6];
	unsigned int m_participant_bitset;
	uint16_t m_host_token;
	CNetGamePlayer* m_last_host;
	CNetGamePlayer* m_host_migration_target;
	CNetGamePlayer* m_apparent_host_player;
	char gap60[8];
	CScriptParticipant* m_participants[32];
	char pad_0168[8];
	int m_next_host_verify_time;
	char m_max_participants;
	char pad_0175[23];
	uint8_t m_num_participants;
	uint8_t m_num_candidates;
	uint8_t m_host_ack_error;
	uint8_t m_host_array_count;
	uint8_t m_player_array_count;
	uint8_t m_host_migration_state;
	unsigned __int8 m_flags;
	char pad_0193[13];
	char m_script_status_queried;

	int get_participant_index(CNetGamePlayer* player);
	bool is_player_a_participant(CNetGamePlayer* player);

	inline bool is_local_player_host()
	{
		if (!m_host)
			return true;// or return false?

		return m_host->m_participant_index == m_local_participant_index;
	}

	inline CNetGamePlayer* get_host()
	{
		if (!m_host)
			return nullptr;

		return m_host->m_net_game_player;
	}
};//Size: 0x01B0
static_assert(sizeof(CGameScriptHandlerNetComponent) == 0x1A8);
#pragma pack(pop)

class CRemoteScriptInfo : public CGameScriptId
{
public:
	uint32_t m_participants;     //0x0040
	char pad_0044[4];            //0x0044
	class CNetGamePlayer* m_host;//0x0048
	uint32_t m_timestamp_2;      //0x0050
	uint16_t m_host_token;       //0x0054
	uint8_t m_reserved_peds;     //0x0056
	uint8_t m_reserved_vehicles; //0x0057
	uint8_t m_reserved_objects;  //0x0058
	uint8_t m_reserved_unk1;     //0x0059
	uint8_t m_reserved_unk2;     //0x005A
	uint8_t m_reserved_unk3;     //0x005B
	uint8_t m_reserved_unk4;     //0x005C
	char pad_005D[3];            //0x005D
};                               //Size: 0x0060
static_assert(sizeof(CRemoteScriptInfo) == 0x60);

class CGameScriptHandlerMgr : public rage::scriptHandlerMgr
{
public:
	char pad_0070[56];                                         //0x0070
	class CRemoteScriptInfo m_remote_script_infos[320];        //0x00A8
	char pad_78A8[4];                                          //0x78A8
	uint32_t m_remote_script_start_idx;                        //0x78AC
	uint32_t m_remote_script_count;                            //0x78B0
	char pad_78B4[4];                                          //0x78B4
	class CRemoteScriptInfo m_detached_remote_script_infos[64];//0x78B8
	char pad_90B8[4];                                          //0x90B8
	uint32_t m_detached_remote_script_start_idx;               //0x90BC
	uint32_t m_detached_remote_script_count;                   //0x90C0
	char pad_90C4[28];                                         //0x90C4
};                                                             //Size: 0x90E0
static_assert(sizeof(CGameScriptHandlerMgr) == 0x90E0);


static_assert(sizeof(rage::scriptHandler) == 0x60);
static_assert(sizeof(CGameScriptHandler) == 0xA0);
static_assert(sizeof(CGameScriptHandlerNetwork) == 0xB0);
#pragma pack(pop)
