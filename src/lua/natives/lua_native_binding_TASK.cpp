#include "lua_native_binding.hpp"
#include "natives.hpp"

namespace lua::native
{
	static void LUA_NATIVE_TASK_TASK_PAUSE(Ped ped, int ms)
	{
		TASK::TASK_PAUSE(ped, ms);
	}

	static void LUA_NATIVE_TASK_TASK_STAND_STILL(Ped ped, int time)
	{
		TASK::TASK_STAND_STILL(ped, time);
	}

	static void LUA_NATIVE_TASK_TASK_JUMP(Ped ped, bool usePlayerLaunchForce, bool doSuperJump, bool useFullSuperJumpForce)
	{
		TASK::TASK_JUMP(ped, usePlayerLaunchForce, doSuperJump, useFullSuperJumpForce);
	}

	static void LUA_NATIVE_TASK_TASK_COWER(Ped ped, int duration)
	{
		TASK::TASK_COWER(ped, duration);
	}

	static void LUA_NATIVE_TASK_TASK_HANDS_UP(Ped ped, int duration, Ped facingPed, int timeToFacePed, int flags)
	{
		TASK::TASK_HANDS_UP(ped, duration, facingPed, timeToFacePed, flags);
	}

	static void LUA_NATIVE_TASK_UPDATE_TASK_HANDS_UP_DURATION(Ped ped, int duration)
	{
		TASK::UPDATE_TASK_HANDS_UP_DURATION(ped, duration);
	}

	static void LUA_NATIVE_TASK_TASK_OPEN_VEHICLE_DOOR(Ped ped, Vehicle vehicle, int timeOut, int seat, float speed)
	{
		TASK::TASK_OPEN_VEHICLE_DOOR(ped, vehicle, timeOut, seat, speed);
	}

	static void LUA_NATIVE_TASK_TASK_ENTER_VEHICLE(Ped ped, Vehicle vehicle, int timeout, int seat, float speed, int flag, sol::stack_object overrideEntryClipsetName, Any p7)
	{
		TASK::TASK_ENTER_VEHICLE(ped, vehicle, timeout, seat, speed, flag, overrideEntryClipsetName.is<const char*>() ? overrideEntryClipsetName.as<const char*>() : nullptr, p7);
	}

	static void LUA_NATIVE_TASK_TASK_LEAVE_VEHICLE(Ped ped, Vehicle vehicle, int flags)
	{
		TASK::TASK_LEAVE_VEHICLE(ped, vehicle, flags);
	}

	static void LUA_NATIVE_TASK_TASK_GET_OFF_BOAT(Ped ped, Vehicle boat)
	{
		TASK::TASK_GET_OFF_BOAT(ped, boat);
	}

	static void LUA_NATIVE_TASK_TASK_SKY_DIVE(Ped ped, bool instant)
	{
		TASK::TASK_SKY_DIVE(ped, instant);
	}

	static void LUA_NATIVE_TASK_TASK_PARACHUTE(Ped ped, bool giveParachuteItem, bool instant)
	{
		TASK::TASK_PARACHUTE(ped, giveParachuteItem, instant);
	}

	static void LUA_NATIVE_TASK_TASK_PARACHUTE_TO_TARGET(Ped ped, float x, float y, float z)
	{
		TASK::TASK_PARACHUTE_TO_TARGET(ped, x, y, z);
	}

	static void LUA_NATIVE_TASK_SET_PARACHUTE_TASK_TARGET(Ped ped, float x, float y, float z)
	{
		TASK::SET_PARACHUTE_TASK_TARGET(ped, x, y, z);
	}

	static void LUA_NATIVE_TASK_SET_PARACHUTE_TASK_THRUST(Ped ped, float thrust)
	{
		TASK::SET_PARACHUTE_TASK_THRUST(ped, thrust);
	}

	static void LUA_NATIVE_TASK_TASK_RAPPEL_FROM_HELI(Ped ped, float minHeightAboveGround)
	{
		TASK::TASK_RAPPEL_FROM_HELI(ped, minHeightAboveGround);
	}

	static void LUA_NATIVE_TASK_TASK_VEHICLE_DRIVE_TO_COORD(Ped ped, Vehicle vehicle, float x, float y, float z, float speed, Any p6, Hash vehicleModel, int drivingMode, float stopRange, float straightLineDistance)
	{
		TASK::TASK_VEHICLE_DRIVE_TO_COORD(ped, vehicle, x, y, z, speed, p6, vehicleModel, drivingMode, stopRange, straightLineDistance);
	}

	static void LUA_NATIVE_TASK_TASK_VEHICLE_DRIVE_TO_COORD_LONGRANGE(Ped ped, Vehicle vehicle, float x, float y, float z, float speed, int driveMode, float stopRange)
	{
		TASK::TASK_VEHICLE_DRIVE_TO_COORD_LONGRANGE(ped, vehicle, x, y, z, speed, driveMode, stopRange);
	}

	static void LUA_NATIVE_TASK_TASK_VEHICLE_DRIVE_WANDER(Ped ped, Vehicle vehicle, float speed, int drivingStyle)
	{
		TASK::TASK_VEHICLE_DRIVE_WANDER(ped, vehicle, speed, drivingStyle);
	}

	static void LUA_NATIVE_TASK_TASK_FOLLOW_TO_OFFSET_OF_ENTITY(Ped ped, Entity entity, float offsetX, float offsetY, float offsetZ, float movementSpeed, int timeout, float stoppingRange, bool persistFollowing)
	{
		TASK::TASK_FOLLOW_TO_OFFSET_OF_ENTITY(ped, entity, offsetX, offsetY, offsetZ, movementSpeed, timeout, stoppingRange, persistFollowing);
	}

	static void LUA_NATIVE_TASK_TASK_GO_STRAIGHT_TO_COORD(Ped ped, float x, float y, float z, float speed, int timeout, float targetHeading, float distanceToSlide)
	{
		TASK::TASK_GO_STRAIGHT_TO_COORD(ped, x, y, z, speed, timeout, targetHeading, distanceToSlide);
	}

	static void LUA_NATIVE_TASK_TASK_GO_STRAIGHT_TO_COORD_RELATIVE_TO_ENTITY(Ped ped, Entity entity, float x, float y, float z, float moveBlendRatio, int time)
	{
		TASK::TASK_GO_STRAIGHT_TO_COORD_RELATIVE_TO_ENTITY(ped, entity, x, y, z, moveBlendRatio, time);
	}

	static void LUA_NATIVE_TASK_TASK_ACHIEVE_HEADING(Ped ped, float heading, int timeout)
	{
		TASK::TASK_ACHIEVE_HEADING(ped, heading, timeout);
	}

	static void LUA_NATIVE_TASK_TASK_FLUSH_ROUTE()
	{
		TASK::TASK_FLUSH_ROUTE();
	}

	static void LUA_NATIVE_TASK_TASK_EXTEND_ROUTE(float x, float y, float z)
	{
		TASK::TASK_EXTEND_ROUTE(x, y, z);
	}

	static void LUA_NATIVE_TASK_TASK_FOLLOW_POINT_ROUTE(Ped ped, float speed, int mode)
	{
		TASK::TASK_FOLLOW_POINT_ROUTE(ped, speed, mode);
	}

	static void LUA_NATIVE_TASK_TASK_GO_TO_ENTITY(Entity entity, Entity target, int duration, float distance, float moveBlendRatio, float slowDownDistance, int flags)
	{
		TASK::TASK_GO_TO_ENTITY(entity, target, duration, distance, moveBlendRatio, slowDownDistance, flags);
	}

	static void LUA_NATIVE_TASK_TASK_SMART_FLEE_COORD(Ped ped, float x, float y, float z, float distance, int time, bool preferPavements, bool quitIfOutOfRange)
	{
		TASK::TASK_SMART_FLEE_COORD(ped, x, y, z, distance, time, preferPavements, quitIfOutOfRange);
	}

	static void LUA_NATIVE_TASK_TASK_SMART_FLEE_PED(Ped ped, Ped fleeTarget, float safeDistance, int fleeTime, bool preferPavements, bool updateToNearestHatedPed)
	{
		TASK::TASK_SMART_FLEE_PED(ped, fleeTarget, safeDistance, fleeTime, preferPavements, updateToNearestHatedPed);
	}

	static void LUA_NATIVE_TASK_TASK_REACT_AND_FLEE_PED(Ped ped, Ped fleeTarget)
	{
		TASK::TASK_REACT_AND_FLEE_PED(ped, fleeTarget);
	}

	static void LUA_NATIVE_TASK_TASK_SHOCKING_EVENT_REACT(Ped ped, int eventHandle)
	{
		TASK::TASK_SHOCKING_EVENT_REACT(ped, eventHandle);
	}

	static void LUA_NATIVE_TASK_TASK_WANDER_IN_AREA(Ped ped, float x, float y, float z, float radius, float minimalLength, float timeBetweenWalks)
	{
		TASK::TASK_WANDER_IN_AREA(ped, x, y, z, radius, minimalLength, timeBetweenWalks);
	}

	static void LUA_NATIVE_TASK_TASK_WANDER_STANDARD(Ped ped, float heading, int flags)
	{
		TASK::TASK_WANDER_STANDARD(ped, heading, flags);
	}

	static void LUA_NATIVE_TASK_TASK_WANDER_SPECIFIC(Ped ped, sol::stack_object conditionalAnimGroupStr, sol::stack_object conditionalAnimStr, float heading)
	{
		TASK::TASK_WANDER_SPECIFIC(ped, conditionalAnimGroupStr.is<const char*>() ? conditionalAnimGroupStr.as<const char*>() : nullptr, conditionalAnimStr.is<const char*>() ? conditionalAnimStr.as<const char*>() : nullptr, heading);
	}

	static void LUA_NATIVE_TASK_TASK_VEHICLE_PARK(Ped ped, Vehicle vehicle, float x, float y, float z, float heading, int mode, float radius, bool keepEngineOn)
	{
		TASK::TASK_VEHICLE_PARK(ped, vehicle, x, y, z, heading, mode, radius, keepEngineOn);
	}

	static void LUA_NATIVE_TASK_TASK_STEALTH_KILL(Ped killer, Ped target, Hash stealthKillActionResultHash, float desiredMoveBlendRatio, int stealthFlags)
	{
		TASK::TASK_STEALTH_KILL(killer, target, stealthKillActionResultHash, desiredMoveBlendRatio, stealthFlags);
	}

	static void LUA_NATIVE_TASK_TASK_PLANT_BOMB(Ped ped, float x, float y, float z, float heading)
	{
		TASK::TASK_PLANT_BOMB(ped, x, y, z, heading);
	}

	static void LUA_NATIVE_TASK_TASK_FOLLOW_NAV_MESH_TO_COORD(Ped ped, float x, float y, float z, float moveBlendRatio, int time, float targetRadius, int flags, float targetHeading)
	{
		TASK::TASK_FOLLOW_NAV_MESH_TO_COORD(ped, x, y, z, moveBlendRatio, time, targetRadius, flags, targetHeading);
	}

	static void LUA_NATIVE_TASK_TASK_FOLLOW_NAV_MESH_TO_COORD_ADVANCED(Ped ped, float x, float y, float z, float moveBlendRatio, int time, float targetRadius, int flags, float slideToCoordHeading, float maxSlopeNavigable, float clampMaxSearchDistance, float targetHeading)
	{
		TASK::TASK_FOLLOW_NAV_MESH_TO_COORD_ADVANCED(ped, x, y, z, moveBlendRatio, time, targetRadius, flags, slideToCoordHeading, maxSlopeNavigable, clampMaxSearchDistance, targetHeading);
	}

	static void LUA_NATIVE_TASK_SET_PED_PATH_CAN_USE_CLIMBOVERS(Ped ped, bool Toggle)
	{
		TASK::SET_PED_PATH_CAN_USE_CLIMBOVERS(ped, Toggle);
	}

	static void LUA_NATIVE_TASK_SET_PED_PATH_CAN_USE_LADDERS(Ped ped, bool Toggle)
	{
		TASK::SET_PED_PATH_CAN_USE_LADDERS(ped, Toggle);
	}

	static void LUA_NATIVE_TASK_SET_PED_PATH_CAN_DROP_FROM_HEIGHT(Ped ped, bool Toggle)
	{
		TASK::SET_PED_PATH_CAN_DROP_FROM_HEIGHT(ped, Toggle);
	}

	static void LUA_NATIVE_TASK_SET_PED_PATH_CLIMB_COST_MODIFIER(Ped ped, float modifier)
	{
		TASK::SET_PED_PATH_CLIMB_COST_MODIFIER(ped, modifier);
	}

	static void LUA_NATIVE_TASK_SET_PED_PATH_MAY_ENTER_WATER(Ped ped, bool mayEnterWater)
	{
		TASK::SET_PED_PATH_MAY_ENTER_WATER(ped, mayEnterWater);
	}

	static void LUA_NATIVE_TASK_SET_PED_PATH_PREFER_TO_AVOID_WATER(Ped ped, bool avoidWater)
	{
		TASK::SET_PED_PATH_PREFER_TO_AVOID_WATER(ped, avoidWater);
	}

	static void LUA_NATIVE_TASK_SET_PED_PATH_AVOID_FIRE(Ped ped, bool avoidFire)
	{
		TASK::SET_PED_PATH_AVOID_FIRE(ped, avoidFire);
	}

	static void LUA_NATIVE_TASK_SET_GLOBAL_MIN_BIRD_FLIGHT_HEIGHT(float height)
	{
		TASK::SET_GLOBAL_MIN_BIRD_FLIGHT_HEIGHT(height);
	}

	static std::tuple<int, float, bool> LUA_NATIVE_TASK_GET_NAVMESH_ROUTE_DISTANCE_REMAINING(Ped ped, float distanceRemaining, bool isPathReady)
	{
		std::tuple<int, float, bool> return_values;
		std::get<0>(return_values) = TASK::GET_NAVMESH_ROUTE_DISTANCE_REMAINING(ped, &distanceRemaining, (BOOL*)&isPathReady);
		std::get<1>(return_values) = distanceRemaining;
		std::get<2>(return_values) = isPathReady;

		return return_values;
	}

	static int LUA_NATIVE_TASK_GET_NAVMESH_ROUTE_RESULT(Ped ped)
	{
		auto retval = TASK::GET_NAVMESH_ROUTE_RESULT(ped);
		return retval;
	}

	static bool LUA_NATIVE_TASK_IS_CONTROLLED_VEHICLE_UNABLE_TO_GET_TO_ROAD(Ped ped)
	{
		auto retval = (bool)TASK::IS_CONTROLLED_VEHICLE_UNABLE_TO_GET_TO_ROAD(ped);
		return retval;
	}

	static void LUA_NATIVE_TASK_TASK_GO_TO_COORD_ANY_MEANS(Ped ped, float x, float y, float z, float moveBlendRatio, Vehicle vehicle, bool useLongRangeVehiclePathing, int drivingFlags, float maxRangeToShootTargets)
	{
		TASK::TASK_GO_TO_COORD_ANY_MEANS(ped, x, y, z, moveBlendRatio, vehicle, useLongRangeVehiclePathing, drivingFlags, maxRangeToShootTargets);
	}

	static void LUA_NATIVE_TASK_TASK_GO_TO_COORD_ANY_MEANS_EXTRA_PARAMS(Ped ped, float x, float y, float z, float moveBlendRatio, Vehicle vehicle, bool useLongRangeVehiclePathing, int drivingFlags, float maxRangeToShootTargets, float extraVehToTargetDistToPreferVehicle, float driveStraightLineDistance, int extraFlags, float warpTimerMS)
	{
		TASK::TASK_GO_TO_COORD_ANY_MEANS_EXTRA_PARAMS(ped, x, y, z, moveBlendRatio, vehicle, useLongRangeVehiclePathing, drivingFlags, maxRangeToShootTargets, extraVehToTargetDistToPreferVehicle, driveStraightLineDistance, extraFlags, warpTimerMS);
	}

	static void LUA_NATIVE_TASK_TASK_GO_TO_COORD_ANY_MEANS_EXTRA_PARAMS_WITH_CRUISE_SPEED(Ped ped, float x, float y, float z, float moveBlendRatio, Vehicle vehicle, bool useLongRangeVehiclePathing, int drivingFlags, float maxRangeToShootTargets, float extraVehToTargetDistToPreferVehicle, float driveStraightLineDistance, int extraFlags, float cruiseSpeed, float targetArriveDist)
	{
		TASK::TASK_GO_TO_COORD_ANY_MEANS_EXTRA_PARAMS_WITH_CRUISE_SPEED(ped, x, y, z, moveBlendRatio, vehicle, useLongRangeVehiclePathing, drivingFlags, maxRangeToShootTargets, extraVehToTargetDistToPreferVehicle, driveStraightLineDistance, extraFlags, cruiseSpeed, targetArriveDist);
	}

	static void LUA_NATIVE_TASK_TASK_PLAY_ANIM(Ped ped, sol::stack_object animDictionary, sol::stack_object animationName, float blendInSpeed, float blendOutSpeed, int duration, int flag, float playbackRate, bool lockX, bool lockY, bool lockZ)
	{
		TASK::TASK_PLAY_ANIM(ped, animDictionary.is<const char*>() ? animDictionary.as<const char*>() : nullptr, animationName.is<const char*>() ? animationName.as<const char*>() : nullptr, blendInSpeed, blendOutSpeed, duration, flag, playbackRate, lockX, lockY, lockZ);
	}

	static void LUA_NATIVE_TASK_TASK_PLAY_ANIM_ADVANCED(Ped ped, sol::stack_object animDict, sol::stack_object animName, float posX, float posY, float posZ, float rotX, float rotY, float rotZ, float animEnterSpeed, float animExitSpeed, int duration, Any flag, float animTime, int rotOrder, int ikFlags)
	{
		TASK::TASK_PLAY_ANIM_ADVANCED(ped, animDict.is<const char*>() ? animDict.as<const char*>() : nullptr, animName.is<const char*>() ? animName.as<const char*>() : nullptr, posX, posY, posZ, rotX, rotY, rotZ, animEnterSpeed, animExitSpeed, duration, flag, animTime, rotOrder, ikFlags);
	}

	static void LUA_NATIVE_TASK_STOP_ANIM_TASK(Entity entity, sol::stack_object animDictionary, sol::stack_object animationName, float blendDelta)
	{
		TASK::STOP_ANIM_TASK(entity, animDictionary.is<const char*>() ? animDictionary.as<const char*>() : nullptr, animationName.is<const char*>() ? animationName.as<const char*>() : nullptr, blendDelta);
	}

	static std::tuple<int, int, int> LUA_NATIVE_TASK_TASK_SCRIPTED_ANIMATION(Ped ped, int priorityLowData, int priorityMidData, int priorityHighData, float blendInDelta, float blendOutDelta)
	{
		std::tuple<int, int, int> return_values;
		TASK::TASK_SCRIPTED_ANIMATION(ped, &priorityLowData, &priorityMidData, &priorityHighData, blendInDelta, blendOutDelta);
		std::get<0>(return_values) = priorityLowData;
		std::get<1>(return_values) = priorityMidData;
		std::get<2>(return_values) = priorityHighData;

		return return_values;
	}

