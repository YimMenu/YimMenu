#pragma once

#include <nlohmann/json.hpp>

namespace big
{
	struct color
	{
		int r;
		int g;
		int b;
		int a;
	};
	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(color, r, g, b, a)
}