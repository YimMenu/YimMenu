#include "common.hpp"
#include "shv_runner.h"
#include "logger.hpp"
#include "natives.hpp"
#include "script.hpp"

namespace big
{
	void shv_runner::run_tick()
	{
		for (auto func : scripts)
		{
			func.second();
		}
	}

	void shv_runner::script_func()
	{
		while (g_running)
		{
			TRY_CLAUSE
			{
				run_tick();
			}EXCEPT_CLAUSE
			script::get_current()->yield();
		}
	}

	void shv_runner::shutdown()
	{
		for (auto & iter : big::shv_runner::scripts)
		{
			big::shv_runner::scripts.erase(iter.first);
			FreeLibrary(iter.first);
			CloseHandle(iter.first);
		}
	}
}
