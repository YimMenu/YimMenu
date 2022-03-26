#pragma once
#include "CAutomobile.hpp"
#include "CPedModelInfo.hpp"
#include "CPedWeaponManager.hpp"
#include "CPlayerInfo.hpp"
#include "fwEntity.hpp"
#include "vector.hpp"

#pragma pack(push, 1)

class CPed : public rage::fwEntity
{
public:
	uint8_t m_hostility; //0x018C
	char pad_018D[243]; //0x018D
	float m_health; //0x0280
	char pad_0284[28]; //0x0284
	float m_maxhealth; //0x02A0
	char pad_02A4[124]; //0x02A4
	rage::fvector3 m_velocity; //0x0320
	char pad_032C[2564]; //0x032C
	class CAutomobile *m_vehicle; //0x0D30
	char pad_0D38[912]; //0x0D38
	class CPlayerInfo *m_player_info; //0x10C8
	char pad_10D0[8]; //0x10D0
	class CPedWeaponManager *m_weapon_manager; //0x10D8
	char pad_10E0[907]; //0x10E0
	uint8_t m_ped_task_flag; //0x146B
	char pad_146C[196]; //0x146C
	float m_armor; //0x1530
}; //Size: 0x1534
static_assert(sizeof(CPed) == 0x1534);

#pragma pack(pop)
