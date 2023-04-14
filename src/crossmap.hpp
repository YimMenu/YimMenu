#pragma once
#include "gta/natives.hpp"

namespace big
{
	constexpr auto NATIVE_COUNT = 6494;
	using crossmap              = std::array<std::pair<rage::scrNativeHash, rage::scrNativeHash>, NATIVE_COUNT>;
	extern const crossmap g_crossmap;
}
