#pragma once
#include "core/scr_globals.hpp"
#include "fiber_pool.hpp"
#include "gta/enums.hpp"
#include "hooking/hooking.hpp"
#include "native_hooks.hpp"
#include "natives.hpp"
#include "util/notify.hpp"
#include "util/scripts.hpp"

namespace big
{
	namespace all_scripts
	{
		void IS_DLC_PRESENT(rage::scrNativeCallContext* src)
		{
			const auto hash = src->get_arg<rage::joaat_t>(0);

			bool return_value = DLC::IS_DLC_PRESENT(hash);

			if (hash == 0x96F02EE6)
				return_value = return_value || g.settings.dev_dlc;

			src->set_return_value<BOOL>((BOOL)return_value);
		}

		void NETWORK_SET_THIS_SCRIPT_IS_NETWORK_SCRIPT(rage::scrNativeCallContext* src)
		{
			if (src->get_arg<int>(2) != -1 && src->get_arg<uint32_t>(2) >= 0x100) [[unlikely]]
			{
				notify::crash_blocked(nullptr, "out of bounds instance id");
				return;
			}

			NETWORK::NETWORK_SET_THIS_SCRIPT_IS_NETWORK_SCRIPT(src->get_arg<int>(0), src->get_arg<BOOL>(1), src->get_arg<int>(2));
		}

		void NETWORK_TRY_TO_SET_THIS_SCRIPT_IS_NETWORK_SCRIPT(rage::scrNativeCallContext* src)
		{
			if (src->get_arg<int>(2) != -1 && src->get_arg<uint32_t>(2) >= 0x100) [[unlikely]]
			{
				notify::crash_blocked(nullptr, "out of bounds instance id");
				src->set_return_value<BOOL>(FALSE);
				return;
			}

			src->set_return_value<BOOL>(NETWORK::NETWORK_TRY_TO_SET_THIS_SCRIPT_IS_NETWORK_SCRIPT(src->get_arg<int>(0), src->get_arg<BOOL>(1), src->get_arg<int>(2)));
		}

		void SET_CURRENT_PED_WEAPON(rage::scrNativeCallContext* src)
		{
			const auto ped  = src->get_arg<Ped>(0);
			const auto hash = src->get_arg<rage::joaat_t>(1);

			if (g.weapons.interior_weapon && ped == self::ped && hash == "WEAPON_UNARMED"_J)
				return;

			WEAPON::SET_CURRENT_PED_WEAPON(ped, hash, src->get_arg<int>(2));
		}

