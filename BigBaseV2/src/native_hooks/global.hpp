#pragma once
#include "native_hooks.hpp"
#include "natives.hpp"

namespace big
{
	namespace global_hooks
	{


		inline void SET_WARNING_MESSAGE_WITH_HEADER(rage::scrNativeCallContext* src)
		{
			const char* line1 = src->get_arg<char*>(1);
			const char* line2 = src->get_arg<char*>(2);
			g_notification_service->push_warning(src->get_arg<char*>(0), fmt::format("{} {}", line1, line2));
		}
	}
}