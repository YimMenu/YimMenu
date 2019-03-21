#pragma once
#include <cstdint>

namespace rage
{
	struct rgbaColor
	{
		rgbaColor(std::uint8_t r = 0, std::uint8_t g = 0, std::uint8_t b = 0, std::uint8_t a = 255) :
			r(r), g(g), b(b), a(a)
		{}

		std::uint8_t r;
		std::uint8_t g;
		std::uint8_t b;
		std::uint8_t a;
	};
	
	static_assert(sizeof(rgbaColor) == sizeof(std::uint8_t) * 4);
}
