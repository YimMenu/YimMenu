#pragma once
#include "vector.hpp"

class CNavigation
{
public:
	char pad_0000[32]; //0x0000
	float m_heading; //0x0020
	float m_heading2; //0x0024
	char pad_0028[8]; //0x0028
	rage::fvector3 m_rotation; //0x0030
	char pad_003C[20]; //0x003C
	rage::fvector3 m_position; //0x0054
}; //Size: 0x0060
static_assert(sizeof(CNavigation) == 0x5C);
