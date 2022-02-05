#pragma once
#include "CBaseModelInfo.hpp"
#include "CNavigation.hpp"
#include "fwDrawData.hpp"
#include "netObject.hpp"

namespace rage
{
#pragma pack(push, 4)
    class fwEntity
    {
    public:
        char pad_0000[32]; //0x0000
        class CBaseModelInfo *m_model_info; //0x0020
        char pad_0028[1]; //0x0028
        int8_t m_entity_type; //0x0029
        char pad_002A[2]; //0x002A
        uint8_t m_invisible; //0x002C
        char pad_002D[3]; //0x002D
        class CNavigation *m_navigation; //0x0030
        char pad_0038[16]; //0x0038
        class rage::fwDrawData *m_draw_data; //0x0048
        char pad_0050[128]; //0x0050
        class rage::netObject *m_net_object; //0x00D0
        char pad_00D8[176]; //0x00D8
        uint32_t m_damage_bits; //0x0188
    }; //Size: 0x018C
    static_assert(sizeof(fwEntity) == 0x18C);
#pragma pack(pop)
}
