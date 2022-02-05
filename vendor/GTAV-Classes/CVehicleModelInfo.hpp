#pragma once

class CVehicleModelInfo
{
public:
	char pad_0000[1419]; //0x0000
	uint8_t m_custom_type; //0x058B
}; //Size: 0x058C
static_assert(sizeof(CVehicleModelInfo) == 0x58C);
