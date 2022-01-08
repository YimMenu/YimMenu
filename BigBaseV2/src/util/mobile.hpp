#pragma once
#include "core/enums.hpp"
#include "gta_util.hpp"
#include "misc.hpp"
#include "natives.hpp"
#include "script.hpp"
#include "script_global.hpp"
#include "script_local.hpp"

namespace big::mobile
{
	inline auto player_global = script_global(2689156);
	inline auto mechanic_global = script_global(2810287);
	inline auto vehicle_global = script_global(1585844);

	namespace util
	{
		int get_current_personal_vehicle(); // forward declare
		inline void despawn_current_personal_vehicle()
		{
			misc::clear_bits(
				vehicle_global.at(get_current_personal_vehicle(), 142).at(103).as<int*>(),
				eVehicleFlags::TRIGGER_SPAWN_TOGGLE | eVehicleFlags::UNK2
			);
		}

		inline int get_current_personal_vehicle()
		{
			return *script_global(2359296).at(0, 5559).at(675).at(2).as<int*>();
		}
	}

	namespace lester
	{
		inline void off_radar(bool toggle)
		{
			*player_global.at(PLAYER::GET_PLAYER_INDEX(), 453).at(209).as<int*>() = toggle;
			*script_global(2703656).at(70).as<int*>() = NETWORK::GET_NETWORK_TIME() + 1;
		}
	}

	namespace mors_mutual
	{
		bool fix_index(int veh_idx);
	}
	namespace mechanic
	{
		inline void summon_vehicle_by_index(int veh_idx)
		{
			// despawn current veh
			util::despawn_current_personal_vehicle();
			mors_mutual::fix_index(veh_idx);

			script::get_current()->yield(100ms);

			*mechanic_global.at(911).as<int*>() = 1;
			*mechanic_global.at(961).as<int*>() = 0;
			*mechanic_global.at(958).as<int*>() = veh_idx;

			script::get_current()->yield(100ms);

			GtaThread* freemode_thread = gta_util::find_script_thread(RAGE_JOAAT("freemode"));
			if (freemode_thread)
				*script_local(freemode_thread, 17437).at(176).as<int*>() = 0; // spawn vehicle instantly
		}
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
					eVehicleFlags::TRIGGER_SPAWN_TOGGLE | eVehicleFlags::UNK2
				);
			}
			return can_be_fixed;
		}
	}
}