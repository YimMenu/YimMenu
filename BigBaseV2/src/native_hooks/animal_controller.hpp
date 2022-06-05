#pragma once
#include "native_hooks.hpp"
#include "natives.hpp"

namespace big
{
	namespace animal_controller
	{
		inline void NETWORK_IS_GAME_IN_PROGRESS(rage::scrNativeCallContext* src)
		{
			LOG(INFO) << "online false";
			src->set_return_value<BOOL>(0);
		}
	}
}