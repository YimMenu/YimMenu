#pragma once
#include "http_request.hpp"

namespace big::api
{
	const std::string domain = "http://home.damon.sh:8089/api/v1";
	//const std::string domain = "http://localhost:8080/api/v1";
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
			static std::atomic_bool busy = false;
			if (busy || g_local_player == nullptr) return false;
			busy = true;

			const std::string path = "/auth/create_session";

			http::Request request(domain + path);

			CPlayerInfo* player_info = g_local_player->m_player_info;
			rage::netPlayerData& netData = player_info->m_net_player_data;

			nlohmann::json body = {
				{ "username", std::string(netData.m_name) },
				{ "rockstar_id", netData.m_rockstar_id }
			};

			try
			{
				http::Response res = request.send("POST", body.dump(), {
					"Content-Type: application/json"
				}, 10000ms);

				nlohmann::json json;
				if (util::parse_body(res, json))
				{
					session_id = json["data"]["sessionId"].get<std::string>();

					LOG(INFO) << "Create session and received ID: " << session_id.c_str();

					busy = false;
					return true;
				}
			}
			catch (const std::exception&)
			{
				LOG(INFO) << "Host is down, unable to create session.";

				busy = false;
				return false;
			}
			
			LOG(INFO) << "Failed to create a session.";

			busy = false;
			return false;
		}
	}

	namespace vehicle
	{
		namespace handling
		{
			static bool create_profile(uint32_t handling_hash, const char* name, const char* description, nlohmann::json& handling_data, nlohmann::json& out)
			{
				if (!util::signed_in()) return false;

				const std::string path = "/vehicle/handling/create";

				http::Request request(domain + path);

				out["handling_hash"] = handling_hash;
				out["name"] = std::string(name);
				out["description"] = std::string(description);
				out["data"] = handling_data;

				http::Response res = request.send("POST", out.dump(), {
					util::authorization_header()
				});
				return util::parse_body(res, out);
			}

			static bool get_by_share_code(std::string share_code, nlohmann::json& out)
			{
				if (!util::signed_in()) return false;

				const std::string path = "/vehicle/handling/get_by_share_code?share_code=";

				http::Request request(domain + path + share_code);

				http::Response res = request.send("GET", "", {
					util::authorization_header()
				});

				return util::parse_body(res, out);
			}

			static bool get_my_handling(uint32_t handling_hash, nlohmann::json &out)
			{
				if (!util::signed_in()) return false;

				const std::string path = "/vehicle/handling/get_mine?handling_hash=";

				http::Request request(domain + path + std::to_string(handling_hash));

				http::Response res = request.send("GET", "", {
					util::authorization_header()
				});

				return util::parse_body(res, out);
			}

			static bool get_saved_handling(uint32_t handling_hash, nlohmann::json& out)
			{
				if (!util::signed_in()) return false;

				const std::string path = "/vehicle/handling/get_saved?handling_hash=";

				http::Request request(domain + path + std::to_string(handling_hash));

				http::Response res = request.send("GET", "", {
					util::authorization_header()
				});

				return util::parse_body(res, out);
			}

			static bool save_profile(std::string share_code)
			{
				if (!util::signed_in()) return false;

				const std::string path = "/vehicle/handling/save_profile";

				http::Request request(domain + path);

				nlohmann::json body = { { "share_code", share_code } };

				http::Response res = request.send("POST", body.dump(), {
					util::authorization_header()
				});
				return util::parse_body(res, body);
			}

			static bool update(uint32_t handling_hash, const char* name, const char* description, std::string share_code, nlohmann::json &update)
			{
				if (!util::signed_in()) return false;

				const std::string path = "/vehicle/handling/update";

				http::Request request(domain + path);
				
				nlohmann::json json;
				json["handling_hash"] = handling_hash;
				json["name"] = std::string(name);
				json["description"] = std::string(description);
				json["data"] = update;
				json["share_code"] = share_code;

				http::Response res = request.send("POST", json.dump(), {
					util::authorization_header()
				});
				return util::parse_body(res, update);
			}
		}
	}
}