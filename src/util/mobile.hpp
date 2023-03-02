#pragma once
#include "core/enums.hpp"
#include "core/scr_globals.hpp"
#include "globals.hpp"
#include "gta_util.hpp"
#include "misc.hpp"
#include "natives.hpp"
#include "notify.hpp"
#include "script.hpp"
#include "script_global.hpp"
#include "script_local.hpp"
#include "vehicle.hpp"

namespace big::mobile
{
	inline auto player_global = script_global(2657589);

	namespace util
	{
		int get_current_personal_vehicle();// forward declare
		inline void despawn_current_personal_vehicle()
		{
			misc::clear_bits(scr_globals::vehicle_global.at(get_current_personal_vehicle(), 142).at(103).as<int*>(), eVehicleFlags::TRIGGER_SPAWN_TOGGLE);
		}

		inline int get_current_personal_vehicle()
		{
			return *script_global(2359296).at(0, 5568).at(681).at(2).as<int*>();
		}
	}

	namespace merry_weather
	{
		inline void request_ammo_drop()
		{
			*script_global(scr_globals::mechanic_global).at(886).as<int*>() = 1;
		}

		inline void request_boat_pickup()
		{
			*script_global(scr_globals::mechanic_global).at(887).as<int*>() = 1;
		}

		inline void request_helicopter_pickup()
		{
			*script_global(scr_globals::mechanic_global).at(888).as<int*>() = 1;
		}

		inline void request_backup_helicopter()
		{
			*script_global(scr_globals::mechanic_global).at(4484).as<int*>() = 1;
		}

		inline void request_airstrike()
		{
			*script_global(scr_globals::mechanic_global).at(4485).as<int*>() = 1;
		}


	}

	namespace mors_mutual
	{
		inline bool fix_index(int veh_idx, bool spawn_veh = false)
		{
			bool can_be_fixed = misc::has_bits_set(scr_globals::vehicle_global.at(veh_idx, 142).at(103).as<int*>(), eVehicleFlags::DESTROYED | eVehicleFlags::HAS_INSURANCE);

			if (can_be_fixed)
			{
				misc::clear_bits(scr_globals::vehicle_global.at(veh_idx, 142).at(103).as<int*>(), eVehicleFlags::DESTROYED | eVehicleFlags::IMPOUNDED | eVehicleFlags::UNK2);

				if (spawn_veh)
				{
					misc::set_bits(scr_globals::vehicle_global.at(veh_idx, 142).at(103).as<int*>(), eVehicleFlags::TRIGGER_SPAWN_TOGGLE | eVehicleFlags::SPAWN_AT_MORS_MUTUAL);
				}
			}
			return can_be_fixed;
		}

		inline int fix_all()
		{
			int fixed_count = 0;

			const int arr_size = *scr_globals::vehicle_global.as<int*>();
			for (int i = 0; i < arr_size; i++)
				if (fix_index(i, true))
					fixed_count++;

			return fixed_count;
		}
	}

	namespace ceo_abilities
	{
		inline void request_bullshark_testosterone()
		{
			*script_global(2672505).at(3689).as<int*>() = 1;
		}

		inline void request_ballistic_armor()//i think this is a ceo ability atleast?
		{
			*script_global(scr_globals::mechanic_global).at(896).as<int*>() = 1;
		}
	}

	namespace mechanic
	{
		inline Vehicle get_personal_vehicle()
		{
			return *scr_globals::mechanic_global.at(299).as<Vehicle*>();
		}

		inline void summon_vehicle_by_index(int veh_idx)
		{
			if (*scr_globals::mechanic_global.at(979).as<int*>() != -1)
				return g_notification_service->push_warning("Vehicle", "Mechanic is not ready to deliver a vehicle right now.");

			if (g.clone_pv.spawn_inside && self::veh)
				TASK::CLEAR_PED_TASKS_IMMEDIATELY(PLAYER::PLAYER_PED_ID());

			// despawn current veh
			util::despawn_current_personal_vehicle();
			mors_mutual::fix_index(veh_idx);

			script::get_current()->yield(100ms);

			// only do this when spawn inside is enabled otherwise the vehicle will spawn relatively far away from players
			if (g.clone_pv.spawn_inside)
			{
				*scr_globals::mechanic_global.at(936).as<int*>() = 1;// disable vehicle node distance check
			}
			*scr_globals::mechanic_global.at(923).as<int*>() = 1;// tell freemode to spawn our vehicle
			*scr_globals::mechanic_global.at(982).as<int*>() = 0;// required
			*scr_globals::mechanic_global.at(979).as<int*>() = veh_idx;

			script::get_current()->yield(100ms);

			GtaThread* freemode_thread = gta_util::find_script_thread(RAGE_JOAAT("freemode"));
			if (freemode_thread)
				*script_local(freemode_thread, 18630).at(176).as<int*>() = 0;// spawn vehicle instantly

			// blocking call till vehicle is delivered
			notify::busy_spinner("Delivering vehicle...", scr_globals::mechanic_global.at(979).as<int*>(), -1);

			if (g.clone_pv.spawn_inside)
			{
				big::vehicle::bring(get_personal_vehicle(), self::pos, true);
			}
		}
	}
}