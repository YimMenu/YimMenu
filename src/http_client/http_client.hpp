#pragma once
#include <cpr/cpr.h>

namespace big
{
    enum class ProxyProtocol
    {
        NONE,
        HTTP,
        HTTPS
    };
    NLOHMANN_JSON_SERIALIZE_ENUM(ProxyProtocol, {
        { ProxyProtocol::NONE, "none" },
        { ProxyProtocol::HTTP, "http" },
        { ProxyProtocol::HTTPS, "https" }
    })

    class http_client
    {
    private:
        std::unordered_map<ProxyProtocol, const std::string_view> m_protocols;

        cpr::Proxies m_proxy;
        cpr::ProxyAuthentication m_proxy_auth;
        ProxyProtocol m_protocol;

    public:
        http_client();
        virtual ~http_client() = default;
        http_client(const http_client&) = delete;
        http_client(http_client&&) noexcept = delete;
        http_client& operator=(const http_client&) = delete;
        http_client& operator=(http_client&&) noexcept = delete;

        bool download(const cpr::Url& url, const std::filesystem::path& path, cpr::Header headers = {}, cpr::Parameters query_params = {});
        cpr::Response get(const cpr::Url& url, cpr::Header headers = {}, cpr::Parameters query_params = {});
        cpr::Response post(const cpr::Url& url, cpr::Header headers = {}, cpr::Body body = {});

        const std::string_view get_protocol();
        
        bool init(ProxyProtocol protocol = ProxyProtocol::NONE, std::string proxy_host = {}, std::pair<const std::string, std::string> proxy_auth = {});
        bool update_proxy(ProxyProtocol protocol, std::string proxy_host = {}, std::pair<const std::string, std::string> proxy_auth = {});

    };

    inline auto g_http_client = http_client();
}