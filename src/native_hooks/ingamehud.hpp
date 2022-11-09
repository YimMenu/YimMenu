#pragma once
#include "native_hooks.hpp"
#include "natives.hpp"

namespace big
{
	namespace ingamehud
	{
		inline void SC_TRANSITION_NEWS_SHOW(rage::scrNativeCallContext* src)
		{
			if (g->tunables.fast_join)
			{
				LOG(INFO) << "SC_TRANSITION_NEWS_SHOW skipped";
				src->set_return_value<BOOL>(false);
			}
			else
			{
				src->set_return_value<BOOL>(SOCIALCLUB::SC_TRANSITION_NEWS_SHOW(src->get_arg<Any>(0)));
			}
		}

		inline void SC_TRANSITION_NEWS_SHOW_TIMED(rage::scrNativeCallContext* src)
		{
			if (g->tunables.fast_join)
			{
				LOG(INFO) << "SC_TRANSITION_NEWS_SHOW_TIMED skipped";
				src->set_return_value<BOOL>(false);
			}
			else
			{
				src->set_return_value<BOOL>(SOCIALCLUB::SC_TRANSITION_NEWS_SHOW_TIMED(src->get_arg<Any>(0), src->get_arg<Any>(0)));
			}
		}
	}
}