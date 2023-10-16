#include "http_client.hpp"

namespace big
{
	http_client::http_client() :
	    m_proxy_mgr(m_session)
	{
		m_session.SetConnectTimeout(CONNECT_TIMEOUT);
		m_session.SetTimeout(REQUEST_TIMEOUT);
	}

	bool http_client::download(const cpr::Url& url, const std::filesystem::path& path, cpr::Header headers, cpr::Parameters query_params)
	{
		m_session.SetUrl(url);
		m_session.SetHeader(headers);
		m_session.SetParameters(query_params);

		std::ofstream of(path, std::ios::binary);
		auto res = m_session.Download(of);

		return res.status_code == 200;
	}

	cpr::Response http_client::get(const cpr::Url& url, cpr::Header headers, cpr::Parameters query_params)
	{
		m_session.SetUrl(url);
		m_session.SetHeader(headers);
		m_session.SetParameters(query_params);

		return m_session.Get();
	}

	cpr::Response http_client::post(const cpr::Url& url, cpr::Header headers, cpr::Body body)
	{
		m_session.SetUrl(url);
		m_session.SetHeader(headers);
		m_session.SetBody(body);

		return m_session.Post();
	}

	bool http_client::init(file proxy_settings_file)
	{
		return m_proxy_mgr.load(proxy_settings_file);
	}
}