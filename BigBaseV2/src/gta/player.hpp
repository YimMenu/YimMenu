#pragma once
#include <cstdint>
#include "fwddec.hpp"
#include "extensible.hpp"
#include "vector.hpp"
#include "gta\natives.hpp"

#pragma pack(push, 1)
namespace rage
{
#	pragma warning(push)
#	pragma warning(disable : 4201) // nonstandard extension used: nameless struct/union
	union netAddress
	{
		std::uint32_t m_raw;
		struct
		{
			std::uint8_t m_field4;
			std::uint8_t m_field3;
			std::uint8_t m_field2;
			std::uint8_t m_field1;
		};
	};
#	pragma warning(pop)

	class netPlayerData
	{
	public:
		char pad_0000[16]; //0x0000
		uint32_t m_sec_key_time; //0x0010
		netAddress m_lan_ip; //0x0014
		uint16_t m_lan_port; //0x0018
		char pad_001A[2]; //0x001A
		netAddress m_relay_ip; //0x001C
		uint32_t m_relay_port; //0x0020
		netAddress m_online_ip; //0x0024
		uint16_t m_online_port; //0x0028
		char pad_002A[22]; //0x002A
		int32_t m_host_token; //0x0040
		char pad_0044[12]; //0x0044
		uint64_t m_rockstar_id; //0x0050
		char pad_0058[12]; //0x0058
		char m_name[20]; //0x0064
	}; //Size: 0x0078

	class nonPhysicalPlayerDataBase
	{
	public:
		virtual ~nonPhysicalPlayerDataBase() = default;    // 0 (0x00)
		virtual void unk_0x08() = 0;                       // 1 (0x08)
		virtual void unk_0x10() = 0;                       // 2 (0x10)
		virtual void unk_0x18() = 0;                       // 3 (0x18)
		virtual void log(netLoggingInterface* logger) = 0; // 4 (0x20)
	};

	class netPlayer
	{
	public:
		virtual ~netPlayer() = default;            // 0 (0x00)
		virtual void reset() = 0;                  // 1 (0x08)
		virtual bool is_valid() const = 0;         // 2 (0x10)
		virtual const char *get_name() const = 0;  // 3 (0x18)
		virtual void _0x20() = 0;                  // 4 (0x20)
		virtual bool is_host() = 0;                // 5 (0x28)
		virtual netPlayerData *get_net_data() = 0; // 6 (0x30)
		virtual void _0x38() = 0;                  // 7 (0x38)
	};

	class netPlayerMgrBase
	{
	public:
		virtual ~netPlayerMgrBase() = default; // 0 (0x00)
	};
}

namespace gta
{
	inline constexpr auto num_players = 32;
}

class CNonPhysicalPlayerData : public rage::nonPhysicalPlayerDataBase
{
public:
	std::int32_t  m_bubble_id; // 0x08
	std::int32_t  m_player_id; // 0x0C
	rage::vector3 m_position;  // 0x10
};

class CNetGamePlayer : public rage::netPlayer
{
public:
	char pad_0x0008[0x10]; //0x0008
	std::uint32_t msg_id; // 0x18
	char pad_0x001C[0x4]; //0x001C
	std::int8_t active_id; //0x0020 
	std::int8_t player_id; //0x0021 
	char pad_0x0022[0x6E]; //0x0022
	BYTE local_player_check;//0x0090
	char pad_0x00A1[0xF]; //0x0091
	CPlayerInfo* player_info; //0x00A0 

	inline bool is_local_player()
	{
		return local_player_check & 1;
	}
};
static_assert(sizeof(CNetGamePlayer) == 0xA8);

//class CPlayerInfo : public rage::fwExtensibleBase
//{
//public:
//	char pad_0020[20]; //0x0020
//	uint32_t m_internal_ip; //0x0034
//	uint16_t m_internal_port; //0x0038
//	char pad_003A[2]; //0x003A
//	uint32_t m_relay_ip; //0x003C
//	uint16_t m_relay_port; //0x0040
//	char pad_0042[2]; //0x0042
//	uint32_t m_external_ip; //0x0044
//	uint16_t m_external_port; //0x0048
//	char pad_004A[38]; //0x004A
//	uint64_t m_rockstar_id; //0x0070
//	char pad_0078[12]; //0x0078
//	char m_name[20]; //0x0084
//	char pad_0098[180]; //0x0098
//	float m_swim_speed; //0x014C
//	float m_run_speed; //0x0150
//	char pad_0154[81]; //0x0154
//	bool m_is_rockstar_dev; //0x01A5
//	char pad_01A6[1]; //0x01A6
//	bool m_is_cheater; //0x01A7
//	char pad_01A8[11]; //0x01A8
//	bool m_is_online; //0x01B3
//	char pad_01B4[20]; //0x01B4
//	class CPed* m_ped; //0x01C8
//	char pad_01D0[40]; //0x01D0
//	uint32_t m_frame_flags; //0x01F8
//	char pad_01FC[28]; //0x01FC
//	uint32_t m_player_controls; //0x0218
//	char pad_021C[1604]; //0x021C
//	bool m_is_wanted; //0x0860
//	char pad_0861[3]; //0x0861
//	int8_t m_wanted_level_display; //0x0864
//	char pad_0865[3]; //0x0865
//	int8_t m_wanted_level; //0x0868
//}; //Size: 0x0869
//static_assert(sizeof(CPlayerInfo) == 0x869);

static_assert(sizeof(CNonPhysicalPlayerData) == 0x1C);
#pragma pack(pop)
