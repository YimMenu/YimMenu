#include "lua_native_binding.hpp"
#include "natives.hpp"

namespace lua::native
{
	static Ped LUA_NATIVE_PED_CREATE_PED(int pedType, Hash modelHash, float x, float y, float z, float heading, bool isNetwork, bool bScriptHostPed)
	{
		auto retval = PED::CREATE_PED(pedType, modelHash, x, y, z, heading, isNetwork, bScriptHostPed);
		return retval;
	}

	static Ped LUA_NATIVE_PED_DELETE_PED(Ped ped)
	{
		PED::DELETE_PED(&ped);
		return ped;
	}

	static Ped LUA_NATIVE_PED_CLONE_PED(Ped ped, bool isNetwork, bool bScriptHostPed, bool copyHeadBlendFlag)
	{
		auto retval = PED::CLONE_PED(ped, isNetwork, bScriptHostPed, copyHeadBlendFlag);
		return retval;
	}

	static Ped LUA_NATIVE_PED_CLONE_PED_ALT(Ped ped, bool isNetwork, bool bScriptHostPed, bool copyHeadBlendFlag, bool p4)
	{
		auto retval = PED::CLONE_PED_ALT(ped, isNetwork, bScriptHostPed, copyHeadBlendFlag, p4);
		return retval;
	}

	static void LUA_NATIVE_PED_CLONE_PED_TO_TARGET(Ped ped, Ped targetPed)
	{
		PED::CLONE_PED_TO_TARGET(ped, targetPed);
	}

	static void LUA_NATIVE_PED_CLONE_PED_TO_TARGET_ALT(Ped ped, Ped targetPed, bool p2)
	{
		PED::CLONE_PED_TO_TARGET_ALT(ped, targetPed, p2);
	}

	static bool LUA_NATIVE_PED_IS_PED_IN_VEHICLE(Ped ped, Vehicle vehicle, bool atGetIn)
	{
		auto retval = (bool)PED::IS_PED_IN_VEHICLE(ped, vehicle, atGetIn);
		return retval;
	}

	static bool LUA_NATIVE_PED_IS_PED_IN_MODEL(Ped ped, Hash modelHash)
	{
		auto retval = (bool)PED::IS_PED_IN_MODEL(ped, modelHash);
		return retval;
	}

	static bool LUA_NATIVE_PED_IS_PED_IN_ANY_VEHICLE(Ped ped, bool atGetIn)
	{
		auto retval = (bool)PED::IS_PED_IN_ANY_VEHICLE(ped, atGetIn);
		return retval;
	}

	static bool LUA_NATIVE_PED_IS_COP_PED_IN_AREA_3D(float x1, float y1, float z1, float x2, float y2, float z2)
	{
		auto retval = (bool)PED::IS_COP_PED_IN_AREA_3D(x1, y1, z1, x2, y2, z2);
		return retval;
	}

	static bool LUA_NATIVE_PED_IS_PED_INJURED(Ped ped)
	{
		auto retval = (bool)PED::IS_PED_INJURED(ped);
		return retval;
	}

	static bool LUA_NATIVE_PED_IS_PED_HURT(Ped ped)
	{
		auto retval = (bool)PED::IS_PED_HURT(ped);
		return retval;
	}

	static bool LUA_NATIVE_PED_IS_PED_FATALLY_INJURED(Ped ped)
	{
		auto retval = (bool)PED::IS_PED_FATALLY_INJURED(ped);
		return retval;
	}

	static bool LUA_NATIVE_PED_IS_PED_DEAD_OR_DYING(Ped ped, bool p1)
	{
		auto retval = (bool)PED::IS_PED_DEAD_OR_DYING(ped, p1);
		return retval;
	}

	static bool LUA_NATIVE_PED_IS_CONVERSATION_PED_DEAD(Ped ped)
	{
		auto retval = (bool)PED::IS_CONVERSATION_PED_DEAD(ped);
		return retval;
	}

	static bool LUA_NATIVE_PED_IS_PED_AIMING_FROM_COVER(Ped ped)
	{
		auto retval = (bool)PED::IS_PED_AIMING_FROM_COVER(ped);
		return retval;
	}

	static bool LUA_NATIVE_PED_IS_PED_RELOADING(Ped ped)
	{
		auto retval = (bool)PED::IS_PED_RELOADING(ped);
		return retval;
	}

	static bool LUA_NATIVE_PED_IS_PED_A_PLAYER(Ped ped)
	{
		auto retval = (bool)PED::IS_PED_A_PLAYER(ped);
		return retval;
	}

	static Ped LUA_NATIVE_PED_CREATE_PED_INSIDE_VEHICLE(Vehicle vehicle, int pedType, Hash modelHash, int seat, bool isNetwork, bool bScriptHostPed)
	{
		auto retval = PED::CREATE_PED_INSIDE_VEHICLE(vehicle, pedType, modelHash, seat, isNetwork, bScriptHostPed);
		return retval;
	}

	static void LUA_NATIVE_PED_SET_PED_DESIRED_HEADING(Ped ped, float heading)
	{
		PED::SET_PED_DESIRED_HEADING(ped, heading);
	}

	static void LUA_NATIVE_PED_FORCE_ALL_HEADING_VALUES_TO_ALIGN(Ped ped)
	{
		PED::FORCE_ALL_HEADING_VALUES_TO_ALIGN(ped);
	}

	static bool LUA_NATIVE_PED_IS_PED_FACING_PED(Ped ped, Ped otherPed, float angle)
	{
		auto retval = (bool)PED::IS_PED_FACING_PED(ped, otherPed, angle);
		return retval;
	}

	static bool LUA_NATIVE_PED_IS_PED_IN_MELEE_COMBAT(Ped ped)
	{
		auto retval = (bool)PED::IS_PED_IN_MELEE_COMBAT(ped);
		return retval;
	}

	static bool LUA_NATIVE_PED_IS_PED_STOPPED(Ped ped)
	{
		auto retval = (bool)PED::IS_PED_STOPPED(ped);
		return retval;
	}

	static bool LUA_NATIVE_PED_IS_PED_SHOOTING_IN_AREA(Ped ped, float x1, float y1, float z1, float x2, float y2, float z2, bool p7, bool p8)
	{
		auto retval = (bool)PED::IS_PED_SHOOTING_IN_AREA(ped, x1, y1, z1, x2, y2, z2, p7, p8);
		return retval;
	}

	static bool LUA_NATIVE_PED_IS_ANY_PED_SHOOTING_IN_AREA(float x1, float y1, float z1, float x2, float y2, float z2, bool p6, bool p7)
	{
		auto retval = (bool)PED::IS_ANY_PED_SHOOTING_IN_AREA(x1, y1, z1, x2, y2, z2, p6, p7);
		return retval;
	}

	static bool LUA_NATIVE_PED_IS_PED_SHOOTING(Ped ped)
	{
		auto retval = (bool)PED::IS_PED_SHOOTING(ped);
		return retval;
	}

	static void LUA_NATIVE_PED_SET_PED_ACCURACY(Ped ped, int accuracy)
	{
		PED::SET_PED_ACCURACY(ped, accuracy);
	}

	static int LUA_NATIVE_PED_GET_PED_ACCURACY(Ped ped)
	{
		auto retval = PED::GET_PED_ACCURACY(ped);
		return retval;
	}

	static void LUA_NATIVE_PED_SET_AMBIENT_LAW_PED_ACCURACY_MODIFIER(float multiplier)
	{
		PED::SET_AMBIENT_LAW_PED_ACCURACY_MODIFIER(multiplier);
	}

	static bool LUA_NATIVE_PED_IS_PED_MODEL(Ped ped, Hash modelHash)
	{
		auto retval = (bool)PED::IS_PED_MODEL(ped, modelHash);
		return retval;
	}

	static void LUA_NATIVE_PED_EXPLODE_PED_HEAD(Ped ped, Hash weaponHash)
	{
		PED::EXPLODE_PED_HEAD(ped, weaponHash);
	}

	static Ped LUA_NATIVE_PED_REMOVE_PED_ELEGANTLY(Ped ped)
	{
		PED::REMOVE_PED_ELEGANTLY(&ped);
		return ped;
	}

	static void LUA_NATIVE_PED_ADD_ARMOUR_TO_PED(Ped ped, int amount)
	{
		PED::ADD_ARMOUR_TO_PED(ped, amount);
	}

	static void LUA_NATIVE_PED_SET_PED_ARMOUR(Ped ped, int amount)
	{
		PED::SET_PED_ARMOUR(ped, amount);
	}

	static void LUA_NATIVE_PED_SET_PED_INTO_VEHICLE(Ped ped, Vehicle vehicle, int seatIndex)
	{
		PED::SET_PED_INTO_VEHICLE(ped, vehicle, seatIndex);
	}

	static void LUA_NATIVE_PED_SET_PED_ALLOW_VEHICLES_OVERRIDE(Ped ped, bool toggle)
	{
		PED::SET_PED_ALLOW_VEHICLES_OVERRIDE(ped, toggle);
	}

	static bool LUA_NATIVE_PED_CAN_CREATE_RANDOM_PED(bool p0)
	{
		auto retval = (bool)PED::CAN_CREATE_RANDOM_PED(p0);
		return retval;
	}

	static Ped LUA_NATIVE_PED_CREATE_RANDOM_PED(float posX, float posY, float posZ)
	{
		auto retval = PED::CREATE_RANDOM_PED(posX, posY, posZ);
		return retval;
	}

	static Ped LUA_NATIVE_PED_CREATE_RANDOM_PED_AS_DRIVER(Vehicle vehicle, bool returnHandle)
	{
		auto retval = PED::CREATE_RANDOM_PED_AS_DRIVER(vehicle, returnHandle);
		return retval;
	}

	static bool LUA_NATIVE_PED_CAN_CREATE_RANDOM_DRIVER()
	{
		auto retval = (bool)PED::CAN_CREATE_RANDOM_DRIVER();
		return retval;
	}

	static bool LUA_NATIVE_PED_CAN_CREATE_RANDOM_BIKE_RIDER()
	{
		auto retval = (bool)PED::CAN_CREATE_RANDOM_BIKE_RIDER();
		return retval;
	}

	static void LUA_NATIVE_PED_SET_PED_MOVE_ANIMS_BLEND_OUT(Ped ped)
	{
		PED::SET_PED_MOVE_ANIMS_BLEND_OUT(ped);
	}

	static void LUA_NATIVE_PED_SET_PED_CAN_BE_DRAGGED_OUT(Ped ped, bool toggle)
	{
		PED::SET_PED_CAN_BE_DRAGGED_OUT(ped, toggle);
	}

	static void LUA_NATIVE_PED_SET_PED_ALLOW_HURT_COMBAT_FOR_ALL_MISSION_PEDS(bool toggle)
	{
		PED::SET_PED_ALLOW_HURT_COMBAT_FOR_ALL_MISSION_PEDS(toggle);
	}

	static bool LUA_NATIVE_PED_IS_PED_MALE(Ped ped)
	{
		auto retval = (bool)PED::IS_PED_MALE(ped);
		return retval;
	}

	static bool LUA_NATIVE_PED_IS_PED_HUMAN(Ped ped)
	{
		auto retval = (bool)PED::IS_PED_HUMAN(ped);
		return retval;
	}

	static Vehicle LUA_NATIVE_PED_GET_VEHICLE_PED_IS_IN(Ped ped, bool includeEntering)
	{
		auto retval = PED::GET_VEHICLE_PED_IS_IN(ped, includeEntering);
		return retval;
	}

	static void LUA_NATIVE_PED_RESET_PED_LAST_VEHICLE(Ped ped)
	{
		PED::RESET_PED_LAST_VEHICLE(ped);
	}

	static void LUA_NATIVE_PED_SET_PED_DENSITY_MULTIPLIER_THIS_FRAME(float multiplier)
	{
		PED::SET_PED_DENSITY_MULTIPLIER_THIS_FRAME(multiplier);
	}

	static void LUA_NATIVE_PED_SET_SCENARIO_PED_DENSITY_MULTIPLIER_THIS_FRAME(float p0, float p1)
	{
		PED::SET_SCENARIO_PED_DENSITY_MULTIPLIER_THIS_FRAME(p0, p1);
	}

	static void LUA_NATIVE_PED_SUPPRESS_AMBIENT_PED_AGGRESSIVE_CLEANUP_THIS_FRAME()
	{
		PED::SUPPRESS_AMBIENT_PED_AGGRESSIVE_CLEANUP_THIS_FRAME();
	}

	static void LUA_NATIVE_PED_SET_SCRIPTED_CONVERSION_COORD_THIS_FRAME(float x, float y, float z)
	{
		PED::SET_SCRIPTED_CONVERSION_COORD_THIS_FRAME(x, y, z);
	}

	static void LUA_NATIVE_PED_SET_PED_NON_CREATION_AREA(float x1, float y1, float z1, float x2, float y2, float z2)
	{
		PED::SET_PED_NON_CREATION_AREA(x1, y1, z1, x2, y2, z2);
	}

	static void LUA_NATIVE_PED_CLEAR_PED_NON_CREATION_AREA()
	{
		PED::CLEAR_PED_NON_CREATION_AREA();
	}

	static void LUA_NATIVE_PED_INSTANTLY_FILL_PED_POPULATION()
	{
		PED::INSTANTLY_FILL_PED_POPULATION();
	}

	static bool LUA_NATIVE_PED_IS_PED_ON_MOUNT(Ped ped)
	{
		auto retval = (bool)PED::IS_PED_ON_MOUNT(ped);
		return retval;
	}

	static Ped LUA_NATIVE_PED_GET_MOUNT(Ped ped)
	{
		auto retval = PED::GET_MOUNT(ped);
		return retval;
	}

	static bool LUA_NATIVE_PED_IS_PED_ON_VEHICLE(Ped ped)
	{
		auto retval = (bool)PED::IS_PED_ON_VEHICLE(ped);
		return retval;
	}

	static bool LUA_NATIVE_PED_IS_PED_ON_SPECIFIC_VEHICLE(Ped ped, Vehicle vehicle)
	{
		auto retval = (bool)PED::IS_PED_ON_SPECIFIC_VEHICLE(ped, vehicle);
		return retval;
	}

	static void LUA_NATIVE_PED_SET_PED_MONEY(Ped ped, int amount)
	{
		PED::SET_PED_MONEY(ped, amount);
	}

	static int LUA_NATIVE_PED_GET_PED_MONEY(Ped ped)
	{
		auto retval = PED::GET_PED_MONEY(ped);
		return retval;
	}

	static void LUA_NATIVE_PED_SET_HEALTH_SNACKS_CARRIED_BY_ALL_NEW_PEDS(float p0, Any p1)
	{
		PED::SET_HEALTH_SNACKS_CARRIED_BY_ALL_NEW_PEDS(p0, p1);
	}

	static void LUA_NATIVE_PED_SET_AMBIENT_PEDS_DROP_MONEY(bool p0)
	{
		PED::SET_AMBIENT_PEDS_DROP_MONEY(p0);
	}

	static void LUA_NATIVE_PED_SET_BLOCKING_OF_NON_TEMPORARY_EVENTS_FOR_AMBIENT_PEDS_THIS_FRAME(bool p0)
	{
		PED::SET_BLOCKING_OF_NON_TEMPORARY_EVENTS_FOR_AMBIENT_PEDS_THIS_FRAME(p0);
	}

	static void LUA_NATIVE_PED_SET_PED_SUFFERS_CRITICAL_HITS(Ped ped, bool toggle)
	{
		PED::SET_PED_SUFFERS_CRITICAL_HITS(ped, toggle);
	}

	static void LUA_NATIVE_PED_SET_PED_UPPER_BODY_DAMAGE_ONLY(Ped ped, bool toggle)
	{
		PED::SET_PED_UPPER_BODY_DAMAGE_ONLY(ped, toggle);
	}

	static bool LUA_NATIVE_PED_IS_PED_SITTING_IN_VEHICLE(Ped ped, Vehicle vehicle)
	{
		auto retval = (bool)PED::IS_PED_SITTING_IN_VEHICLE(ped, vehicle);
		return retval;
	}

	static bool LUA_NATIVE_PED_IS_PED_SITTING_IN_ANY_VEHICLE(Ped ped)
	{
		auto retval = (bool)PED::IS_PED_SITTING_IN_ANY_VEHICLE(ped);
		return retval;
	}

	static bool LUA_NATIVE_PED_IS_PED_ON_FOOT(Ped ped)
	{
		auto retval = (bool)PED::IS_PED_ON_FOOT(ped);
		return retval;
	}

	static bool LUA_NATIVE_PED_IS_PED_ON_ANY_BIKE(Ped ped)
	{
		auto retval = (bool)PED::IS_PED_ON_ANY_BIKE(ped);
		return retval;
	}

	static bool LUA_NATIVE_PED_IS_PED_PLANTING_BOMB(Ped ped)
	{
		auto retval = (bool)PED::IS_PED_PLANTING_BOMB(ped);
		return retval;
	}

	static Vector3 LUA_NATIVE_PED_GET_DEAD_PED_PICKUP_COORDS(Ped ped, float p1, float p2)
	{
		auto retval = PED::GET_DEAD_PED_PICKUP_COORDS(ped, p1, p2);
		return retval;
	}

	static bool LUA_NATIVE_PED_IS_PED_IN_ANY_BOAT(Ped ped)
	{
		auto retval = (bool)PED::IS_PED_IN_ANY_BOAT(ped);
		return retval;
	}

	static bool LUA_NATIVE_PED_IS_PED_IN_ANY_SUB(Ped ped)
	{
		auto retval = (bool)PED::IS_PED_IN_ANY_SUB(ped);
		return retval;
	}

	static bool LUA_NATIVE_PED_IS_PED_IN_ANY_HELI(Ped ped)
	{
		auto retval = (bool)PED::IS_PED_IN_ANY_HELI(ped);
		return retval;
	}

	static bool LUA_NATIVE_PED_IS_PED_IN_ANY_PLANE(Ped ped)
	{
		auto retval = (bool)PED::IS_PED_IN_ANY_PLANE(ped);
		return retval;
	}

	static bool LUA_NATIVE_PED_IS_PED_IN_FLYING_VEHICLE(Ped ped)
	{
		auto retval = (bool)PED::IS_PED_IN_FLYING_VEHICLE(ped);
		return retval;
	}

	static void LUA_NATIVE_PED_SET_PED_DIES_IN_WATER(Ped ped, bool toggle)
	{
		PED::SET_PED_DIES_IN_WATER(ped, toggle);
	}

	static bool LUA_NATIVE_PED_GET_PED_DIES_IN_WATER(Ped ped)
	{
		auto retval = (bool)PED::GET_PED_DIES_IN_WATER(ped);
		return retval;
	}

	static void LUA_NATIVE_PED_SET_PED_DIES_IN_SINKING_VEHICLE(Ped ped, bool toggle)
	{
		PED::SET_PED_DIES_IN_SINKING_VEHICLE(ped, toggle);
	}

	static int LUA_NATIVE_PED_GET_PED_ARMOUR(Ped ped)
	{
		auto retval = PED::GET_PED_ARMOUR(ped);
		return retval;
	}

	static void LUA_NATIVE_PED_SET_PED_STAY_IN_VEHICLE_WHEN_JACKED(Ped ped, bool toggle)
	{
		PED::SET_PED_STAY_IN_VEHICLE_WHEN_JACKED(ped, toggle);
	}

	static void LUA_NATIVE_PED_SET_PED_CAN_BE_SHOT_IN_VEHICLE(Ped ped, bool toggle)
	{
		PED::SET_PED_CAN_BE_SHOT_IN_VEHICLE(ped, toggle);
	}

	static std::tuple<bool, int> LUA_NATIVE_PED_GET_PED_LAST_DAMAGE_BONE(Ped ped, int outBone)
	{
		std::tuple<bool, int> return_values;
		std::get<0>(return_values) = (bool)PED::GET_PED_LAST_DAMAGE_BONE(ped, &outBone);
		std::get<1>(return_values) = outBone;

		return return_values;
	}

	static void LUA_NATIVE_PED_CLEAR_PED_LAST_DAMAGE_BONE(Ped ped)
	{
		PED::CLEAR_PED_LAST_DAMAGE_BONE(ped);
	}

	static void LUA_NATIVE_PED_SET_AI_WEAPON_DAMAGE_MODIFIER(float value)
	{
		PED::SET_AI_WEAPON_DAMAGE_MODIFIER(value);
	}

	static void LUA_NATIVE_PED_RESET_AI_WEAPON_DAMAGE_MODIFIER()
	{
		PED::RESET_AI_WEAPON_DAMAGE_MODIFIER();
	}

	static void LUA_NATIVE_PED_SET_AI_MELEE_WEAPON_DAMAGE_MODIFIER(float modifier)
	{
		PED::SET_AI_MELEE_WEAPON_DAMAGE_MODIFIER(modifier);
	}

	static void LUA_NATIVE_PED_RESET_AI_MELEE_WEAPON_DAMAGE_MODIFIER()
	{
		PED::RESET_AI_MELEE_WEAPON_DAMAGE_MODIFIER();
	}

	static void LUA_NATIVE_PED_SET_TREAT_AS_AMBIENT_PED_FOR_DRIVER_LOCKON(Ped ped, bool p1)
	{
		PED::SET_TREAT_AS_AMBIENT_PED_FOR_DRIVER_LOCKON(ped, p1);
	}

	static void LUA_NATIVE_PED_SET_PED_CAN_BE_TARGETTED(Ped ped, bool toggle)
	{
		PED::SET_PED_CAN_BE_TARGETTED(ped, toggle);
	}

	static void LUA_NATIVE_PED_SET_PED_CAN_BE_TARGETTED_BY_TEAM(Ped ped, int team, bool toggle)
	{
		PED::SET_PED_CAN_BE_TARGETTED_BY_TEAM(ped, team, toggle);
	}

	static void LUA_NATIVE_PED_SET_PED_CAN_BE_TARGETTED_BY_PLAYER(Ped ped, Player player, bool toggle)
	{
		PED::SET_PED_CAN_BE_TARGETTED_BY_PLAYER(ped, player, toggle);
	}

	static void LUA_NATIVE_PED_SET_ALLOW_LOCKON_TO_PED_IF_FRIENDLY(Ped ped, bool toggle)
	{
		PED::SET_ALLOW_LOCKON_TO_PED_IF_FRIENDLY(ped, toggle);
	}

	static void LUA_NATIVE_PED_SET_USE_CAMERA_HEADING_FOR_DESIRED_DIRECTION_LOCK_ON_TEST(Ped ped, bool toggle)
	{
		PED::SET_USE_CAMERA_HEADING_FOR_DESIRED_DIRECTION_LOCK_ON_TEST(ped, toggle);
	}

	static bool LUA_NATIVE_PED_IS_PED_IN_ANY_POLICE_VEHICLE(Ped ped)
	{
		auto retval = (bool)PED::IS_PED_IN_ANY_POLICE_VEHICLE(ped);
		return retval;
	}

	static void LUA_NATIVE_PED_FORCE_PED_TO_OPEN_PARACHUTE(Ped ped)
	{
		PED::FORCE_PED_TO_OPEN_PARACHUTE(ped);
	}

	static bool LUA_NATIVE_PED_IS_PED_IN_PARACHUTE_FREE_FALL(Ped ped)
	{
		auto retval = (bool)PED::IS_PED_IN_PARACHUTE_FREE_FALL(ped);
		return retval;
	}

	static bool LUA_NATIVE_PED_IS_PED_FALLING(Ped ped)
	{
		auto retval = (bool)PED::IS_PED_FALLING(ped);
		return retval;
	}

	static bool LUA_NATIVE_PED_IS_PED_JUMPING(Ped ped)
	{
		auto retval = (bool)PED::IS_PED_JUMPING(ped);
		return retval;
	}

	static bool LUA_NATIVE_PED_IS_PED_LANDING(Any p0)
	{
		auto retval = (bool)PED::IS_PED_LANDING(p0);
		return retval;
	}

	static bool LUA_NATIVE_PED_IS_PED_DOING_A_BEAST_JUMP(Any p0)
	{
		auto retval = (bool)PED::IS_PED_DOING_A_BEAST_JUMP(p0);
		return retval;
	}

	static bool LUA_NATIVE_PED_IS_PED_CLIMBING(Ped ped)
	{
		auto retval = (bool)PED::IS_PED_CLIMBING(ped);
		return retval;
	}

	static bool LUA_NATIVE_PED_IS_PED_VAULTING(Ped ped)
	{
		auto retval = (bool)PED::IS_PED_VAULTING(ped);
		return retval;
	}

	static bool LUA_NATIVE_PED_IS_PED_DIVING(Ped ped)
	{
		auto retval = (bool)PED::IS_PED_DIVING(ped);
		return retval;
	}

	static bool LUA_NATIVE_PED_IS_PED_JUMPING_OUT_OF_VEHICLE(Ped ped)
	{
		auto retval = (bool)PED::IS_PED_JUMPING_OUT_OF_VEHICLE(ped);
		return retval;
	}

	static bool LUA_NATIVE_PED_IS_PED_OPENING_DOOR(Ped ped)
	{
		auto retval = (bool)PED::IS_PED_OPENING_DOOR(ped);
		return retval;
	}

	static int LUA_NATIVE_PED_GET_PED_PARACHUTE_STATE(Ped ped)
	{
		auto retval = PED::GET_PED_PARACHUTE_STATE(ped);
		return retval;
	}

	static int LUA_NATIVE_PED_GET_PED_PARACHUTE_LANDING_TYPE(Ped ped)
	{
		auto retval = PED::GET_PED_PARACHUTE_LANDING_TYPE(ped);
		return retval;
	}

	static void LUA_NATIVE_PED_SET_PED_PARACHUTE_TINT_INDEX(Ped ped, int tintIndex)
	{
		PED::SET_PED_PARACHUTE_TINT_INDEX(ped, tintIndex);
	}

	static int LUA_NATIVE_PED_GET_PED_PARACHUTE_TINT_INDEX(Ped ped, int outTintIndex)
	{
		PED::GET_PED_PARACHUTE_TINT_INDEX(ped, &outTintIndex);
		return outTintIndex;
	}

	static void LUA_NATIVE_PED_SET_PED_RESERVE_PARACHUTE_TINT_INDEX(Ped ped, Any p1)
	{
		PED::SET_PED_RESERVE_PARACHUTE_TINT_INDEX(ped, p1);
	}

	static Object LUA_NATIVE_PED_CREATE_PARACHUTE_BAG_OBJECT(Ped ped, bool p1, bool p2)
	{
		auto retval = PED::CREATE_PARACHUTE_BAG_OBJECT(ped, p1, p2);
		return retval;
	}

	static void LUA_NATIVE_PED_SET_PED_DUCKING(Ped ped, bool toggle)
	{
		PED::SET_PED_DUCKING(ped, toggle);
	}

	static bool LUA_NATIVE_PED_IS_PED_DUCKING(Ped ped)
	{
		auto retval = (bool)PED::IS_PED_DUCKING(ped);
		return retval;
	}

	static bool LUA_NATIVE_PED_IS_PED_IN_ANY_TAXI(Ped ped)
	{
		auto retval = (bool)PED::IS_PED_IN_ANY_TAXI(ped);
		return retval;
	}

	static void LUA_NATIVE_PED_SET_PED_ID_RANGE(Ped ped, float value)
	{
		PED::SET_PED_ID_RANGE(ped, value);
	}

	static void LUA_NATIVE_PED_SET_PED_HIGHLY_PERCEPTIVE(Ped ped, bool toggle)
	{
		PED::SET_PED_HIGHLY_PERCEPTIVE(ped, toggle);
	}

	static void LUA_NATIVE_PED_SET_COP_PERCEPTION_OVERRIDES(float seeingRange, float seeingRangePeripheral, float hearingRange, float visualFieldMinAzimuthAngle, float visualFieldMaxAzimuthAngle, float fieldOfGazeMaxAngle, float p6)
	{
		PED::SET_COP_PERCEPTION_OVERRIDES(seeingRange, seeingRangePeripheral, hearingRange, visualFieldMinAzimuthAngle, visualFieldMaxAzimuthAngle, fieldOfGazeMaxAngle, p6);
	}

	static void LUA_NATIVE_PED_SET_PED_INJURED_ON_GROUND_BEHAVIOUR(Ped ped, float p1)
	{
		PED::SET_PED_INJURED_ON_GROUND_BEHAVIOUR(ped, p1);
	}

	static void LUA_NATIVE_PED_DISABLE_PED_INJURED_ON_GROUND_BEHAVIOUR(Ped ped)
	{
		PED::DISABLE_PED_INJURED_ON_GROUND_BEHAVIOUR(ped);
	}

	static void LUA_NATIVE_PED_SET_PED_SEEING_RANGE(Ped ped, float value)
	{
		PED::SET_PED_SEEING_RANGE(ped, value);
	}

	static void LUA_NATIVE_PED_SET_PED_HEARING_RANGE(Ped ped, float value)
	{
		PED::SET_PED_HEARING_RANGE(ped, value);
	}

	static void LUA_NATIVE_PED_SET_PED_VISUAL_FIELD_MIN_ANGLE(Ped ped, float value)
	{
		PED::SET_PED_VISUAL_FIELD_MIN_ANGLE(ped, value);
	}

	static void LUA_NATIVE_PED_SET_PED_VISUAL_FIELD_MAX_ANGLE(Ped ped, float value)
	{
		PED::SET_PED_VISUAL_FIELD_MAX_ANGLE(ped, value);
	}

	static void LUA_NATIVE_PED_SET_PED_VISUAL_FIELD_MIN_ELEVATION_ANGLE(Ped ped, float angle)
	{
		PED::SET_PED_VISUAL_FIELD_MIN_ELEVATION_ANGLE(ped, angle);
	}

	static void LUA_NATIVE_PED_SET_PED_VISUAL_FIELD_MAX_ELEVATION_ANGLE(Ped ped, float angle)
	{
		PED::SET_PED_VISUAL_FIELD_MAX_ELEVATION_ANGLE(ped, angle);
	}

	static void LUA_NATIVE_PED_SET_PED_VISUAL_FIELD_PERIPHERAL_RANGE(Ped ped, float range)
	{
		PED::SET_PED_VISUAL_FIELD_PERIPHERAL_RANGE(ped, range);
	}

	static void LUA_NATIVE_PED_SET_PED_VISUAL_FIELD_CENTER_ANGLE(Ped ped, float angle)
	{
		PED::SET_PED_VISUAL_FIELD_CENTER_ANGLE(ped, angle);
	}

	static float LUA_NATIVE_PED_GET_PED_VISUAL_FIELD_CENTER_ANGLE(Ped ped)
	{
		auto retval = PED::GET_PED_VISUAL_FIELD_CENTER_ANGLE(ped);
		return retval;
	}

	static void LUA_NATIVE_PED_SET_PED_STEALTH_MOVEMENT(Ped ped, bool p1, sol::stack_object action)
	{
		PED::SET_PED_STEALTH_MOVEMENT(ped, p1, action.is<const char*>() ? action.as<const char*>() : nullptr);
	}

	static bool LUA_NATIVE_PED_GET_PED_STEALTH_MOVEMENT(Ped ped)
	{
		auto retval = (bool)PED::GET_PED_STEALTH_MOVEMENT(ped);
		return retval;
	}

	static int LUA_NATIVE_PED_CREATE_GROUP(int unused)
	{
		auto retval = PED::CREATE_GROUP(unused);
		return retval;
	}

	static void LUA_NATIVE_PED_SET_PED_AS_GROUP_LEADER(Ped ped, int groupId)
	{
		PED::SET_PED_AS_GROUP_LEADER(ped, groupId);
	}

