#include "hooking.hpp"
#include "native_hooks/native_hooks.hpp"
#include "services/script_patcher/script_patcher_service.hpp"

namespace big
{
	bool hooks::init_native_tables(rage::scrProgram* program)
	{
		bool ret = g_hooking->get_original<hooks::init_native_tables>()(program);
		g_script_patcher_service->on_script_load(program);
		g_native_hooks->hook_program(program);

		return ret;
	}
}