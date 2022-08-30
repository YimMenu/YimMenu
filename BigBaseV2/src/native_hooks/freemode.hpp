#pragma once
#include "native_hooks.hpp"
#include "natives.hpp"

namespace big
{
	namespace freemode
	{
		inline void NETWORK_BAIL(rage::scrNativeCallContext* src)
		{
			LOG(INFO) << "NETWORK_BAIL prevented";
		}
	}
}