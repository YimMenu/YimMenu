#pragma once
#include <cpr/cpr.h>

namespace big
{
	constexpr auto CONNECT_TIMEOUT = 1000;
	constexpr auto REQUEST_TIMEOUT = 5000;

	class http_client
	{
	private:
		cpr::Session m_session;

	public:
		http_client();
		virtual ~http_client()                         = default;
		http_client(const http_client&)                = delete;
		http_client(http_client&&) noexcept            = delete;
		http_client& operator=(const http_client&)     = delete;
		http_client& operator=(http_client&&) noexcept = delete;

		bool download(const cpr::Url& url, const std::filesystem::path& path, cpr::Header headers = {}, cpr::Parameters query_params = {});
		cpr::Response get(const cpr::Url& url, cpr::Header headers = {}, cpr::Parameters query_params = {});
		cpr::Response post(const cpr::Url& url, cpr::Header headers = {}, cpr::Body body = {});
	};

	inline auto g_http_client = http_client();
}