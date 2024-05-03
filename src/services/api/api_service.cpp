#include "api_service.hpp"

#include "http_client/http_client.hpp"
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

	std::string api_service::get_translation_from_LibreTranslate(std::string message, std::string target_language)
	{
		std::string url = g.session.chat_translator_endpoint;
		const auto response = g_http_client.post(url,
		    {{"Content-Type", "application/json"}}, std::format(R"({{"q":"{}", "source":"auto", "target": "{}"}})", message, target_language));
		if (response.status_code == 200)
		{
			try
			{
				nlohmann::json obj = nlohmann::json::parse(response.text);
				std::string source_language = obj["detectedLanguage"]["language"];
				std::string result = obj["translatedText"];
				
				if (source_language == g.session.chat_translator_target && g.session.chat_translator_bypass)
					return "";
				return result;
			}
			catch (std::exception& e)
			{
				g_notification_service.push_error("END_KICK"_T.data(),
				    "BACKEND_END_SESSION_KICK_FORCE_SCRIPT_HOST_FAILED"_T.data());

				LOG(WARNING) << "[Chat Translator]Error when parse JSON data: " << e.what();
			}
		}
		else if (response.status_code == 0)
		{
			g.session.chat_translator = false;
			g_notification_service.push_error("Chat Translator", "Cannot reach LibreTranslate server.\nRead cout.log for details");
			LOG(WARNING) << "[Chat Translator]Cannot reach LibreTranslate server. Follow the guide in Yimmenu Wiki to setup LibreTranslate server on your computer.";
		}
		else
		{
			LOG(WARNING) << "[Chat Translator]Error when sending request. Status code: " << response.status_code << " Response: " << response.text;
		}
		
		return "";
	}

	bool api_service::get_rid_from_username(std::string_view username, uint64_t& result)
	{
		const auto response = g_http_client.post("https://scui.rockstargames.com/api/friend/accountsearch", {{"Authorization", AUTHORIZATION_TICKET}, {"X-Requested-With", "XMLHttpRequest"}}, {std::format("searchNickname={}", username)});
		if (response.status_code == 200)
		{
			try
			{
				nlohmann::json obj = nlohmann::json::parse(response.text);

				if (obj["Total"] > 0 && username.compare(obj["Accounts"].at(0)["Nickname"]) == 0)
				{
					result = obj["Accounts"].at(0)["RockstarId"];
					return true;
				}
			}
			catch (std::exception& e)
			{
				return false;
			}
		}

		return false;
	}

	bool api_service::get_username_from_rid(uint64_t rid, std::string& result)
	{
		const auto response = g_http_client.post("https://scui.rockstargames.com/api/friend/getprofile", {{"Authorization", AUTHORIZATION_TICKET}, {"X-Requested-With", "XMLHttpRequest"}, {"Content-Type", "application/json"}}, std::format(R"({{"RockstarId":"{}"}})", rid));
		if (response.status_code == 200)
		{
			try
			{
				nlohmann::json obj = nlohmann::json::parse(response.text);
				result             = obj["Accounts"].at(0)["RockstarAccount"]["Name"];
				return true;
			}
			catch (std::exception& e)
			{
				return false;
			}
		}

		return false;
	}

	// Ratelimit: 10 per Minute, if exceeded than 5 min cooldown
	bool api_service::send_socialclub_message(uint64_t rid, std::string_view message)
	{
		const auto response = g_http_client.post("https://scui.rockstargames.com/api/messaging/sendmessage", {{"Authorization", AUTHORIZATION_TICKET}, {"X-Requested-With", "XMLHttpRequest"}, {"Content-Type", "application/json"}}, {std::format(R"({{"env":"prod","title":"gta5","version":11,"recipientRockstarId":"{}","messageText":"{}"}})", rid, message)});

		return response.status_code == 200;
	}

	bool api_service::get_job_details(std::string_view content_id, nlohmann::json& result)
	{
		const auto response = g_http_client.get("https://scapi.rockstargames.com/ugc/mission/details",
		    {{"X-AMC", "true"}, {"X-Requested-With", "XMLHttpRequest"}},
		    {{"title", "gtav"}, {"contentId", content_id.data()}});

		if (response.status_code != 200)
			return false;

		try
		{
			result = nlohmann::json::parse(response.text);
			return true;
		}
		catch (std::exception& e)
		{
			return false;
		}
	}

	bool api_service::download_job_metadata(std::string_view content_id, int f1, int f0, int lang)
	{
		const auto response = g_http_client.get(std::format("https://prod.cloud.rockstargames.com/ugc/gta5mission/{}/{}_{}_{}.json",
		    content_id,
		    f1,
		    f0,
		    languages.at(lang)));

		if (response.status_code == 200)
		{
			const auto of = creator_storage_service::create_file(std::string(content_id) + ".json");

			return g_http_client.download(response.url, of);
		}

		return false;
	}
}