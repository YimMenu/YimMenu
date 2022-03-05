#pragma once

class CItemInfo
{
public:
	char pad_0000[16]; //0x0000
	uint32_t m_name; //0x0010
	uint32_t m_model; //0x0014
	uint32_t m_audio; //0x0018
	uint32_t m_slot; //0x001C
}; //Size: 0x0020
static_assert(sizeof(CItemInfo) == 0x20);
