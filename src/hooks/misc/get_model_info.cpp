#include "hooking.hpp"
#include "util/model_info.hpp"

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

	CBaseModelInfo* hooks::get_model_info(rage::joaat_t hash, uint32_t* a2)
	{
		for (size_t i = 0; i < g.world.model_swapper.models.size(); i++)
		{
			rage::joaat_t first = get_hash(g.world.model_swapper.models[i].first);
			if(hash == first)
				return g_hooking->get_original<get_model_info>()(get_hash(g.world.model_swapper.models[i].second), a2);
		}
		return g_hooking->get_original<get_model_info>()(hash, a2);
	}
}
