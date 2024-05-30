#pragma once

namespace big
{
	namespace am_launcher
	{
		static void START_NEW_SCRIPT_WITH_ARGS(rage::scrNativeCallContext* src)
		{
			const char* const name = src->get_arg<const char*>(0);

			Any* args            = src->get_arg<Any*>(1);
			const int argc       = src->get_arg<int>(2);
			const int stackSize  = src->get_arg<int>(3);

			src->set_return_value<int>(SYSTEM::START_NEW_SCRIPT_WITH_ARGS(name, args, argc, stackSize));
		}
	}
}
