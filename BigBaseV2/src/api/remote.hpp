#pragma once
#include "util/http.hpp"

namespace big::remote
{
	inline bool download_binary(const std::string_view file_url, const std::filesystem::path& location)
	{
		std::ofstream file(location, std::ios::binary | std::ios::trunc);

		try
		{
			auto result = web::get(file_url, 10s);
			file << result->body;
		}
		catch (const std::exception& e)
		{
			LOG(INFO) << "Failed to download binary, is the host down?: " << e.what();

			file.close();

			return false;
		}
		file.close();

		return true;
	}
}