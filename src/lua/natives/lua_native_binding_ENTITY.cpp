#include "lua_native_binding.hpp"
#include "natives.hpp"

namespace lua::native
{
	static bool LUA_NATIVE_ENTITY_DOES_ENTITY_EXIST(Entity entity)
	{
		auto retval = (bool)ENTITY::DOES_ENTITY_EXIST(entity);
		return retval;
	}

	static bool LUA_NATIVE_ENTITY_DOES_ENTITY_BELONG_TO_THIS_SCRIPT(Entity entity, bool p1)
	{
		auto retval = (bool)ENTITY::DOES_ENTITY_BELONG_TO_THIS_SCRIPT(entity, p1);
		return retval;
	}

	static bool LUA_NATIVE_ENTITY_DOES_ENTITY_HAVE_DRAWABLE(Entity entity)
	{
		auto retval = (bool)ENTITY::DOES_ENTITY_HAVE_DRAWABLE(entity);
		return retval;
	}

	static bool LUA_NATIVE_ENTITY_DOES_ENTITY_HAVE_PHYSICS(Entity entity)
	{
		auto retval = (bool)ENTITY::DOES_ENTITY_HAVE_PHYSICS(entity);
		return retval;
	}

	static bool LUA_NATIVE_ENTITY_DOES_ENTITY_HAVE_SKELETON(Entity entity)
	{
		auto retval = (bool)ENTITY::DOES_ENTITY_HAVE_SKELETON(entity);
		return retval;
	}

	static bool LUA_NATIVE_ENTITY_DOES_ENTITY_HAVE_ANIM_DIRECTOR(Entity entity)
	{
		auto retval = (bool)ENTITY::DOES_ENTITY_HAVE_ANIM_DIRECTOR(entity);
		return retval;
	}

	static bool LUA_NATIVE_ENTITY_HAS_ENTITY_ANIM_FINISHED(Entity entity, sol::stack_object animDict, sol::stack_object animName, int p3)
	{
		auto retval = (bool)ENTITY::HAS_ENTITY_ANIM_FINISHED(entity, animDict.is<const char*>() ? animDict.as<const char*>() : nullptr, animName.is<const char*>() ? animName.as<const char*>() : nullptr, p3);
		return retval;
	}

	static bool LUA_NATIVE_ENTITY_HAS_ENTITY_BEEN_DAMAGED_BY_ANY_OBJECT(Entity entity)
	{
		auto retval = (bool)ENTITY::HAS_ENTITY_BEEN_DAMAGED_BY_ANY_OBJECT(entity);
		return retval;
	}

	static bool LUA_NATIVE_ENTITY_HAS_ENTITY_BEEN_DAMAGED_BY_ANY_PED(Entity entity)
	{
		auto retval = (bool)ENTITY::HAS_ENTITY_BEEN_DAMAGED_BY_ANY_PED(entity);
		return retval;
	}

	static bool LUA_NATIVE_ENTITY_HAS_ENTITY_BEEN_DAMAGED_BY_ANY_VEHICLE(Entity entity)
	{
		auto retval = (bool)ENTITY::HAS_ENTITY_BEEN_DAMAGED_BY_ANY_VEHICLE(entity);
		return retval;
	}

	static bool LUA_NATIVE_ENTITY_HAS_ENTITY_BEEN_DAMAGED_BY_ENTITY(Entity entity1, Entity entity2, bool p2)
	{
		auto retval = (bool)ENTITY::HAS_ENTITY_BEEN_DAMAGED_BY_ENTITY(entity1, entity2, p2);
		return retval;
	}

	static bool LUA_NATIVE_ENTITY_HAS_ENTITY_CLEAR_LOS_TO_ENTITY(Entity entity1, Entity entity2, int traceType)
	{
		auto retval = (bool)ENTITY::HAS_ENTITY_CLEAR_LOS_TO_ENTITY(entity1, entity2, traceType);
		return retval;
	}

	static bool LUA_NATIVE_ENTITY_HAS_ENTITY_CLEAR_LOS_TO_ENTITY_ADJUST_FOR_COVER(Entity entity1, Entity entity2, int traceType)
	{
		auto retval = (bool)ENTITY::HAS_ENTITY_CLEAR_LOS_TO_ENTITY_ADJUST_FOR_COVER(entity1, entity2, traceType);
		return retval;
	}

	static bool LUA_NATIVE_ENTITY_HAS_ENTITY_CLEAR_LOS_TO_ENTITY_IN_FRONT(Entity entity1, Entity entity2)
	{
		auto retval = (bool)ENTITY::HAS_ENTITY_CLEAR_LOS_TO_ENTITY_IN_FRONT(entity1, entity2);
		return retval;
	}

	static bool LUA_NATIVE_ENTITY_HAS_ENTITY_COLLIDED_WITH_ANYTHING(Entity entity)
	{
		auto retval = (bool)ENTITY::HAS_ENTITY_COLLIDED_WITH_ANYTHING(entity);
		return retval;
	}

	static Entity LUA_NATIVE_ENTITY_GET_LAST_ENTITY_HIT_BY_ENTITY_(Entity entity)
	{
		auto retval = ENTITY::_GET_LAST_ENTITY_HIT_BY_ENTITY(entity);
		return retval;
	}

	static Hash LUA_NATIVE_ENTITY_GET_LAST_MATERIAL_HIT_BY_ENTITY(Entity entity)
	{
		auto retval = ENTITY::GET_LAST_MATERIAL_HIT_BY_ENTITY(entity);
		return retval;
	}

	static Vector3 LUA_NATIVE_ENTITY_GET_COLLISION_NORMAL_OF_LAST_HIT_FOR_ENTITY(Entity entity)
	{
		auto retval = ENTITY::GET_COLLISION_NORMAL_OF_LAST_HIT_FOR_ENTITY(entity);
		return retval;
	}

	static void LUA_NATIVE_ENTITY_FORCE_ENTITY_AI_AND_ANIMATION_UPDATE(Entity entity)
	{
		ENTITY::FORCE_ENTITY_AI_AND_ANIMATION_UPDATE(entity);
	}

	static float LUA_NATIVE_ENTITY_GET_ENTITY_ANIM_CURRENT_TIME(Entity entity, sol::stack_object animDict, sol::stack_object animName)
	{
		auto retval = ENTITY::GET_ENTITY_ANIM_CURRENT_TIME(entity, animDict.is<const char*>() ? animDict.as<const char*>() : nullptr, animName.is<const char*>() ? animName.as<const char*>() : nullptr);
		return retval;
	}

	static float LUA_NATIVE_ENTITY_GET_ENTITY_ANIM_TOTAL_TIME(Entity entity, sol::stack_object animDict, sol::stack_object animName)
	{
		auto retval = ENTITY::GET_ENTITY_ANIM_TOTAL_TIME(entity, animDict.is<const char*>() ? animDict.as<const char*>() : nullptr, animName.is<const char*>() ? animName.as<const char*>() : nullptr);
		return retval;
	}

	static float LUA_NATIVE_ENTITY_GET_ANIM_DURATION(sol::stack_object animDict, sol::stack_object animName)
	{
		auto retval = ENTITY::GET_ANIM_DURATION(animDict.is<const char*>() ? animDict.as<const char*>() : nullptr, animName.is<const char*>() ? animName.as<const char*>() : nullptr);
		return retval;
	}

	static Entity LUA_NATIVE_ENTITY_GET_ENTITY_ATTACHED_TO(Entity entity)
	{
		auto retval = ENTITY::GET_ENTITY_ATTACHED_TO(entity);
		return retval;
	}

	static Vector3 LUA_NATIVE_ENTITY_GET_ENTITY_COORDS(Entity entity, bool alive)
	{
		auto retval = ENTITY::GET_ENTITY_COORDS(entity, alive);
		return retval;
	}

	static Vector3 LUA_NATIVE_ENTITY_GET_ENTITY_FORWARD_VECTOR(Entity entity)
	{
		auto retval = ENTITY::GET_ENTITY_FORWARD_VECTOR(entity);
		return retval;
	}

	static float LUA_NATIVE_ENTITY_GET_ENTITY_FORWARD_X(Entity entity)
	{
		auto retval = ENTITY::GET_ENTITY_FORWARD_X(entity);
		return retval;
	}

	static float LUA_NATIVE_ENTITY_GET_ENTITY_FORWARD_Y(Entity entity)
	{
		auto retval = ENTITY::GET_ENTITY_FORWARD_Y(entity);
		return retval;
	}

	static float LUA_NATIVE_ENTITY_GET_ENTITY_HEADING(Entity entity)
	{
		auto retval = ENTITY::GET_ENTITY_HEADING(entity);
		return retval;
	}

	static float LUA_NATIVE_ENTITY_GET_ENTITY_HEADING_FROM_EULERS(Entity entity)
	{
		auto retval = ENTITY::GET_ENTITY_HEADING_FROM_EULERS(entity);
		return retval;
	}

	static int LUA_NATIVE_ENTITY_GET_ENTITY_HEALTH(Entity entity)
	{
		auto retval = ENTITY::GET_ENTITY_HEALTH(entity);
		return retval;
	}

	static int LUA_NATIVE_ENTITY_GET_ENTITY_MAX_HEALTH(Entity entity)
	{
		auto retval = ENTITY::GET_ENTITY_MAX_HEALTH(entity);
		return retval;
	}

	static void LUA_NATIVE_ENTITY_SET_ENTITY_MAX_HEALTH(Entity entity, int value)
	{
		ENTITY::SET_ENTITY_MAX_HEALTH(entity, value);
	}

	static float LUA_NATIVE_ENTITY_GET_ENTITY_HEIGHT(Entity entity, float X, float Y, float Z, bool atTop, bool inWorldCoords)
	{
		auto retval = ENTITY::GET_ENTITY_HEIGHT(entity, X, Y, Z, atTop, inWorldCoords);
		return retval;
	}

	static float LUA_NATIVE_ENTITY_GET_ENTITY_HEIGHT_ABOVE_GROUND(Entity entity)
	{
		auto retval = ENTITY::GET_ENTITY_HEIGHT_ABOVE_GROUND(entity);
		return retval;
	}

	static std::tuple<Vector3, Vector3, Vector3, Vector3> LUA_NATIVE_ENTITY_GET_ENTITY_MATRIX(Entity entity, Vector3 forwardVector, Vector3 rightVector, Vector3 upVector, Vector3 position)
	{
		std::tuple<Vector3, Vector3, Vector3, Vector3> return_values;
		ENTITY::GET_ENTITY_MATRIX(entity, &forwardVector, &rightVector, &upVector, &position);
		std::get<0>(return_values) = forwardVector;
		std::get<1>(return_values) = rightVector;
		std::get<2>(return_values) = upVector;
		std::get<3>(return_values) = position;

		return return_values;
	}

	static Hash LUA_NATIVE_ENTITY_GET_ENTITY_MODEL(Entity entity)
	{
		auto retval = ENTITY::GET_ENTITY_MODEL(entity);
		return retval;
	}

	static Vector3 LUA_NATIVE_ENTITY_GET_OFFSET_FROM_ENTITY_GIVEN_WORLD_COORDS(Entity entity, float posX, float posY, float posZ)
	{
		auto retval = ENTITY::GET_OFFSET_FROM_ENTITY_GIVEN_WORLD_COORDS(entity, posX, posY, posZ);
		return retval;
	}

	static Vector3 LUA_NATIVE_ENTITY_GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(Entity entity, float offsetX, float offsetY, float offsetZ)
	{
		auto retval = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(entity, offsetX, offsetY, offsetZ);
		return retval;
	}

