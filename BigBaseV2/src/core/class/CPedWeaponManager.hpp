#pragma once
#include "CWeaponInfo.hpp"

#pragma pack(push, 1)

class CPedWeaponManager
{
public:
	char pad_0000[32]; //0x0000
	class CWeaponInfo* m_weapon_info; //0x0020
	char pad_0028[72]; //0x0028
	class CWeaponInfo* m_vehicle_weapon_info; //0x0070
}; //Size: 0x0078
static_assert(sizeof(CPedWeaponManager) == 0x78);

#pragma pack(pop)