	static void LUA_NATIVE_PED_SET_PED_AS_GROUP_MEMBER(Ped ped, int groupId)
	{
		PED::SET_PED_AS_GROUP_MEMBER(ped, groupId);
	}

	static void LUA_NATIVE_PED_SET_PED_CAN_TELEPORT_TO_GROUP_LEADER(Ped pedHandle, int groupHandle, bool toggle)
	{
		PED::SET_PED_CAN_TELEPORT_TO_GROUP_LEADER(pedHandle, groupHandle, toggle);
	}

	static void LUA_NATIVE_PED_REMOVE_GROUP(int groupId)
	{
		PED::REMOVE_GROUP(groupId);
	}

	static void LUA_NATIVE_PED_REMOVE_PED_FROM_GROUP(Ped ped)
	{
		PED::REMOVE_PED_FROM_GROUP(ped);
	}

	static bool LUA_NATIVE_PED_IS_PED_GROUP_MEMBER(Ped ped, int groupId)
	{
		auto retval = (bool)PED::IS_PED_GROUP_MEMBER(ped, groupId);
		return retval;
	}

	static bool LUA_NATIVE_PED_IS_PED_HANGING_ON_TO_VEHICLE(Ped ped)
	{
		auto retval = (bool)PED::IS_PED_HANGING_ON_TO_VEHICLE(ped);
		return retval;
	}

	static void LUA_NATIVE_PED_SET_GROUP_SEPARATION_RANGE(int groupHandle, float separationRange)
	{
		PED::SET_GROUP_SEPARATION_RANGE(groupHandle, separationRange);
	}

	static void LUA_NATIVE_PED_SET_PED_MIN_GROUND_TIME_FOR_STUNGUN(Ped ped, int ms)
	{
		PED::SET_PED_MIN_GROUND_TIME_FOR_STUNGUN(ped, ms);
	}

	static bool LUA_NATIVE_PED_IS_PED_PRONE(Ped ped)
	{
		auto retval = (bool)PED::IS_PED_PRONE(ped);
		return retval;
	}

	static bool LUA_NATIVE_PED_IS_PED_IN_COMBAT(Ped ped, Ped target)
	{
		auto retval = (bool)PED::IS_PED_IN_COMBAT(ped, target);
		return retval;
	}

	static Entity LUA_NATIVE_PED_GET_PED_TARGET_FROM_COMBAT_PED(Ped ped, Any p1)
	{
		auto retval = PED::GET_PED_TARGET_FROM_COMBAT_PED(ped, p1);
		return retval;
	}

	static bool LUA_NATIVE_PED_CAN_PED_IN_COMBAT_SEE_TARGET(Ped ped, Ped target)
	{
		auto retval = (bool)PED::CAN_PED_IN_COMBAT_SEE_TARGET(ped, target);
		return retval;
	}

	static bool LUA_NATIVE_PED_IS_PED_DOING_DRIVEBY(Ped ped)
	{
		auto retval = (bool)PED::IS_PED_DOING_DRIVEBY(ped);
		return retval;
	}

	static bool LUA_NATIVE_PED_IS_PED_JACKING(Ped ped)
	{
		auto retval = (bool)PED::IS_PED_JACKING(ped);
		return retval;
	}

	static bool LUA_NATIVE_PED_IS_PED_BEING_JACKED(Ped ped)
	{
		auto retval = (bool)PED::IS_PED_BEING_JACKED(ped);
		return retval;
	}

	static bool LUA_NATIVE_PED_IS_PED_BEING_STUNNED(Ped ped, int p1)
	{
		auto retval = (bool)PED::IS_PED_BEING_STUNNED(ped, p1);
		return retval;
	}

	static Ped LUA_NATIVE_PED_GET_PEDS_JACKER(Ped ped)
	{
		auto retval = PED::GET_PEDS_JACKER(ped);
		return retval;
	}

	static Ped LUA_NATIVE_PED_GET_JACK_TARGET(Ped ped)
	{
		auto retval = PED::GET_JACK_TARGET(ped);
		return retval;
	}

	static bool LUA_NATIVE_PED_IS_PED_FLEEING(Ped ped)
	{
		auto retval = (bool)PED::IS_PED_FLEEING(ped);
		return retval;
	}

	static bool LUA_NATIVE_PED_IS_PED_IN_COVER(Ped ped, bool exceptUseWeapon)
	{
		auto retval = (bool)PED::IS_PED_IN_COVER(ped, exceptUseWeapon);
		return retval;
	}

	static bool LUA_NATIVE_PED_IS_PED_IN_COVER_FACING_LEFT(Ped ped)
	{
		auto retval = (bool)PED::IS_PED_IN_COVER_FACING_LEFT(ped);
		return retval;
	}

	static bool LUA_NATIVE_PED_IS_PED_IN_HIGH_COVER(Ped ped)
	{
		auto retval = (bool)PED::IS_PED_IN_HIGH_COVER(ped);
		return retval;
	}

	static bool LUA_NATIVE_PED_IS_PED_GOING_INTO_COVER(Ped ped)
	{
		auto retval = (bool)PED::IS_PED_GOING_INTO_COVER(ped);
		return retval;
	}

	static bool LUA_NATIVE_PED_SET_PED_PINNED_DOWN(Ped ped, bool pinned, int i)
	{
		auto retval = (bool)PED::SET_PED_PINNED_DOWN(ped, pinned, i);
		return retval;
	}

	static bool LUA_NATIVE_PED_HAS_PED_CLEAR_LOS_TO_ENTITY_(Ped ped, Entity entity, float x, float y, float z, int p5, bool p6, bool p7)
	{
		auto retval = (bool)PED::_HAS_PED_CLEAR_LOS_TO_ENTITY(ped, entity, x, y, z, p5, p6, p7);
		return retval;
	}

	static int LUA_NATIVE_PED_GET_SEAT_PED_IS_TRYING_TO_ENTER(Ped ped)
	{
		auto retval = PED::GET_SEAT_PED_IS_TRYING_TO_ENTER(ped);
		return retval;
	}

	static Vehicle LUA_NATIVE_PED_GET_VEHICLE_PED_IS_TRYING_TO_ENTER(Ped ped)
	{
		auto retval = PED::GET_VEHICLE_PED_IS_TRYING_TO_ENTER(ped);
		return retval;
	}

	static Entity LUA_NATIVE_PED_GET_PED_SOURCE_OF_DEATH(Ped ped)
	{
		auto retval = PED::GET_PED_SOURCE_OF_DEATH(ped);
		return retval;
	}

	static Hash LUA_NATIVE_PED_GET_PED_CAUSE_OF_DEATH(Ped ped)
	{
		auto retval = PED::GET_PED_CAUSE_OF_DEATH(ped);
		return retval;
	}

	static int LUA_NATIVE_PED_GET_PED_TIME_OF_DEATH(Ped ped)
	{
		auto retval = PED::GET_PED_TIME_OF_DEATH(ped);
		return retval;
	}

	static int LUA_NATIVE_PED_COUNT_PEDS_IN_COMBAT_WITH_TARGET(Ped ped)
	{
		auto retval = PED::COUNT_PEDS_IN_COMBAT_WITH_TARGET(ped);
		return retval;
	}

	static int LUA_NATIVE_PED_COUNT_PEDS_IN_COMBAT_WITH_TARGET_WITHIN_RADIUS(Ped ped, float x, float y, float z, float radius)
	{
		auto retval = PED::COUNT_PEDS_IN_COMBAT_WITH_TARGET_WITHIN_RADIUS(ped, x, y, z, radius);
		return retval;
	}

	static void LUA_NATIVE_PED_SET_PED_RELATIONSHIP_GROUP_DEFAULT_HASH(Ped ped, Hash hash)
	{
		PED::SET_PED_RELATIONSHIP_GROUP_DEFAULT_HASH(ped, hash);
	}

	static void LUA_NATIVE_PED_SET_PED_RELATIONSHIP_GROUP_HASH(Ped ped, Hash hash)
	{
		PED::SET_PED_RELATIONSHIP_GROUP_HASH(ped, hash);
	}

	static void LUA_NATIVE_PED_SET_RELATIONSHIP_BETWEEN_GROUPS(int relationship, Hash group1, Hash group2)
	{
		PED::SET_RELATIONSHIP_BETWEEN_GROUPS(relationship, group1, group2);
	}

	static void LUA_NATIVE_PED_CLEAR_RELATIONSHIP_BETWEEN_GROUPS(int relationship, Hash group1, Hash group2)
	{
		PED::CLEAR_RELATIONSHIP_BETWEEN_GROUPS(relationship, group1, group2);
	}

	static std::tuple<bool, Hash> LUA_NATIVE_PED_ADD_RELATIONSHIP_GROUP(sol::stack_object name, Hash groupHash)
	{
		std::tuple<bool, Hash> return_values;
		std::get<0>(return_values) = (bool)PED::ADD_RELATIONSHIP_GROUP(name.is<const char*>() ? name.as<const char*>() : nullptr, &groupHash);
		std::get<1>(return_values) = groupHash;

		return return_values;
	}

	static void LUA_NATIVE_PED_REMOVE_RELATIONSHIP_GROUP(Hash groupHash)
	{
		PED::REMOVE_RELATIONSHIP_GROUP(groupHash);
	}

	static bool LUA_NATIVE_PED_DOES_RELATIONSHIP_GROUP_EXIST(Hash groupHash)
	{
		auto retval = (bool)PED::DOES_RELATIONSHIP_GROUP_EXIST(groupHash);
		return retval;
	}

	static int LUA_NATIVE_PED_GET_RELATIONSHIP_BETWEEN_PEDS(Ped ped1, Ped ped2)
	{
		auto retval = PED::GET_RELATIONSHIP_BETWEEN_PEDS(ped1, ped2);
		return retval;
	}

	static Hash LUA_NATIVE_PED_GET_PED_RELATIONSHIP_GROUP_DEFAULT_HASH(Ped ped)
	{
		auto retval = PED::GET_PED_RELATIONSHIP_GROUP_DEFAULT_HASH(ped);
		return retval;
	}

	static Hash LUA_NATIVE_PED_GET_PED_RELATIONSHIP_GROUP_HASH(Ped ped)
	{
		auto retval = PED::GET_PED_RELATIONSHIP_GROUP_HASH(ped);
		return retval;
	}

	static int LUA_NATIVE_PED_GET_RELATIONSHIP_BETWEEN_GROUPS(Hash group1, Hash group2)
	{
		auto retval = PED::GET_RELATIONSHIP_BETWEEN_GROUPS(group1, group2);
		return retval;
	}

	static void LUA_NATIVE_PED_SET_RELATIONSHIP_GROUP_AFFECTS_WANTED_LEVEL(Hash group, bool p1)
	{
		PED::SET_RELATIONSHIP_GROUP_AFFECTS_WANTED_LEVEL(group, p1);
	}

	static void LUA_NATIVE_PED_TELL_GROUP_PEDS_IN_AREA_TO_ATTACK(Ped ped, Any p1, float p2, Hash hash, Any p4, Any p5)
	{
		PED::TELL_GROUP_PEDS_IN_AREA_TO_ATTACK(ped, p1, p2, hash, p4, p5);
	}

	static void LUA_NATIVE_PED_SET_PED_CAN_BE_TARGETED_WITHOUT_LOS(Ped ped, bool toggle)
	{
		PED::SET_PED_CAN_BE_TARGETED_WITHOUT_LOS(ped, toggle);
	}

	static void LUA_NATIVE_PED_SET_PED_TO_INFORM_RESPECTED_FRIENDS(Ped ped, float radius, int maxFriends)
	{
		PED::SET_PED_TO_INFORM_RESPECTED_FRIENDS(ped, radius, maxFriends);
	}

	static bool LUA_NATIVE_PED_IS_PED_RESPONDING_TO_EVENT(Ped ped, Any event)
	{
		auto retval = (bool)PED::IS_PED_RESPONDING_TO_EVENT(ped, event);
		return retval;
	}

	static bool LUA_NATIVE_PED_GET_POS_FROM_FIRED_EVENT(Ped ped, int eventType, uintptr_t outData)
	{
		auto retval = (bool)PED::GET_POS_FROM_FIRED_EVENT(ped, eventType, (Any*)outData);
		return retval;
	}

	static void LUA_NATIVE_PED_SET_PED_FIRING_PATTERN(Ped ped, Hash patternHash)
	{
		PED::SET_PED_FIRING_PATTERN(ped, patternHash);
	}

	static void LUA_NATIVE_PED_SET_PED_SHOOT_RATE(Ped ped, int shootRate)
	{
		PED::SET_PED_SHOOT_RATE(ped, shootRate);
	}

	static void LUA_NATIVE_PED_SET_COMBAT_FLOAT(Ped ped, int combatType, float p2)
	{
		PED::SET_COMBAT_FLOAT(ped, combatType, p2);
	}

	static float LUA_NATIVE_PED_GET_COMBAT_FLOAT(Ped ped, int p1)
	{
		auto retval = PED::GET_COMBAT_FLOAT(ped, p1);
		return retval;
	}

	static int LUA_NATIVE_PED_GET_GROUP_SIZE(int groupID, uintptr_t p1, int sizeInMembers)
	{
		PED::GET_GROUP_SIZE(groupID, (Any*)p1, &sizeInMembers);
		return sizeInMembers;
	}

	static bool LUA_NATIVE_PED_DOES_GROUP_EXIST(int groupId)
	{
		auto retval = (bool)PED::DOES_GROUP_EXIST(groupId);
		return retval;
	}

	static int LUA_NATIVE_PED_GET_PED_GROUP_INDEX(Ped ped)
	{
		auto retval = PED::GET_PED_GROUP_INDEX(ped);
		return retval;
	}

	static bool LUA_NATIVE_PED_IS_PED_IN_GROUP(Ped ped)
	{
		auto retval = (bool)PED::IS_PED_IN_GROUP(ped);
		return retval;
	}

	static Player LUA_NATIVE_PED_GET_PLAYER_PED_IS_FOLLOWING(Ped ped)
	{
		auto retval = PED::GET_PLAYER_PED_IS_FOLLOWING(ped);
		return retval;
	}

	static void LUA_NATIVE_PED_SET_GROUP_FORMATION(int groupId, int formationType)
	{
		PED::SET_GROUP_FORMATION(groupId, formationType);
	}

	static void LUA_NATIVE_PED_SET_GROUP_FORMATION_SPACING(int groupId, float x, float y, float z)
	{
		PED::SET_GROUP_FORMATION_SPACING(groupId, x, y, z);
	}

	static void LUA_NATIVE_PED_RESET_GROUP_FORMATION_DEFAULT_SPACING(int groupHandle)
	{
		PED::RESET_GROUP_FORMATION_DEFAULT_SPACING(groupHandle);
	}

	static Vehicle LUA_NATIVE_PED_GET_VEHICLE_PED_IS_USING(Ped ped)
	{
		auto retval = PED::GET_VEHICLE_PED_IS_USING(ped);
		return retval;
	}

	static Vehicle LUA_NATIVE_PED_GET_VEHICLE_PED_IS_ENTERING(Ped ped)
	{
		auto retval = PED::GET_VEHICLE_PED_IS_ENTERING(ped);
		return retval;
	}

	static void LUA_NATIVE_PED_SET_PED_GRAVITY(Ped ped, bool toggle)
	{
		PED::SET_PED_GRAVITY(ped, toggle);
	}

	static void LUA_NATIVE_PED_APPLY_DAMAGE_TO_PED(Ped ped, int damageAmount, bool p2, Any p3, Hash weaponType)
	{
		PED::APPLY_DAMAGE_TO_PED(ped, damageAmount, p2, p3, weaponType);
	}

	static int LUA_NATIVE_PED_GET_TIME_PED_DAMAGED_BY_WEAPON(Ped ped, Hash weaponHash)
	{
		auto retval = PED::GET_TIME_PED_DAMAGED_BY_WEAPON(ped, weaponHash);
		return retval;
	}

	static void LUA_NATIVE_PED_SET_PED_ALLOWED_TO_DUCK(Ped ped, bool toggle)
	{
		PED::SET_PED_ALLOWED_TO_DUCK(ped, toggle);
	}

	static void LUA_NATIVE_PED_SET_PED_NEVER_LEAVES_GROUP(Ped ped, bool toggle)
	{
		PED::SET_PED_NEVER_LEAVES_GROUP(ped, toggle);
	}

	static int LUA_NATIVE_PED_GET_PED_TYPE(Ped ped)
	{
		auto retval = PED::GET_PED_TYPE(ped);
		return retval;
	}

	static void LUA_NATIVE_PED_SET_PED_AS_COP(Ped ped, bool toggle)
	{
		PED::SET_PED_AS_COP(ped, toggle);
	}

	static void LUA_NATIVE_PED_SET_PED_HEALTH_PENDING_LAST_DAMAGE_EVENT_OVERRIDE_FLAG(bool toggle)
	{
		PED::SET_PED_HEALTH_PENDING_LAST_DAMAGE_EVENT_OVERRIDE_FLAG(toggle);
	}

	static void LUA_NATIVE_PED_SET_PED_MAX_HEALTH(Ped ped, int value)
	{
		PED::SET_PED_MAX_HEALTH(ped, value);
	}

	static int LUA_NATIVE_PED_GET_PED_MAX_HEALTH(Ped ped)
	{
		auto retval = PED::GET_PED_MAX_HEALTH(ped);
		return retval;
	}

	static void LUA_NATIVE_PED_SET_PED_MAX_TIME_IN_WATER(Ped ped, float value)
	{
		PED::SET_PED_MAX_TIME_IN_WATER(ped, value);
	}

	static void LUA_NATIVE_PED_SET_PED_MAX_TIME_UNDERWATER(Ped ped, float value)
	{
		PED::SET_PED_MAX_TIME_UNDERWATER(ped, value);
	}

	static void LUA_NATIVE_PED_SET_CORPSE_RAGDOLL_FRICTION(Ped ped, float p1)
	{
		PED::SET_CORPSE_RAGDOLL_FRICTION(ped, p1);
	}

	static void LUA_NATIVE_PED_SET_PED_VEHICLE_FORCED_SEAT_USAGE(Ped ped, Vehicle vehicle, int seatIndex, int flags, Any p4)
	{
		PED::SET_PED_VEHICLE_FORCED_SEAT_USAGE(ped, vehicle, seatIndex, flags, p4);
	}

	static void LUA_NATIVE_PED_CLEAR_ALL_PED_VEHICLE_FORCED_SEAT_USAGE(Ped ped)
	{
		PED::CLEAR_ALL_PED_VEHICLE_FORCED_SEAT_USAGE(ped);
	}

	static void LUA_NATIVE_PED_SET_PED_CAN_BE_KNOCKED_OFF_BIKE(Any p0, Any p1)
	{
		PED::SET_PED_CAN_BE_KNOCKED_OFF_BIKE(p0, p1);
	}

	static void LUA_NATIVE_PED_SET_PED_CAN_BE_KNOCKED_OFF_VEHICLE(Ped ped, int state)
	{
		PED::SET_PED_CAN_BE_KNOCKED_OFF_VEHICLE(ped, state);
	}

	static bool LUA_NATIVE_PED_CAN_KNOCK_PED_OFF_VEHICLE(Ped ped)
	{
		auto retval = (bool)PED::CAN_KNOCK_PED_OFF_VEHICLE(ped);
		return retval;
	}

	static void LUA_NATIVE_PED_KNOCK_PED_OFF_VEHICLE(Ped ped)
	{
		PED::KNOCK_PED_OFF_VEHICLE(ped);
	}

	static void LUA_NATIVE_PED_SET_PED_COORDS_NO_GANG(Ped ped, float posX, float posY, float posZ)
	{
		PED::SET_PED_COORDS_NO_GANG(ped, posX, posY, posZ);
	}

	static Ped LUA_NATIVE_PED_GET_PED_AS_GROUP_MEMBER(int groupID, int memberNumber)
	{
		auto retval = PED::GET_PED_AS_GROUP_MEMBER(groupID, memberNumber);
		return retval;
	}

	static Ped LUA_NATIVE_PED_GET_PED_AS_GROUP_LEADER(int groupID)
	{
		auto retval = PED::GET_PED_AS_GROUP_LEADER(groupID);
		return retval;
	}

	static void LUA_NATIVE_PED_SET_PED_KEEP_TASK(Ped ped, bool toggle)
	{
		PED::SET_PED_KEEP_TASK(ped, toggle);
	}

	static void LUA_NATIVE_PED_SET_PED_ALLOW_MINOR_REACTIONS_AS_MISSION_PED(Ped ped, bool toggle)
	{
		PED::SET_PED_ALLOW_MINOR_REACTIONS_AS_MISSION_PED(ped, toggle);
	}

	static bool LUA_NATIVE_PED_IS_PED_SWIMMING(Ped ped)
	{
		auto retval = (bool)PED::IS_PED_SWIMMING(ped);
		return retval;
	}

	static bool LUA_NATIVE_PED_IS_PED_SWIMMING_UNDER_WATER(Ped ped)
	{
		auto retval = (bool)PED::IS_PED_SWIMMING_UNDER_WATER(ped);
		return retval;
	}

	static void LUA_NATIVE_PED_SET_PED_COORDS_KEEP_VEHICLE(Ped ped, float posX, float posY, float posZ)
	{
		PED::SET_PED_COORDS_KEEP_VEHICLE(ped, posX, posY, posZ);
	}

	static void LUA_NATIVE_PED_SET_PED_DIES_IN_VEHICLE(Ped ped, bool toggle)
	{
		PED::SET_PED_DIES_IN_VEHICLE(ped, toggle);
	}

	static void LUA_NATIVE_PED_SET_CREATE_RANDOM_COPS(bool toggle)
	{
		PED::SET_CREATE_RANDOM_COPS(toggle);
	}

	static void LUA_NATIVE_PED_SET_CREATE_RANDOM_COPS_NOT_ON_SCENARIOS(bool toggle)
	{
		PED::SET_CREATE_RANDOM_COPS_NOT_ON_SCENARIOS(toggle);
	}

	static void LUA_NATIVE_PED_SET_CREATE_RANDOM_COPS_ON_SCENARIOS(bool toggle)
	{
		PED::SET_CREATE_RANDOM_COPS_ON_SCENARIOS(toggle);
	}

	static bool LUA_NATIVE_PED_CAN_CREATE_RANDOM_COPS()
	{
		auto retval = (bool)PED::CAN_CREATE_RANDOM_COPS();
		return retval;
	}

	static void LUA_NATIVE_PED_SET_PED_AS_ENEMY(Ped ped, bool toggle)
	{
		PED::SET_PED_AS_ENEMY(ped, toggle);
	}

	static void LUA_NATIVE_PED_SET_PED_CAN_SMASH_GLASS(Ped ped, bool p1, bool p2)
	{
		PED::SET_PED_CAN_SMASH_GLASS(ped, p1, p2);
	}

	static bool LUA_NATIVE_PED_IS_PED_IN_ANY_TRAIN(Ped ped)
	{
		auto retval = (bool)PED::IS_PED_IN_ANY_TRAIN(ped);
		return retval;
	}

	static bool LUA_NATIVE_PED_IS_PED_GETTING_INTO_A_VEHICLE(Ped ped)
	{
		auto retval = (bool)PED::IS_PED_GETTING_INTO_A_VEHICLE(ped);
		return retval;
	}

	static bool LUA_NATIVE_PED_IS_PED_TRYING_TO_ENTER_A_LOCKED_VEHICLE(Ped ped)
	{
		auto retval = (bool)PED::IS_PED_TRYING_TO_ENTER_A_LOCKED_VEHICLE(ped);
		return retval;
	}

	static void LUA_NATIVE_PED_SET_ENABLE_HANDCUFFS(Ped ped, bool toggle)
	{
		PED::SET_ENABLE_HANDCUFFS(ped, toggle);
	}

	static void LUA_NATIVE_PED_SET_ENABLE_BOUND_ANKLES(Ped ped, bool toggle)
	{
		PED::SET_ENABLE_BOUND_ANKLES(ped, toggle);
	}

	static void LUA_NATIVE_PED_SET_ENABLE_SCUBA(Ped ped, bool toggle)
	{
		PED::SET_ENABLE_SCUBA(ped, toggle);
	}

	static void LUA_NATIVE_PED_SET_CAN_ATTACK_FRIENDLY(Ped ped, bool toggle, bool p2)
	{
		PED::SET_CAN_ATTACK_FRIENDLY(ped, toggle, p2);
	}

	static int LUA_NATIVE_PED_GET_PED_ALERTNESS(Ped ped)
	{
		auto retval = PED::GET_PED_ALERTNESS(ped);
		return retval;
	}

	static void LUA_NATIVE_PED_SET_PED_ALERTNESS(Ped ped, int value)
	{
		PED::SET_PED_ALERTNESS(ped, value);
	}

	static void LUA_NATIVE_PED_SET_PED_GET_OUT_UPSIDE_DOWN_VEHICLE(Ped ped, bool toggle)
	{
		PED::SET_PED_GET_OUT_UPSIDE_DOWN_VEHICLE(ped, toggle);
	}

	static void LUA_NATIVE_PED_SET_PED_MOVEMENT_CLIPSET(Ped ped, sol::stack_object clipSet, float transitionSpeed)
	{
		PED::SET_PED_MOVEMENT_CLIPSET(ped, clipSet.is<const char*>() ? clipSet.as<const char*>() : nullptr, transitionSpeed);
	}

	static void LUA_NATIVE_PED_RESET_PED_MOVEMENT_CLIPSET(Ped ped, float p1)
	{
		PED::RESET_PED_MOVEMENT_CLIPSET(ped, p1);
	}

	static void LUA_NATIVE_PED_SET_PED_STRAFE_CLIPSET(Ped ped, sol::stack_object clipSet)
	{
		PED::SET_PED_STRAFE_CLIPSET(ped, clipSet.is<const char*>() ? clipSet.as<const char*>() : nullptr);
	}

	static void LUA_NATIVE_PED_RESET_PED_STRAFE_CLIPSET(Ped ped)
	{
		PED::RESET_PED_STRAFE_CLIPSET(ped);
	}

	static void LUA_NATIVE_PED_SET_PED_WEAPON_MOVEMENT_CLIPSET(Ped ped, sol::stack_object clipSet)
	{
		PED::SET_PED_WEAPON_MOVEMENT_CLIPSET(ped, clipSet.is<const char*>() ? clipSet.as<const char*>() : nullptr);
	}

	static void LUA_NATIVE_PED_RESET_PED_WEAPON_MOVEMENT_CLIPSET(Ped ped)
	{
		PED::RESET_PED_WEAPON_MOVEMENT_CLIPSET(ped);
	}

	static void LUA_NATIVE_PED_SET_PED_DRIVE_BY_CLIPSET_OVERRIDE(Ped ped, sol::stack_object clipset)
	{
		PED::SET_PED_DRIVE_BY_CLIPSET_OVERRIDE(ped, clipset.is<const char*>() ? clipset.as<const char*>() : nullptr);
	}

	static void LUA_NATIVE_PED_CLEAR_PED_DRIVE_BY_CLIPSET_OVERRIDE(Ped ped)
	{
		PED::CLEAR_PED_DRIVE_BY_CLIPSET_OVERRIDE(ped);
	}

	static void LUA_NATIVE_PED_SET_PED_MOTION_IN_COVER_CLIPSET_OVERRIDE(Ped ped, sol::stack_object p1)
	{
		PED::SET_PED_MOTION_IN_COVER_CLIPSET_OVERRIDE(ped, p1.is<const char*>() ? p1.as<const char*>() : nullptr);
	}

	static void LUA_NATIVE_PED_CLEAR_PED_MOTION_IN_COVER_CLIPSET_OVERRIDE(Ped ped)
	{
		PED::CLEAR_PED_MOTION_IN_COVER_CLIPSET_OVERRIDE(ped);
	}

	static void LUA_NATIVE_PED_CLEAR_PED_FALL_UPPER_BODY_CLIPSET_OVERRIDE(Ped ped)
	{
		PED::CLEAR_PED_FALL_UPPER_BODY_CLIPSET_OVERRIDE(ped);
	}

	static void LUA_NATIVE_PED_SET_PED_IN_VEHICLE_CONTEXT(Ped ped, Hash context)
	{
		PED::SET_PED_IN_VEHICLE_CONTEXT(ped, context);
	}

	static void LUA_NATIVE_PED_RESET_PED_IN_VEHICLE_CONTEXT(Ped ped)
	{
		PED::RESET_PED_IN_VEHICLE_CONTEXT(ped);
	}

	static bool LUA_NATIVE_PED_IS_SCRIPTED_SCENARIO_PED_USING_CONDITIONAL_ANIM(Ped ped, sol::stack_object animDict, sol::stack_object anim)
	{
		auto retval = (bool)PED::IS_SCRIPTED_SCENARIO_PED_USING_CONDITIONAL_ANIM(ped, animDict.is<const char*>() ? animDict.as<const char*>() : nullptr, anim.is<const char*>() ? anim.as<const char*>() : nullptr);
		return retval;
	}

	static void LUA_NATIVE_PED_SET_PED_ALTERNATE_WALK_ANIM(Ped ped, sol::stack_object animDict, sol::stack_object animName, float p3, bool p4)
	{
		PED::SET_PED_ALTERNATE_WALK_ANIM(ped, animDict.is<const char*>() ? animDict.as<const char*>() : nullptr, animName.is<const char*>() ? animName.as<const char*>() : nullptr, p3, p4);
	}

	static void LUA_NATIVE_PED_CLEAR_PED_ALTERNATE_WALK_ANIM(Ped ped, float p1)
	{
		PED::CLEAR_PED_ALTERNATE_WALK_ANIM(ped, p1);
	}

	static void LUA_NATIVE_PED_SET_PED_ALTERNATE_MOVEMENT_ANIM(Ped ped, int stance, sol::stack_object animDictionary, sol::stack_object animationName, float p4, bool p5)
	{
		PED::SET_PED_ALTERNATE_MOVEMENT_ANIM(ped, stance, animDictionary.is<const char*>() ? animDictionary.as<const char*>() : nullptr, animationName.is<const char*>() ? animationName.as<const char*>() : nullptr, p4, p5);
	}

	static void LUA_NATIVE_PED_CLEAR_PED_ALTERNATE_MOVEMENT_ANIM(Ped ped, int stance, float p2)
	{
		PED::CLEAR_PED_ALTERNATE_MOVEMENT_ANIM(ped, stance, p2);
	}

	static void LUA_NATIVE_PED_SET_PED_GESTURE_GROUP(Ped ped, sol::stack_object animGroupGesture)
	{
		PED::SET_PED_GESTURE_GROUP(ped, animGroupGesture.is<const char*>() ? animGroupGesture.as<const char*>() : nullptr);
	}

	static Vector3 LUA_NATIVE_PED_GET_ANIM_INITIAL_OFFSET_POSITION(sol::stack_object animDict, sol::stack_object animName, float x, float y, float z, float xRot, float yRot, float zRot, float p8, int p9)
	{
		auto retval = PED::GET_ANIM_INITIAL_OFFSET_POSITION(animDict.is<const char*>() ? animDict.as<const char*>() : nullptr, animName.is<const char*>() ? animName.as<const char*>() : nullptr, x, y, z, xRot, yRot, zRot, p8, p9);
		return retval;
	}

