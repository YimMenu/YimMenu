#pragma once

namespace rage
{
    class netAddress
    {
    public:
        uint8_t m_field4; //0x0000
        uint8_t m_field3; //0x0001
        uint8_t m_field2; //0x0002
        uint8_t m_field1; //0x0003
    }; //Size: 0x0004
    static_assert(sizeof(netAddress) == 0x4);

    class netPlayerData
    {
    public:
        char pad_0000[8]; //0x0000
        uint64_t m_rockstar_id; //0x0008
        char pad_0010[52]; //0x0010
        class netAddress m_relay_ip; //0x0044
        uint16_t m_relay_port; //0x0048
        char pad_004A[2]; //0x004A
        class netAddress m_external_ip; //0x004C
        uint16_t m_external_port; //0x0050
        char pad_0052[2]; //0x0052
        class netAddress m_internal_ip; //0x0054
        uint16_t m_internal_port; //0x0058
        char pad_005A[6]; //0x005A
        uint64_t m_host_token; //0x0060
        uint64_t m_peer_id; //0x0068
        uint64_t m_rockstar_id2; //0x0070
        char pad_0078[12]; //0x0078
        char m_name[20]; //0x0084
    }; //Size: 0x0098
    static_assert(sizeof(netPlayerData) == 0x98);
}