	static std::tuple<int, int, int> LUA_NATIVE_TASK_PLAY_ENTITY_SCRIPTED_ANIM(Entity entity, int priorityLowData, int priorityMidData, int priorityHighData, float blendInDelta, float blendOutDelta)
	{
		std::tuple<int, int, int> return_values;
		TASK::PLAY_ENTITY_SCRIPTED_ANIM(entity, &priorityLowData, &priorityMidData, &priorityHighData, blendInDelta, blendOutDelta);
		std::get<0>(return_values) = priorityLowData;
		std::get<1>(return_values) = priorityMidData;
		std::get<2>(return_values) = priorityHighData;

		return return_values;
	}

	static void LUA_NATIVE_TASK_STOP_ANIM_PLAYBACK(Entity entity, int priority, bool secondary)
	{
		TASK::STOP_ANIM_PLAYBACK(entity, priority, secondary);
	}

	static void LUA_NATIVE_TASK_SET_ANIM_WEIGHT(Entity entity, float weight, int priority, int index, bool secondary)
	{
		TASK::SET_ANIM_WEIGHT(entity, weight, priority, index, secondary);
	}

	static void LUA_NATIVE_TASK_SET_ANIM_PHASE(Entity entity, float phase, int priority, bool secondary)
	{
		TASK::SET_ANIM_PHASE(entity, phase, priority, secondary);
	}

	static void LUA_NATIVE_TASK_SET_ANIM_RATE(Entity entity, float rate, int priority, bool secondary)
	{
		TASK::SET_ANIM_RATE(entity, rate, priority, secondary);
	}

	static void LUA_NATIVE_TASK_SET_ANIM_LOOPED(Entity entity, bool looped, int priority, bool secondary)
	{
		TASK::SET_ANIM_LOOPED(entity, looped, priority, secondary);
	}

	static void LUA_NATIVE_TASK_TASK_PLAY_PHONE_GESTURE_ANIMATION(Ped ped, sol::stack_object animDict, sol::stack_object animation, sol::stack_object boneMaskType, float blendInDuration, float blendOutDuration, bool isLooping, bool holdLastFrame)
	{
		TASK::TASK_PLAY_PHONE_GESTURE_ANIMATION(ped, animDict.is<const char*>() ? animDict.as<const char*>() : nullptr, animation.is<const char*>() ? animation.as<const char*>() : nullptr, boneMaskType.is<const char*>() ? boneMaskType.as<const char*>() : nullptr, blendInDuration, blendOutDuration, isLooping, holdLastFrame);
	}

	static void LUA_NATIVE_TASK_TASK_STOP_PHONE_GESTURE_ANIMATION(Ped ped, float blendOutOverride)
	{
		TASK::TASK_STOP_PHONE_GESTURE_ANIMATION(ped, blendOutOverride);
	}

	static bool LUA_NATIVE_TASK_IS_PLAYING_PHONE_GESTURE_ANIM(Ped ped)
	{
		auto retval = (bool)TASK::IS_PLAYING_PHONE_GESTURE_ANIM(ped);
		return retval;
	}

	static float LUA_NATIVE_TASK_GET_PHONE_GESTURE_ANIM_CURRENT_TIME(Ped ped)
	{
		auto retval = TASK::GET_PHONE_GESTURE_ANIM_CURRENT_TIME(ped);
		return retval;
	}

	static float LUA_NATIVE_TASK_GET_PHONE_GESTURE_ANIM_TOTAL_TIME(Ped ped)
	{
		auto retval = TASK::GET_PHONE_GESTURE_ANIM_TOTAL_TIME(ped);
		return retval;
	}

	static void LUA_NATIVE_TASK_TASK_VEHICLE_PLAY_ANIM(Vehicle vehicle, sol::stack_object animationSet, sol::stack_object animationName)
	{
		TASK::TASK_VEHICLE_PLAY_ANIM(vehicle, animationSet.is<const char*>() ? animationSet.as<const char*>() : nullptr, animationName.is<const char*>() ? animationName.as<const char*>() : nullptr);
	}

	static void LUA_NATIVE_TASK_TASK_LOOK_AT_COORD(Entity entity, float x, float y, float z, int duration, int flags, int priority)
	{
		TASK::TASK_LOOK_AT_COORD(entity, x, y, z, duration, flags, priority);
	}

	static void LUA_NATIVE_TASK_TASK_LOOK_AT_ENTITY(Ped ped, Entity lookAt, int duration, int flags, int priority)
	{
		TASK::TASK_LOOK_AT_ENTITY(ped, lookAt, duration, flags, priority);
	}

	static void LUA_NATIVE_TASK_TASK_CLEAR_LOOK_AT(Ped ped)
	{
		TASK::TASK_CLEAR_LOOK_AT(ped);
	}

	static int LUA_NATIVE_TASK_OPEN_SEQUENCE_TASK(int taskSequenceId)
	{
		TASK::OPEN_SEQUENCE_TASK(&taskSequenceId);
		return taskSequenceId;
	}

	static void LUA_NATIVE_TASK_CLOSE_SEQUENCE_TASK(int taskSequenceId)
	{
		TASK::CLOSE_SEQUENCE_TASK(taskSequenceId);
	}

	static void LUA_NATIVE_TASK_TASK_PERFORM_SEQUENCE(Ped ped, int taskSequenceId)
	{
		TASK::TASK_PERFORM_SEQUENCE(ped, taskSequenceId);
	}

	static void LUA_NATIVE_TASK_TASK_PERFORM_SEQUENCE_LOCALLY(Ped ped, int taskSequenceId)
	{
		TASK::TASK_PERFORM_SEQUENCE_LOCALLY(ped, taskSequenceId);
	}

	static int LUA_NATIVE_TASK_CLEAR_SEQUENCE_TASK(int taskSequenceId)
	{
		TASK::CLEAR_SEQUENCE_TASK(&taskSequenceId);
		return taskSequenceId;
	}

	static void LUA_NATIVE_TASK_SET_SEQUENCE_TO_REPEAT(int taskSequenceId, bool repeat)
	{
		TASK::SET_SEQUENCE_TO_REPEAT(taskSequenceId, repeat);
	}

	static int LUA_NATIVE_TASK_GET_SEQUENCE_PROGRESS(Ped ped)
	{
		auto retval = TASK::GET_SEQUENCE_PROGRESS(ped);
		return retval;
	}

	static bool LUA_NATIVE_TASK_GET_IS_TASK_ACTIVE(Ped ped, int taskIndex)
	{
		auto retval = (bool)TASK::GET_IS_TASK_ACTIVE(ped, taskIndex);
		return retval;
	}

	static int LUA_NATIVE_TASK_GET_SCRIPT_TASK_STATUS(Ped ped, Hash taskHash)
	{
		auto retval = TASK::GET_SCRIPT_TASK_STATUS(ped, taskHash);
		return retval;
	}

	static int LUA_NATIVE_TASK_GET_ACTIVE_VEHICLE_MISSION_TYPE(Vehicle vehicle)
	{
		auto retval = TASK::GET_ACTIVE_VEHICLE_MISSION_TYPE(vehicle);
		return retval;
	}

	static void LUA_NATIVE_TASK_TASK_LEAVE_ANY_VEHICLE(Ped ped, int delayTime, int flags)
	{
		TASK::TASK_LEAVE_ANY_VEHICLE(ped, delayTime, flags);
	}

	static void LUA_NATIVE_TASK_TASK_AIM_GUN_SCRIPTED(Ped ped, Hash scriptTask, bool disableBlockingClip, bool instantBlendToAim)
	{
		TASK::TASK_AIM_GUN_SCRIPTED(ped, scriptTask, disableBlockingClip, instantBlendToAim);
	}

	static void LUA_NATIVE_TASK_TASK_AIM_GUN_SCRIPTED_WITH_TARGET(Ped ped, Ped target, float x, float y, float z, int gunTaskType, bool disableBlockingClip, bool forceAim)
	{
		TASK::TASK_AIM_GUN_SCRIPTED_WITH_TARGET(ped, target, x, y, z, gunTaskType, disableBlockingClip, forceAim);
	}

	static void LUA_NATIVE_TASK_UPDATE_TASK_AIM_GUN_SCRIPTED_TARGET(Ped ped, Ped target, float x, float y, float z, bool disableBlockingClip)
	{
		TASK::UPDATE_TASK_AIM_GUN_SCRIPTED_TARGET(ped, target, x, y, z, disableBlockingClip);
	}

	static const char* LUA_NATIVE_TASK_GET_CLIP_SET_FOR_SCRIPTED_GUN_TASK(int gunTaskType)
	{
		auto retval = TASK::GET_CLIP_SET_FOR_SCRIPTED_GUN_TASK(gunTaskType);
		return retval;
	}

	static void LUA_NATIVE_TASK_TASK_AIM_GUN_AT_ENTITY(Ped ped, Entity entity, int duration, bool instantBlendToAim)
	{
		TASK::TASK_AIM_GUN_AT_ENTITY(ped, entity, duration, instantBlendToAim);
	}

	static void LUA_NATIVE_TASK_TASK_TURN_PED_TO_FACE_ENTITY(Ped ped, Entity entity, int duration)
	{
		TASK::TASK_TURN_PED_TO_FACE_ENTITY(ped, entity, duration);
	}

	static void LUA_NATIVE_TASK_TASK_AIM_GUN_AT_COORD(Ped ped, float x, float y, float z, int time, bool instantBlendToAim, bool playAnimIntro)
	{
		TASK::TASK_AIM_GUN_AT_COORD(ped, x, y, z, time, instantBlendToAim, playAnimIntro);
	}

	static void LUA_NATIVE_TASK_TASK_SHOOT_AT_COORD(Ped ped, float x, float y, float z, int duration, Hash firingPattern)
	{
		TASK::TASK_SHOOT_AT_COORD(ped, x, y, z, duration, firingPattern);
	}

	static void LUA_NATIVE_TASK_TASK_SHUFFLE_TO_NEXT_VEHICLE_SEAT(Ped ped, Vehicle vehicle, bool useAlternateShuffle)
	{
		TASK::TASK_SHUFFLE_TO_NEXT_VEHICLE_SEAT(ped, vehicle, useAlternateShuffle);
	}

	static void LUA_NATIVE_TASK_CLEAR_PED_TASKS(Ped ped)
	{
		TASK::CLEAR_PED_TASKS(ped);
	}

	static void LUA_NATIVE_TASK_CLEAR_PED_SECONDARY_TASK(Ped ped)
	{
		TASK::CLEAR_PED_SECONDARY_TASK(ped);
	}

	static void LUA_NATIVE_TASK_TASK_EVERYONE_LEAVE_VEHICLE(Vehicle vehicle)
	{
		TASK::TASK_EVERYONE_LEAVE_VEHICLE(vehicle);
	}

	static void LUA_NATIVE_TASK_TASK_GOTO_ENTITY_OFFSET(Ped ped, Entity entity, int time, float seekRadius, float seekAngleDeg, float moveBlendRatio, int gotoEntityOffsetFlags)
	{
		TASK::TASK_GOTO_ENTITY_OFFSET(ped, entity, time, seekRadius, seekAngleDeg, moveBlendRatio, gotoEntityOffsetFlags);
	}

	static void LUA_NATIVE_TASK_TASK_GOTO_ENTITY_OFFSET_XY(Ped ped, Entity entity, int duration, float targetRadius, float offsetX, float offsetY, float moveBlendRatio, int gotoEntityOffsetFlags)
	{
		TASK::TASK_GOTO_ENTITY_OFFSET_XY(ped, entity, duration, targetRadius, offsetX, offsetY, moveBlendRatio, gotoEntityOffsetFlags);
	}

	static void LUA_NATIVE_TASK_TASK_TURN_PED_TO_FACE_COORD(Ped ped, float x, float y, float z, int duration)
	{
		TASK::TASK_TURN_PED_TO_FACE_COORD(ped, x, y, z, duration);
	}

	static void LUA_NATIVE_TASK_TASK_VEHICLE_TEMP_ACTION(Ped driver, Vehicle vehicle, int action, int time)
	{
		TASK::TASK_VEHICLE_TEMP_ACTION(driver, vehicle, action, time);
	}

	static void LUA_NATIVE_TASK_TASK_VEHICLE_MISSION(Ped driver, Vehicle vehicle, Vehicle vehicleTarget, int missionType, float cruiseSpeed, int drivingStyle, float targetReached, float straightLineDistance, bool DriveAgainstTraffic)
	{
		TASK::TASK_VEHICLE_MISSION(driver, vehicle, vehicleTarget, missionType, cruiseSpeed, drivingStyle, targetReached, straightLineDistance, DriveAgainstTraffic);
	}

	static void LUA_NATIVE_TASK_TASK_VEHICLE_MISSION_PED_TARGET(Ped ped, Vehicle vehicle, Ped pedTarget, int missionType, float maxSpeed, int drivingStyle, float minDistance, float straightLineDistance, bool DriveAgainstTraffic)
	{
		TASK::TASK_VEHICLE_MISSION_PED_TARGET(ped, vehicle, pedTarget, missionType, maxSpeed, drivingStyle, minDistance, straightLineDistance, DriveAgainstTraffic);
	}

	static void LUA_NATIVE_TASK_TASK_VEHICLE_MISSION_COORS_TARGET(Ped ped, Vehicle vehicle, float x, float y, float z, int mission, float cruiseSpeed, int drivingStyle, float targetReached, float straightLineDistance, bool DriveAgainstTraffic)
	{
		TASK::TASK_VEHICLE_MISSION_COORS_TARGET(ped, vehicle, x, y, z, mission, cruiseSpeed, drivingStyle, targetReached, straightLineDistance, DriveAgainstTraffic);
	}

	static void LUA_NATIVE_TASK_TASK_VEHICLE_ESCORT(Ped ped, Vehicle vehicle, Vehicle targetVehicle, int mode, float speed, int drivingStyle, float minDistance, int minHeightAboveTerrain, float noRoadsDistance)
	{
		TASK::TASK_VEHICLE_ESCORT(ped, vehicle, targetVehicle, mode, speed, drivingStyle, minDistance, minHeightAboveTerrain, noRoadsDistance);
	}

	static void LUA_NATIVE_TASK_TASK_VEHICLE_FOLLOW(Ped driver, Vehicle vehicle, Entity targetEntity, float speed, int drivingStyle, int minDistance)
	{
		TASK::TASK_VEHICLE_FOLLOW(driver, vehicle, targetEntity, speed, drivingStyle, minDistance);
	}

	static void LUA_NATIVE_TASK_TASK_VEHICLE_CHASE(Ped driver, Entity targetEnt)
	{
		TASK::TASK_VEHICLE_CHASE(driver, targetEnt);
	}

	static void LUA_NATIVE_TASK_TASK_VEHICLE_HELI_PROTECT(Ped pilot, Vehicle vehicle, Entity entityToFollow, float targetSpeed, int drivingFlags, float radius, int altitude, int heliFlags)
	{
		TASK::TASK_VEHICLE_HELI_PROTECT(pilot, vehicle, entityToFollow, targetSpeed, drivingFlags, radius, altitude, heliFlags);
	}

	static void LUA_NATIVE_TASK_SET_TASK_VEHICLE_CHASE_BEHAVIOR_FLAG(Ped ped, int flag, bool set)
	{
		TASK::SET_TASK_VEHICLE_CHASE_BEHAVIOR_FLAG(ped, flag, set);
	}

	static void LUA_NATIVE_TASK_SET_TASK_VEHICLE_CHASE_IDEAL_PURSUIT_DISTANCE(Ped ped, float distance)
	{
		TASK::SET_TASK_VEHICLE_CHASE_IDEAL_PURSUIT_DISTANCE(ped, distance);
	}

	static void LUA_NATIVE_TASK_TASK_HELI_CHASE(Ped pilot, Entity entityToFollow, float x, float y, float z)
	{
		TASK::TASK_HELI_CHASE(pilot, entityToFollow, x, y, z);
	}

	static void LUA_NATIVE_TASK_TASK_PLANE_CHASE(Ped pilot, Entity entityToFollow, float x, float y, float z)
	{
		TASK::TASK_PLANE_CHASE(pilot, entityToFollow, x, y, z);
	}

	static void LUA_NATIVE_TASK_TASK_PLANE_LAND(Ped pilot, Vehicle plane, float runwayStartX, float runwayStartY, float runwayStartZ, float runwayEndX, float runwayEndY, float runwayEndZ)
	{
		TASK::TASK_PLANE_LAND(pilot, plane, runwayStartX, runwayStartY, runwayStartZ, runwayEndX, runwayEndY, runwayEndZ);
	}

	static void LUA_NATIVE_TASK_CLEAR_DEFAULT_PRIMARY_TASK(Ped ped)
	{
		TASK::CLEAR_DEFAULT_PRIMARY_TASK(ped);
	}

	static void LUA_NATIVE_TASK_CLEAR_PRIMARY_VEHICLE_TASK(Vehicle vehicle)
	{
		TASK::CLEAR_PRIMARY_VEHICLE_TASK(vehicle);
	}

	static void LUA_NATIVE_TASK_CLEAR_VEHICLE_CRASH_TASK(Vehicle vehicle)
	{
		TASK::CLEAR_VEHICLE_CRASH_TASK(vehicle);
	}

	static void LUA_NATIVE_TASK_TASK_PLANE_GOTO_PRECISE_VTOL(Ped ped, Vehicle vehicle, float x, float y, float z, int flightHeight, int minHeightAboveTerrain, bool useDesiredOrientation, float desiredOrientation, bool autopilot)
	{
		TASK::TASK_PLANE_GOTO_PRECISE_VTOL(ped, vehicle, x, y, z, flightHeight, minHeightAboveTerrain, useDesiredOrientation, desiredOrientation, autopilot);
	}

	static void LUA_NATIVE_TASK_TASK_SUBMARINE_GOTO_AND_STOP(Ped ped, Vehicle submarine, float x, float y, float z, bool autopilot)
	{
		TASK::TASK_SUBMARINE_GOTO_AND_STOP(ped, submarine, x, y, z, autopilot);
	}

	static void LUA_NATIVE_TASK_TASK_HELI_MISSION(Ped pilot, Vehicle aircraft, Vehicle targetVehicle, Ped targetPed, float destinationX, float destinationY, float destinationZ, int missionFlag, float maxSpeed, float radius, float targetHeading, int maxHeight, int minHeight, float slowDownDistance, int behaviorFlags)
	{
		TASK::TASK_HELI_MISSION(pilot, aircraft, targetVehicle, targetPed, destinationX, destinationY, destinationZ, missionFlag, maxSpeed, radius, targetHeading, maxHeight, minHeight, slowDownDistance, behaviorFlags);
	}

	static void LUA_NATIVE_TASK_TASK_HELI_ESCORT_HELI(Ped pilot, Vehicle heli1, Vehicle heli2, float offsetX, float offsetY, float offsetZ)
	{
		TASK::TASK_HELI_ESCORT_HELI(pilot, heli1, heli2, offsetX, offsetY, offsetZ);
	}