	static Vector3 LUA_NATIVE_PED_GET_ANIM_INITIAL_OFFSET_ROTATION(sol::stack_object animDict, sol::stack_object animName, float x, float y, float z, float xRot, float yRot, float zRot, float p8, int p9)
	{
		auto retval = PED::GET_ANIM_INITIAL_OFFSET_ROTATION(animDict.is<const char*>() ? animDict.as<const char*>() : nullptr, animName.is<const char*>() ? animName.as<const char*>() : nullptr, x, y, z, xRot, yRot, zRot, p8, p9);
		return retval;
	}

	static int LUA_NATIVE_PED_GET_PED_DRAWABLE_VARIATION(Ped ped, int componentId)
	{
		auto retval = PED::GET_PED_DRAWABLE_VARIATION(ped, componentId);
		return retval;
	}

	static int LUA_NATIVE_PED_GET_NUMBER_OF_PED_DRAWABLE_VARIATIONS(Ped ped, int componentId)
	{
		auto retval = PED::GET_NUMBER_OF_PED_DRAWABLE_VARIATIONS(ped, componentId);
		return retval;
	}

	static int LUA_NATIVE_PED_GET_PED_TEXTURE_VARIATION(Ped ped, int componentId)
	{
		auto retval = PED::GET_PED_TEXTURE_VARIATION(ped, componentId);
		return retval;
	}

	static int LUA_NATIVE_PED_GET_NUMBER_OF_PED_TEXTURE_VARIATIONS(Ped ped, int componentId, int drawableId)
	{
		auto retval = PED::GET_NUMBER_OF_PED_TEXTURE_VARIATIONS(ped, componentId, drawableId);
		return retval;
	}

	static int LUA_NATIVE_PED_GET_NUMBER_OF_PED_PROP_DRAWABLE_VARIATIONS(Ped ped, int propId)
	{
		auto retval = PED::GET_NUMBER_OF_PED_PROP_DRAWABLE_VARIATIONS(ped, propId);
		return retval;
	}

	static int LUA_NATIVE_PED_GET_NUMBER_OF_PED_PROP_TEXTURE_VARIATIONS(Ped ped, int propId, int drawableId)
	{
		auto retval = PED::GET_NUMBER_OF_PED_PROP_TEXTURE_VARIATIONS(ped, propId, drawableId);
		return retval;
	}

	static int LUA_NATIVE_PED_GET_PED_PALETTE_VARIATION(Ped ped, int componentId)
	{
		auto retval = PED::GET_PED_PALETTE_VARIATION(ped, componentId);
		return retval;
	}

	static bool LUA_NATIVE_PED_GET_MP_OUTFIT_DATA_FROM_METADATA(uintptr_t p0, uintptr_t p1)
	{
		auto retval = (bool)PED::GET_MP_OUTFIT_DATA_FROM_METADATA((Any*)p0, (Any*)p1);
		return retval;
	}

	static int LUA_NATIVE_PED_GET_FM_MALE_SHOP_PED_APPAREL_ITEM_INDEX(int p0)
	{
		auto retval = PED::GET_FM_MALE_SHOP_PED_APPAREL_ITEM_INDEX(p0);
		return retval;
	}

	static int LUA_NATIVE_PED_GET_FM_FEMALE_SHOP_PED_APPAREL_ITEM_INDEX(int p0)
	{
		auto retval = PED::GET_FM_FEMALE_SHOP_PED_APPAREL_ITEM_INDEX(p0);
		return retval;
	}

	static bool LUA_NATIVE_PED_IS_PED_COMPONENT_VARIATION_VALID(Ped ped, int componentId, int drawableId, int textureId)
	{
		auto retval = (bool)PED::IS_PED_COMPONENT_VARIATION_VALID(ped, componentId, drawableId, textureId);
		return retval;
	}

	static void LUA_NATIVE_PED_SET_PED_COMPONENT_VARIATION(Ped ped, int componentId, int drawableId, int textureId, int paletteId)
	{
		PED::SET_PED_COMPONENT_VARIATION(ped, componentId, drawableId, textureId, paletteId);
	}

	static void LUA_NATIVE_PED_SET_PED_RANDOM_COMPONENT_VARIATION(Ped ped, int p1)
	{
		PED::SET_PED_RANDOM_COMPONENT_VARIATION(ped, p1);
	}

	static void LUA_NATIVE_PED_SET_PED_RANDOM_PROPS(Ped ped)
	{
		PED::SET_PED_RANDOM_PROPS(ped);
	}

	static void LUA_NATIVE_PED_SET_PED_DEFAULT_COMPONENT_VARIATION(Ped ped)
	{
		PED::SET_PED_DEFAULT_COMPONENT_VARIATION(ped);
	}

	static void LUA_NATIVE_PED_SET_PED_BLEND_FROM_PARENTS(Ped ped, Any p1, Any p2, float p3, float p4)
	{
		PED::SET_PED_BLEND_FROM_PARENTS(ped, p1, p2, p3, p4);
	}

	static void LUA_NATIVE_PED_SET_PED_HEAD_BLEND_DATA(Ped ped, int shapeFirstID, int shapeSecondID, int shapeThirdID, int skinFirstID, int skinSecondID, int skinThirdID, float shapeMix, float skinMix, float thirdMix, bool isParent)
	{
		PED::SET_PED_HEAD_BLEND_DATA(ped, shapeFirstID, shapeSecondID, shapeThirdID, skinFirstID, skinSecondID, skinThirdID, shapeMix, skinMix, thirdMix, isParent);
	}

	static bool LUA_NATIVE_PED_GET_PED_HEAD_BLEND_DATA(Ped ped, uintptr_t headBlendData)
	{
		auto retval = (bool)PED::GET_PED_HEAD_BLEND_DATA(ped, (Any*)headBlendData);
		return retval;
	}

	static void LUA_NATIVE_PED_UPDATE_PED_HEAD_BLEND_DATA(Ped ped, float shapeMix, float skinMix, float thirdMix)
	{
		PED::UPDATE_PED_HEAD_BLEND_DATA(ped, shapeMix, skinMix, thirdMix);
	}

	static void LUA_NATIVE_PED_SET_HEAD_BLEND_EYE_COLOR(Ped ped, int index)
	{
		PED::SET_HEAD_BLEND_EYE_COLOR(ped, index);
	}

	static int LUA_NATIVE_PED_GET_HEAD_BLEND_EYE_COLOR(Ped ped)
	{
		auto retval = PED::GET_HEAD_BLEND_EYE_COLOR(ped);
		return retval;
	}

	static void LUA_NATIVE_PED_SET_PED_HEAD_OVERLAY(Ped ped, int overlayID, int index, float opacity)
	{
		PED::SET_PED_HEAD_OVERLAY(ped, overlayID, index, opacity);
	}

	static int LUA_NATIVE_PED_GET_PED_HEAD_OVERLAY(Ped ped, int overlayID)
	{
		auto retval = PED::GET_PED_HEAD_OVERLAY(ped, overlayID);
		return retval;
	}

	static int LUA_NATIVE_PED_GET_PED_HEAD_OVERLAY_NUM(int overlayID)
	{
		auto retval = PED::GET_PED_HEAD_OVERLAY_NUM(overlayID);
		return retval;
	}

	static void LUA_NATIVE_PED_SET_PED_HEAD_OVERLAY_TINT(Ped ped, int overlayID, int colorType, int colorID, int secondColorID)
	{
		PED::SET_PED_HEAD_OVERLAY_TINT(ped, overlayID, colorType, colorID, secondColorID);
	}

	static void LUA_NATIVE_PED_SET_PED_HAIR_TINT(Ped ped, int colorID, int highlightColorID)
	{
		PED::SET_PED_HAIR_TINT(ped, colorID, highlightColorID);
	}

	static int LUA_NATIVE_PED_GET_NUM_PED_HAIR_TINTS()
	{
		auto retval = PED::GET_NUM_PED_HAIR_TINTS();
		return retval;
	}

	static int LUA_NATIVE_PED_GET_NUM_PED_MAKEUP_TINTS()
	{
		auto retval = PED::GET_NUM_PED_MAKEUP_TINTS();
		return retval;
	}

	static std::tuple<int, int, int> LUA_NATIVE_PED_GET_PED_HAIR_TINT_COLOR(int hairColorIndex, int outR, int outG, int outB)
	{
		std::tuple<int, int, int> return_values;
		PED::GET_PED_HAIR_TINT_COLOR(hairColorIndex, &outR, &outG, &outB);
		std::get<0>(return_values) = outR;
		std::get<1>(return_values) = outG;
		std::get<2>(return_values) = outB;

		return return_values;
	}

	static std::tuple<int, int, int> LUA_NATIVE_PED_GET_PED_MAKEUP_TINT_COLOR(int makeupColorIndex, int outR, int outG, int outB)
	{
		std::tuple<int, int, int> return_values;
		PED::GET_PED_MAKEUP_TINT_COLOR(makeupColorIndex, &outR, &outG, &outB);
		std::get<0>(return_values) = outR;
		std::get<1>(return_values) = outG;
		std::get<2>(return_values) = outB;

		return return_values;
	}

	static bool LUA_NATIVE_PED_IS_PED_HAIR_TINT_FOR_CREATOR(int colorId)
	{
		auto retval = (bool)PED::IS_PED_HAIR_TINT_FOR_CREATOR(colorId);
		return retval;
	}

	static int LUA_NATIVE_PED_GET_DEFAULT_SECONDARY_TINT_FOR_CREATOR(int colorId)
	{
		auto retval = PED::GET_DEFAULT_SECONDARY_TINT_FOR_CREATOR(colorId);
		return retval;
	}

	static bool LUA_NATIVE_PED_IS_PED_LIPSTICK_TINT_FOR_CREATOR(int colorId)
	{
		auto retval = (bool)PED::IS_PED_LIPSTICK_TINT_FOR_CREATOR(colorId);
		return retval;
	}

	static bool LUA_NATIVE_PED_IS_PED_BLUSH_TINT_FOR_CREATOR(int colorId)
	{
		auto retval = (bool)PED::IS_PED_BLUSH_TINT_FOR_CREATOR(colorId);
		return retval;
	}

	static bool LUA_NATIVE_PED_IS_PED_HAIR_TINT_FOR_BARBER(int colorID)
	{
		auto retval = (bool)PED::IS_PED_HAIR_TINT_FOR_BARBER(colorID);
		return retval;
	}

	static int LUA_NATIVE_PED_GET_DEFAULT_SECONDARY_TINT_FOR_BARBER(int colorID)
	{
		auto retval = PED::GET_DEFAULT_SECONDARY_TINT_FOR_BARBER(colorID);
		return retval;
	}

	static bool LUA_NATIVE_PED_IS_PED_LIPSTICK_TINT_FOR_BARBER(int colorID)
	{
		auto retval = (bool)PED::IS_PED_LIPSTICK_TINT_FOR_BARBER(colorID);
		return retval;
	}

	static bool LUA_NATIVE_PED_IS_PED_BLUSH_TINT_FOR_BARBER(int colorID)
	{
		auto retval = (bool)PED::IS_PED_BLUSH_TINT_FOR_BARBER(colorID);
		return retval;
	}

	static bool LUA_NATIVE_PED_IS_PED_BLUSH_FACEPAINT_TINT_FOR_BARBER(int colorId)
	{
		auto retval = (bool)PED::IS_PED_BLUSH_FACEPAINT_TINT_FOR_BARBER(colorId);
		return retval;
	}

	static int LUA_NATIVE_PED_GET_TINT_INDEX_FOR_LAST_GEN_HAIR_TEXTURE(Hash modelHash, int drawableId, int textureId)
	{
		auto retval = PED::GET_TINT_INDEX_FOR_LAST_GEN_HAIR_TEXTURE(modelHash, drawableId, textureId);
		return retval;
	}

	static void LUA_NATIVE_PED_SET_PED_MICRO_MORPH(Ped ped, int index, float scale)
	{
		PED::SET_PED_MICRO_MORPH(ped, index, scale);
	}

	static bool LUA_NATIVE_PED_HAS_PED_HEAD_BLEND_FINISHED(Ped ped)
	{
		auto retval = (bool)PED::HAS_PED_HEAD_BLEND_FINISHED(ped);
		return retval;
	}

	static void LUA_NATIVE_PED_FINALIZE_HEAD_BLEND(Ped ped)
	{
		PED::FINALIZE_HEAD_BLEND(ped);
	}

	static void LUA_NATIVE_PED_SET_HEAD_BLEND_PALETTE_COLOR(Ped ped, int r, int g, int b, int id)
	{
		PED::SET_HEAD_BLEND_PALETTE_COLOR(ped, r, g, b, id);
	}

	static void LUA_NATIVE_PED_DISABLE_HEAD_BLEND_PALETTE_COLOR(Ped ped)
	{
		PED::DISABLE_HEAD_BLEND_PALETTE_COLOR(ped);
	}

	static int LUA_NATIVE_PED_GET_PED_HEAD_BLEND_FIRST_INDEX(int type)
	{
		auto retval = PED::GET_PED_HEAD_BLEND_FIRST_INDEX(type);
		return retval;
	}

	static int LUA_NATIVE_PED_GET_PED_HEAD_BLEND_NUM_HEADS(int type)
	{
		auto retval = PED::GET_PED_HEAD_BLEND_NUM_HEADS(type);
		return retval;
	}

	static int LUA_NATIVE_PED_SET_PED_PRELOAD_VARIATION_DATA(Ped ped, int slot, int drawableId, int textureId)
	{
		auto retval = PED::SET_PED_PRELOAD_VARIATION_DATA(ped, slot, drawableId, textureId);
		return retval;
	}

	static bool LUA_NATIVE_PED_HAS_PED_PRELOAD_VARIATION_DATA_FINISHED(Ped ped)
	{
		auto retval = (bool)PED::HAS_PED_PRELOAD_VARIATION_DATA_FINISHED(ped);
		return retval;
	}

	static void LUA_NATIVE_PED_RELEASE_PED_PRELOAD_VARIATION_DATA(Ped ped)
	{
		PED::RELEASE_PED_PRELOAD_VARIATION_DATA(ped);
	}

	static int LUA_NATIVE_PED_SET_PED_PRELOAD_PROP_DATA(Ped ped, int componentId, int drawableId, int TextureId)
	{
		auto retval = PED::SET_PED_PRELOAD_PROP_DATA(ped, componentId, drawableId, TextureId);
		return retval;
	}

	static bool LUA_NATIVE_PED_HAS_PED_PRELOAD_PROP_DATA_FINISHED(Ped ped)
	{
		auto retval = (bool)PED::HAS_PED_PRELOAD_PROP_DATA_FINISHED(ped);
		return retval;
	}

	static void LUA_NATIVE_PED_RELEASE_PED_PRELOAD_PROP_DATA(Ped ped)
	{
		PED::RELEASE_PED_PRELOAD_PROP_DATA(ped);
	}

	static int LUA_NATIVE_PED_GET_PED_PROP_INDEX(Ped ped, int componentId, Any p2)
	{
		auto retval = PED::GET_PED_PROP_INDEX(ped, componentId, p2);
		return retval;
	}

	static void LUA_NATIVE_PED_SET_PED_PROP_INDEX(Ped ped, int componentId, int drawableId, int TextureId, bool attach, Any p5)
	{
		PED::SET_PED_PROP_INDEX(ped, componentId, drawableId, TextureId, attach, p5);
	}

	static void LUA_NATIVE_PED_KNOCK_OFF_PED_PROP(Ped ped, bool p1, bool p2, bool p3, bool p4)
	{
		PED::KNOCK_OFF_PED_PROP(ped, p1, p2, p3, p4);
	}

	static void LUA_NATIVE_PED_CLEAR_PED_PROP(Ped ped, int propId, Any p2)
	{
		PED::CLEAR_PED_PROP(ped, propId, p2);
	}

	static void LUA_NATIVE_PED_CLEAR_ALL_PED_PROPS(Ped ped, Any p1)
	{
		PED::CLEAR_ALL_PED_PROPS(ped, p1);
	}

	static void LUA_NATIVE_PED_DROP_AMBIENT_PROP(Ped ped)
	{
		PED::DROP_AMBIENT_PROP(ped);
	}

	static int LUA_NATIVE_PED_GET_PED_PROP_TEXTURE_INDEX(Ped ped, int componentId)
	{
		auto retval = PED::GET_PED_PROP_TEXTURE_INDEX(ped, componentId);
		return retval;
	}

	static void LUA_NATIVE_PED_CLEAR_PED_PARACHUTE_PACK_VARIATION(Ped ped)
	{
		PED::CLEAR_PED_PARACHUTE_PACK_VARIATION(ped);
	}

	static void LUA_NATIVE_PED_SET_PED_SCUBA_GEAR_VARIATION(Ped ped)
	{
		PED::SET_PED_SCUBA_GEAR_VARIATION(ped);
	}

	static void LUA_NATIVE_PED_CLEAR_PED_SCUBA_GEAR_VARIATION(Ped ped)
	{
		PED::CLEAR_PED_SCUBA_GEAR_VARIATION(ped);
	}

	static bool LUA_NATIVE_PED_IS_USING_PED_SCUBA_GEAR_VARIATION(Any p0)
	{
		auto retval = (bool)PED::IS_USING_PED_SCUBA_GEAR_VARIATION(p0);
		return retval;
	}

	static void LUA_NATIVE_PED_SET_BLOCKING_OF_NON_TEMPORARY_EVENTS(Ped ped, bool toggle)
	{
		PED::SET_BLOCKING_OF_NON_TEMPORARY_EVENTS(ped, toggle);
	}

	static void LUA_NATIVE_PED_SET_PED_BOUNDS_ORIENTATION(Ped ped, float p1, float p2, float x, float y, float z)
	{
		PED::SET_PED_BOUNDS_ORIENTATION(ped, p1, p2, x, y, z);
	}

	static void LUA_NATIVE_PED_REGISTER_TARGET(Ped ped, Ped target)
	{
		PED::REGISTER_TARGET(ped, target);
	}

	static void LUA_NATIVE_PED_REGISTER_HATED_TARGETS_AROUND_PED(Ped ped, float radius)
	{
		PED::REGISTER_HATED_TARGETS_AROUND_PED(ped, radius);
	}

	static Ped LUA_NATIVE_PED_GET_RANDOM_PED_AT_COORD(float x, float y, float z, float xRadius, float yRadius, float zRadius, int pedType)
	{
		auto retval = PED::GET_RANDOM_PED_AT_COORD(x, y, z, xRadius, yRadius, zRadius, pedType);
		return retval;
	}

	static std::tuple<bool, Ped> LUA_NATIVE_PED_GET_CLOSEST_PED(float x, float y, float z, float radius, bool p4, bool p5, Ped outPed, bool p7, bool p8, int pedType)
	{
		std::tuple<bool, Ped> return_values;
		std::get<0>(return_values) = (bool)PED::GET_CLOSEST_PED(x, y, z, radius, p4, p5, &outPed, p7, p8, pedType);
		std::get<1>(return_values) = outPed;

		return return_values;
	}

	static void LUA_NATIVE_PED_SET_SCENARIO_PEDS_TO_BE_RETURNED_BY_NEXT_COMMAND(bool value)
	{
		PED::SET_SCENARIO_PEDS_TO_BE_RETURNED_BY_NEXT_COMMAND(value);
	}

	static bool LUA_NATIVE_PED_GET_CAN_PED_BE_GRABBED_BY_SCRIPT(Ped ped, bool p1, bool p2, bool p3, bool p4, bool p5, bool p6, bool p7, Any p8)
	{
		auto retval = (bool)PED::GET_CAN_PED_BE_GRABBED_BY_SCRIPT(ped, p1, p2, p3, p4, p5, p6, p7, p8);
		return retval;
	}

	static void LUA_NATIVE_PED_SET_DRIVER_RACING_MODIFIER(Ped driver, float modifier)
	{
		PED::SET_DRIVER_RACING_MODIFIER(driver, modifier);
	}

	static void LUA_NATIVE_PED_SET_DRIVER_ABILITY(Ped driver, float ability)
	{
		PED::SET_DRIVER_ABILITY(driver, ability);
	}

	static void LUA_NATIVE_PED_SET_DRIVER_AGGRESSIVENESS(Ped driver, float aggressiveness)
	{
		PED::SET_DRIVER_AGGRESSIVENESS(driver, aggressiveness);
	}

	static bool LUA_NATIVE_PED_CAN_PED_RAGDOLL(Ped ped)
	{
		auto retval = (bool)PED::CAN_PED_RAGDOLL(ped);
		return retval;
	}

	static bool LUA_NATIVE_PED_SET_PED_TO_RAGDOLL(Ped ped, int time1, int time2, int ragdollType, bool p4, bool p5, bool p6)
	{
		auto retval = (bool)PED::SET_PED_TO_RAGDOLL(ped, time1, time2, ragdollType, p4, p5, p6);
		return retval;
	}

	static bool LUA_NATIVE_PED_SET_PED_TO_RAGDOLL_WITH_FALL(Ped ped, int time, int p2, int ragdollType, float x, float y, float z, float velocity, float p8, float p9, float p10, float p11, float p12, float p13)
	{
		auto retval = (bool)PED::SET_PED_TO_RAGDOLL_WITH_FALL(ped, time, p2, ragdollType, x, y, z, velocity, p8, p9, p10, p11, p12, p13);
		return retval;
	}

	static void LUA_NATIVE_PED_SET_PED_RAGDOLL_ON_COLLISION(Ped ped, bool toggle)
	{
		PED::SET_PED_RAGDOLL_ON_COLLISION(ped, toggle);
	}

	static bool LUA_NATIVE_PED_IS_PED_RAGDOLL(Ped ped)
	{
		auto retval = (bool)PED::IS_PED_RAGDOLL(ped);
		return retval;
	}

	static bool LUA_NATIVE_PED_IS_PED_RUNNING_RAGDOLL_TASK(Ped ped)
	{
		auto retval = (bool)PED::IS_PED_RUNNING_RAGDOLL_TASK(ped);
		return retval;
	}

	static void LUA_NATIVE_PED_SET_PED_RAGDOLL_FORCE_FALL(Ped ped)
	{
		PED::SET_PED_RAGDOLL_FORCE_FALL(ped);
	}

	static void LUA_NATIVE_PED_RESET_PED_RAGDOLL_TIMER(Ped ped)
	{
		PED::RESET_PED_RAGDOLL_TIMER(ped);
	}

	static void LUA_NATIVE_PED_SET_PED_CAN_RAGDOLL(Ped ped, bool toggle)
	{
		PED::SET_PED_CAN_RAGDOLL(ped, toggle);
	}

	static bool LUA_NATIVE_PED_IS_PED_RUNNING_MELEE_TASK(Ped ped)
	{
		auto retval = (bool)PED::IS_PED_RUNNING_MELEE_TASK(ped);
		return retval;
	}

	static bool LUA_NATIVE_PED_IS_PED_RUNNING_MOBILE_PHONE_TASK(Ped ped)
	{
		auto retval = (bool)PED::IS_PED_RUNNING_MOBILE_PHONE_TASK(ped);
		return retval;
	}

	static bool LUA_NATIVE_PED_IS_MOBILE_PHONE_TO_PED_EAR(Ped ped)
	{
		auto retval = (bool)PED::IS_MOBILE_PHONE_TO_PED_EAR(ped);
		return retval;
	}

	static void LUA_NATIVE_PED_SET_RAGDOLL_BLOCKING_FLAGS(Ped ped, int blockingFlag)
	{
		PED::SET_RAGDOLL_BLOCKING_FLAGS(ped, blockingFlag);
	}

	static void LUA_NATIVE_PED_CLEAR_RAGDOLL_BLOCKING_FLAGS(Ped ped, int blockingFlag)
	{
		PED::CLEAR_RAGDOLL_BLOCKING_FLAGS(ped, blockingFlag);
	}

	static void LUA_NATIVE_PED_SET_PED_ANGLED_DEFENSIVE_AREA(Ped ped, float p1, float p2, float p3, float p4, float p5, float p6, float p7, bool p8, bool p9)
	{
		PED::SET_PED_ANGLED_DEFENSIVE_AREA(ped, p1, p2, p3, p4, p5, p6, p7, p8, p9);
	}

	static void LUA_NATIVE_PED_SET_PED_SPHERE_DEFENSIVE_AREA(Ped ped, float x, float y, float z, float radius, bool p5, bool p6)
	{
		PED::SET_PED_SPHERE_DEFENSIVE_AREA(ped, x, y, z, radius, p5, p6);
	}

	static void LUA_NATIVE_PED_SET_PED_DEFENSIVE_SPHERE_ATTACHED_TO_PED(Ped ped, Ped target, float xOffset, float yOffset, float zOffset, float radius, bool p6)
	{
		PED::SET_PED_DEFENSIVE_SPHERE_ATTACHED_TO_PED(ped, target, xOffset, yOffset, zOffset, radius, p6);
	}

	static void LUA_NATIVE_PED_SET_PED_DEFENSIVE_SPHERE_ATTACHED_TO_VEHICLE(Ped ped, Vehicle target, float xOffset, float yOffset, float zOffset, float radius, bool p6)
	{
		PED::SET_PED_DEFENSIVE_SPHERE_ATTACHED_TO_VEHICLE(ped, target, xOffset, yOffset, zOffset, radius, p6);
	}

	static void LUA_NATIVE_PED_SET_PED_DEFENSIVE_AREA_ATTACHED_TO_PED(Ped ped, Ped attachPed, float p2, float p3, float p4, float p5, float p6, float p7, float p8, bool p9, bool p10)
	{
		PED::SET_PED_DEFENSIVE_AREA_ATTACHED_TO_PED(ped, attachPed, p2, p3, p4, p5, p6, p7, p8, p9, p10);
	}

	static void LUA_NATIVE_PED_SET_PED_DEFENSIVE_AREA_DIRECTION(Ped ped, float p1, float p2, float p3, bool p4)
	{
		PED::SET_PED_DEFENSIVE_AREA_DIRECTION(ped, p1, p2, p3, p4);
	}

	static void LUA_NATIVE_PED_REMOVE_PED_DEFENSIVE_AREA(Ped ped, bool toggle)
	{
		PED::REMOVE_PED_DEFENSIVE_AREA(ped, toggle);
	}

	static Vector3 LUA_NATIVE_PED_GET_PED_DEFENSIVE_AREA_POSITION(Ped ped, bool p1)
	{
		auto retval = PED::GET_PED_DEFENSIVE_AREA_POSITION(ped, p1);
		return retval;
	}

	static bool LUA_NATIVE_PED_IS_PED_DEFENSIVE_AREA_ACTIVE(Ped ped, bool p1)
	{
		auto retval = (bool)PED::IS_PED_DEFENSIVE_AREA_ACTIVE(ped, p1);
		return retval;
	}

	static void LUA_NATIVE_PED_SET_PED_PREFERRED_COVER_SET(Ped ped, Any itemSet)
	{
		PED::SET_PED_PREFERRED_COVER_SET(ped, itemSet);
	}

	static void LUA_NATIVE_PED_REMOVE_PED_PREFERRED_COVER_SET(Ped ped)
	{
		PED::REMOVE_PED_PREFERRED_COVER_SET(ped);
	}

	static void LUA_NATIVE_PED_REVIVE_INJURED_PED(Ped ped)
	{
		PED::REVIVE_INJURED_PED(ped);
	}

	static void LUA_NATIVE_PED_RESURRECT_PED(Ped ped)
	{
		PED::RESURRECT_PED(ped);
	}

	static void LUA_NATIVE_PED_SET_PED_NAME_DEBUG(Ped ped, sol::stack_object name)
	{
		PED::SET_PED_NAME_DEBUG(ped, name.is<const char*>() ? name.as<const char*>() : nullptr);
	}

	static Vector3 LUA_NATIVE_PED_GET_PED_EXTRACTED_DISPLACEMENT(Ped ped, bool worldSpace)
	{
		auto retval = PED::GET_PED_EXTRACTED_DISPLACEMENT(ped, worldSpace);
		return retval;
	}

	static void LUA_NATIVE_PED_SET_PED_DIES_WHEN_INJURED(Ped ped, bool toggle)
	{
		PED::SET_PED_DIES_WHEN_INJURED(ped, toggle);
	}

	static void LUA_NATIVE_PED_SET_PED_ENABLE_WEAPON_BLOCKING(Ped ped, bool toggle)
	{
		PED::SET_PED_ENABLE_WEAPON_BLOCKING(ped, toggle);
	}

	static void LUA_NATIVE_PED_SPECIAL_FUNCTION_DO_NOT_USE(Ped ped, bool p1)
	{
		PED::SPECIAL_FUNCTION_DO_NOT_USE(ped, p1);
	}

	static void LUA_NATIVE_PED_RESET_PED_VISIBLE_DAMAGE(Ped ped)
	{
		PED::RESET_PED_VISIBLE_DAMAGE(ped);
	}

	static void LUA_NATIVE_PED_APPLY_PED_BLOOD_DAMAGE_BY_ZONE(Ped ped, Any p1, float p2, float p3, Any p4)
	{
		PED::APPLY_PED_BLOOD_DAMAGE_BY_ZONE(ped, p1, p2, p3, p4);
	}

	static void LUA_NATIVE_PED_APPLY_PED_BLOOD(Ped ped, int boneIndex, float xRot, float yRot, float zRot, sol::stack_object woundType)
	{
		PED::APPLY_PED_BLOOD(ped, boneIndex, xRot, yRot, zRot, woundType.is<const char*>() ? woundType.as<const char*>() : nullptr);
	}

	static void LUA_NATIVE_PED_APPLY_PED_BLOOD_BY_ZONE(Ped ped, int p1, float p2, float p3, sol::stack_object p4)
	{
		PED::APPLY_PED_BLOOD_BY_ZONE(ped, p1, p2, p3, p4.is<const char*>() ? p4.as<const char*>() : nullptr);
	}

	static void LUA_NATIVE_PED_APPLY_PED_BLOOD_SPECIFIC(Ped ped, int p1, float p2, float p3, float p4, float p5, int p6, float p7, sol::stack_object p8)
	{
		PED::APPLY_PED_BLOOD_SPECIFIC(ped, p1, p2, p3, p4, p5, p6, p7, p8.is<const char*>() ? p8.as<const char*>() : nullptr);
	}

	static void LUA_NATIVE_PED_APPLY_PED_DAMAGE_DECAL(Ped ped, int damageZone, float xOffset, float yOffset, float heading, float scale, float alpha, int variation, bool fadeIn, sol::stack_object decalName)
	{
		PED::APPLY_PED_DAMAGE_DECAL(ped, damageZone, xOffset, yOffset, heading, scale, alpha, variation, fadeIn, decalName.is<const char*>() ? decalName.as<const char*>() : nullptr);
	}

	static void LUA_NATIVE_PED_APPLY_PED_DAMAGE_PACK(Ped ped, sol::stack_object damagePack, float damage, float mult)
	{
		PED::APPLY_PED_DAMAGE_PACK(ped, damagePack.is<const char*>() ? damagePack.as<const char*>() : nullptr, damage, mult);
	}

	static void LUA_NATIVE_PED_CLEAR_PED_BLOOD_DAMAGE(Ped ped)
	{
		PED::CLEAR_PED_BLOOD_DAMAGE(ped);
	}

	static void LUA_NATIVE_PED_CLEAR_PED_BLOOD_DAMAGE_BY_ZONE(Ped ped, int p1)
	{
		PED::CLEAR_PED_BLOOD_DAMAGE_BY_ZONE(ped, p1);
	}

	static void LUA_NATIVE_PED_HIDE_PED_BLOOD_DAMAGE_BY_ZONE(Ped ped, Any p1, bool p2)
	{
		PED::HIDE_PED_BLOOD_DAMAGE_BY_ZONE(ped, p1, p2);
	}

