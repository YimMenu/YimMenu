#include "http_client.hpp"

namespace big
{
    http_client::http_client()
    {
        m_protocols = {
            {ProxyProtocol::NONE, "None"},
            {ProxyProtocol::HTTP, "http"},
            {ProxyProtocol::HTTPS, "https"},
        };
    }

	bool http_client::download(const cpr::Url& url, const std::filesystem::path& path, cpr::Header headers, cpr::Parameters query_params)
	{
        std::ofstream of(path, std::ios::binary);
        auto res = cpr::Download(of, url, query_params, m_proxy, m_proxy_auth);

		return res.status_code == 200;
	}

	cpr::Response http_client::get(const cpr::Url& url, cpr::Header headers, cpr::Parameters query_params)
	{
        return cpr::Get(url, headers, query_params, m_proxy, m_proxy_auth);
    }

	cpr::Response http_client::post(const cpr::Url& url, cpr::Header headers, cpr::Body body)
	{
		return cpr::Post(url, headers, body, m_proxy, m_proxy_auth);
	}

	const std::string_view http_client::get_protocol()
    {
        return m_protocols[m_protocol];
    }

    bool http_client::init(ProxyProtocol protocol, std::string proxy_host, std::pair<const std::string, std::string> proxy_auth)
    {
        return update_proxy(protocol, proxy_host, proxy_auth);
    }

    bool http_client::update_proxy(ProxyProtocol protocol, std::string proxy_host, std::pair<const std::string, std::string> proxy_auth)
    {
        m_protocol = protocol;

        if (protocol == ProxyProtocol::NONE)
        {
            m_proxy = {};
            m_proxy_auth = {};

            return true;
        }
        const auto protocol_type = m_protocols[protocol].data();
        m_proxy = {{ protocol_type, proxy_host }};
        m_proxy_auth = {{ protocol_type, cpr::EncodedAuthentication(proxy_auth.first, proxy_auth.second) }};

        return true;
    }
}