	static void LUA_NATIVE_TASK_TASK_PLANE_MISSION(Ped pilot, Vehicle aircraft, Vehicle targetVehicle, Ped targetPed, float destinationX, float destinationY, float destinationZ, int missionFlag, float angularDrag, float targetReached, float targetHeading, float maxZ, float minZ, bool precise)
	{
		TASK::TASK_PLANE_MISSION(pilot, aircraft, targetVehicle, targetPed, destinationX, destinationY, destinationZ, missionFlag, angularDrag, targetReached, targetHeading, maxZ, minZ, precise);
	}

	static void LUA_NATIVE_TASK_TASK_PLANE_TAXI(Ped pilot, Vehicle aircraft, float x, float y, float z, float cruiseSpeed, float targetReached)
	{
		TASK::TASK_PLANE_TAXI(pilot, aircraft, x, y, z, cruiseSpeed, targetReached);
	}

	static void LUA_NATIVE_TASK_TASK_BOAT_MISSION(Ped pedDriver, Vehicle vehicle, Vehicle targetVehicle, Ped targetPed, float x, float y, float z, int mission, float maxSpeed, int drivingStyle, float targetReached, Any boatFlags)
	{
		TASK::TASK_BOAT_MISSION(pedDriver, vehicle, targetVehicle, targetPed, x, y, z, mission, maxSpeed, drivingStyle, targetReached, boatFlags);
	}

	static void LUA_NATIVE_TASK_TASK_DRIVE_BY(Ped driverPed, Ped targetPed, Vehicle targetVehicle, float targetX, float targetY, float targetZ, float distanceToShoot, int pedAccuracy, bool pushUnderneathDrivingTaskIfDriving, Hash firingPattern)
	{
		TASK::TASK_DRIVE_BY(driverPed, targetPed, targetVehicle, targetX, targetY, targetZ, distanceToShoot, pedAccuracy, pushUnderneathDrivingTaskIfDriving, firingPattern);
	}

	static void LUA_NATIVE_TASK_SET_DRIVEBY_TASK_TARGET(Ped shootingPed, Ped targetPed, Vehicle targetVehicle, float x, float y, float z)
	{
		TASK::SET_DRIVEBY_TASK_TARGET(shootingPed, targetPed, targetVehicle, x, y, z);
	}

	static void LUA_NATIVE_TASK_CLEAR_DRIVEBY_TASK_UNDERNEATH_DRIVING_TASK(Ped ped)
	{
		TASK::CLEAR_DRIVEBY_TASK_UNDERNEATH_DRIVING_TASK(ped);
	}

	static bool LUA_NATIVE_TASK_IS_DRIVEBY_TASK_UNDERNEATH_DRIVING_TASK(Ped ped)
	{
		auto retval = (bool)TASK::IS_DRIVEBY_TASK_UNDERNEATH_DRIVING_TASK(ped);
		return retval;
	}

	static bool LUA_NATIVE_TASK_CONTROL_MOUNTED_WEAPON(Ped ped)
	{
		auto retval = (bool)TASK::CONTROL_MOUNTED_WEAPON(ped);
		return retval;
	}

	static void LUA_NATIVE_TASK_SET_MOUNTED_WEAPON_TARGET(Ped shootingPed, Ped targetPed, Vehicle targetVehicle, float x, float y, float z, int taskMode, bool ignoreTargetVehDeadCheck)
	{
		TASK::SET_MOUNTED_WEAPON_TARGET(shootingPed, targetPed, targetVehicle, x, y, z, taskMode, ignoreTargetVehDeadCheck);
	}

	static bool LUA_NATIVE_TASK_IS_MOUNTED_WEAPON_TASK_UNDERNEATH_DRIVING_TASK(Ped ped)
	{
		auto retval = (bool)TASK::IS_MOUNTED_WEAPON_TASK_UNDERNEATH_DRIVING_TASK(ped);
		return retval;
	}

	static void LUA_NATIVE_TASK_TASK_USE_MOBILE_PHONE(Ped ped, bool usePhone, int desiredPhoneMode)
	{
		TASK::TASK_USE_MOBILE_PHONE(ped, usePhone, desiredPhoneMode);
	}

	static void LUA_NATIVE_TASK_TASK_USE_MOBILE_PHONE_TIMED(Ped ped, int duration)
	{
		TASK::TASK_USE_MOBILE_PHONE_TIMED(ped, duration);
	}

	static void LUA_NATIVE_TASK_TASK_CHAT_TO_PED(Ped ped, Ped target, int flags, float goToLocationX, float goToLocationY, float goToLocationZ, float headingDegs, float idleTime)
	{
		TASK::TASK_CHAT_TO_PED(ped, target, flags, goToLocationX, goToLocationY, goToLocationZ, headingDegs, idleTime);
	}

	static void LUA_NATIVE_TASK_TASK_WARP_PED_INTO_VEHICLE(Ped ped, Vehicle vehicle, int seat)
	{
		TASK::TASK_WARP_PED_INTO_VEHICLE(ped, vehicle, seat);
	}

	static void LUA_NATIVE_TASK_TASK_SHOOT_AT_ENTITY(Entity entity, Entity target, int duration, Hash firingPattern)
	{
		TASK::TASK_SHOOT_AT_ENTITY(entity, target, duration, firingPattern);
	}

	static void LUA_NATIVE_TASK_TASK_CLIMB(Ped ped, bool usePlayerLaunchForce)
	{
		TASK::TASK_CLIMB(ped, usePlayerLaunchForce);
	}

	static void LUA_NATIVE_TASK_TASK_CLIMB_LADDER(Ped ped, bool fast)
	{
		TASK::TASK_CLIMB_LADDER(ped, fast);
	}

	static void LUA_NATIVE_TASK_TASK_RAPPEL_DOWN_WALL_USING_CLIPSET_OVERRIDE(Ped ped, float x1, float y1, float z1, float x2, float y2, float z2, float minZ, int ropeHandle, sol::stack_object clipSet, Any p10, Any p11)
	{
		TASK::TASK_RAPPEL_DOWN_WALL_USING_CLIPSET_OVERRIDE(ped, x1, y1, z1, x2, y2, z2, minZ, ropeHandle, clipSet.is<const char*>() ? clipSet.as<const char*>() : nullptr, p10, p11);
	}

	static int LUA_NATIVE_TASK_GET_TASK_RAPPEL_DOWN_WALL_STATE(Ped ped)
	{
		auto retval = TASK::GET_TASK_RAPPEL_DOWN_WALL_STATE(ped);
		return retval;
	}

	static void LUA_NATIVE_TASK_CLEAR_PED_TASKS_IMMEDIATELY(Ped ped)
	{
		TASK::CLEAR_PED_TASKS_IMMEDIATELY(ped);
	}

	static void LUA_NATIVE_TASK_TASK_PERFORM_SEQUENCE_FROM_PROGRESS(Ped ped, int taskIndex, int progress1, int progress2)
	{
		TASK::TASK_PERFORM_SEQUENCE_FROM_PROGRESS(ped, taskIndex, progress1, progress2);
	}

	static void LUA_NATIVE_TASK_SET_NEXT_DESIRED_MOVE_STATE(float nextMoveState)
	{
		TASK::SET_NEXT_DESIRED_MOVE_STATE(nextMoveState);
	}

	static void LUA_NATIVE_TASK_SET_PED_DESIRED_MOVE_BLEND_RATIO(Ped ped, float newMoveBlendRatio)
	{
		TASK::SET_PED_DESIRED_MOVE_BLEND_RATIO(ped, newMoveBlendRatio);
	}

	static float LUA_NATIVE_TASK_GET_PED_DESIRED_MOVE_BLEND_RATIO(Ped ped)
	{
		auto retval = TASK::GET_PED_DESIRED_MOVE_BLEND_RATIO(ped);
		return retval;
	}

	static void LUA_NATIVE_TASK_TASK_GOTO_ENTITY_AIMING(Ped ped, Entity target, float distanceToStopAt, float StartAimingDist)
	{
		TASK::TASK_GOTO_ENTITY_AIMING(ped, target, distanceToStopAt, StartAimingDist);
	}

	static void LUA_NATIVE_TASK_TASK_SET_DECISION_MAKER(Ped ped, Hash decisionMakerId)
	{
		TASK::TASK_SET_DECISION_MAKER(ped, decisionMakerId);
	}

	static void LUA_NATIVE_TASK_TASK_SET_SPHERE_DEFENSIVE_AREA(Ped ped, float x, float y, float z, float radius)
	{
		TASK::TASK_SET_SPHERE_DEFENSIVE_AREA(ped, x, y, z, radius);
	}

	static void LUA_NATIVE_TASK_TASK_CLEAR_DEFENSIVE_AREA(Ped ped)
	{
		TASK::TASK_CLEAR_DEFENSIVE_AREA(ped);
	}

	static void LUA_NATIVE_TASK_TASK_PED_SLIDE_TO_COORD(Ped ped, float x, float y, float z, float heading, float speed)
	{
		TASK::TASK_PED_SLIDE_TO_COORD(ped, x, y, z, heading, speed);
	}

	static void LUA_NATIVE_TASK_TASK_PED_SLIDE_TO_COORD_HDG_RATE(Ped ped, float x, float y, float z, float heading, float speed, float headingChangeRate)
	{
		TASK::TASK_PED_SLIDE_TO_COORD_HDG_RATE(ped, x, y, z, heading, speed, headingChangeRate);
	}

	static ScrHandle LUA_NATIVE_TASK_ADD_COVER_POINT(float x, float y, float z, float direction, int usage, int height, int arc, bool isPriority)
	{
		auto retval = TASK::ADD_COVER_POINT(x, y, z, direction, usage, height, arc, isPriority);
		return retval;
	}

	static void LUA_NATIVE_TASK_REMOVE_COVER_POINT(ScrHandle coverpoint)
	{
		TASK::REMOVE_COVER_POINT(coverpoint);
	}

	static bool LUA_NATIVE_TASK_DOES_SCRIPTED_COVER_POINT_EXIST_AT_COORDS(float x, float y, float z)
	{
		auto retval = (bool)TASK::DOES_SCRIPTED_COVER_POINT_EXIST_AT_COORDS(x, y, z);
		return retval;
	}

	static Vector3 LUA_NATIVE_TASK_GET_SCRIPTED_COVER_POINT_COORDS(ScrHandle coverpoint)
	{
		auto retval = TASK::GET_SCRIPTED_COVER_POINT_COORDS(coverpoint);
		return retval;
	}

	static void LUA_NATIVE_TASK_ADD_SCRIPTED_COVER_AREA(float x, float y, float z, float radius)
	{
		TASK::ADD_SCRIPTED_COVER_AREA(x, y, z, radius);
	}

	static void LUA_NATIVE_TASK_TASK_COMBAT_PED(Ped ped, Ped targetPed, int combatFlags, int threatResponseFlags)
	{
		TASK::TASK_COMBAT_PED(ped, targetPed, combatFlags, threatResponseFlags);
	}

	static void LUA_NATIVE_TASK_TASK_COMBAT_PED_TIMED(Ped ped, Ped target, int time, int flags)
	{
		TASK::TASK_COMBAT_PED_TIMED(ped, target, time, flags);
	}

	static void LUA_NATIVE_TASK_TASK_SEEK_COVER_FROM_POS(Ped ped, float x, float y, float z, int duration, bool allowPeekingAndFiring)
	{
		TASK::TASK_SEEK_COVER_FROM_POS(ped, x, y, z, duration, allowPeekingAndFiring);
	}

	static void LUA_NATIVE_TASK_TASK_SEEK_COVER_FROM_PED(Ped ped, Ped target, int duration, bool allowPeekingAndFiring)
	{
		TASK::TASK_SEEK_COVER_FROM_PED(ped, target, duration, allowPeekingAndFiring);
	}

	static void LUA_NATIVE_TASK_TASK_SEEK_COVER_TO_COVER_POINT(Ped ped, ScrHandle coverpoint, float x, float y, float z, int time, bool allowPeekingAndFiring)
	{
		TASK::TASK_SEEK_COVER_TO_COVER_POINT(ped, coverpoint, x, y, z, time, allowPeekingAndFiring);
	}

	static void LUA_NATIVE_TASK_TASK_SEEK_COVER_TO_COORDS(Ped ped, float x1, float y1, float z1, float x2, float y2, float z2, int timeout, bool shortRoute)
	{
		TASK::TASK_SEEK_COVER_TO_COORDS(ped, x1, y1, z1, x2, y2, z2, timeout, shortRoute);
	}

	static void LUA_NATIVE_TASK_TASK_PUT_PED_DIRECTLY_INTO_COVER(Ped ped, float x, float y, float z, int time, bool allowPeekingAndFiring, float blendInDuration, bool forceInitialFacingDirection, bool forceFaceLeft, int identifier, bool doEntry)
	{
		TASK::TASK_PUT_PED_DIRECTLY_INTO_COVER(ped, x, y, z, time, allowPeekingAndFiring, blendInDuration, forceInitialFacingDirection, forceFaceLeft, identifier, doEntry);
	}

	static void LUA_NATIVE_TASK_TASK_WARP_PED_DIRECTLY_INTO_COVER(Ped ped, int time, bool allowPeekingAndFiring, bool forceInitialFacingDirection, bool forceFaceLeft, int identifier)
	{
		TASK::TASK_WARP_PED_DIRECTLY_INTO_COVER(ped, time, allowPeekingAndFiring, forceInitialFacingDirection, forceFaceLeft, identifier);
	}

	static void LUA_NATIVE_TASK_TASK_EXIT_COVER(Ped ped, int exitType, float x, float y, float z)
	{
		TASK::TASK_EXIT_COVER(ped, exitType, x, y, z);
	}

	static void LUA_NATIVE_TASK_TASK_PUT_PED_DIRECTLY_INTO_MELEE(Ped ped, Ped meleeTarget, float blendInDuration, float timeInMelee, float strafePhaseSync, int aiCombatFlags)
	{
		TASK::TASK_PUT_PED_DIRECTLY_INTO_MELEE(ped, meleeTarget, blendInDuration, timeInMelee, strafePhaseSync, aiCombatFlags);
	}

	static void LUA_NATIVE_TASK_TASK_TOGGLE_DUCK(Ped ped, int toggleType)
	{
		TASK::TASK_TOGGLE_DUCK(ped, toggleType);
	}

	static void LUA_NATIVE_TASK_TASK_GUARD_CURRENT_POSITION(Ped ped, float maxPatrolProximity, float defensiveAreaRadius, bool setDefensiveArea)
	{
		TASK::TASK_GUARD_CURRENT_POSITION(ped, maxPatrolProximity, defensiveAreaRadius, setDefensiveArea);
	}

	static void LUA_NATIVE_TASK_TASK_GUARD_ASSIGNED_DEFENSIVE_AREA(Ped ped, float x, float y, float z, float heading, float maxPatrolProximity, int timer)
	{
		TASK::TASK_GUARD_ASSIGNED_DEFENSIVE_AREA(ped, x, y, z, heading, maxPatrolProximity, timer);
	}

	static void LUA_NATIVE_TASK_TASK_GUARD_SPHERE_DEFENSIVE_AREA(Ped ped, float defendPositionX, float defendPositionY, float defendPositionZ, float heading, float maxPatrolProximity, int time, float x, float y, float z, float defensiveAreaRadius)
	{
		TASK::TASK_GUARD_SPHERE_DEFENSIVE_AREA(ped, defendPositionX, defendPositionY, defendPositionZ, heading, maxPatrolProximity, time, x, y, z, defensiveAreaRadius);
	}

	static void LUA_NATIVE_TASK_TASK_STAND_GUARD(Ped ped, float x, float y, float z, float heading, sol::stack_object scenarioName)
	{
		TASK::TASK_STAND_GUARD(ped, x, y, z, heading, scenarioName.is<const char*>() ? scenarioName.as<const char*>() : nullptr);
	}

	static void LUA_NATIVE_TASK_SET_DRIVE_TASK_CRUISE_SPEED(Ped driver, float cruiseSpeed)
	{
		TASK::SET_DRIVE_TASK_CRUISE_SPEED(driver, cruiseSpeed);
	}

	static void LUA_NATIVE_TASK_SET_DRIVE_TASK_MAX_CRUISE_SPEED(Ped ped, float speed)
	{
		TASK::SET_DRIVE_TASK_MAX_CRUISE_SPEED(ped, speed);
	}

	static void LUA_NATIVE_TASK_SET_DRIVE_TASK_DRIVING_STYLE(Ped ped, int drivingStyle)
	{
		TASK::SET_DRIVE_TASK_DRIVING_STYLE(ped, drivingStyle);
	}

	static void LUA_NATIVE_TASK_ADD_COVER_BLOCKING_AREA(float startX, float startY, float startZ, float endX, float endY, float endZ, bool blockObjects, bool blockVehicles, bool blockMap, bool blockPlayer)
	{
		TASK::ADD_COVER_BLOCKING_AREA(startX, startY, startZ, endX, endY, endZ, blockObjects, blockVehicles, blockMap, blockPlayer);
	}

	static void LUA_NATIVE_TASK_REMOVE_ALL_COVER_BLOCKING_AREAS()
	{
		TASK::REMOVE_ALL_COVER_BLOCKING_AREAS();
	}

	static void LUA_NATIVE_TASK_REMOVE_COVER_BLOCKING_AREAS_AT_POSITION(float x, float y, float z)
	{
		TASK::REMOVE_COVER_BLOCKING_AREAS_AT_POSITION(x, y, z);
	}

	static void LUA_NATIVE_TASK_REMOVE_SPECIFIC_COVER_BLOCKING_AREAS(float startX, float startY, float startZ, float endX, float endY, float endZ, bool blockObjects, bool blockVehicles, bool blockMap, bool blockPlayer)
	{
		TASK::REMOVE_SPECIFIC_COVER_BLOCKING_AREAS(startX, startY, startZ, endX, endY, endZ, blockObjects, blockVehicles, blockMap, blockPlayer);
	}

	static void LUA_NATIVE_TASK_TASK_START_SCENARIO_IN_PLACE(Ped ped, sol::stack_object scenarioName, int unkDelay, bool playEnterAnim)
	{
		TASK::TASK_START_SCENARIO_IN_PLACE(ped, scenarioName.is<const char*>() ? scenarioName.as<const char*>() : nullptr, unkDelay, playEnterAnim);
	}

	static void LUA_NATIVE_TASK_TASK_START_SCENARIO_AT_POSITION(Ped ped, sol::stack_object scenarioName, float x, float y, float z, float heading, int duration, bool sittingScenario, bool teleport)
	{
		TASK::TASK_START_SCENARIO_AT_POSITION(ped, scenarioName.is<const char*>() ? scenarioName.as<const char*>() : nullptr, x, y, z, heading, duration, sittingScenario, teleport);
	}

	static void LUA_NATIVE_TASK_TASK_USE_NEAREST_SCENARIO_TO_COORD(Ped ped, float x, float y, float z, float distance, int duration)
	{
		TASK::TASK_USE_NEAREST_SCENARIO_TO_COORD(ped, x, y, z, distance, duration);
	}

