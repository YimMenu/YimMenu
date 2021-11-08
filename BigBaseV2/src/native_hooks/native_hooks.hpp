#pragma once
#include "natives.hpp"

namespace big::native_hook
{
	inline void NETWORK_CAN_BAIL(rage::scrNativeCallContext* src);
	inline void STAT_SET_INT(rage::scrNativeCallContext* src);
	inline void TRIGGER_SCRIPT_EVENT(rage::scrNativeCallContext* src);

	static std::unordered_map<rage::scrNativeHash, rage::scrNativeHandler> natives_replace =
	{
		{ 0x580CE4438479CC61, &NETWORK_CAN_BAIL },
		{ 0xB3271D7AB655B441, &STAT_SET_INT },
		{ 0x5AE99C571D5BBE5D, &TRIGGER_SCRIPT_EVENT }
	};
}