	static float LUA_NATIVE_ENTITY_GET_ENTITY_PITCH(Entity entity)
	{
		auto retval = ENTITY::GET_ENTITY_PITCH(entity);
		return retval;
	}

	static std::tuple<float, float, float, float> LUA_NATIVE_ENTITY_GET_ENTITY_QUATERNION(Entity entity, float x, float y, float z, float w)
	{
		std::tuple<float, float, float, float> return_values;
		ENTITY::GET_ENTITY_QUATERNION(entity, &x, &y, &z, &w);
		std::get<0>(return_values) = x;
		std::get<1>(return_values) = y;
		std::get<2>(return_values) = z;
		std::get<3>(return_values) = w;

		return return_values;
	}

	static float LUA_NATIVE_ENTITY_GET_ENTITY_ROLL(Entity entity)
	{
		auto retval = ENTITY::GET_ENTITY_ROLL(entity);
		return retval;
	}

	static Vector3 LUA_NATIVE_ENTITY_GET_ENTITY_ROTATION(Entity entity, int rotationOrder)
	{
		auto retval = ENTITY::GET_ENTITY_ROTATION(entity, rotationOrder);
		return retval;
	}

	static Vector3 LUA_NATIVE_ENTITY_GET_ENTITY_ROTATION_VELOCITY(Entity entity)
	{
		auto retval = ENTITY::GET_ENTITY_ROTATION_VELOCITY(entity);
		return retval;
	}

	static std::tuple<const char*, ScrHandle> LUA_NATIVE_ENTITY_GET_ENTITY_SCRIPT(Entity entity, ScrHandle script)
	{
		std::tuple<const char*, ScrHandle> return_values;
		std::get<0>(return_values) = ENTITY::GET_ENTITY_SCRIPT(entity, &script);
		std::get<1>(return_values) = script;

		return return_values;
	}

	static float LUA_NATIVE_ENTITY_GET_ENTITY_SPEED(Entity entity)
	{
		auto retval = ENTITY::GET_ENTITY_SPEED(entity);
		return retval;
	}

	static Vector3 LUA_NATIVE_ENTITY_GET_ENTITY_SPEED_VECTOR(Entity entity, bool relative)
	{
		auto retval = ENTITY::GET_ENTITY_SPEED_VECTOR(entity, relative);
		return retval;
	}

	static float LUA_NATIVE_ENTITY_GET_ENTITY_UPRIGHT_VALUE(Entity entity)
	{
		auto retval = ENTITY::GET_ENTITY_UPRIGHT_VALUE(entity);
		return retval;
	}

	static Vector3 LUA_NATIVE_ENTITY_GET_ENTITY_VELOCITY(Entity entity)
	{
		auto retval = ENTITY::GET_ENTITY_VELOCITY(entity);
		return retval;
	}

	static Object LUA_NATIVE_ENTITY_GET_OBJECT_INDEX_FROM_ENTITY_INDEX(Entity entity)
	{
		auto retval = ENTITY::GET_OBJECT_INDEX_FROM_ENTITY_INDEX(entity);
		return retval;
	}

	static Ped LUA_NATIVE_ENTITY_GET_PED_INDEX_FROM_ENTITY_INDEX(Entity entity)
	{
		auto retval = ENTITY::GET_PED_INDEX_FROM_ENTITY_INDEX(entity);
		return retval;
	}

	static Vehicle LUA_NATIVE_ENTITY_GET_VEHICLE_INDEX_FROM_ENTITY_INDEX(Entity entity)
	{
		auto retval = ENTITY::GET_VEHICLE_INDEX_FROM_ENTITY_INDEX(entity);
		return retval;
	}

	static Vector3 LUA_NATIVE_ENTITY_GET_WORLD_POSITION_OF_ENTITY_BONE(Entity entity, int boneIndex)
	{
		auto retval = ENTITY::GET_WORLD_POSITION_OF_ENTITY_BONE(entity, boneIndex);
		return retval;
	}

	static Player LUA_NATIVE_ENTITY_GET_NEAREST_PLAYER_TO_ENTITY(Entity entity)
	{
		auto retval = ENTITY::GET_NEAREST_PLAYER_TO_ENTITY(entity);
		return retval;
	}

	static Player LUA_NATIVE_ENTITY_GET_NEAREST_PLAYER_TO_ENTITY_ON_TEAM(Entity entity, int team)
	{
		auto retval = ENTITY::GET_NEAREST_PLAYER_TO_ENTITY_ON_TEAM(entity, team);
		return retval;
	}

	static int LUA_NATIVE_ENTITY_GET_NEAREST_PARTICIPANT_TO_ENTITY(Entity entity)
	{
		auto retval = ENTITY::GET_NEAREST_PARTICIPANT_TO_ENTITY(entity);
		return retval;
	}

	static int LUA_NATIVE_ENTITY_GET_ENTITY_TYPE(Entity entity)
	{
		auto retval = ENTITY::GET_ENTITY_TYPE(entity);
		return retval;
	}

	static int LUA_NATIVE_ENTITY_GET_ENTITY_POPULATION_TYPE(Entity entity)
	{
		auto retval = ENTITY::GET_ENTITY_POPULATION_TYPE(entity);
		return retval;
	}

	static bool LUA_NATIVE_ENTITY_IS_AN_ENTITY(ScrHandle handle)
	{
		auto retval = (bool)ENTITY::IS_AN_ENTITY(handle);
		return retval;
	}

	static bool LUA_NATIVE_ENTITY_IS_ENTITY_A_PED(Entity entity)
	{
		auto retval = (bool)ENTITY::IS_ENTITY_A_PED(entity);
		return retval;
	}

	static bool LUA_NATIVE_ENTITY_IS_ENTITY_A_MISSION_ENTITY(Entity entity)
	{
		auto retval = (bool)ENTITY::IS_ENTITY_A_MISSION_ENTITY(entity);
		return retval;
	}

	static bool LUA_NATIVE_ENTITY_IS_ENTITY_A_VEHICLE(Entity entity)
	{
		auto retval = (bool)ENTITY::IS_ENTITY_A_VEHICLE(entity);
		return retval;
	}

	static bool LUA_NATIVE_ENTITY_IS_ENTITY_AN_OBJECT(Entity entity)
	{
		auto retval = (bool)ENTITY::IS_ENTITY_AN_OBJECT(entity);
		return retval;
	}

	static bool LUA_NATIVE_ENTITY_IS_ENTITY_AT_COORD(Entity entity, float xPos, float yPos, float zPos, float xSize, float ySize, float zSize, bool p7, bool p8, int p9)
	{
		auto retval = (bool)ENTITY::IS_ENTITY_AT_COORD(entity, xPos, yPos, zPos, xSize, ySize, zSize, p7, p8, p9);
		return retval;
	}

	static bool LUA_NATIVE_ENTITY_IS_ENTITY_AT_ENTITY(Entity entity1, Entity entity2, float xSize, float ySize, float zSize, bool p5, bool p6, int p7)
	{
		auto retval = (bool)ENTITY::IS_ENTITY_AT_ENTITY(entity1, entity2, xSize, ySize, zSize, p5, p6, p7);
		return retval;
	}

	static bool LUA_NATIVE_ENTITY_IS_ENTITY_ATTACHED(Entity entity)
	{
		auto retval = (bool)ENTITY::IS_ENTITY_ATTACHED(entity);
		return retval;
	}

	static bool LUA_NATIVE_ENTITY_IS_ENTITY_ATTACHED_TO_ANY_OBJECT(Entity entity)
	{
		auto retval = (bool)ENTITY::IS_ENTITY_ATTACHED_TO_ANY_OBJECT(entity);
		return retval;
	}

	static bool LUA_NATIVE_ENTITY_IS_ENTITY_ATTACHED_TO_ANY_PED(Entity entity)
	{
		auto retval = (bool)ENTITY::IS_ENTITY_ATTACHED_TO_ANY_PED(entity);
		return retval;
	}

	static bool LUA_NATIVE_ENTITY_IS_ENTITY_ATTACHED_TO_ANY_VEHICLE(Entity entity)
	{
		auto retval = (bool)ENTITY::IS_ENTITY_ATTACHED_TO_ANY_VEHICLE(entity);
		return retval;
	}

	static bool LUA_NATIVE_ENTITY_IS_ENTITY_ATTACHED_TO_ENTITY(Entity from, Entity to)
	{
		auto retval = (bool)ENTITY::IS_ENTITY_ATTACHED_TO_ENTITY(from, to);
		return retval;
	}

	static bool LUA_NATIVE_ENTITY_IS_ENTITY_DEAD(Entity entity, bool p1)
	{
		auto retval = (bool)ENTITY::IS_ENTITY_DEAD(entity, p1);
		return retval;
	}

	static bool LUA_NATIVE_ENTITY_IS_ENTITY_IN_AIR(Entity entity)
	{
		auto retval = (bool)ENTITY::IS_ENTITY_IN_AIR(entity);
		return retval;
	}

	static bool LUA_NATIVE_ENTITY_IS_ENTITY_IN_ANGLED_AREA(Entity entity, float x1, float y1, float z1, float x2, float y2, float z2, float width, bool debug, bool includeZ, Any p10)
	{
		auto retval = (bool)ENTITY::IS_ENTITY_IN_ANGLED_AREA(entity, x1, y1, z1, x2, y2, z2, width, debug, includeZ, p10);
		return retval;
	}

	static bool LUA_NATIVE_ENTITY_IS_ENTITY_IN_AREA(Entity entity, float x1, float y1, float z1, float x2, float y2, float z2, bool p7, bool p8, Any p9)
	{
		auto retval = (bool)ENTITY::IS_ENTITY_IN_AREA(entity, x1, y1, z1, x2, y2, z2, p7, p8, p9);
		return retval;
	}

	static bool LUA_NATIVE_ENTITY_IS_ENTITY_IN_ZONE(Entity entity, sol::stack_object zone)
	{
		auto retval = (bool)ENTITY::IS_ENTITY_IN_ZONE(entity, zone.is<const char*>() ? zone.as<const char*>() : nullptr);
		return retval;
	}

	static bool LUA_NATIVE_ENTITY_IS_ENTITY_IN_WATER(Entity entity)
	{
		auto retval = (bool)ENTITY::IS_ENTITY_IN_WATER(entity);
		return retval;
	}

	static float LUA_NATIVE_ENTITY_GET_ENTITY_SUBMERGED_LEVEL(Entity entity)
	{
		auto retval = ENTITY::GET_ENTITY_SUBMERGED_LEVEL(entity);
		return retval;
	}

	static void LUA_NATIVE_ENTITY_SET_ENTITY_REQUIRES_MORE_EXPENSIVE_RIVER_CHECK(Entity entity, bool toggle)
	{
		ENTITY::SET_ENTITY_REQUIRES_MORE_EXPENSIVE_RIVER_CHECK(entity, toggle);
	}

	static bool LUA_NATIVE_ENTITY_IS_ENTITY_ON_SCREEN(Entity entity)
	{
		auto retval = (bool)ENTITY::IS_ENTITY_ON_SCREEN(entity);
		return retval;
	}

	static bool LUA_NATIVE_ENTITY_IS_ENTITY_PLAYING_ANIM(Entity entity, sol::stack_object animDict, sol::stack_object animName, int taskFlag)
	{
		auto retval = (bool)ENTITY::IS_ENTITY_PLAYING_ANIM(entity, animDict.is<const char*>() ? animDict.as<const char*>() : nullptr, animName.is<const char*>() ? animName.as<const char*>() : nullptr, taskFlag);
		return retval;
	}

