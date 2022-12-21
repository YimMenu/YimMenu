#include "api_service.hpp"
#include "pointers.hpp"
#include "services/creator_storage/creator_storage_service.hpp"

namespace big
{

	api_service::api_service()
	{
		g_api_service = this;
	}

	api_service::~api_service()
	{
		g_api_service = nullptr;
	}

	bool api_service::get_rid_from_username(std::string_view username, uint64_t& result)
	{
		cpr::Response response = cpr::Post(
			cpr::Url{ "https://scui.rockstargames.com/api/friend/accountsearch" },
			cpr::Header{ {"Authorization", AUTHORIZATION_TICKET }, { "X-Requested-With", "XMLHttpRequest"} },
			cpr::Body{ { std::format("searchNickname={}", username) } });

		if (response.status_code == 200)
		{
			nlohmann::json obj = nlohmann::json::parse(response.text);
			if (obj["Total"] > 0 && username.compare(obj["Accounts"].at(0)["Nickname"]) == 0)
			{
				result = obj["Accounts"].at(0)["RockstarId"];
				return true;
			}
		}

		return false;
	}

	bool api_service::get_username_from_rid(uint64_t rid, std::string& result)
	{
		cpr::Response response = cpr::Post(
			cpr::Url{ "https://scui.rockstargames.com/api/friend/getprofile" },
			cpr::Header{ {"Authorization", AUTHORIZATION_TICKET }, { "X-Requested-With", "XMLHttpRequest"}, {"Content-Type", "application/json"} },
			cpr::Body{ { std::format(R"({{"RockstarId":"{}"}})", rid) } });

		if (response.status_code == 200)
		{
			nlohmann::json obj = nlohmann::json::parse(response.text);
			result = obj["Accounts"].at(0)["RockstarAccount"]["Name"];
			return true;
		}

		return false;
	}

	// Ratelimit: 10 per Minute, if exceeded than 5 min cooldown
	bool api_service::send_socialclub_message(uint64_t rid, std::string_view message)
	{
		cpr::Response response = cpr::Post(
			cpr::Url{ "https://scui.rockstargames.com/api/messaging/sendmessage" },
			cpr::Header{ {"Authorization", AUTHORIZATION_TICKET }, { "X-Requested-With", "XMLHttpRequest"}, {"Content-Type", "application/json"} },
			cpr::Body{ { std::format(R"({{"env":"prod","title":"gta5","version":11,"recipientRockstarId":"{}","messageText":"{}"}})", rid, message) } });

		return response.status_code == 200;
	}

	bool api_service::get_job_details(std::string_view job_link, nlohmann::json& result)
	{
		if (job_link.starts_with("https://"))
			job_link = job_link.substr(46); // https://socialclub.rockstargames.com/job/gtav/

		cpr::Response response = cpr::Get(
			cpr::Url{ "https://scapi.rockstargames.com/ugc/mission/details" },
			cpr::Header{ {"X-AMC", "true" }, { "X-Requested-With", "XMLHttpRequest"} },
			cpr::Parameters{ {"title", "gtav"}, {"contentId", job_link.data()} });

		result = nlohmann::json::parse(response.text);

		return response.status_code == 200;
	}

	bool api_service::download_job_metadata(std::string_view content_part)
	{
		for (int major = 0; major < 3; major++)
		{
			for (int minor = 0; minor < 3; minor++)
			{
				for (const auto& lang : languages)
				{
					cpr::Response response = cpr::Get(cpr::Url{ std::format("https://prod.cloud.rockstargames.com/ugc/gta5mission/{}/{}_{}_{}.json", content_part, major, minor, lang) });

					if (response.status_code == 200)
					{
						std::ofstream of = creator_storage_service::create_file(std::string(content_part).substr(5) + ".json");
						cpr::Response r = cpr::Download(of, response.url);

						return true;
					}
				}
			}
		}

		return false;
	}
}