	static void LUA_NATIVE_TASK_TASK_USE_NEAREST_SCENARIO_TO_COORD_WARP(Ped ped, float x, float y, float z, float radius, int timeToLeave)
	{
		TASK::TASK_USE_NEAREST_SCENARIO_TO_COORD_WARP(ped, x, y, z, radius, timeToLeave);
	}

	static void LUA_NATIVE_TASK_TASK_USE_NEAREST_SCENARIO_CHAIN_TO_COORD(Ped ped, float x, float y, float z, float maxRange, int timeToLeave)
	{
		TASK::TASK_USE_NEAREST_SCENARIO_CHAIN_TO_COORD(ped, x, y, z, maxRange, timeToLeave);
	}

	static void LUA_NATIVE_TASK_TASK_USE_NEAREST_SCENARIO_CHAIN_TO_COORD_WARP(Ped ped, float x, float y, float z, float radius, int timeToLeave)
	{
		TASK::TASK_USE_NEAREST_SCENARIO_CHAIN_TO_COORD_WARP(ped, x, y, z, radius, timeToLeave);
	}

	static bool LUA_NATIVE_TASK_DOES_SCENARIO_EXIST_IN_AREA(float x, float y, float z, float radius, bool mustBeFree)
	{
		auto retval = (bool)TASK::DOES_SCENARIO_EXIST_IN_AREA(x, y, z, radius, mustBeFree);
		return retval;
	}

	static bool LUA_NATIVE_TASK_DOES_SCENARIO_OF_TYPE_EXIST_IN_AREA(float x, float y, float z, sol::stack_object scenarioName, float radius, bool mustBeFree)
	{
		auto retval = (bool)TASK::DOES_SCENARIO_OF_TYPE_EXIST_IN_AREA(x, y, z, scenarioName.is<const char*>() ? scenarioName.as<const char*>() : nullptr, radius, mustBeFree);
		return retval;
	}

	static bool LUA_NATIVE_TASK_IS_SCENARIO_OCCUPIED(float x, float y, float z, float maxRange, bool onlyUsersActuallyAtScenario)
	{
		auto retval = (bool)TASK::IS_SCENARIO_OCCUPIED(x, y, z, maxRange, onlyUsersActuallyAtScenario);
		return retval;
	}

	static bool LUA_NATIVE_TASK_PED_HAS_USE_SCENARIO_TASK(Ped ped)
	{
		auto retval = (bool)TASK::PED_HAS_USE_SCENARIO_TASK(ped);
		return retval;
	}

	static void LUA_NATIVE_TASK_PLAY_ANIM_ON_RUNNING_SCENARIO(Ped ped, sol::stack_object animDict, sol::stack_object animName)
	{
		TASK::PLAY_ANIM_ON_RUNNING_SCENARIO(ped, animDict.is<const char*>() ? animDict.as<const char*>() : nullptr, animName.is<const char*>() ? animName.as<const char*>() : nullptr);
	}

	static bool LUA_NATIVE_TASK_DOES_SCENARIO_GROUP_EXIST(sol::stack_object scenarioGroup)
	{
		auto retval = (bool)TASK::DOES_SCENARIO_GROUP_EXIST(scenarioGroup.is<const char*>() ? scenarioGroup.as<const char*>() : nullptr);
		return retval;
	}

	static bool LUA_NATIVE_TASK_IS_SCENARIO_GROUP_ENABLED(sol::stack_object scenarioGroup)
	{
		auto retval = (bool)TASK::IS_SCENARIO_GROUP_ENABLED(scenarioGroup.is<const char*>() ? scenarioGroup.as<const char*>() : nullptr);
		return retval;
	}

	static void LUA_NATIVE_TASK_SET_SCENARIO_GROUP_ENABLED(sol::stack_object scenarioGroup, bool enabled)
	{
		TASK::SET_SCENARIO_GROUP_ENABLED(scenarioGroup.is<const char*>() ? scenarioGroup.as<const char*>() : nullptr, enabled);
	}

	static void LUA_NATIVE_TASK_RESET_SCENARIO_GROUPS_ENABLED()
	{
		TASK::RESET_SCENARIO_GROUPS_ENABLED();
	}

	static void LUA_NATIVE_TASK_SET_EXCLUSIVE_SCENARIO_GROUP(sol::stack_object scenarioGroup)
	{
		TASK::SET_EXCLUSIVE_SCENARIO_GROUP(scenarioGroup.is<const char*>() ? scenarioGroup.as<const char*>() : nullptr);
	}

	static void LUA_NATIVE_TASK_RESET_EXCLUSIVE_SCENARIO_GROUP()
	{
		TASK::RESET_EXCLUSIVE_SCENARIO_GROUP();
	}

	static bool LUA_NATIVE_TASK_IS_SCENARIO_TYPE_ENABLED(sol::stack_object scenarioType)
	{
		auto retval = (bool)TASK::IS_SCENARIO_TYPE_ENABLED(scenarioType.is<const char*>() ? scenarioType.as<const char*>() : nullptr);
		return retval;
	}

	static void LUA_NATIVE_TASK_SET_SCENARIO_TYPE_ENABLED(sol::stack_object scenarioType, bool toggle)
	{
		TASK::SET_SCENARIO_TYPE_ENABLED(scenarioType.is<const char*>() ? scenarioType.as<const char*>() : nullptr, toggle);
	}

	static void LUA_NATIVE_TASK_RESET_SCENARIO_TYPES_ENABLED()
	{
		TASK::RESET_SCENARIO_TYPES_ENABLED();
	}

	static bool LUA_NATIVE_TASK_IS_PED_ACTIVE_IN_SCENARIO(Ped ped)
	{
		auto retval = (bool)TASK::IS_PED_ACTIVE_IN_SCENARIO(ped);
		return retval;
	}

	static bool LUA_NATIVE_TASK_IS_PED_PLAYING_BASE_CLIP_IN_SCENARIO(Ped ped)
	{
		auto retval = (bool)TASK::IS_PED_PLAYING_BASE_CLIP_IN_SCENARIO(ped);
		return retval;
	}

	static void LUA_NATIVE_TASK_SET_PED_CAN_PLAY_AMBIENT_IDLES(Ped ped, bool blockIdleClips, bool removeIdleClipIfPlaying)
	{
		TASK::SET_PED_CAN_PLAY_AMBIENT_IDLES(ped, blockIdleClips, removeIdleClipIfPlaying);
	}

	static void LUA_NATIVE_TASK_TASK_COMBAT_HATED_TARGETS_IN_AREA(Ped ped, float x, float y, float z, float radius, int combatFlags)
	{
		TASK::TASK_COMBAT_HATED_TARGETS_IN_AREA(ped, x, y, z, radius, combatFlags);
	}

	static void LUA_NATIVE_TASK_TASK_COMBAT_HATED_TARGETS_AROUND_PED(Ped ped, float radius, int combatFlags)
	{
		TASK::TASK_COMBAT_HATED_TARGETS_AROUND_PED(ped, radius, combatFlags);
	}

	static void LUA_NATIVE_TASK_TASK_COMBAT_HATED_TARGETS_AROUND_PED_TIMED(Ped ped, float radius, int time, int combatFlags)
	{
		TASK::TASK_COMBAT_HATED_TARGETS_AROUND_PED_TIMED(ped, radius, time, combatFlags);
	}

	static void LUA_NATIVE_TASK_TASK_THROW_PROJECTILE(Ped ped, float x, float y, float z, int ignoreCollisionEntityIndex, bool createInvincibleProjectile)
	{
		TASK::TASK_THROW_PROJECTILE(ped, x, y, z, ignoreCollisionEntityIndex, createInvincibleProjectile);
	}

	static void LUA_NATIVE_TASK_TASK_SWAP_WEAPON(Ped ped, bool drawWeapon)
	{
		TASK::TASK_SWAP_WEAPON(ped, drawWeapon);
	}

	static void LUA_NATIVE_TASK_TASK_RELOAD_WEAPON(Ped ped, bool drawWeapon)
	{
		TASK::TASK_RELOAD_WEAPON(ped, drawWeapon);
	}

	static bool LUA_NATIVE_TASK_IS_PED_GETTING_UP(Ped ped)
	{
		auto retval = (bool)TASK::IS_PED_GETTING_UP(ped);
		return retval;
	}

	static void LUA_NATIVE_TASK_TASK_WRITHE(Ped ped, Ped target, int minFireLoops, int startState, bool forceShootOnGround, int shootFromGroundTimer)
	{
		TASK::TASK_WRITHE(ped, target, minFireLoops, startState, forceShootOnGround, shootFromGroundTimer);
	}

	static bool LUA_NATIVE_TASK_IS_PED_IN_WRITHE(Ped ped)
	{
		auto retval = (bool)TASK::IS_PED_IN_WRITHE(ped);
		return retval;
	}

	static void LUA_NATIVE_TASK_OPEN_PATROL_ROUTE(sol::stack_object patrolRoute)
	{
		TASK::OPEN_PATROL_ROUTE(patrolRoute.is<const char*>() ? patrolRoute.as<const char*>() : nullptr);
	}

	static void LUA_NATIVE_TASK_CLOSE_PATROL_ROUTE()
	{
		TASK::CLOSE_PATROL_ROUTE();
	}

	static void LUA_NATIVE_TASK_ADD_PATROL_ROUTE_NODE(int nodeId, sol::stack_object nodeType, float posX, float posY, float posZ, float headingX, float headingY, float headingZ, int duration)
	{
		TASK::ADD_PATROL_ROUTE_NODE(nodeId, nodeType.is<const char*>() ? nodeType.as<const char*>() : nullptr, posX, posY, posZ, headingX, headingY, headingZ, duration);
	}

	static void LUA_NATIVE_TASK_ADD_PATROL_ROUTE_LINK(int nodeId1, int nodeId2)
	{
		TASK::ADD_PATROL_ROUTE_LINK(nodeId1, nodeId2);
	}

	static void LUA_NATIVE_TASK_CREATE_PATROL_ROUTE()
	{
		TASK::CREATE_PATROL_ROUTE();
	}

	static void LUA_NATIVE_TASK_DELETE_PATROL_ROUTE(sol::stack_object patrolRoute)
	{
		TASK::DELETE_PATROL_ROUTE(patrolRoute.is<const char*>() ? patrolRoute.as<const char*>() : nullptr);
	}

	static std::tuple<bool, int, int> LUA_NATIVE_TASK_GET_PATROL_TASK_INFO(Ped ped, int timeLeftAtNode, int nodeId)
	{
		std::tuple<bool, int, int> return_values;
		std::get<0>(return_values) = (bool)TASK::GET_PATROL_TASK_INFO(ped, &timeLeftAtNode, &nodeId);
		std::get<1>(return_values) = timeLeftAtNode;
		std::get<2>(return_values) = nodeId;

		return return_values;
	}

	static void LUA_NATIVE_TASK_TASK_PATROL(Ped ped, sol::stack_object patrolRouteName, int alertState, bool canChatToPeds, bool useHeadLookAt)
	{
		TASK::TASK_PATROL(ped, patrolRouteName.is<const char*>() ? patrolRouteName.as<const char*>() : nullptr, alertState, canChatToPeds, useHeadLookAt);
	}

	static void LUA_NATIVE_TASK_TASK_STAY_IN_COVER(Ped ped)
	{
		TASK::TASK_STAY_IN_COVER(ped);
	}

	static void LUA_NATIVE_TASK_ADD_VEHICLE_SUBTASK_ATTACK_COORD(Ped ped, float x, float y, float z)
	{
		TASK::ADD_VEHICLE_SUBTASK_ATTACK_COORD(ped, x, y, z);
	}

	static void LUA_NATIVE_TASK_ADD_VEHICLE_SUBTASK_ATTACK_PED(Ped ped, Ped target)
	{
		TASK::ADD_VEHICLE_SUBTASK_ATTACK_PED(ped, target);
	}

	static void LUA_NATIVE_TASK_TASK_VEHICLE_SHOOT_AT_PED(Ped ped, Ped target, float fireTolerance)
	{
		TASK::TASK_VEHICLE_SHOOT_AT_PED(ped, target, fireTolerance);
	}

	static void LUA_NATIVE_TASK_TASK_VEHICLE_AIM_AT_PED(Ped ped, Ped target)
	{
		TASK::TASK_VEHICLE_AIM_AT_PED(ped, target);
	}

	static void LUA_NATIVE_TASK_TASK_VEHICLE_SHOOT_AT_COORD(Ped ped, float x, float y, float z, float fireTolerance)
	{
		TASK::TASK_VEHICLE_SHOOT_AT_COORD(ped, x, y, z, fireTolerance);
	}

	static void LUA_NATIVE_TASK_TASK_VEHICLE_AIM_AT_COORD(Ped ped, float x, float y, float z)
	{
		TASK::TASK_VEHICLE_AIM_AT_COORD(ped, x, y, z);
	}

	static void LUA_NATIVE_TASK_TASK_VEHICLE_GOTO_NAVMESH(Ped ped, Vehicle vehicle, float x, float y, float z, float speed, int behaviorFlag, float stoppingRange)
	{
		TASK::TASK_VEHICLE_GOTO_NAVMESH(ped, vehicle, x, y, z, speed, behaviorFlag, stoppingRange);
	}

	static void LUA_NATIVE_TASK_TASK_GO_TO_COORD_WHILE_AIMING_AT_COORD(Ped ped, float x, float y, float z, float aimAtX, float aimAtY, float aimAtZ, float moveBlendRatio, bool shoot, float targetRadius, float slowDistance, bool useNavMesh, int navFlags, bool instantBlendToAim, Hash firingPattern)
	{
		TASK::TASK_GO_TO_COORD_WHILE_AIMING_AT_COORD(ped, x, y, z, aimAtX, aimAtY, aimAtZ, moveBlendRatio, shoot, targetRadius, slowDistance, useNavMesh, navFlags, instantBlendToAim, firingPattern);
	}

	static void LUA_NATIVE_TASK_TASK_GO_TO_COORD_WHILE_AIMING_AT_ENTITY(Ped ped, float x, float y, float z, Entity aimAtID, float moveBlendRatio, bool shoot, float targetRadius, float slowDistance, bool useNavMesh, int navFlags, bool instantBlendToAim, Hash firingPattern, int time)
	{
		TASK::TASK_GO_TO_COORD_WHILE_AIMING_AT_ENTITY(ped, x, y, z, aimAtID, moveBlendRatio, shoot, targetRadius, slowDistance, useNavMesh, navFlags, instantBlendToAim, firingPattern, time);
	}

	static void LUA_NATIVE_TASK_TASK_GO_TO_COORD_AND_AIM_AT_HATED_ENTITIES_NEAR_COORD(Ped pedHandle, float goToLocationX, float goToLocationY, float goToLocationZ, float focusLocationX, float focusLocationY, float focusLocationZ, float speed, bool shootAtEnemies, float distanceToStopAt, float noRoadsDistance, bool useNavMesh, int navFlags, int taskFlags, Hash firingPattern)
	{
		TASK::TASK_GO_TO_COORD_AND_AIM_AT_HATED_ENTITIES_NEAR_COORD(pedHandle, goToLocationX, goToLocationY, goToLocationZ, focusLocationX, focusLocationY, focusLocationZ, speed, shootAtEnemies, distanceToStopAt, noRoadsDistance, useNavMesh, navFlags, taskFlags, firingPattern);
	}

	static void LUA_NATIVE_TASK_TASK_GO_TO_ENTITY_WHILE_AIMING_AT_COORD(Ped ped, Entity entity, float aimX, float aimY, float aimZ, float moveBlendRatio, bool shoot, float targetRadius, float slowDistance, bool useNavMesh, bool instantBlendToAim, Hash firingPattern)
	{
		TASK::TASK_GO_TO_ENTITY_WHILE_AIMING_AT_COORD(ped, entity, aimX, aimY, aimZ, moveBlendRatio, shoot, targetRadius, slowDistance, useNavMesh, instantBlendToAim, firingPattern);
	}

	static void LUA_NATIVE_TASK_TASK_GO_TO_ENTITY_WHILE_AIMING_AT_ENTITY(Ped ped, Entity entityToWalkTo, Entity entityToAimAt, float speed, bool shootatEntity, float targetRadius, float slowDistance, bool useNavMesh, bool instantBlendToAim, Hash firingPattern)
	{
		TASK::TASK_GO_TO_ENTITY_WHILE_AIMING_AT_ENTITY(ped, entityToWalkTo, entityToAimAt, speed, shootatEntity, targetRadius, slowDistance, useNavMesh, instantBlendToAim, firingPattern);
	}

	static void LUA_NATIVE_TASK_SET_HIGH_FALL_TASK(Ped ped, int minTime, int maxTime, int entryType)
	{
		TASK::SET_HIGH_FALL_TASK(ped, minTime, maxTime, entryType);
	}

	static void LUA_NATIVE_TASK_REQUEST_WAYPOINT_RECORDING(sol::stack_object name)
	{
		TASK::REQUEST_WAYPOINT_RECORDING(name.is<const char*>() ? name.as<const char*>() : nullptr);
	}

	static bool LUA_NATIVE_TASK_GET_IS_WAYPOINT_RECORDING_LOADED(sol::stack_object name)
	{
		auto retval = (bool)TASK::GET_IS_WAYPOINT_RECORDING_LOADED(name.is<const char*>() ? name.as<const char*>() : nullptr);
		return retval;
	}

	static void LUA_NATIVE_TASK_REMOVE_WAYPOINT_RECORDING(sol::stack_object name)
	{
		TASK::REMOVE_WAYPOINT_RECORDING(name.is<const char*>() ? name.as<const char*>() : nullptr);
	}

	static std::tuple<bool, int> LUA_NATIVE_TASK_WAYPOINT_RECORDING_GET_NUM_POINTS(sol::stack_object name, int points)
	{
		std::tuple<bool, int> return_values;
		std::get<0>(return_values) = (bool)TASK::WAYPOINT_RECORDING_GET_NUM_POINTS(name.is<const char*>() ? name.as<const char*>() : nullptr, &points);
		std::get<1>(return_values) = points;

		return return_values;
	}

	static std::tuple<bool, Vector3> LUA_NATIVE_TASK_WAYPOINT_RECORDING_GET_COORD(sol::stack_object name, int point, Vector3 coord)
	{
		std::tuple<bool, Vector3> return_values;
		std::get<0>(return_values) = (bool)TASK::WAYPOINT_RECORDING_GET_COORD(name.is<const char*>() ? name.as<const char*>() : nullptr, point, &coord);
		std::get<1>(return_values) = coord;

		return return_values;
	}

	static float LUA_NATIVE_TASK_WAYPOINT_RECORDING_GET_SPEED_AT_POINT(sol::stack_object name, int point)
	{
		auto retval = TASK::WAYPOINT_RECORDING_GET_SPEED_AT_POINT(name.is<const char*>() ? name.as<const char*>() : nullptr, point);
		return retval;
	}

	static std::tuple<bool, int> LUA_NATIVE_TASK_WAYPOINT_RECORDING_GET_CLOSEST_WAYPOINT(sol::stack_object name, float x, float y, float z, int point)
	{
		std::tuple<bool, int> return_values;
		std::get<0>(return_values) = (bool)TASK::WAYPOINT_RECORDING_GET_CLOSEST_WAYPOINT(name.is<const char*>() ? name.as<const char*>() : nullptr, x, y, z, &point);
		std::get<1>(return_values) = point;

		return return_values;
	}

