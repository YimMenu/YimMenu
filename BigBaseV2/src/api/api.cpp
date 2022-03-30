#include "api/api.hpp"
#include "api/api_vehicle.hpp"
#include "pointers.hpp"
#include "thread_pool.hpp"

namespace big::api
{
	api::api(std::string_view origin)
		: Client(origin.data()), m_origin(origin)
	{
		set_connection_timeout(5);
		set_read_timeout(10s);
		set_write_timeout(10s);

		/*g_thread_pool->push([this]
		{
			auto_signin();
		});*/

		vehicle = std::make_unique<vehicle_api>(this);

		g_api = this;
	}

	api::~api()
	{
		g_api = nullptr;
	}

	bool api::authenticate(const char* sc_token)
	{
		const auto token = std::string(sc_token);
		const nlohmann::json body({
			{ "token", token }
		});

		const auto result = Post("/api/v2/authenticate", body.dump(), "application/json");
		if (result.error() != httplib::Error::Success)
		{
			LOG(WARNING) << "HTTPLib error: " << to_string(result.error());

			return false;
		}
		if (result->status != 200)
		{
			LOG(WARNING) << "non-200 response code returned while trying to authenticate with backend.";

			return false;
		}

		try
		{
			const auto response_body = nlohmann::json::parse(
				result->body
			);
			m_session_id = response_body["sessionId"];
			m_authenticated = true;

			LOG(INFO) << "Successfully authenticated with API.";
		}
		catch (...)
		{
			LOG(WARNING) << "Failed to parse JSON response body.";

			return false;
		}

		return true;
	}

	httplib::Headers api::get_headers() const
	{
		return {
			{ "Authorization", m_session_id }
		};
	}

	bool api::is_authenticated() const
	{
		return m_authenticated;
	}


// private methods
	void api::auto_signin()
	{
		while (g_running && !is_authenticated())
		{
			if (g_pointers->m_sc_info->m_ticket[0] == '\0')
			{
				std::this_thread::sleep_for(1s);

				continue;
			}

			if (!authenticate(g_pointers->m_sc_info->m_ticket))
				std::this_thread::sleep_for(10s);
		}	
	}

	bool api::parse_body(const std::string& body, nlohmann::json& out)
	{
		try
		{
			out = nlohmann::json::parse(body);

			return true;
		}
		catch (...)
		{
			return false;
		}
	}

}