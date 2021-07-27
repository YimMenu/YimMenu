#pragma once
#include "CAutomobile.hpp"
#include "CPedModelInfo.hpp"
#include "CPedWeaponManager.hpp"
#include "CPlayerInfo.hpp"
#include "gta/vector.hpp"

#pragma pack(push, 1)

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
	char pad_0D38[912]; //0x0D38
	class CPlayerInfo* m_player_info; //0x10C8
	char pad_10D0[8]; //0x10D0
	class CPedWeaponManager* m_weapon_manager; //0x10D8
	char pad_10E0[919]; //0x10E0
	uint8_t m_in_vehicle; //0x1477
	char pad_1478[104]; //0x1478
	float m_armor; //0x14E0
}; //Size: 0x14E4
static_assert(sizeof(CPed) == 0x14E4);

#pragma pack(pop)