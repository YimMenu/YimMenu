#pragma once

#pragma pack(push, 1)

class CAmmoInfo
{
public:
	char pad_0000[12]; //0x0000
	uint32_t m_projectile_type; //0x000C
	uint32_t m_ammo_name_hash; //0x0010
	uint32_t m_ammo_model_hash; //0x0014
	char pad_0018[16]; //0x0018
	uint32_t m_max_ammo; //0x0028
	char pad_002C[44]; //0x002C
	float m_missile_speed; //0x0058
	char pad_005C[284]; //0x005C
	uint32_t m_lock_on_time; //0x0178
}; //Size: 0x017C
static_assert(sizeof(CAmmoInfo) == 0x17C);

#pragma pack(pop)