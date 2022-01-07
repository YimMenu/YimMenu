#pragma once
#include "common.hpp"

namespace big::shv_runner
{
	void run_tick();
	void script_func();
	void shutdown();

	inline std::map<HMODULE, void(*)()> scripts;
}