	static void LUA_NATIVE_PED_CLEAR_PED_DAMAGE_DECAL_BY_ZONE(Ped ped, int p1, sol::stack_object p2)
	{
		PED::CLEAR_PED_DAMAGE_DECAL_BY_ZONE(ped, p1, p2.is<const char*>() ? p2.as<const char*>() : nullptr);
	}

	static int LUA_NATIVE_PED_GET_PED_DECORATIONS_STATE(Ped ped)
	{
		auto retval = PED::GET_PED_DECORATIONS_STATE(ped);
		return retval;
	}

	static void LUA_NATIVE_PED_MARK_PED_DECORATIONS_AS_CLONED_FROM_LOCAL_PLAYER(Ped ped, bool p1)
	{
		PED::MARK_PED_DECORATIONS_AS_CLONED_FROM_LOCAL_PLAYER(ped, p1);
	}

	static void LUA_NATIVE_PED_CLEAR_PED_WETNESS(Ped ped)
	{
		PED::CLEAR_PED_WETNESS(ped);
	}

	static void LUA_NATIVE_PED_SET_PED_WETNESS_HEIGHT(Ped ped, float height)
	{
		PED::SET_PED_WETNESS_HEIGHT(ped, height);
	}

	static void LUA_NATIVE_PED_SET_PED_WETNESS_ENABLED_THIS_FRAME(Ped ped)
	{
		PED::SET_PED_WETNESS_ENABLED_THIS_FRAME(ped);
	}

	static void LUA_NATIVE_PED_SET_PED_WETNESS(Ped ped, float wetLevel)
	{
		PED::SET_PED_WETNESS(ped, wetLevel);
	}

	static void LUA_NATIVE_PED_CLEAR_PED_ENV_DIRT(Ped ped)
	{
		PED::CLEAR_PED_ENV_DIRT(ped);
	}

	static void LUA_NATIVE_PED_SET_PED_SWEAT(Ped ped, float sweat)
	{
		PED::SET_PED_SWEAT(ped, sweat);
	}

	static void LUA_NATIVE_PED_ADD_PED_DECORATION_FROM_HASHES(Ped ped, Hash collection, Hash overlay)
	{
		PED::ADD_PED_DECORATION_FROM_HASHES(ped, collection, overlay);
	}

	static void LUA_NATIVE_PED_ADD_PED_DECORATION_FROM_HASHES_IN_CORONA(Ped ped, Hash collection, Hash overlay)
	{
		PED::ADD_PED_DECORATION_FROM_HASHES_IN_CORONA(ped, collection, overlay);
	}

	static int LUA_NATIVE_PED_GET_PED_DECORATION_ZONE_FROM_HASHES(Hash collection, Hash overlay)
	{
		auto retval = PED::GET_PED_DECORATION_ZONE_FROM_HASHES(collection, overlay);
		return retval;
	}

	static void LUA_NATIVE_PED_CLEAR_PED_DECORATIONS(Ped ped)
	{
		PED::CLEAR_PED_DECORATIONS(ped);
	}

	static void LUA_NATIVE_PED_CLEAR_PED_DECORATIONS_LEAVE_SCARS(Ped ped)
	{
		PED::CLEAR_PED_DECORATIONS_LEAVE_SCARS(ped);
	}

	static bool LUA_NATIVE_PED_WAS_PED_SKELETON_UPDATED(Ped ped)
	{
		auto retval = (bool)PED::WAS_PED_SKELETON_UPDATED(ped);
		return retval;
	}

	static Vector3 LUA_NATIVE_PED_GET_PED_BONE_COORDS(Ped ped, int boneId, float offsetX, float offsetY, float offsetZ)
	{
		auto retval = PED::GET_PED_BONE_COORDS(ped, boneId, offsetX, offsetY, offsetZ);
		return retval;
	}

	static void LUA_NATIVE_PED_CREATE_NM_MESSAGE(bool startImmediately, int messageId)
	{
		PED::CREATE_NM_MESSAGE(startImmediately, messageId);
	}

	static void LUA_NATIVE_PED_GIVE_PED_NM_MESSAGE(Ped ped)
	{
		PED::GIVE_PED_NM_MESSAGE(ped);
	}

	static int LUA_NATIVE_PED_ADD_SCENARIO_BLOCKING_AREA(float x1, float y1, float z1, float x2, float y2, float z2, bool p6, bool p7, bool p8, bool p9, Any p10)
	{
		auto retval = PED::ADD_SCENARIO_BLOCKING_AREA(x1, y1, z1, x2, y2, z2, p6, p7, p8, p9, p10);
		return retval;
	}

	static void LUA_NATIVE_PED_REMOVE_SCENARIO_BLOCKING_AREAS()
	{
		PED::REMOVE_SCENARIO_BLOCKING_AREAS();
	}

	static void LUA_NATIVE_PED_REMOVE_SCENARIO_BLOCKING_AREA(Any p0, bool p1)
	{
		PED::REMOVE_SCENARIO_BLOCKING_AREA(p0, p1);
	}

	static void LUA_NATIVE_PED_SET_SCENARIO_PEDS_SPAWN_IN_SPHERE_AREA(float x, float y, float z, float range, int p4)
	{
		PED::SET_SCENARIO_PEDS_SPAWN_IN_SPHERE_AREA(x, y, z, range, p4);
	}

	static bool LUA_NATIVE_PED_DOES_SCENARIO_BLOCKING_AREA_EXISTS(float x1, float y1, float z1, float x2, float y2, float z2)
	{
		auto retval = (bool)PED::DOES_SCENARIO_BLOCKING_AREA_EXISTS(x1, y1, z1, x2, y2, z2);
		return retval;
	}

	static bool LUA_NATIVE_PED_IS_PED_USING_SCENARIO(Ped ped, sol::stack_object scenario)
	{
		auto retval = (bool)PED::IS_PED_USING_SCENARIO(ped, scenario.is<const char*>() ? scenario.as<const char*>() : nullptr);
		return retval;
	}

	static bool LUA_NATIVE_PED_IS_PED_USING_ANY_SCENARIO(Ped ped)
	{
		auto retval = (bool)PED::IS_PED_USING_ANY_SCENARIO(ped);
		return retval;
	}

	static bool LUA_NATIVE_PED_SET_PED_PANIC_EXIT_SCENARIO(Any p0, Any p1, Any p2, Any p3)
	{
		auto retval = (bool)PED::SET_PED_PANIC_EXIT_SCENARIO(p0, p1, p2, p3);
		return retval;
	}

	static void LUA_NATIVE_PED_TOGGLE_SCENARIO_PED_COWER_IN_PLACE(Ped ped, bool toggle)
	{
		PED::TOGGLE_SCENARIO_PED_COWER_IN_PLACE(ped, toggle);
	}

	static bool LUA_NATIVE_PED_TRIGGER_PED_SCENARIO_PANICEXITTOFLEE(Any p0, Any p1, Any p2, Any p3)
	{
		auto retval = (bool)PED::TRIGGER_PED_SCENARIO_PANICEXITTOFLEE(p0, p1, p2, p3);
		return retval;
	}

	static bool LUA_NATIVE_PED_SET_PED_SHOULD_PLAY_DIRECTED_NORMAL_SCENARIO_EXIT(Any p0, Any p1, Any p2, Any p3)
	{
		auto retval = (bool)PED::SET_PED_SHOULD_PLAY_DIRECTED_NORMAL_SCENARIO_EXIT(p0, p1, p2, p3);
		return retval;
	}

	static void LUA_NATIVE_PED_SET_PED_SHOULD_PLAY_NORMAL_SCENARIO_EXIT(Ped ped)
	{
		PED::SET_PED_SHOULD_PLAY_NORMAL_SCENARIO_EXIT(ped);
	}

	static void LUA_NATIVE_PED_SET_PED_SHOULD_PLAY_IMMEDIATE_SCENARIO_EXIT(Ped ped)
	{
		PED::SET_PED_SHOULD_PLAY_IMMEDIATE_SCENARIO_EXIT(ped);
	}

	static bool LUA_NATIVE_PED_SET_PED_SHOULD_PLAY_FLEE_SCENARIO_EXIT(Ped ped, Any p1, Any p2, Any p3)
	{
		auto retval = (bool)PED::SET_PED_SHOULD_PLAY_FLEE_SCENARIO_EXIT(ped, p1, p2, p3);
		return retval;
	}

	static void LUA_NATIVE_PED_SET_PED_SHOULD_IGNORE_SCENARIO_EXIT_COLLISION_CHECKS(Ped ped, bool p1)
	{
		PED::SET_PED_SHOULD_IGNORE_SCENARIO_EXIT_COLLISION_CHECKS(ped, p1);
	}

	static void LUA_NATIVE_PED_SET_PED_SHOULD_IGNORE_SCENARIO_NAV_CHECKS(Any p0, bool p1)
	{
		PED::SET_PED_SHOULD_IGNORE_SCENARIO_NAV_CHECKS(p0, p1);
	}

	static void LUA_NATIVE_PED_SET_PED_SHOULD_PROBE_FOR_SCENARIO_EXITS_IN_ONE_FRAME(Any p0, bool p1)
	{
		PED::SET_PED_SHOULD_PROBE_FOR_SCENARIO_EXITS_IN_ONE_FRAME(p0, p1);
	}

	static bool LUA_NATIVE_PED_IS_PED_GESTURING(Any p0)
	{
		auto retval = (bool)PED::IS_PED_GESTURING(p0);
		return retval;
	}

	static void LUA_NATIVE_PED_RESET_FACIAL_IDLE_ANIM(Ped ped)
	{
		PED::RESET_FACIAL_IDLE_ANIM(ped);
	}

	static void LUA_NATIVE_PED_PLAY_FACIAL_ANIM(Ped ped, sol::stack_object animName, sol::stack_object animDict)
	{
		PED::PLAY_FACIAL_ANIM(ped, animName.is<const char*>() ? animName.as<const char*>() : nullptr, animDict.is<const char*>() ? animDict.as<const char*>() : nullptr);
	}

	static void LUA_NATIVE_PED_SET_FACIAL_CLIPSET(Ped ped, sol::stack_object animDict)
	{
		PED::SET_FACIAL_CLIPSET(ped, animDict.is<const char*>() ? animDict.as<const char*>() : nullptr);
	}

	static void LUA_NATIVE_PED_SET_FACIAL_IDLE_ANIM_OVERRIDE(Ped ped, sol::stack_object animName, sol::stack_object animDict)
	{
		PED::SET_FACIAL_IDLE_ANIM_OVERRIDE(ped, animName.is<const char*>() ? animName.as<const char*>() : nullptr, animDict.is<const char*>() ? animDict.as<const char*>() : nullptr);
	}

	static void LUA_NATIVE_PED_CLEAR_FACIAL_IDLE_ANIM_OVERRIDE(Ped ped)
	{
		PED::CLEAR_FACIAL_IDLE_ANIM_OVERRIDE(ped);
	}

	static void LUA_NATIVE_PED_SET_PED_CAN_PLAY_GESTURE_ANIMS(Ped ped, bool toggle)
	{
		PED::SET_PED_CAN_PLAY_GESTURE_ANIMS(ped, toggle);
	}

	static void LUA_NATIVE_PED_SET_PED_CAN_PLAY_VISEME_ANIMS(Ped ped, bool toggle, bool p2)
	{
		PED::SET_PED_CAN_PLAY_VISEME_ANIMS(ped, toggle, p2);
	}

	static void LUA_NATIVE_PED_SET_PED_IS_IGNORED_BY_AUTO_OPEN_DOORS(Ped ped, bool p1)
	{
		PED::SET_PED_IS_IGNORED_BY_AUTO_OPEN_DOORS(ped, p1);
	}

	static void LUA_NATIVE_PED_SET_PED_CAN_PLAY_AMBIENT_ANIMS(Ped ped, bool toggle)
	{
		PED::SET_PED_CAN_PLAY_AMBIENT_ANIMS(ped, toggle);
	}

	static void LUA_NATIVE_PED_SET_PED_CAN_PLAY_AMBIENT_BASE_ANIMS(Ped ped, bool toggle)
	{
		PED::SET_PED_CAN_PLAY_AMBIENT_BASE_ANIMS(ped, toggle);
	}

	static void LUA_NATIVE_PED_TRIGGER_IDLE_ANIMATION_ON_PED(Ped ped)
	{
		PED::TRIGGER_IDLE_ANIMATION_ON_PED(ped);
	}

	static void LUA_NATIVE_PED_SET_PED_CAN_ARM_IK(Ped ped, bool toggle)
	{
		PED::SET_PED_CAN_ARM_IK(ped, toggle);
	}

	static void LUA_NATIVE_PED_SET_PED_CAN_HEAD_IK(Ped ped, bool toggle)
	{
		PED::SET_PED_CAN_HEAD_IK(ped, toggle);
	}

	static void LUA_NATIVE_PED_SET_PED_CAN_LEG_IK(Ped ped, bool toggle)
	{
		PED::SET_PED_CAN_LEG_IK(ped, toggle);
	}

	static void LUA_NATIVE_PED_SET_PED_CAN_TORSO_IK(Ped ped, bool toggle)
	{
		PED::SET_PED_CAN_TORSO_IK(ped, toggle);
	}

	static void LUA_NATIVE_PED_SET_PED_CAN_TORSO_REACT_IK(Ped ped, bool p1)
	{
		PED::SET_PED_CAN_TORSO_REACT_IK(ped, p1);
	}

	static void LUA_NATIVE_PED_SET_PED_CAN_TORSO_VEHICLE_IK(Ped ped, bool p1)
	{
		PED::SET_PED_CAN_TORSO_VEHICLE_IK(ped, p1);
	}

	static void LUA_NATIVE_PED_SET_PED_CAN_USE_AUTO_CONVERSATION_LOOKAT(Ped ped, bool toggle)
	{
		PED::SET_PED_CAN_USE_AUTO_CONVERSATION_LOOKAT(ped, toggle);
	}

	static bool LUA_NATIVE_PED_IS_PED_HEADTRACKING_PED(Ped ped1, Ped ped2)
	{
		auto retval = (bool)PED::IS_PED_HEADTRACKING_PED(ped1, ped2);
		return retval;
	}

	static bool LUA_NATIVE_PED_IS_PED_HEADTRACKING_ENTITY(Ped ped, Entity entity)
	{
		auto retval = (bool)PED::IS_PED_HEADTRACKING_ENTITY(ped, entity);
		return retval;
	}

	static void LUA_NATIVE_PED_SET_PED_PRIMARY_LOOKAT(Ped ped, Ped lookAt)
	{
		PED::SET_PED_PRIMARY_LOOKAT(ped, lookAt);
	}

	static void LUA_NATIVE_PED_SET_PED_CLOTH_PIN_FRAMES(Any p0, Any p1)
	{
		PED::SET_PED_CLOTH_PIN_FRAMES(p0, p1);
	}

	static void LUA_NATIVE_PED_SET_PED_CLOTH_PACKAGE_INDEX(Any p0, Any p1)
	{
		PED::SET_PED_CLOTH_PACKAGE_INDEX(p0, p1);
	}

	static void LUA_NATIVE_PED_SET_PED_CLOTH_PRONE(Any p0, bool p1)
	{
		PED::SET_PED_CLOTH_PRONE(p0, p1);
	}

	static void LUA_NATIVE_PED_SET_PED_CONFIG_FLAG(Ped ped, int flagId, bool value)
	{
		PED::SET_PED_CONFIG_FLAG(ped, flagId, value);
	}

	static void LUA_NATIVE_PED_SET_PED_RESET_FLAG(Ped ped, int flagId, bool doReset)
	{
		PED::SET_PED_RESET_FLAG(ped, flagId, doReset);
	}

	static bool LUA_NATIVE_PED_GET_PED_CONFIG_FLAG(Ped ped, int flagId, bool p2)
	{
		auto retval = (bool)PED::GET_PED_CONFIG_FLAG(ped, flagId, p2);
		return retval;
	}

	static bool LUA_NATIVE_PED_GET_PED_RESET_FLAG(Ped ped, int flagId)
	{
		auto retval = (bool)PED::GET_PED_RESET_FLAG(ped, flagId);
		return retval;
	}

	static void LUA_NATIVE_PED_SET_PED_GROUP_MEMBER_PASSENGER_INDEX(Ped ped, int index)
	{
		PED::SET_PED_GROUP_MEMBER_PASSENGER_INDEX(ped, index);
	}

	static void LUA_NATIVE_PED_SET_PED_CAN_EVASIVE_DIVE(Ped ped, bool toggle)
	{
		PED::SET_PED_CAN_EVASIVE_DIVE(ped, toggle);
	}

	static std::tuple<bool, Entity> LUA_NATIVE_PED_IS_PED_EVASIVE_DIVING(Ped ped, Entity evadingEntity)
	{
		std::tuple<bool, Entity> return_values;
		std::get<0>(return_values) = (bool)PED::IS_PED_EVASIVE_DIVING(ped, &evadingEntity);
		std::get<1>(return_values) = evadingEntity;

		return return_values;
	}

	static void LUA_NATIVE_PED_SET_PED_SHOOTS_AT_COORD(Ped ped, float x, float y, float z, bool toggle)
	{
		PED::SET_PED_SHOOTS_AT_COORD(ped, x, y, z, toggle);
	}

	static void LUA_NATIVE_PED_SET_PED_MODEL_IS_SUPPRESSED(Hash modelHash, bool toggle)
	{
		PED::SET_PED_MODEL_IS_SUPPRESSED(modelHash, toggle);
	}

	static void LUA_NATIVE_PED_STOP_ANY_PED_MODEL_BEING_SUPPRESSED()
	{
		PED::STOP_ANY_PED_MODEL_BEING_SUPPRESSED();
	}

	static void LUA_NATIVE_PED_SET_PED_CAN_BE_TARGETED_WHEN_INJURED(Ped ped, bool toggle)
	{
		PED::SET_PED_CAN_BE_TARGETED_WHEN_INJURED(ped, toggle);
	}

	static void LUA_NATIVE_PED_SET_PED_GENERATES_DEAD_BODY_EVENTS(Ped ped, bool toggle)
	{
		PED::SET_PED_GENERATES_DEAD_BODY_EVENTS(ped, toggle);
	}

	static void LUA_NATIVE_PED_BLOCK_PED_FROM_GENERATING_DEAD_BODY_EVENTS_WHEN_DEAD(Ped ped, bool toggle)
	{
		PED::BLOCK_PED_FROM_GENERATING_DEAD_BODY_EVENTS_WHEN_DEAD(ped, toggle);
	}

	static void LUA_NATIVE_PED_SET_PED_WILL_ONLY_ATTACK_WANTED_PLAYER(Any p0, Any p1)
	{
		PED::SET_PED_WILL_ONLY_ATTACK_WANTED_PLAYER(p0, p1);
	}

	static void LUA_NATIVE_PED_SET_PED_CAN_RAGDOLL_FROM_PLAYER_IMPACT(Ped ped, bool toggle)
	{
		PED::SET_PED_CAN_RAGDOLL_FROM_PLAYER_IMPACT(ped, toggle);
	}

	static void LUA_NATIVE_PED_GIVE_PED_HELMET(Ped ped, bool cannotRemove, int helmetFlag, int textureIndex)
	{
		PED::GIVE_PED_HELMET(ped, cannotRemove, helmetFlag, textureIndex);
	}

	static void LUA_NATIVE_PED_REMOVE_PED_HELMET(Ped ped, bool instantly)
	{
		PED::REMOVE_PED_HELMET(ped, instantly);
	}

	static bool LUA_NATIVE_PED_IS_PED_TAKING_OFF_HELMET(Ped ped)
	{
		auto retval = (bool)PED::IS_PED_TAKING_OFF_HELMET(ped);
		return retval;
	}

	static void LUA_NATIVE_PED_SET_PED_HELMET(Ped ped, bool canWearHelmet)
	{
		PED::SET_PED_HELMET(ped, canWearHelmet);
	}

	static void LUA_NATIVE_PED_SET_PED_HELMET_FLAG(Ped ped, int helmetFlag)
	{
		PED::SET_PED_HELMET_FLAG(ped, helmetFlag);
	}

	static void LUA_NATIVE_PED_SET_PED_HELMET_PROP_INDEX(Ped ped, int propIndex, bool p2)
	{
		PED::SET_PED_HELMET_PROP_INDEX(ped, propIndex, p2);
	}

	static void LUA_NATIVE_PED_SET_PED_HELMET_VISOR_PROP_INDICES(Ped ped, bool p1, int p2, int p3)
	{
		PED::SET_PED_HELMET_VISOR_PROP_INDICES(ped, p1, p2, p3);
	}

	static bool LUA_NATIVE_PED_IS_PED_HELMET_VISOR_UP(Ped ped)
	{
		auto retval = (bool)PED::IS_PED_HELMET_VISOR_UP(ped);
		return retval;
	}

	static void LUA_NATIVE_PED_SET_PED_HELMET_TEXTURE_INDEX(Ped ped, int textureIndex)
	{
		PED::SET_PED_HELMET_TEXTURE_INDEX(ped, textureIndex);
	}

	static bool LUA_NATIVE_PED_IS_PED_WEARING_HELMET(Ped ped)
	{
		auto retval = (bool)PED::IS_PED_WEARING_HELMET(ped);
		return retval;
	}

	static void LUA_NATIVE_PED_CLEAR_PED_STORED_HAT_PROP(Ped ped)
	{
		PED::CLEAR_PED_STORED_HAT_PROP(ped);
	}

	static int LUA_NATIVE_PED_GET_PED_HELMET_STORED_HAT_PROP_INDEX(Ped ped)
	{
		auto retval = PED::GET_PED_HELMET_STORED_HAT_PROP_INDEX(ped);
		return retval;
	}

	static int LUA_NATIVE_PED_GET_PED_HELMET_STORED_HAT_TEX_INDEX(Ped ped)
	{
		auto retval = PED::GET_PED_HELMET_STORED_HAT_TEX_INDEX(ped);
		return retval;
	}

	static bool LUA_NATIVE_PED_IS_CURRENT_HEAD_PROP_A_HELMET(Any p0)
	{
		auto retval = (bool)PED::IS_CURRENT_HEAD_PROP_A_HELMET(p0);
		return retval;
	}

	static void LUA_NATIVE_PED_SET_PED_TO_LOAD_COVER(Ped ped, bool toggle)
	{
		PED::SET_PED_TO_LOAD_COVER(ped, toggle);
	}

	static void LUA_NATIVE_PED_SET_PED_CAN_COWER_IN_COVER(Ped ped, bool toggle)
	{
		PED::SET_PED_CAN_COWER_IN_COVER(ped, toggle);
	}

	static void LUA_NATIVE_PED_SET_PED_CAN_PEEK_IN_COVER(Ped ped, bool toggle)
	{
		PED::SET_PED_CAN_PEEK_IN_COVER(ped, toggle);
	}

	static void LUA_NATIVE_PED_SET_PED_PLAYS_HEAD_ON_HORN_ANIM_WHEN_DIES_IN_VEHICLE(Ped ped, bool toggle)
	{
		PED::SET_PED_PLAYS_HEAD_ON_HORN_ANIM_WHEN_DIES_IN_VEHICLE(ped, toggle);
	}

	static void LUA_NATIVE_PED_SET_PED_LEG_IK_MODE(Ped ped, int mode)
	{
		PED::SET_PED_LEG_IK_MODE(ped, mode);
	}

	static void LUA_NATIVE_PED_SET_PED_MOTION_BLUR(Ped ped, bool toggle)
	{
		PED::SET_PED_MOTION_BLUR(ped, toggle);
	}

	static void LUA_NATIVE_PED_SET_PED_CAN_SWITCH_WEAPON(Ped ped, bool toggle)
	{
		PED::SET_PED_CAN_SWITCH_WEAPON(ped, toggle);
	}

	static void LUA_NATIVE_PED_SET_PED_DIES_INSTANTLY_IN_WATER(Ped ped, bool toggle)
	{
		PED::SET_PED_DIES_INSTANTLY_IN_WATER(ped, toggle);
	}

	static void LUA_NATIVE_PED_SET_LADDER_CLIMB_INPUT_STATE(Ped ped, int p1)
	{
		PED::SET_LADDER_CLIMB_INPUT_STATE(ped, p1);
	}

	static void LUA_NATIVE_PED_STOP_PED_WEAPON_FIRING_WHEN_DROPPED(Ped ped)
	{
		PED::STOP_PED_WEAPON_FIRING_WHEN_DROPPED(ped);
	}

	static void LUA_NATIVE_PED_SET_SCRIPTED_ANIM_SEAT_OFFSET(Ped ped, float p1)
	{
		PED::SET_SCRIPTED_ANIM_SEAT_OFFSET(ped, p1);
	}

	static void LUA_NATIVE_PED_SET_PED_COMBAT_MOVEMENT(Ped ped, int combatMovement)
	{
		PED::SET_PED_COMBAT_MOVEMENT(ped, combatMovement);
	}

	static int LUA_NATIVE_PED_GET_PED_COMBAT_MOVEMENT(Ped ped)
	{
		auto retval = PED::GET_PED_COMBAT_MOVEMENT(ped);
		return retval;
	}

	static void LUA_NATIVE_PED_SET_PED_COMBAT_ABILITY(Ped ped, int abilityLevel)
	{
		PED::SET_PED_COMBAT_ABILITY(ped, abilityLevel);
	}

	static void LUA_NATIVE_PED_SET_PED_COMBAT_RANGE(Ped ped, int combatRange)
	{
		PED::SET_PED_COMBAT_RANGE(ped, combatRange);
	}

	static int LUA_NATIVE_PED_GET_PED_COMBAT_RANGE(Ped ped)
	{
		auto retval = PED::GET_PED_COMBAT_RANGE(ped);
		return retval;
	}

	static void LUA_NATIVE_PED_SET_PED_COMBAT_ATTRIBUTES(Ped ped, int attributeId, bool enabled)
	{
		PED::SET_PED_COMBAT_ATTRIBUTES(ped, attributeId, enabled);
	}

	static void LUA_NATIVE_PED_SET_PED_TARGET_LOSS_RESPONSE(Ped ped, int responseType)
	{
		PED::SET_PED_TARGET_LOSS_RESPONSE(ped, responseType);
	}

	static bool LUA_NATIVE_PED_IS_PED_PERFORMING_MELEE_ACTION(Ped ped)
	{
		auto retval = (bool)PED::IS_PED_PERFORMING_MELEE_ACTION(ped);
		return retval;
	}

	static bool LUA_NATIVE_PED_IS_PED_PERFORMING_STEALTH_KILL(Ped ped)
	{
		auto retval = (bool)PED::IS_PED_PERFORMING_STEALTH_KILL(ped);
		return retval;
	}

	static bool LUA_NATIVE_PED_IS_PED_PERFORMING_A_COUNTER_ATTACK(Ped ped)
	{
		auto retval = (bool)PED::IS_PED_PERFORMING_A_COUNTER_ATTACK(ped);
		return retval;
	}

	static bool LUA_NATIVE_PED_IS_PED_BEING_STEALTH_KILLED(Ped ped)
	{
		auto retval = (bool)PED::IS_PED_BEING_STEALTH_KILLED(ped);
		return retval;
	}

	static Ped LUA_NATIVE_PED_GET_MELEE_TARGET_FOR_PED(Ped ped)
	{
		auto retval = PED::GET_MELEE_TARGET_FOR_PED(ped);
		return retval;
	}

	static bool LUA_NATIVE_PED_WAS_PED_KILLED_BY_STEALTH(Ped ped)
	{
		auto retval = (bool)PED::WAS_PED_KILLED_BY_STEALTH(ped);
		return retval;
	}

	static bool LUA_NATIVE_PED_WAS_PED_KILLED_BY_TAKEDOWN(Ped ped)
	{
		auto retval = (bool)PED::WAS_PED_KILLED_BY_TAKEDOWN(ped);
		return retval;
	}

	static bool LUA_NATIVE_PED_WAS_PED_KNOCKED_OUT(Ped ped)
	{
		auto retval = (bool)PED::WAS_PED_KNOCKED_OUT(ped);
		return retval;
	}

	static void LUA_NATIVE_PED_SET_PED_FLEE_ATTRIBUTES(Ped ped, int attributeFlags, bool enable)
	{
		PED::SET_PED_FLEE_ATTRIBUTES(ped, attributeFlags, enable);
	}

	static void LUA_NATIVE_PED_SET_PED_COWER_HASH(Ped ped, sol::stack_object p1)
	{
		PED::SET_PED_COWER_HASH(ped, p1.is<const char*>() ? p1.as<const char*>() : nullptr);
	}

	static void LUA_NATIVE_PED_SET_PED_STEERS_AROUND_DEAD_BODIES(Ped ped, bool toggle)
	{
		PED::SET_PED_STEERS_AROUND_DEAD_BODIES(ped, toggle);
	}

	static void LUA_NATIVE_PED_SET_PED_STEERS_AROUND_PEDS(Ped ped, bool toggle)
	{
		PED::SET_PED_STEERS_AROUND_PEDS(ped, toggle);
	}

	static void LUA_NATIVE_PED_SET_PED_STEERS_AROUND_OBJECTS(Ped ped, bool toggle)
	{
		PED::SET_PED_STEERS_AROUND_OBJECTS(ped, toggle);
	}

	static void LUA_NATIVE_PED_SET_PED_STEERS_AROUND_VEHICLES(Ped ped, bool toggle)
	{
		PED::SET_PED_STEERS_AROUND_VEHICLES(ped, toggle);
	}

	static void LUA_NATIVE_PED_SET_PED_IS_AVOIDED_BY_OTHERS(Any p0, bool p1)
	{
		PED::SET_PED_IS_AVOIDED_BY_OTHERS(p0, p1);
	}

	static void LUA_NATIVE_PED_SET_PED_INCREASED_AVOIDANCE_RADIUS(Ped ped)
	{
		PED::SET_PED_INCREASED_AVOIDANCE_RADIUS(ped);
	}

	static void LUA_NATIVE_PED_SET_PED_BLOCKS_PATHING_WHEN_DEAD(Ped ped, bool toggle)
	{
		PED::SET_PED_BLOCKS_PATHING_WHEN_DEAD(ped, toggle);
	}

	static void LUA_NATIVE_PED_SET_PED_NO_TIME_DELAY_BEFORE_SHOT(Any p0)
	{
		PED::SET_PED_NO_TIME_DELAY_BEFORE_SHOT(p0);
	}

	static bool LUA_NATIVE_PED_IS_ANY_PED_NEAR_POINT(float x, float y, float z, float radius)
	{
		auto retval = (bool)PED::IS_ANY_PED_NEAR_POINT(x, y, z, radius);
		return retval;
	}

	static void LUA_NATIVE_PED_FORCE_PED_AI_AND_ANIMATION_UPDATE(Ped ped, bool p1, bool p2)
	{
		PED::FORCE_PED_AI_AND_ANIMATION_UPDATE(ped, p1, p2);
	}

	static bool LUA_NATIVE_PED_IS_PED_HEADING_TOWARDS_POSITION(Ped ped, float x, float y, float z, float p4)
	{
		auto retval = (bool)PED::IS_PED_HEADING_TOWARDS_POSITION(ped, x, y, z, p4);
		return retval;
	}

	static void LUA_NATIVE_PED_REQUEST_PED_VISIBILITY_TRACKING(Ped ped)
	{
		PED::REQUEST_PED_VISIBILITY_TRACKING(ped);
	}

	static void LUA_NATIVE_PED_REQUEST_PED_VEHICLE_VISIBILITY_TRACKING(Ped ped, bool p1)
	{
		PED::REQUEST_PED_VEHICLE_VISIBILITY_TRACKING(ped, p1);
	}

