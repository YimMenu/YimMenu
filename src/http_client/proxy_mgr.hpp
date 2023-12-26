#pragma once
#include <cpr/cpr.h>
#include "proxy_protocols.hpp"
#include "proxy_settings.hpp"

namespace big
{
	class proxy_mgr
	{
	private:
		cpr::Session& m_session;
		// protocols supported by CURL
        std::unordered_map<ProxyProtocol, std::string> m_protocols;
		// protocols to be proxied
		std::array<const std::string, 2> m_supported_protocols = { "http", "https" };

		proxy_settings m_proxy_settings;
        file m_proxy_settings_file;

	public:
		proxy_mgr(cpr::Session& session);

		bool load(file proxy_settings_file);
		void update(const std::string& host, const int port, const ProxyProtocol protocol);
		void update(const std::string& host, const int port, const ProxyProtocol protocol, const std::string& user, const std::string& password);
		void reset();

		std::string protocol_str() const;
		const std::string& protocol_str(ProxyProtocol protocol) const;
		const auto& protocols() const
		{ return m_protocols; }

		const proxy_settings& settings() const
		{ return m_proxy_settings; }

	private:
        void apply_proxy_to_session();
		std::string build_url(const std::string& host, const std::string& port) const;
		bool save();

	};
}