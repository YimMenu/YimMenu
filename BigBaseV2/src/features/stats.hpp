#pragma once
#include "natives.hpp"
#include "script.hpp"
#include "fiber_pool.hpp"

namespace big::features
{
	class stats
	{
	public:
		static void unlock_all();
	};
}