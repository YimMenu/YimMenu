#pragma once
#include "netPlayerData.hpp"

namespace rage
{
    class netPlayer
    {
    public:
        virtual ~netPlayer();
        virtual void reset();
        virtual bool is_valid();
        virtual const char* get_name();
        virtual void _0x20();
        virtual bool is_host();
        virtual netPlayerData* get_net_data();
        virtual void _0x38();
    }; //Size: 0x0008
    static_assert(sizeof(netPlayer) == 0x8);
}
