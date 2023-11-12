#include "hooking.hpp"

namespace big
{
	static std::vector<std::pair<rage::joaat_t, rage::joaat_t>> cache_models;

	CBaseModelInfo* hooks::get_model_info(rage::joaat_t hash, uint32_t* a2)
	{
		for (size_t i = 0; i < cache_models.size(); i++)
			if (cache_models[i].first == hash)
				return g_hooking->get_original<get_model_info>()(cache_models[i].second, a2);
		return g_hooking->get_original<get_model_info>()(hash, a2);
	}
}
