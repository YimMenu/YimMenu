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

    bool http_client::init(file proxy_settings_file)
    {
        m_proxy_settings_file = proxy_settings_file;
        if (proxy_settings_file.exists())
        {
            auto settings_file = std::ifstream(proxy_settings_file.get_path(), std::ios::binary);
            try
            {
                nlohmann::json j;
                settings_file >> j;

                const auto data = j.get<proxy_settings>();
                return update_proxy(data.protocol, data.proxy_host, { data.user, data.password });
            }
            catch(const std::exception& e)
            {
                LOG(WARNING) << "Failed to parse proxy settings file: " << e.what();
            }
        }
        return update_proxy(ProxyProtocol::NONE);
    }

    bool http_client::update_proxy(ProxyProtocol protocol, std::string proxy_host, std::pair<std::string, std::string> proxy_auth)
    {
        m_protocol = protocol;
        m_proxy = {};
        m_proxy_auth = {};

        if (protocol != ProxyProtocol::NONE)
        {
            const auto protocol_type = m_protocols[protocol].data();
            m_proxy = {{ protocol_type, proxy_host }};
            m_proxy_auth = {{ protocol_type, cpr::EncodedAuthentication(proxy_auth.first, proxy_auth.second) }};
        }
        m_proxy_settings = { proxy_host, m_protocol, proxy_auth.first, proxy_auth.second };

        return true;
    }

    bool http_client::save() const
    {
        auto settings_file = std::ofstream(m_proxy_settings_file.get_path(), std::ios::binary | std::ios::trunc);

        nlohmann::json j = m_proxy_settings;
        settings_file << j;

        return true;
    }
}