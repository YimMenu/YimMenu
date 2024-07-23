#include "hooking/hooking.hpp"

namespace big
{
	static auto get_hash(const std::string& str)
	{
		rage::joaat_t hash = 0;
		if (str.substr(0, 2) == "0x")
			std::stringstream(str.substr(2)) >> std::hex >> hash;
		else
			hash = rage::joaat(str.c_str());
		return hash;
	}

	static std::vector<std::pair<rage::joaat_t, rage::joaat_t>> cache_models;

	static void update()
	{
		std::lock_guard lock(g.world.model_swapper.m);
		cache_models.clear();
		for (size_t i = 0; i < g.world.model_swapper.models.size(); i++)
			cache_models.push_back(
			    std::make_pair(get_hash(g.world.model_swapper.models[i].first), get_hash(g.world.model_swapper.models[i].second)));
		g.world.model_swapper.update = false;
	}

	CBaseModelInfo* hooks::get_model_info(rage::joaat_t hash, uint32_t* a2)
	{
		static bool init = ([] { update(); }(), true);
		if (g.world.model_swapper.update)
			update();
		for (size_t i = 0; i < cache_models.size(); i++)
			if (cache_models[i].first == hash)
				return g_hooking->get_original<get_model_info>()(cache_models[i].second, a2);
		return g_hooking->get_original<get_model_info>()(hash, a2);
	}
}
