#pragma once
#include "fwddec.hpp"

#pragma pack(push, 1)
// Created with ReClass.NET 1.2 by KN4CK3R

class CPedFactory
{
public:
	char pad_0000[8]; //0x0000
	class CPed* m_local_ped; //0x0008
}; //Size: 0x0010
static_assert(sizeof(CPedFactory) == 0x10);

class CPed
{
public:
	char pad_0000[32]; //0x0000
	class CPedModelInfo* m_ped_model_info; //0x0020
	uint8_t m_entity_type; //0x0028
	char pad_0029[3]; //0x0029
	uint8_t m_invisible; //0x002C
	char pad_002D[1]; //0x002D
	uint8_t m_freeze_momentum; //0x002E
	char pad_002F[97]; //0x002F
	rage::vector3 m_position; //0x0090
	char pad_009C[237]; //0x009C
	uint8_t m_godmode; //0x0189
	char pad_018A[246]; //0x018A
	float m_health; //0x0280
	char pad_0284[28]; //0x0284
	float m_maxhealth; //0x02A0
	char pad_02A4[124]; //0x02A4
	rage::vector3 m_velocity; //0x0320
	char pad_032C[2564]; //0x032C
	class CAutomobile* m_vehicle; //0x0D30
	char pad_0D38[896]; //0x0D38
	uint8_t m_ragdoll; //0x10B8
	char pad_10B9[15]; //0x10B9
	class CPlayerInfo* m_player_info; //0x10C8
	char pad_10D0[8]; //0x10D0
	class CPedWeaponManager* m_weapon_manager; //0x10D8
	char pad_10E0[919]; //0x10E0
	uint8_t m_in_vehicle; //0x1477
	char pad_1478[104]; //0x1478
	float m_armor; //0x14E0
}; //Size: 0x14E4
static_assert(sizeof(CPed) == 0x14E4);

class CAutomobile
{
public:
	char pad_0000[393]; //0x0000
	uint8_t m_godmode; //0x0189
	char pad_018A[1722]; //0x018A
	float m_health; //0x0844
	char pad_0848[188]; //0x0848
	float m_health2; //0x0904
	char pad_0908[48]; //0x0908
	class CHandlingData* m_handling; //0x0938
	char pad_0940[796]; //0x0940
	float m_gravity; //0x0C5C
}; //Size: 0x0C60
static_assert(sizeof(CAutomobile) == 0xC60);

class CPlayerInfo
{
public:
	char pad_0000[52]; //0x0000
	uint32_t m_internal_ip; //0x0034
	uint16_t m_internal_port; //0x0038
	char pad_003A[2]; //0x003A
	uint32_t m_relay_ip; //0x003C
	uint16_t m_relay_port; //0x0040
	char pad_0042[2]; //0x0042
	uint32_t m_external_ip; //0x0044
	uint16_t m_external_port; //0x0048
	char pad_004A[38]; //0x004A
	uint64_t m_rockstar_id; //0x0070
	char pad_0078[12]; //0x0078
	char m_name[20]; //0x0084
	char pad_0098[180]; //0x0098
	float m_swim_speed; //0x014C
	float m_run_speed; //0x0150
	char pad_0154[81]; //0x0154
	bool m_is_rockstar_dev; //0x01A5
	char pad_01A6[1]; //0x01A6
	bool m_is_cheater; //0x01A7
	char pad_01A8[11]; //0x01A8
	bool m_is_online; //0x01B3
	char pad_01B4[20]; //0x01B4
	class CPed* m_ped; //0x01C8
	char pad_01D0[40]; //0x01D0
	uint32_t m_frame_flags; //0x01F8
	char pad_01FC[28]; //0x01FC
	uint32_t m_player_controls; //0x0218
	char pad_021C[1588]; //0x021C
	uint32_t m_npc_ignore; //0x0850
	char pad_0854[12]; //0x0854
	bool m_is_wanted; //0x0860
	char pad_0861[3]; //0x0861
	int8_t m_wanted_level_display; //0x0864
	char pad_0865[3]; //0x0865
	int8_t m_wanted_level; //0x0868
	char pad_0869[1131]; //0x0869
	float m_stamina; //0x0CD4
	float m_max_stamina; //0x0CD8
}; //Size: 0x0CDC
static_assert(sizeof(CPlayerInfo) == 0xCDC);

class CPedWeaponManager
{
public:
	char pad_0000[32]; //0x0000
	class CWeaponInfo* m_weapon_info; //0x0020
	char pad_0028[152]; //0x0028
}; //Size: 0x00C0
static_assert(sizeof(CPedWeaponManager) == 0xC0);

class CHandlingData
{
public:
	char pad_0000[12]; //0x0000
	float m_mass; //0x000C
	char pad_0010[16]; //0x0010
	rage::vector3 m_centre_of_mass; //0x0020
	float m_drive_bias_front; //0x002C
	rage::vector3 m_inertia_multiplier; //0x0030
	float m_drive_inertia; //0x003C
	float m_buoyancy; //0x0040
	char pad_0044[8]; //0x0044
	float m_acceleration; //0x004C
	char pad_0050[8]; //0x0050
	float m_upshift; //0x0058
	float m_downshift; //0x005C
	float m_initial_drive_force; //0x0060
	char pad_0064[8]; //0x0064
	float m_brakeforce; //0x006C
	char pad_0070[24]; //0x0070
	float m_traction_curve_max; //0x0088
	char pad_008C[4]; //0x008C
	float m_traction_curve_min; //0x0090
	char pad_0094[36]; //0x0094
	float m_traction_loss_mult; //0x00B8
	float m_suspension_force; //0x00BC
	float m_suspension_comp_damp; //0x00C0
	float m_suspension_rebound_damp; //0x00C4
	float m_suspension_upper_limit; //0x00C8
	float m_suspension_lower_limit; //0x00CC
	float m_camber_stiffness; //0x00D0
	char pad_00D4[8]; //0x00D4
	float m_anti_rollbar_force; //0x00DC
	char pad_00E0[8]; //0x00E0
	float m_roll_centre_height_front; //0x00E8
	float m_roll_centre_height_rear; //0x00EC
	float m_collision_damage_mult; //0x00F0
	float m_weapon_damamge_mult; //0x00F4
	float m_deformation_mult; //0x00F8
	float m_engine_damage_mult; //0x00FC
	float m_petrol_tank_volume; //0x0100
	float m_oil_volume; //0x0104
}; //Size: 0x0108
static_assert(sizeof(CHandlingData) == 0x108);

class CWeaponInfo
{
public:
	char pad_0000[376]; //0x0000
}; //Size: 0x0178
static_assert(sizeof(CWeaponInfo) == 0x178);

class CPedModelInfo
{
public:
	char pad_0000[136]; //0x0000
}; //Size: 0x0088
static_assert(sizeof(CPedModelInfo) == 0x88);
#pragma pack(pop)