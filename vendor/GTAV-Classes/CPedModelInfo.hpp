#pragma once

class CPedModelInfo
{
public:
	char pad_0000[24]; //0x0000
	uint32_t m_model_hash; //0x0018
}; //Size: 0x001C
static_assert(sizeof(CPedModelInfo) == 0x1C);
