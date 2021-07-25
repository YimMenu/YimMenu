#pragma once
#include "CHandlingData.hpp"
#include "CVehicleDrawHandler.hpp"

#pragma pack(push, 1)
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
	uint8_t m_bullet_proof_tyres; //0x0942
	char pad_0943[793]; //0x0943
	float m_gravity; //0x0C5C
}; //Size: 0x0C60
static_assert(sizeof(CAutomobile) == 0xC60);
#pragma pack(pop)