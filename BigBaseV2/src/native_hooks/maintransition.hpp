#pragma once
#include "native_hooks.hpp"
#include "script_global.hpp"

namespace big
{
	namespace maintransition
	{
		inline void SWITCH_OUT_PLAYER_(rage::scrNativeCallContext* src)
		{
			LOG(INFO) << "Player Switch prevented";
		}
	}
}