#include "backend/looped/looped.hpp"
#include "pointers.hpp"
#include "CPedFactory.hpp"

namespace big
{
	//static std::vector<std::pair<uint32_t, float>> og_spread_values{};
	//static uint32_t prev_weapon_hash{};

	//auto is_spread_value_cached(uint32_t hash)
	//{
	//	return std::find_if(og_spread_values.begin(), og_spread_values.end(), [hash](auto const entry)
	//		{
	//			return hash == entry.first;
	//		}) != og_spread_values.end();
	//}

	//float get_og_spread_value(uint32_t hash)
	//{
	//	return std::find_if(og_spread_values.begin(), og_spread_values.end(), [hash](auto const entry)
	//		{
	//			return hash == entry.first;
	//		})->second;
	//}

	//auto get_spread_value(uint32_t hash)
	//{
	//	return g->weapons.no_spread
	//		? 0.f
	//		: get_og_spread_value(hash);
	//}

	void looped::weapons_no_spread()
	{
		auto* const weapon_mgr = (*g_pointers->m_ped_factory)->m_local_ped->m_weapon_manager;
		if (weapon_mgr)
		{
			weapon_mgr->m_weapon_info->m_spread = 0.f;
			//auto const cur_weapon_hash = weapon_mgr->m_selected_weapon_hash;
			//if (prev_weapon_hash != cur_weapon_hash)
			//{
			//	if (!is_spread_value_cached(cur_weapon_hash))
			//	{
			//		og_spread_values.push_back({ cur_weapon_hash, weapon_mgr->m_weapon_info->m_spread });
			//	}

			//	weapon_mgr->m_weapon_info->m_spread = 0.f; //get_spread_value(cur_weapon_hash);
			//}
		}
	}
}