		void DISABLE_CONTROL_ACTION(rage::scrNativeCallContext* src)
		{
			const auto action = src->get_arg<ControllerInputs>(1);

			if (g.weapons.interior_weapon) // Filtering from the inside of Kosatka
			{
				switch (action)
				{
				// case ControllerInputs::INPUT_JUMP: TODO: add as separate feature
				case ControllerInputs::INPUT_ATTACK:
				case ControllerInputs::INPUT_AIM:
				case ControllerInputs::INPUT_DUCK:
				case ControllerInputs::INPUT_SELECT_WEAPON:
				case ControllerInputs::INPUT_COVER:
				case ControllerInputs::INPUT_TALK:
				case ControllerInputs::INPUT_DETONATE:
				case ControllerInputs::INPUT_WEAPON_SPECIAL:
				case ControllerInputs::INPUT_WEAPON_SPECIAL_TWO:
				case ControllerInputs::INPUT_VEH_AIM:
				case ControllerInputs::INPUT_VEH_ATTACK:
				case ControllerInputs::INPUT_VEH_ATTACK2:
				case ControllerInputs::INPUT_VEH_HEADLIGHT:
				case ControllerInputs::INPUT_VEH_NEXT_RADIO:
				case ControllerInputs::INPUT_VEH_PREV_RADIO:
				case ControllerInputs::INPUT_VEH_NEXT_RADIO_TRACK:
				case ControllerInputs::INPUT_VEH_PREV_RADIO_TRACK:
				case ControllerInputs::INPUT_VEH_RADIO_WHEEL:
				case ControllerInputs::INPUT_VEH_PASSENGER_AIM:
				case ControllerInputs::INPUT_VEH_PASSENGER_ATTACK:
				case ControllerInputs::INPUT_VEH_SELECT_NEXT_WEAPON:
				case ControllerInputs::INPUT_VEH_SELECT_PREV_WEAPON:
				case ControllerInputs::INPUT_VEH_ROOF:
				case ControllerInputs::INPUT_VEH_JUMP:
				case ControllerInputs::INPUT_VEH_FLY_ATTACK:
				case ControllerInputs::INPUT_MELEE_ATTACK_LIGHT:
				case ControllerInputs::INPUT_MELEE_ATTACK_HEAVY:
				case ControllerInputs::INPUT_MELEE_ATTACK_ALTERNATE:
				case ControllerInputs::INPUT_MELEE_BLOCK:
				case ControllerInputs::INPUT_SELECT_WEAPON_UNARMED:
				case ControllerInputs::INPUT_SELECT_WEAPON_MELEE:
				case ControllerInputs::INPUT_SELECT_WEAPON_HANDGUN:
				case ControllerInputs::INPUT_SELECT_WEAPON_SHOTGUN:
				case ControllerInputs::INPUT_SELECT_WEAPON_SMG:
				case ControllerInputs::INPUT_SELECT_WEAPON_AUTO_RIFLE:
				case ControllerInputs::INPUT_SELECT_WEAPON_SNIPER:
				case ControllerInputs::INPUT_SELECT_WEAPON_HEAVY:
				case ControllerInputs::INPUT_SELECT_WEAPON_SPECIAL:
				case ControllerInputs::INPUT_ATTACK2:
				case ControllerInputs::INPUT_MELEE_ATTACK1:
				case ControllerInputs::INPUT_MELEE_ATTACK2:
				case ControllerInputs::INPUT_VEH_GUN_LEFT:
				case ControllerInputs::INPUT_VEH_GUN_RIGHT:
				case ControllerInputs::INPUT_VEH_GUN_UP:
				case ControllerInputs::INPUT_VEH_GUN_DOWN:
				case ControllerInputs::INPUT_VEH_HYDRAULICS_CONTROL_TOGGLE:
				case ControllerInputs::INPUT_VEH_MELEE_HOLD:
				case ControllerInputs::INPUT_VEH_MELEE_LEFT:
				case ControllerInputs::INPUT_VEH_MELEE_RIGHT:
				case ControllerInputs::INPUT_VEH_CAR_JUMP:
				case ControllerInputs::INPUT_VEH_ROCKET_BOOST:
				case ControllerInputs::INPUT_VEH_FLY_BOOST:
				case ControllerInputs::INPUT_VEH_PARACHUTE:
				case ControllerInputs::INPUT_VEH_BIKE_WINGS:
				case ControllerInputs::INPUT_VEH_TRANSFORM: return;
				}
			}

			PAD::DISABLE_CONTROL_ACTION(src->get_arg<int>(0), (int)action, src->get_arg<int>(2));
		}

		void HUD_FORCE_WEAPON_WHEEL(rage::scrNativeCallContext* src)
		{
			if (g.weapons.interior_weapon && src->get_arg<BOOL>(0) == false)
				return;

			HUD::HUD_FORCE_WEAPON_WHEEL(src->get_arg<BOOL>(0));
		}

		void NETWORK_OVERRIDE_CLOCK_TIME(rage::scrNativeCallContext* src)
		{
			if (g.world.custom_time.override_time)
				return;

			NETWORK::NETWORK_OVERRIDE_CLOCK_TIME(src->get_arg<int>(0), src->get_arg<int>(1), src->get_arg<int>(2));
		}

		void SET_ENTITY_HEALTH(rage::scrNativeCallContext* src)
		{
			Entity entity = src->get_arg<Entity>(0);
			int health    = src->get_arg<int>(1);
			int p2        = src->get_arg<int>(2);
			int p3        = src->get_arg<int>(3);

			if (g.self.god_mode && entity == self::ped)
				health = ENTITY::GET_ENTITY_MAX_HEALTH(entity);

			ENTITY::SET_ENTITY_HEALTH(entity, health, p2, p3);
		}

		void APPLY_DAMAGE_TO_PED(rage::scrNativeCallContext* src)
		{
			Ped ped                 = src->get_arg<Ped>(0);
			int damage              = src->get_arg<int>(1);
			BOOL damage_armor_first = src->get_arg<BOOL>(2);
			Any p3                  = src->get_arg<Any>(3);
			int p4                  = src->get_arg<int>(4);

			if (g.self.god_mode && ped == self::ped)
				return;

			PED::APPLY_DAMAGE_TO_PED(ped, damage, damage_armor_first, p3, p4);
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
