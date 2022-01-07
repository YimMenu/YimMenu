#pragma once
#include "core/enums.hpp"
#include "script_global.hpp"
#include "misc.hpp"
#include "natives.hpp"

namespace big::mobile
{
	inline auto player_global = script_global(2689156);
	inline auto vehicle_global = script_global(1585844);

	namespace lester
	{
		inline void off_radar(bool toggle)
		{
			*player_global.at(PLAYER::GET_PLAYER_INDEX(), 453).at(209).as<int*>() = toggle;
			*script_global(2703656).at(70).as<int*>() = NETWORK::GET_NETWORK_TIME() + 1;
		}
	}

	namespace mechanic
	{

	}

	namespace mors_mutual
	{
		bool fix_index(int veh_idx); // forward declare func
		inline int fix_all()
		{
			int fixed_count = 0;

			for (int i = 0; i < *vehicle_global.as<int*>(); i++)
				if (fix_index(i))
					fixed_count++;

			return fixed_count;
		}

		inline bool fix_index(int veh_idx)
		{
			bool can_be_fixed = misc::has_bits_set(
				vehicle_global.at(veh_idx, 142).at(103).as<int*>(),
				eVehicleFlags::DESTROYED | eVehicleFlags::HAS_INSURANCE
			);

			if (can_be_fixed)
			{
				misc::clear_bits(
					vehicle_global.at(veh_idx, 142).at(103).as<int*>(),
					eVehicleFlags::DESTROYED | eVehicleFlags::IMPOUNDED | eVehicleFlags::UNK3
				);
				misc::set_bits(
					vehicle_global.at(veh_idx, 142).at(103).as<int*>(),
					eVehicleFlags::UNK0 | eVehicleFlags::UNK2
				);
			}
			return can_be_fixed;
		}
	}
}