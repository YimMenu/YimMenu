#include "proxy_mgr.hpp"

namespace big
{
	proxy_mgr::proxy_mgr(cpr::Session& session) :
	    m_session(session),
	    m_protocols({
	        {ProxyProtocol::NONE, "none"},
	        {ProxyProtocol::HTTP, "http"},
	        {ProxyProtocol::HTTPS, "https"},
	        {ProxyProtocol::SOCKS4, "socks4"},
	        {ProxyProtocol::SOCKS4A, "socks4a"},
	        {ProxyProtocol::SOCKS5, "socks5"},
	        {ProxyProtocol::SOCKS5H, "socks5h"},
	    })
	{
	}

	bool proxy_mgr::load(file proxy_settings_file)
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
			}
			catch (const std::exception& e)
			{
				LOG(WARNING) << "Failed to parse proxy settings file: " << e.what();
				return false;
			}
		}

		if (m_proxy_settings.creds.uses_creds)
		{
			update(m_proxy_settings.proxy_host,
			    m_proxy_settings.proxy_port,
			    m_proxy_settings.protocol,
			    m_proxy_settings.creds.user,
			    m_proxy_settings.creds.password);

			return true;
		}
		update(m_proxy_settings.proxy_host, m_proxy_settings.proxy_port, m_proxy_settings.protocol);

		return true;
	}

	void proxy_mgr::update(const std::string& host, const int port, const ProxyProtocol protocol)
	{
		m_proxy_settings.protocol   = protocol;
		m_proxy_settings.proxy_host = host;
		m_proxy_settings.proxy_port = port;

		m_proxy_settings.creds = {};

		apply_proxy_to_session();
		save();
	}

	void proxy_mgr::update(const std::string& host, const int port, const ProxyProtocol protocol, const std::string& user, const std::string& password)
	{
		m_proxy_settings.protocol   = protocol;
		m_proxy_settings.proxy_host = host;
		m_proxy_settings.proxy_port = port;

		m_proxy_settings.creds.uses_creds = true;
		m_proxy_settings.creds.user       = user;
		m_proxy_settings.creds.password   = password;

		apply_proxy_to_session();
		save();
	}

	void proxy_mgr::reset()
	{
		m_proxy_settings = {};

		save();
	}

	std::string proxy_mgr::protocol_str() const
	{
		return m_protocols.at(m_proxy_settings.protocol);
	}

	const std::string& proxy_mgr::protocol_str(ProxyProtocol protocol) const
	{
		return m_protocols.at(protocol);
	}

	void proxy_mgr::apply_proxy_to_session()
	{
		if (m_proxy_settings.protocol == ProxyProtocol::NONE)
		{
			m_session.SetProxies({});
			m_session.SetProxyAuth({});

			return;
		}

		std::map<std::string, std::string> proxies;
		std::map<std::string, cpr::EncodedAuthentication> proxy_auths;
		const auto proxy_auth = cpr::EncodedAuthentication{m_proxy_settings.creds.user, m_proxy_settings.creds.password};

		for (const auto& supported_protocol : m_supported_protocols)
		{
			proxies.insert({supported_protocol, build_url(m_proxy_settings.proxy_host, std::to_string(m_proxy_settings.proxy_port))});
			if (m_proxy_settings.creds.uses_creds)
			{
				proxy_auths.insert({supported_protocol, proxy_auth});
			}
		}

		m_session.SetProxies(proxies);
		if (m_proxy_settings.creds.uses_creds)
			m_session.SetProxyAuth(proxy_auths);
	}

	std::string proxy_mgr::build_url(const std::string& host, const std::string& port) const
	{
		return protocol_str() + "://" + host + ":" + port;
	}

	bool proxy_mgr::save()
	{
		try
		{
			auto settings_file = std::ofstream(m_proxy_settings_file.get_path(), std::ios::binary | std::ios::trunc);

			nlohmann::json j = m_proxy_settings;
			settings_file << j;
		}
		catch (const std::exception& e)
		{
			std::cerr << e.what() << '\n';

			return false;
		}

		return true;
	}
}