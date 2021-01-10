#include "hooking.hpp"
#include "features.hpp"

namespace big
{
	bool hooks::read_session_response(uint64_t rcx)
	{
		bool bReturn = true;

		if (rcx && *(uint32_t*)(rcx + 0x23C4)) {
			uint32_t i = 0;
			do {
				uint64_t address = rcx + 0x22C0 + (i * 8);
				if (*(uint64_t*)(address)) {
					const char* responseData = *(const char**)(address);
					if (responseData) {
						try {
							nlohmann::json Json = nlohmann::json::parse(responseData);
							if (Json.find("gsinfo") == Json.end()) {
								return false;
							}

							uint64_t rockstar_id = std::stoul(Json["_id"].get<std::string>().substr(3));
							std::string gs_info_json = Json["gsinfo"].get<std::string>();

							features::notify::above_map("HOOK GOT DRIP.");

							LOG(INFO) << "Rockstar ID: " << rockstar_id;
							LOG(INFO) << "Data: ";
							LOG(INFO) << gs_info_json;
							LOG(INFO) << rockstar_id << " == " << g_rid_joiner.rid;

							if (rockstar_id == g_rid_joiner.rid) {
								if (gs_info_json.empty())
								{
									// PendingTimeout = 0;
								}
								else
								{
									g_rid_joiner.gs_info = gs_info_json;
								}

								bReturn = false;
							}
						}
						catch (...) {
							return false;
						}
					}
				}

				i++;
			} while (i < *(uint32_t*)(rcx + 0x23C4));
		}

		if (!bReturn) return false;
		return g_hooking->m_read_session_response.get_original<decltype(&hooks::read_session_response)>()(rcx);
	}
}