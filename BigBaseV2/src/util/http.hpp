#pragma once
#include <httplib.h>
#include <url.hpp>

namespace big::web
{
	template <class Rep, class Period>
	inline httplib::Result get(const std::string_view url, const std::chrono::duration<Rep, Period>& timeout)
	{
		Url copy(url.data());
		const auto path = copy.path();

		copy.fragment("");
		copy.path("");

		httplib::Client cli(copy.str());

		cli.enable_server_certificate_verification(false);
		cli.set_connection_timeout(2);
		cli.set_read_timeout(timeout);

		return cli.Get(path.c_str());
	}
}