#pragma once
#include "CHandlingData.hpp"
#include "CVehicleDrawHandler.hpp"
#include "CVehicleModelInfo.hpp"
#include "fwEntity.hpp"

#pragma pack(push, 4)
class CAutomobile : public rage::fwEntity
{
public:
	char pad_018C[244]; //0x018C
	float m_health; //0x0280
	char pad_0284[28]; //0x0284
	float m_health_max; //0x02A0
	char pad_02A4[116]; //0x02A4
	uint8_t m_boost_state; //0x0318
	char pad_0319[2]; //0x0319
	uint8_t m_boost_allow_recharge; //0x031B
	char pad_031C[4]; //0x031C
	float m_boost; //0x0320
	float m_rocket_recharge_speed; //0x0324
	char pad_0328[136]; //0x0328
	float m_jump_boost_charge; //0x03B0
	char pad_03B4[1164]; //0x03B4
	float m_body_health; //0x0840
	float m_petrol_tank_health; //0x0844
	char pad_0848[192]; //0x0848
	float m_engine_health; //0x0908
	char pad_090C[44]; //0x090C
	class CHandlingData *m_handling; //0x0938
	char pad_0940[2]; //0x0940
	uint8_t m_is_drivable; //0x0942
	uint8_t m_tyres_can_burst; //0x0943
	uint8_t m_deform_god; //0x0944
	char pad_0945[179]; //0x0945
	float m_dirt_level; //0x09F8
	char pad_09FC[194]; //0x09FC
	uint8_t m_is_targetable; //0x0ABE
	char pad_0ABF[413]; //0x0ABF
	float m_gravity; //0x0C5C
	char pad_0C60[8]; //0x0C60
	class CPed *m_driver; //0x0C68
	class CPed *m_passengers[15]; //0x0C70
	class CPed *m_last_driver; //0x0CE8
}; //Size: 0x0CF0
static_assert(sizeof(CAutomobile) == 0xCF0);
#pragma pack(pop)