	static void LUA_NATIVE_TASK_TASK_FOLLOW_WAYPOINT_RECORDING(Ped ped, sol::stack_object name, int p2, int p3, int p4)
	{
		TASK::TASK_FOLLOW_WAYPOINT_RECORDING(ped, name.is<const char*>() ? name.as<const char*>() : nullptr, p2, p3, p4);
	}

	static bool LUA_NATIVE_TASK_IS_WAYPOINT_PLAYBACK_GOING_ON_FOR_PED(Ped ped)
	{
		auto retval = (bool)TASK::IS_WAYPOINT_PLAYBACK_GOING_ON_FOR_PED(ped);
		return retval;
	}

	static int LUA_NATIVE_TASK_GET_PED_WAYPOINT_PROGRESS(Ped ped)
	{
		auto retval = TASK::GET_PED_WAYPOINT_PROGRESS(ped);
		return retval;
	}

	static float LUA_NATIVE_TASK_GET_PED_WAYPOINT_DISTANCE(Any p0)
	{
		auto retval = TASK::GET_PED_WAYPOINT_DISTANCE(p0);
		return retval;
	}

	static bool LUA_NATIVE_TASK_SET_PED_WAYPOINT_ROUTE_OFFSET(Ped ped, float x, float y, float z)
	{
		auto retval = (bool)TASK::SET_PED_WAYPOINT_ROUTE_OFFSET(ped, x, y, z);
		return retval;
	}

	static float LUA_NATIVE_TASK_GET_WAYPOINT_DISTANCE_ALONG_ROUTE(sol::stack_object name, int point)
	{
		auto retval = TASK::GET_WAYPOINT_DISTANCE_ALONG_ROUTE(name.is<const char*>() ? name.as<const char*>() : nullptr, point);
		return retval;
	}

	static bool LUA_NATIVE_TASK_WAYPOINT_PLAYBACK_GET_IS_PAUSED(Any p0)
	{
		auto retval = (bool)TASK::WAYPOINT_PLAYBACK_GET_IS_PAUSED(p0);
		return retval;
	}

	static void LUA_NATIVE_TASK_WAYPOINT_PLAYBACK_PAUSE(Any p0, bool p1, bool p2)
	{
		TASK::WAYPOINT_PLAYBACK_PAUSE(p0, p1, p2);
	}

	static void LUA_NATIVE_TASK_WAYPOINT_PLAYBACK_RESUME(Any p0, bool p1, Any p2, Any p3)
	{
		TASK::WAYPOINT_PLAYBACK_RESUME(p0, p1, p2, p3);
	}

	static void LUA_NATIVE_TASK_WAYPOINT_PLAYBACK_OVERRIDE_SPEED(Any p0, float p1, bool p2)
	{
		TASK::WAYPOINT_PLAYBACK_OVERRIDE_SPEED(p0, p1, p2);
	}

	static void LUA_NATIVE_TASK_WAYPOINT_PLAYBACK_USE_DEFAULT_SPEED(Any p0)
	{
		TASK::WAYPOINT_PLAYBACK_USE_DEFAULT_SPEED(p0);
	}

	static void LUA_NATIVE_TASK_USE_WAYPOINT_RECORDING_AS_ASSISTED_MOVEMENT_ROUTE(sol::stack_object name, bool p1, float p2, float p3)
	{
		TASK::USE_WAYPOINT_RECORDING_AS_ASSISTED_MOVEMENT_ROUTE(name.is<const char*>() ? name.as<const char*>() : nullptr, p1, p2, p3);
	}

	static void LUA_NATIVE_TASK_WAYPOINT_PLAYBACK_START_AIMING_AT_PED(Ped ped, Ped target, bool p2)
	{
		TASK::WAYPOINT_PLAYBACK_START_AIMING_AT_PED(ped, target, p2);
	}

	static void LUA_NATIVE_TASK_WAYPOINT_PLAYBACK_START_AIMING_AT_COORD(Ped ped, float x, float y, float z, bool p4)
	{
		TASK::WAYPOINT_PLAYBACK_START_AIMING_AT_COORD(ped, x, y, z, p4);
	}

	static void LUA_NATIVE_TASK_WAYPOINT_PLAYBACK_START_SHOOTING_AT_PED(Ped ped, Ped ped2, bool p2, bool p3)
	{
		TASK::WAYPOINT_PLAYBACK_START_SHOOTING_AT_PED(ped, ped2, p2, p3);
	}

	static void LUA_NATIVE_TASK_WAYPOINT_PLAYBACK_START_SHOOTING_AT_COORD(Ped ped, float x, float y, float z, bool p4, Hash firingPattern)
	{
		TASK::WAYPOINT_PLAYBACK_START_SHOOTING_AT_COORD(ped, x, y, z, p4, firingPattern);
	}

	static void LUA_NATIVE_TASK_WAYPOINT_PLAYBACK_STOP_AIMING_OR_SHOOTING(Ped ped)
	{
		TASK::WAYPOINT_PLAYBACK_STOP_AIMING_OR_SHOOTING(ped);
	}

	static void LUA_NATIVE_TASK_ASSISTED_MOVEMENT_REQUEST_ROUTE(sol::stack_object route)
	{
		TASK::ASSISTED_MOVEMENT_REQUEST_ROUTE(route.is<const char*>() ? route.as<const char*>() : nullptr);
	}

	static void LUA_NATIVE_TASK_ASSISTED_MOVEMENT_REMOVE_ROUTE(sol::stack_object route)
	{
		TASK::ASSISTED_MOVEMENT_REMOVE_ROUTE(route.is<const char*>() ? route.as<const char*>() : nullptr);
	}

	static bool LUA_NATIVE_TASK_ASSISTED_MOVEMENT_IS_ROUTE_LOADED(sol::stack_object route)
	{
		auto retval = (bool)TASK::ASSISTED_MOVEMENT_IS_ROUTE_LOADED(route.is<const char*>() ? route.as<const char*>() : nullptr);
		return retval;
	}

	static void LUA_NATIVE_TASK_ASSISTED_MOVEMENT_SET_ROUTE_PROPERTIES(sol::stack_object route, int props)
	{
		TASK::ASSISTED_MOVEMENT_SET_ROUTE_PROPERTIES(route.is<const char*>() ? route.as<const char*>() : nullptr, props);
	}

	static void LUA_NATIVE_TASK_ASSISTED_MOVEMENT_OVERRIDE_LOAD_DISTANCE_THIS_FRAME(float dist)
	{
		TASK::ASSISTED_MOVEMENT_OVERRIDE_LOAD_DISTANCE_THIS_FRAME(dist);
	}

	static void LUA_NATIVE_TASK_TASK_VEHICLE_FOLLOW_WAYPOINT_RECORDING(Ped ped, Vehicle vehicle, sol::stack_object WPRecording, int p3, int p4, int p5, int p6, float p7, bool p8, float p9)
	{
		TASK::TASK_VEHICLE_FOLLOW_WAYPOINT_RECORDING(ped, vehicle, WPRecording.is<const char*>() ? WPRecording.as<const char*>() : nullptr, p3, p4, p5, p6, p7, p8, p9);
	}

	static bool LUA_NATIVE_TASK_IS_WAYPOINT_PLAYBACK_GOING_ON_FOR_VEHICLE(Vehicle vehicle)
	{
		auto retval = (bool)TASK::IS_WAYPOINT_PLAYBACK_GOING_ON_FOR_VEHICLE(vehicle);
		return retval;
	}

	static int LUA_NATIVE_TASK_GET_VEHICLE_WAYPOINT_PROGRESS(Vehicle vehicle)
	{
		auto retval = TASK::GET_VEHICLE_WAYPOINT_PROGRESS(vehicle);
		return retval;
	}

	static int LUA_NATIVE_TASK_GET_VEHICLE_WAYPOINT_TARGET_POINT(Vehicle vehicle)
	{
		auto retval = TASK::GET_VEHICLE_WAYPOINT_TARGET_POINT(vehicle);
		return retval;
	}

	static void LUA_NATIVE_TASK_VEHICLE_WAYPOINT_PLAYBACK_PAUSE(Vehicle vehicle)
	{
		TASK::VEHICLE_WAYPOINT_PLAYBACK_PAUSE(vehicle);
	}

	static void LUA_NATIVE_TASK_VEHICLE_WAYPOINT_PLAYBACK_RESUME(Vehicle vehicle)
	{
		TASK::VEHICLE_WAYPOINT_PLAYBACK_RESUME(vehicle);
	}

	static void LUA_NATIVE_TASK_VEHICLE_WAYPOINT_PLAYBACK_USE_DEFAULT_SPEED(Vehicle vehicle)
	{
		TASK::VEHICLE_WAYPOINT_PLAYBACK_USE_DEFAULT_SPEED(vehicle);
	}

	static void LUA_NATIVE_TASK_VEHICLE_WAYPOINT_PLAYBACK_OVERRIDE_SPEED(Vehicle vehicle, float speed)
	{
		TASK::VEHICLE_WAYPOINT_PLAYBACK_OVERRIDE_SPEED(vehicle, speed);
	}

	static void LUA_NATIVE_TASK_TASK_SET_BLOCKING_OF_NON_TEMPORARY_EVENTS(Ped ped, bool toggle)
	{
		TASK::TASK_SET_BLOCKING_OF_NON_TEMPORARY_EVENTS(ped, toggle);
	}

	static void LUA_NATIVE_TASK_TASK_FORCE_MOTION_STATE(Ped ped, Hash state, bool forceRestart)
	{
		TASK::TASK_FORCE_MOTION_STATE(ped, state, forceRestart);
	}

	static void LUA_NATIVE_TASK_TASK_MOVE_NETWORK_BY_NAME(Ped ped, sol::stack_object task, float multiplier, bool allowOverrideCloneUpdate, sol::stack_object animDict, int flags)
	{
		TASK::TASK_MOVE_NETWORK_BY_NAME(ped, task.is<const char*>() ? task.as<const char*>() : nullptr, multiplier, allowOverrideCloneUpdate, animDict.is<const char*>() ? animDict.as<const char*>() : nullptr, flags);
	}

	static void LUA_NATIVE_TASK_TASK_MOVE_NETWORK_ADVANCED_BY_NAME(Ped ped, sol::stack_object network, float x, float y, float z, float rotX, float rotY, float rotZ, int rotOrder, float blendDuration, bool allowOverrideCloneUpdate, sol::stack_object animDict, int flags)
	{
		TASK::TASK_MOVE_NETWORK_ADVANCED_BY_NAME(ped, network.is<const char*>() ? network.as<const char*>() : nullptr, x, y, z, rotX, rotY, rotZ, rotOrder, blendDuration, allowOverrideCloneUpdate, animDict.is<const char*>() ? animDict.as<const char*>() : nullptr, flags);
	}

	static int LUA_NATIVE_TASK_TASK_MOVE_NETWORK_BY_NAME_WITH_INIT_PARAMS(Ped ped, sol::stack_object network, int initialParameters, float blendDuration, bool allowOverrideCloneUpdate, sol::stack_object animDict, int flags)
	{
		TASK::TASK_MOVE_NETWORK_BY_NAME_WITH_INIT_PARAMS(ped, network.is<const char*>() ? network.as<const char*>() : nullptr, &initialParameters, blendDuration, allowOverrideCloneUpdate, animDict.is<const char*>() ? animDict.as<const char*>() : nullptr, flags);
		return initialParameters;
	}

	static int LUA_NATIVE_TASK_TASK_MOVE_NETWORK_ADVANCED_BY_NAME_WITH_INIT_PARAMS(Ped ped, sol::stack_object network, int initialParameters, float x, float y, float z, float rotX, float rotY, float rotZ, int rotOrder, float blendDuration, bool allowOverrideCloneUpdate, sol::stack_object dictionary, int flags)
	{
		TASK::TASK_MOVE_NETWORK_ADVANCED_BY_NAME_WITH_INIT_PARAMS(ped, network.is<const char*>() ? network.as<const char*>() : nullptr, &initialParameters, x, y, z, rotX, rotY, rotZ, rotOrder, blendDuration, allowOverrideCloneUpdate, dictionary.is<const char*>() ? dictionary.as<const char*>() : nullptr, flags);
		return initialParameters;
	}

	static bool LUA_NATIVE_TASK_IS_TASK_MOVE_NETWORK_ACTIVE(Ped ped)
	{
		auto retval = (bool)TASK::IS_TASK_MOVE_NETWORK_ACTIVE(ped);
		return retval;
	}

	static bool LUA_NATIVE_TASK_IS_TASK_MOVE_NETWORK_READY_FOR_TRANSITION(Ped ped)
	{
		auto retval = (bool)TASK::IS_TASK_MOVE_NETWORK_READY_FOR_TRANSITION(ped);
		return retval;
	}

	static bool LUA_NATIVE_TASK_REQUEST_TASK_MOVE_NETWORK_STATE_TRANSITION(Ped ped, sol::stack_object name)
	{
		auto retval = (bool)TASK::REQUEST_TASK_MOVE_NETWORK_STATE_TRANSITION(ped, name.is<const char*>() ? name.as<const char*>() : nullptr);
		return retval;
	}

	static bool LUA_NATIVE_TASK_SET_EXPECTED_CLONE_NEXT_TASK_MOVE_NETWORK_STATE(Ped ped, sol::stack_object state)
	{
		auto retval = (bool)TASK::SET_EXPECTED_CLONE_NEXT_TASK_MOVE_NETWORK_STATE(ped, state.is<const char*>() ? state.as<const char*>() : nullptr);
		return retval;
	}

	static const char* LUA_NATIVE_TASK_GET_TASK_MOVE_NETWORK_STATE(Ped ped)
	{
		auto retval = TASK::GET_TASK_MOVE_NETWORK_STATE(ped);
		return retval;
	}

	static void LUA_NATIVE_TASK_SET_TASK_MOVE_NETWORK_ANIM_SET(Ped ped, Hash clipSet, Hash variableClipSet)
	{
		TASK::SET_TASK_MOVE_NETWORK_ANIM_SET(ped, clipSet, variableClipSet);
	}

	static void LUA_NATIVE_TASK_SET_TASK_MOVE_NETWORK_SIGNAL_FLOAT(Ped ped, sol::stack_object signalName, float value)
	{
		TASK::SET_TASK_MOVE_NETWORK_SIGNAL_FLOAT(ped, signalName.is<const char*>() ? signalName.as<const char*>() : nullptr, value);
	}

	static void LUA_NATIVE_TASK_SET_TASK_MOVE_NETWORK_SIGNAL_LOCAL_FLOAT(Ped ped, sol::stack_object signalName, float value)
	{
		TASK::SET_TASK_MOVE_NETWORK_SIGNAL_LOCAL_FLOAT(ped, signalName.is<const char*>() ? signalName.as<const char*>() : nullptr, value);
	}

	static void LUA_NATIVE_TASK_SET_TASK_MOVE_NETWORK_SIGNAL_FLOAT_LERP_RATE(Ped ped, sol::stack_object signalName, float value)
	{
		TASK::SET_TASK_MOVE_NETWORK_SIGNAL_FLOAT_LERP_RATE(ped, signalName.is<const char*>() ? signalName.as<const char*>() : nullptr, value);
	}

	static void LUA_NATIVE_TASK_SET_TASK_MOVE_NETWORK_SIGNAL_BOOL(Ped ped, sol::stack_object signalName, bool value)
	{
		TASK::SET_TASK_MOVE_NETWORK_SIGNAL_BOOL(ped, signalName.is<const char*>() ? signalName.as<const char*>() : nullptr, value);
	}

	static float LUA_NATIVE_TASK_GET_TASK_MOVE_NETWORK_SIGNAL_FLOAT(Ped ped, sol::stack_object signalName)
	{
		auto retval = TASK::GET_TASK_MOVE_NETWORK_SIGNAL_FLOAT(ped, signalName.is<const char*>() ? signalName.as<const char*>() : nullptr);
		return retval;
	}

	static bool LUA_NATIVE_TASK_GET_TASK_MOVE_NETWORK_SIGNAL_BOOL(Ped ped, sol::stack_object signalName)
	{
		auto retval = (bool)TASK::GET_TASK_MOVE_NETWORK_SIGNAL_BOOL(ped, signalName.is<const char*>() ? signalName.as<const char*>() : nullptr);
		return retval;
	}

	static bool LUA_NATIVE_TASK_GET_TASK_MOVE_NETWORK_EVENT(Ped ped, sol::stack_object eventName)
	{
		auto retval = (bool)TASK::GET_TASK_MOVE_NETWORK_EVENT(ped, eventName.is<const char*>() ? eventName.as<const char*>() : nullptr);
		return retval;
	}

	static bool LUA_NATIVE_TASK_SET_TASK_MOVE_NETWORK_ENABLE_COLLISION_ON_NETWORK_CLONE_WHEN_FIXED(Ped ped, bool enable)
	{
		auto retval = (bool)TASK::SET_TASK_MOVE_NETWORK_ENABLE_COLLISION_ON_NETWORK_CLONE_WHEN_FIXED(ped, enable);
		return retval;
	}

	static void LUA_NATIVE_TASK_SET_SCRIPT_TASK_ENABLE_COLLISION_ON_NETWORK_CLONE_WHEN_FIXED_(Ped ped, bool enable)
	{
		TASK::_SET_SCRIPT_TASK_ENABLE_COLLISION_ON_NETWORK_CLONE_WHEN_FIXED(ped, enable);
	}

	static bool LUA_NATIVE_TASK_IS_MOVE_BLEND_RATIO_STILL(Ped ped)
	{
		auto retval = (bool)TASK::IS_MOVE_BLEND_RATIO_STILL(ped);
		return retval;
	}

	static bool LUA_NATIVE_TASK_IS_MOVE_BLEND_RATIO_WALKING(Ped ped)
	{
		auto retval = (bool)TASK::IS_MOVE_BLEND_RATIO_WALKING(ped);
		return retval;
	}

	static bool LUA_NATIVE_TASK_IS_MOVE_BLEND_RATIO_RUNNING(Ped ped)
	{
		auto retval = (bool)TASK::IS_MOVE_BLEND_RATIO_RUNNING(ped);
		return retval;
	}

	static bool LUA_NATIVE_TASK_IS_MOVE_BLEND_RATIO_SPRINTING(Ped ped)
	{
		auto retval = (bool)TASK::IS_MOVE_BLEND_RATIO_SPRINTING(ped);
		return retval;
	}

	static bool LUA_NATIVE_TASK_IS_PED_STILL(Ped ped)
	{
		auto retval = (bool)TASK::IS_PED_STILL(ped);
		return retval;
	}

	static bool LUA_NATIVE_TASK_IS_PED_WALKING(Ped ped)
	{
		auto retval = (bool)TASK::IS_PED_WALKING(ped);
		return retval;
	}

	static bool LUA_NATIVE_TASK_IS_PED_RUNNING(Ped ped)
	{
		auto retval = (bool)TASK::IS_PED_RUNNING(ped);
		return retval;
	}

