#pragma once
#include <cpr/cpr.h>

namespace big
{
    enum class ProxyProtocol
    {
        NONE,
        HTTP,
        HTTPS,
        SOCKS4,
        SOCKS4A,
        SOCKS5,
        SOCKS5H,
    };
    NLOHMANN_JSON_SERIALIZE_ENUM(ProxyProtocol, {
        { ProxyProtocol::NONE, "none" },
        { ProxyProtocol::HTTP, "http" },
        { ProxyProtocol::HTTPS, "https" },
        { ProxyProtocol::SOCKS4, "socks4" },
        { ProxyProtocol::SOCKS4A, "socks4a" },
        { ProxyProtocol::SOCKS5, "socks5" },
        { ProxyProtocol::SOCKS5H, "socks5h" },
    })

    struct proxy_settings
    {
        std::string proxy_host;
        ProxyProtocol protocol = ProxyProtocol::NONE;
        std::string user;
        std::string password;

        NLOHMANN_DEFINE_TYPE_INTRUSIVE(proxy_settings, proxy_host, protocol, user, password)

    };

    class http_client
    {
    private:
        std::unordered_map<ProxyProtocol, const std::string_view> m_protocols;

        cpr::Proxies m_proxy;
        cpr::ProxyAuthentication m_proxy_auth;
        ProxyProtocol m_protocol;

        proxy_settings m_proxy_settings;
        file m_proxy_settings_file;

    public:
        http_client();
        virtual ~http_client() = default;
        http_client(const http_client&) = delete;
        http_client(http_client&&) noexcept = delete;
        http_client& operator=(const http_client&) = delete;
        http_client& operator=(http_client&&) noexcept = delete;

        const std::string_view protocol();
        const std::unordered_map<ProxyProtocol, const std::string_view>& protocols() const;

        bool download(const cpr::Url& url, const std::filesystem::path& path, cpr::Header headers = {}, cpr::Parameters query_params = {});
        cpr::Response get(const cpr::Url& url, cpr::Header headers = {}, cpr::Parameters query_params = {});
        cpr::Response post(const cpr::Url& url, cpr::Header headers = {}, cpr::Body body = {});
        
        proxy_settings& settings()
        {
            return m_proxy_settings;
        }

        bool init(file proxy_settings_file);
        bool update_proxy(proxy_settings settings = {});
        bool save() const;

    private:

    };

    inline auto g_http_client = http_client();
}