#pragma once
#include "CWeaponInfo.hpp"

#pragma pack(push, 1)

class CPedWeaponManager
{
public:
	char pad_0000[32]; //0x0000
	class CWeaponInfo* m_weapon_info; //0x0020
}; //Size: 0x0028
static_assert(sizeof(CPedWeaponManager) == 0x28);

#pragma pack(pop)