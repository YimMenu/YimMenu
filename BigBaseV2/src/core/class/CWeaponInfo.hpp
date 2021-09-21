#pragma once
#include "CAmmonInfo.hpp"

#pragma pack(push, 1)

class CWeaponInfo
{
public:
	char pad_0000[16]; //0x0000
	uint32_t m_name_hash; //0x0010
	uint32_t m_model_hash; //0x0014
	char pad_0018[12]; //0x0018
	uint32_t m_impact_explosion; //0x0024
	char pad_0028[56]; //0x0028
	class CAmmoInfo* m_ammo_info; //0x0060
	char pad_0068[20]; //0x0068
	float m_spread; //0x007C
	char pad_0080[60]; //0x0080
	float m_bullet_dmg; //0x00BC
	char pad_00C0[28]; //0x00C0
	float m_force_on_ped; //0x00DC
	float m_force_on_vehicle; //0x00E0
	float m_force_on_heli; //0x00E4
	char pad_00E8[40]; //0x00E8
	float m_penetration; //0x0110
	char pad_0114[8]; //0x0114
	float m_muzzle_velocity; //0x011C
	char pad_0120[16]; //0x0120
	float m_vehicle_reload_mult; //0x0130
	float m_reload_mult; //0x0134
	char pad_0138[12]; //0x0138
	float m_spinup; //0x0144
	float m_spin; //0x0148
	char pad_014C[316]; //0x014C
	float m_lock_on_range; //0x0288
	float m_weapon_range; //0x028C
	char pad_0290[100]; //0x0290
	float m_accuracy_recoil; //0x02F4
}; //Size: 0x02F8
static_assert(sizeof(CWeaponInfo) == 0x2F8);

#pragma pack(pop)