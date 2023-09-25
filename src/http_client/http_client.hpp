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

        bool download(const cpr::Url& url, const std::filesystem::path& path, cpr::Header headers = {}, cpr::Parameters query_params = {});
        cpr::Response get(const cpr::Url& url, cpr::Header headers = {}, cpr::Parameters query_params = {});
        cpr::Response post(const cpr::Url& url, cpr::Header headers = {}, cpr::Body body = {});
        
        bool init(file proxy_settings_file);
        bool update_proxy(ProxyProtocol protocol, std::string proxy_host = {}, std::pair<std::string, std::string> proxy_auth = {});
        bool save() const;

    private:

    };

    inline auto g_http_client = http_client();
}