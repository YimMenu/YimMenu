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

		inline void NETWORK_HAS_RECEIVED_HOST_BROADCAST_DATA(rage::scrNativeCallContext* src)
		{
			if (g->tunables.fast_join)
			{
				LOG(G3LOG_DEBUG) << "NETWORK_HAS_RECEIVED_HOST_BROADCAST_DATA skipped";
				src->set_return_value<BOOL>(TRUE);
			}
			else
			{
				src->set_return_value<BOOL>(NETWORK::NETWORK_HAS_RECEIVED_HOST_BROADCAST_DATA());
			}
		}
	}
}