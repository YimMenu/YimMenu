#pragma once
#include <cstdint>
#include "fwddec.hpp"
#include "extensible.hpp"
#include "vector.hpp"

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

};

class CWantedData
{
public:
	char m_padding[0x98];
	std::int32_t m_wanted_level;
};

class CPlayerInfo : public rage::fwExtensibleBase
{
public:
	char m_padding1[0x1D8];      // 0x20
	std::uint32_t m_frame_flags; // 0x1F8
	char m_padding2[0x584];      // 0x1FC
	CWantedData m_wanted_data;   // 0x780
};

static_assert(sizeof(CNonPhysicalPlayerData) == 0x1C);
#pragma pack(pop)
