#pragma once
#include "proxy_protocols.hpp"

namespace big
{
    struct proxy_settings
    {
        std::string proxy_host;
        int proxy_port;
        ProxyProtocol protocol = ProxyProtocol::NONE;

        struct credentials
        {
            bool uses_creds;
        
            std::string user;
            std::string password;

            NLOHMANN_DEFINE_TYPE_INTRUSIVE(credentials, uses_creds, user, password)
        } creds{};

        NLOHMANN_DEFINE_TYPE_INTRUSIVE(proxy_settings, proxy_host, proxy_port, protocol, creds)

    };
}