	static bool LUA_NATIVE_ENTITY_IS_ENTITY_STATIC(Entity entity)
	{
		auto retval = (bool)ENTITY::IS_ENTITY_STATIC(entity);
		return retval;
	}

	static bool LUA_NATIVE_ENTITY_IS_ENTITY_TOUCHING_ENTITY(Entity entity, Entity targetEntity)
	{
		auto retval = (bool)ENTITY::IS_ENTITY_TOUCHING_ENTITY(entity, targetEntity);
		return retval;
	}

	static bool LUA_NATIVE_ENTITY_IS_ENTITY_TOUCHING_MODEL(Entity entity, Hash modelHash)
	{
		auto retval = (bool)ENTITY::IS_ENTITY_TOUCHING_MODEL(entity, modelHash);
		return retval;
	}

	static bool LUA_NATIVE_ENTITY_IS_ENTITY_UPRIGHT(Entity entity, float angle)
	{
		auto retval = (bool)ENTITY::IS_ENTITY_UPRIGHT(entity, angle);
		return retval;
	}

	static bool LUA_NATIVE_ENTITY_IS_ENTITY_UPSIDEDOWN(Entity entity)
	{
		auto retval = (bool)ENTITY::IS_ENTITY_UPSIDEDOWN(entity);
		return retval;
	}

	static bool LUA_NATIVE_ENTITY_IS_ENTITY_VISIBLE(Entity entity)
	{
		auto retval = (bool)ENTITY::IS_ENTITY_VISIBLE(entity);
		return retval;
	}

	static bool LUA_NATIVE_ENTITY_IS_ENTITY_VISIBLE_TO_SCRIPT(Entity entity)
	{
		auto retval = (bool)ENTITY::IS_ENTITY_VISIBLE_TO_SCRIPT(entity);
		return retval;
	}

	static bool LUA_NATIVE_ENTITY_IS_ENTITY_OCCLUDED(Entity entity)
	{
		auto retval = (bool)ENTITY::IS_ENTITY_OCCLUDED(entity);
		return retval;
	}

	static bool LUA_NATIVE_ENTITY_WOULD_ENTITY_BE_OCCLUDED(Hash entityModelHash, float x, float y, float z, bool p4)
	{
		auto retval = (bool)ENTITY::WOULD_ENTITY_BE_OCCLUDED(entityModelHash, x, y, z, p4);
		return retval;
	}

	static bool LUA_NATIVE_ENTITY_IS_ENTITY_WAITING_FOR_WORLD_COLLISION(Entity entity)
	{
		auto retval = (bool)ENTITY::IS_ENTITY_WAITING_FOR_WORLD_COLLISION(entity);
		return retval;
	}

	static void LUA_NATIVE_ENTITY_APPLY_FORCE_TO_ENTITY_CENTER_OF_MASS(Entity entity, int forceType, float x, float y, float z, bool p5, bool isDirectionRel, bool isForceRel, bool p8)
	{
		ENTITY::APPLY_FORCE_TO_ENTITY_CENTER_OF_MASS(entity, forceType, x, y, z, p5, isDirectionRel, isForceRel, p8);
	}

	static void LUA_NATIVE_ENTITY_APPLY_FORCE_TO_ENTITY(Entity entity, int forceFlags, float x, float y, float z, float offX, float offY, float offZ, int boneIndex, bool isDirectionRel, bool ignoreUpVec, bool isForceRel, bool p12, bool p13)
	{
		ENTITY::APPLY_FORCE_TO_ENTITY(entity, forceFlags, x, y, z, offX, offY, offZ, boneIndex, isDirectionRel, ignoreUpVec, isForceRel, p12, p13);
	}

	static void LUA_NATIVE_ENTITY_ATTACH_ENTITY_TO_ENTITY(Entity entity1, Entity entity2, int boneIndex, float xPos, float yPos, float zPos, float xRot, float yRot, float zRot, bool p9, bool useSoftPinning, bool collision, bool isPed, int vertexIndex, bool fixedRot, Any p15)
	{
		ENTITY::ATTACH_ENTITY_TO_ENTITY(entity1, entity2, boneIndex, xPos, yPos, zPos, xRot, yRot, zRot, p9, useSoftPinning, collision, isPed, vertexIndex, fixedRot, p15);
	}

	static void LUA_NATIVE_ENTITY_ATTACH_ENTITY_BONE_TO_ENTITY_BONE(Entity entity1, Entity entity2, int boneIndex1, int boneIndex2, bool p4, bool p5)
	{
		ENTITY::ATTACH_ENTITY_BONE_TO_ENTITY_BONE(entity1, entity2, boneIndex1, boneIndex2, p4, p5);
	}

	static void LUA_NATIVE_ENTITY_ATTACH_ENTITY_BONE_TO_ENTITY_BONE_Y_FORWARD(Entity entity1, Entity entity2, int boneIndex1, int boneIndex2, bool p4, bool p5)
	{
		ENTITY::ATTACH_ENTITY_BONE_TO_ENTITY_BONE_Y_FORWARD(entity1, entity2, boneIndex1, boneIndex2, p4, p5);
	}

	static void LUA_NATIVE_ENTITY_ATTACH_ENTITY_TO_ENTITY_PHYSICALLY(Entity entity1, Entity entity2, int boneIndex1, int boneIndex2, float xPos1, float yPos1, float zPos1, float xPos2, float yPos2, float zPos2, float xRot, float yRot, float zRot, float breakForce, bool fixedRot, bool p15, bool collision, bool p17, int p18)
	{
		ENTITY::ATTACH_ENTITY_TO_ENTITY_PHYSICALLY(entity1, entity2, boneIndex1, boneIndex2, xPos1, yPos1, zPos1, xPos2, yPos2, zPos2, xRot, yRot, zRot, breakForce, fixedRot, p15, collision, p17, p18);
	}

	static void LUA_NATIVE_ENTITY_ATTACH_ENTITY_TO_ENTITY_PHYSICALLY_OVERRIDE_INVERSE_MASS(Entity firstEntityIndex, Entity secondEntityIndex, int firstEntityBoneIndex, int secondEntityBoneIndex, float secondEntityOffsetX, float secondEntityOffsetY, float secondEntityOffsetZ, float firstEntityOffsetX, float firstEntityOffsetY, float firstEntityOffsetZ, float vecRotationX, float vecRotationY, float vecRotationZ, float physicalStrength, bool constrainRotation, bool doInitialWarp, bool collideWithEntity, bool addInitialSeperation, int rotOrder, float invMassScaleA, float invMassScaleB)
	{
		ENTITY::ATTACH_ENTITY_TO_ENTITY_PHYSICALLY_OVERRIDE_INVERSE_MASS(firstEntityIndex, secondEntityIndex, firstEntityBoneIndex, secondEntityBoneIndex, secondEntityOffsetX, secondEntityOffsetY, secondEntityOffsetZ, firstEntityOffsetX, firstEntityOffsetY, firstEntityOffsetZ, vecRotationX, vecRotationY, vecRotationZ, physicalStrength, constrainRotation, doInitialWarp, collideWithEntity, addInitialSeperation, rotOrder, invMassScaleA, invMassScaleB);
	}

	static void LUA_NATIVE_ENTITY_PROCESS_ENTITY_ATTACHMENTS(Entity entity)
	{
		ENTITY::PROCESS_ENTITY_ATTACHMENTS(entity);
	}

	static int LUA_NATIVE_ENTITY_GET_ENTITY_BONE_INDEX_BY_NAME(Entity entity, sol::stack_object boneName)
	{
		auto retval = ENTITY::GET_ENTITY_BONE_INDEX_BY_NAME(entity, boneName.is<const char*>() ? boneName.as<const char*>() : nullptr);
		return retval;
	}

	static void LUA_NATIVE_ENTITY_CLEAR_ENTITY_LAST_DAMAGE_ENTITY(Entity entity)
	{
		ENTITY::CLEAR_ENTITY_LAST_DAMAGE_ENTITY(entity);
	}

	static Entity LUA_NATIVE_ENTITY_DELETE_ENTITY(Entity entity)
	{
		ENTITY::DELETE_ENTITY(&entity);
		return entity;
	}

	static void LUA_NATIVE_ENTITY_DETACH_ENTITY(Entity entity, bool dynamic, bool collision)
	{
		ENTITY::DETACH_ENTITY(entity, dynamic, collision);
	}

	static void LUA_NATIVE_ENTITY_FREEZE_ENTITY_POSITION(Entity entity, bool toggle)
	{
		ENTITY::FREEZE_ENTITY_POSITION(entity, toggle);
	}

	static void LUA_NATIVE_ENTITY_SET_ENTITY_SHOULD_FREEZE_WAITING_ON_COLLISION(Entity entity, bool toggle)
	{
		ENTITY::SET_ENTITY_SHOULD_FREEZE_WAITING_ON_COLLISION(entity, toggle);
	}

	static bool LUA_NATIVE_ENTITY_PLAY_ENTITY_ANIM(Entity entity, sol::stack_object animName, sol::stack_object animDict, float p3, bool loop, bool stayInAnim, bool p6, float delta, Any bitset)
	{
		auto retval = (bool)ENTITY::PLAY_ENTITY_ANIM(entity, animName.is<const char*>() ? animName.as<const char*>() : nullptr, animDict.is<const char*>() ? animDict.as<const char*>() : nullptr, p3, loop, stayInAnim, p6, delta, bitset);
		return retval;
	}

	static bool LUA_NATIVE_ENTITY_PLAY_SYNCHRONIZED_ENTITY_ANIM(Entity entity, int syncedScene, sol::stack_object animation, sol::stack_object propName, float p4, float p5, Any p6, float p7)
	{
		auto retval = (bool)ENTITY::PLAY_SYNCHRONIZED_ENTITY_ANIM(entity, syncedScene, animation.is<const char*>() ? animation.as<const char*>() : nullptr, propName.is<const char*>() ? propName.as<const char*>() : nullptr, p4, p5, p6, p7);
		return retval;
	}

	static bool LUA_NATIVE_ENTITY_PLAY_SYNCHRONIZED_MAP_ENTITY_ANIM(float x1, float y1, float z1, float x2, Any y2, float z2, sol::stack_object p6, sol::stack_object p7, float p8, float p9, Any p10, float p11)
	{
		auto retval = (bool)ENTITY::PLAY_SYNCHRONIZED_MAP_ENTITY_ANIM(x1, y1, z1, x2, y2, z2, p6.is<const char*>() ? p6.as<const char*>() : nullptr, p7.is<const char*>() ? p7.as<const char*>() : nullptr, p8, p9, p10, p11);
		return retval;
	}

	static bool LUA_NATIVE_ENTITY_STOP_SYNCHRONIZED_MAP_ENTITY_ANIM(float x1, float y1, float z1, float x2, Any y2, float z2)
	{
		auto retval = (bool)ENTITY::STOP_SYNCHRONIZED_MAP_ENTITY_ANIM(x1, y1, z1, x2, y2, z2);
		return retval;
	}

	static bool LUA_NATIVE_ENTITY_STOP_ENTITY_ANIM(Entity entity, sol::stack_object animation, sol::stack_object animGroup, float p3)
	{
		auto retval = (bool)ENTITY::STOP_ENTITY_ANIM(entity, animation.is<const char*>() ? animation.as<const char*>() : nullptr, animGroup.is<const char*>() ? animGroup.as<const char*>() : nullptr, p3);
		return retval;
	}

