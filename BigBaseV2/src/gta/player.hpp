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
		std::uint64_t m_unk1;         // 0x00
		std::uint64_t m_unk2;         // 0x08
		std::uint32_t m_sec_key_time; // 0x10
		netAddress    m_lan_ip;       // 0x14
		std::uint16_t m_lan_port;     // 0x18
		char          m_pad1[0x02];   // 0x1A
		netAddress    m_relay_ip;     // 0x1C
		std::uint16_t m_relay_port;   // 0x20
		char          m_pad2[0x02];   // 0x22
		netAddress    m_online_ip;    // 0x24
		std::uint16_t m_online_port;  // 0x26
		char          m_pad3[0x1E];   // 0x28
		std::uint64_t m_rockstar_id;  // 0x48
		bool          m_id_flag;      // 0x50
		char          m_pad4[0x0B];   // 0x51
		char          m_name[0x14];   // 0x5C
	};

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
	char pad_0x0008[0x25]; //0x0008
	std::int8_t player_id; //0x002D 
	char pad_0x002E[0x7A]; //0x002E
	CPlayerInfo* player_info; //0x00A8 
	char pad_0x00B0[0x14]; //0x00B0
	std::uint32_t bubble_id; //0x00C4	
	Player player; //0x00C8
};

class CPlayerInfo : public rage::fwExtensibleBase
{
public:
	char pad_0020[20]; //0x0020
	std::uint32_t m_internal_ip; //0x0034
	std::uint16_t m_internal_port; //0x0038
	char pad_003A[2]; //0x003A
	std::uint32_t m_relay_ip; //0x003C
	std::uint16_t m_relay_port; //0x0040
	char pad_0042[2]; //0x0042
	std::uint32_t m_external_ip; //0x0044
	std::uint16_t m_external_port; //0x0048
	char pad_004A[30]; //0x004A
	std::uint64_t m_rockstar_id; //0x0068
	char pad_0070[12]; //0x0070
	char m_name[20]; //0x007C
	char pad_0090[184]; //0x0090
	float m_swim_speed; //0x0148
	float m_run_speed; //0x014C
	char pad_0150[81]; //0x0150
	bool m_is_rockstar_dev; //0x01A1
	char pad_01A2[1]; //0x01A2
	bool m_is_cheater; //0x01A3
	char pad_01A4[11]; //0x01A4
	bool m_is_online; //0x01AF
	char pad_01B0[24]; //0x01B0
	rage::CPed* m_ped; //0x01C8
	char pad_01D0[40]; //0x01D0
	std::uint32_t m_frame_flags; //0x01F8
	char pad_01FC[28]; //0x01FC
	std::uint32_t m_player_controls; //0x0218
	char pad_021C[1524]; //0x021C
	bool m_is_wanted; //0x0810
	char pad_0811[51]; //0x0811
	std::int32_t m_wanted_level_display; //0x0844
	std::int32_t m_wanted_level; //0x0848
}; //Size: 0x084C

static_assert(sizeof(CNonPhysicalPlayerData) == 0x1C);
#pragma pack(pop)
