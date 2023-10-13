#pragma once
#include <atomic>

#define TYPING_TICKS 3

namespace big
{
	inline struct g_hud
	{
		std::atomic_uint_fast8_t typing = 0;
	} g_hud{};
}