	static bool LUA_NATIVE_TASK_IS_PED_SPRINTING(Ped ped)
	{
		auto retval = (bool)TASK::IS_PED_SPRINTING(ped);
		return retval;
	}

	static bool LUA_NATIVE_TASK_IS_PED_STRAFING(Ped ped)
	{
		auto retval = (bool)TASK::IS_PED_STRAFING(ped);
		return retval;
	}

	static void LUA_NATIVE_TASK_TASK_SYNCHRONIZED_SCENE(Ped ped, int scene, sol::stack_object animDictionary, sol::stack_object animationName, float blendIn, float blendOut, int flags, int ragdollBlockingFlags, float moverBlendDelta, int ikFlags)
	{
		TASK::TASK_SYNCHRONIZED_SCENE(ped, scene, animDictionary.is<const char*>() ? animDictionary.as<const char*>() : nullptr, animationName.is<const char*>() ? animationName.as<const char*>() : nullptr, blendIn, blendOut, flags, ragdollBlockingFlags, moverBlendDelta, ikFlags);
	}

	static void LUA_NATIVE_TASK_TASK_AGITATED_ACTION_CONFRONT_RESPONSE(Ped ped, Ped ped2)
	{
		TASK::TASK_AGITATED_ACTION_CONFRONT_RESPONSE(ped, ped2);
	}

	static void LUA_NATIVE_TASK_TASK_SWEEP_AIM_ENTITY(Ped ped, sol::stack_object animDict, sol::stack_object lowAnimName, sol::stack_object medAnimName, sol::stack_object hiAnimName, int runtime, Entity targetEntity, float turnRate, float blendInDuration)
	{
		TASK::TASK_SWEEP_AIM_ENTITY(ped, animDict.is<const char*>() ? animDict.as<const char*>() : nullptr, lowAnimName.is<const char*>() ? lowAnimName.as<const char*>() : nullptr, medAnimName.is<const char*>() ? medAnimName.as<const char*>() : nullptr, hiAnimName.is<const char*>() ? hiAnimName.as<const char*>() : nullptr, runtime, targetEntity, turnRate, blendInDuration);
	}

	static void LUA_NATIVE_TASK_UPDATE_TASK_SWEEP_AIM_ENTITY(Ped ped, Entity entity)
	{
		TASK::UPDATE_TASK_SWEEP_AIM_ENTITY(ped, entity);
	}

	static void LUA_NATIVE_TASK_TASK_SWEEP_AIM_POSITION(Ped ped, sol::stack_object animDict, sol::stack_object lowAnimName, sol::stack_object medAnimName, sol::stack_object hiAnimName, int runtime, float x, float y, float z, float turnRate, float blendInDuration)
	{
		TASK::TASK_SWEEP_AIM_POSITION(ped, animDict.is<const char*>() ? animDict.as<const char*>() : nullptr, lowAnimName.is<const char*>() ? lowAnimName.as<const char*>() : nullptr, medAnimName.is<const char*>() ? medAnimName.as<const char*>() : nullptr, hiAnimName.is<const char*>() ? hiAnimName.as<const char*>() : nullptr, runtime, x, y, z, turnRate, blendInDuration);
	}

	static void LUA_NATIVE_TASK_UPDATE_TASK_SWEEP_AIM_POSITION(Ped ped, float x, float y, float z)
	{
		TASK::UPDATE_TASK_SWEEP_AIM_POSITION(ped, x, y, z);
	}

	static void LUA_NATIVE_TASK_TASK_ARREST_PED(Ped ped, Ped target)
	{
		TASK::TASK_ARREST_PED(ped, target);
	}

	static bool LUA_NATIVE_TASK_IS_PED_RUNNING_ARREST_TASK(Ped ped)
	{
		auto retval = (bool)TASK::IS_PED_RUNNING_ARREST_TASK(ped);
		return retval;
	}

	static bool LUA_NATIVE_TASK_IS_PED_BEING_ARRESTED(Ped ped)
	{
		auto retval = (bool)TASK::IS_PED_BEING_ARRESTED(ped);
		return retval;
	}

	static void LUA_NATIVE_TASK_UNCUFF_PED(Ped ped)
	{
		TASK::UNCUFF_PED(ped);
	}

	static bool LUA_NATIVE_TASK_IS_PED_CUFFED(Ped ped)
	{
		auto retval = (bool)TASK::IS_PED_CUFFED(ped);
		return retval;
	}

