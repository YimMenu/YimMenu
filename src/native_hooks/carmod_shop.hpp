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
			case "MP0_RACES_WON"_J:
			case "MP0_NUMBER_TURBO_STARTS_IN_RACE"_J:
			case "MP0_USJS_COMPLETED"_J:
			case "MP0_AWD_FM_RACES_FASTEST_LAP"_J:
			case "MP1_RACES_WON"_J:
			case "MP1_NUMBER_TURBO_STARTS_IN_RACE"_J:
			case "MP1_USJS_COMPLETED"_J:
			case "MP1_AWD_FM_RACES_FASTEST_LAP"_J: *out = 50; break;
			case "MP0_NUMBER_SLIPSTREAMS_IN_RACE"_J:
			case "MP1_NUMBER_SLIPSTREAMS_IN_RACE"_J: *out = 100; break;
			case "MP0_CHAR_FM_CARMOD_1_UNLCK"_J:
			case "MP0_CHAR_FM_CARMOD_2_UNLCK"_J:
			case "MP0_CHAR_FM_CARMOD_3_UNLCK"_J:
			case "MP0_CHAR_FM_CARMOD_4_UNLCK"_J:
			case "MP0_CHAR_FM_CARMOD_5_UNLCK"_J:
			case "MP0_CHAR_FM_CARMOD_6_UNLCK"_J:
			case "MP0_CHAR_FM_CARMOD_7_UNLCK"_J:
			case "MP1_CHAR_FM_CARMOD_1_UNLCK"_J:
			case "MP1_CHAR_FM_CARMOD_2_UNLCK"_J:
			case "MP1_CHAR_FM_CARMOD_3_UNLCK"_J:
			case "MP1_CHAR_FM_CARMOD_4_UNLCK"_J:
			case "MP1_CHAR_FM_CARMOD_5_UNLCK"_J:
			case "MP1_CHAR_FM_CARMOD_6_UNLCK"_J:
			case "MP1_CHAR_FM_CARMOD_7_UNLCK"_J: *out = -1; break;
			case "MP0_AWD_FMRALLYWONDRIVE"_J:
			case "MP0_AWD_FMRALLYWONNAV"_J:
			case "MP0_AWD_FMWINSEARACE"_J:
			case "MP0_AWD_FMWINAIRRACE"_J:
			case "MP1_AWD_FMRALLYWONDRIVE"_J:
			case "MP1_AWD_FMRALLYWONNAV"_J:
			case "MP1_AWD_FMWINSEARACE"_J:
			case "MP1_AWD_FMWINAIRRACE"_J: *out = 1; break;
			default: src->set_return_value<BOOL>(STATS::STAT_GET_INT(hash, out, src->get_arg<int>(2))); break;
			}
		}

		inline void STAT_SET_INT(rage::scrNativeCallContext* src)
		{
			const auto hash = src->get_arg<Hash>(0);
			if (hash == "SP0_TOTAL_CASH"_J || hash == "SP1_TOTAL_CASH"_J || hash == "SP2_TOTAL_CASH"_J)
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
