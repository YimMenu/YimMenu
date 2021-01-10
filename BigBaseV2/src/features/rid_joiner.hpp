#pragma once
#include "common.hpp"

namespace big
{
	class rid_joiner
	{
	public:
        std::string gs_info;
        uint64_t rid;

        void look_for_session();
        void handle_info();
		void join_player(uint64_t rid);
	private:
		bool awaiting_request = false;
		int type = 0;
	};

    inline rid_joiner g_rid_joiner{};

    struct rockstar_identifier {
        uint64_t rockstar_id;
        uint32_t type;
        uint32_t sub_type;
    };

    struct gs_session {
        char _0x0000[0x8];
        uint64_t PeerToken;
        char _0x0010[0x38];
        uint64_t RockstarID;
    };

    struct net_msg_identifier {
        uint64_t rockstar_id;
        uint8_t type;
        char _0x0009[0xB];
    };

    struct rs_info {
        char scs_ticket[0x100];
        char _0x0100[0x190];
        uint64_t peer;
        char _0x0298[0xA7];
        char email[0x50];
        char _0x038f[0x20];
        char name[0x20];
        char _0x03cf[0x29];
        uint32_t rockstar_id;
    };

    struct network_handle {
        int Handle;
        char _0x0[48];
    };

    struct join_rstar_id_request {
        char _0x0000[0x8];
        gs_session session_info;
        net_msg_identifier identifier;
    };
}