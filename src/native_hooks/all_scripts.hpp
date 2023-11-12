#pragma once
#include "core/data/world.hpp"
#include "core/scr_globals.hpp"
#include "core/settings/self.hpp"
#include "fiber_pool.hpp"
#include "gta/enums.hpp"
#include "hooking.hpp"
#include "native_hooks.hpp"
#include "natives.hpp"
#include "util/notify.hpp"
#include "util/scripts.hpp"

namespace big
{
	namespace all_scripts
	{
		void NETWORK_SET_THIS_SCRIPT_IS_NETWORK_SCRIPT(rage::scrNativeCallContext* src)
		{
			if (src->get_arg<int>(2) != -1 && src->get_arg<uint32_t>(2) >= 0x100)
			{
				notify::crash_blocked(nullptr, "out of bounds instance id");
				return;
			}

			NETWORK::NETWORK_SET_THIS_SCRIPT_IS_NETWORK_SCRIPT(src->get_arg<int>(0), src->get_arg<BOOL>(1), src->get_arg<int>(2));
		}

		void NETWORK_TRY_TO_SET_THIS_SCRIPT_IS_NETWORK_SCRIPT(rage::scrNativeCallContext* src)
		{
			if (src->get_arg<int>(2) != -1 && src->get_arg<uint32_t>(2) >= 0x100)
			{
				notify::crash_blocked(nullptr, "out of bounds instance id");
				src->set_return_value<BOOL>(FALSE);
				return;
			}

			src->set_return_value<BOOL>(NETWORK::NETWORK_TRY_TO_SET_THIS_SCRIPT_IS_NETWORK_SCRIPT(src->get_arg<int>(0), src->get_arg<BOOL>(1), src->get_arg<int>(2)));
		}

		void NETWORK_OVERRIDE_CLOCK_TIME(rage::scrNativeCallContext* src)
		{
			if (g_world.custom_time.override_time)
				return;

			NETWORK::NETWORK_OVERRIDE_CLOCK_TIME(src->get_arg<int>(0), src->get_arg<int>(1), src->get_arg<int>(2));
		}

		void SET_ENTITY_HEALTH(rage::scrNativeCallContext* src)
		{
			Entity entity = src->get_arg<Entity>(0);
			int health    = src->get_arg<int>(1);
			int p2        = src->get_arg<int>(2);

			if (g_self.god_mode && entity == self::ped)
				health = ENTITY::GET_ENTITY_MAX_HEALTH(entity);

			ENTITY::SET_ENTITY_HEALTH(entity, health, p2);
		}

		void APPLY_DAMAGE_TO_PED(rage::scrNativeCallContext* src)
		{
			Ped ped                 = src->get_arg<Ped>(0);
			int damage              = src->get_arg<int>(1);
			BOOL damage_armor_first = src->get_arg<BOOL>(2);
			Any p3                  = src->get_arg<Any>(3);

			if (g_self.god_mode && ped == self::ped)
				return;

			PED::APPLY_DAMAGE_TO_PED(ped, damage, damage_armor_first, p3);
		}

		void RETURN_TRUE(rage::scrNativeCallContext* src)
		{
			src->set_return_value<BOOL>(TRUE);
		}

		void RETURN_FALSE(rage::scrNativeCallContext* src)
		{
			src->set_return_value<BOOL>(FALSE);
		}

		void DO_NOTHING(rage::scrNativeCallContext* src)
		{
		}
	}
}