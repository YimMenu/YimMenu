#include "api_service.hpp"
#include "pointers.hpp"

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
			cpr::Header{ {"Authorization", AUTHORIZATION_TICKET) }, { "X-Requested-With", "XMLHttpRequest"}},
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
			cpr::Header{ {"Authorization", AUTHORIZATION_TICKET) }, { "X-Requested-With", "XMLHttpRequest"}, {"Content-Type", "application/json"} },
			cpr::Body{ { std::format(R"({{"RockstarId":"{}"}})", rid) } });

		if (response.status_code == 200) 
		{
			nlohmann::json obj = nlohmann::json::parse(response.text);
			result = obj["Accounts"].at(0)["RockstarAccount"]["Name"];
			return true;
		}

		return false;
	}

	bool api_service::send_socialclub_message(uint64_t rid, std::string_view message)
	{
		cpr::Response response = cpr::Post(
			cpr::Url{ "https://scui.rockstargames.com/api/messaging/sendmessage" },
			cpr::Header{ {"Authorization", AUTHORIZATION_TICKET) }, { "X-Requested-With", "XMLHttpRequest"}, {"Content-Type", "application/json"} },
			cpr::Body{ { std::format(R"({{"env":"prod","title":"gta5","version":11,"recipientRockstarId":"{}","messageText":"{}"}})", rid, message) } });

		return response.status_code == 200;
	}
}