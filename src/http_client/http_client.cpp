#include "http_client.hpp"

namespace big
{
	http_client::http_client()
	{
		m_protocols = {
		    {ProxyProtocol::NONE, "None"},
		    {ProxyProtocol::HTTP, "http"},
		    {ProxyProtocol::HTTPS, "https"},
		    {ProxyProtocol::SOCKS4, "socks4"},
		    {ProxyProtocol::SOCKS4A, "socks4a"},
		    {ProxyProtocol::SOCKS5, "socks5"},
		    {ProxyProtocol::SOCKS5H, "socks5h"},
		};
	}

	const std::string_view http_client::protocol()
	{
		return m_protocols[m_proxy_settings.protocol];
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

	const std::unordered_map<ProxyProtocol, const std::string_view>& http_client::protocols() const
	{
		return m_protocols;
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

				m_proxy_settings = j.get<proxy_settings>();
				return update_proxy(m_proxy_settings);
			}
			catch (const std::exception& e)
			{
				LOG(WARNING) << "Failed to parse proxy settings file: " << e.what();
			}
		}
		return update_proxy();
	}

	bool http_client::update_proxy(proxy_settings settings)
	{
		m_protocol   = settings.protocol;
		m_proxy      = {};
		m_proxy_auth = {};

		if (m_protocol != ProxyProtocol::NONE)
		{
			const auto protocol_type = m_protocols[m_protocol].data();
			m_proxy                  = {{protocol_type, settings.proxy_host}};
			m_proxy_auth             = {{protocol_type, cpr::EncodedAuthentication(settings.user, settings.password)}};
		}

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