	static bool LUA_NATIVE_ENTITY_STOP_SYNCHRONIZED_ENTITY_ANIM(Entity entity, float p1, bool p2)
	{
		auto retval = (bool)ENTITY::STOP_SYNCHRONIZED_ENTITY_ANIM(entity, p1, p2);
		return retval;
	}

	static bool LUA_NATIVE_ENTITY_HAS_ANIM_EVENT_FIRED(Entity entity, Hash actionHash)
	{
		auto retval = (bool)ENTITY::HAS_ANIM_EVENT_FIRED(entity, actionHash);
		return retval;
	}

	static bool LUA_NATIVE_ENTITY_FIND_ANIM_EVENT_PHASE(sol::stack_object animDictionary, sol::stack_object animName, sol::stack_object p2, uintptr_t p3, uintptr_t p4)
	{
		auto retval = (bool)ENTITY::FIND_ANIM_EVENT_PHASE(animDictionary.is<const char*>() ? animDictionary.as<const char*>() : nullptr, animName.is<const char*>() ? animName.as<const char*>() : nullptr, p2.is<const char*>() ? p2.as<const char*>() : nullptr, (Any*)p3, (Any*)p4);
		return retval;
	}

	static void LUA_NATIVE_ENTITY_SET_ENTITY_ANIM_CURRENT_TIME(Entity entity, sol::stack_object animDictionary, sol::stack_object animName, float time)
	{
		ENTITY::SET_ENTITY_ANIM_CURRENT_TIME(entity, animDictionary.is<const char*>() ? animDictionary.as<const char*>() : nullptr, animName.is<const char*>() ? animName.as<const char*>() : nullptr, time);
	}

	static void LUA_NATIVE_ENTITY_SET_ENTITY_ANIM_SPEED(Entity entity, sol::stack_object animDictionary, sol::stack_object animName, float speedMultiplier)
	{
		ENTITY::SET_ENTITY_ANIM_SPEED(entity, animDictionary.is<const char*>() ? animDictionary.as<const char*>() : nullptr, animName.is<const char*>() ? animName.as<const char*>() : nullptr, speedMultiplier);
	}

	static void LUA_NATIVE_ENTITY_SET_ENTITY_AS_MISSION_ENTITY(Entity entity, bool p1, bool p2)
	{
		ENTITY::SET_ENTITY_AS_MISSION_ENTITY(entity, p1, p2);
	}

	static Entity LUA_NATIVE_ENTITY_SET_ENTITY_AS_NO_LONGER_NEEDED(Entity entity)
	{
		ENTITY::SET_ENTITY_AS_NO_LONGER_NEEDED(&entity);
		return entity;
	}

	static Ped LUA_NATIVE_ENTITY_SET_PED_AS_NO_LONGER_NEEDED(Ped ped)
	{
		ENTITY::SET_PED_AS_NO_LONGER_NEEDED(&ped);
		return ped;
	}

	static Vehicle LUA_NATIVE_ENTITY_SET_VEHICLE_AS_NO_LONGER_NEEDED(Vehicle vehicle)
	{
		ENTITY::SET_VEHICLE_AS_NO_LONGER_NEEDED(&vehicle);
		return vehicle;
	}

	static Object LUA_NATIVE_ENTITY_SET_OBJECT_AS_NO_LONGER_NEEDED(Object object)
	{
		ENTITY::SET_OBJECT_AS_NO_LONGER_NEEDED(&object);
		return object;
	}

	static void LUA_NATIVE_ENTITY_SET_ENTITY_CAN_BE_DAMAGED(Entity entity, bool toggle)
	{
		ENTITY::SET_ENTITY_CAN_BE_DAMAGED(entity, toggle);
	}

	static bool LUA_NATIVE_ENTITY_GET_ENTITY_CAN_BE_DAMAGED(Entity entity)
	{
		auto retval = (bool)ENTITY::GET_ENTITY_CAN_BE_DAMAGED(entity);
		return retval;
	}

	static void LUA_NATIVE_ENTITY_SET_ENTITY_CAN_BE_DAMAGED_BY_RELATIONSHIP_GROUP(Entity entity, bool bCanBeDamaged, int relGroup)
	{
		ENTITY::SET_ENTITY_CAN_BE_DAMAGED_BY_RELATIONSHIP_GROUP(entity, bCanBeDamaged, relGroup);
	}

	static void LUA_NATIVE_ENTITY_SET_ENTITY_CAN_ONLY_BE_DAMAGED_BY_SCRIPT_PARTICIPANTS(Entity entity, bool toggle)
	{
		ENTITY::SET_ENTITY_CAN_ONLY_BE_DAMAGED_BY_SCRIPT_PARTICIPANTS(entity, toggle);
	}

	static void LUA_NATIVE_ENTITY_SET_ENTITY_CAN_BE_TARGETED_WITHOUT_LOS(Entity entity, bool toggle)
	{
		ENTITY::SET_ENTITY_CAN_BE_TARGETED_WITHOUT_LOS(entity, toggle);
	}

	static void LUA_NATIVE_ENTITY_SET_ENTITY_COLLISION(Entity entity, bool toggle, bool keepPhysics)
	{
		ENTITY::SET_ENTITY_COLLISION(entity, toggle, keepPhysics);
	}

	static bool LUA_NATIVE_ENTITY_GET_ENTITY_COLLISION_DISABLED(Entity entity)
	{
		auto retval = (bool)ENTITY::GET_ENTITY_COLLISION_DISABLED(entity);
		return retval;
	}

	static void LUA_NATIVE_ENTITY_SET_ENTITY_COMPLETELY_DISABLE_COLLISION(Entity entity, bool toggle, bool keepPhysics)
	{
		ENTITY::SET_ENTITY_COMPLETELY_DISABLE_COLLISION(entity, toggle, keepPhysics);
	}

	static void LUA_NATIVE_ENTITY_SET_ENTITY_COORDS(Entity entity, float xPos, float yPos, float zPos, bool xAxis, bool yAxis, bool zAxis, bool clearArea)
	{
		ENTITY::SET_ENTITY_COORDS(entity, xPos, yPos, zPos, xAxis, yAxis, zAxis, clearArea);
	}

	static void LUA_NATIVE_ENTITY_SET_ENTITY_COORDS_WITHOUT_PLANTS_RESET(Entity entity, float xPos, float yPos, float zPos, bool alive, bool deadFlag, bool ragdollFlag, bool clearArea)
	{
		ENTITY::SET_ENTITY_COORDS_WITHOUT_PLANTS_RESET(entity, xPos, yPos, zPos, alive, deadFlag, ragdollFlag, clearArea);
	}

	static void LUA_NATIVE_ENTITY_SET_ENTITY_COORDS_NO_OFFSET(Entity entity, float xPos, float yPos, float zPos, bool xAxis, bool yAxis, bool zAxis)
	{
		ENTITY::SET_ENTITY_COORDS_NO_OFFSET(entity, xPos, yPos, zPos, xAxis, yAxis, zAxis);
	}

	static void LUA_NATIVE_ENTITY_SET_ENTITY_DYNAMIC(Entity entity, bool toggle)
	{
		ENTITY::SET_ENTITY_DYNAMIC(entity, toggle);
	}

	static void LUA_NATIVE_ENTITY_SET_ENTITY_HEADING(Entity entity, float heading)
	{
		ENTITY::SET_ENTITY_HEADING(entity, heading);
	}

	static void LUA_NATIVE_ENTITY_SET_ENTITY_HEALTH(Entity entity, int health, Entity instigator, Hash weaponType)
	{
		ENTITY::SET_ENTITY_HEALTH(entity, health, instigator, weaponType);
	}

	static void LUA_NATIVE_ENTITY_SET_ENTITY_INVINCIBLE(Entity entity, bool toggle)
	{
		ENTITY::SET_ENTITY_INVINCIBLE(entity, toggle);
	}

	static void LUA_NATIVE_ENTITY_SET_ENTITY_IS_TARGET_PRIORITY(Entity entity, bool p1, float p2)
	{
		ENTITY::SET_ENTITY_IS_TARGET_PRIORITY(entity, p1, p2);
	}

	static void LUA_NATIVE_ENTITY_SET_ENTITY_LIGHTS(Entity entity, bool toggle)
	{
		ENTITY::SET_ENTITY_LIGHTS(entity, toggle);
	}

	static void LUA_NATIVE_ENTITY_SET_ENTITY_LOAD_COLLISION_FLAG(Entity entity, bool toggle, Any p2)
	{
		ENTITY::SET_ENTITY_LOAD_COLLISION_FLAG(entity, toggle, p2);
	}

	static bool LUA_NATIVE_ENTITY_HAS_COLLISION_LOADED_AROUND_ENTITY(Entity entity)
	{
		auto retval = (bool)ENTITY::HAS_COLLISION_LOADED_AROUND_ENTITY(entity);
		return retval;
	}

	static void LUA_NATIVE_ENTITY_SET_ENTITY_MAX_SPEED(Entity entity, float speed)
	{
		ENTITY::SET_ENTITY_MAX_SPEED(entity, speed);
	}

	static void LUA_NATIVE_ENTITY_SET_ENTITY_ONLY_DAMAGED_BY_PLAYER(Entity entity, bool toggle)
	{
		ENTITY::SET_ENTITY_ONLY_DAMAGED_BY_PLAYER(entity, toggle);
	}

	static void LUA_NATIVE_ENTITY_SET_ENTITY_ONLY_DAMAGED_BY_RELATIONSHIP_GROUP(Entity entity, bool p1, Any p2)
	{
		ENTITY::SET_ENTITY_ONLY_DAMAGED_BY_RELATIONSHIP_GROUP(entity, p1, p2);
	}

	static void LUA_NATIVE_ENTITY_SET_ENTITY_PROOFS(Entity entity, bool bulletProof, bool fireProof, bool explosionProof, bool collisionProof, bool meleeProof, bool steamProof, bool p7, bool waterProof)
	{
		ENTITY::SET_ENTITY_PROOFS(entity, bulletProof, fireProof, explosionProof, collisionProof, meleeProof, steamProof, p7, waterProof);
	}

	static std::tuple<bool, bool, bool, bool, bool, bool, bool, bool, bool> LUA_NATIVE_ENTITY_GET_ENTITY_PROOFS(Entity entity, bool bulletProof, bool fireProof, bool explosionProof, bool collisionProof, bool meleeProof, bool steamProof, bool p7, bool drownProof)
	{
		std::tuple<bool, bool, bool, bool, bool, bool, bool, bool, bool> return_values;
		std::get<0>(return_values) = (bool)ENTITY::GET_ENTITY_PROOFS(entity, (BOOL*)&bulletProof, (BOOL*)&fireProof, (BOOL*)&explosionProof, (BOOL*)&collisionProof, (BOOL*)&meleeProof, (BOOL*)&steamProof, (BOOL*)&p7, (BOOL*)&drownProof);
		std::get<1>(return_values) = bulletProof;
		std::get<2>(return_values) = fireProof;
		std::get<3>(return_values) = explosionProof;
		std::get<4>(return_values) = collisionProof;
		std::get<5>(return_values) = meleeProof;
		std::get<6>(return_values) = steamProof;
		std::get<7>(return_values) = p7;
		std::get<8>(return_values) = drownProof;

		return return_values;
	}

