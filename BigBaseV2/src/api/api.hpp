#pragma once
#include <httplib.h>

namespace big::api
{
	class vehicle_api;

	class api final : protected httplib::Client
	{
		const std::string_view m_origin;
		std::string m_session_id;

		bool m_authenticated = false;

	public:
		explicit api(std::string_view origin);
		~api();

		bool authenticate(const char* sc_token);

		[[nodiscard]] bool is_authenticated() const;

		[[nodiscard]] static bool parse_body(const std::string& body, nlohmann::json& out);

		std::unique_ptr<vehicle_api> vehicle;

	private:
		friend class vehicle_api;

		void auto_signin();

		[[nodiscard]] httplib::Headers get_headers() const;
	};
}

namespace big
{
	inline api::api* g_api{};
}
