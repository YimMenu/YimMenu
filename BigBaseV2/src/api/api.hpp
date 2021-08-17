#pragma once
#include "http_request.hpp"

namespace big::api
{
	const std::string domain = "http://localhost:8080/api/v1";
	inline std::string session_id;

	namespace util
	{
		static std::string authorization_header()
		{
			return std::string("Authorization: ") + api::session_id;
		}

		static bool parse_body(http::Response& res, nlohmann::json& out)
		{
			try
			{
				out = nlohmann::json::parse(res.body.begin(), res.body.end());

				return out["status"] == std::string("success");
			}
			catch (const std::exception& e)
			{
				out = nullptr;

				LOG(INFO) << "Failed to parse request body: " << std::endl << e.what();

				return false;
			}
		}

		static bool signed_in()
		{
			return !session_id.empty();
		}
	}

	namespace auth
	{
		static bool create_session()
		{
			if (g_local_player == nullptr) return false;

			const std::string path = "/auth/create_session";

			http::Request request(domain + path);

			CPlayerInfo* player_info = g_local_player->m_player_info;
			nlohmann::json body = {
				{ "username", std::string(player_info->m_name) },
				{ "rockstar_id", player_info->m_rockstar_id2 }
			};

			http::Response res = request.send("POST", body.dump(), {
				"Content-Type: application/json"
			});

			nlohmann::json json;
			if (util::parse_body(res, json))
			{
				session_id = json["data"]["sessionId"].get<std::string>();

				LOG(INFO) << "Create session and received ID: " << session_id.c_str();

				return true;
			}
			
			LOG(INFO) << "Failed to create a session.";

			return false;
		}
	}

	namespace vehicle
	{
		namespace handling
		{
			static bool create_profile(uint32_t handling_hash, const char* name, const char* description, nlohmann::json &handling_data)
			{
				const std::string path = "/vehicle/handling/create";

				http::Request request(domain + path);

				nlohmann::json json;
				json["handling_hash"] = handling_hash;
				json["name"] = std::string(name);
				json["description"] = std::string(description);
				json["data"] = handling_data;

				http::Response res = request.send("POST", json.dump(), {
					util::authorization_header()
				});
				return util::parse_body(res, json);
			}

			static bool get_by_share_code(std::string share_code, nlohmann::json& out)
			{
				const std::string path = "/vehicle/handling/get_by_share_code?share_code=";

				http::Request request(domain + path + share_code);

				http::Response res = request.send("GET", "", {
					util::authorization_header()
				});

				return util::parse_body(res, out);
			}

			static bool get_my_handling(uint32_t handling_hash, nlohmann::json &out)
			{
				const std::string path = "/vehicle/handling/get_mine?handling_hash=";

				http::Request request(domain + path + std::to_string(handling_hash));

				http::Response res = request.send("GET", "", {
					util::authorization_header()
				});

				return util::parse_body(res, out);
			}
		}
	}
}