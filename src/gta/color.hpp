#pragma once
#include <cstdint>

namespace rage
{
	struct rgbaColor
	{
		rgbaColor(uint8_t r = 0, uint8_t g = 0, uint8_t b = 0, uint8_t a = 255) :
		    r(r),
		    g(g),
		    b(b),
		    a(a)
		{
		}

		uint8_t r;
		uint8_t g;
		uint8_t b;
		uint8_t a;
	};

	static_assert(sizeof(rgbaColor) == sizeof(uint8_t) * 4);
}