	static void LUA_NATIVE_PED_REQUEST_PED_RESTRICTED_VEHICLE_VISIBILITY_TRACKING(Ped ped, bool p1)
	{
		PED::REQUEST_PED_RESTRICTED_VEHICLE_VISIBILITY_TRACKING(ped, p1);
	}

	static void LUA_NATIVE_PED_REQUEST_PED_USE_SMALL_BBOX_VISIBILITY_TRACKING(Ped ped, bool p1)
	{
		PED::REQUEST_PED_USE_SMALL_BBOX_VISIBILITY_TRACKING(ped, p1);
	}

	static bool LUA_NATIVE_PED_IS_TRACKED_PED_VISIBLE(Ped ped)
	{
		auto retval = (bool)PED::IS_TRACKED_PED_VISIBLE(ped);
		return retval;
	}

	static int LUA_NATIVE_PED_GET_TRACKED_PED_PIXELCOUNT(Ped ped)
	{
		auto retval = PED::GET_TRACKED_PED_PIXELCOUNT(ped);
		return retval;
	}

	static bool LUA_NATIVE_PED_IS_PED_TRACKED(Ped ped)
	{
		auto retval = (bool)PED::IS_PED_TRACKED(ped);
		return retval;
	}

	static bool LUA_NATIVE_PED_HAS_PED_RECEIVED_EVENT(Ped ped, int eventId)
	{
		auto retval = (bool)PED::HAS_PED_RECEIVED_EVENT(ped, eventId);
		return retval;
	}

	static bool LUA_NATIVE_PED_CAN_PED_SEE_HATED_PED(Ped ped1, Ped ped2)
	{
		auto retval = (bool)PED::CAN_PED_SEE_HATED_PED(ped1, ped2);
		return retval;
	}

	static std::tuple<bool, int> LUA_NATIVE_PED_CAN_PED_SHUFFLE_TO_OR_FROM_TURRET_SEAT(Ped ped, int p1)
	{
		std::tuple<bool, int> return_values;
		std::get<0>(return_values) = (bool)PED::CAN_PED_SHUFFLE_TO_OR_FROM_TURRET_SEAT(ped, &p1);
		std::get<1>(return_values) = p1;

		return return_values;
	}

	static std::tuple<bool, int> LUA_NATIVE_PED_CAN_PED_SHUFFLE_TO_OR_FROM_EXTRA_SEAT(Ped ped, int p1)
	{
		std::tuple<bool, int> return_values;
		std::get<0>(return_values) = (bool)PED::CAN_PED_SHUFFLE_TO_OR_FROM_EXTRA_SEAT(ped, &p1);
		std::get<1>(return_values) = p1;

		return return_values;
	}

	static int LUA_NATIVE_PED_GET_PED_BONE_INDEX(Ped ped, int boneId)
	{
		auto retval = PED::GET_PED_BONE_INDEX(ped, boneId);
		return retval;
	}

	static int LUA_NATIVE_PED_GET_PED_RAGDOLL_BONE_INDEX(Ped ped, int bone)
	{
		auto retval = PED::GET_PED_RAGDOLL_BONE_INDEX(ped, bone);
		return retval;
	}

	static void LUA_NATIVE_PED_SET_PED_ENVEFF_SCALE(Ped ped, float value)
	{
		PED::SET_PED_ENVEFF_SCALE(ped, value);
	}

	static float LUA_NATIVE_PED_GET_PED_ENVEFF_SCALE(Ped ped)
	{
		auto retval = PED::GET_PED_ENVEFF_SCALE(ped);
		return retval;
	}

	static void LUA_NATIVE_PED_SET_ENABLE_PED_ENVEFF_SCALE(Ped ped, bool toggle)
	{
		PED::SET_ENABLE_PED_ENVEFF_SCALE(ped, toggle);
	}

	static void LUA_NATIVE_PED_SET_PED_ENVEFF_CPV_ADD(Ped ped, float p1)
	{
		PED::SET_PED_ENVEFF_CPV_ADD(ped, p1);
	}

	static void LUA_NATIVE_PED_SET_PED_ENVEFF_COLOR_MODULATOR(Ped ped, int p1, int p2, int p3)
	{
		PED::SET_PED_ENVEFF_COLOR_MODULATOR(ped, p1, p2, p3);
	}

	static void LUA_NATIVE_PED_SET_PED_EMISSIVE_SCALE(Ped ped, float intensity)
	{
		PED::SET_PED_EMISSIVE_SCALE(ped, intensity);
	}

	static float LUA_NATIVE_PED_GET_PED_EMISSIVE_SCALE(Ped ped)
	{
		auto retval = PED::GET_PED_EMISSIVE_SCALE(ped);
		return retval;
	}

	static bool LUA_NATIVE_PED_IS_PED_SHADER_READY(Ped ped)
	{
		auto retval = (bool)PED::IS_PED_SHADER_READY(ped);
		return retval;
	}

	static void LUA_NATIVE_PED_SET_PED_ENABLE_CREW_EMBLEM(Ped ped, bool toggle)
	{
		PED::SET_PED_ENABLE_CREW_EMBLEM(ped, toggle);
	}

	static void LUA_NATIVE_PED_REQUEST_RAGDOLL_BOUNDS_UPDATE(Any p0, Any p1)
	{
		PED::REQUEST_RAGDOLL_BOUNDS_UPDATE(p0, p1);
	}

	static void LUA_NATIVE_PED_SET_PED_AO_BLOB_RENDERING(Ped ped, bool toggle)
	{
		PED::SET_PED_AO_BLOB_RENDERING(ped, toggle);
	}

	static bool LUA_NATIVE_PED_IS_PED_SHELTERED(Ped ped)
	{
		auto retval = (bool)PED::IS_PED_SHELTERED(ped);
		return retval;
	}

	static int LUA_NATIVE_PED_CREATE_SYNCHRONIZED_SCENE(float x, float y, float z, float roll, float pitch, float yaw, int p6)
	{
		auto retval = PED::CREATE_SYNCHRONIZED_SCENE(x, y, z, roll, pitch, yaw, p6);
		return retval;
	}

	static int LUA_NATIVE_PED_CREATE_SYNCHRONIZED_SCENE_AT_MAP_OBJECT(float x, float y, float z, float radius, Hash object)
	{
		auto retval = PED::CREATE_SYNCHRONIZED_SCENE_AT_MAP_OBJECT(x, y, z, radius, object);
		return retval;
	}

	static bool LUA_NATIVE_PED_IS_SYNCHRONIZED_SCENE_RUNNING(int sceneId)
	{
		auto retval = (bool)PED::IS_SYNCHRONIZED_SCENE_RUNNING(sceneId);
		return retval;
	}

	static void LUA_NATIVE_PED_SET_SYNCHRONIZED_SCENE_ORIGIN(int sceneID, float x, float y, float z, float roll, float pitch, float yaw, bool p7)
	{
		PED::SET_SYNCHRONIZED_SCENE_ORIGIN(sceneID, x, y, z, roll, pitch, yaw, p7);
	}

	static void LUA_NATIVE_PED_SET_SYNCHRONIZED_SCENE_PHASE(int sceneID, float phase)
	{
		PED::SET_SYNCHRONIZED_SCENE_PHASE(sceneID, phase);
	}

	static float LUA_NATIVE_PED_GET_SYNCHRONIZED_SCENE_PHASE(int sceneID)
	{
		auto retval = PED::GET_SYNCHRONIZED_SCENE_PHASE(sceneID);
		return retval;
	}

	static void LUA_NATIVE_PED_SET_SYNCHRONIZED_SCENE_RATE(int sceneID, float rate)
	{
		PED::SET_SYNCHRONIZED_SCENE_RATE(sceneID, rate);
	}

	static float LUA_NATIVE_PED_GET_SYNCHRONIZED_SCENE_RATE(int sceneID)
	{
		auto retval = PED::GET_SYNCHRONIZED_SCENE_RATE(sceneID);
		return retval;
	}

	static void LUA_NATIVE_PED_SET_SYNCHRONIZED_SCENE_LOOPED(int sceneID, bool toggle)
	{
		PED::SET_SYNCHRONIZED_SCENE_LOOPED(sceneID, toggle);
	}

	static bool LUA_NATIVE_PED_IS_SYNCHRONIZED_SCENE_LOOPED(int sceneID)
	{
		auto retval = (bool)PED::IS_SYNCHRONIZED_SCENE_LOOPED(sceneID);
		return retval;
	}

	static void LUA_NATIVE_PED_SET_SYNCHRONIZED_SCENE_HOLD_LAST_FRAME(int sceneID, bool toggle)
	{
		PED::SET_SYNCHRONIZED_SCENE_HOLD_LAST_FRAME(sceneID, toggle);
	}

	static bool LUA_NATIVE_PED_IS_SYNCHRONIZED_SCENE_HOLD_LAST_FRAME(int sceneID)
	{
		auto retval = (bool)PED::IS_SYNCHRONIZED_SCENE_HOLD_LAST_FRAME(sceneID);
		return retval;
	}

	static void LUA_NATIVE_PED_ATTACH_SYNCHRONIZED_SCENE_TO_ENTITY(int sceneID, Entity entity, int boneIndex)
	{
		PED::ATTACH_SYNCHRONIZED_SCENE_TO_ENTITY(sceneID, entity, boneIndex);
	}

	static void LUA_NATIVE_PED_DETACH_SYNCHRONIZED_SCENE(int sceneID)
	{
		PED::DETACH_SYNCHRONIZED_SCENE(sceneID);
	}

	static void LUA_NATIVE_PED_TAKE_OWNERSHIP_OF_SYNCHRONIZED_SCENE(int scene)
	{
		PED::TAKE_OWNERSHIP_OF_SYNCHRONIZED_SCENE(scene);
	}

	static bool LUA_NATIVE_PED_FORCE_PED_MOTION_STATE(Ped ped, Hash motionStateHash, bool p2, int p3, bool p4)
	{
		auto retval = (bool)PED::FORCE_PED_MOTION_STATE(ped, motionStateHash, p2, p3, p4);
		return retval;
	}

	static std::tuple<bool, float, float> LUA_NATIVE_PED_GET_PED_CURRENT_MOVE_BLEND_RATIO(Ped ped, float speedX, float speedY)
	{
		std::tuple<bool, float, float> return_values;
		std::get<0>(return_values) = (bool)PED::GET_PED_CURRENT_MOVE_BLEND_RATIO(ped, &speedX, &speedY);
		std::get<1>(return_values) = speedX;
		std::get<2>(return_values) = speedY;

		return return_values;
	}

	static void LUA_NATIVE_PED_SET_PED_MAX_MOVE_BLEND_RATIO(Ped ped, float value)
	{
		PED::SET_PED_MAX_MOVE_BLEND_RATIO(ped, value);
	}

	static void LUA_NATIVE_PED_SET_PED_MIN_MOVE_BLEND_RATIO(Ped ped, float value)
	{
		PED::SET_PED_MIN_MOVE_BLEND_RATIO(ped, value);
	}

	static void LUA_NATIVE_PED_SET_PED_MOVE_RATE_OVERRIDE(Ped ped, float value)
	{
		PED::SET_PED_MOVE_RATE_OVERRIDE(ped, value);
	}

	static void LUA_NATIVE_PED_SET_PED_MOVE_RATE_IN_WATER_OVERRIDE(Ped ped, float p1)
	{
		PED::SET_PED_MOVE_RATE_IN_WATER_OVERRIDE(ped, p1);
	}

	static bool LUA_NATIVE_PED_PED_HAS_SEXINESS_FLAG_SET(Ped ped, int sexinessFlag)
	{
		auto retval = (bool)PED::PED_HAS_SEXINESS_FLAG_SET(ped, sexinessFlag);
		return retval;
	}

	static int LUA_NATIVE_PED_GET_PED_NEARBY_VEHICLES(Ped ped, uintptr_t sizeAndVehs)
	{
		auto retval = PED::GET_PED_NEARBY_VEHICLES(ped, (Any*)sizeAndVehs);
		return retval;
	}

	static int LUA_NATIVE_PED_GET_PED_NEARBY_PEDS(Ped ped, uintptr_t sizeAndPeds, int ignore)
	{
		auto retval = PED::GET_PED_NEARBY_PEDS(ped, (Any*)sizeAndPeds, ignore);
		return retval;
	}

	static bool LUA_NATIVE_PED_HAVE_ALL_STREAMING_REQUESTS_COMPLETED(Ped ped)
	{
		auto retval = (bool)PED::HAVE_ALL_STREAMING_REQUESTS_COMPLETED(ped);
		return retval;
	}

	static bool LUA_NATIVE_PED_IS_PED_USING_ACTION_MODE(Ped ped)
	{
		auto retval = (bool)PED::IS_PED_USING_ACTION_MODE(ped);
		return retval;
	}

	static void LUA_NATIVE_PED_SET_PED_USING_ACTION_MODE(Ped ped, bool p1, int p2, sol::stack_object action)
	{
		PED::SET_PED_USING_ACTION_MODE(ped, p1, p2, action.is<const char*>() ? action.as<const char*>() : nullptr);
	}

	static void LUA_NATIVE_PED_SET_MOVEMENT_MODE_OVERRIDE(Ped ped, sol::stack_object name)
	{
		PED::SET_MOVEMENT_MODE_OVERRIDE(ped, name.is<const char*>() ? name.as<const char*>() : nullptr);
	}

	static void LUA_NATIVE_PED_SET_PED_CAPSULE(Ped ped, float value)
	{
		PED::SET_PED_CAPSULE(ped, value);
	}

	static int LUA_NATIVE_PED_REGISTER_PEDHEADSHOT(Ped ped)
	{
		auto retval = PED::REGISTER_PEDHEADSHOT(ped);
		return retval;
	}

	static int LUA_NATIVE_PED_REGISTER_PEDHEADSHOT_HIRES(Ped ped)
	{
		auto retval = PED::REGISTER_PEDHEADSHOT_HIRES(ped);
		return retval;
	}

	static int LUA_NATIVE_PED_REGISTER_PEDHEADSHOT_TRANSPARENT(Ped ped)
	{
		auto retval = PED::REGISTER_PEDHEADSHOT_TRANSPARENT(ped);
		return retval;
	}

	static void LUA_NATIVE_PED_UNREGISTER_PEDHEADSHOT(int id)
	{
		PED::UNREGISTER_PEDHEADSHOT(id);
	}

	static bool LUA_NATIVE_PED_IS_PEDHEADSHOT_VALID(int id)
	{
		auto retval = (bool)PED::IS_PEDHEADSHOT_VALID(id);
		return retval;
	}

	static bool LUA_NATIVE_PED_IS_PEDHEADSHOT_READY(int id)
	{
		auto retval = (bool)PED::IS_PEDHEADSHOT_READY(id);
		return retval;
	}

	static const char* LUA_NATIVE_PED_GET_PEDHEADSHOT_TXD_STRING(int id)
	{
		auto retval = PED::GET_PEDHEADSHOT_TXD_STRING(id);
		return retval;
	}

	static bool LUA_NATIVE_PED_REQUEST_PEDHEADSHOT_IMG_UPLOAD(int id)
	{
		auto retval = (bool)PED::REQUEST_PEDHEADSHOT_IMG_UPLOAD(id);
		return retval;
	}

	static void LUA_NATIVE_PED_RELEASE_PEDHEADSHOT_IMG_UPLOAD(int id)
	{
		PED::RELEASE_PEDHEADSHOT_IMG_UPLOAD(id);
	}

	static bool LUA_NATIVE_PED_IS_PEDHEADSHOT_IMG_UPLOAD_AVAILABLE()
	{
		auto retval = (bool)PED::IS_PEDHEADSHOT_IMG_UPLOAD_AVAILABLE();
		return retval;
	}

	static bool LUA_NATIVE_PED_HAS_PEDHEADSHOT_IMG_UPLOAD_FAILED()
	{
		auto retval = (bool)PED::HAS_PEDHEADSHOT_IMG_UPLOAD_FAILED();
		return retval;
	}

	static bool LUA_NATIVE_PED_HAS_PEDHEADSHOT_IMG_UPLOAD_SUCCEEDED()
	{
		auto retval = (bool)PED::HAS_PEDHEADSHOT_IMG_UPLOAD_SUCCEEDED();
		return retval;
	}

	static void LUA_NATIVE_PED_SET_PED_HEATSCALE_OVERRIDE(Ped ped, float heatScale)
	{
		PED::SET_PED_HEATSCALE_OVERRIDE(ped, heatScale);
	}

	static void LUA_NATIVE_PED_DISABLE_PED_HEATSCALE_OVERRIDE(Ped ped)
	{
		PED::DISABLE_PED_HEATSCALE_OVERRIDE(ped);
	}

	static void LUA_NATIVE_PED_SPAWNPOINTS_START_SEARCH(float p0, float p1, float p2, float p3, float p4, int interiorFlags, float scale, int duration)
	{
		PED::SPAWNPOINTS_START_SEARCH(p0, p1, p2, p3, p4, interiorFlags, scale, duration);
	}

	static void LUA_NATIVE_PED_SPAWNPOINTS_START_SEARCH_IN_ANGLED_AREA(float x1, float y1, float z1, float x2, float y2, float z2, float width, int interiorFlags, float scale, int duration)
	{
		PED::SPAWNPOINTS_START_SEARCH_IN_ANGLED_AREA(x1, y1, z1, x2, y2, z2, width, interiorFlags, scale, duration);
	}

	static void LUA_NATIVE_PED_SPAWNPOINTS_CANCEL_SEARCH()
	{
		PED::SPAWNPOINTS_CANCEL_SEARCH();
	}

	static bool LUA_NATIVE_PED_SPAWNPOINTS_IS_SEARCH_ACTIVE()
	{
		auto retval = (bool)PED::SPAWNPOINTS_IS_SEARCH_ACTIVE();
		return retval;
	}

	static bool LUA_NATIVE_PED_SPAWNPOINTS_IS_SEARCH_COMPLETE()
	{
		auto retval = (bool)PED::SPAWNPOINTS_IS_SEARCH_COMPLETE();
		return retval;
	}

	static bool LUA_NATIVE_PED_SPAWNPOINTS_IS_SEARCH_FAILED()
	{
		auto retval = (bool)PED::SPAWNPOINTS_IS_SEARCH_FAILED();
		return retval;
	}

	static int LUA_NATIVE_PED_SPAWNPOINTS_GET_NUM_SEARCH_RESULTS()
	{
		auto retval = PED::SPAWNPOINTS_GET_NUM_SEARCH_RESULTS();
		return retval;
	}

	static std::tuple<float, float, float> LUA_NATIVE_PED_SPAWNPOINTS_GET_SEARCH_RESULT(int randomInt, float x, float y, float z)
	{
		std::tuple<float, float, float> return_values;
		PED::SPAWNPOINTS_GET_SEARCH_RESULT(randomInt, &x, &y, &z);
		std::get<0>(return_values) = x;
		std::get<1>(return_values) = y;
		std::get<2>(return_values) = z;

		return return_values;
	}

	static int LUA_NATIVE_PED_SPAWNPOINTS_GET_SEARCH_RESULT_FLAGS(int p0, int p1)
	{
		PED::SPAWNPOINTS_GET_SEARCH_RESULT_FLAGS(p0, &p1);
		return p1;
	}

	static void LUA_NATIVE_PED_SET_IK_TARGET(Ped ped, int ikIndex, Entity entityLookAt, int boneLookAt, float offsetX, float offsetY, float offsetZ, Any p7, int blendInDuration, int blendOutDuration)
	{
		PED::SET_IK_TARGET(ped, ikIndex, entityLookAt, boneLookAt, offsetX, offsetY, offsetZ, p7, blendInDuration, blendOutDuration);
	}

	static void LUA_NATIVE_PED_FORCE_INSTANT_LEG_IK_SETUP(Ped ped)
	{
		PED::FORCE_INSTANT_LEG_IK_SETUP(ped);
	}

	static void LUA_NATIVE_PED_REQUEST_ACTION_MODE_ASSET(sol::stack_object asset)
	{
		PED::REQUEST_ACTION_MODE_ASSET(asset.is<const char*>() ? asset.as<const char*>() : nullptr);
	}

	static bool LUA_NATIVE_PED_HAS_ACTION_MODE_ASSET_LOADED(sol::stack_object asset)
	{
		auto retval = (bool)PED::HAS_ACTION_MODE_ASSET_LOADED(asset.is<const char*>() ? asset.as<const char*>() : nullptr);
		return retval;
	}

	static void LUA_NATIVE_PED_REMOVE_ACTION_MODE_ASSET(sol::stack_object asset)
	{
		PED::REMOVE_ACTION_MODE_ASSET(asset.is<const char*>() ? asset.as<const char*>() : nullptr);
	}

	static void LUA_NATIVE_PED_REQUEST_STEALTH_MODE_ASSET(sol::stack_object asset)
	{
		PED::REQUEST_STEALTH_MODE_ASSET(asset.is<const char*>() ? asset.as<const char*>() : nullptr);
	}

	static bool LUA_NATIVE_PED_HAS_STEALTH_MODE_ASSET_LOADED(sol::stack_object asset)
	{
		auto retval = (bool)PED::HAS_STEALTH_MODE_ASSET_LOADED(asset.is<const char*>() ? asset.as<const char*>() : nullptr);
		return retval;
	}

	static void LUA_NATIVE_PED_REMOVE_STEALTH_MODE_ASSET(sol::stack_object asset)
	{
		PED::REMOVE_STEALTH_MODE_ASSET(asset.is<const char*>() ? asset.as<const char*>() : nullptr);
	}

	static void LUA_NATIVE_PED_SET_PED_LOD_MULTIPLIER(Ped ped, float multiplier)
	{
		PED::SET_PED_LOD_MULTIPLIER(ped, multiplier);
	}

	static void LUA_NATIVE_PED_SET_PED_CAN_LOSE_PROPS_ON_DAMAGE(Ped ped, bool toggle, int p2)
	{
		PED::SET_PED_CAN_LOSE_PROPS_ON_DAMAGE(ped, toggle, p2);
	}

	static void LUA_NATIVE_PED_SET_FORCE_FOOTSTEP_UPDATE(Ped ped, bool toggle)
	{
		PED::SET_FORCE_FOOTSTEP_UPDATE(ped, toggle);
	}

	static void LUA_NATIVE_PED_SET_FORCE_STEP_TYPE(Ped ped, bool p1, int type, int p3)
	{
		PED::SET_FORCE_STEP_TYPE(ped, p1, type, p3);
	}

	static bool LUA_NATIVE_PED_IS_ANY_HOSTILE_PED_NEAR_POINT(Ped ped, float x, float y, float z, float radius)
	{
		auto retval = (bool)PED::IS_ANY_HOSTILE_PED_NEAR_POINT(ped, x, y, z, radius);
		return retval;
	}

	static void LUA_NATIVE_PED_SET_PED_CAN_PLAY_IN_CAR_IDLES(Ped ped, bool toggle)
	{
		PED::SET_PED_CAN_PLAY_IN_CAR_IDLES(ped, toggle);
	}

	static bool LUA_NATIVE_PED_IS_TARGET_PED_IN_PERCEPTION_AREA(Ped ped, Ped targetPed, float p2, float p3, float p4, float p5)
	{
		auto retval = (bool)PED::IS_TARGET_PED_IN_PERCEPTION_AREA(ped, targetPed, p2, p3, p4, p5);
		return retval;
	}

	static void LUA_NATIVE_PED_SET_POP_CONTROL_SPHERE_THIS_FRAME(float x, float y, float z, float min, float max)
	{
		PED::SET_POP_CONTROL_SPHERE_THIS_FRAME(x, y, z, min, max);
	}

	static void LUA_NATIVE_PED_FORCE_ZERO_MASS_IN_COLLISIONS(Ped ped)
	{
		PED::FORCE_ZERO_MASS_IN_COLLISIONS(ped);
	}

	static void LUA_NATIVE_PED_SET_DISABLE_HIGH_FALL_DEATH(Ped ped, bool toggle)
	{
		PED::SET_DISABLE_HIGH_FALL_DEATH(ped, toggle);
	}

	static void LUA_NATIVE_PED_SET_PED_PHONE_PALETTE_IDX(Any p0, Any p1)
	{
		PED::SET_PED_PHONE_PALETTE_IDX(p0, p1);
	}

	static void LUA_NATIVE_PED_SET_PED_STEER_BIAS(Ped ped, float value)
	{
		PED::SET_PED_STEER_BIAS(ped, value);
	}

	static bool LUA_NATIVE_PED_IS_PED_SWITCHING_WEAPON(Ped Ped)
	{
		auto retval = (bool)PED::IS_PED_SWITCHING_WEAPON(Ped);
		return retval;
	}

	static void LUA_NATIVE_PED_SET_PED_TREATED_AS_FRIENDLY(Any p0, Any p1, Any p2)
	{
		PED::SET_PED_TREATED_AS_FRIENDLY(p0, p1, p2);
	}

	static void LUA_NATIVE_PED_SET_DISABLE_PED_MAP_COLLISION(Ped ped)
	{
		PED::SET_DISABLE_PED_MAP_COLLISION(ped);
	}

	static void LUA_NATIVE_PED_ENABLE_MP_LIGHT(Ped ped, bool toggle)
	{
		PED::ENABLE_MP_LIGHT(ped, toggle);
	}

	static bool LUA_NATIVE_PED_GET_MP_LIGHT_ENABLED(Ped ped)
	{
		auto retval = (bool)PED::GET_MP_LIGHT_ENABLED(ped);
		return retval;
	}

	static void LUA_NATIVE_PED_CLEAR_COVER_POINT_FOR_PED(Ped ped)
	{
		PED::CLEAR_COVER_POINT_FOR_PED(ped);
	}

	static void LUA_NATIVE_PED_SET_ALLOW_STUNT_JUMP_CAMERA(Ped ped, bool toggle)
	{
		PED::SET_ALLOW_STUNT_JUMP_CAMERA(ped, toggle);
	}

