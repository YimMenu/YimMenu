#pragma once

#pragma pack(push, 1)

class CWeaponInfo
{
public:
	char pad_0000[16]; //0x0000
	uint32_t m_model_hash; //0x0010
}; //Size: 0x0014
static_assert(sizeof(CWeaponInfo) == 0x14);

#pragma pack(pop)