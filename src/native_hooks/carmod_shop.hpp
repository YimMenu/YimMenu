#pragma once
#include "native_hooks.hpp"
#include "natives.hpp"

namespace big
{
	namespace carmod_shop
	{
		inline void STAT_GET_INT(rage::scrNativeCallContext* src)
		{
			const auto hash = src->get_arg<Hash>(0);
			int* out        = src->get_arg<int*>(1);
			src->set_return_value<BOOL>(1);

			switch (hash)
			{
			case RAGE_JOAAT("MP0_RACES_WON"):
			case RAGE_JOAAT("MP0_NUMBER_TURBO_STARTS_IN_RACE"):
			case RAGE_JOAAT("MP0_USJS_COMPLETED"):
			case RAGE_JOAAT("MP0_AWD_FM_RACES_FASTEST_LAP"):
			case RAGE_JOAAT("MP1_RACES_WON"):
			case RAGE_JOAAT("MP1_NUMBER_TURBO_STARTS_IN_RACE"):
			case RAGE_JOAAT("MP1_USJS_COMPLETED"):
			case RAGE_JOAAT("MP1_AWD_FM_RACES_FASTEST_LAP"): *out = 50; break;
			case RAGE_JOAAT("MP0_NUMBER_SLIPSTREAMS_IN_RACE"):
			case RAGE_JOAAT("MP1_NUMBER_SLIPSTREAMS_IN_RACE"): *out = 100; break;
			case RAGE_JOAAT("MP0_CHAR_FM_CARMOD_1_UNLCK"):
			case RAGE_JOAAT("MP0_CHAR_FM_CARMOD_2_UNLCK"):
			case RAGE_JOAAT("MP0_CHAR_FM_CARMOD_3_UNLCK"):
			case RAGE_JOAAT("MP0_CHAR_FM_CARMOD_4_UNLCK"):
			case RAGE_JOAAT("MP0_CHAR_FM_CARMOD_5_UNLCK"):
			case RAGE_JOAAT("MP0_CHAR_FM_CARMOD_6_UNLCK"):
			case RAGE_JOAAT("MP0_CHAR_FM_CARMOD_7_UNLCK"):
			case RAGE_JOAAT("MP1_CHAR_FM_CARMOD_1_UNLCK"):
			case RAGE_JOAAT("MP1_CHAR_FM_CARMOD_2_UNLCK"):
			case RAGE_JOAAT("MP1_CHAR_FM_CARMOD_3_UNLCK"):
			case RAGE_JOAAT("MP1_CHAR_FM_CARMOD_4_UNLCK"):
			case RAGE_JOAAT("MP1_CHAR_FM_CARMOD_5_UNLCK"):
			case RAGE_JOAAT("MP1_CHAR_FM_CARMOD_6_UNLCK"):
			case RAGE_JOAAT("MP1_CHAR_FM_CARMOD_7_UNLCK"): *out = -1; break;
			case RAGE_JOAAT("MP0_AWD_FMRALLYWONDRIVE"):
			case RAGE_JOAAT("MP0_AWD_FMRALLYWONNAV"):
			case RAGE_JOAAT("MP0_AWD_FMWINSEARACE"):
			case RAGE_JOAAT("MP0_AWD_FMWINAIRRACE"):
			case RAGE_JOAAT("MP1_AWD_FMRALLYWONDRIVE"):
			case RAGE_JOAAT("MP1_AWD_FMRALLYWONNAV"):
			case RAGE_JOAAT("MP1_AWD_FMWINSEARACE"):
			case RAGE_JOAAT("MP1_AWD_FMWINAIRRACE"): *out = 1; break;
			case RAGE_JOAAT("SP0_TOTAL_CASH"):
			case RAGE_JOAAT("SP1_TOTAL_CASH"):
			case RAGE_JOAAT("SP2_TOTAL_CASH"): *out = 999999; break;
			default: src->set_return_value<BOOL>(STATS::STAT_GET_INT(hash, out, src->get_arg<int>(2))); break;
			}
		}

		inline void STAT_SET_INT(rage::scrNativeCallContext* src)
		{
			const auto hash = src->get_arg<Hash>(0);
			if (hash == RAGE_JOAAT("SP0_TOTAL_CASH") || hash == RAGE_JOAAT("SP1_TOTAL_CASH") || hash == RAGE_JOAAT("SP2_TOTAL_CASH"))
				return;

			src->set_return_value<BOOL>(STATS::STAT_SET_INT(hash, src->get_arg<int>(1), src->get_arg<int>(2)));
		}

		inline void SET_ENTITY_COORDS(rage::scrNativeCallContext* src)
		{
			if (!g.vehicle.ls_customs)
			{
				ENTITY::SET_ENTITY_COORDS(src->get_arg<Entity>(0), src->get_arg<float>(1), src->get_arg<float>(2), src->get_arg<float>(3), src->get_arg<BOOL>(4), src->get_arg<BOOL>(5), src->get_arg<BOOL>(6), src->get_arg<BOOL>(7));
			}
		}

		inline void SET_ENTITY_HEADING(rage::scrNativeCallContext* src)
		{
			if (!g.vehicle.ls_customs)
			{
				ENTITY::SET_ENTITY_HEADING(src->get_arg<Entity>(0), src->get_arg<float>(1));
			}
		}

		inline void SET_VEHICLE_LIGHTS(rage::scrNativeCallContext* src)
		{
			if (!g.vehicle.ls_customs)
			{
				VEHICLE::SET_VEHICLE_LIGHTS(src->get_arg<Vehicle>(0), src->get_arg<int>(1));
			}
		}

		inline void DISABLE_ALL_CONTROL_ACTIONS(rage::scrNativeCallContext* src)
		{
			if (!g.vehicle.ls_customs)
			{
				PAD::DISABLE_ALL_CONTROL_ACTIONS(src->get_arg<int>(0));
			}
		}
	}
}