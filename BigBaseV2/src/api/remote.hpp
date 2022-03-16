#pragma once
#include "api/http_request.hpp"

namespace big::remote
{
	inline bool download_binary(const std::string_view file_url, const std::filesystem::path& location)
	{
		std::ofstream file(location, std::ios::binary | std::ios::trunc);

		try
		{
			http::Request req(file_url.data());
			http::Response res = req.send("GET", "", {}, 10s);

			std::ostream_iterator<std::uint8_t> outputIter(file);
			std::copy(res.body.begin(), res.body.end(), outputIter);
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