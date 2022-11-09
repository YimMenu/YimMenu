#pragma once

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