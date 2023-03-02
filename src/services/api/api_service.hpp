#pragma once
#include "pointers.hpp"

#include <cpr/cpr.h>
#define AUTHORIZATION_TICKET std::format("SCAUTH val=\"{}\"", get_ticket())

namespace big
{
	class api_service
	{
	public:
		api_service();
		~api_service();

		// Returns true if an valid profile matching his username has been found
		bool get_rid_from_username(std::string_view username, uint64_t& result);

		// Returns true if an valid profile matching his rid has been found
		bool get_username_from_rid(uint64_t rid, std::string& result);

		// Returns true if the message has been successfully sended to the target
		bool send_socialclub_message(uint64_t rid, std::string_view message);

		// Returns true if the job data query was successfully
		bool get_job_details(std::string_view job_link, nlohmann::json& result);

		// Returns true if the job metadata was successfully downloaded
		bool download_job_metadata(std::string_view content_id, int f1, int f0, int lang);

	private:
		const std::vector<std::string> languages = {"unset", "en", "fr", "de", "it", "es", "pt", "pl", "ru", "es-mx"};

		inline std::string get_ticket()
		{
			return g_pointers->m_sc_info->m_ticket;
		}
	};

	inline api_service* g_api_service;
}