	static void LUA_NATIVE_ENTITY_SET_ENTITY_QUATERNION(Entity entity, float x, float y, float z, float w)
	{
		ENTITY::SET_ENTITY_QUATERNION(entity, x, y, z, w);
	}

	static void LUA_NATIVE_ENTITY_SET_ENTITY_RECORDS_COLLISIONS(Entity entity, bool toggle)
	{
		ENTITY::SET_ENTITY_RECORDS_COLLISIONS(entity, toggle);
	}

	static void LUA_NATIVE_ENTITY_SET_ENTITY_ROTATION(Entity entity, float pitch, float roll, float yaw, int rotationOrder, bool p5)
	{
		ENTITY::SET_ENTITY_ROTATION(entity, pitch, roll, yaw, rotationOrder, p5);
	}

	static void LUA_NATIVE_ENTITY_SET_ENTITY_VISIBLE(Entity entity, bool toggle, bool p2)
	{
		ENTITY::SET_ENTITY_VISIBLE(entity, toggle, p2);
	}

	static void LUA_NATIVE_ENTITY_SET_ENTITY_WATER_REFLECTION_FLAG(Entity entity, bool toggle)
	{
		ENTITY::SET_ENTITY_WATER_REFLECTION_FLAG(entity, toggle);
	}

	static void LUA_NATIVE_ENTITY_SET_ENTITY_MIRROR_REFLECTION_FLAG(Entity entity, bool p1)
	{
		ENTITY::SET_ENTITY_MIRROR_REFLECTION_FLAG(entity, p1);
	}

	static void LUA_NATIVE_ENTITY_SET_ENTITY_VELOCITY(Entity entity, float x, float y, float z)
	{
		ENTITY::SET_ENTITY_VELOCITY(entity, x, y, z);
	}

	static void LUA_NATIVE_ENTITY_SET_ENTITY_ANGULAR_VELOCITY(Entity entity, float x, float y, float z)
	{
		ENTITY::SET_ENTITY_ANGULAR_VELOCITY(entity, x, y, z);
	}

	static void LUA_NATIVE_ENTITY_SET_ENTITY_HAS_GRAVITY(Entity entity, bool toggle)
	{
		ENTITY::SET_ENTITY_HAS_GRAVITY(entity, toggle);
	}

	static void LUA_NATIVE_ENTITY_SET_ENTITY_LOD_DIST(Entity entity, int value)
	{
		ENTITY::SET_ENTITY_LOD_DIST(entity, value);
	}

	static int LUA_NATIVE_ENTITY_GET_ENTITY_LOD_DIST(Entity entity)
	{
		auto retval = ENTITY::GET_ENTITY_LOD_DIST(entity);
		return retval;
	}

	static void LUA_NATIVE_ENTITY_SET_ENTITY_ALPHA(Entity entity, int alphaLevel, bool skin)
	{
		ENTITY::SET_ENTITY_ALPHA(entity, alphaLevel, skin);
	}

	static int LUA_NATIVE_ENTITY_GET_ENTITY_ALPHA(Entity entity)
	{
		auto retval = ENTITY::GET_ENTITY_ALPHA(entity);
		return retval;
	}

	static void LUA_NATIVE_ENTITY_RESET_ENTITY_ALPHA(Entity entity)
	{
		ENTITY::RESET_ENTITY_ALPHA(entity);
	}

	static void LUA_NATIVE_ENTITY_RESET_PICKUP_ENTITY_GLOW(Entity entity)
	{
		ENTITY::RESET_PICKUP_ENTITY_GLOW(entity);
	}

	static void LUA_NATIVE_ENTITY_SET_PICKUP_COLLIDES_WITH_PROJECTILES(Any p0, Any p1)
	{
		ENTITY::SET_PICKUP_COLLIDES_WITH_PROJECTILES(p0, p1);
	}

	static void LUA_NATIVE_ENTITY_SET_ENTITY_SORT_BIAS(Entity entity, float p1)
	{
		ENTITY::SET_ENTITY_SORT_BIAS(entity, p1);
	}

	static void LUA_NATIVE_ENTITY_SET_ENTITY_ALWAYS_PRERENDER(Entity entity, bool toggle)
	{
		ENTITY::SET_ENTITY_ALWAYS_PRERENDER(entity, toggle);
	}

	static void LUA_NATIVE_ENTITY_SET_ENTITY_RENDER_SCORCHED(Entity entity, bool toggle)
	{
		ENTITY::SET_ENTITY_RENDER_SCORCHED(entity, toggle);
	}

	static void LUA_NATIVE_ENTITY_SET_ENTITY_TRAFFICLIGHT_OVERRIDE(Entity entity, int state)
	{
		ENTITY::SET_ENTITY_TRAFFICLIGHT_OVERRIDE(entity, state);
	}

	static void LUA_NATIVE_ENTITY_SET_ENTITY_IS_IN_VEHICLE(Entity entity)
	{
		ENTITY::SET_ENTITY_IS_IN_VEHICLE(entity);
	}

	static void LUA_NATIVE_ENTITY_CREATE_MODEL_SWAP(float x, float y, float z, float radius, Hash originalModel, Hash newModel, bool p6)
	{
		ENTITY::CREATE_MODEL_SWAP(x, y, z, radius, originalModel, newModel, p6);
	}

	static void LUA_NATIVE_ENTITY_REMOVE_MODEL_SWAP(float x, float y, float z, float radius, Hash originalModel, Hash newModel, bool p6)
	{
		ENTITY::REMOVE_MODEL_SWAP(x, y, z, radius, originalModel, newModel, p6);
	}

	static void LUA_NATIVE_ENTITY_CREATE_MODEL_HIDE(float x, float y, float z, float radius, Hash modelHash, bool p5)
	{
		ENTITY::CREATE_MODEL_HIDE(x, y, z, radius, modelHash, p5);
	}

	static void LUA_NATIVE_ENTITY_CREATE_MODEL_HIDE_EXCLUDING_SCRIPT_OBJECTS(float x, float y, float z, float radius, Hash modelHash, bool p5)
	{
		ENTITY::CREATE_MODEL_HIDE_EXCLUDING_SCRIPT_OBJECTS(x, y, z, radius, modelHash, p5);
	}

	static void LUA_NATIVE_ENTITY_REMOVE_MODEL_HIDE(float x, float y, float z, float radius, Hash modelHash, bool p5)
	{
		ENTITY::REMOVE_MODEL_HIDE(x, y, z, radius, modelHash, p5);
	}

	static void LUA_NATIVE_ENTITY_CREATE_FORCED_OBJECT(float x, float y, float z, Any p3, Hash modelHash, bool p5)
	{
		ENTITY::CREATE_FORCED_OBJECT(x, y, z, p3, modelHash, p5);
	}

	static void LUA_NATIVE_ENTITY_REMOVE_FORCED_OBJECT(float x, float y, float z, float p3, Hash modelHash)
	{
		ENTITY::REMOVE_FORCED_OBJECT(x, y, z, p3, modelHash);
	}

	static void LUA_NATIVE_ENTITY_SET_ENTITY_NO_COLLISION_ENTITY(Entity entity1, Entity entity2, bool thisFrameOnly)
	{
		ENTITY::SET_ENTITY_NO_COLLISION_ENTITY(entity1, entity2, thisFrameOnly);
	}

	static void LUA_NATIVE_ENTITY_SET_ENTITY_MOTION_BLUR(Entity entity, bool toggle)
	{
		ENTITY::SET_ENTITY_MOTION_BLUR(entity, toggle);
	}

	static void LUA_NATIVE_ENTITY_SET_CAN_AUTO_VAULT_ON_ENTITY(Entity entity, bool toggle)
	{
		ENTITY::SET_CAN_AUTO_VAULT_ON_ENTITY(entity, toggle);
	}

	static void LUA_NATIVE_ENTITY_SET_CAN_CLIMB_ON_ENTITY(Entity entity, bool toggle)
	{
		ENTITY::SET_CAN_CLIMB_ON_ENTITY(entity, toggle);
	}

	static void LUA_NATIVE_ENTITY_SET_WAIT_FOR_COLLISIONS_BEFORE_PROBE(Entity entity, bool toggle)
	{
		ENTITY::SET_WAIT_FOR_COLLISIONS_BEFORE_PROBE(entity, toggle);
	}

	static void LUA_NATIVE_ENTITY_SET_ENTITY_NOWEAPONDECALS(Entity entity, bool p1)
	{
		ENTITY::SET_ENTITY_NOWEAPONDECALS(entity, p1);
	}

	static void LUA_NATIVE_ENTITY_SET_ENTITY_USE_MAX_DISTANCE_FOR_WATER_REFLECTION(Entity entity, bool p1)
	{
		ENTITY::SET_ENTITY_USE_MAX_DISTANCE_FOR_WATER_REFLECTION(entity, p1);
	}

	static Vector3 LUA_NATIVE_ENTITY_GET_ENTITY_BONE_ROTATION(Entity entity, int boneIndex)
	{
		auto retval = ENTITY::GET_ENTITY_BONE_ROTATION(entity, boneIndex);
		return retval;
	}

	static Vector3 LUA_NATIVE_ENTITY_GET_ENTITY_BONE_POSTION(Entity entity, int boneIndex)
	{
		auto retval = ENTITY::GET_ENTITY_BONE_POSTION(entity, boneIndex);
		return retval;
	}

	static Vector3 LUA_NATIVE_ENTITY_GET_ENTITY_BONE_OBJECT_ROTATION(Entity entity, int boneIndex)
	{
		auto retval = ENTITY::GET_ENTITY_BONE_OBJECT_ROTATION(entity, boneIndex);
		return retval;
	}

	static Vector3 LUA_NATIVE_ENTITY_GET_ENTITY_BONE_OBJECT_POSTION(Entity entity, int boneIndex)
	{
		auto retval = ENTITY::GET_ENTITY_BONE_OBJECT_POSTION(entity, boneIndex);
		return retval;
	}

	static int LUA_NATIVE_ENTITY_GET_ENTITY_BONE_COUNT(Entity entity)
	{
		auto retval = ENTITY::GET_ENTITY_BONE_COUNT(entity);
		return retval;
	}

	static void LUA_NATIVE_ENTITY_ENABLE_ENTITY_BULLET_COLLISION(Entity entity)
	{
		ENTITY::ENABLE_ENTITY_BULLET_COLLISION(entity);
	}

	static void LUA_NATIVE_ENTITY_SET_ENTITY_CAN_ONLY_BE_DAMAGED_BY_ENTITY(Entity entity1, Entity entity2)
	{
		ENTITY::SET_ENTITY_CAN_ONLY_BE_DAMAGED_BY_ENTITY(entity1, entity2);
	}

	static void LUA_NATIVE_ENTITY_SET_ENTITY_CANT_CAUSE_COLLISION_DAMAGED_ENTITY(Entity entity1, Entity entity2)
	{
		ENTITY::SET_ENTITY_CANT_CAUSE_COLLISION_DAMAGED_ENTITY(entity1, entity2);
	}

	static void LUA_NATIVE_ENTITY_SET_ALLOW_MIGRATE_TO_SPECTATOR(Entity entity, Any p1)
	{
		ENTITY::SET_ALLOW_MIGRATE_TO_SPECTATOR(entity, p1);
	}

	static Entity LUA_NATIVE_ENTITY_GET_ENTITY_OF_TYPE_ATTACHED_TO_ENTITY(Entity entity, Hash modelHash)
	{
		auto retval = ENTITY::GET_ENTITY_OF_TYPE_ATTACHED_TO_ENTITY(entity, modelHash);
		return retval;
	}

