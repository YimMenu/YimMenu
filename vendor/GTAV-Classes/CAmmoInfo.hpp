#pragma once
#include "CItemInfo.hpp"

enum class eAmmoSpecialType : int32_t
{
	None,
	ArmorPiercing,
	Explosive,
	FMJ,
	HollowPoint,
	Incendiary,
	Tracer
};

class CAmmoInfo : public CItemInfo
{
public:
	int32_t m_ammo_max; //0x0020
	int32_t m_ammo_max_50; //0x0024
	int32_t m_ammo_max_100; //0x0028
	int32_t m_ammo_max_mp; //0x002C
	int32_t m_ammo_max_50_mp; //0x0030
	int32_t m_ammo_max_100_mp; //0x0034
	uint32_t m_ammo_flags; //0x0038
	eAmmoSpecialType m_ammo_special_type; //0x003C
	char pad_0040[24]; //0x0040
	float m_missile_speed; //0x0058
	char pad_005C[284]; //0x005C
	uint32_t m_lock_on_time; //0x0178
}; //Size: 0x017C
static_assert(sizeof(CAmmoInfo) == 0x17C);
