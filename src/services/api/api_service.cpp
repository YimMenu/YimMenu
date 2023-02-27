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
		cpr::Response response = cpr::Post(cpr::Url{"https://scui.rockstargames.com/api/friend/accountsearch"}, cpr::Header{{"Authorization", AUTHORIZATION_TICKET}, {"X-Requested-With", "XMLHttpRequest"}}, cpr::Body{{std::format("searchNickname={}", username)}});

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
		cpr::Response response = cpr::Post(cpr::Url{"https://scui.rockstargames.com/api/friend/getprofile"}, cpr::Header{{"Authorization", AUTHORIZATION_TICKET}, {"X-Requested-With", "XMLHttpRequest"}, {"Content-Type", "application/json"}}, cpr::Body{{std::format(R"({{"RockstarId":"{}"}})", rid)}});

		if (response.status_code == 200)
		{
			nlohmann::json obj = nlohmann::json::parse(response.text);
			result             = obj["Accounts"].at(0)["RockstarAccount"]["Name"];
			return true;
		}

		return false;
	}

	// Ratelimit: 10 per Minute, if exceeded than 5 min cooldown
	bool api_service::send_socialclub_message(uint64_t rid, std::string_view message)
	{
		cpr::Response response = cpr::Post(cpr::Url{"https://scui.rockstargames.com/api/messaging/sendmessage"}, cpr::Header{{"Authorization", AUTHORIZATION_TICKET}, {"X-Requested-With", "XMLHttpRequest"}, {"Content-Type", "application/json"}}, cpr::Body{{std::format(R"({{"env":"prod","title":"gta5","version":11,"recipientRockstarId":"{}","messageText":"{}"}})", rid, message)}});

		return response.status_code == 200;
	}

	bool api_service::get_job_details(std::string_view content_id, nlohmann::json& result)
	{
		cpr::Response response = cpr::Get(cpr::Url{"https://scapi.rockstargames.com/ugc/mission/details"},
		    cpr::Header{{"X-AMC", "true"}, {"X-Requested-With", "XMLHttpRequest"}},
		    cpr::Parameters{{"title", "gtav"}, {"contentId", content_id.data()}});

		result = nlohmann::json::parse(response.text);

		return response.status_code == 200;
	}

	bool api_service::download_job_metadata(std::string_view content_id, int f1, int f0, int lang)
	{
		cpr::Response response = cpr::Get(cpr::Url{std::format("https://prod.cloud.rockstargames.com/ugc/gta5mission/{}/{}_{}_{}.json",
		    content_id,
		    f1,
		    f0,
		    languages.at(lang))});

		if (response.status_code == 200)
		{
			std::ofstream of = creator_storage_service::create_file(std::string(content_id) + ".json");
			cpr::Response r  = cpr::Download(of, response.url);

			return true;
		}

		return false;
	}
}