	static void LUA_NATIVE_ENTITY_SET_PICK_UP_BY_CARGOBOB_DISABLED(Entity entity, bool toggle)
	{
		ENTITY::SET_PICK_UP_BY_CARGOBOB_DISABLED(entity, toggle);
	}

	void init_native_binding_ENTITY(sol::state& L)
	{
		auto ENTITY = L["ENTITY"].get_or_create<sol::table>();
		ENTITY.set_function("DOES_ENTITY_EXIST", LUA_NATIVE_ENTITY_DOES_ENTITY_EXIST);
		ENTITY.set_function("DOES_ENTITY_BELONG_TO_THIS_SCRIPT", LUA_NATIVE_ENTITY_DOES_ENTITY_BELONG_TO_THIS_SCRIPT);
		ENTITY.set_function("DOES_ENTITY_HAVE_DRAWABLE", LUA_NATIVE_ENTITY_DOES_ENTITY_HAVE_DRAWABLE);
		ENTITY.set_function("DOES_ENTITY_HAVE_PHYSICS", LUA_NATIVE_ENTITY_DOES_ENTITY_HAVE_PHYSICS);
		ENTITY.set_function("DOES_ENTITY_HAVE_SKELETON", LUA_NATIVE_ENTITY_DOES_ENTITY_HAVE_SKELETON);
		ENTITY.set_function("DOES_ENTITY_HAVE_ANIM_DIRECTOR", LUA_NATIVE_ENTITY_DOES_ENTITY_HAVE_ANIM_DIRECTOR);
		ENTITY.set_function("HAS_ENTITY_ANIM_FINISHED", LUA_NATIVE_ENTITY_HAS_ENTITY_ANIM_FINISHED);
		ENTITY.set_function("HAS_ENTITY_BEEN_DAMAGED_BY_ANY_OBJECT", LUA_NATIVE_ENTITY_HAS_ENTITY_BEEN_DAMAGED_BY_ANY_OBJECT);
		ENTITY.set_function("HAS_ENTITY_BEEN_DAMAGED_BY_ANY_PED", LUA_NATIVE_ENTITY_HAS_ENTITY_BEEN_DAMAGED_BY_ANY_PED);
		ENTITY.set_function("HAS_ENTITY_BEEN_DAMAGED_BY_ANY_VEHICLE", LUA_NATIVE_ENTITY_HAS_ENTITY_BEEN_DAMAGED_BY_ANY_VEHICLE);
		ENTITY.set_function("HAS_ENTITY_BEEN_DAMAGED_BY_ENTITY", LUA_NATIVE_ENTITY_HAS_ENTITY_BEEN_DAMAGED_BY_ENTITY);
		ENTITY.set_function("HAS_ENTITY_CLEAR_LOS_TO_ENTITY", LUA_NATIVE_ENTITY_HAS_ENTITY_CLEAR_LOS_TO_ENTITY);
		ENTITY.set_function("HAS_ENTITY_CLEAR_LOS_TO_ENTITY_ADJUST_FOR_COVER", LUA_NATIVE_ENTITY_HAS_ENTITY_CLEAR_LOS_TO_ENTITY_ADJUST_FOR_COVER);
		ENTITY.set_function("HAS_ENTITY_CLEAR_LOS_TO_ENTITY_IN_FRONT", LUA_NATIVE_ENTITY_HAS_ENTITY_CLEAR_LOS_TO_ENTITY_IN_FRONT);
		ENTITY.set_function("HAS_ENTITY_COLLIDED_WITH_ANYTHING", LUA_NATIVE_ENTITY_HAS_ENTITY_COLLIDED_WITH_ANYTHING);
		ENTITY.set_function("GET_LAST_ENTITY_HIT_BY_ENTITY_", LUA_NATIVE_ENTITY_GET_LAST_ENTITY_HIT_BY_ENTITY_);
		ENTITY.set_function("GET_LAST_MATERIAL_HIT_BY_ENTITY", LUA_NATIVE_ENTITY_GET_LAST_MATERIAL_HIT_BY_ENTITY);
		ENTITY.set_function("GET_COLLISION_NORMAL_OF_LAST_HIT_FOR_ENTITY", LUA_NATIVE_ENTITY_GET_COLLISION_NORMAL_OF_LAST_HIT_FOR_ENTITY);
		ENTITY.set_function("FORCE_ENTITY_AI_AND_ANIMATION_UPDATE", LUA_NATIVE_ENTITY_FORCE_ENTITY_AI_AND_ANIMATION_UPDATE);
		ENTITY.set_function("GET_ENTITY_ANIM_CURRENT_TIME", LUA_NATIVE_ENTITY_GET_ENTITY_ANIM_CURRENT_TIME);
		ENTITY.set_function("GET_ENTITY_ANIM_TOTAL_TIME", LUA_NATIVE_ENTITY_GET_ENTITY_ANIM_TOTAL_TIME);
		ENTITY.set_function("GET_ANIM_DURATION", LUA_NATIVE_ENTITY_GET_ANIM_DURATION);
		ENTITY.set_function("GET_ENTITY_ATTACHED_TO", LUA_NATIVE_ENTITY_GET_ENTITY_ATTACHED_TO);
		ENTITY.set_function("GET_ENTITY_COORDS", LUA_NATIVE_ENTITY_GET_ENTITY_COORDS);
		ENTITY.set_function("GET_ENTITY_FORWARD_VECTOR", LUA_NATIVE_ENTITY_GET_ENTITY_FORWARD_VECTOR);
		ENTITY.set_function("GET_ENTITY_FORWARD_X", LUA_NATIVE_ENTITY_GET_ENTITY_FORWARD_X);
		ENTITY.set_function("GET_ENTITY_FORWARD_Y", LUA_NATIVE_ENTITY_GET_ENTITY_FORWARD_Y);
		ENTITY.set_function("GET_ENTITY_HEADING", LUA_NATIVE_ENTITY_GET_ENTITY_HEADING);
		ENTITY.set_function("GET_ENTITY_HEADING_FROM_EULERS", LUA_NATIVE_ENTITY_GET_ENTITY_HEADING_FROM_EULERS);
		ENTITY.set_function("GET_ENTITY_HEALTH", LUA_NATIVE_ENTITY_GET_ENTITY_HEALTH);
		ENTITY.set_function("GET_ENTITY_MAX_HEALTH", LUA_NATIVE_ENTITY_GET_ENTITY_MAX_HEALTH);
		ENTITY.set_function("SET_ENTITY_MAX_HEALTH", LUA_NATIVE_ENTITY_SET_ENTITY_MAX_HEALTH);
		ENTITY.set_function("GET_ENTITY_HEIGHT", LUA_NATIVE_ENTITY_GET_ENTITY_HEIGHT);
		ENTITY.set_function("GET_ENTITY_HEIGHT_ABOVE_GROUND", LUA_NATIVE_ENTITY_GET_ENTITY_HEIGHT_ABOVE_GROUND);
		ENTITY.set_function("GET_ENTITY_MATRIX", LUA_NATIVE_ENTITY_GET_ENTITY_MATRIX);
		ENTITY.set_function("GET_ENTITY_MODEL", LUA_NATIVE_ENTITY_GET_ENTITY_MODEL);
		ENTITY.set_function("GET_OFFSET_FROM_ENTITY_GIVEN_WORLD_COORDS", LUA_NATIVE_ENTITY_GET_OFFSET_FROM_ENTITY_GIVEN_WORLD_COORDS);
		ENTITY.set_function("GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS", LUA_NATIVE_ENTITY_GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS);
		ENTITY.set_function("GET_ENTITY_PITCH", LUA_NATIVE_ENTITY_GET_ENTITY_PITCH);
		ENTITY.set_function("GET_ENTITY_QUATERNION", LUA_NATIVE_ENTITY_GET_ENTITY_QUATERNION);
		ENTITY.set_function("GET_ENTITY_ROLL", LUA_NATIVE_ENTITY_GET_ENTITY_ROLL);
		ENTITY.set_function("GET_ENTITY_ROTATION", LUA_NATIVE_ENTITY_GET_ENTITY_ROTATION);
		ENTITY.set_function("GET_ENTITY_ROTATION_VELOCITY", LUA_NATIVE_ENTITY_GET_ENTITY_ROTATION_VELOCITY);
		ENTITY.set_function("GET_ENTITY_SCRIPT", LUA_NATIVE_ENTITY_GET_ENTITY_SCRIPT);
		ENTITY.set_function("GET_ENTITY_SPEED", LUA_NATIVE_ENTITY_GET_ENTITY_SPEED);
		ENTITY.set_function("GET_ENTITY_SPEED_VECTOR", LUA_NATIVE_ENTITY_GET_ENTITY_SPEED_VECTOR);
		ENTITY.set_function("GET_ENTITY_UPRIGHT_VALUE", LUA_NATIVE_ENTITY_GET_ENTITY_UPRIGHT_VALUE);
		ENTITY.set_function("GET_ENTITY_VELOCITY", LUA_NATIVE_ENTITY_GET_ENTITY_VELOCITY);
		ENTITY.set_function("GET_OBJECT_INDEX_FROM_ENTITY_INDEX", LUA_NATIVE_ENTITY_GET_OBJECT_INDEX_FROM_ENTITY_INDEX);
		ENTITY.set_function("GET_PED_INDEX_FROM_ENTITY_INDEX", LUA_NATIVE_ENTITY_GET_PED_INDEX_FROM_ENTITY_INDEX);
		ENTITY.set_function("GET_VEHICLE_INDEX_FROM_ENTITY_INDEX", LUA_NATIVE_ENTITY_GET_VEHICLE_INDEX_FROM_ENTITY_INDEX);
		ENTITY.set_function("GET_WORLD_POSITION_OF_ENTITY_BONE", LUA_NATIVE_ENTITY_GET_WORLD_POSITION_OF_ENTITY_BONE);
		ENTITY.set_function("GET_NEAREST_PLAYER_TO_ENTITY", LUA_NATIVE_ENTITY_GET_NEAREST_PLAYER_TO_ENTITY);
		ENTITY.set_function("GET_NEAREST_PLAYER_TO_ENTITY_ON_TEAM", LUA_NATIVE_ENTITY_GET_NEAREST_PLAYER_TO_ENTITY_ON_TEAM);
		ENTITY.set_function("GET_NEAREST_PARTICIPANT_TO_ENTITY", LUA_NATIVE_ENTITY_GET_NEAREST_PARTICIPANT_TO_ENTITY);
		ENTITY.set_function("GET_ENTITY_TYPE", LUA_NATIVE_ENTITY_GET_ENTITY_TYPE);
		ENTITY.set_function("GET_ENTITY_POPULATION_TYPE", LUA_NATIVE_ENTITY_GET_ENTITY_POPULATION_TYPE);
		ENTITY.set_function("IS_AN_ENTITY", LUA_NATIVE_ENTITY_IS_AN_ENTITY);
		ENTITY.set_function("IS_ENTITY_A_PED", LUA_NATIVE_ENTITY_IS_ENTITY_A_PED);
		ENTITY.set_function("IS_ENTITY_A_MISSION_ENTITY", LUA_NATIVE_ENTITY_IS_ENTITY_A_MISSION_ENTITY);
		ENTITY.set_function("IS_ENTITY_A_VEHICLE", LUA_NATIVE_ENTITY_IS_ENTITY_A_VEHICLE);
		ENTITY.set_function("IS_ENTITY_AN_OBJECT", LUA_NATIVE_ENTITY_IS_ENTITY_AN_OBJECT);
		ENTITY.set_function("IS_ENTITY_AT_COORD", LUA_NATIVE_ENTITY_IS_ENTITY_AT_COORD);
		ENTITY.set_function("IS_ENTITY_AT_ENTITY", LUA_NATIVE_ENTITY_IS_ENTITY_AT_ENTITY);
		ENTITY.set_function("IS_ENTITY_ATTACHED", LUA_NATIVE_ENTITY_IS_ENTITY_ATTACHED);
		ENTITY.set_function("IS_ENTITY_ATTACHED_TO_ANY_OBJECT", LUA_NATIVE_ENTITY_IS_ENTITY_ATTACHED_TO_ANY_OBJECT);
		ENTITY.set_function("IS_ENTITY_ATTACHED_TO_ANY_PED", LUA_NATIVE_ENTITY_IS_ENTITY_ATTACHED_TO_ANY_PED);
		ENTITY.set_function("IS_ENTITY_ATTACHED_TO_ANY_VEHICLE", LUA_NATIVE_ENTITY_IS_ENTITY_ATTACHED_TO_ANY_VEHICLE);
		ENTITY.set_function("IS_ENTITY_ATTACHED_TO_ENTITY", LUA_NATIVE_ENTITY_IS_ENTITY_ATTACHED_TO_ENTITY);
		ENTITY.set_function("IS_ENTITY_DEAD", LUA_NATIVE_ENTITY_IS_ENTITY_DEAD);
		ENTITY.set_function("IS_ENTITY_IN_AIR", LUA_NATIVE_ENTITY_IS_ENTITY_IN_AIR);
		ENTITY.set_function("IS_ENTITY_IN_ANGLED_AREA", LUA_NATIVE_ENTITY_IS_ENTITY_IN_ANGLED_AREA);
		ENTITY.set_function("IS_ENTITY_IN_AREA", LUA_NATIVE_ENTITY_IS_ENTITY_IN_AREA);
		ENTITY.set_function("IS_ENTITY_IN_ZONE", LUA_NATIVE_ENTITY_IS_ENTITY_IN_ZONE);
		ENTITY.set_function("IS_ENTITY_IN_WATER", LUA_NATIVE_ENTITY_IS_ENTITY_IN_WATER);
		ENTITY.set_function("GET_ENTITY_SUBMERGED_LEVEL", LUA_NATIVE_ENTITY_GET_ENTITY_SUBMERGED_LEVEL);
		ENTITY.set_function("SET_ENTITY_REQUIRES_MORE_EXPENSIVE_RIVER_CHECK", LUA_NATIVE_ENTITY_SET_ENTITY_REQUIRES_MORE_EXPENSIVE_RIVER_CHECK);
		ENTITY.set_function("IS_ENTITY_ON_SCREEN", LUA_NATIVE_ENTITY_IS_ENTITY_ON_SCREEN);
		ENTITY.set_function("IS_ENTITY_PLAYING_ANIM", LUA_NATIVE_ENTITY_IS_ENTITY_PLAYING_ANIM);
		ENTITY.set_function("IS_ENTITY_STATIC", LUA_NATIVE_ENTITY_IS_ENTITY_STATIC);
		ENTITY.set_function("IS_ENTITY_TOUCHING_ENTITY", LUA_NATIVE_ENTITY_IS_ENTITY_TOUCHING_ENTITY);
		ENTITY.set_function("IS_ENTITY_TOUCHING_MODEL", LUA_NATIVE_ENTITY_IS_ENTITY_TOUCHING_MODEL);
		ENTITY.set_function("IS_ENTITY_UPRIGHT", LUA_NATIVE_ENTITY_IS_ENTITY_UPRIGHT);
		ENTITY.set_function("IS_ENTITY_UPSIDEDOWN", LUA_NATIVE_ENTITY_IS_ENTITY_UPSIDEDOWN);
		ENTITY.set_function("IS_ENTITY_VISIBLE", LUA_NATIVE_ENTITY_IS_ENTITY_VISIBLE);
		ENTITY.set_function("IS_ENTITY_VISIBLE_TO_SCRIPT", LUA_NATIVE_ENTITY_IS_ENTITY_VISIBLE_TO_SCRIPT);
		ENTITY.set_function("IS_ENTITY_OCCLUDED", LUA_NATIVE_ENTITY_IS_ENTITY_OCCLUDED);
		ENTITY.set_function("WOULD_ENTITY_BE_OCCLUDED", LUA_NATIVE_ENTITY_WOULD_ENTITY_BE_OCCLUDED);
		ENTITY.set_function("IS_ENTITY_WAITING_FOR_WORLD_COLLISION", LUA_NATIVE_ENTITY_IS_ENTITY_WAITING_FOR_WORLD_COLLISION);
		ENTITY.set_function("APPLY_FORCE_TO_ENTITY_CENTER_OF_MASS", LUA_NATIVE_ENTITY_APPLY_FORCE_TO_ENTITY_CENTER_OF_MASS);
		ENTITY.set_function("APPLY_FORCE_TO_ENTITY", LUA_NATIVE_ENTITY_APPLY_FORCE_TO_ENTITY);
		ENTITY.set_function("ATTACH_ENTITY_TO_ENTITY", LUA_NATIVE_ENTITY_ATTACH_ENTITY_TO_ENTITY);
		ENTITY.set_function("ATTACH_ENTITY_BONE_TO_ENTITY_BONE", LUA_NATIVE_ENTITY_ATTACH_ENTITY_BONE_TO_ENTITY_BONE);
		ENTITY.set_function("ATTACH_ENTITY_BONE_TO_ENTITY_BONE_Y_FORWARD", LUA_NATIVE_ENTITY_ATTACH_ENTITY_BONE_TO_ENTITY_BONE_Y_FORWARD);
		ENTITY.set_function("ATTACH_ENTITY_TO_ENTITY_PHYSICALLY", LUA_NATIVE_ENTITY_ATTACH_ENTITY_TO_ENTITY_PHYSICALLY);
		ENTITY.set_function("ATTACH_ENTITY_TO_ENTITY_PHYSICALLY_OVERRIDE_INVERSE_MASS", LUA_NATIVE_ENTITY_ATTACH_ENTITY_TO_ENTITY_PHYSICALLY_OVERRIDE_INVERSE_MASS);
		ENTITY.set_function("PROCESS_ENTITY_ATTACHMENTS", LUA_NATIVE_ENTITY_PROCESS_ENTITY_ATTACHMENTS);
		ENTITY.set_function("GET_ENTITY_BONE_INDEX_BY_NAME", LUA_NATIVE_ENTITY_GET_ENTITY_BONE_INDEX_BY_NAME);
		ENTITY.set_function("CLEAR_ENTITY_LAST_DAMAGE_ENTITY", LUA_NATIVE_ENTITY_CLEAR_ENTITY_LAST_DAMAGE_ENTITY);
		ENTITY.set_function("DELETE_ENTITY", LUA_NATIVE_ENTITY_DELETE_ENTITY);
		ENTITY.set_function("DETACH_ENTITY", LUA_NATIVE_ENTITY_DETACH_ENTITY);
		ENTITY.set_function("FREEZE_ENTITY_POSITION", LUA_NATIVE_ENTITY_FREEZE_ENTITY_POSITION);
		ENTITY.set_function("SET_ENTITY_SHOULD_FREEZE_WAITING_ON_COLLISION", LUA_NATIVE_ENTITY_SET_ENTITY_SHOULD_FREEZE_WAITING_ON_COLLISION);
		ENTITY.set_function("PLAY_ENTITY_ANIM", LUA_NATIVE_ENTITY_PLAY_ENTITY_ANIM);
		ENTITY.set_function("PLAY_SYNCHRONIZED_ENTITY_ANIM", LUA_NATIVE_ENTITY_PLAY_SYNCHRONIZED_ENTITY_ANIM);
		ENTITY.set_function("PLAY_SYNCHRONIZED_MAP_ENTITY_ANIM", LUA_NATIVE_ENTITY_PLAY_SYNCHRONIZED_MAP_ENTITY_ANIM);
		ENTITY.set_function("STOP_SYNCHRONIZED_MAP_ENTITY_ANIM", LUA_NATIVE_ENTITY_STOP_SYNCHRONIZED_MAP_ENTITY_ANIM);
		ENTITY.set_function("STOP_ENTITY_ANIM", LUA_NATIVE_ENTITY_STOP_ENTITY_ANIM);
		ENTITY.set_function("STOP_SYNCHRONIZED_ENTITY_ANIM", LUA_NATIVE_ENTITY_STOP_SYNCHRONIZED_ENTITY_ANIM);
		ENTITY.set_function("HAS_ANIM_EVENT_FIRED", LUA_NATIVE_ENTITY_HAS_ANIM_EVENT_FIRED);
		ENTITY.set_function("FIND_ANIM_EVENT_PHASE", LUA_NATIVE_ENTITY_FIND_ANIM_EVENT_PHASE);
		ENTITY.set_function("SET_ENTITY_ANIM_CURRENT_TIME", LUA_NATIVE_ENTITY_SET_ENTITY_ANIM_CURRENT_TIME);
		ENTITY.set_function("SET_ENTITY_ANIM_SPEED", LUA_NATIVE_ENTITY_SET_ENTITY_ANIM_SPEED);
		ENTITY.set_function("SET_ENTITY_AS_MISSION_ENTITY", LUA_NATIVE_ENTITY_SET_ENTITY_AS_MISSION_ENTITY);
		ENTITY.set_function("SET_ENTITY_AS_NO_LONGER_NEEDED", LUA_NATIVE_ENTITY_SET_ENTITY_AS_NO_LONGER_NEEDED);
		ENTITY.set_function("SET_PED_AS_NO_LONGER_NEEDED", LUA_NATIVE_ENTITY_SET_PED_AS_NO_LONGER_NEEDED);
		ENTITY.set_function("SET_VEHICLE_AS_NO_LONGER_NEEDED", LUA_NATIVE_ENTITY_SET_VEHICLE_AS_NO_LONGER_NEEDED);
		ENTITY.set_function("SET_OBJECT_AS_NO_LONGER_NEEDED", LUA_NATIVE_ENTITY_SET_OBJECT_AS_NO_LONGER_NEEDED);
		ENTITY.set_function("SET_ENTITY_CAN_BE_DAMAGED", LUA_NATIVE_ENTITY_SET_ENTITY_CAN_BE_DAMAGED);
		ENTITY.set_function("GET_ENTITY_CAN_BE_DAMAGED", LUA_NATIVE_ENTITY_GET_ENTITY_CAN_BE_DAMAGED);
		ENTITY.set_function("SET_ENTITY_CAN_BE_DAMAGED_BY_RELATIONSHIP_GROUP", LUA_NATIVE_ENTITY_SET_ENTITY_CAN_BE_DAMAGED_BY_RELATIONSHIP_GROUP);
		ENTITY.set_function("SET_ENTITY_CAN_ONLY_BE_DAMAGED_BY_SCRIPT_PARTICIPANTS", LUA_NATIVE_ENTITY_SET_ENTITY_CAN_ONLY_BE_DAMAGED_BY_SCRIPT_PARTICIPANTS);
		ENTITY.set_function("SET_ENTITY_CAN_BE_TARGETED_WITHOUT_LOS", LUA_NATIVE_ENTITY_SET_ENTITY_CAN_BE_TARGETED_WITHOUT_LOS);
		ENTITY.set_function("SET_ENTITY_COLLISION", LUA_NATIVE_ENTITY_SET_ENTITY_COLLISION);
		ENTITY.set_function("GET_ENTITY_COLLISION_DISABLED", LUA_NATIVE_ENTITY_GET_ENTITY_COLLISION_DISABLED);
		ENTITY.set_function("SET_ENTITY_COMPLETELY_DISABLE_COLLISION", LUA_NATIVE_ENTITY_SET_ENTITY_COMPLETELY_DISABLE_COLLISION);
		ENTITY.set_function("SET_ENTITY_COORDS", LUA_NATIVE_ENTITY_SET_ENTITY_COORDS);
		ENTITY.set_function("SET_ENTITY_COORDS_WITHOUT_PLANTS_RESET", LUA_NATIVE_ENTITY_SET_ENTITY_COORDS_WITHOUT_PLANTS_RESET);
		ENTITY.set_function("SET_ENTITY_COORDS_NO_OFFSET", LUA_NATIVE_ENTITY_SET_ENTITY_COORDS_NO_OFFSET);
		ENTITY.set_function("SET_ENTITY_DYNAMIC", LUA_NATIVE_ENTITY_SET_ENTITY_DYNAMIC);
		ENTITY.set_function("SET_ENTITY_HEADING", LUA_NATIVE_ENTITY_SET_ENTITY_HEADING);
		ENTITY.set_function("SET_ENTITY_HEALTH", LUA_NATIVE_ENTITY_SET_ENTITY_HEALTH);
		ENTITY.set_function("SET_ENTITY_INVINCIBLE", LUA_NATIVE_ENTITY_SET_ENTITY_INVINCIBLE);
		ENTITY.set_function("SET_ENTITY_IS_TARGET_PRIORITY", LUA_NATIVE_ENTITY_SET_ENTITY_IS_TARGET_PRIORITY);
		ENTITY.set_function("SET_ENTITY_LIGHTS", LUA_NATIVE_ENTITY_SET_ENTITY_LIGHTS);
		ENTITY.set_function("SET_ENTITY_LOAD_COLLISION_FLAG", LUA_NATIVE_ENTITY_SET_ENTITY_LOAD_COLLISION_FLAG);
		ENTITY.set_function("HAS_COLLISION_LOADED_AROUND_ENTITY", LUA_NATIVE_ENTITY_HAS_COLLISION_LOADED_AROUND_ENTITY);
		ENTITY.set_function("SET_ENTITY_MAX_SPEED", LUA_NATIVE_ENTITY_SET_ENTITY_MAX_SPEED);
		ENTITY.set_function("SET_ENTITY_ONLY_DAMAGED_BY_PLAYER", LUA_NATIVE_ENTITY_SET_ENTITY_ONLY_DAMAGED_BY_PLAYER);
		ENTITY.set_function("SET_ENTITY_ONLY_DAMAGED_BY_RELATIONSHIP_GROUP", LUA_NATIVE_ENTITY_SET_ENTITY_ONLY_DAMAGED_BY_RELATIONSHIP_GROUP);
		ENTITY.set_function("SET_ENTITY_PROOFS", LUA_NATIVE_ENTITY_SET_ENTITY_PROOFS);
		ENTITY.set_function("GET_ENTITY_PROOFS", LUA_NATIVE_ENTITY_GET_ENTITY_PROOFS);
		ENTITY.set_function("SET_ENTITY_QUATERNION", LUA_NATIVE_ENTITY_SET_ENTITY_QUATERNION);
		ENTITY.set_function("SET_ENTITY_RECORDS_COLLISIONS", LUA_NATIVE_ENTITY_SET_ENTITY_RECORDS_COLLISIONS);
		ENTITY.set_function("SET_ENTITY_ROTATION", LUA_NATIVE_ENTITY_SET_ENTITY_ROTATION);
		ENTITY.set_function("SET_ENTITY_VISIBLE", LUA_NATIVE_ENTITY_SET_ENTITY_VISIBLE);
		ENTITY.set_function("SET_ENTITY_WATER_REFLECTION_FLAG", LUA_NATIVE_ENTITY_SET_ENTITY_WATER_REFLECTION_FLAG);
		ENTITY.set_function("SET_ENTITY_MIRROR_REFLECTION_FLAG", LUA_NATIVE_ENTITY_SET_ENTITY_MIRROR_REFLECTION_FLAG);
		ENTITY.set_function("SET_ENTITY_VELOCITY", LUA_NATIVE_ENTITY_SET_ENTITY_VELOCITY);
		ENTITY.set_function("SET_ENTITY_ANGULAR_VELOCITY", LUA_NATIVE_ENTITY_SET_ENTITY_ANGULAR_VELOCITY);
		ENTITY.set_function("SET_ENTITY_HAS_GRAVITY", LUA_NATIVE_ENTITY_SET_ENTITY_HAS_GRAVITY);
		ENTITY.set_function("SET_ENTITY_LOD_DIST", LUA_NATIVE_ENTITY_SET_ENTITY_LOD_DIST);
		ENTITY.set_function("GET_ENTITY_LOD_DIST", LUA_NATIVE_ENTITY_GET_ENTITY_LOD_DIST);
		ENTITY.set_function("SET_ENTITY_ALPHA", LUA_NATIVE_ENTITY_SET_ENTITY_ALPHA);
		ENTITY.set_function("GET_ENTITY_ALPHA", LUA_NATIVE_ENTITY_GET_ENTITY_ALPHA);
		ENTITY.set_function("RESET_ENTITY_ALPHA", LUA_NATIVE_ENTITY_RESET_ENTITY_ALPHA);
		ENTITY.set_function("RESET_PICKUP_ENTITY_GLOW", LUA_NATIVE_ENTITY_RESET_PICKUP_ENTITY_GLOW);
		ENTITY.set_function("SET_PICKUP_COLLIDES_WITH_PROJECTILES", LUA_NATIVE_ENTITY_SET_PICKUP_COLLIDES_WITH_PROJECTILES);
		ENTITY.set_function("SET_ENTITY_SORT_BIAS", LUA_NATIVE_ENTITY_SET_ENTITY_SORT_BIAS);
		ENTITY.set_function("SET_ENTITY_ALWAYS_PRERENDER", LUA_NATIVE_ENTITY_SET_ENTITY_ALWAYS_PRERENDER);
		ENTITY.set_function("SET_ENTITY_RENDER_SCORCHED", LUA_NATIVE_ENTITY_SET_ENTITY_RENDER_SCORCHED);
		ENTITY.set_function("SET_ENTITY_TRAFFICLIGHT_OVERRIDE", LUA_NATIVE_ENTITY_SET_ENTITY_TRAFFICLIGHT_OVERRIDE);
		ENTITY.set_function("SET_ENTITY_IS_IN_VEHICLE", LUA_NATIVE_ENTITY_SET_ENTITY_IS_IN_VEHICLE);
		ENTITY.set_function("CREATE_MODEL_SWAP", LUA_NATIVE_ENTITY_CREATE_MODEL_SWAP);
		ENTITY.set_function("REMOVE_MODEL_SWAP", LUA_NATIVE_ENTITY_REMOVE_MODEL_SWAP);
		ENTITY.set_function("CREATE_MODEL_HIDE", LUA_NATIVE_ENTITY_CREATE_MODEL_HIDE);
		ENTITY.set_function("CREATE_MODEL_HIDE_EXCLUDING_SCRIPT_OBJECTS", LUA_NATIVE_ENTITY_CREATE_MODEL_HIDE_EXCLUDING_SCRIPT_OBJECTS);
		ENTITY.set_function("REMOVE_MODEL_HIDE", LUA_NATIVE_ENTITY_REMOVE_MODEL_HIDE);
		ENTITY.set_function("CREATE_FORCED_OBJECT", LUA_NATIVE_ENTITY_CREATE_FORCED_OBJECT);
		ENTITY.set_function("REMOVE_FORCED_OBJECT", LUA_NATIVE_ENTITY_REMOVE_FORCED_OBJECT);
		ENTITY.set_function("SET_ENTITY_NO_COLLISION_ENTITY", LUA_NATIVE_ENTITY_SET_ENTITY_NO_COLLISION_ENTITY);
		ENTITY.set_function("SET_ENTITY_MOTION_BLUR", LUA_NATIVE_ENTITY_SET_ENTITY_MOTION_BLUR);
		ENTITY.set_function("SET_CAN_AUTO_VAULT_ON_ENTITY", LUA_NATIVE_ENTITY_SET_CAN_AUTO_VAULT_ON_ENTITY);
		ENTITY.set_function("SET_CAN_CLIMB_ON_ENTITY", LUA_NATIVE_ENTITY_SET_CAN_CLIMB_ON_ENTITY);
		ENTITY.set_function("SET_WAIT_FOR_COLLISIONS_BEFORE_PROBE", LUA_NATIVE_ENTITY_SET_WAIT_FOR_COLLISIONS_BEFORE_PROBE);
		ENTITY.set_function("SET_ENTITY_NOWEAPONDECALS", LUA_NATIVE_ENTITY_SET_ENTITY_NOWEAPONDECALS);
		ENTITY.set_function("SET_ENTITY_USE_MAX_DISTANCE_FOR_WATER_REFLECTION", LUA_NATIVE_ENTITY_SET_ENTITY_USE_MAX_DISTANCE_FOR_WATER_REFLECTION);
		ENTITY.set_function("GET_ENTITY_BONE_ROTATION", LUA_NATIVE_ENTITY_GET_ENTITY_BONE_ROTATION);
		ENTITY.set_function("GET_ENTITY_BONE_POSTION", LUA_NATIVE_ENTITY_GET_ENTITY_BONE_POSTION);
		ENTITY.set_function("GET_ENTITY_BONE_OBJECT_ROTATION", LUA_NATIVE_ENTITY_GET_ENTITY_BONE_OBJECT_ROTATION);
		ENTITY.set_function("GET_ENTITY_BONE_OBJECT_POSTION", LUA_NATIVE_ENTITY_GET_ENTITY_BONE_OBJECT_POSTION);
		ENTITY.set_function("GET_ENTITY_BONE_COUNT", LUA_NATIVE_ENTITY_GET_ENTITY_BONE_COUNT);
		ENTITY.set_function("ENABLE_ENTITY_BULLET_COLLISION", LUA_NATIVE_ENTITY_ENABLE_ENTITY_BULLET_COLLISION);
		ENTITY.set_function("SET_ENTITY_CAN_ONLY_BE_DAMAGED_BY_ENTITY", LUA_NATIVE_ENTITY_SET_ENTITY_CAN_ONLY_BE_DAMAGED_BY_ENTITY);
		ENTITY.set_function("SET_ENTITY_CANT_CAUSE_COLLISION_DAMAGED_ENTITY", LUA_NATIVE_ENTITY_SET_ENTITY_CANT_CAUSE_COLLISION_DAMAGED_ENTITY);
		ENTITY.set_function("SET_ALLOW_MIGRATE_TO_SPECTATOR", LUA_NATIVE_ENTITY_SET_ALLOW_MIGRATE_TO_SPECTATOR);
		ENTITY.set_function("GET_ENTITY_OF_TYPE_ATTACHED_TO_ENTITY", LUA_NATIVE_ENTITY_GET_ENTITY_OF_TYPE_ATTACHED_TO_ENTITY);
		ENTITY.set_function("SET_PICK_UP_BY_CARGOBOB_DISABLED", LUA_NATIVE_ENTITY_SET_PICK_UP_BY_CARGOBOB_DISABLED);
	}
}
