#pragma once
#include "CPlayerInfo.hpp"
#include "CNonPhysicalPlayerData.hpp"
#include "netPlayer.hpp"

#pragma pack(push, 1)

class CNetGamePlayer : public rage::netPlayer
{
public:
    char pad_0008[8]; //0x0008
    class CNonPhysicalPlayerData *m_non_physical_player; //0x0010
    uint32_t m_msg_id; //0x0018
    char pad_001C[4]; //0x001C
    uint8_t m_active_id; //0x0020
    uint8_t m_player_id; //0x0021
    char pad_0022[3]; //0x0022
    uint16_t m_complaints; //0x0025
    char pad_0027[17]; //0x0027
    class CNetGamePlayer *m_unk_net_player_list[10]; //0x0038
    char pad_0088[24]; //0x0088
    class CPlayerInfo *m_player_info; //0x00A0
}; //Size: 0x00A8
static_assert(sizeof(CNetGamePlayer) == 0xA8);

#pragma pack(pop)
