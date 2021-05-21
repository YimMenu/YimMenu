#pragma once
#include "CHandlingData.hpp"
#include "CVehicleDrawHandler.hpp"

class CAutomobile
{
public:
	char pad_0000[72]; //0x0000
	class CVehicleDrawHandler* m_mods; //0x0048
	char pad_0050[313]; //0x0050
	uint8_t m_godmode; //0x0189
	char pad_018A[406]; //0x018A
	float m_boost; //0x0320
	float m_rocket_recharge_speed; //0x0324
	char pad_0328[1308]; //0x0328
	float m_health; //0x0844
	char pad_0848[192]; //0x0848
	float m_health2; //0x0908
	char pad_090C[44]; //0x090C
	class CHandlingData* m_handling; //0x0938
	char pad_0940[2]; //0x0940
	uint8_t m_bulletproof_tyres; //0x0942
	char pad_0943[685]; //0x0943
	class WheelArray* m_wheels; //0x0BF0
	char pad_0BF8[100]; //0x0BF8
	float m_gravity; //0x0C5C
}; //Size: 0x0C60
static_assert(sizeof(CAutomobile) == 0xC60);

class CWheel
{
public:
	char pad_0000[8]; //0x0000
	float m_camber; //0x0008
	float m_camber_inverted; //0x000C
	char pad_0010[552]; //0x0010
}; //Size: 0x0238
static_assert(sizeof(CWheel) == 0x238);

class WheelArray
{
public:
	class CWheel* m_wheel1; //0x0000
	class CWheel* m_wheel2; //0x0008
	class CWheel* m_wheel3; //0x0010
	class CWheel* m_wheel4; //0x0018
	char pad_0020[88]; //0x0020
}; //Size: 0x0078
static_assert(sizeof(WheelArray) == 0x78);