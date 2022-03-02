#include "pointers.hpp"
#include "CPedFactory.hpp"
#include "backend/looped/looped.hpp"

namespace big
{
	static std::vector<std::pair<uint32_t, float>> og_recoil_values{};
	static uint32_t prev_weapon_hash{};

	auto is_recoil_value_cached(uint32_t hash)
	{
		return std::find_if(og_recoil_values.begin(), og_recoil_values.end(), [hash](auto const entry)
			{
				return hash == entry.first;
			}) != og_recoil_values.end();
	}

	float get_og_recoil_value(uint32_t hash)
	{
		return std::find_if(og_recoil_values.begin(), og_recoil_values.end(), [hash](auto const entry)
			{
				return hash == entry.first;
			})->second;
	}

	auto get_recoil_value(uint32_t hash)
	{
		return g->weapons.no_recoil
			? 0.f
			: get_og_recoil_value(hash);
	}

	void looped::weapons_no_recoil()
	{
		auto* const weapon_mgr = (*g_pointers->m_ped_factory)->m_local_ped->m_weapon_manager;
		if (weapon_mgr)
		{
			auto const cur_weapon_hash = weapon_mgr->m_selected_weapon_hash;
			if (prev_weapon_hash != cur_weapon_hash)
			{
				if (!is_recoil_value_cached(cur_weapon_hash))
				{
					og_recoil_values.push_back({ cur_weapon_hash, weapon_mgr->m_weapon_info->m_accuracy_recoil });
				}
				
				weapon_mgr->m_weapon_info->m_accuracy_recoil = get_recoil_value(cur_weapon_hash);
			}
		}
	}
}