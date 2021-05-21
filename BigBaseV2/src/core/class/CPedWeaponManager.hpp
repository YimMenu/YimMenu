#pragma once

class CPedWeaponManager
{
public:
	char pad_0000[32]; //0x0000
	class CWeaponInfo* m_weapon_info; //0x0020
}; //Size: 0x0028
static_assert(sizeof(CPedWeaponManager) == 0x28);

class CWeaponInfo
{
public:
	char pad_0000[16]; //0x0000
	uint32_t m_model_hash; //0x0010
}; //Size: 0x0014
static_assert(sizeof(CWeaponInfo) == 0x14);