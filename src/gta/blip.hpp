#pragma once

#include "natives.hpp"

namespace rage
{
#pragma pack(push, 1)
	class Blip_t
	{
	public:
		int32_t m_id; //0x0000
		uint16_t m_blip_array_index; //0x0004
		char pad_0006[4]; //0x0006
		bool m_active; //0x000A
		uint8_t N00000197; //0x000B
		int32_t m_entity_id; //0x000C
		float m_x; //0x0010
		float m_y; //0x0014
		float m_z; //0x0018
		char pad_001C[4]; //0x001C
		uint32_t m_display_bits; //0x0020
		uint32_t m_render_bits; //0x0024
		char *m_message; //0x0028
		char pad_0030[8]; //0x0030
		Hash m_description; //0x0038
		char pad_003C[4]; //0x003C
		int32_t m_icon; //0x0040
		int16_t m_flash_interval; //0x0044
		int16_t m_flash_timer; //0x0046
		uint32_t m_color; //0x0048
		uint32_t m_secondary_color; //0x004C
		float m_scale_x; //0x0050
		float m_scale_y; //0x0054
		float m_rotation; //0x0058
		uint8_t m_mission_bits; //0x005C
		uint8_t m_priority; //0x005D
		uint8_t m_display_id; //0x005E
		uint8_t m_alpha; //0x005F
		int8_t m_category; //0x0060
		int8_t m_show_number; //0x0061
		char pad_0062[14]; //0x0062
	}; //Size: 0x0070
	static_assert(sizeof(Blip_t) == 0x70, "Blip_t is not sized properly.");
#pragma pack(pop)

	class BlipEntry
	{
	public:
		Blip_t* m_pBlip; //0x0000 

	};//Size=0x0008

	class BlipList
	{
	public:
		BlipEntry m_Blips[1500]; //0x0000 
		char _0x2EE0[56];

	};//Size=0x2F18
}