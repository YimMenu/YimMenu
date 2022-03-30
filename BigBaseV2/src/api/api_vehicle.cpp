#include "api.hpp"
#include "api_vehicle.hpp"

namespace big::api
{
	vehicle_api::vehicle_api(api* api)
		: m_api(api)
	{
		
	}

	bool vehicle_api::create_handling_profile(
		const std::uint32_t handling_hash,
		const std::string_view name,
		const std::string_view descr,
		const nlohmann::json& data,
		nlohmann::json& out) const
	{
		if (!m_api->is_authenticated())
			return false;

		const auto body = nlohmann::json{
			{ "handlingHash", handling_hash },
			{ "name", name.data() },
			{ "description", descr.data() },
			{ "data", data }
		};

		const auto result = m_api->Post("/api/v2/vehicle/handling", m_api->get_headers(), out.dump(), "application/json");
		if (result.error() != httplib::Error::Success)
		{
			LOG(WARNING) << "HTTPLib error: " << to_string(result.error());

			return false;
		}
		if (result->status != 200)
		{
			LOG(WARNING) << "API did not return 200 success code when creating handling profile.";

			return false;
		}
		if (!api::parse_body(result->body, out))
		{
			LOG(WARNING) << "Failed to parse handling JSON data.";

			return false;
		}

		return true;
	}

	bool vehicle_api::delete_handling_profile(const std::string_view share_code) const
	{
		if (!m_api->is_authenticated())
			return false;

		const auto body = nlohmann::json{
			{ "shareCode", share_code.data() }
		};

		const auto result = m_api->Delete("/api/v2/vehicle/handling", m_api->get_headers(), body.dump(), "application/json");
		if (result.error() != httplib::Error::Success)
		{
			LOG(WARNING) << "HTTPLib error: " << to_string(result.error());

			return false;
		}
		if (result->status != 204)
		{
			LOG(WARNING) << "API did not return 204 success code when deleting handling profile.";

			return false;
		}

		return true;
	}

	bool vehicle_api::delete_saved_handling_profile(const std::string_view share_code) const
	{
		if (!m_api->is_authenticated())
			return false;

		const auto body = nlohmann::json{
			{ "shareCode", share_code.data() }
		};

		const auto result = m_api->Delete("/api/v2/vehicle/saved_handling", m_api->get_headers(), body.dump(), "application/json");
		if (result.error() != httplib::Error::Success)
		{
			LOG(WARNING) << "HTTPLib error: " << to_string(result.error());

			return false;
		}
		if (result->status != 204)
		{
			LOG(WARNING) << "API did not return 204 success code when deleting saved handling profile.";

			return false;
		}

		return true;
	}

	bool vehicle_api::get_handling_profile(const std::string_view share_code, nlohmann::json& out) const
	{
		if (!m_api->is_authenticated())
			return false;

		std::string path = "/api/v2/vehicle/handling";
		path += "?share_code=";
		path += share_code.data();

		const auto result = m_api->Get(path.c_str(), m_api->get_headers());
		if (result.error() != httplib::Error::Success)
		{
			LOG(WARNING) << "HTTPLib error: " << to_string(result.error());

			return false;
		}
		if (result->status != 200)
		{
			LOG(WARNING) << "API did not return 200 success code when getting handling profile.";

			return false;
		}
		if (!api::parse_body(result->body, out))
		{
			LOG(WARNING) << "Failed to parse handling JSON data.";

			return false;
		}

		return true;
	}

	bool vehicle_api::get_my_handling_profiles(const std::uint32_t handling_hash, nlohmann::json& out) const
	{
		if (!m_api->is_authenticated())
			return false;

		std::string path = "/api/v2/vehicle/handling";
		path += "?handling_hash=";
		path += std::to_string(handling_hash);
		path += "&mine";

		const auto result = m_api->Get(path.c_str(), m_api->get_headers());
		if (result.error() != httplib::Error::Success)
		{
			LOG(WARNING) << "HTTPLib error: " << to_string(result.error());

			return false;
		}
		if (result->status != 200)
		{
			LOG(WARNING) << "API did not return 200 success code when getting personal handling profiles.";

			return false;
		}
		if (!api::parse_body(result->body, out))
		{
			LOG(WARNING) << "Failed to parse handling JSON data.";

			return false;
		}

		return true;
	}

	bool vehicle_api::get_saved_handling_profiles(const std::uint32_t handling_hash, nlohmann::json& out) const
	{
		if (!m_api->is_authenticated())
			return false;

		std::string path = "/api/v2/vehicle/handling";
		path += "?handling_hash=";
		path += std::to_string(handling_hash);
		path += "&saved";

		const auto result = m_api->Get(path.c_str(), m_api->get_headers());
		if (result.error() != httplib::Error::Success)
		{
			LOG(WARNING) << "HTTPLib error: " << to_string(result.error());

			return false;
		}
		if (result->status != 200)
		{
			LOG(WARNING) << "API did not return 200 success code when getting saved handling profiles.";

			return false;
		}
		if (!api::parse_body(result->body, out))
		{
			LOG(WARNING) << "Failed to parse handling JSON data.";

			return false;
		}

		return true;
	}

	bool vehicle_api::update_handling_profile(const std::string_view share_code, const std::string_view name, const std::string_view descr, const nlohmann::json& update, nlohmann::json& out) const
	{
		if (!m_api->is_authenticated())
			return false;

		const auto body = nlohmann::json{
			{ "shareCode", share_code.data() },
			{ "name", name.data() },
			{ "description", descr.data() },
			{ "data", update }
		};

		const auto result = m_api->Put("/api/v2/vehicle/handling", m_api->get_headers(), body.dump(), "application/json");
		if (result.error() != httplib::Error::Success)
		{
			LOG(WARNING) << "HTTPLib error: " << to_string(result.error());

			return false;
		}
		if (result->status != 200)
		{
			LOG(WARNING) << "API did not return 200 success code when updating handling profile.";

			return false;
		}
		if (!api::parse_body(result->body, out))
		{
			LOG(WARNING) << "Failed to parse handling JSON data.";

			return false;
		}

		return true;
	}

	bool vehicle_api::update_saved_handling_profile(const std::string_view share_code) const
	{
		if (!m_api->is_authenticated())
			return false;

		const auto body = nlohmann::json{
			{ "shareCode", share_code.data() }
		};

		const auto result = m_api->Put("/api/v2/vehicle/saved_handling", m_api->get_headers(), body.dump(), "application/json");
		if (result.error() != httplib::Error::Success)
		{
			LOG(WARNING) << "HTTPLib error: " << to_string(result.error());

			return false;
		}
		if (result->status != 204)
		{
			LOG(WARNING) << "API did not return 204 success code when adding saved handling profile.";

			return false;
		}

		return true;
	}
}
