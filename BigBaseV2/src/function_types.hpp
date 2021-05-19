#pragma once
#include "common.hpp"
#include "gta/fwddec.hpp"
#include "gta/natives.hpp"

namespace big::functions
{
	using run_script_threads_t = bool(*)(std::uint32_t ops_to_execute);
	using get_native_handler_t = rage::scrNativeHandler(*)(rage::scrNativeRegistrationTable*, rage::scrNativeHash);
	using fix_vectors_t = void(*)(rage::scrNativeCallContext*);

	using gta_thread_tick = __int64(GtaThread* a1, unsigned int a2);
	using gta_thread_kill = __int64(GtaThread* a1);

	using increment_stat_event = bool(uint64_t net_event_struct, int64_t sender, int64_t a3);
}