	void init_native_binding_PED(sol::state& L)
	{
		auto PED = L["PED"].get_or_create<sol::table>();
		PED.set_function("CREATE_PED", LUA_NATIVE_PED_CREATE_PED);
		PED.set_function("DELETE_PED", LUA_NATIVE_PED_DELETE_PED);
		PED.set_function("CLONE_PED", LUA_NATIVE_PED_CLONE_PED);
		PED.set_function("CLONE_PED_ALT", LUA_NATIVE_PED_CLONE_PED_ALT);
		PED.set_function("CLONE_PED_TO_TARGET", LUA_NATIVE_PED_CLONE_PED_TO_TARGET);
		PED.set_function("CLONE_PED_TO_TARGET_ALT", LUA_NATIVE_PED_CLONE_PED_TO_TARGET_ALT);
		PED.set_function("IS_PED_IN_VEHICLE", LUA_NATIVE_PED_IS_PED_IN_VEHICLE);
		PED.set_function("IS_PED_IN_MODEL", LUA_NATIVE_PED_IS_PED_IN_MODEL);
		PED.set_function("IS_PED_IN_ANY_VEHICLE", LUA_NATIVE_PED_IS_PED_IN_ANY_VEHICLE);
		PED.set_function("IS_COP_PED_IN_AREA_3D", LUA_NATIVE_PED_IS_COP_PED_IN_AREA_3D);
		PED.set_function("IS_PED_INJURED", LUA_NATIVE_PED_IS_PED_INJURED);
		PED.set_function("IS_PED_HURT", LUA_NATIVE_PED_IS_PED_HURT);
		PED.set_function("IS_PED_FATALLY_INJURED", LUA_NATIVE_PED_IS_PED_FATALLY_INJURED);
		PED.set_function("IS_PED_DEAD_OR_DYING", LUA_NATIVE_PED_IS_PED_DEAD_OR_DYING);
		PED.set_function("IS_CONVERSATION_PED_DEAD", LUA_NATIVE_PED_IS_CONVERSATION_PED_DEAD);
		PED.set_function("IS_PED_AIMING_FROM_COVER", LUA_NATIVE_PED_IS_PED_AIMING_FROM_COVER);
		PED.set_function("IS_PED_RELOADING", LUA_NATIVE_PED_IS_PED_RELOADING);
		PED.set_function("IS_PED_A_PLAYER", LUA_NATIVE_PED_IS_PED_A_PLAYER);
		PED.set_function("CREATE_PED_INSIDE_VEHICLE", LUA_NATIVE_PED_CREATE_PED_INSIDE_VEHICLE);
		PED.set_function("SET_PED_DESIRED_HEADING", LUA_NATIVE_PED_SET_PED_DESIRED_HEADING);
		PED.set_function("FORCE_ALL_HEADING_VALUES_TO_ALIGN", LUA_NATIVE_PED_FORCE_ALL_HEADING_VALUES_TO_ALIGN);
		PED.set_function("IS_PED_FACING_PED", LUA_NATIVE_PED_IS_PED_FACING_PED);
		PED.set_function("IS_PED_IN_MELEE_COMBAT", LUA_NATIVE_PED_IS_PED_IN_MELEE_COMBAT);
		PED.set_function("IS_PED_STOPPED", LUA_NATIVE_PED_IS_PED_STOPPED);
		PED.set_function("IS_PED_SHOOTING_IN_AREA", LUA_NATIVE_PED_IS_PED_SHOOTING_IN_AREA);
		PED.set_function("IS_ANY_PED_SHOOTING_IN_AREA", LUA_NATIVE_PED_IS_ANY_PED_SHOOTING_IN_AREA);
		PED.set_function("IS_PED_SHOOTING", LUA_NATIVE_PED_IS_PED_SHOOTING);
		PED.set_function("SET_PED_ACCURACY", LUA_NATIVE_PED_SET_PED_ACCURACY);
		PED.set_function("GET_PED_ACCURACY", LUA_NATIVE_PED_GET_PED_ACCURACY);
		PED.set_function("SET_AMBIENT_LAW_PED_ACCURACY_MODIFIER", LUA_NATIVE_PED_SET_AMBIENT_LAW_PED_ACCURACY_MODIFIER);
		PED.set_function("IS_PED_MODEL", LUA_NATIVE_PED_IS_PED_MODEL);
		PED.set_function("EXPLODE_PED_HEAD", LUA_NATIVE_PED_EXPLODE_PED_HEAD);
		PED.set_function("REMOVE_PED_ELEGANTLY", LUA_NATIVE_PED_REMOVE_PED_ELEGANTLY);
		PED.set_function("ADD_ARMOUR_TO_PED", LUA_NATIVE_PED_ADD_ARMOUR_TO_PED);
		PED.set_function("SET_PED_ARMOUR", LUA_NATIVE_PED_SET_PED_ARMOUR);
		PED.set_function("SET_PED_INTO_VEHICLE", LUA_NATIVE_PED_SET_PED_INTO_VEHICLE);
		PED.set_function("SET_PED_ALLOW_VEHICLES_OVERRIDE", LUA_NATIVE_PED_SET_PED_ALLOW_VEHICLES_OVERRIDE);
		PED.set_function("CAN_CREATE_RANDOM_PED", LUA_NATIVE_PED_CAN_CREATE_RANDOM_PED);
		PED.set_function("CREATE_RANDOM_PED", LUA_NATIVE_PED_CREATE_RANDOM_PED);
		PED.set_function("CREATE_RANDOM_PED_AS_DRIVER", LUA_NATIVE_PED_CREATE_RANDOM_PED_AS_DRIVER);
		PED.set_function("CAN_CREATE_RANDOM_DRIVER", LUA_NATIVE_PED_CAN_CREATE_RANDOM_DRIVER);
		PED.set_function("CAN_CREATE_RANDOM_BIKE_RIDER", LUA_NATIVE_PED_CAN_CREATE_RANDOM_BIKE_RIDER);
		PED.set_function("SET_PED_MOVE_ANIMS_BLEND_OUT", LUA_NATIVE_PED_SET_PED_MOVE_ANIMS_BLEND_OUT);
		PED.set_function("SET_PED_CAN_BE_DRAGGED_OUT", LUA_NATIVE_PED_SET_PED_CAN_BE_DRAGGED_OUT);
		PED.set_function("SET_PED_ALLOW_HURT_COMBAT_FOR_ALL_MISSION_PEDS", LUA_NATIVE_PED_SET_PED_ALLOW_HURT_COMBAT_FOR_ALL_MISSION_PEDS);
		PED.set_function("IS_PED_MALE", LUA_NATIVE_PED_IS_PED_MALE);
		PED.set_function("IS_PED_HUMAN", LUA_NATIVE_PED_IS_PED_HUMAN);
		PED.set_function("GET_VEHICLE_PED_IS_IN", LUA_NATIVE_PED_GET_VEHICLE_PED_IS_IN);
		PED.set_function("RESET_PED_LAST_VEHICLE", LUA_NATIVE_PED_RESET_PED_LAST_VEHICLE);
		PED.set_function("SET_PED_DENSITY_MULTIPLIER_THIS_FRAME", LUA_NATIVE_PED_SET_PED_DENSITY_MULTIPLIER_THIS_FRAME);
		PED.set_function("SET_SCENARIO_PED_DENSITY_MULTIPLIER_THIS_FRAME", LUA_NATIVE_PED_SET_SCENARIO_PED_DENSITY_MULTIPLIER_THIS_FRAME);
		PED.set_function("SUPPRESS_AMBIENT_PED_AGGRESSIVE_CLEANUP_THIS_FRAME", LUA_NATIVE_PED_SUPPRESS_AMBIENT_PED_AGGRESSIVE_CLEANUP_THIS_FRAME);
		PED.set_function("SET_SCRIPTED_CONVERSION_COORD_THIS_FRAME", LUA_NATIVE_PED_SET_SCRIPTED_CONVERSION_COORD_THIS_FRAME);
		PED.set_function("SET_PED_NON_CREATION_AREA", LUA_NATIVE_PED_SET_PED_NON_CREATION_AREA);
		PED.set_function("CLEAR_PED_NON_CREATION_AREA", LUA_NATIVE_PED_CLEAR_PED_NON_CREATION_AREA);
		PED.set_function("INSTANTLY_FILL_PED_POPULATION", LUA_NATIVE_PED_INSTANTLY_FILL_PED_POPULATION);
		PED.set_function("IS_PED_ON_MOUNT", LUA_NATIVE_PED_IS_PED_ON_MOUNT);
		PED.set_function("GET_MOUNT", LUA_NATIVE_PED_GET_MOUNT);
		PED.set_function("IS_PED_ON_VEHICLE", LUA_NATIVE_PED_IS_PED_ON_VEHICLE);
		PED.set_function("IS_PED_ON_SPECIFIC_VEHICLE", LUA_NATIVE_PED_IS_PED_ON_SPECIFIC_VEHICLE);
		PED.set_function("SET_PED_MONEY", LUA_NATIVE_PED_SET_PED_MONEY);
		PED.set_function("GET_PED_MONEY", LUA_NATIVE_PED_GET_PED_MONEY);
		PED.set_function("SET_HEALTH_SNACKS_CARRIED_BY_ALL_NEW_PEDS", LUA_NATIVE_PED_SET_HEALTH_SNACKS_CARRIED_BY_ALL_NEW_PEDS);
		PED.set_function("SET_AMBIENT_PEDS_DROP_MONEY", LUA_NATIVE_PED_SET_AMBIENT_PEDS_DROP_MONEY);
		PED.set_function("SET_BLOCKING_OF_NON_TEMPORARY_EVENTS_FOR_AMBIENT_PEDS_THIS_FRAME", LUA_NATIVE_PED_SET_BLOCKING_OF_NON_TEMPORARY_EVENTS_FOR_AMBIENT_PEDS_THIS_FRAME);
		PED.set_function("SET_PED_SUFFERS_CRITICAL_HITS", LUA_NATIVE_PED_SET_PED_SUFFERS_CRITICAL_HITS);
		PED.set_function("SET_PED_UPPER_BODY_DAMAGE_ONLY", LUA_NATIVE_PED_SET_PED_UPPER_BODY_DAMAGE_ONLY);
		PED.set_function("IS_PED_SITTING_IN_VEHICLE", LUA_NATIVE_PED_IS_PED_SITTING_IN_VEHICLE);
		PED.set_function("IS_PED_SITTING_IN_ANY_VEHICLE", LUA_NATIVE_PED_IS_PED_SITTING_IN_ANY_VEHICLE);
		PED.set_function("IS_PED_ON_FOOT", LUA_NATIVE_PED_IS_PED_ON_FOOT);
		PED.set_function("IS_PED_ON_ANY_BIKE", LUA_NATIVE_PED_IS_PED_ON_ANY_BIKE);
		PED.set_function("IS_PED_PLANTING_BOMB", LUA_NATIVE_PED_IS_PED_PLANTING_BOMB);
		PED.set_function("GET_DEAD_PED_PICKUP_COORDS", LUA_NATIVE_PED_GET_DEAD_PED_PICKUP_COORDS);
		PED.set_function("IS_PED_IN_ANY_BOAT", LUA_NATIVE_PED_IS_PED_IN_ANY_BOAT);
		PED.set_function("IS_PED_IN_ANY_SUB", LUA_NATIVE_PED_IS_PED_IN_ANY_SUB);
		PED.set_function("IS_PED_IN_ANY_HELI", LUA_NATIVE_PED_IS_PED_IN_ANY_HELI);
		PED.set_function("IS_PED_IN_ANY_PLANE", LUA_NATIVE_PED_IS_PED_IN_ANY_PLANE);
		PED.set_function("IS_PED_IN_FLYING_VEHICLE", LUA_NATIVE_PED_IS_PED_IN_FLYING_VEHICLE);
		PED.set_function("SET_PED_DIES_IN_WATER", LUA_NATIVE_PED_SET_PED_DIES_IN_WATER);
		PED.set_function("GET_PED_DIES_IN_WATER", LUA_NATIVE_PED_GET_PED_DIES_IN_WATER);
		PED.set_function("SET_PED_DIES_IN_SINKING_VEHICLE", LUA_NATIVE_PED_SET_PED_DIES_IN_SINKING_VEHICLE);
		PED.set_function("GET_PED_ARMOUR", LUA_NATIVE_PED_GET_PED_ARMOUR);
		PED.set_function("SET_PED_STAY_IN_VEHICLE_WHEN_JACKED", LUA_NATIVE_PED_SET_PED_STAY_IN_VEHICLE_WHEN_JACKED);
		PED.set_function("SET_PED_CAN_BE_SHOT_IN_VEHICLE", LUA_NATIVE_PED_SET_PED_CAN_BE_SHOT_IN_VEHICLE);
		PED.set_function("GET_PED_LAST_DAMAGE_BONE", LUA_NATIVE_PED_GET_PED_LAST_DAMAGE_BONE);
		PED.set_function("CLEAR_PED_LAST_DAMAGE_BONE", LUA_NATIVE_PED_CLEAR_PED_LAST_DAMAGE_BONE);
		PED.set_function("SET_AI_WEAPON_DAMAGE_MODIFIER", LUA_NATIVE_PED_SET_AI_WEAPON_DAMAGE_MODIFIER);
		PED.set_function("RESET_AI_WEAPON_DAMAGE_MODIFIER", LUA_NATIVE_PED_RESET_AI_WEAPON_DAMAGE_MODIFIER);
		PED.set_function("SET_AI_MELEE_WEAPON_DAMAGE_MODIFIER", LUA_NATIVE_PED_SET_AI_MELEE_WEAPON_DAMAGE_MODIFIER);
		PED.set_function("RESET_AI_MELEE_WEAPON_DAMAGE_MODIFIER", LUA_NATIVE_PED_RESET_AI_MELEE_WEAPON_DAMAGE_MODIFIER);
		PED.set_function("SET_TREAT_AS_AMBIENT_PED_FOR_DRIVER_LOCKON", LUA_NATIVE_PED_SET_TREAT_AS_AMBIENT_PED_FOR_DRIVER_LOCKON);
		PED.set_function("SET_PED_CAN_BE_TARGETTED", LUA_NATIVE_PED_SET_PED_CAN_BE_TARGETTED);
		PED.set_function("SET_PED_CAN_BE_TARGETTED_BY_TEAM", LUA_NATIVE_PED_SET_PED_CAN_BE_TARGETTED_BY_TEAM);
		PED.set_function("SET_PED_CAN_BE_TARGETTED_BY_PLAYER", LUA_NATIVE_PED_SET_PED_CAN_BE_TARGETTED_BY_PLAYER);
		PED.set_function("SET_ALLOW_LOCKON_TO_PED_IF_FRIENDLY", LUA_NATIVE_PED_SET_ALLOW_LOCKON_TO_PED_IF_FRIENDLY);
		PED.set_function("SET_USE_CAMERA_HEADING_FOR_DESIRED_DIRECTION_LOCK_ON_TEST", LUA_NATIVE_PED_SET_USE_CAMERA_HEADING_FOR_DESIRED_DIRECTION_LOCK_ON_TEST);
		PED.set_function("IS_PED_IN_ANY_POLICE_VEHICLE", LUA_NATIVE_PED_IS_PED_IN_ANY_POLICE_VEHICLE);
		PED.set_function("FORCE_PED_TO_OPEN_PARACHUTE", LUA_NATIVE_PED_FORCE_PED_TO_OPEN_PARACHUTE);
		PED.set_function("IS_PED_IN_PARACHUTE_FREE_FALL", LUA_NATIVE_PED_IS_PED_IN_PARACHUTE_FREE_FALL);
		PED.set_function("IS_PED_FALLING", LUA_NATIVE_PED_IS_PED_FALLING);
		PED.set_function("IS_PED_JUMPING", LUA_NATIVE_PED_IS_PED_JUMPING);
		PED.set_function("IS_PED_LANDING", LUA_NATIVE_PED_IS_PED_LANDING);
		PED.set_function("IS_PED_DOING_A_BEAST_JUMP", LUA_NATIVE_PED_IS_PED_DOING_A_BEAST_JUMP);
		PED.set_function("IS_PED_CLIMBING", LUA_NATIVE_PED_IS_PED_CLIMBING);
		PED.set_function("IS_PED_VAULTING", LUA_NATIVE_PED_IS_PED_VAULTING);
		PED.set_function("IS_PED_DIVING", LUA_NATIVE_PED_IS_PED_DIVING);
		PED.set_function("IS_PED_JUMPING_OUT_OF_VEHICLE", LUA_NATIVE_PED_IS_PED_JUMPING_OUT_OF_VEHICLE);
		PED.set_function("IS_PED_OPENING_DOOR", LUA_NATIVE_PED_IS_PED_OPENING_DOOR);
		PED.set_function("GET_PED_PARACHUTE_STATE", LUA_NATIVE_PED_GET_PED_PARACHUTE_STATE);
		PED.set_function("GET_PED_PARACHUTE_LANDING_TYPE", LUA_NATIVE_PED_GET_PED_PARACHUTE_LANDING_TYPE);
		PED.set_function("SET_PED_PARACHUTE_TINT_INDEX", LUA_NATIVE_PED_SET_PED_PARACHUTE_TINT_INDEX);
		PED.set_function("GET_PED_PARACHUTE_TINT_INDEX", LUA_NATIVE_PED_GET_PED_PARACHUTE_TINT_INDEX);
		PED.set_function("SET_PED_RESERVE_PARACHUTE_TINT_INDEX", LUA_NATIVE_PED_SET_PED_RESERVE_PARACHUTE_TINT_INDEX);
		PED.set_function("CREATE_PARACHUTE_BAG_OBJECT", LUA_NATIVE_PED_CREATE_PARACHUTE_BAG_OBJECT);
		PED.set_function("SET_PED_DUCKING", LUA_NATIVE_PED_SET_PED_DUCKING);
		PED.set_function("IS_PED_DUCKING", LUA_NATIVE_PED_IS_PED_DUCKING);
		PED.set_function("IS_PED_IN_ANY_TAXI", LUA_NATIVE_PED_IS_PED_IN_ANY_TAXI);
		PED.set_function("SET_PED_ID_RANGE", LUA_NATIVE_PED_SET_PED_ID_RANGE);
		PED.set_function("SET_PED_HIGHLY_PERCEPTIVE", LUA_NATIVE_PED_SET_PED_HIGHLY_PERCEPTIVE);
		PED.set_function("SET_COP_PERCEPTION_OVERRIDES", LUA_NATIVE_PED_SET_COP_PERCEPTION_OVERRIDES);
		PED.set_function("SET_PED_INJURED_ON_GROUND_BEHAVIOUR", LUA_NATIVE_PED_SET_PED_INJURED_ON_GROUND_BEHAVIOUR);
		PED.set_function("DISABLE_PED_INJURED_ON_GROUND_BEHAVIOUR", LUA_NATIVE_PED_DISABLE_PED_INJURED_ON_GROUND_BEHAVIOUR);
		PED.set_function("SET_PED_SEEING_RANGE", LUA_NATIVE_PED_SET_PED_SEEING_RANGE);
		PED.set_function("SET_PED_HEARING_RANGE", LUA_NATIVE_PED_SET_PED_HEARING_RANGE);
		PED.set_function("SET_PED_VISUAL_FIELD_MIN_ANGLE", LUA_NATIVE_PED_SET_PED_VISUAL_FIELD_MIN_ANGLE);
		PED.set_function("SET_PED_VISUAL_FIELD_MAX_ANGLE", LUA_NATIVE_PED_SET_PED_VISUAL_FIELD_MAX_ANGLE);
		PED.set_function("SET_PED_VISUAL_FIELD_MIN_ELEVATION_ANGLE", LUA_NATIVE_PED_SET_PED_VISUAL_FIELD_MIN_ELEVATION_ANGLE);
		PED.set_function("SET_PED_VISUAL_FIELD_MAX_ELEVATION_ANGLE", LUA_NATIVE_PED_SET_PED_VISUAL_FIELD_MAX_ELEVATION_ANGLE);
		PED.set_function("SET_PED_VISUAL_FIELD_PERIPHERAL_RANGE", LUA_NATIVE_PED_SET_PED_VISUAL_FIELD_PERIPHERAL_RANGE);
		PED.set_function("SET_PED_VISUAL_FIELD_CENTER_ANGLE", LUA_NATIVE_PED_SET_PED_VISUAL_FIELD_CENTER_ANGLE);
		PED.set_function("GET_PED_VISUAL_FIELD_CENTER_ANGLE", LUA_NATIVE_PED_GET_PED_VISUAL_FIELD_CENTER_ANGLE);
		PED.set_function("SET_PED_STEALTH_MOVEMENT", LUA_NATIVE_PED_SET_PED_STEALTH_MOVEMENT);
		PED.set_function("GET_PED_STEALTH_MOVEMENT", LUA_NATIVE_PED_GET_PED_STEALTH_MOVEMENT);
		PED.set_function("CREATE_GROUP", LUA_NATIVE_PED_CREATE_GROUP);
		PED.set_function("SET_PED_AS_GROUP_LEADER", LUA_NATIVE_PED_SET_PED_AS_GROUP_LEADER);
		PED.set_function("SET_PED_AS_GROUP_MEMBER", LUA_NATIVE_PED_SET_PED_AS_GROUP_MEMBER);
		PED.set_function("SET_PED_CAN_TELEPORT_TO_GROUP_LEADER", LUA_NATIVE_PED_SET_PED_CAN_TELEPORT_TO_GROUP_LEADER);
		PED.set_function("REMOVE_GROUP", LUA_NATIVE_PED_REMOVE_GROUP);
		PED.set_function("REMOVE_PED_FROM_GROUP", LUA_NATIVE_PED_REMOVE_PED_FROM_GROUP);
		PED.set_function("IS_PED_GROUP_MEMBER", LUA_NATIVE_PED_IS_PED_GROUP_MEMBER);
		PED.set_function("IS_PED_HANGING_ON_TO_VEHICLE", LUA_NATIVE_PED_IS_PED_HANGING_ON_TO_VEHICLE);
		PED.set_function("SET_GROUP_SEPARATION_RANGE", LUA_NATIVE_PED_SET_GROUP_SEPARATION_RANGE);
		PED.set_function("SET_PED_MIN_GROUND_TIME_FOR_STUNGUN", LUA_NATIVE_PED_SET_PED_MIN_GROUND_TIME_FOR_STUNGUN);
		PED.set_function("IS_PED_PRONE", LUA_NATIVE_PED_IS_PED_PRONE);
		PED.set_function("IS_PED_IN_COMBAT", LUA_NATIVE_PED_IS_PED_IN_COMBAT);
		PED.set_function("GET_PED_TARGET_FROM_COMBAT_PED", LUA_NATIVE_PED_GET_PED_TARGET_FROM_COMBAT_PED);
		PED.set_function("CAN_PED_IN_COMBAT_SEE_TARGET", LUA_NATIVE_PED_CAN_PED_IN_COMBAT_SEE_TARGET);
		PED.set_function("IS_PED_DOING_DRIVEBY", LUA_NATIVE_PED_IS_PED_DOING_DRIVEBY);
		PED.set_function("IS_PED_JACKING", LUA_NATIVE_PED_IS_PED_JACKING);
		PED.set_function("IS_PED_BEING_JACKED", LUA_NATIVE_PED_IS_PED_BEING_JACKED);
		PED.set_function("IS_PED_BEING_STUNNED", LUA_NATIVE_PED_IS_PED_BEING_STUNNED);
		PED.set_function("GET_PEDS_JACKER", LUA_NATIVE_PED_GET_PEDS_JACKER);
		PED.set_function("GET_JACK_TARGET", LUA_NATIVE_PED_GET_JACK_TARGET);
		PED.set_function("IS_PED_FLEEING", LUA_NATIVE_PED_IS_PED_FLEEING);
		PED.set_function("IS_PED_IN_COVER", LUA_NATIVE_PED_IS_PED_IN_COVER);
		PED.set_function("IS_PED_IN_COVER_FACING_LEFT", LUA_NATIVE_PED_IS_PED_IN_COVER_FACING_LEFT);
		PED.set_function("IS_PED_IN_HIGH_COVER", LUA_NATIVE_PED_IS_PED_IN_HIGH_COVER);
		PED.set_function("IS_PED_GOING_INTO_COVER", LUA_NATIVE_PED_IS_PED_GOING_INTO_COVER);
		PED.set_function("SET_PED_PINNED_DOWN", LUA_NATIVE_PED_SET_PED_PINNED_DOWN);
		PED.set_function("HAS_PED_CLEAR_LOS_TO_ENTITY_", LUA_NATIVE_PED_HAS_PED_CLEAR_LOS_TO_ENTITY_);
		PED.set_function("GET_SEAT_PED_IS_TRYING_TO_ENTER", LUA_NATIVE_PED_GET_SEAT_PED_IS_TRYING_TO_ENTER);
		PED.set_function("GET_VEHICLE_PED_IS_TRYING_TO_ENTER", LUA_NATIVE_PED_GET_VEHICLE_PED_IS_TRYING_TO_ENTER);
		PED.set_function("GET_PED_SOURCE_OF_DEATH", LUA_NATIVE_PED_GET_PED_SOURCE_OF_DEATH);
		PED.set_function("GET_PED_CAUSE_OF_DEATH", LUA_NATIVE_PED_GET_PED_CAUSE_OF_DEATH);
		PED.set_function("GET_PED_TIME_OF_DEATH", LUA_NATIVE_PED_GET_PED_TIME_OF_DEATH);
		PED.set_function("COUNT_PEDS_IN_COMBAT_WITH_TARGET", LUA_NATIVE_PED_COUNT_PEDS_IN_COMBAT_WITH_TARGET);
		PED.set_function("COUNT_PEDS_IN_COMBAT_WITH_TARGET_WITHIN_RADIUS", LUA_NATIVE_PED_COUNT_PEDS_IN_COMBAT_WITH_TARGET_WITHIN_RADIUS);
		PED.set_function("SET_PED_RELATIONSHIP_GROUP_DEFAULT_HASH", LUA_NATIVE_PED_SET_PED_RELATIONSHIP_GROUP_DEFAULT_HASH);
		PED.set_function("SET_PED_RELATIONSHIP_GROUP_HASH", LUA_NATIVE_PED_SET_PED_RELATIONSHIP_GROUP_HASH);
		PED.set_function("SET_RELATIONSHIP_BETWEEN_GROUPS", LUA_NATIVE_PED_SET_RELATIONSHIP_BETWEEN_GROUPS);
		PED.set_function("CLEAR_RELATIONSHIP_BETWEEN_GROUPS", LUA_NATIVE_PED_CLEAR_RELATIONSHIP_BETWEEN_GROUPS);
		PED.set_function("ADD_RELATIONSHIP_GROUP", LUA_NATIVE_PED_ADD_RELATIONSHIP_GROUP);
		PED.set_function("REMOVE_RELATIONSHIP_GROUP", LUA_NATIVE_PED_REMOVE_RELATIONSHIP_GROUP);
		PED.set_function("DOES_RELATIONSHIP_GROUP_EXIST", LUA_NATIVE_PED_DOES_RELATIONSHIP_GROUP_EXIST);
		PED.set_function("GET_RELATIONSHIP_BETWEEN_PEDS", LUA_NATIVE_PED_GET_RELATIONSHIP_BETWEEN_PEDS);
		PED.set_function("GET_PED_RELATIONSHIP_GROUP_DEFAULT_HASH", LUA_NATIVE_PED_GET_PED_RELATIONSHIP_GROUP_DEFAULT_HASH);
		PED.set_function("GET_PED_RELATIONSHIP_GROUP_HASH", LUA_NATIVE_PED_GET_PED_RELATIONSHIP_GROUP_HASH);
		PED.set_function("GET_RELATIONSHIP_BETWEEN_GROUPS", LUA_NATIVE_PED_GET_RELATIONSHIP_BETWEEN_GROUPS);
		PED.set_function("SET_RELATIONSHIP_GROUP_AFFECTS_WANTED_LEVEL", LUA_NATIVE_PED_SET_RELATIONSHIP_GROUP_AFFECTS_WANTED_LEVEL);
		PED.set_function("TELL_GROUP_PEDS_IN_AREA_TO_ATTACK", LUA_NATIVE_PED_TELL_GROUP_PEDS_IN_AREA_TO_ATTACK);
		PED.set_function("SET_PED_CAN_BE_TARGETED_WITHOUT_LOS", LUA_NATIVE_PED_SET_PED_CAN_BE_TARGETED_WITHOUT_LOS);
		PED.set_function("SET_PED_TO_INFORM_RESPECTED_FRIENDS", LUA_NATIVE_PED_SET_PED_TO_INFORM_RESPECTED_FRIENDS);
		PED.set_function("IS_PED_RESPONDING_TO_EVENT", LUA_NATIVE_PED_IS_PED_RESPONDING_TO_EVENT);
		PED.set_function("GET_POS_FROM_FIRED_EVENT", LUA_NATIVE_PED_GET_POS_FROM_FIRED_EVENT);
		PED.set_function("SET_PED_FIRING_PATTERN", LUA_NATIVE_PED_SET_PED_FIRING_PATTERN);
		PED.set_function("SET_PED_SHOOT_RATE", LUA_NATIVE_PED_SET_PED_SHOOT_RATE);
		PED.set_function("SET_COMBAT_FLOAT", LUA_NATIVE_PED_SET_COMBAT_FLOAT);
		PED.set_function("GET_COMBAT_FLOAT", LUA_NATIVE_PED_GET_COMBAT_FLOAT);
		PED.set_function("GET_GROUP_SIZE", LUA_NATIVE_PED_GET_GROUP_SIZE);
		PED.set_function("DOES_GROUP_EXIST", LUA_NATIVE_PED_DOES_GROUP_EXIST);
		PED.set_function("GET_PED_GROUP_INDEX", LUA_NATIVE_PED_GET_PED_GROUP_INDEX);
		PED.set_function("IS_PED_IN_GROUP", LUA_NATIVE_PED_IS_PED_IN_GROUP);
		PED.set_function("GET_PLAYER_PED_IS_FOLLOWING", LUA_NATIVE_PED_GET_PLAYER_PED_IS_FOLLOWING);
		PED.set_function("SET_GROUP_FORMATION", LUA_NATIVE_PED_SET_GROUP_FORMATION);
		PED.set_function("SET_GROUP_FORMATION_SPACING", LUA_NATIVE_PED_SET_GROUP_FORMATION_SPACING);
		PED.set_function("RESET_GROUP_FORMATION_DEFAULT_SPACING", LUA_NATIVE_PED_RESET_GROUP_FORMATION_DEFAULT_SPACING);
		PED.set_function("GET_VEHICLE_PED_IS_USING", LUA_NATIVE_PED_GET_VEHICLE_PED_IS_USING);
		PED.set_function("GET_VEHICLE_PED_IS_ENTERING", LUA_NATIVE_PED_GET_VEHICLE_PED_IS_ENTERING);
		PED.set_function("SET_PED_GRAVITY", LUA_NATIVE_PED_SET_PED_GRAVITY);
		PED.set_function("APPLY_DAMAGE_TO_PED", LUA_NATIVE_PED_APPLY_DAMAGE_TO_PED);
		PED.set_function("GET_TIME_PED_DAMAGED_BY_WEAPON", LUA_NATIVE_PED_GET_TIME_PED_DAMAGED_BY_WEAPON);
		PED.set_function("SET_PED_ALLOWED_TO_DUCK", LUA_NATIVE_PED_SET_PED_ALLOWED_TO_DUCK);
		PED.set_function("SET_PED_NEVER_LEAVES_GROUP", LUA_NATIVE_PED_SET_PED_NEVER_LEAVES_GROUP);
		PED.set_function("GET_PED_TYPE", LUA_NATIVE_PED_GET_PED_TYPE);
		PED.set_function("SET_PED_AS_COP", LUA_NATIVE_PED_SET_PED_AS_COP);
		PED.set_function("SET_PED_HEALTH_PENDING_LAST_DAMAGE_EVENT_OVERRIDE_FLAG", LUA_NATIVE_PED_SET_PED_HEALTH_PENDING_LAST_DAMAGE_EVENT_OVERRIDE_FLAG);
		PED.set_function("SET_PED_MAX_HEALTH", LUA_NATIVE_PED_SET_PED_MAX_HEALTH);
		PED.set_function("GET_PED_MAX_HEALTH", LUA_NATIVE_PED_GET_PED_MAX_HEALTH);
		PED.set_function("SET_PED_MAX_TIME_IN_WATER", LUA_NATIVE_PED_SET_PED_MAX_TIME_IN_WATER);
		PED.set_function("SET_PED_MAX_TIME_UNDERWATER", LUA_NATIVE_PED_SET_PED_MAX_TIME_UNDERWATER);
		PED.set_function("SET_CORPSE_RAGDOLL_FRICTION", LUA_NATIVE_PED_SET_CORPSE_RAGDOLL_FRICTION);
		PED.set_function("SET_PED_VEHICLE_FORCED_SEAT_USAGE", LUA_NATIVE_PED_SET_PED_VEHICLE_FORCED_SEAT_USAGE);
		PED.set_function("CLEAR_ALL_PED_VEHICLE_FORCED_SEAT_USAGE", LUA_NATIVE_PED_CLEAR_ALL_PED_VEHICLE_FORCED_SEAT_USAGE);
		PED.set_function("SET_PED_CAN_BE_KNOCKED_OFF_BIKE", LUA_NATIVE_PED_SET_PED_CAN_BE_KNOCKED_OFF_BIKE);
		PED.set_function("SET_PED_CAN_BE_KNOCKED_OFF_VEHICLE", LUA_NATIVE_PED_SET_PED_CAN_BE_KNOCKED_OFF_VEHICLE);
		PED.set_function("CAN_KNOCK_PED_OFF_VEHICLE", LUA_NATIVE_PED_CAN_KNOCK_PED_OFF_VEHICLE);
		PED.set_function("KNOCK_PED_OFF_VEHICLE", LUA_NATIVE_PED_KNOCK_PED_OFF_VEHICLE);
		PED.set_function("SET_PED_COORDS_NO_GANG", LUA_NATIVE_PED_SET_PED_COORDS_NO_GANG);
		PED.set_function("GET_PED_AS_GROUP_MEMBER", LUA_NATIVE_PED_GET_PED_AS_GROUP_MEMBER);
		PED.set_function("GET_PED_AS_GROUP_LEADER", LUA_NATIVE_PED_GET_PED_AS_GROUP_LEADER);
		PED.set_function("SET_PED_KEEP_TASK", LUA_NATIVE_PED_SET_PED_KEEP_TASK);
		PED.set_function("SET_PED_ALLOW_MINOR_REACTIONS_AS_MISSION_PED", LUA_NATIVE_PED_SET_PED_ALLOW_MINOR_REACTIONS_AS_MISSION_PED);
		PED.set_function("IS_PED_SWIMMING", LUA_NATIVE_PED_IS_PED_SWIMMING);
		PED.set_function("IS_PED_SWIMMING_UNDER_WATER", LUA_NATIVE_PED_IS_PED_SWIMMING_UNDER_WATER);
		PED.set_function("SET_PED_COORDS_KEEP_VEHICLE", LUA_NATIVE_PED_SET_PED_COORDS_KEEP_VEHICLE);
		PED.set_function("SET_PED_DIES_IN_VEHICLE", LUA_NATIVE_PED_SET_PED_DIES_IN_VEHICLE);
		PED.set_function("SET_CREATE_RANDOM_COPS", LUA_NATIVE_PED_SET_CREATE_RANDOM_COPS);
		PED.set_function("SET_CREATE_RANDOM_COPS_NOT_ON_SCENARIOS", LUA_NATIVE_PED_SET_CREATE_RANDOM_COPS_NOT_ON_SCENARIOS);
		PED.set_function("SET_CREATE_RANDOM_COPS_ON_SCENARIOS", LUA_NATIVE_PED_SET_CREATE_RANDOM_COPS_ON_SCENARIOS);
		PED.set_function("CAN_CREATE_RANDOM_COPS", LUA_NATIVE_PED_CAN_CREATE_RANDOM_COPS);
		PED.set_function("SET_PED_AS_ENEMY", LUA_NATIVE_PED_SET_PED_AS_ENEMY);
		PED.set_function("SET_PED_CAN_SMASH_GLASS", LUA_NATIVE_PED_SET_PED_CAN_SMASH_GLASS);
		PED.set_function("IS_PED_IN_ANY_TRAIN", LUA_NATIVE_PED_IS_PED_IN_ANY_TRAIN);
		PED.set_function("IS_PED_GETTING_INTO_A_VEHICLE", LUA_NATIVE_PED_IS_PED_GETTING_INTO_A_VEHICLE);
		PED.set_function("IS_PED_TRYING_TO_ENTER_A_LOCKED_VEHICLE", LUA_NATIVE_PED_IS_PED_TRYING_TO_ENTER_A_LOCKED_VEHICLE);
		PED.set_function("SET_ENABLE_HANDCUFFS", LUA_NATIVE_PED_SET_ENABLE_HANDCUFFS);
		PED.set_function("SET_ENABLE_BOUND_ANKLES", LUA_NATIVE_PED_SET_ENABLE_BOUND_ANKLES);
		PED.set_function("SET_ENABLE_SCUBA", LUA_NATIVE_PED_SET_ENABLE_SCUBA);
		PED.set_function("SET_CAN_ATTACK_FRIENDLY", LUA_NATIVE_PED_SET_CAN_ATTACK_FRIENDLY);
		PED.set_function("GET_PED_ALERTNESS", LUA_NATIVE_PED_GET_PED_ALERTNESS);
		PED.set_function("SET_PED_ALERTNESS", LUA_NATIVE_PED_SET_PED_ALERTNESS);
		PED.set_function("SET_PED_GET_OUT_UPSIDE_DOWN_VEHICLE", LUA_NATIVE_PED_SET_PED_GET_OUT_UPSIDE_DOWN_VEHICLE);
		PED.set_function("SET_PED_MOVEMENT_CLIPSET", LUA_NATIVE_PED_SET_PED_MOVEMENT_CLIPSET);
		PED.set_function("RESET_PED_MOVEMENT_CLIPSET", LUA_NATIVE_PED_RESET_PED_MOVEMENT_CLIPSET);
		PED.set_function("SET_PED_STRAFE_CLIPSET", LUA_NATIVE_PED_SET_PED_STRAFE_CLIPSET);
		PED.set_function("RESET_PED_STRAFE_CLIPSET", LUA_NATIVE_PED_RESET_PED_STRAFE_CLIPSET);
		PED.set_function("SET_PED_WEAPON_MOVEMENT_CLIPSET", LUA_NATIVE_PED_SET_PED_WEAPON_MOVEMENT_CLIPSET);
		PED.set_function("RESET_PED_WEAPON_MOVEMENT_CLIPSET", LUA_NATIVE_PED_RESET_PED_WEAPON_MOVEMENT_CLIPSET);
		PED.set_function("SET_PED_DRIVE_BY_CLIPSET_OVERRIDE", LUA_NATIVE_PED_SET_PED_DRIVE_BY_CLIPSET_OVERRIDE);
		PED.set_function("CLEAR_PED_DRIVE_BY_CLIPSET_OVERRIDE", LUA_NATIVE_PED_CLEAR_PED_DRIVE_BY_CLIPSET_OVERRIDE);
		PED.set_function("SET_PED_MOTION_IN_COVER_CLIPSET_OVERRIDE", LUA_NATIVE_PED_SET_PED_MOTION_IN_COVER_CLIPSET_OVERRIDE);
		PED.set_function("CLEAR_PED_MOTION_IN_COVER_CLIPSET_OVERRIDE", LUA_NATIVE_PED_CLEAR_PED_MOTION_IN_COVER_CLIPSET_OVERRIDE);
		PED.set_function("CLEAR_PED_FALL_UPPER_BODY_CLIPSET_OVERRIDE", LUA_NATIVE_PED_CLEAR_PED_FALL_UPPER_BODY_CLIPSET_OVERRIDE);
		PED.set_function("SET_PED_IN_VEHICLE_CONTEXT", LUA_NATIVE_PED_SET_PED_IN_VEHICLE_CONTEXT);
		PED.set_function("RESET_PED_IN_VEHICLE_CONTEXT", LUA_NATIVE_PED_RESET_PED_IN_VEHICLE_CONTEXT);
		PED.set_function("IS_SCRIPTED_SCENARIO_PED_USING_CONDITIONAL_ANIM", LUA_NATIVE_PED_IS_SCRIPTED_SCENARIO_PED_USING_CONDITIONAL_ANIM);
		PED.set_function("SET_PED_ALTERNATE_WALK_ANIM", LUA_NATIVE_PED_SET_PED_ALTERNATE_WALK_ANIM);
		PED.set_function("CLEAR_PED_ALTERNATE_WALK_ANIM", LUA_NATIVE_PED_CLEAR_PED_ALTERNATE_WALK_ANIM);
		PED.set_function("SET_PED_ALTERNATE_MOVEMENT_ANIM", LUA_NATIVE_PED_SET_PED_ALTERNATE_MOVEMENT_ANIM);
		PED.set_function("CLEAR_PED_ALTERNATE_MOVEMENT_ANIM", LUA_NATIVE_PED_CLEAR_PED_ALTERNATE_MOVEMENT_ANIM);
		PED.set_function("SET_PED_GESTURE_GROUP", LUA_NATIVE_PED_SET_PED_GESTURE_GROUP);
		PED.set_function("GET_ANIM_INITIAL_OFFSET_POSITION", LUA_NATIVE_PED_GET_ANIM_INITIAL_OFFSET_POSITION);
		PED.set_function("GET_ANIM_INITIAL_OFFSET_ROTATION", LUA_NATIVE_PED_GET_ANIM_INITIAL_OFFSET_ROTATION);
		PED.set_function("GET_PED_DRAWABLE_VARIATION", LUA_NATIVE_PED_GET_PED_DRAWABLE_VARIATION);
		PED.set_function("GET_NUMBER_OF_PED_DRAWABLE_VARIATIONS", LUA_NATIVE_PED_GET_NUMBER_OF_PED_DRAWABLE_VARIATIONS);
		PED.set_function("GET_PED_TEXTURE_VARIATION", LUA_NATIVE_PED_GET_PED_TEXTURE_VARIATION);
		PED.set_function("GET_NUMBER_OF_PED_TEXTURE_VARIATIONS", LUA_NATIVE_PED_GET_NUMBER_OF_PED_TEXTURE_VARIATIONS);
		PED.set_function("GET_NUMBER_OF_PED_PROP_DRAWABLE_VARIATIONS", LUA_NATIVE_PED_GET_NUMBER_OF_PED_PROP_DRAWABLE_VARIATIONS);
		PED.set_function("GET_NUMBER_OF_PED_PROP_TEXTURE_VARIATIONS", LUA_NATIVE_PED_GET_NUMBER_OF_PED_PROP_TEXTURE_VARIATIONS);
		PED.set_function("GET_PED_PALETTE_VARIATION", LUA_NATIVE_PED_GET_PED_PALETTE_VARIATION);
		PED.set_function("GET_MP_OUTFIT_DATA_FROM_METADATA", LUA_NATIVE_PED_GET_MP_OUTFIT_DATA_FROM_METADATA);
		PED.set_function("GET_FM_MALE_SHOP_PED_APPAREL_ITEM_INDEX", LUA_NATIVE_PED_GET_FM_MALE_SHOP_PED_APPAREL_ITEM_INDEX);
		PED.set_function("GET_FM_FEMALE_SHOP_PED_APPAREL_ITEM_INDEX", LUA_NATIVE_PED_GET_FM_FEMALE_SHOP_PED_APPAREL_ITEM_INDEX);
		PED.set_function("IS_PED_COMPONENT_VARIATION_VALID", LUA_NATIVE_PED_IS_PED_COMPONENT_VARIATION_VALID);
		PED.set_function("SET_PED_COMPONENT_VARIATION", LUA_NATIVE_PED_SET_PED_COMPONENT_VARIATION);
		PED.set_function("SET_PED_RANDOM_COMPONENT_VARIATION", LUA_NATIVE_PED_SET_PED_RANDOM_COMPONENT_VARIATION);
		PED.set_function("SET_PED_RANDOM_PROPS", LUA_NATIVE_PED_SET_PED_RANDOM_PROPS);
		PED.set_function("SET_PED_DEFAULT_COMPONENT_VARIATION", LUA_NATIVE_PED_SET_PED_DEFAULT_COMPONENT_VARIATION);
		PED.set_function("SET_PED_BLEND_FROM_PARENTS", LUA_NATIVE_PED_SET_PED_BLEND_FROM_PARENTS);
		PED.set_function("SET_PED_HEAD_BLEND_DATA", LUA_NATIVE_PED_SET_PED_HEAD_BLEND_DATA);
		PED.set_function("GET_PED_HEAD_BLEND_DATA", LUA_NATIVE_PED_GET_PED_HEAD_BLEND_DATA);
		PED.set_function("UPDATE_PED_HEAD_BLEND_DATA", LUA_NATIVE_PED_UPDATE_PED_HEAD_BLEND_DATA);
		PED.set_function("SET_HEAD_BLEND_EYE_COLOR", LUA_NATIVE_PED_SET_HEAD_BLEND_EYE_COLOR);
		PED.set_function("GET_HEAD_BLEND_EYE_COLOR", LUA_NATIVE_PED_GET_HEAD_BLEND_EYE_COLOR);
		PED.set_function("SET_PED_HEAD_OVERLAY", LUA_NATIVE_PED_SET_PED_HEAD_OVERLAY);
		PED.set_function("GET_PED_HEAD_OVERLAY", LUA_NATIVE_PED_GET_PED_HEAD_OVERLAY);
		PED.set_function("GET_PED_HEAD_OVERLAY_NUM", LUA_NATIVE_PED_GET_PED_HEAD_OVERLAY_NUM);
		PED.set_function("SET_PED_HEAD_OVERLAY_TINT", LUA_NATIVE_PED_SET_PED_HEAD_OVERLAY_TINT);
		PED.set_function("SET_PED_HAIR_TINT", LUA_NATIVE_PED_SET_PED_HAIR_TINT);
		PED.set_function("GET_NUM_PED_HAIR_TINTS", LUA_NATIVE_PED_GET_NUM_PED_HAIR_TINTS);
		PED.set_function("GET_NUM_PED_MAKEUP_TINTS", LUA_NATIVE_PED_GET_NUM_PED_MAKEUP_TINTS);
		PED.set_function("GET_PED_HAIR_TINT_COLOR", LUA_NATIVE_PED_GET_PED_HAIR_TINT_COLOR);
		PED.set_function("GET_PED_MAKEUP_TINT_COLOR", LUA_NATIVE_PED_GET_PED_MAKEUP_TINT_COLOR);
		PED.set_function("IS_PED_HAIR_TINT_FOR_CREATOR", LUA_NATIVE_PED_IS_PED_HAIR_TINT_FOR_CREATOR);
		PED.set_function("GET_DEFAULT_SECONDARY_TINT_FOR_CREATOR", LUA_NATIVE_PED_GET_DEFAULT_SECONDARY_TINT_FOR_CREATOR);
		PED.set_function("IS_PED_LIPSTICK_TINT_FOR_CREATOR", LUA_NATIVE_PED_IS_PED_LIPSTICK_TINT_FOR_CREATOR);
		PED.set_function("IS_PED_BLUSH_TINT_FOR_CREATOR", LUA_NATIVE_PED_IS_PED_BLUSH_TINT_FOR_CREATOR);
		PED.set_function("IS_PED_HAIR_TINT_FOR_BARBER", LUA_NATIVE_PED_IS_PED_HAIR_TINT_FOR_BARBER);
		PED.set_function("GET_DEFAULT_SECONDARY_TINT_FOR_BARBER", LUA_NATIVE_PED_GET_DEFAULT_SECONDARY_TINT_FOR_BARBER);
		PED.set_function("IS_PED_LIPSTICK_TINT_FOR_BARBER", LUA_NATIVE_PED_IS_PED_LIPSTICK_TINT_FOR_BARBER);
		PED.set_function("IS_PED_BLUSH_TINT_FOR_BARBER", LUA_NATIVE_PED_IS_PED_BLUSH_TINT_FOR_BARBER);
		PED.set_function("IS_PED_BLUSH_FACEPAINT_TINT_FOR_BARBER", LUA_NATIVE_PED_IS_PED_BLUSH_FACEPAINT_TINT_FOR_BARBER);
		PED.set_function("GET_TINT_INDEX_FOR_LAST_GEN_HAIR_TEXTURE", LUA_NATIVE_PED_GET_TINT_INDEX_FOR_LAST_GEN_HAIR_TEXTURE);
		PED.set_function("SET_PED_MICRO_MORPH", LUA_NATIVE_PED_SET_PED_MICRO_MORPH);
		PED.set_function("HAS_PED_HEAD_BLEND_FINISHED", LUA_NATIVE_PED_HAS_PED_HEAD_BLEND_FINISHED);
		PED.set_function("FINALIZE_HEAD_BLEND", LUA_NATIVE_PED_FINALIZE_HEAD_BLEND);
		PED.set_function("SET_HEAD_BLEND_PALETTE_COLOR", LUA_NATIVE_PED_SET_HEAD_BLEND_PALETTE_COLOR);
		PED.set_function("DISABLE_HEAD_BLEND_PALETTE_COLOR", LUA_NATIVE_PED_DISABLE_HEAD_BLEND_PALETTE_COLOR);
		PED.set_function("GET_PED_HEAD_BLEND_FIRST_INDEX", LUA_NATIVE_PED_GET_PED_HEAD_BLEND_FIRST_INDEX);
		PED.set_function("GET_PED_HEAD_BLEND_NUM_HEADS", LUA_NATIVE_PED_GET_PED_HEAD_BLEND_NUM_HEADS);
		PED.set_function("SET_PED_PRELOAD_VARIATION_DATA", LUA_NATIVE_PED_SET_PED_PRELOAD_VARIATION_DATA);
		PED.set_function("HAS_PED_PRELOAD_VARIATION_DATA_FINISHED", LUA_NATIVE_PED_HAS_PED_PRELOAD_VARIATION_DATA_FINISHED);
		PED.set_function("RELEASE_PED_PRELOAD_VARIATION_DATA", LUA_NATIVE_PED_RELEASE_PED_PRELOAD_VARIATION_DATA);
		PED.set_function("SET_PED_PRELOAD_PROP_DATA", LUA_NATIVE_PED_SET_PED_PRELOAD_PROP_DATA);
		PED.set_function("HAS_PED_PRELOAD_PROP_DATA_FINISHED", LUA_NATIVE_PED_HAS_PED_PRELOAD_PROP_DATA_FINISHED);
		PED.set_function("RELEASE_PED_PRELOAD_PROP_DATA", LUA_NATIVE_PED_RELEASE_PED_PRELOAD_PROP_DATA);
		PED.set_function("GET_PED_PROP_INDEX", LUA_NATIVE_PED_GET_PED_PROP_INDEX);
		PED.set_function("SET_PED_PROP_INDEX", LUA_NATIVE_PED_SET_PED_PROP_INDEX);
		PED.set_function("KNOCK_OFF_PED_PROP", LUA_NATIVE_PED_KNOCK_OFF_PED_PROP);
		PED.set_function("CLEAR_PED_PROP", LUA_NATIVE_PED_CLEAR_PED_PROP);
		PED.set_function("CLEAR_ALL_PED_PROPS", LUA_NATIVE_PED_CLEAR_ALL_PED_PROPS);
		PED.set_function("DROP_AMBIENT_PROP", LUA_NATIVE_PED_DROP_AMBIENT_PROP);
		PED.set_function("GET_PED_PROP_TEXTURE_INDEX", LUA_NATIVE_PED_GET_PED_PROP_TEXTURE_INDEX);
		PED.set_function("CLEAR_PED_PARACHUTE_PACK_VARIATION", LUA_NATIVE_PED_CLEAR_PED_PARACHUTE_PACK_VARIATION);
		PED.set_function("SET_PED_SCUBA_GEAR_VARIATION", LUA_NATIVE_PED_SET_PED_SCUBA_GEAR_VARIATION);
		PED.set_function("CLEAR_PED_SCUBA_GEAR_VARIATION", LUA_NATIVE_PED_CLEAR_PED_SCUBA_GEAR_VARIATION);
		PED.set_function("IS_USING_PED_SCUBA_GEAR_VARIATION", LUA_NATIVE_PED_IS_USING_PED_SCUBA_GEAR_VARIATION);
		PED.set_function("SET_BLOCKING_OF_NON_TEMPORARY_EVENTS", LUA_NATIVE_PED_SET_BLOCKING_OF_NON_TEMPORARY_EVENTS);
		PED.set_function("SET_PED_BOUNDS_ORIENTATION", LUA_NATIVE_PED_SET_PED_BOUNDS_ORIENTATION);
		PED.set_function("REGISTER_TARGET", LUA_NATIVE_PED_REGISTER_TARGET);
		PED.set_function("REGISTER_HATED_TARGETS_AROUND_PED", LUA_NATIVE_PED_REGISTER_HATED_TARGETS_AROUND_PED);
		PED.set_function("GET_RANDOM_PED_AT_COORD", LUA_NATIVE_PED_GET_RANDOM_PED_AT_COORD);
		PED.set_function("GET_CLOSEST_PED", LUA_NATIVE_PED_GET_CLOSEST_PED);
		PED.set_function("SET_SCENARIO_PEDS_TO_BE_RETURNED_BY_NEXT_COMMAND", LUA_NATIVE_PED_SET_SCENARIO_PEDS_TO_BE_RETURNED_BY_NEXT_COMMAND);
		PED.set_function("GET_CAN_PED_BE_GRABBED_BY_SCRIPT", LUA_NATIVE_PED_GET_CAN_PED_BE_GRABBED_BY_SCRIPT);
		PED.set_function("SET_DRIVER_RACING_MODIFIER", LUA_NATIVE_PED_SET_DRIVER_RACING_MODIFIER);
		PED.set_function("SET_DRIVER_ABILITY", LUA_NATIVE_PED_SET_DRIVER_ABILITY);
		PED.set_function("SET_DRIVER_AGGRESSIVENESS", LUA_NATIVE_PED_SET_DRIVER_AGGRESSIVENESS);
		PED.set_function("CAN_PED_RAGDOLL", LUA_NATIVE_PED_CAN_PED_RAGDOLL);
		PED.set_function("SET_PED_TO_RAGDOLL", LUA_NATIVE_PED_SET_PED_TO_RAGDOLL);
		PED.set_function("SET_PED_TO_RAGDOLL_WITH_FALL", LUA_NATIVE_PED_SET_PED_TO_RAGDOLL_WITH_FALL);
		PED.set_function("SET_PED_RAGDOLL_ON_COLLISION", LUA_NATIVE_PED_SET_PED_RAGDOLL_ON_COLLISION);
		PED.set_function("IS_PED_RAGDOLL", LUA_NATIVE_PED_IS_PED_RAGDOLL);
		PED.set_function("IS_PED_RUNNING_RAGDOLL_TASK", LUA_NATIVE_PED_IS_PED_RUNNING_RAGDOLL_TASK);
		PED.set_function("SET_PED_RAGDOLL_FORCE_FALL", LUA_NATIVE_PED_SET_PED_RAGDOLL_FORCE_FALL);
		PED.set_function("RESET_PED_RAGDOLL_TIMER", LUA_NATIVE_PED_RESET_PED_RAGDOLL_TIMER);
		PED.set_function("SET_PED_CAN_RAGDOLL", LUA_NATIVE_PED_SET_PED_CAN_RAGDOLL);
		PED.set_function("IS_PED_RUNNING_MELEE_TASK", LUA_NATIVE_PED_IS_PED_RUNNING_MELEE_TASK);
		PED.set_function("IS_PED_RUNNING_MOBILE_PHONE_TASK", LUA_NATIVE_PED_IS_PED_RUNNING_MOBILE_PHONE_TASK);
		PED.set_function("IS_MOBILE_PHONE_TO_PED_EAR", LUA_NATIVE_PED_IS_MOBILE_PHONE_TO_PED_EAR);
		PED.set_function("SET_RAGDOLL_BLOCKING_FLAGS", LUA_NATIVE_PED_SET_RAGDOLL_BLOCKING_FLAGS);
		PED.set_function("CLEAR_RAGDOLL_BLOCKING_FLAGS", LUA_NATIVE_PED_CLEAR_RAGDOLL_BLOCKING_FLAGS);
		PED.set_function("SET_PED_ANGLED_DEFENSIVE_AREA", LUA_NATIVE_PED_SET_PED_ANGLED_DEFENSIVE_AREA);
		PED.set_function("SET_PED_SPHERE_DEFENSIVE_AREA", LUA_NATIVE_PED_SET_PED_SPHERE_DEFENSIVE_AREA);
		PED.set_function("SET_PED_DEFENSIVE_SPHERE_ATTACHED_TO_PED", LUA_NATIVE_PED_SET_PED_DEFENSIVE_SPHERE_ATTACHED_TO_PED);
		PED.set_function("SET_PED_DEFENSIVE_SPHERE_ATTACHED_TO_VEHICLE", LUA_NATIVE_PED_SET_PED_DEFENSIVE_SPHERE_ATTACHED_TO_VEHICLE);
		PED.set_function("SET_PED_DEFENSIVE_AREA_ATTACHED_TO_PED", LUA_NATIVE_PED_SET_PED_DEFENSIVE_AREA_ATTACHED_TO_PED);
		PED.set_function("SET_PED_DEFENSIVE_AREA_DIRECTION", LUA_NATIVE_PED_SET_PED_DEFENSIVE_AREA_DIRECTION);
		PED.set_function("REMOVE_PED_DEFENSIVE_AREA", LUA_NATIVE_PED_REMOVE_PED_DEFENSIVE_AREA);
		PED.set_function("GET_PED_DEFENSIVE_AREA_POSITION", LUA_NATIVE_PED_GET_PED_DEFENSIVE_AREA_POSITION);
		PED.set_function("IS_PED_DEFENSIVE_AREA_ACTIVE", LUA_NATIVE_PED_IS_PED_DEFENSIVE_AREA_ACTIVE);
		PED.set_function("SET_PED_PREFERRED_COVER_SET", LUA_NATIVE_PED_SET_PED_PREFERRED_COVER_SET);
		PED.set_function("REMOVE_PED_PREFERRED_COVER_SET", LUA_NATIVE_PED_REMOVE_PED_PREFERRED_COVER_SET);
		PED.set_function("REVIVE_INJURED_PED", LUA_NATIVE_PED_REVIVE_INJURED_PED);
		PED.set_function("RESURRECT_PED", LUA_NATIVE_PED_RESURRECT_PED);
		PED.set_function("SET_PED_NAME_DEBUG", LUA_NATIVE_PED_SET_PED_NAME_DEBUG);
		PED.set_function("GET_PED_EXTRACTED_DISPLACEMENT", LUA_NATIVE_PED_GET_PED_EXTRACTED_DISPLACEMENT);
		PED.set_function("SET_PED_DIES_WHEN_INJURED", LUA_NATIVE_PED_SET_PED_DIES_WHEN_INJURED);
		PED.set_function("SET_PED_ENABLE_WEAPON_BLOCKING", LUA_NATIVE_PED_SET_PED_ENABLE_WEAPON_BLOCKING);
		PED.set_function("SPECIAL_FUNCTION_DO_NOT_USE", LUA_NATIVE_PED_SPECIAL_FUNCTION_DO_NOT_USE);
		PED.set_function("RESET_PED_VISIBLE_DAMAGE", LUA_NATIVE_PED_RESET_PED_VISIBLE_DAMAGE);
		PED.set_function("APPLY_PED_BLOOD_DAMAGE_BY_ZONE", LUA_NATIVE_PED_APPLY_PED_BLOOD_DAMAGE_BY_ZONE);
		PED.set_function("APPLY_PED_BLOOD", LUA_NATIVE_PED_APPLY_PED_BLOOD);
		PED.set_function("APPLY_PED_BLOOD_BY_ZONE", LUA_NATIVE_PED_APPLY_PED_BLOOD_BY_ZONE);
		PED.set_function("APPLY_PED_BLOOD_SPECIFIC", LUA_NATIVE_PED_APPLY_PED_BLOOD_SPECIFIC);
		PED.set_function("APPLY_PED_DAMAGE_DECAL", LUA_NATIVE_PED_APPLY_PED_DAMAGE_DECAL);
		PED.set_function("APPLY_PED_DAMAGE_PACK", LUA_NATIVE_PED_APPLY_PED_DAMAGE_PACK);
		PED.set_function("CLEAR_PED_BLOOD_DAMAGE", LUA_NATIVE_PED_CLEAR_PED_BLOOD_DAMAGE);
		PED.set_function("CLEAR_PED_BLOOD_DAMAGE_BY_ZONE", LUA_NATIVE_PED_CLEAR_PED_BLOOD_DAMAGE_BY_ZONE);
		PED.set_function("HIDE_PED_BLOOD_DAMAGE_BY_ZONE", LUA_NATIVE_PED_HIDE_PED_BLOOD_DAMAGE_BY_ZONE);
		PED.set_function("CLEAR_PED_DAMAGE_DECAL_BY_ZONE", LUA_NATIVE_PED_CLEAR_PED_DAMAGE_DECAL_BY_ZONE);
		PED.set_function("GET_PED_DECORATIONS_STATE", LUA_NATIVE_PED_GET_PED_DECORATIONS_STATE);
		PED.set_function("MARK_PED_DECORATIONS_AS_CLONED_FROM_LOCAL_PLAYER", LUA_NATIVE_PED_MARK_PED_DECORATIONS_AS_CLONED_FROM_LOCAL_PLAYER);
		PED.set_function("CLEAR_PED_WETNESS", LUA_NATIVE_PED_CLEAR_PED_WETNESS);
		PED.set_function("SET_PED_WETNESS_HEIGHT", LUA_NATIVE_PED_SET_PED_WETNESS_HEIGHT);
		PED.set_function("SET_PED_WETNESS_ENABLED_THIS_FRAME", LUA_NATIVE_PED_SET_PED_WETNESS_ENABLED_THIS_FRAME);
		PED.set_function("SET_PED_WETNESS", LUA_NATIVE_PED_SET_PED_WETNESS);
		PED.set_function("CLEAR_PED_ENV_DIRT", LUA_NATIVE_PED_CLEAR_PED_ENV_DIRT);
		PED.set_function("SET_PED_SWEAT", LUA_NATIVE_PED_SET_PED_SWEAT);
		PED.set_function("ADD_PED_DECORATION_FROM_HASHES", LUA_NATIVE_PED_ADD_PED_DECORATION_FROM_HASHES);
		PED.set_function("ADD_PED_DECORATION_FROM_HASHES_IN_CORONA", LUA_NATIVE_PED_ADD_PED_DECORATION_FROM_HASHES_IN_CORONA);
		PED.set_function("GET_PED_DECORATION_ZONE_FROM_HASHES", LUA_NATIVE_PED_GET_PED_DECORATION_ZONE_FROM_HASHES);
		PED.set_function("CLEAR_PED_DECORATIONS", LUA_NATIVE_PED_CLEAR_PED_DECORATIONS);
		PED.set_function("CLEAR_PED_DECORATIONS_LEAVE_SCARS", LUA_NATIVE_PED_CLEAR_PED_DECORATIONS_LEAVE_SCARS);
		PED.set_function("WAS_PED_SKELETON_UPDATED", LUA_NATIVE_PED_WAS_PED_SKELETON_UPDATED);
		PED.set_function("GET_PED_BONE_COORDS", LUA_NATIVE_PED_GET_PED_BONE_COORDS);
		PED.set_function("CREATE_NM_MESSAGE", LUA_NATIVE_PED_CREATE_NM_MESSAGE);
		PED.set_function("GIVE_PED_NM_MESSAGE", LUA_NATIVE_PED_GIVE_PED_NM_MESSAGE);
		PED.set_function("ADD_SCENARIO_BLOCKING_AREA", LUA_NATIVE_PED_ADD_SCENARIO_BLOCKING_AREA);
		PED.set_function("REMOVE_SCENARIO_BLOCKING_AREAS", LUA_NATIVE_PED_REMOVE_SCENARIO_BLOCKING_AREAS);
		PED.set_function("REMOVE_SCENARIO_BLOCKING_AREA", LUA_NATIVE_PED_REMOVE_SCENARIO_BLOCKING_AREA);
		PED.set_function("SET_SCENARIO_PEDS_SPAWN_IN_SPHERE_AREA", LUA_NATIVE_PED_SET_SCENARIO_PEDS_SPAWN_IN_SPHERE_AREA);
		PED.set_function("DOES_SCENARIO_BLOCKING_AREA_EXISTS", LUA_NATIVE_PED_DOES_SCENARIO_BLOCKING_AREA_EXISTS);
		PED.set_function("IS_PED_USING_SCENARIO", LUA_NATIVE_PED_IS_PED_USING_SCENARIO);
		PED.set_function("IS_PED_USING_ANY_SCENARIO", LUA_NATIVE_PED_IS_PED_USING_ANY_SCENARIO);
		PED.set_function("SET_PED_PANIC_EXIT_SCENARIO", LUA_NATIVE_PED_SET_PED_PANIC_EXIT_SCENARIO);
		PED.set_function("TOGGLE_SCENARIO_PED_COWER_IN_PLACE", LUA_NATIVE_PED_TOGGLE_SCENARIO_PED_COWER_IN_PLACE);
		PED.set_function("TRIGGER_PED_SCENARIO_PANICEXITTOFLEE", LUA_NATIVE_PED_TRIGGER_PED_SCENARIO_PANICEXITTOFLEE);
		PED.set_function("SET_PED_SHOULD_PLAY_DIRECTED_NORMAL_SCENARIO_EXIT", LUA_NATIVE_PED_SET_PED_SHOULD_PLAY_DIRECTED_NORMAL_SCENARIO_EXIT);
		PED.set_function("SET_PED_SHOULD_PLAY_NORMAL_SCENARIO_EXIT", LUA_NATIVE_PED_SET_PED_SHOULD_PLAY_NORMAL_SCENARIO_EXIT);
		PED.set_function("SET_PED_SHOULD_PLAY_IMMEDIATE_SCENARIO_EXIT", LUA_NATIVE_PED_SET_PED_SHOULD_PLAY_IMMEDIATE_SCENARIO_EXIT);
		PED.set_function("SET_PED_SHOULD_PLAY_FLEE_SCENARIO_EXIT", LUA_NATIVE_PED_SET_PED_SHOULD_PLAY_FLEE_SCENARIO_EXIT);
		PED.set_function("SET_PED_SHOULD_IGNORE_SCENARIO_EXIT_COLLISION_CHECKS", LUA_NATIVE_PED_SET_PED_SHOULD_IGNORE_SCENARIO_EXIT_COLLISION_CHECKS);
		PED.set_function("SET_PED_SHOULD_IGNORE_SCENARIO_NAV_CHECKS", LUA_NATIVE_PED_SET_PED_SHOULD_IGNORE_SCENARIO_NAV_CHECKS);
		PED.set_function("SET_PED_SHOULD_PROBE_FOR_SCENARIO_EXITS_IN_ONE_FRAME", LUA_NATIVE_PED_SET_PED_SHOULD_PROBE_FOR_SCENARIO_EXITS_IN_ONE_FRAME);
		PED.set_function("IS_PED_GESTURING", LUA_NATIVE_PED_IS_PED_GESTURING);
		PED.set_function("RESET_FACIAL_IDLE_ANIM", LUA_NATIVE_PED_RESET_FACIAL_IDLE_ANIM);
		PED.set_function("PLAY_FACIAL_ANIM", LUA_NATIVE_PED_PLAY_FACIAL_ANIM);
		PED.set_function("SET_FACIAL_CLIPSET", LUA_NATIVE_PED_SET_FACIAL_CLIPSET);
		PED.set_function("SET_FACIAL_IDLE_ANIM_OVERRIDE", LUA_NATIVE_PED_SET_FACIAL_IDLE_ANIM_OVERRIDE);
		PED.set_function("CLEAR_FACIAL_IDLE_ANIM_OVERRIDE", LUA_NATIVE_PED_CLEAR_FACIAL_IDLE_ANIM_OVERRIDE);
		PED.set_function("SET_PED_CAN_PLAY_GESTURE_ANIMS", LUA_NATIVE_PED_SET_PED_CAN_PLAY_GESTURE_ANIMS);
		PED.set_function("SET_PED_CAN_PLAY_VISEME_ANIMS", LUA_NATIVE_PED_SET_PED_CAN_PLAY_VISEME_ANIMS);
		PED.set_function("SET_PED_IS_IGNORED_BY_AUTO_OPEN_DOORS", LUA_NATIVE_PED_SET_PED_IS_IGNORED_BY_AUTO_OPEN_DOORS);
		PED.set_function("SET_PED_CAN_PLAY_AMBIENT_ANIMS", LUA_NATIVE_PED_SET_PED_CAN_PLAY_AMBIENT_ANIMS);
		PED.set_function("SET_PED_CAN_PLAY_AMBIENT_BASE_ANIMS", LUA_NATIVE_PED_SET_PED_CAN_PLAY_AMBIENT_BASE_ANIMS);
		PED.set_function("TRIGGER_IDLE_ANIMATION_ON_PED", LUA_NATIVE_PED_TRIGGER_IDLE_ANIMATION_ON_PED);
		PED.set_function("SET_PED_CAN_ARM_IK", LUA_NATIVE_PED_SET_PED_CAN_ARM_IK);
		PED.set_function("SET_PED_CAN_HEAD_IK", LUA_NATIVE_PED_SET_PED_CAN_HEAD_IK);
		PED.set_function("SET_PED_CAN_LEG_IK", LUA_NATIVE_PED_SET_PED_CAN_LEG_IK);
		PED.set_function("SET_PED_CAN_TORSO_IK", LUA_NATIVE_PED_SET_PED_CAN_TORSO_IK);
		PED.set_function("SET_PED_CAN_TORSO_REACT_IK", LUA_NATIVE_PED_SET_PED_CAN_TORSO_REACT_IK);
		PED.set_function("SET_PED_CAN_TORSO_VEHICLE_IK", LUA_NATIVE_PED_SET_PED_CAN_TORSO_VEHICLE_IK);
		PED.set_function("SET_PED_CAN_USE_AUTO_CONVERSATION_LOOKAT", LUA_NATIVE_PED_SET_PED_CAN_USE_AUTO_CONVERSATION_LOOKAT);
		PED.set_function("IS_PED_HEADTRACKING_PED", LUA_NATIVE_PED_IS_PED_HEADTRACKING_PED);
		PED.set_function("IS_PED_HEADTRACKING_ENTITY", LUA_NATIVE_PED_IS_PED_HEADTRACKING_ENTITY);
		PED.set_function("SET_PED_PRIMARY_LOOKAT", LUA_NATIVE_PED_SET_PED_PRIMARY_LOOKAT);
		PED.set_function("SET_PED_CLOTH_PIN_FRAMES", LUA_NATIVE_PED_SET_PED_CLOTH_PIN_FRAMES);
		PED.set_function("SET_PED_CLOTH_PACKAGE_INDEX", LUA_NATIVE_PED_SET_PED_CLOTH_PACKAGE_INDEX);
		PED.set_function("SET_PED_CLOTH_PRONE", LUA_NATIVE_PED_SET_PED_CLOTH_PRONE);
		PED.set_function("SET_PED_CONFIG_FLAG", LUA_NATIVE_PED_SET_PED_CONFIG_FLAG);
		PED.set_function("SET_PED_RESET_FLAG", LUA_NATIVE_PED_SET_PED_RESET_FLAG);
		PED.set_function("GET_PED_CONFIG_FLAG", LUA_NATIVE_PED_GET_PED_CONFIG_FLAG);
		PED.set_function("GET_PED_RESET_FLAG", LUA_NATIVE_PED_GET_PED_RESET_FLAG);
		PED.set_function("SET_PED_GROUP_MEMBER_PASSENGER_INDEX", LUA_NATIVE_PED_SET_PED_GROUP_MEMBER_PASSENGER_INDEX);
		PED.set_function("SET_PED_CAN_EVASIVE_DIVE", LUA_NATIVE_PED_SET_PED_CAN_EVASIVE_DIVE);
		PED.set_function("IS_PED_EVASIVE_DIVING", LUA_NATIVE_PED_IS_PED_EVASIVE_DIVING);
		PED.set_function("SET_PED_SHOOTS_AT_COORD", LUA_NATIVE_PED_SET_PED_SHOOTS_AT_COORD);
		PED.set_function("SET_PED_MODEL_IS_SUPPRESSED", LUA_NATIVE_PED_SET_PED_MODEL_IS_SUPPRESSED);
		PED.set_function("STOP_ANY_PED_MODEL_BEING_SUPPRESSED", LUA_NATIVE_PED_STOP_ANY_PED_MODEL_BEING_SUPPRESSED);
		PED.set_function("SET_PED_CAN_BE_TARGETED_WHEN_INJURED", LUA_NATIVE_PED_SET_PED_CAN_BE_TARGETED_WHEN_INJURED);
		PED.set_function("SET_PED_GENERATES_DEAD_BODY_EVENTS", LUA_NATIVE_PED_SET_PED_GENERATES_DEAD_BODY_EVENTS);
		PED.set_function("BLOCK_PED_FROM_GENERATING_DEAD_BODY_EVENTS_WHEN_DEAD", LUA_NATIVE_PED_BLOCK_PED_FROM_GENERATING_DEAD_BODY_EVENTS_WHEN_DEAD);
		PED.set_function("SET_PED_WILL_ONLY_ATTACK_WANTED_PLAYER", LUA_NATIVE_PED_SET_PED_WILL_ONLY_ATTACK_WANTED_PLAYER);
		PED.set_function("SET_PED_CAN_RAGDOLL_FROM_PLAYER_IMPACT", LUA_NATIVE_PED_SET_PED_CAN_RAGDOLL_FROM_PLAYER_IMPACT);
		PED.set_function("GIVE_PED_HELMET", LUA_NATIVE_PED_GIVE_PED_HELMET);
		PED.set_function("REMOVE_PED_HELMET", LUA_NATIVE_PED_REMOVE_PED_HELMET);
		PED.set_function("IS_PED_TAKING_OFF_HELMET", LUA_NATIVE_PED_IS_PED_TAKING_OFF_HELMET);
		PED.set_function("SET_PED_HELMET", LUA_NATIVE_PED_SET_PED_HELMET);
		PED.set_function("SET_PED_HELMET_FLAG", LUA_NATIVE_PED_SET_PED_HELMET_FLAG);
		PED.set_function("SET_PED_HELMET_PROP_INDEX", LUA_NATIVE_PED_SET_PED_HELMET_PROP_INDEX);
		PED.set_function("SET_PED_HELMET_VISOR_PROP_INDICES", LUA_NATIVE_PED_SET_PED_HELMET_VISOR_PROP_INDICES);
		PED.set_function("IS_PED_HELMET_VISOR_UP", LUA_NATIVE_PED_IS_PED_HELMET_VISOR_UP);
		PED.set_function("SET_PED_HELMET_TEXTURE_INDEX", LUA_NATIVE_PED_SET_PED_HELMET_TEXTURE_INDEX);
		PED.set_function("IS_PED_WEARING_HELMET", LUA_NATIVE_PED_IS_PED_WEARING_HELMET);
		PED.set_function("CLEAR_PED_STORED_HAT_PROP", LUA_NATIVE_PED_CLEAR_PED_STORED_HAT_PROP);
		PED.set_function("GET_PED_HELMET_STORED_HAT_PROP_INDEX", LUA_NATIVE_PED_GET_PED_HELMET_STORED_HAT_PROP_INDEX);
		PED.set_function("GET_PED_HELMET_STORED_HAT_TEX_INDEX", LUA_NATIVE_PED_GET_PED_HELMET_STORED_HAT_TEX_INDEX);
		PED.set_function("IS_CURRENT_HEAD_PROP_A_HELMET", LUA_NATIVE_PED_IS_CURRENT_HEAD_PROP_A_HELMET);
		PED.set_function("SET_PED_TO_LOAD_COVER", LUA_NATIVE_PED_SET_PED_TO_LOAD_COVER);
		PED.set_function("SET_PED_CAN_COWER_IN_COVER", LUA_NATIVE_PED_SET_PED_CAN_COWER_IN_COVER);
		PED.set_function("SET_PED_CAN_PEEK_IN_COVER", LUA_NATIVE_PED_SET_PED_CAN_PEEK_IN_COVER);
		PED.set_function("SET_PED_PLAYS_HEAD_ON_HORN_ANIM_WHEN_DIES_IN_VEHICLE", LUA_NATIVE_PED_SET_PED_PLAYS_HEAD_ON_HORN_ANIM_WHEN_DIES_IN_VEHICLE);
		PED.set_function("SET_PED_LEG_IK_MODE", LUA_NATIVE_PED_SET_PED_LEG_IK_MODE);
		PED.set_function("SET_PED_MOTION_BLUR", LUA_NATIVE_PED_SET_PED_MOTION_BLUR);
		PED.set_function("SET_PED_CAN_SWITCH_WEAPON", LUA_NATIVE_PED_SET_PED_CAN_SWITCH_WEAPON);
		PED.set_function("SET_PED_DIES_INSTANTLY_IN_WATER", LUA_NATIVE_PED_SET_PED_DIES_INSTANTLY_IN_WATER);
		PED.set_function("SET_LADDER_CLIMB_INPUT_STATE", LUA_NATIVE_PED_SET_LADDER_CLIMB_INPUT_STATE);
		PED.set_function("STOP_PED_WEAPON_FIRING_WHEN_DROPPED", LUA_NATIVE_PED_STOP_PED_WEAPON_FIRING_WHEN_DROPPED);
		PED.set_function("SET_SCRIPTED_ANIM_SEAT_OFFSET", LUA_NATIVE_PED_SET_SCRIPTED_ANIM_SEAT_OFFSET);
		PED.set_function("SET_PED_COMBAT_MOVEMENT", LUA_NATIVE_PED_SET_PED_COMBAT_MOVEMENT);
		PED.set_function("GET_PED_COMBAT_MOVEMENT", LUA_NATIVE_PED_GET_PED_COMBAT_MOVEMENT);
		PED.set_function("SET_PED_COMBAT_ABILITY", LUA_NATIVE_PED_SET_PED_COMBAT_ABILITY);
		PED.set_function("SET_PED_COMBAT_RANGE", LUA_NATIVE_PED_SET_PED_COMBAT_RANGE);
		PED.set_function("GET_PED_COMBAT_RANGE", LUA_NATIVE_PED_GET_PED_COMBAT_RANGE);
		PED.set_function("SET_PED_COMBAT_ATTRIBUTES", LUA_NATIVE_PED_SET_PED_COMBAT_ATTRIBUTES);
		PED.set_function("SET_PED_TARGET_LOSS_RESPONSE", LUA_NATIVE_PED_SET_PED_TARGET_LOSS_RESPONSE);
		PED.set_function("IS_PED_PERFORMING_MELEE_ACTION", LUA_NATIVE_PED_IS_PED_PERFORMING_MELEE_ACTION);
		PED.set_function("IS_PED_PERFORMING_STEALTH_KILL", LUA_NATIVE_PED_IS_PED_PERFORMING_STEALTH_KILL);
		PED.set_function("IS_PED_PERFORMING_A_COUNTER_ATTACK", LUA_NATIVE_PED_IS_PED_PERFORMING_A_COUNTER_ATTACK);
		PED.set_function("IS_PED_BEING_STEALTH_KILLED", LUA_NATIVE_PED_IS_PED_BEING_STEALTH_KILLED);
		PED.set_function("GET_MELEE_TARGET_FOR_PED", LUA_NATIVE_PED_GET_MELEE_TARGET_FOR_PED);
		PED.set_function("WAS_PED_KILLED_BY_STEALTH", LUA_NATIVE_PED_WAS_PED_KILLED_BY_STEALTH);
		PED.set_function("WAS_PED_KILLED_BY_TAKEDOWN", LUA_NATIVE_PED_WAS_PED_KILLED_BY_TAKEDOWN);
		PED.set_function("WAS_PED_KNOCKED_OUT", LUA_NATIVE_PED_WAS_PED_KNOCKED_OUT);
		PED.set_function("SET_PED_FLEE_ATTRIBUTES", LUA_NATIVE_PED_SET_PED_FLEE_ATTRIBUTES);
		PED.set_function("SET_PED_COWER_HASH", LUA_NATIVE_PED_SET_PED_COWER_HASH);
		PED.set_function("SET_PED_STEERS_AROUND_DEAD_BODIES", LUA_NATIVE_PED_SET_PED_STEERS_AROUND_DEAD_BODIES);
		PED.set_function("SET_PED_STEERS_AROUND_PEDS", LUA_NATIVE_PED_SET_PED_STEERS_AROUND_PEDS);
		PED.set_function("SET_PED_STEERS_AROUND_OBJECTS", LUA_NATIVE_PED_SET_PED_STEERS_AROUND_OBJECTS);
		PED.set_function("SET_PED_STEERS_AROUND_VEHICLES", LUA_NATIVE_PED_SET_PED_STEERS_AROUND_VEHICLES);
		PED.set_function("SET_PED_IS_AVOIDED_BY_OTHERS", LUA_NATIVE_PED_SET_PED_IS_AVOIDED_BY_OTHERS);
		PED.set_function("SET_PED_INCREASED_AVOIDANCE_RADIUS", LUA_NATIVE_PED_SET_PED_INCREASED_AVOIDANCE_RADIUS);
		PED.set_function("SET_PED_BLOCKS_PATHING_WHEN_DEAD", LUA_NATIVE_PED_SET_PED_BLOCKS_PATHING_WHEN_DEAD);
		PED.set_function("SET_PED_NO_TIME_DELAY_BEFORE_SHOT", LUA_NATIVE_PED_SET_PED_NO_TIME_DELAY_BEFORE_SHOT);
		PED.set_function("IS_ANY_PED_NEAR_POINT", LUA_NATIVE_PED_IS_ANY_PED_NEAR_POINT);
		PED.set_function("FORCE_PED_AI_AND_ANIMATION_UPDATE", LUA_NATIVE_PED_FORCE_PED_AI_AND_ANIMATION_UPDATE);
		PED.set_function("IS_PED_HEADING_TOWARDS_POSITION", LUA_NATIVE_PED_IS_PED_HEADING_TOWARDS_POSITION);
		PED.set_function("REQUEST_PED_VISIBILITY_TRACKING", LUA_NATIVE_PED_REQUEST_PED_VISIBILITY_TRACKING);
		PED.set_function("REQUEST_PED_VEHICLE_VISIBILITY_TRACKING", LUA_NATIVE_PED_REQUEST_PED_VEHICLE_VISIBILITY_TRACKING);
		PED.set_function("REQUEST_PED_RESTRICTED_VEHICLE_VISIBILITY_TRACKING", LUA_NATIVE_PED_REQUEST_PED_RESTRICTED_VEHICLE_VISIBILITY_TRACKING);
		PED.set_function("REQUEST_PED_USE_SMALL_BBOX_VISIBILITY_TRACKING", LUA_NATIVE_PED_REQUEST_PED_USE_SMALL_BBOX_VISIBILITY_TRACKING);
		PED.set_function("IS_TRACKED_PED_VISIBLE", LUA_NATIVE_PED_IS_TRACKED_PED_VISIBLE);
		PED.set_function("GET_TRACKED_PED_PIXELCOUNT", LUA_NATIVE_PED_GET_TRACKED_PED_PIXELCOUNT);
		PED.set_function("IS_PED_TRACKED", LUA_NATIVE_PED_IS_PED_TRACKED);
		PED.set_function("HAS_PED_RECEIVED_EVENT", LUA_NATIVE_PED_HAS_PED_RECEIVED_EVENT);
		PED.set_function("CAN_PED_SEE_HATED_PED", LUA_NATIVE_PED_CAN_PED_SEE_HATED_PED);
		PED.set_function("CAN_PED_SHUFFLE_TO_OR_FROM_TURRET_SEAT", LUA_NATIVE_PED_CAN_PED_SHUFFLE_TO_OR_FROM_TURRET_SEAT);
		PED.set_function("CAN_PED_SHUFFLE_TO_OR_FROM_EXTRA_SEAT", LUA_NATIVE_PED_CAN_PED_SHUFFLE_TO_OR_FROM_EXTRA_SEAT);
		PED.set_function("GET_PED_BONE_INDEX", LUA_NATIVE_PED_GET_PED_BONE_INDEX);
		PED.set_function("GET_PED_RAGDOLL_BONE_INDEX", LUA_NATIVE_PED_GET_PED_RAGDOLL_BONE_INDEX);
		PED.set_function("SET_PED_ENVEFF_SCALE", LUA_NATIVE_PED_SET_PED_ENVEFF_SCALE);
		PED.set_function("GET_PED_ENVEFF_SCALE", LUA_NATIVE_PED_GET_PED_ENVEFF_SCALE);
		PED.set_function("SET_ENABLE_PED_ENVEFF_SCALE", LUA_NATIVE_PED_SET_ENABLE_PED_ENVEFF_SCALE);
		PED.set_function("SET_PED_ENVEFF_CPV_ADD", LUA_NATIVE_PED_SET_PED_ENVEFF_CPV_ADD);
		PED.set_function("SET_PED_ENVEFF_COLOR_MODULATOR", LUA_NATIVE_PED_SET_PED_ENVEFF_COLOR_MODULATOR);
		PED.set_function("SET_PED_EMISSIVE_SCALE", LUA_NATIVE_PED_SET_PED_EMISSIVE_SCALE);
		PED.set_function("GET_PED_EMISSIVE_SCALE", LUA_NATIVE_PED_GET_PED_EMISSIVE_SCALE);
		PED.set_function("IS_PED_SHADER_READY", LUA_NATIVE_PED_IS_PED_SHADER_READY);
		PED.set_function("SET_PED_ENABLE_CREW_EMBLEM", LUA_NATIVE_PED_SET_PED_ENABLE_CREW_EMBLEM);
		PED.set_function("REQUEST_RAGDOLL_BOUNDS_UPDATE", LUA_NATIVE_PED_REQUEST_RAGDOLL_BOUNDS_UPDATE);
		PED.set_function("SET_PED_AO_BLOB_RENDERING", LUA_NATIVE_PED_SET_PED_AO_BLOB_RENDERING);
		PED.set_function("IS_PED_SHELTERED", LUA_NATIVE_PED_IS_PED_SHELTERED);
		PED.set_function("CREATE_SYNCHRONIZED_SCENE", LUA_NATIVE_PED_CREATE_SYNCHRONIZED_SCENE);
		PED.set_function("CREATE_SYNCHRONIZED_SCENE_AT_MAP_OBJECT", LUA_NATIVE_PED_CREATE_SYNCHRONIZED_SCENE_AT_MAP_OBJECT);
		PED.set_function("IS_SYNCHRONIZED_SCENE_RUNNING", LUA_NATIVE_PED_IS_SYNCHRONIZED_SCENE_RUNNING);
		PED.set_function("SET_SYNCHRONIZED_SCENE_ORIGIN", LUA_NATIVE_PED_SET_SYNCHRONIZED_SCENE_ORIGIN);
		PED.set_function("SET_SYNCHRONIZED_SCENE_PHASE", LUA_NATIVE_PED_SET_SYNCHRONIZED_SCENE_PHASE);
		PED.set_function("GET_SYNCHRONIZED_SCENE_PHASE", LUA_NATIVE_PED_GET_SYNCHRONIZED_SCENE_PHASE);
		PED.set_function("SET_SYNCHRONIZED_SCENE_RATE", LUA_NATIVE_PED_SET_SYNCHRONIZED_SCENE_RATE);
		PED.set_function("GET_SYNCHRONIZED_SCENE_RATE", LUA_NATIVE_PED_GET_SYNCHRONIZED_SCENE_RATE);
		PED.set_function("SET_SYNCHRONIZED_SCENE_LOOPED", LUA_NATIVE_PED_SET_SYNCHRONIZED_SCENE_LOOPED);
		PED.set_function("IS_SYNCHRONIZED_SCENE_LOOPED", LUA_NATIVE_PED_IS_SYNCHRONIZED_SCENE_LOOPED);
		PED.set_function("SET_SYNCHRONIZED_SCENE_HOLD_LAST_FRAME", LUA_NATIVE_PED_SET_SYNCHRONIZED_SCENE_HOLD_LAST_FRAME);
		PED.set_function("IS_SYNCHRONIZED_SCENE_HOLD_LAST_FRAME", LUA_NATIVE_PED_IS_SYNCHRONIZED_SCENE_HOLD_LAST_FRAME);
		PED.set_function("ATTACH_SYNCHRONIZED_SCENE_TO_ENTITY", LUA_NATIVE_PED_ATTACH_SYNCHRONIZED_SCENE_TO_ENTITY);
		PED.set_function("DETACH_SYNCHRONIZED_SCENE", LUA_NATIVE_PED_DETACH_SYNCHRONIZED_SCENE);
		PED.set_function("TAKE_OWNERSHIP_OF_SYNCHRONIZED_SCENE", LUA_NATIVE_PED_TAKE_OWNERSHIP_OF_SYNCHRONIZED_SCENE);
		PED.set_function("FORCE_PED_MOTION_STATE", LUA_NATIVE_PED_FORCE_PED_MOTION_STATE);
		PED.set_function("GET_PED_CURRENT_MOVE_BLEND_RATIO", LUA_NATIVE_PED_GET_PED_CURRENT_MOVE_BLEND_RATIO);
		PED.set_function("SET_PED_MAX_MOVE_BLEND_RATIO", LUA_NATIVE_PED_SET_PED_MAX_MOVE_BLEND_RATIO);
		PED.set_function("SET_PED_MIN_MOVE_BLEND_RATIO", LUA_NATIVE_PED_SET_PED_MIN_MOVE_BLEND_RATIO);
		PED.set_function("SET_PED_MOVE_RATE_OVERRIDE", LUA_NATIVE_PED_SET_PED_MOVE_RATE_OVERRIDE);
		PED.set_function("SET_PED_MOVE_RATE_IN_WATER_OVERRIDE", LUA_NATIVE_PED_SET_PED_MOVE_RATE_IN_WATER_OVERRIDE);
		PED.set_function("PED_HAS_SEXINESS_FLAG_SET", LUA_NATIVE_PED_PED_HAS_SEXINESS_FLAG_SET);
		PED.set_function("GET_PED_NEARBY_VEHICLES", LUA_NATIVE_PED_GET_PED_NEARBY_VEHICLES);
		PED.set_function("GET_PED_NEARBY_PEDS", LUA_NATIVE_PED_GET_PED_NEARBY_PEDS);
		PED.set_function("HAVE_ALL_STREAMING_REQUESTS_COMPLETED", LUA_NATIVE_PED_HAVE_ALL_STREAMING_REQUESTS_COMPLETED);
		PED.set_function("IS_PED_USING_ACTION_MODE", LUA_NATIVE_PED_IS_PED_USING_ACTION_MODE);
		PED.set_function("SET_PED_USING_ACTION_MODE", LUA_NATIVE_PED_SET_PED_USING_ACTION_MODE);
		PED.set_function("SET_MOVEMENT_MODE_OVERRIDE", LUA_NATIVE_PED_SET_MOVEMENT_MODE_OVERRIDE);
		PED.set_function("SET_PED_CAPSULE", LUA_NATIVE_PED_SET_PED_CAPSULE);
		PED.set_function("REGISTER_PEDHEADSHOT", LUA_NATIVE_PED_REGISTER_PEDHEADSHOT);
		PED.set_function("REGISTER_PEDHEADSHOT_HIRES", LUA_NATIVE_PED_REGISTER_PEDHEADSHOT_HIRES);
		PED.set_function("REGISTER_PEDHEADSHOT_TRANSPARENT", LUA_NATIVE_PED_REGISTER_PEDHEADSHOT_TRANSPARENT);
		PED.set_function("UNREGISTER_PEDHEADSHOT", LUA_NATIVE_PED_UNREGISTER_PEDHEADSHOT);
		PED.set_function("IS_PEDHEADSHOT_VALID", LUA_NATIVE_PED_IS_PEDHEADSHOT_VALID);
		PED.set_function("IS_PEDHEADSHOT_READY", LUA_NATIVE_PED_IS_PEDHEADSHOT_READY);
		PED.set_function("GET_PEDHEADSHOT_TXD_STRING", LUA_NATIVE_PED_GET_PEDHEADSHOT_TXD_STRING);
		PED.set_function("REQUEST_PEDHEADSHOT_IMG_UPLOAD", LUA_NATIVE_PED_REQUEST_PEDHEADSHOT_IMG_UPLOAD);
		PED.set_function("RELEASE_PEDHEADSHOT_IMG_UPLOAD", LUA_NATIVE_PED_RELEASE_PEDHEADSHOT_IMG_UPLOAD);
		PED.set_function("IS_PEDHEADSHOT_IMG_UPLOAD_AVAILABLE", LUA_NATIVE_PED_IS_PEDHEADSHOT_IMG_UPLOAD_AVAILABLE);
		PED.set_function("HAS_PEDHEADSHOT_IMG_UPLOAD_FAILED", LUA_NATIVE_PED_HAS_PEDHEADSHOT_IMG_UPLOAD_FAILED);
		PED.set_function("HAS_PEDHEADSHOT_IMG_UPLOAD_SUCCEEDED", LUA_NATIVE_PED_HAS_PEDHEADSHOT_IMG_UPLOAD_SUCCEEDED);
		PED.set_function("SET_PED_HEATSCALE_OVERRIDE", LUA_NATIVE_PED_SET_PED_HEATSCALE_OVERRIDE);
		PED.set_function("DISABLE_PED_HEATSCALE_OVERRIDE", LUA_NATIVE_PED_DISABLE_PED_HEATSCALE_OVERRIDE);
		PED.set_function("SPAWNPOINTS_START_SEARCH", LUA_NATIVE_PED_SPAWNPOINTS_START_SEARCH);
		PED.set_function("SPAWNPOINTS_START_SEARCH_IN_ANGLED_AREA", LUA_NATIVE_PED_SPAWNPOINTS_START_SEARCH_IN_ANGLED_AREA);
		PED.set_function("SPAWNPOINTS_CANCEL_SEARCH", LUA_NATIVE_PED_SPAWNPOINTS_CANCEL_SEARCH);
		PED.set_function("SPAWNPOINTS_IS_SEARCH_ACTIVE", LUA_NATIVE_PED_SPAWNPOINTS_IS_SEARCH_ACTIVE);
		PED.set_function("SPAWNPOINTS_IS_SEARCH_COMPLETE", LUA_NATIVE_PED_SPAWNPOINTS_IS_SEARCH_COMPLETE);
		PED.set_function("SPAWNPOINTS_IS_SEARCH_FAILED", LUA_NATIVE_PED_SPAWNPOINTS_IS_SEARCH_FAILED);
		PED.set_function("SPAWNPOINTS_GET_NUM_SEARCH_RESULTS", LUA_NATIVE_PED_SPAWNPOINTS_GET_NUM_SEARCH_RESULTS);
		PED.set_function("SPAWNPOINTS_GET_SEARCH_RESULT", LUA_NATIVE_PED_SPAWNPOINTS_GET_SEARCH_RESULT);
		PED.set_function("SPAWNPOINTS_GET_SEARCH_RESULT_FLAGS", LUA_NATIVE_PED_SPAWNPOINTS_GET_SEARCH_RESULT_FLAGS);
		PED.set_function("SET_IK_TARGET", LUA_NATIVE_PED_SET_IK_TARGET);
		PED.set_function("FORCE_INSTANT_LEG_IK_SETUP", LUA_NATIVE_PED_FORCE_INSTANT_LEG_IK_SETUP);
		PED.set_function("REQUEST_ACTION_MODE_ASSET", LUA_NATIVE_PED_REQUEST_ACTION_MODE_ASSET);
		PED.set_function("HAS_ACTION_MODE_ASSET_LOADED", LUA_NATIVE_PED_HAS_ACTION_MODE_ASSET_LOADED);
		PED.set_function("REMOVE_ACTION_MODE_ASSET", LUA_NATIVE_PED_REMOVE_ACTION_MODE_ASSET);
		PED.set_function("REQUEST_STEALTH_MODE_ASSET", LUA_NATIVE_PED_REQUEST_STEALTH_MODE_ASSET);
		PED.set_function("HAS_STEALTH_MODE_ASSET_LOADED", LUA_NATIVE_PED_HAS_STEALTH_MODE_ASSET_LOADED);
		PED.set_function("REMOVE_STEALTH_MODE_ASSET", LUA_NATIVE_PED_REMOVE_STEALTH_MODE_ASSET);
		PED.set_function("SET_PED_LOD_MULTIPLIER", LUA_NATIVE_PED_SET_PED_LOD_MULTIPLIER);
		PED.set_function("SET_PED_CAN_LOSE_PROPS_ON_DAMAGE", LUA_NATIVE_PED_SET_PED_CAN_LOSE_PROPS_ON_DAMAGE);
		PED.set_function("SET_FORCE_FOOTSTEP_UPDATE", LUA_NATIVE_PED_SET_FORCE_FOOTSTEP_UPDATE);
		PED.set_function("SET_FORCE_STEP_TYPE", LUA_NATIVE_PED_SET_FORCE_STEP_TYPE);
		PED.set_function("IS_ANY_HOSTILE_PED_NEAR_POINT", LUA_NATIVE_PED_IS_ANY_HOSTILE_PED_NEAR_POINT);
		PED.set_function("SET_PED_CAN_PLAY_IN_CAR_IDLES", LUA_NATIVE_PED_SET_PED_CAN_PLAY_IN_CAR_IDLES);
		PED.set_function("IS_TARGET_PED_IN_PERCEPTION_AREA", LUA_NATIVE_PED_IS_TARGET_PED_IN_PERCEPTION_AREA);
		PED.set_function("SET_POP_CONTROL_SPHERE_THIS_FRAME", LUA_NATIVE_PED_SET_POP_CONTROL_SPHERE_THIS_FRAME);
		PED.set_function("FORCE_ZERO_MASS_IN_COLLISIONS", LUA_NATIVE_PED_FORCE_ZERO_MASS_IN_COLLISIONS);
		PED.set_function("SET_DISABLE_HIGH_FALL_DEATH", LUA_NATIVE_PED_SET_DISABLE_HIGH_FALL_DEATH);
		PED.set_function("SET_PED_PHONE_PALETTE_IDX", LUA_NATIVE_PED_SET_PED_PHONE_PALETTE_IDX);
		PED.set_function("SET_PED_STEER_BIAS", LUA_NATIVE_PED_SET_PED_STEER_BIAS);
		PED.set_function("IS_PED_SWITCHING_WEAPON", LUA_NATIVE_PED_IS_PED_SWITCHING_WEAPON);
		PED.set_function("SET_PED_TREATED_AS_FRIENDLY", LUA_NATIVE_PED_SET_PED_TREATED_AS_FRIENDLY);
		PED.set_function("SET_DISABLE_PED_MAP_COLLISION", LUA_NATIVE_PED_SET_DISABLE_PED_MAP_COLLISION);
		PED.set_function("ENABLE_MP_LIGHT", LUA_NATIVE_PED_ENABLE_MP_LIGHT);
		PED.set_function("GET_MP_LIGHT_ENABLED", LUA_NATIVE_PED_GET_MP_LIGHT_ENABLED);
		PED.set_function("CLEAR_COVER_POINT_FOR_PED", LUA_NATIVE_PED_CLEAR_COVER_POINT_FOR_PED);
		PED.set_function("SET_ALLOW_STUNT_JUMP_CAMERA", LUA_NATIVE_PED_SET_ALLOW_STUNT_JUMP_CAMERA);
	}
}