	void init_native_binding_TASK(sol::state& L)
	{
		auto TASK = L["TASK"].get_or_create<sol::table>();
		TASK.set_function("TASK_PAUSE", LUA_NATIVE_TASK_TASK_PAUSE);
		TASK.set_function("TASK_STAND_STILL", LUA_NATIVE_TASK_TASK_STAND_STILL);
		TASK.set_function("TASK_JUMP", LUA_NATIVE_TASK_TASK_JUMP);
		TASK.set_function("TASK_COWER", LUA_NATIVE_TASK_TASK_COWER);
		TASK.set_function("TASK_HANDS_UP", LUA_NATIVE_TASK_TASK_HANDS_UP);
		TASK.set_function("UPDATE_TASK_HANDS_UP_DURATION", LUA_NATIVE_TASK_UPDATE_TASK_HANDS_UP_DURATION);
		TASK.set_function("TASK_OPEN_VEHICLE_DOOR", LUA_NATIVE_TASK_TASK_OPEN_VEHICLE_DOOR);
		TASK.set_function("TASK_ENTER_VEHICLE", LUA_NATIVE_TASK_TASK_ENTER_VEHICLE);
		TASK.set_function("TASK_LEAVE_VEHICLE", LUA_NATIVE_TASK_TASK_LEAVE_VEHICLE);
		TASK.set_function("TASK_GET_OFF_BOAT", LUA_NATIVE_TASK_TASK_GET_OFF_BOAT);
		TASK.set_function("TASK_SKY_DIVE", LUA_NATIVE_TASK_TASK_SKY_DIVE);
		TASK.set_function("TASK_PARACHUTE", LUA_NATIVE_TASK_TASK_PARACHUTE);
		TASK.set_function("TASK_PARACHUTE_TO_TARGET", LUA_NATIVE_TASK_TASK_PARACHUTE_TO_TARGET);
		TASK.set_function("SET_PARACHUTE_TASK_TARGET", LUA_NATIVE_TASK_SET_PARACHUTE_TASK_TARGET);
		TASK.set_function("SET_PARACHUTE_TASK_THRUST", LUA_NATIVE_TASK_SET_PARACHUTE_TASK_THRUST);
		TASK.set_function("TASK_RAPPEL_FROM_HELI", LUA_NATIVE_TASK_TASK_RAPPEL_FROM_HELI);
		TASK.set_function("TASK_VEHICLE_DRIVE_TO_COORD", LUA_NATIVE_TASK_TASK_VEHICLE_DRIVE_TO_COORD);
		TASK.set_function("TASK_VEHICLE_DRIVE_TO_COORD_LONGRANGE", LUA_NATIVE_TASK_TASK_VEHICLE_DRIVE_TO_COORD_LONGRANGE);
		TASK.set_function("TASK_VEHICLE_DRIVE_WANDER", LUA_NATIVE_TASK_TASK_VEHICLE_DRIVE_WANDER);
		TASK.set_function("TASK_FOLLOW_TO_OFFSET_OF_ENTITY", LUA_NATIVE_TASK_TASK_FOLLOW_TO_OFFSET_OF_ENTITY);
		TASK.set_function("TASK_GO_STRAIGHT_TO_COORD", LUA_NATIVE_TASK_TASK_GO_STRAIGHT_TO_COORD);
		TASK.set_function("TASK_GO_STRAIGHT_TO_COORD_RELATIVE_TO_ENTITY", LUA_NATIVE_TASK_TASK_GO_STRAIGHT_TO_COORD_RELATIVE_TO_ENTITY);
		TASK.set_function("TASK_ACHIEVE_HEADING", LUA_NATIVE_TASK_TASK_ACHIEVE_HEADING);
		TASK.set_function("TASK_FLUSH_ROUTE", LUA_NATIVE_TASK_TASK_FLUSH_ROUTE);
		TASK.set_function("TASK_EXTEND_ROUTE", LUA_NATIVE_TASK_TASK_EXTEND_ROUTE);
		TASK.set_function("TASK_FOLLOW_POINT_ROUTE", LUA_NATIVE_TASK_TASK_FOLLOW_POINT_ROUTE);
		TASK.set_function("TASK_GO_TO_ENTITY", LUA_NATIVE_TASK_TASK_GO_TO_ENTITY);
		TASK.set_function("TASK_SMART_FLEE_COORD", LUA_NATIVE_TASK_TASK_SMART_FLEE_COORD);
		TASK.set_function("TASK_SMART_FLEE_PED", LUA_NATIVE_TASK_TASK_SMART_FLEE_PED);
		TASK.set_function("TASK_REACT_AND_FLEE_PED", LUA_NATIVE_TASK_TASK_REACT_AND_FLEE_PED);
		TASK.set_function("TASK_SHOCKING_EVENT_REACT", LUA_NATIVE_TASK_TASK_SHOCKING_EVENT_REACT);
		TASK.set_function("TASK_WANDER_IN_AREA", LUA_NATIVE_TASK_TASK_WANDER_IN_AREA);
		TASK.set_function("TASK_WANDER_STANDARD", LUA_NATIVE_TASK_TASK_WANDER_STANDARD);
		TASK.set_function("TASK_WANDER_SPECIFIC", LUA_NATIVE_TASK_TASK_WANDER_SPECIFIC);
		TASK.set_function("TASK_VEHICLE_PARK", LUA_NATIVE_TASK_TASK_VEHICLE_PARK);
		TASK.set_function("TASK_STEALTH_KILL", LUA_NATIVE_TASK_TASK_STEALTH_KILL);
		TASK.set_function("TASK_PLANT_BOMB", LUA_NATIVE_TASK_TASK_PLANT_BOMB);
		TASK.set_function("TASK_FOLLOW_NAV_MESH_TO_COORD", LUA_NATIVE_TASK_TASK_FOLLOW_NAV_MESH_TO_COORD);
		TASK.set_function("TASK_FOLLOW_NAV_MESH_TO_COORD_ADVANCED", LUA_NATIVE_TASK_TASK_FOLLOW_NAV_MESH_TO_COORD_ADVANCED);
		TASK.set_function("SET_PED_PATH_CAN_USE_CLIMBOVERS", LUA_NATIVE_TASK_SET_PED_PATH_CAN_USE_CLIMBOVERS);
		TASK.set_function("SET_PED_PATH_CAN_USE_LADDERS", LUA_NATIVE_TASK_SET_PED_PATH_CAN_USE_LADDERS);
		TASK.set_function("SET_PED_PATH_CAN_DROP_FROM_HEIGHT", LUA_NATIVE_TASK_SET_PED_PATH_CAN_DROP_FROM_HEIGHT);
		TASK.set_function("SET_PED_PATH_CLIMB_COST_MODIFIER", LUA_NATIVE_TASK_SET_PED_PATH_CLIMB_COST_MODIFIER);
		TASK.set_function("SET_PED_PATH_MAY_ENTER_WATER", LUA_NATIVE_TASK_SET_PED_PATH_MAY_ENTER_WATER);
		TASK.set_function("SET_PED_PATH_PREFER_TO_AVOID_WATER", LUA_NATIVE_TASK_SET_PED_PATH_PREFER_TO_AVOID_WATER);
		TASK.set_function("SET_PED_PATH_AVOID_FIRE", LUA_NATIVE_TASK_SET_PED_PATH_AVOID_FIRE);
		TASK.set_function("SET_GLOBAL_MIN_BIRD_FLIGHT_HEIGHT", LUA_NATIVE_TASK_SET_GLOBAL_MIN_BIRD_FLIGHT_HEIGHT);
		TASK.set_function("GET_NAVMESH_ROUTE_DISTANCE_REMAINING", LUA_NATIVE_TASK_GET_NAVMESH_ROUTE_DISTANCE_REMAINING);
		TASK.set_function("GET_NAVMESH_ROUTE_RESULT", LUA_NATIVE_TASK_GET_NAVMESH_ROUTE_RESULT);
		TASK.set_function("IS_CONTROLLED_VEHICLE_UNABLE_TO_GET_TO_ROAD", LUA_NATIVE_TASK_IS_CONTROLLED_VEHICLE_UNABLE_TO_GET_TO_ROAD);
		TASK.set_function("TASK_GO_TO_COORD_ANY_MEANS", LUA_NATIVE_TASK_TASK_GO_TO_COORD_ANY_MEANS);
		TASK.set_function("TASK_GO_TO_COORD_ANY_MEANS_EXTRA_PARAMS", LUA_NATIVE_TASK_TASK_GO_TO_COORD_ANY_MEANS_EXTRA_PARAMS);
		TASK.set_function("TASK_GO_TO_COORD_ANY_MEANS_EXTRA_PARAMS_WITH_CRUISE_SPEED", LUA_NATIVE_TASK_TASK_GO_TO_COORD_ANY_MEANS_EXTRA_PARAMS_WITH_CRUISE_SPEED);
		TASK.set_function("TASK_PLAY_ANIM", LUA_NATIVE_TASK_TASK_PLAY_ANIM);
		TASK.set_function("TASK_PLAY_ANIM_ADVANCED", LUA_NATIVE_TASK_TASK_PLAY_ANIM_ADVANCED);
		TASK.set_function("STOP_ANIM_TASK", LUA_NATIVE_TASK_STOP_ANIM_TASK);
		TASK.set_function("TASK_SCRIPTED_ANIMATION", LUA_NATIVE_TASK_TASK_SCRIPTED_ANIMATION);
		TASK.set_function("PLAY_ENTITY_SCRIPTED_ANIM", LUA_NATIVE_TASK_PLAY_ENTITY_SCRIPTED_ANIM);
		TASK.set_function("STOP_ANIM_PLAYBACK", LUA_NATIVE_TASK_STOP_ANIM_PLAYBACK);
		TASK.set_function("SET_ANIM_WEIGHT", LUA_NATIVE_TASK_SET_ANIM_WEIGHT);
		TASK.set_function("SET_ANIM_PHASE", LUA_NATIVE_TASK_SET_ANIM_PHASE);
		TASK.set_function("SET_ANIM_RATE", LUA_NATIVE_TASK_SET_ANIM_RATE);
		TASK.set_function("SET_ANIM_LOOPED", LUA_NATIVE_TASK_SET_ANIM_LOOPED);
		TASK.set_function("TASK_PLAY_PHONE_GESTURE_ANIMATION", LUA_NATIVE_TASK_TASK_PLAY_PHONE_GESTURE_ANIMATION);
		TASK.set_function("TASK_STOP_PHONE_GESTURE_ANIMATION", LUA_NATIVE_TASK_TASK_STOP_PHONE_GESTURE_ANIMATION);
		TASK.set_function("IS_PLAYING_PHONE_GESTURE_ANIM", LUA_NATIVE_TASK_IS_PLAYING_PHONE_GESTURE_ANIM);
		TASK.set_function("GET_PHONE_GESTURE_ANIM_CURRENT_TIME", LUA_NATIVE_TASK_GET_PHONE_GESTURE_ANIM_CURRENT_TIME);
		TASK.set_function("GET_PHONE_GESTURE_ANIM_TOTAL_TIME", LUA_NATIVE_TASK_GET_PHONE_GESTURE_ANIM_TOTAL_TIME);
		TASK.set_function("TASK_VEHICLE_PLAY_ANIM", LUA_NATIVE_TASK_TASK_VEHICLE_PLAY_ANIM);
		TASK.set_function("TASK_LOOK_AT_COORD", LUA_NATIVE_TASK_TASK_LOOK_AT_COORD);
		TASK.set_function("TASK_LOOK_AT_ENTITY", LUA_NATIVE_TASK_TASK_LOOK_AT_ENTITY);
		TASK.set_function("TASK_CLEAR_LOOK_AT", LUA_NATIVE_TASK_TASK_CLEAR_LOOK_AT);
		TASK.set_function("OPEN_SEQUENCE_TASK", LUA_NATIVE_TASK_OPEN_SEQUENCE_TASK);
		TASK.set_function("CLOSE_SEQUENCE_TASK", LUA_NATIVE_TASK_CLOSE_SEQUENCE_TASK);
		TASK.set_function("TASK_PERFORM_SEQUENCE", LUA_NATIVE_TASK_TASK_PERFORM_SEQUENCE);
		TASK.set_function("TASK_PERFORM_SEQUENCE_LOCALLY", LUA_NATIVE_TASK_TASK_PERFORM_SEQUENCE_LOCALLY);
		TASK.set_function("CLEAR_SEQUENCE_TASK", LUA_NATIVE_TASK_CLEAR_SEQUENCE_TASK);
		TASK.set_function("SET_SEQUENCE_TO_REPEAT", LUA_NATIVE_TASK_SET_SEQUENCE_TO_REPEAT);
		TASK.set_function("GET_SEQUENCE_PROGRESS", LUA_NATIVE_TASK_GET_SEQUENCE_PROGRESS);
		TASK.set_function("GET_IS_TASK_ACTIVE", LUA_NATIVE_TASK_GET_IS_TASK_ACTIVE);
		TASK.set_function("GET_SCRIPT_TASK_STATUS", LUA_NATIVE_TASK_GET_SCRIPT_TASK_STATUS);
		TASK.set_function("GET_ACTIVE_VEHICLE_MISSION_TYPE", LUA_NATIVE_TASK_GET_ACTIVE_VEHICLE_MISSION_TYPE);
		TASK.set_function("TASK_LEAVE_ANY_VEHICLE", LUA_NATIVE_TASK_TASK_LEAVE_ANY_VEHICLE);
		TASK.set_function("TASK_AIM_GUN_SCRIPTED", LUA_NATIVE_TASK_TASK_AIM_GUN_SCRIPTED);
		TASK.set_function("TASK_AIM_GUN_SCRIPTED_WITH_TARGET", LUA_NATIVE_TASK_TASK_AIM_GUN_SCRIPTED_WITH_TARGET);
		TASK.set_function("UPDATE_TASK_AIM_GUN_SCRIPTED_TARGET", LUA_NATIVE_TASK_UPDATE_TASK_AIM_GUN_SCRIPTED_TARGET);
		TASK.set_function("GET_CLIP_SET_FOR_SCRIPTED_GUN_TASK", LUA_NATIVE_TASK_GET_CLIP_SET_FOR_SCRIPTED_GUN_TASK);
		TASK.set_function("TASK_AIM_GUN_AT_ENTITY", LUA_NATIVE_TASK_TASK_AIM_GUN_AT_ENTITY);
		TASK.set_function("TASK_TURN_PED_TO_FACE_ENTITY", LUA_NATIVE_TASK_TASK_TURN_PED_TO_FACE_ENTITY);
		TASK.set_function("TASK_AIM_GUN_AT_COORD", LUA_NATIVE_TASK_TASK_AIM_GUN_AT_COORD);
		TASK.set_function("TASK_SHOOT_AT_COORD", LUA_NATIVE_TASK_TASK_SHOOT_AT_COORD);
		TASK.set_function("TASK_SHUFFLE_TO_NEXT_VEHICLE_SEAT", LUA_NATIVE_TASK_TASK_SHUFFLE_TO_NEXT_VEHICLE_SEAT);
		TASK.set_function("CLEAR_PED_TASKS", LUA_NATIVE_TASK_CLEAR_PED_TASKS);
		TASK.set_function("CLEAR_PED_SECONDARY_TASK", LUA_NATIVE_TASK_CLEAR_PED_SECONDARY_TASK);
		TASK.set_function("TASK_EVERYONE_LEAVE_VEHICLE", LUA_NATIVE_TASK_TASK_EVERYONE_LEAVE_VEHICLE);
		TASK.set_function("TASK_GOTO_ENTITY_OFFSET", LUA_NATIVE_TASK_TASK_GOTO_ENTITY_OFFSET);
		TASK.set_function("TASK_GOTO_ENTITY_OFFSET_XY", LUA_NATIVE_TASK_TASK_GOTO_ENTITY_OFFSET_XY);
		TASK.set_function("TASK_TURN_PED_TO_FACE_COORD", LUA_NATIVE_TASK_TASK_TURN_PED_TO_FACE_COORD);
		TASK.set_function("TASK_VEHICLE_TEMP_ACTION", LUA_NATIVE_TASK_TASK_VEHICLE_TEMP_ACTION);
		TASK.set_function("TASK_VEHICLE_MISSION", LUA_NATIVE_TASK_TASK_VEHICLE_MISSION);
		TASK.set_function("TASK_VEHICLE_MISSION_PED_TARGET", LUA_NATIVE_TASK_TASK_VEHICLE_MISSION_PED_TARGET);
		TASK.set_function("TASK_VEHICLE_MISSION_COORS_TARGET", LUA_NATIVE_TASK_TASK_VEHICLE_MISSION_COORS_TARGET);
		TASK.set_function("TASK_VEHICLE_ESCORT", LUA_NATIVE_TASK_TASK_VEHICLE_ESCORT);
		TASK.set_function("TASK_VEHICLE_FOLLOW", LUA_NATIVE_TASK_TASK_VEHICLE_FOLLOW);
		TASK.set_function("TASK_VEHICLE_CHASE", LUA_NATIVE_TASK_TASK_VEHICLE_CHASE);
		TASK.set_function("TASK_VEHICLE_HELI_PROTECT", LUA_NATIVE_TASK_TASK_VEHICLE_HELI_PROTECT);
		TASK.set_function("SET_TASK_VEHICLE_CHASE_BEHAVIOR_FLAG", LUA_NATIVE_TASK_SET_TASK_VEHICLE_CHASE_BEHAVIOR_FLAG);
		TASK.set_function("SET_TASK_VEHICLE_CHASE_IDEAL_PURSUIT_DISTANCE", LUA_NATIVE_TASK_SET_TASK_VEHICLE_CHASE_IDEAL_PURSUIT_DISTANCE);
		TASK.set_function("TASK_HELI_CHASE", LUA_NATIVE_TASK_TASK_HELI_CHASE);
		TASK.set_function("TASK_PLANE_CHASE", LUA_NATIVE_TASK_TASK_PLANE_CHASE);
		TASK.set_function("TASK_PLANE_LAND", LUA_NATIVE_TASK_TASK_PLANE_LAND);
		TASK.set_function("CLEAR_DEFAULT_PRIMARY_TASK", LUA_NATIVE_TASK_CLEAR_DEFAULT_PRIMARY_TASK);
		TASK.set_function("CLEAR_PRIMARY_VEHICLE_TASK", LUA_NATIVE_TASK_CLEAR_PRIMARY_VEHICLE_TASK);
		TASK.set_function("CLEAR_VEHICLE_CRASH_TASK", LUA_NATIVE_TASK_CLEAR_VEHICLE_CRASH_TASK);
		TASK.set_function("TASK_PLANE_GOTO_PRECISE_VTOL", LUA_NATIVE_TASK_TASK_PLANE_GOTO_PRECISE_VTOL);
		TASK.set_function("TASK_SUBMARINE_GOTO_AND_STOP", LUA_NATIVE_TASK_TASK_SUBMARINE_GOTO_AND_STOP);
		TASK.set_function("TASK_HELI_MISSION", LUA_NATIVE_TASK_TASK_HELI_MISSION);
		TASK.set_function("TASK_HELI_ESCORT_HELI", LUA_NATIVE_TASK_TASK_HELI_ESCORT_HELI);
		TASK.set_function("TASK_PLANE_MISSION", LUA_NATIVE_TASK_TASK_PLANE_MISSION);
		TASK.set_function("TASK_PLANE_TAXI", LUA_NATIVE_TASK_TASK_PLANE_TAXI);
		TASK.set_function("TASK_BOAT_MISSION", LUA_NATIVE_TASK_TASK_BOAT_MISSION);
		TASK.set_function("TASK_DRIVE_BY", LUA_NATIVE_TASK_TASK_DRIVE_BY);
		TASK.set_function("SET_DRIVEBY_TASK_TARGET", LUA_NATIVE_TASK_SET_DRIVEBY_TASK_TARGET);
		TASK.set_function("CLEAR_DRIVEBY_TASK_UNDERNEATH_DRIVING_TASK", LUA_NATIVE_TASK_CLEAR_DRIVEBY_TASK_UNDERNEATH_DRIVING_TASK);
		TASK.set_function("IS_DRIVEBY_TASK_UNDERNEATH_DRIVING_TASK", LUA_NATIVE_TASK_IS_DRIVEBY_TASK_UNDERNEATH_DRIVING_TASK);
		TASK.set_function("CONTROL_MOUNTED_WEAPON", LUA_NATIVE_TASK_CONTROL_MOUNTED_WEAPON);
		TASK.set_function("SET_MOUNTED_WEAPON_TARGET", LUA_NATIVE_TASK_SET_MOUNTED_WEAPON_TARGET);
		TASK.set_function("IS_MOUNTED_WEAPON_TASK_UNDERNEATH_DRIVING_TASK", LUA_NATIVE_TASK_IS_MOUNTED_WEAPON_TASK_UNDERNEATH_DRIVING_TASK);
		TASK.set_function("TASK_USE_MOBILE_PHONE", LUA_NATIVE_TASK_TASK_USE_MOBILE_PHONE);
		TASK.set_function("TASK_USE_MOBILE_PHONE_TIMED", LUA_NATIVE_TASK_TASK_USE_MOBILE_PHONE_TIMED);
		TASK.set_function("TASK_CHAT_TO_PED", LUA_NATIVE_TASK_TASK_CHAT_TO_PED);
		TASK.set_function("TASK_WARP_PED_INTO_VEHICLE", LUA_NATIVE_TASK_TASK_WARP_PED_INTO_VEHICLE);
		TASK.set_function("TASK_SHOOT_AT_ENTITY", LUA_NATIVE_TASK_TASK_SHOOT_AT_ENTITY);
		TASK.set_function("TASK_CLIMB", LUA_NATIVE_TASK_TASK_CLIMB);
		TASK.set_function("TASK_CLIMB_LADDER", LUA_NATIVE_TASK_TASK_CLIMB_LADDER);
		TASK.set_function("TASK_RAPPEL_DOWN_WALL_USING_CLIPSET_OVERRIDE", LUA_NATIVE_TASK_TASK_RAPPEL_DOWN_WALL_USING_CLIPSET_OVERRIDE);
		TASK.set_function("GET_TASK_RAPPEL_DOWN_WALL_STATE", LUA_NATIVE_TASK_GET_TASK_RAPPEL_DOWN_WALL_STATE);
		TASK.set_function("CLEAR_PED_TASKS_IMMEDIATELY", LUA_NATIVE_TASK_CLEAR_PED_TASKS_IMMEDIATELY);
		TASK.set_function("TASK_PERFORM_SEQUENCE_FROM_PROGRESS", LUA_NATIVE_TASK_TASK_PERFORM_SEQUENCE_FROM_PROGRESS);
		TASK.set_function("SET_NEXT_DESIRED_MOVE_STATE", LUA_NATIVE_TASK_SET_NEXT_DESIRED_MOVE_STATE);
		TASK.set_function("SET_PED_DESIRED_MOVE_BLEND_RATIO", LUA_NATIVE_TASK_SET_PED_DESIRED_MOVE_BLEND_RATIO);
		TASK.set_function("GET_PED_DESIRED_MOVE_BLEND_RATIO", LUA_NATIVE_TASK_GET_PED_DESIRED_MOVE_BLEND_RATIO);
		TASK.set_function("TASK_GOTO_ENTITY_AIMING", LUA_NATIVE_TASK_TASK_GOTO_ENTITY_AIMING);
		TASK.set_function("TASK_SET_DECISION_MAKER", LUA_NATIVE_TASK_TASK_SET_DECISION_MAKER);
		TASK.set_function("TASK_SET_SPHERE_DEFENSIVE_AREA", LUA_NATIVE_TASK_TASK_SET_SPHERE_DEFENSIVE_AREA);
		TASK.set_function("TASK_CLEAR_DEFENSIVE_AREA", LUA_NATIVE_TASK_TASK_CLEAR_DEFENSIVE_AREA);
		TASK.set_function("TASK_PED_SLIDE_TO_COORD", LUA_NATIVE_TASK_TASK_PED_SLIDE_TO_COORD);
		TASK.set_function("TASK_PED_SLIDE_TO_COORD_HDG_RATE", LUA_NATIVE_TASK_TASK_PED_SLIDE_TO_COORD_HDG_RATE);
		TASK.set_function("ADD_COVER_POINT", LUA_NATIVE_TASK_ADD_COVER_POINT);
		TASK.set_function("REMOVE_COVER_POINT", LUA_NATIVE_TASK_REMOVE_COVER_POINT);
		TASK.set_function("DOES_SCRIPTED_COVER_POINT_EXIST_AT_COORDS", LUA_NATIVE_TASK_DOES_SCRIPTED_COVER_POINT_EXIST_AT_COORDS);
		TASK.set_function("GET_SCRIPTED_COVER_POINT_COORDS", LUA_NATIVE_TASK_GET_SCRIPTED_COVER_POINT_COORDS);
		TASK.set_function("ADD_SCRIPTED_COVER_AREA", LUA_NATIVE_TASK_ADD_SCRIPTED_COVER_AREA);
		TASK.set_function("TASK_COMBAT_PED", LUA_NATIVE_TASK_TASK_COMBAT_PED);
		TASK.set_function("TASK_COMBAT_PED_TIMED", LUA_NATIVE_TASK_TASK_COMBAT_PED_TIMED);
		TASK.set_function("TASK_SEEK_COVER_FROM_POS", LUA_NATIVE_TASK_TASK_SEEK_COVER_FROM_POS);
		TASK.set_function("TASK_SEEK_COVER_FROM_PED", LUA_NATIVE_TASK_TASK_SEEK_COVER_FROM_PED);
		TASK.set_function("TASK_SEEK_COVER_TO_COVER_POINT", LUA_NATIVE_TASK_TASK_SEEK_COVER_TO_COVER_POINT);
		TASK.set_function("TASK_SEEK_COVER_TO_COORDS", LUA_NATIVE_TASK_TASK_SEEK_COVER_TO_COORDS);
		TASK.set_function("TASK_PUT_PED_DIRECTLY_INTO_COVER", LUA_NATIVE_TASK_TASK_PUT_PED_DIRECTLY_INTO_COVER);
		TASK.set_function("TASK_WARP_PED_DIRECTLY_INTO_COVER", LUA_NATIVE_TASK_TASK_WARP_PED_DIRECTLY_INTO_COVER);
		TASK.set_function("TASK_EXIT_COVER", LUA_NATIVE_TASK_TASK_EXIT_COVER);
		TASK.set_function("TASK_PUT_PED_DIRECTLY_INTO_MELEE", LUA_NATIVE_TASK_TASK_PUT_PED_DIRECTLY_INTO_MELEE);
		TASK.set_function("TASK_TOGGLE_DUCK", LUA_NATIVE_TASK_TASK_TOGGLE_DUCK);
		TASK.set_function("TASK_GUARD_CURRENT_POSITION", LUA_NATIVE_TASK_TASK_GUARD_CURRENT_POSITION);
		TASK.set_function("TASK_GUARD_ASSIGNED_DEFENSIVE_AREA", LUA_NATIVE_TASK_TASK_GUARD_ASSIGNED_DEFENSIVE_AREA);
		TASK.set_function("TASK_GUARD_SPHERE_DEFENSIVE_AREA", LUA_NATIVE_TASK_TASK_GUARD_SPHERE_DEFENSIVE_AREA);
		TASK.set_function("TASK_STAND_GUARD", LUA_NATIVE_TASK_TASK_STAND_GUARD);
		TASK.set_function("SET_DRIVE_TASK_CRUISE_SPEED", LUA_NATIVE_TASK_SET_DRIVE_TASK_CRUISE_SPEED);
		TASK.set_function("SET_DRIVE_TASK_MAX_CRUISE_SPEED", LUA_NATIVE_TASK_SET_DRIVE_TASK_MAX_CRUISE_SPEED);
		TASK.set_function("SET_DRIVE_TASK_DRIVING_STYLE", LUA_NATIVE_TASK_SET_DRIVE_TASK_DRIVING_STYLE);
		TASK.set_function("ADD_COVER_BLOCKING_AREA", LUA_NATIVE_TASK_ADD_COVER_BLOCKING_AREA);
		TASK.set_function("REMOVE_ALL_COVER_BLOCKING_AREAS", LUA_NATIVE_TASK_REMOVE_ALL_COVER_BLOCKING_AREAS);
		TASK.set_function("REMOVE_COVER_BLOCKING_AREAS_AT_POSITION", LUA_NATIVE_TASK_REMOVE_COVER_BLOCKING_AREAS_AT_POSITION);
		TASK.set_function("REMOVE_SPECIFIC_COVER_BLOCKING_AREAS", LUA_NATIVE_TASK_REMOVE_SPECIFIC_COVER_BLOCKING_AREAS);
		TASK.set_function("TASK_START_SCENARIO_IN_PLACE", LUA_NATIVE_TASK_TASK_START_SCENARIO_IN_PLACE);
		TASK.set_function("TASK_START_SCENARIO_AT_POSITION", LUA_NATIVE_TASK_TASK_START_SCENARIO_AT_POSITION);
		TASK.set_function("TASK_USE_NEAREST_SCENARIO_TO_COORD", LUA_NATIVE_TASK_TASK_USE_NEAREST_SCENARIO_TO_COORD);
		TASK.set_function("TASK_USE_NEAREST_SCENARIO_TO_COORD_WARP", LUA_NATIVE_TASK_TASK_USE_NEAREST_SCENARIO_TO_COORD_WARP);
		TASK.set_function("TASK_USE_NEAREST_SCENARIO_CHAIN_TO_COORD", LUA_NATIVE_TASK_TASK_USE_NEAREST_SCENARIO_CHAIN_TO_COORD);
		TASK.set_function("TASK_USE_NEAREST_SCENARIO_CHAIN_TO_COORD_WARP", LUA_NATIVE_TASK_TASK_USE_NEAREST_SCENARIO_CHAIN_TO_COORD_WARP);
		TASK.set_function("DOES_SCENARIO_EXIST_IN_AREA", LUA_NATIVE_TASK_DOES_SCENARIO_EXIST_IN_AREA);
		TASK.set_function("DOES_SCENARIO_OF_TYPE_EXIST_IN_AREA", LUA_NATIVE_TASK_DOES_SCENARIO_OF_TYPE_EXIST_IN_AREA);
		TASK.set_function("IS_SCENARIO_OCCUPIED", LUA_NATIVE_TASK_IS_SCENARIO_OCCUPIED);
		TASK.set_function("PED_HAS_USE_SCENARIO_TASK", LUA_NATIVE_TASK_PED_HAS_USE_SCENARIO_TASK);
		TASK.set_function("PLAY_ANIM_ON_RUNNING_SCENARIO", LUA_NATIVE_TASK_PLAY_ANIM_ON_RUNNING_SCENARIO);
		TASK.set_function("DOES_SCENARIO_GROUP_EXIST", LUA_NATIVE_TASK_DOES_SCENARIO_GROUP_EXIST);
		TASK.set_function("IS_SCENARIO_GROUP_ENABLED", LUA_NATIVE_TASK_IS_SCENARIO_GROUP_ENABLED);
		TASK.set_function("SET_SCENARIO_GROUP_ENABLED", LUA_NATIVE_TASK_SET_SCENARIO_GROUP_ENABLED);
		TASK.set_function("RESET_SCENARIO_GROUPS_ENABLED", LUA_NATIVE_TASK_RESET_SCENARIO_GROUPS_ENABLED);
		TASK.set_function("SET_EXCLUSIVE_SCENARIO_GROUP", LUA_NATIVE_TASK_SET_EXCLUSIVE_SCENARIO_GROUP);
		TASK.set_function("RESET_EXCLUSIVE_SCENARIO_GROUP", LUA_NATIVE_TASK_RESET_EXCLUSIVE_SCENARIO_GROUP);
		TASK.set_function("IS_SCENARIO_TYPE_ENABLED", LUA_NATIVE_TASK_IS_SCENARIO_TYPE_ENABLED);
		TASK.set_function("SET_SCENARIO_TYPE_ENABLED", LUA_NATIVE_TASK_SET_SCENARIO_TYPE_ENABLED);
		TASK.set_function("RESET_SCENARIO_TYPES_ENABLED", LUA_NATIVE_TASK_RESET_SCENARIO_TYPES_ENABLED);
		TASK.set_function("IS_PED_ACTIVE_IN_SCENARIO", LUA_NATIVE_TASK_IS_PED_ACTIVE_IN_SCENARIO);
		TASK.set_function("IS_PED_PLAYING_BASE_CLIP_IN_SCENARIO", LUA_NATIVE_TASK_IS_PED_PLAYING_BASE_CLIP_IN_SCENARIO);
		TASK.set_function("SET_PED_CAN_PLAY_AMBIENT_IDLES", LUA_NATIVE_TASK_SET_PED_CAN_PLAY_AMBIENT_IDLES);
		TASK.set_function("TASK_COMBAT_HATED_TARGETS_IN_AREA", LUA_NATIVE_TASK_TASK_COMBAT_HATED_TARGETS_IN_AREA);
		TASK.set_function("TASK_COMBAT_HATED_TARGETS_AROUND_PED", LUA_NATIVE_TASK_TASK_COMBAT_HATED_TARGETS_AROUND_PED);
		TASK.set_function("TASK_COMBAT_HATED_TARGETS_AROUND_PED_TIMED", LUA_NATIVE_TASK_TASK_COMBAT_HATED_TARGETS_AROUND_PED_TIMED);
		TASK.set_function("TASK_THROW_PROJECTILE", LUA_NATIVE_TASK_TASK_THROW_PROJECTILE);
		TASK.set_function("TASK_SWAP_WEAPON", LUA_NATIVE_TASK_TASK_SWAP_WEAPON);
		TASK.set_function("TASK_RELOAD_WEAPON", LUA_NATIVE_TASK_TASK_RELOAD_WEAPON);
		TASK.set_function("IS_PED_GETTING_UP", LUA_NATIVE_TASK_IS_PED_GETTING_UP);
		TASK.set_function("TASK_WRITHE", LUA_NATIVE_TASK_TASK_WRITHE);
		TASK.set_function("IS_PED_IN_WRITHE", LUA_NATIVE_TASK_IS_PED_IN_WRITHE);
		TASK.set_function("OPEN_PATROL_ROUTE", LUA_NATIVE_TASK_OPEN_PATROL_ROUTE);
		TASK.set_function("CLOSE_PATROL_ROUTE", LUA_NATIVE_TASK_CLOSE_PATROL_ROUTE);
		TASK.set_function("ADD_PATROL_ROUTE_NODE", LUA_NATIVE_TASK_ADD_PATROL_ROUTE_NODE);
		TASK.set_function("ADD_PATROL_ROUTE_LINK", LUA_NATIVE_TASK_ADD_PATROL_ROUTE_LINK);
		TASK.set_function("CREATE_PATROL_ROUTE", LUA_NATIVE_TASK_CREATE_PATROL_ROUTE);
		TASK.set_function("DELETE_PATROL_ROUTE", LUA_NATIVE_TASK_DELETE_PATROL_ROUTE);
		TASK.set_function("GET_PATROL_TASK_INFO", LUA_NATIVE_TASK_GET_PATROL_TASK_INFO);
		TASK.set_function("TASK_PATROL", LUA_NATIVE_TASK_TASK_PATROL);
		TASK.set_function("TASK_STAY_IN_COVER", LUA_NATIVE_TASK_TASK_STAY_IN_COVER);
		TASK.set_function("ADD_VEHICLE_SUBTASK_ATTACK_COORD", LUA_NATIVE_TASK_ADD_VEHICLE_SUBTASK_ATTACK_COORD);
		TASK.set_function("ADD_VEHICLE_SUBTASK_ATTACK_PED", LUA_NATIVE_TASK_ADD_VEHICLE_SUBTASK_ATTACK_PED);
		TASK.set_function("TASK_VEHICLE_SHOOT_AT_PED", LUA_NATIVE_TASK_TASK_VEHICLE_SHOOT_AT_PED);
		TASK.set_function("TASK_VEHICLE_AIM_AT_PED", LUA_NATIVE_TASK_TASK_VEHICLE_AIM_AT_PED);
		TASK.set_function("TASK_VEHICLE_SHOOT_AT_COORD", LUA_NATIVE_TASK_TASK_VEHICLE_SHOOT_AT_COORD);
		TASK.set_function("TASK_VEHICLE_AIM_AT_COORD", LUA_NATIVE_TASK_TASK_VEHICLE_AIM_AT_COORD);
		TASK.set_function("TASK_VEHICLE_GOTO_NAVMESH", LUA_NATIVE_TASK_TASK_VEHICLE_GOTO_NAVMESH);
		TASK.set_function("TASK_GO_TO_COORD_WHILE_AIMING_AT_COORD", LUA_NATIVE_TASK_TASK_GO_TO_COORD_WHILE_AIMING_AT_COORD);
		TASK.set_function("TASK_GO_TO_COORD_WHILE_AIMING_AT_ENTITY", LUA_NATIVE_TASK_TASK_GO_TO_COORD_WHILE_AIMING_AT_ENTITY);
		TASK.set_function("TASK_GO_TO_COORD_AND_AIM_AT_HATED_ENTITIES_NEAR_COORD", LUA_NATIVE_TASK_TASK_GO_TO_COORD_AND_AIM_AT_HATED_ENTITIES_NEAR_COORD);
		TASK.set_function("TASK_GO_TO_ENTITY_WHILE_AIMING_AT_COORD", LUA_NATIVE_TASK_TASK_GO_TO_ENTITY_WHILE_AIMING_AT_COORD);
		TASK.set_function("TASK_GO_TO_ENTITY_WHILE_AIMING_AT_ENTITY", LUA_NATIVE_TASK_TASK_GO_TO_ENTITY_WHILE_AIMING_AT_ENTITY);
		TASK.set_function("SET_HIGH_FALL_TASK", LUA_NATIVE_TASK_SET_HIGH_FALL_TASK);
		TASK.set_function("REQUEST_WAYPOINT_RECORDING", LUA_NATIVE_TASK_REQUEST_WAYPOINT_RECORDING);
		TASK.set_function("GET_IS_WAYPOINT_RECORDING_LOADED", LUA_NATIVE_TASK_GET_IS_WAYPOINT_RECORDING_LOADED);
		TASK.set_function("REMOVE_WAYPOINT_RECORDING", LUA_NATIVE_TASK_REMOVE_WAYPOINT_RECORDING);
		TASK.set_function("WAYPOINT_RECORDING_GET_NUM_POINTS", LUA_NATIVE_TASK_WAYPOINT_RECORDING_GET_NUM_POINTS);
		TASK.set_function("WAYPOINT_RECORDING_GET_COORD", LUA_NATIVE_TASK_WAYPOINT_RECORDING_GET_COORD);
		TASK.set_function("WAYPOINT_RECORDING_GET_SPEED_AT_POINT", LUA_NATIVE_TASK_WAYPOINT_RECORDING_GET_SPEED_AT_POINT);
		TASK.set_function("WAYPOINT_RECORDING_GET_CLOSEST_WAYPOINT", LUA_NATIVE_TASK_WAYPOINT_RECORDING_GET_CLOSEST_WAYPOINT);
		TASK.set_function("TASK_FOLLOW_WAYPOINT_RECORDING", LUA_NATIVE_TASK_TASK_FOLLOW_WAYPOINT_RECORDING);
		TASK.set_function("IS_WAYPOINT_PLAYBACK_GOING_ON_FOR_PED", LUA_NATIVE_TASK_IS_WAYPOINT_PLAYBACK_GOING_ON_FOR_PED);
		TASK.set_function("GET_PED_WAYPOINT_PROGRESS", LUA_NATIVE_TASK_GET_PED_WAYPOINT_PROGRESS);
		TASK.set_function("GET_PED_WAYPOINT_DISTANCE", LUA_NATIVE_TASK_GET_PED_WAYPOINT_DISTANCE);
		TASK.set_function("SET_PED_WAYPOINT_ROUTE_OFFSET", LUA_NATIVE_TASK_SET_PED_WAYPOINT_ROUTE_OFFSET);
		TASK.set_function("GET_WAYPOINT_DISTANCE_ALONG_ROUTE", LUA_NATIVE_TASK_GET_WAYPOINT_DISTANCE_ALONG_ROUTE);
		TASK.set_function("WAYPOINT_PLAYBACK_GET_IS_PAUSED", LUA_NATIVE_TASK_WAYPOINT_PLAYBACK_GET_IS_PAUSED);
		TASK.set_function("WAYPOINT_PLAYBACK_PAUSE", LUA_NATIVE_TASK_WAYPOINT_PLAYBACK_PAUSE);
		TASK.set_function("WAYPOINT_PLAYBACK_RESUME", LUA_NATIVE_TASK_WAYPOINT_PLAYBACK_RESUME);
		TASK.set_function("WAYPOINT_PLAYBACK_OVERRIDE_SPEED", LUA_NATIVE_TASK_WAYPOINT_PLAYBACK_OVERRIDE_SPEED);
		TASK.set_function("WAYPOINT_PLAYBACK_USE_DEFAULT_SPEED", LUA_NATIVE_TASK_WAYPOINT_PLAYBACK_USE_DEFAULT_SPEED);
		TASK.set_function("USE_WAYPOINT_RECORDING_AS_ASSISTED_MOVEMENT_ROUTE", LUA_NATIVE_TASK_USE_WAYPOINT_RECORDING_AS_ASSISTED_MOVEMENT_ROUTE);
		TASK.set_function("WAYPOINT_PLAYBACK_START_AIMING_AT_PED", LUA_NATIVE_TASK_WAYPOINT_PLAYBACK_START_AIMING_AT_PED);
		TASK.set_function("WAYPOINT_PLAYBACK_START_AIMING_AT_COORD", LUA_NATIVE_TASK_WAYPOINT_PLAYBACK_START_AIMING_AT_COORD);
		TASK.set_function("WAYPOINT_PLAYBACK_START_SHOOTING_AT_PED", LUA_NATIVE_TASK_WAYPOINT_PLAYBACK_START_SHOOTING_AT_PED);
		TASK.set_function("WAYPOINT_PLAYBACK_START_SHOOTING_AT_COORD", LUA_NATIVE_TASK_WAYPOINT_PLAYBACK_START_SHOOTING_AT_COORD);
		TASK.set_function("WAYPOINT_PLAYBACK_STOP_AIMING_OR_SHOOTING", LUA_NATIVE_TASK_WAYPOINT_PLAYBACK_STOP_AIMING_OR_SHOOTING);
		TASK.set_function("ASSISTED_MOVEMENT_REQUEST_ROUTE", LUA_NATIVE_TASK_ASSISTED_MOVEMENT_REQUEST_ROUTE);
		TASK.set_function("ASSISTED_MOVEMENT_REMOVE_ROUTE", LUA_NATIVE_TASK_ASSISTED_MOVEMENT_REMOVE_ROUTE);
		TASK.set_function("ASSISTED_MOVEMENT_IS_ROUTE_LOADED", LUA_NATIVE_TASK_ASSISTED_MOVEMENT_IS_ROUTE_LOADED);
		TASK.set_function("ASSISTED_MOVEMENT_SET_ROUTE_PROPERTIES", LUA_NATIVE_TASK_ASSISTED_MOVEMENT_SET_ROUTE_PROPERTIES);
		TASK.set_function("ASSISTED_MOVEMENT_OVERRIDE_LOAD_DISTANCE_THIS_FRAME", LUA_NATIVE_TASK_ASSISTED_MOVEMENT_OVERRIDE_LOAD_DISTANCE_THIS_FRAME);
		TASK.set_function("TASK_VEHICLE_FOLLOW_WAYPOINT_RECORDING", LUA_NATIVE_TASK_TASK_VEHICLE_FOLLOW_WAYPOINT_RECORDING);
		TASK.set_function("IS_WAYPOINT_PLAYBACK_GOING_ON_FOR_VEHICLE", LUA_NATIVE_TASK_IS_WAYPOINT_PLAYBACK_GOING_ON_FOR_VEHICLE);
		TASK.set_function("GET_VEHICLE_WAYPOINT_PROGRESS", LUA_NATIVE_TASK_GET_VEHICLE_WAYPOINT_PROGRESS);
		TASK.set_function("GET_VEHICLE_WAYPOINT_TARGET_POINT", LUA_NATIVE_TASK_GET_VEHICLE_WAYPOINT_TARGET_POINT);
		TASK.set_function("VEHICLE_WAYPOINT_PLAYBACK_PAUSE", LUA_NATIVE_TASK_VEHICLE_WAYPOINT_PLAYBACK_PAUSE);
		TASK.set_function("VEHICLE_WAYPOINT_PLAYBACK_RESUME", LUA_NATIVE_TASK_VEHICLE_WAYPOINT_PLAYBACK_RESUME);
		TASK.set_function("VEHICLE_WAYPOINT_PLAYBACK_USE_DEFAULT_SPEED", LUA_NATIVE_TASK_VEHICLE_WAYPOINT_PLAYBACK_USE_DEFAULT_SPEED);
		TASK.set_function("VEHICLE_WAYPOINT_PLAYBACK_OVERRIDE_SPEED", LUA_NATIVE_TASK_VEHICLE_WAYPOINT_PLAYBACK_OVERRIDE_SPEED);
		TASK.set_function("TASK_SET_BLOCKING_OF_NON_TEMPORARY_EVENTS", LUA_NATIVE_TASK_TASK_SET_BLOCKING_OF_NON_TEMPORARY_EVENTS);
		TASK.set_function("TASK_FORCE_MOTION_STATE", LUA_NATIVE_TASK_TASK_FORCE_MOTION_STATE);
		TASK.set_function("TASK_MOVE_NETWORK_BY_NAME", LUA_NATIVE_TASK_TASK_MOVE_NETWORK_BY_NAME);
		TASK.set_function("TASK_MOVE_NETWORK_ADVANCED_BY_NAME", LUA_NATIVE_TASK_TASK_MOVE_NETWORK_ADVANCED_BY_NAME);
		TASK.set_function("TASK_MOVE_NETWORK_BY_NAME_WITH_INIT_PARAMS", LUA_NATIVE_TASK_TASK_MOVE_NETWORK_BY_NAME_WITH_INIT_PARAMS);
		TASK.set_function("TASK_MOVE_NETWORK_ADVANCED_BY_NAME_WITH_INIT_PARAMS", LUA_NATIVE_TASK_TASK_MOVE_NETWORK_ADVANCED_BY_NAME_WITH_INIT_PARAMS);
		TASK.set_function("IS_TASK_MOVE_NETWORK_ACTIVE", LUA_NATIVE_TASK_IS_TASK_MOVE_NETWORK_ACTIVE);
		TASK.set_function("IS_TASK_MOVE_NETWORK_READY_FOR_TRANSITION", LUA_NATIVE_TASK_IS_TASK_MOVE_NETWORK_READY_FOR_TRANSITION);
		TASK.set_function("REQUEST_TASK_MOVE_NETWORK_STATE_TRANSITION", LUA_NATIVE_TASK_REQUEST_TASK_MOVE_NETWORK_STATE_TRANSITION);
		TASK.set_function("SET_EXPECTED_CLONE_NEXT_TASK_MOVE_NETWORK_STATE", LUA_NATIVE_TASK_SET_EXPECTED_CLONE_NEXT_TASK_MOVE_NETWORK_STATE);
		TASK.set_function("GET_TASK_MOVE_NETWORK_STATE", LUA_NATIVE_TASK_GET_TASK_MOVE_NETWORK_STATE);
		TASK.set_function("SET_TASK_MOVE_NETWORK_ANIM_SET", LUA_NATIVE_TASK_SET_TASK_MOVE_NETWORK_ANIM_SET);
		TASK.set_function("SET_TASK_MOVE_NETWORK_SIGNAL_FLOAT", LUA_NATIVE_TASK_SET_TASK_MOVE_NETWORK_SIGNAL_FLOAT);
		TASK.set_function("SET_TASK_MOVE_NETWORK_SIGNAL_LOCAL_FLOAT", LUA_NATIVE_TASK_SET_TASK_MOVE_NETWORK_SIGNAL_LOCAL_FLOAT);
		TASK.set_function("SET_TASK_MOVE_NETWORK_SIGNAL_FLOAT_LERP_RATE", LUA_NATIVE_TASK_SET_TASK_MOVE_NETWORK_SIGNAL_FLOAT_LERP_RATE);
		TASK.set_function("SET_TASK_MOVE_NETWORK_SIGNAL_BOOL", LUA_NATIVE_TASK_SET_TASK_MOVE_NETWORK_SIGNAL_BOOL);
		TASK.set_function("GET_TASK_MOVE_NETWORK_SIGNAL_FLOAT", LUA_NATIVE_TASK_GET_TASK_MOVE_NETWORK_SIGNAL_FLOAT);
		TASK.set_function("GET_TASK_MOVE_NETWORK_SIGNAL_BOOL", LUA_NATIVE_TASK_GET_TASK_MOVE_NETWORK_SIGNAL_BOOL);
		TASK.set_function("GET_TASK_MOVE_NETWORK_EVENT", LUA_NATIVE_TASK_GET_TASK_MOVE_NETWORK_EVENT);
		TASK.set_function("SET_TASK_MOVE_NETWORK_ENABLE_COLLISION_ON_NETWORK_CLONE_WHEN_FIXED", LUA_NATIVE_TASK_SET_TASK_MOVE_NETWORK_ENABLE_COLLISION_ON_NETWORK_CLONE_WHEN_FIXED);
		TASK.set_function("SET_SCRIPT_TASK_ENABLE_COLLISION_ON_NETWORK_CLONE_WHEN_FIXED_", LUA_NATIVE_TASK_SET_SCRIPT_TASK_ENABLE_COLLISION_ON_NETWORK_CLONE_WHEN_FIXED_);
		TASK.set_function("IS_MOVE_BLEND_RATIO_STILL", LUA_NATIVE_TASK_IS_MOVE_BLEND_RATIO_STILL);
		TASK.set_function("IS_MOVE_BLEND_RATIO_WALKING", LUA_NATIVE_TASK_IS_MOVE_BLEND_RATIO_WALKING);
		TASK.set_function("IS_MOVE_BLEND_RATIO_RUNNING", LUA_NATIVE_TASK_IS_MOVE_BLEND_RATIO_RUNNING);
		TASK.set_function("IS_MOVE_BLEND_RATIO_SPRINTING", LUA_NATIVE_TASK_IS_MOVE_BLEND_RATIO_SPRINTING);
		TASK.set_function("IS_PED_STILL", LUA_NATIVE_TASK_IS_PED_STILL);
		TASK.set_function("IS_PED_WALKING", LUA_NATIVE_TASK_IS_PED_WALKING);
		TASK.set_function("IS_PED_RUNNING", LUA_NATIVE_TASK_IS_PED_RUNNING);
		TASK.set_function("IS_PED_SPRINTING", LUA_NATIVE_TASK_IS_PED_SPRINTING);
		TASK.set_function("IS_PED_STRAFING", LUA_NATIVE_TASK_IS_PED_STRAFING);
		TASK.set_function("TASK_SYNCHRONIZED_SCENE", LUA_NATIVE_TASK_TASK_SYNCHRONIZED_SCENE);
		TASK.set_function("TASK_AGITATED_ACTION_CONFRONT_RESPONSE", LUA_NATIVE_TASK_TASK_AGITATED_ACTION_CONFRONT_RESPONSE);
		TASK.set_function("TASK_SWEEP_AIM_ENTITY", LUA_NATIVE_TASK_TASK_SWEEP_AIM_ENTITY);
		TASK.set_function("UPDATE_TASK_SWEEP_AIM_ENTITY", LUA_NATIVE_TASK_UPDATE_TASK_SWEEP_AIM_ENTITY);
		TASK.set_function("TASK_SWEEP_AIM_POSITION", LUA_NATIVE_TASK_TASK_SWEEP_AIM_POSITION);
		TASK.set_function("UPDATE_TASK_SWEEP_AIM_POSITION", LUA_NATIVE_TASK_UPDATE_TASK_SWEEP_AIM_POSITION);
		TASK.set_function("TASK_ARREST_PED", LUA_NATIVE_TASK_TASK_ARREST_PED);
		TASK.set_function("IS_PED_RUNNING_ARREST_TASK", LUA_NATIVE_TASK_IS_PED_RUNNING_ARREST_TASK);
		TASK.set_function("IS_PED_BEING_ARRESTED", LUA_NATIVE_TASK_IS_PED_BEING_ARRESTED);
		TASK.set_function("UNCUFF_PED", LUA_NATIVE_TASK_UNCUFF_PED);
		TASK.set_function("IS_PED_CUFFED", LUA_NATIVE_TASK_IS_PED_CUFFED);
	}
}
