#pragma once

enum class eModelType : std::uint8_t
{
    UNK_0,
    UNK_1,
    UNK_2,
    UNK_3,
    UNK_4,
    Vehicle,
    Ped,
};

#pragma pack(push, 2)
class CBaseModelInfo
{
public:
	char pad_0000[24]; //0x0000
	uint32_t m_model_hash; //0x0018
	char pad_001C[129]; //0x001C
	eModelType m_model_type; //0x009D
	char pad_009E[6]; //0x009E
}; //Size: 0x00A4
static_assert(sizeof(CBaseModelInfo) == 0xA4);
#pragma pack(pop)
