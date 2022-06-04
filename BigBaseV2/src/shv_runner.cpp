#include "common.hpp"
#include "script.hpp"
#include "shv_runner.hpp"

namespace big
{
	void shv_runner::run_tick()
	{
		for (const auto& func : scripts)
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
		for (const auto& iter : scripts)
		{
			scripts.erase(iter.first);
			FreeLibrary(iter.first);
			CloseHandle(iter.first);
		}
	}
}