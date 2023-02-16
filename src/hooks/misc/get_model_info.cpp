#include "hooking.hpp"
#include "util/model_info.hpp"

namespace big
{
	CBaseModelInfo* hooks::get_model_info(rage::joaat_t hash, int* a2)
	{

		return g_hooking->get_original<get_model_info>()(hash, a2);
	}
}
