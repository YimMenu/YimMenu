#pragma once
#include "api/http_request.hpp"

namespace big::remote
{
	inline std::string get_etag_from_headers(std::vector<std::string> headers)
	{
		std::string remote_etag = "";

		for (auto& header : headers)
		{
			if (header.rfind("ETag", 0) == 0)
			{
				remote_etag = header;
				break;
			}
		}

		return remote_etag;
	}


	inline bool update_binary(const std::string_view file_url, const std::filesystem::path& file_location, const std::filesystem::path& etag_location)
	{
		try
		{
			std::string local_etag = "";
			std::string remote_etag = "";

			const std::vector<std::string> headers = { "User-Agent: Mozilla/5.0 (Windows; U; Windows NT 6.1; en-US) AppleWebKit/533.2 (KHTML, like Gecko) Chrome/6.0" };

			try {

				{
					std::ifstream file_etag_ifstream(etag_location, std::ios::binary);
					std::stringstream file_etag_stringstream;
					file_etag_stringstream << file_etag_ifstream.rdbuf();
					local_etag = file_etag_stringstream.str();
				}

				if (!local_etag.empty())
				{
					http::Request req(file_url.data());
					http::Response res = req.send("HEAD", "", headers, 15s);

					remote_etag = get_etag_from_headers(res.headers);

					if (remote_etag == local_etag)
					{
						return false;
					}
				}
			}
			catch (const std::exception& e)
			{
				LOG(INFO) << "Update Error: " << e.what();
			}

			http::Request req(file_url.data());
			http::Response res = req.send("GET", "", headers, 30s);

			std::ofstream file_ofstream(file_location, std::ios::binary | std::ios::trunc);
			std::ostream_iterator<std::uint8_t> file_out_iter(file_ofstream);
			std::copy(res.body.begin(), res.body.end(), file_out_iter);

			remote_etag = get_etag_from_headers(res.headers);

			std::ofstream file_etag_ofstream(etag_location, std::ios::binary | std::ios::trunc);
			file_etag_ofstream << remote_etag;

			return true;
		}
		catch (const std::exception& e)
		{
			LOG(INFO) << "Failed to download binary, is the host down?: " << e.what();
		}

		return false;
	}
}