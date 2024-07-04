#include "lua_native_binding.hpp"
#include "natives.hpp"

namespace lua::native
{
	static Object LUA_NATIVE_OBJECT_CREATE_OBJECT(Hash modelHash, float x, float y, float z, bool isNetwork, bool bScriptHostObj, bool dynamic)
	{
		auto retval = OBJECT::CREATE_OBJECT(modelHash, x, y, z, isNetwork, bScriptHostObj, dynamic);
		return retval;
	}

	static Object LUA_NATIVE_OBJECT_CREATE_OBJECT_NO_OFFSET(Hash modelHash, float x, float y, float z, bool isNetwork, bool bScriptHostObj, bool dynamic, Any p7)
	{
		auto retval = OBJECT::CREATE_OBJECT_NO_OFFSET(modelHash, x, y, z, isNetwork, bScriptHostObj, dynamic, p7);
		return retval;
	}

	static Object LUA_NATIVE_OBJECT_DELETE_OBJECT(Object object)
	{
		OBJECT::DELETE_OBJECT(&object);
		return object;
	}

	static bool LUA_NATIVE_OBJECT_PLACE_OBJECT_ON_GROUND_PROPERLY(Object object)
	{
		auto retval = (bool)OBJECT::PLACE_OBJECT_ON_GROUND_PROPERLY(object);
		return retval;
	}

	static bool LUA_NATIVE_OBJECT_PLACE_OBJECT_ON_GROUND_OR_OBJECT_PROPERLY(Object object)
	{
		auto retval = (bool)OBJECT::PLACE_OBJECT_ON_GROUND_OR_OBJECT_PROPERLY(object);
		return retval;
	}

	static bool LUA_NATIVE_OBJECT_ROTATE_OBJECT(Object object, float p1, float p2, bool p3)
	{
		auto retval = (bool)OBJECT::ROTATE_OBJECT(object, p1, p2, p3);
		return retval;
	}

	static bool LUA_NATIVE_OBJECT_SLIDE_OBJECT(Object object, float toX, float toY, float toZ, float speedX, float speedY, float speedZ, bool collision)
	{
		auto retval = (bool)OBJECT::SLIDE_OBJECT(object, toX, toY, toZ, speedX, speedY, speedZ, collision);
		return retval;
	}

	static void LUA_NATIVE_OBJECT_SET_OBJECT_TARGETTABLE(Object object, bool targettable, Any p2)
	{
		OBJECT::SET_OBJECT_TARGETTABLE(object, targettable, p2);
	}

	static void LUA_NATIVE_OBJECT_SET_OBJECT_FORCE_VEHICLES_TO_AVOID(Object object, bool toggle)
	{
		OBJECT::SET_OBJECT_FORCE_VEHICLES_TO_AVOID(object, toggle);
	}

	static Object LUA_NATIVE_OBJECT_GET_CLOSEST_OBJECT_OF_TYPE(float x, float y, float z, float radius, Hash modelHash, bool isMission, bool p6, bool p7)
	{
		auto retval = OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(x, y, z, radius, modelHash, isMission, p6, p7);
		return retval;
	}

	static bool LUA_NATIVE_OBJECT_HAS_OBJECT_BEEN_BROKEN(Object object, Any p1)
	{
		auto retval = (bool)OBJECT::HAS_OBJECT_BEEN_BROKEN(object, p1);
		return retval;
	}

	static bool LUA_NATIVE_OBJECT_HAS_CLOSEST_OBJECT_OF_TYPE_BEEN_BROKEN(float p0, float p1, float p2, float p3, Hash modelHash, Any p5)
	{
		auto retval = (bool)OBJECT::HAS_CLOSEST_OBJECT_OF_TYPE_BEEN_BROKEN(p0, p1, p2, p3, modelHash, p5);
		return retval;
	}

	static bool LUA_NATIVE_OBJECT_HAS_CLOSEST_OBJECT_OF_TYPE_BEEN_COMPLETELY_DESTROYED(float x, float y, float z, float radius, Hash modelHash, bool p5)
	{
		auto retval = (bool)OBJECT::HAS_CLOSEST_OBJECT_OF_TYPE_BEEN_COMPLETELY_DESTROYED(x, y, z, radius, modelHash, p5);
		return retval;
	}

	static bool LUA_NATIVE_OBJECT_GET_HAS_OBJECT_BEEN_COMPLETELY_DESTROYED(Any p0)
	{
		auto retval = (bool)OBJECT::GET_HAS_OBJECT_BEEN_COMPLETELY_DESTROYED(p0);
		return retval;
	}

	static Vector3 LUA_NATIVE_OBJECT_GET_OFFSET_FROM_COORD_AND_HEADING_IN_WORLD_COORDS(float xPos, float yPos, float zPos, float heading, float xOffset, float yOffset, float zOffset)
	{
		auto retval = OBJECT::GET_OFFSET_FROM_COORD_AND_HEADING_IN_WORLD_COORDS(xPos, yPos, zPos, heading, xOffset, yOffset, zOffset);
		return retval;
	}

	static std::tuple<bool, Vector3, Vector3> LUA_NATIVE_OBJECT_GET_COORDS_AND_ROTATION_OF_CLOSEST_OBJECT_OF_TYPE(float x, float y, float z, float radius, Hash modelHash, Vector3 outPosition, Vector3 outRotation, int rotationOrder)
	{
		std::tuple<bool, Vector3, Vector3> return_values;
		std::get<0>(return_values) = (bool)OBJECT::GET_COORDS_AND_ROTATION_OF_CLOSEST_OBJECT_OF_TYPE(x, y, z, radius, modelHash, &outPosition, &outRotation, rotationOrder);
		std::get<1>(return_values) = outPosition;
		std::get<2>(return_values) = outRotation;

		return return_values;
	}

	static void LUA_NATIVE_OBJECT_SET_STATE_OF_CLOSEST_DOOR_OF_TYPE(Hash type, float x, float y, float z, bool locked, float heading, bool p6)
	{
		OBJECT::SET_STATE_OF_CLOSEST_DOOR_OF_TYPE(type, x, y, z, locked, heading, p6);
	}

	static std::tuple<bool, float> LUA_NATIVE_OBJECT_GET_STATE_OF_CLOSEST_DOOR_OF_TYPE(Hash type, float x, float y, float z, bool locked, float heading)
	{
		std::tuple<bool, float> return_values;
		OBJECT::GET_STATE_OF_CLOSEST_DOOR_OF_TYPE(type, x, y, z, (BOOL*)&locked, &heading);
		std::get<0>(return_values) = locked;
		std::get<1>(return_values) = heading;

		return return_values;
	}

	static void LUA_NATIVE_OBJECT_SET_LOCKED_UNSTREAMED_IN_DOOR_OF_TYPE(Hash modelHash, float x, float y, float z, bool locked, float xRotMult, float yRotMult, float zRotMult)
	{
		OBJECT::SET_LOCKED_UNSTREAMED_IN_DOOR_OF_TYPE(modelHash, x, y, z, locked, xRotMult, yRotMult, zRotMult);
	}

	static void LUA_NATIVE_OBJECT_PLAY_OBJECT_AUTO_START_ANIM(Any p0)
	{
		OBJECT::PLAY_OBJECT_AUTO_START_ANIM(p0);
	}

	static void LUA_NATIVE_OBJECT_ADD_DOOR_TO_SYSTEM(Hash doorHash, Hash modelHash, float x, float y, float z, bool p5, bool scriptDoor, bool isLocal, Any p8)
	{
		OBJECT::ADD_DOOR_TO_SYSTEM(doorHash, modelHash, x, y, z, p5, scriptDoor, isLocal, p8);
	}

	static void LUA_NATIVE_OBJECT_REMOVE_DOOR_FROM_SYSTEM(Hash doorHash, Any p1)
	{
		OBJECT::REMOVE_DOOR_FROM_SYSTEM(doorHash, p1);
	}

	static void LUA_NATIVE_OBJECT_DOOR_SYSTEM_SET_DOOR_STATE(Hash doorHash, int state, bool requestDoor, bool forceUpdate)
	{
		OBJECT::DOOR_SYSTEM_SET_DOOR_STATE(doorHash, state, requestDoor, forceUpdate);
	}

	static int LUA_NATIVE_OBJECT_DOOR_SYSTEM_GET_DOOR_STATE(Hash doorHash)
	{
		auto retval = OBJECT::DOOR_SYSTEM_GET_DOOR_STATE(doorHash);
		return retval;
	}

	static int LUA_NATIVE_OBJECT_DOOR_SYSTEM_GET_DOOR_PENDING_STATE(Hash doorHash)
	{
		auto retval = OBJECT::DOOR_SYSTEM_GET_DOOR_PENDING_STATE(doorHash);
		return retval;
	}

	static void LUA_NATIVE_OBJECT_DOOR_SYSTEM_SET_AUTOMATIC_RATE(Hash doorHash, float rate, bool requestDoor, bool forceUpdate)
	{
		OBJECT::DOOR_SYSTEM_SET_AUTOMATIC_RATE(doorHash, rate, requestDoor, forceUpdate);
	}

	static void LUA_NATIVE_OBJECT_DOOR_SYSTEM_SET_AUTOMATIC_DISTANCE(Hash doorHash, float distance, bool requestDoor, bool forceUpdate)
	{
		OBJECT::DOOR_SYSTEM_SET_AUTOMATIC_DISTANCE(doorHash, distance, requestDoor, forceUpdate);
	}

	static void LUA_NATIVE_OBJECT_DOOR_SYSTEM_SET_OPEN_RATIO(Hash doorHash, float ajar, bool requestDoor, bool forceUpdate)
	{
		OBJECT::DOOR_SYSTEM_SET_OPEN_RATIO(doorHash, ajar, requestDoor, forceUpdate);
	}

	static float LUA_NATIVE_OBJECT_DOOR_SYSTEM_GET_AUTOMATIC_DISTANCE(Hash doorHash)
	{
		auto retval = OBJECT::DOOR_SYSTEM_GET_AUTOMATIC_DISTANCE(doorHash);
		return retval;
	}

	static float LUA_NATIVE_OBJECT_DOOR_SYSTEM_GET_OPEN_RATIO(Hash doorHash)
	{
		auto retval = OBJECT::DOOR_SYSTEM_GET_OPEN_RATIO(doorHash);
		return retval;
	}

	static void LUA_NATIVE_OBJECT_DOOR_SYSTEM_SET_SPRING_REMOVED(Hash doorHash, bool removed, bool requestDoor, bool forceUpdate)
	{
		OBJECT::DOOR_SYSTEM_SET_SPRING_REMOVED(doorHash, removed, requestDoor, forceUpdate);
	}

	static void LUA_NATIVE_OBJECT_DOOR_SYSTEM_SET_HOLD_OPEN(Hash doorHash, bool toggle)
	{
		OBJECT::DOOR_SYSTEM_SET_HOLD_OPEN(doorHash, toggle);
	}

	static void LUA_NATIVE_OBJECT_DOOR_SYSTEM_SET_DOOR_OPEN_FOR_RACES(Hash doorHash, bool p1)
	{
		OBJECT::DOOR_SYSTEM_SET_DOOR_OPEN_FOR_RACES(doorHash, p1);
	}

	static bool LUA_NATIVE_OBJECT_IS_DOOR_REGISTERED_WITH_SYSTEM(Hash doorHash)
	{
		auto retval = (bool)OBJECT::IS_DOOR_REGISTERED_WITH_SYSTEM(doorHash);
		return retval;
	}

	static bool LUA_NATIVE_OBJECT_IS_DOOR_CLOSED(Hash doorHash)
	{
		auto retval = (bool)OBJECT::IS_DOOR_CLOSED(doorHash);
		return retval;
	}

	static void LUA_NATIVE_OBJECT_OPEN_ALL_BARRIERS_FOR_RACE(bool p0)
	{
		OBJECT::OPEN_ALL_BARRIERS_FOR_RACE(p0);
	}

	static void LUA_NATIVE_OBJECT_CLOSE_ALL_BARRIERS_FOR_RACE()
	{
		OBJECT::CLOSE_ALL_BARRIERS_FOR_RACE();
	}

	static bool LUA_NATIVE_OBJECT_DOOR_SYSTEM_GET_IS_PHYSICS_LOADED(Any p0)
	{
		auto retval = (bool)OBJECT::DOOR_SYSTEM_GET_IS_PHYSICS_LOADED(p0);
		return retval;
	}

	static std::tuple<bool, Hash> LUA_NATIVE_OBJECT_DOOR_SYSTEM_FIND_EXISTING_DOOR(float x, float y, float z, Hash modelHash, Hash outDoorHash)
	{
		std::tuple<bool, Hash> return_values;
		std::get<0>(return_values) = (bool)OBJECT::DOOR_SYSTEM_FIND_EXISTING_DOOR(x, y, z, modelHash, &outDoorHash);
		std::get<1>(return_values) = outDoorHash;

		return return_values;
	}

	static bool LUA_NATIVE_OBJECT_IS_GARAGE_EMPTY(Hash garageHash, bool p1, int p2)
	{
		auto retval = (bool)OBJECT::IS_GARAGE_EMPTY(garageHash, p1, p2);
		return retval;
	}

	static bool LUA_NATIVE_OBJECT_IS_PLAYER_ENTIRELY_INSIDE_GARAGE(Hash garageHash, Player player, float p2, int p3)
	{
		auto retval = (bool)OBJECT::IS_PLAYER_ENTIRELY_INSIDE_GARAGE(garageHash, player, p2, p3);
		return retval;
	}

	static bool LUA_NATIVE_OBJECT_IS_PLAYER_PARTIALLY_INSIDE_GARAGE(Hash garageHash, Player player, int p2)
	{
		auto retval = (bool)OBJECT::IS_PLAYER_PARTIALLY_INSIDE_GARAGE(garageHash, player, p2);
		return retval;
	}

	static bool LUA_NATIVE_OBJECT_ARE_ENTITIES_ENTIRELY_INSIDE_GARAGE(Hash garageHash, bool p1, bool p2, bool p3, Any p4)
	{
		auto retval = (bool)OBJECT::ARE_ENTITIES_ENTIRELY_INSIDE_GARAGE(garageHash, p1, p2, p3, p4);
		return retval;
	}

	static bool LUA_NATIVE_OBJECT_IS_ANY_ENTITY_ENTIRELY_INSIDE_GARAGE(Hash garageHash, bool p1, bool p2, bool p3, Any p4)
	{
		auto retval = (bool)OBJECT::IS_ANY_ENTITY_ENTIRELY_INSIDE_GARAGE(garageHash, p1, p2, p3, p4);
		return retval;
	}

	static bool LUA_NATIVE_OBJECT_IS_OBJECT_ENTIRELY_INSIDE_GARAGE(Hash garageHash, Entity entity, float p2, int p3)
	{
		auto retval = (bool)OBJECT::IS_OBJECT_ENTIRELY_INSIDE_GARAGE(garageHash, entity, p2, p3);
		return retval;
	}

	static bool LUA_NATIVE_OBJECT_IS_OBJECT_PARTIALLY_INSIDE_GARAGE(Hash garageHash, Entity entity, int p2)
	{
		auto retval = (bool)OBJECT::IS_OBJECT_PARTIALLY_INSIDE_GARAGE(garageHash, entity, p2);
		return retval;
	}

	static void LUA_NATIVE_OBJECT_CLEAR_GARAGE(Hash garageHash, bool isNetwork)
	{
		OBJECT::CLEAR_GARAGE(garageHash, isNetwork);
	}

	static void LUA_NATIVE_OBJECT_CLEAR_OBJECTS_INSIDE_GARAGE(Hash garageHash, bool vehicles, bool peds, bool objects, bool isNetwork)
	{
		OBJECT::CLEAR_OBJECTS_INSIDE_GARAGE(garageHash, vehicles, peds, objects, isNetwork);
	}

	static void LUA_NATIVE_OBJECT_DISABLE_TIDYING_UP_IN_GARAGE(int id, bool toggle)
	{
		OBJECT::DISABLE_TIDYING_UP_IN_GARAGE(id, toggle);
	}

	static void LUA_NATIVE_OBJECT_ENABLE_SAVING_IN_GARAGE(Hash garageHash, bool toggle)
	{
		OBJECT::ENABLE_SAVING_IN_GARAGE(garageHash, toggle);
	}

	static void LUA_NATIVE_OBJECT_CLOSE_SAFEHOUSE_GARAGES()
	{
		OBJECT::CLOSE_SAFEHOUSE_GARAGES();
	}

	static bool LUA_NATIVE_OBJECT_DOES_OBJECT_OF_TYPE_EXIST_AT_COORDS(float x, float y, float z, float radius, Hash hash, bool p5)
	{
		auto retval = (bool)OBJECT::DOES_OBJECT_OF_TYPE_EXIST_AT_COORDS(x, y, z, radius, hash, p5);
		return retval;
	}

	static bool LUA_NATIVE_OBJECT_IS_POINT_IN_ANGLED_AREA(float xPos, float yPos, float zPos, float x1, float y1, float z1, float x2, float y2, float z2, float width, bool debug, bool includeZ)
	{
		auto retval = (bool)OBJECT::IS_POINT_IN_ANGLED_AREA(xPos, yPos, zPos, x1, y1, z1, x2, y2, z2, width, debug, includeZ);
		return retval;
	}

	static void LUA_NATIVE_OBJECT_SET_OBJECT_ALLOW_LOW_LOD_BUOYANCY(Object object, bool toggle)
	{
		OBJECT::SET_OBJECT_ALLOW_LOW_LOD_BUOYANCY(object, toggle);
	}

	static void LUA_NATIVE_OBJECT_SET_OBJECT_PHYSICS_PARAMS(Object object, float weight, float p2, float p3, float p4, float p5, float gravity, float p7, float p8, float p9, float p10, float buoyancy)
	{
		OBJECT::SET_OBJECT_PHYSICS_PARAMS(object, weight, p2, p3, p4, p5, gravity, p7, p8, p9, p10, buoyancy);
	}

	static float LUA_NATIVE_OBJECT_GET_OBJECT_FRAGMENT_DAMAGE_HEALTH(Any p0, bool p1)
	{
		auto retval = OBJECT::GET_OBJECT_FRAGMENT_DAMAGE_HEALTH(p0, p1);
		return retval;
	}

	static void LUA_NATIVE_OBJECT_SET_ACTIVATE_OBJECT_PHYSICS_AS_SOON_AS_IT_IS_UNFROZEN(Object object, bool toggle)
	{
		OBJECT::SET_ACTIVATE_OBJECT_PHYSICS_AS_SOON_AS_IT_IS_UNFROZEN(object, toggle);
	}

	static bool LUA_NATIVE_OBJECT_IS_ANY_OBJECT_NEAR_POINT(float x, float y, float z, float range, bool p4)
	{
		auto retval = (bool)OBJECT::IS_ANY_OBJECT_NEAR_POINT(x, y, z, range, p4);
		return retval;
	}

	static bool LUA_NATIVE_OBJECT_IS_OBJECT_NEAR_POINT(Hash objectHash, float x, float y, float z, float range)
	{
		auto retval = (bool)OBJECT::IS_OBJECT_NEAR_POINT(objectHash, x, y, z, range);
		return retval;
	}

	static void LUA_NATIVE_OBJECT_REMOVE_OBJECT_HIGH_DETAIL_MODEL(Object object)
	{
		OBJECT::REMOVE_OBJECT_HIGH_DETAIL_MODEL(object);
	}

	static void LUA_NATIVE_OBJECT_BREAK_OBJECT_FRAGMENT_CHILD(Object p0, Any p1, bool p2)
	{
		OBJECT::BREAK_OBJECT_FRAGMENT_CHILD(p0, p1, p2);
	}

	static void LUA_NATIVE_OBJECT_DAMAGE_OBJECT_FRAGMENT_CHILD(Any p0, Any p1, Any p2)
	{
		OBJECT::DAMAGE_OBJECT_FRAGMENT_CHILD(p0, p1, p2);
	}

	static void LUA_NATIVE_OBJECT_FIX_OBJECT_FRAGMENT(Object object)
	{
		OBJECT::FIX_OBJECT_FRAGMENT(object);
	}

	static void LUA_NATIVE_OBJECT_TRACK_OBJECT_VISIBILITY(Object object)
	{
		OBJECT::TRACK_OBJECT_VISIBILITY(object);
	}

	static bool LUA_NATIVE_OBJECT_IS_OBJECT_VISIBLE(Object object)
	{
		auto retval = (bool)OBJECT::IS_OBJECT_VISIBLE(object);
		return retval;
	}

	static void LUA_NATIVE_OBJECT_SET_OBJECT_IS_SPECIAL_GOLFBALL(Object object, bool toggle)
	{
		OBJECT::SET_OBJECT_IS_SPECIAL_GOLFBALL(object, toggle);
	}

	static void LUA_NATIVE_OBJECT_SET_OBJECT_TAKES_DAMAGE_FROM_COLLIDING_WITH_BUILDINGS(Any p0, bool p1)
	{
		OBJECT::SET_OBJECT_TAKES_DAMAGE_FROM_COLLIDING_WITH_BUILDINGS(p0, p1);
	}

	static void LUA_NATIVE_OBJECT_ALLOW_DAMAGE_EVENTS_FOR_NON_NETWORKED_OBJECTS(bool value)
	{
		OBJECT::ALLOW_DAMAGE_EVENTS_FOR_NON_NETWORKED_OBJECTS(value);
	}

	static void LUA_NATIVE_OBJECT_SET_CUTSCENES_WEAPON_FLASHLIGHT_ON_THIS_FRAME(Object object, bool toggle)
	{
		OBJECT::SET_CUTSCENES_WEAPON_FLASHLIGHT_ON_THIS_FRAME(object, toggle);
	}

	static Object LUA_NATIVE_OBJECT_GET_RAYFIRE_MAP_OBJECT(float x, float y, float z, float radius, sol::stack_object name)
	{
		auto retval = OBJECT::GET_RAYFIRE_MAP_OBJECT(x, y, z, radius, name.is<const char*>() ? name.as<const char*>() : nullptr);
		return retval;
	}

	static void LUA_NATIVE_OBJECT_SET_STATE_OF_RAYFIRE_MAP_OBJECT(Object object, int state)
	{
		OBJECT::SET_STATE_OF_RAYFIRE_MAP_OBJECT(object, state);
	}

	static int LUA_NATIVE_OBJECT_GET_STATE_OF_RAYFIRE_MAP_OBJECT(Object object)
	{
		auto retval = OBJECT::GET_STATE_OF_RAYFIRE_MAP_OBJECT(object);
		return retval;
	}

	static bool LUA_NATIVE_OBJECT_DOES_RAYFIRE_MAP_OBJECT_EXIST(Object object)
	{
		auto retval = (bool)OBJECT::DOES_RAYFIRE_MAP_OBJECT_EXIST(object);
		return retval;
	}

	static float LUA_NATIVE_OBJECT_GET_RAYFIRE_MAP_OBJECT_ANIM_PHASE(Object object)
	{
		auto retval = OBJECT::GET_RAYFIRE_MAP_OBJECT_ANIM_PHASE(object);
		return retval;
	}

	static Pickup LUA_NATIVE_OBJECT_CREATE_PICKUP(Hash pickupHash, float posX, float posY, float posZ, int p4, int value, bool p6, Hash modelHash)
	{
		auto retval = OBJECT::CREATE_PICKUP(pickupHash, posX, posY, posZ, p4, value, p6, modelHash);
		return retval;
	}

	static Pickup LUA_NATIVE_OBJECT_CREATE_PICKUP_ROTATE(Hash pickupHash, float posX, float posY, float posZ, float rotX, float rotY, float rotZ, int flag, int amount, Any p9, bool p10, Hash modelHash)
	{
		auto retval = OBJECT::CREATE_PICKUP_ROTATE(pickupHash, posX, posY, posZ, rotX, rotY, rotZ, flag, amount, p9, p10, modelHash);
		return retval;
	}

	static void LUA_NATIVE_OBJECT_FORCE_PICKUP_ROTATE_FACE_UP()
	{
		OBJECT::FORCE_PICKUP_ROTATE_FACE_UP();
	}

	static void LUA_NATIVE_OBJECT_SET_CUSTOM_PICKUP_WEAPON_HASH(Hash pickupHash, Pickup pickup)
	{
		OBJECT::SET_CUSTOM_PICKUP_WEAPON_HASH(pickupHash, pickup);
	}

	static Object LUA_NATIVE_OBJECT_CREATE_AMBIENT_PICKUP(Hash pickupHash, float posX, float posY, float posZ, int flags, int value, Hash modelHash, bool p7, bool p8)
	{
		auto retval = OBJECT::CREATE_AMBIENT_PICKUP(pickupHash, posX, posY, posZ, flags, value, modelHash, p7, p8);
		return retval;
	}

	static Object LUA_NATIVE_OBJECT_CREATE_NON_NETWORKED_AMBIENT_PICKUP(Hash pickupHash, float posX, float posY, float posZ, int flags, int value, Hash modelHash, bool p7, bool p8)
	{
		auto retval = OBJECT::CREATE_NON_NETWORKED_AMBIENT_PICKUP(pickupHash, posX, posY, posZ, flags, value, modelHash, p7, p8);
		return retval;
	}

	static void LUA_NATIVE_OBJECT_BLOCK_PLAYERS_FOR_AMBIENT_PICKUP(Any p0, Any p1)
	{
		OBJECT::BLOCK_PLAYERS_FOR_AMBIENT_PICKUP(p0, p1);
	}

	static Object LUA_NATIVE_OBJECT_CREATE_PORTABLE_PICKUP(Hash pickupHash, float x, float y, float z, bool placeOnGround, Hash modelHash)
	{
		auto retval = OBJECT::CREATE_PORTABLE_PICKUP(pickupHash, x, y, z, placeOnGround, modelHash);
		return retval;
	}

	static Object LUA_NATIVE_OBJECT_CREATE_NON_NETWORKED_PORTABLE_PICKUP(Hash pickupHash, float x, float y, float z, bool placeOnGround, Hash modelHash)
	{
		auto retval = OBJECT::CREATE_NON_NETWORKED_PORTABLE_PICKUP(pickupHash, x, y, z, placeOnGround, modelHash);
		return retval;
	}

	static void LUA_NATIVE_OBJECT_ATTACH_PORTABLE_PICKUP_TO_PED(Object pickupObject, Ped ped)
	{
		OBJECT::ATTACH_PORTABLE_PICKUP_TO_PED(pickupObject, ped);
	}

	static void LUA_NATIVE_OBJECT_DETACH_PORTABLE_PICKUP_FROM_PED(Object pickupObject)
	{
		OBJECT::DETACH_PORTABLE_PICKUP_FROM_PED(pickupObject);
	}

	static void LUA_NATIVE_OBJECT_FORCE_PORTABLE_PICKUP_LAST_ACCESSIBLE_POSITION_SETTING(Object object)
	{
		OBJECT::FORCE_PORTABLE_PICKUP_LAST_ACCESSIBLE_POSITION_SETTING(object);
	}

	static void LUA_NATIVE_OBJECT_HIDE_PORTABLE_PICKUP_WHEN_DETACHED(Object pickupObject, bool toggle)
	{
		OBJECT::HIDE_PORTABLE_PICKUP_WHEN_DETACHED(pickupObject, toggle);
	}

	static void LUA_NATIVE_OBJECT_SET_MAX_NUM_PORTABLE_PICKUPS_CARRIED_BY_PLAYER(Hash modelHash, int number)
	{
		OBJECT::SET_MAX_NUM_PORTABLE_PICKUPS_CARRIED_BY_PLAYER(modelHash, number);
	}

	static void LUA_NATIVE_OBJECT_SET_LOCAL_PLAYER_CAN_COLLECT_PORTABLE_PICKUPS(bool toggle)
	{
		OBJECT::SET_LOCAL_PLAYER_CAN_COLLECT_PORTABLE_PICKUPS(toggle);
	}

	static Vector3 LUA_NATIVE_OBJECT_GET_SAFE_PICKUP_COORDS(float x, float y, float z, float p3, float p4)
	{
		auto retval = OBJECT::GET_SAFE_PICKUP_COORDS(x, y, z, p3, p4);
		return retval;
	}

	static void LUA_NATIVE_OBJECT_ADD_EXTENDED_PICKUP_PROBE_AREA(float x, float y, float z, float radius)
	{
		OBJECT::ADD_EXTENDED_PICKUP_PROBE_AREA(x, y, z, radius);
	}

	static void LUA_NATIVE_OBJECT_CLEAR_EXTENDED_PICKUP_PROBE_AREAS()
	{
		OBJECT::CLEAR_EXTENDED_PICKUP_PROBE_AREAS();
	}

	static Vector3 LUA_NATIVE_OBJECT_GET_PICKUP_COORDS(Pickup pickup)
	{
		auto retval = OBJECT::GET_PICKUP_COORDS(pickup);
		return retval;
	}

	static void LUA_NATIVE_OBJECT_SUPPRESS_PICKUP_SOUND_FOR_PICKUP(Any p0, Any p1)
	{
		OBJECT::SUPPRESS_PICKUP_SOUND_FOR_PICKUP(p0, p1);
	}

	static void LUA_NATIVE_OBJECT_REMOVE_ALL_PICKUPS_OF_TYPE(Hash pickupHash)
	{
		OBJECT::REMOVE_ALL_PICKUPS_OF_TYPE(pickupHash);
	}

	static bool LUA_NATIVE_OBJECT_HAS_PICKUP_BEEN_COLLECTED(Pickup pickup)
	{
		auto retval = (bool)OBJECT::HAS_PICKUP_BEEN_COLLECTED(pickup);
		return retval;
	}

	static void LUA_NATIVE_OBJECT_REMOVE_PICKUP(Pickup pickup)
	{
		OBJECT::REMOVE_PICKUP(pickup);
	}

	static void LUA_NATIVE_OBJECT_CREATE_MONEY_PICKUPS(float x, float y, float z, int value, int amount, Hash model)
	{
		OBJECT::CREATE_MONEY_PICKUPS(x, y, z, value, amount, model);
	}

	static bool LUA_NATIVE_OBJECT_DOES_PICKUP_EXIST(Pickup pickup)
	{
		auto retval = (bool)OBJECT::DOES_PICKUP_EXIST(pickup);
		return retval;
	}

	static bool LUA_NATIVE_OBJECT_DOES_PICKUP_OBJECT_EXIST(Object pickupObject)
	{
		auto retval = (bool)OBJECT::DOES_PICKUP_OBJECT_EXIST(pickupObject);
		return retval;
	}

	static Object LUA_NATIVE_OBJECT_GET_PICKUP_OBJECT(Pickup pickup)
	{
		auto retval = OBJECT::GET_PICKUP_OBJECT(pickup);
		return retval;
	}

	static bool LUA_NATIVE_OBJECT_IS_OBJECT_A_PICKUP(Object object)
	{
		auto retval = (bool)OBJECT::IS_OBJECT_A_PICKUP(object);
		return retval;
	}

	static bool LUA_NATIVE_OBJECT_IS_OBJECT_A_PORTABLE_PICKUP(Object object)
	{
		auto retval = (bool)OBJECT::IS_OBJECT_A_PORTABLE_PICKUP(object);
		return retval;
	}

	static bool LUA_NATIVE_OBJECT_DOES_PICKUP_OF_TYPE_EXIST_IN_AREA(Hash pickupHash, float x, float y, float z, float radius)
	{
		auto retval = (bool)OBJECT::DOES_PICKUP_OF_TYPE_EXIST_IN_AREA(pickupHash, x, y, z, radius);
		return retval;
	}

	static void LUA_NATIVE_OBJECT_SET_PICKUP_REGENERATION_TIME(Pickup pickup, int duration)
	{
		OBJECT::SET_PICKUP_REGENERATION_TIME(pickup, duration);
	}

	static void LUA_NATIVE_OBJECT_FORCE_PICKUP_REGENERATE(Any p0)
	{
		OBJECT::FORCE_PICKUP_REGENERATE(p0);
	}

	static void LUA_NATIVE_OBJECT_SET_PLAYER_PERMITTED_TO_COLLECT_PICKUPS_OF_TYPE(Player player, Hash pickupHash, bool toggle)
	{
		OBJECT::SET_PLAYER_PERMITTED_TO_COLLECT_PICKUPS_OF_TYPE(player, pickupHash, toggle);
	}

	static void LUA_NATIVE_OBJECT_SET_LOCAL_PLAYER_PERMITTED_TO_COLLECT_PICKUPS_WITH_MODEL(Hash modelHash, bool toggle)
	{
		OBJECT::SET_LOCAL_PLAYER_PERMITTED_TO_COLLECT_PICKUPS_WITH_MODEL(modelHash, toggle);
	}

	static void LUA_NATIVE_OBJECT_ALLOW_ALL_PLAYERS_TO_COLLECT_PICKUPS_OF_TYPE(Hash pickupHash)
	{
		OBJECT::ALLOW_ALL_PLAYERS_TO_COLLECT_PICKUPS_OF_TYPE(pickupHash);
	}

	static void LUA_NATIVE_OBJECT_SET_TEAM_PICKUP_OBJECT(Object object, Any p1, bool p2)
	{
		OBJECT::SET_TEAM_PICKUP_OBJECT(object, p1, p2);
	}

	static void LUA_NATIVE_OBJECT_PREVENT_COLLECTION_OF_PORTABLE_PICKUP(Object object, bool p1, bool p2)
	{
		OBJECT::PREVENT_COLLECTION_OF_PORTABLE_PICKUP(object, p1, p2);
	}

	static void LUA_NATIVE_OBJECT_SET_PICKUP_OBJECT_GLOW_WHEN_UNCOLLECTABLE(Pickup pickup, bool toggle)
	{
		OBJECT::SET_PICKUP_OBJECT_GLOW_WHEN_UNCOLLECTABLE(pickup, toggle);
	}

	static void LUA_NATIVE_OBJECT_SET_PICKUP_GLOW_OFFSET(Pickup pickup, float p1)
	{
		OBJECT::SET_PICKUP_GLOW_OFFSET(pickup, p1);
	}

	static void LUA_NATIVE_OBJECT_SET_PICKUP_OBJECT_GLOW_OFFSET(Pickup pickup, float p1, bool p2)
	{
		OBJECT::SET_PICKUP_OBJECT_GLOW_OFFSET(pickup, p1, p2);
	}

	static void LUA_NATIVE_OBJECT_SET_OBJECT_GLOW_IN_SAME_TEAM(Pickup pickup)
	{
		OBJECT::SET_OBJECT_GLOW_IN_SAME_TEAM(pickup);
	}

	static void LUA_NATIVE_OBJECT_SET_PICKUP_OBJECT_ARROW_MARKER(Pickup pickup, bool toggle)
	{
		OBJECT::SET_PICKUP_OBJECT_ARROW_MARKER(pickup, toggle);
	}

	static void LUA_NATIVE_OBJECT_ALLOW_PICKUP_ARROW_MARKER_WHEN_UNCOLLECTABLE(Pickup pickup, bool toggle)
	{
		OBJECT::ALLOW_PICKUP_ARROW_MARKER_WHEN_UNCOLLECTABLE(pickup, toggle);
	}

	static int LUA_NATIVE_OBJECT_GET_DEFAULT_AMMO_FOR_WEAPON_PICKUP(Hash pickupHash)
	{
		auto retval = OBJECT::GET_DEFAULT_AMMO_FOR_WEAPON_PICKUP(pickupHash);
		return retval;
	}

	static void LUA_NATIVE_OBJECT_SET_PICKUP_GENERATION_RANGE_MULTIPLIER(float multiplier)
	{
		OBJECT::SET_PICKUP_GENERATION_RANGE_MULTIPLIER(multiplier);
	}

	static float LUA_NATIVE_OBJECT_GET_PICKUP_GENERATION_RANGE_MULTIPLIER()
	{
		auto retval = OBJECT::GET_PICKUP_GENERATION_RANGE_MULTIPLIER();
		return retval;
	}

	static void LUA_NATIVE_OBJECT_SET_ONLY_ALLOW_AMMO_COLLECTION_WHEN_LOW(bool p0)
	{
		OBJECT::SET_ONLY_ALLOW_AMMO_COLLECTION_WHEN_LOW(p0);
	}

	static void LUA_NATIVE_OBJECT_SET_PICKUP_UNCOLLECTABLE(Pickup pickup, bool toggle)
	{
		OBJECT::SET_PICKUP_UNCOLLECTABLE(pickup, toggle);
	}

	static void LUA_NATIVE_OBJECT_SET_PICKUP_TRANSPARENT_WHEN_UNCOLLECTABLE(Pickup pickup, bool toggle)
	{
		OBJECT::SET_PICKUP_TRANSPARENT_WHEN_UNCOLLECTABLE(pickup, toggle);
	}

	static void LUA_NATIVE_OBJECT_SET_PICKUP_HIDDEN_WHEN_UNCOLLECTABLE(Pickup pickup, bool toggle)
	{
		OBJECT::SET_PICKUP_HIDDEN_WHEN_UNCOLLECTABLE(pickup, toggle);
	}

	static void LUA_NATIVE_OBJECT_SET_PICKUP_OBJECT_TRANSPARENT_WHEN_UNCOLLECTABLE(Pickup pickup, bool toggle)
	{
		OBJECT::SET_PICKUP_OBJECT_TRANSPARENT_WHEN_UNCOLLECTABLE(pickup, toggle);
	}

	static void LUA_NATIVE_OBJECT_SET_PICKUP_OBJECT_ALPHA_WHEN_TRANSPARENT(int p0)
	{
		OBJECT::SET_PICKUP_OBJECT_ALPHA_WHEN_TRANSPARENT(p0);
	}

	static void LUA_NATIVE_OBJECT_SET_PORTABLE_PICKUP_PERSIST(Pickup pickup, bool toggle)
	{
		OBJECT::SET_PORTABLE_PICKUP_PERSIST(pickup, toggle);
	}

	static void LUA_NATIVE_OBJECT_ALLOW_PORTABLE_PICKUP_TO_MIGRATE_TO_NON_PARTICIPANTS(Pickup pickup, bool toggle)
	{
		OBJECT::ALLOW_PORTABLE_PICKUP_TO_MIGRATE_TO_NON_PARTICIPANTS(pickup, toggle);
	}

	static void LUA_NATIVE_OBJECT_FORCE_ACTIVATE_PHYSICS_ON_UNFIXED_PICKUP(Pickup pickup, bool toggle)
	{
		OBJECT::FORCE_ACTIVATE_PHYSICS_ON_UNFIXED_PICKUP(pickup, toggle);
	}

	static void LUA_NATIVE_OBJECT_ALLOW_PICKUP_BY_NONE_PARTICIPANT(Pickup pickup, bool toggle)
	{
		OBJECT::ALLOW_PICKUP_BY_NONE_PARTICIPANT(pickup, toggle);
	}

	static void LUA_NATIVE_OBJECT_SUPPRESS_PICKUP_REWARD_TYPE(int rewardType, bool suppress)
	{
		OBJECT::SUPPRESS_PICKUP_REWARD_TYPE(rewardType, suppress);
	}

	static void LUA_NATIVE_OBJECT_CLEAR_ALL_PICKUP_REWARD_TYPE_SUPPRESSION()
	{
		OBJECT::CLEAR_ALL_PICKUP_REWARD_TYPE_SUPPRESSION();
	}

	static void LUA_NATIVE_OBJECT_CLEAR_PICKUP_REWARD_TYPE_SUPPRESSION(int rewardType)
	{
		OBJECT::CLEAR_PICKUP_REWARD_TYPE_SUPPRESSION(rewardType);
	}

	static void LUA_NATIVE_OBJECT_RENDER_FAKE_PICKUP_GLOW(float x, float y, float z, int colorIndex)
	{
		OBJECT::RENDER_FAKE_PICKUP_GLOW(x, y, z, colorIndex);
	}

	static void LUA_NATIVE_OBJECT_SET_PICKUP_OBJECT_COLLECTABLE_IN_VEHICLE(Pickup pickup)
	{
		OBJECT::SET_PICKUP_OBJECT_COLLECTABLE_IN_VEHICLE(pickup);
	}

	static void LUA_NATIVE_OBJECT_SET_PICKUP_TRACK_DAMAGE_EVENTS(Pickup pickup, bool toggle)
	{
		OBJECT::SET_PICKUP_TRACK_DAMAGE_EVENTS(pickup, toggle);
	}

	static void LUA_NATIVE_OBJECT_SET_ENTITY_FLAG_SUPPRESS_SHADOW(Entity entity, bool toggle)
	{
		OBJECT::SET_ENTITY_FLAG_SUPPRESS_SHADOW(entity, toggle);
	}

	static void LUA_NATIVE_OBJECT_SET_ENTITY_FLAG_RENDER_SMALL_SHADOW(Object object, bool toggle)
	{
		OBJECT::SET_ENTITY_FLAG_RENDER_SMALL_SHADOW(object, toggle);
	}

	static Hash LUA_NATIVE_OBJECT_GET_WEAPON_TYPE_FROM_PICKUP_TYPE(Hash pickupHash)
	{
		auto retval = OBJECT::GET_WEAPON_TYPE_FROM_PICKUP_TYPE(pickupHash);
		return retval;
	}

	static Hash LUA_NATIVE_OBJECT_GET_PICKUP_TYPE_FROM_WEAPON_HASH(Hash weaponHash)
	{
		auto retval = OBJECT::GET_PICKUP_TYPE_FROM_WEAPON_HASH(weaponHash);
		return retval;
	}

	static bool LUA_NATIVE_OBJECT_IS_PICKUP_WEAPON_OBJECT_VALID(Object object)
	{
		auto retval = (bool)OBJECT::IS_PICKUP_WEAPON_OBJECT_VALID(object);
		return retval;
	}

	static int LUA_NATIVE_OBJECT_GET_OBJECT_TINT_INDEX(Object object)
	{
		auto retval = OBJECT::GET_OBJECT_TINT_INDEX(object);
		return retval;
	}

	static void LUA_NATIVE_OBJECT_SET_OBJECT_TINT_INDEX(Object object, int textureVariation)
	{
		OBJECT::SET_OBJECT_TINT_INDEX(object, textureVariation);
	}

	static bool LUA_NATIVE_OBJECT_SET_TINT_INDEX_CLOSEST_BUILDING_OF_TYPE(float x, float y, float z, float radius, Hash modelHash, int textureVariation)
	{
		auto retval = (bool)OBJECT::SET_TINT_INDEX_CLOSEST_BUILDING_OF_TYPE(x, y, z, radius, modelHash, textureVariation);
		return retval;
	}

	static void LUA_NATIVE_OBJECT_SET_PROP_TINT_INDEX(Any p0, Any p1)
	{
		OBJECT::SET_PROP_TINT_INDEX(p0, p1);
	}

	static bool LUA_NATIVE_OBJECT_SET_PROP_LIGHT_COLOR(Object object, bool p1, int r, int g, int b)
	{
		auto retval = (bool)OBJECT::SET_PROP_LIGHT_COLOR(object, p1, r, g, b);
		return retval;
	}

	static bool LUA_NATIVE_OBJECT_IS_PROP_LIGHT_OVERRIDEN(Object object)
	{
		auto retval = (bool)OBJECT::IS_PROP_LIGHT_OVERRIDEN(object);
		return retval;
	}

	static void LUA_NATIVE_OBJECT_SET_OBJECT_IS_VISIBLE_IN_MIRRORS(Object object, bool toggle)
	{
		OBJECT::SET_OBJECT_IS_VISIBLE_IN_MIRRORS(object, toggle);
	}

	static void LUA_NATIVE_OBJECT_SET_OBJECT_SPEED_BOOST_AMOUNT(Object object, Any p1)
	{
		OBJECT::SET_OBJECT_SPEED_BOOST_AMOUNT(object, p1);
	}

	static void LUA_NATIVE_OBJECT_SET_OBJECT_SPEED_BOOST_DURATION(Object object, float duration)
	{
		OBJECT::SET_OBJECT_SPEED_BOOST_DURATION(object, duration);
	}

	static Hash LUA_NATIVE_OBJECT_CONVERT_OLD_PICKUP_TYPE_TO_NEW(Hash pickupHash)
	{
		auto retval = OBJECT::CONVERT_OLD_PICKUP_TYPE_TO_NEW(pickupHash);
		return retval;
	}

	static void LUA_NATIVE_OBJECT_SET_FORCE_OBJECT_THIS_FRAME(float x, float y, float z, float p3)
	{
		OBJECT::SET_FORCE_OBJECT_THIS_FRAME(x, y, z, p3);
	}

	static void LUA_NATIVE_OBJECT_ONLY_CLEAN_UP_OBJECT_WHEN_OUT_OF_RANGE(Object object)
	{
		OBJECT::ONLY_CLEAN_UP_OBJECT_WHEN_OUT_OF_RANGE(object);
	}

	static void LUA_NATIVE_OBJECT_SET_DISABLE_COLLISIONS_BETWEEN_CARS_AND_CAR_PARACHUTE(Any p0)
	{
		OBJECT::SET_DISABLE_COLLISIONS_BETWEEN_CARS_AND_CAR_PARACHUTE(p0);
	}

	static void LUA_NATIVE_OBJECT_SET_PROJECTILES_SHOULD_EXPLODE_ON_CONTACT(Entity entity, Any p1)
	{
		OBJECT::SET_PROJECTILES_SHOULD_EXPLODE_ON_CONTACT(entity, p1);
	}

	static void LUA_NATIVE_OBJECT_SET_DRIVE_ARTICULATED_JOINT(Object object, bool toggle, int p2)
	{
		OBJECT::SET_DRIVE_ARTICULATED_JOINT(object, toggle, p2);
	}

	static void LUA_NATIVE_OBJECT_SET_DRIVE_ARTICULATED_JOINT_WITH_INFLICTOR(Object object, bool toggle, int p2, Ped ped)
	{
		OBJECT::SET_DRIVE_ARTICULATED_JOINT_WITH_INFLICTOR(object, toggle, p2, ped);
	}

	static void LUA_NATIVE_OBJECT_SET_OBJECT_IS_A_PRESSURE_PLATE(Object object, bool toggle)
	{
		OBJECT::SET_OBJECT_IS_A_PRESSURE_PLATE(object, toggle);
	}

	static void LUA_NATIVE_OBJECT_SET_WEAPON_IMPACTS_APPLY_GREATER_FORCE(Object object, bool p1)
	{
		OBJECT::SET_WEAPON_IMPACTS_APPLY_GREATER_FORCE(object, p1);
	}

	static bool LUA_NATIVE_OBJECT_GET_IS_ARTICULATED_JOINT_AT_MIN_ANGLE(Object object, Any p1)
	{
		auto retval = (bool)OBJECT::GET_IS_ARTICULATED_JOINT_AT_MIN_ANGLE(object, p1);
		return retval;
	}

	static bool LUA_NATIVE_OBJECT_GET_IS_ARTICULATED_JOINT_AT_MAX_ANGLE(Any p0, Any p1)
	{
		auto retval = (bool)OBJECT::GET_IS_ARTICULATED_JOINT_AT_MAX_ANGLE(p0, p1);
		return retval;
	}

	static void LUA_NATIVE_OBJECT_SET_IS_OBJECT_ARTICULATED(Object object, bool toggle)
	{
		OBJECT::SET_IS_OBJECT_ARTICULATED(object, toggle);
	}

	static void LUA_NATIVE_OBJECT_SET_IS_OBJECT_BALL(Object object, bool toggle)
	{
		OBJECT::SET_IS_OBJECT_BALL(object, toggle);
	}

	void init_native_binding_OBJECT(sol::state& L)
	{
		auto OBJECT = L["OBJECT"].get_or_create<sol::table>();
		OBJECT.set_function("CREATE_OBJECT", LUA_NATIVE_OBJECT_CREATE_OBJECT);
		OBJECT.set_function("CREATE_OBJECT_NO_OFFSET", LUA_NATIVE_OBJECT_CREATE_OBJECT_NO_OFFSET);
		OBJECT.set_function("DELETE_OBJECT", LUA_NATIVE_OBJECT_DELETE_OBJECT);
		OBJECT.set_function("PLACE_OBJECT_ON_GROUND_PROPERLY", LUA_NATIVE_OBJECT_PLACE_OBJECT_ON_GROUND_PROPERLY);
		OBJECT.set_function("PLACE_OBJECT_ON_GROUND_OR_OBJECT_PROPERLY", LUA_NATIVE_OBJECT_PLACE_OBJECT_ON_GROUND_OR_OBJECT_PROPERLY);
		OBJECT.set_function("ROTATE_OBJECT", LUA_NATIVE_OBJECT_ROTATE_OBJECT);
		OBJECT.set_function("SLIDE_OBJECT", LUA_NATIVE_OBJECT_SLIDE_OBJECT);
		OBJECT.set_function("SET_OBJECT_TARGETTABLE", LUA_NATIVE_OBJECT_SET_OBJECT_TARGETTABLE);
		OBJECT.set_function("SET_OBJECT_FORCE_VEHICLES_TO_AVOID", LUA_NATIVE_OBJECT_SET_OBJECT_FORCE_VEHICLES_TO_AVOID);
		OBJECT.set_function("GET_CLOSEST_OBJECT_OF_TYPE", LUA_NATIVE_OBJECT_GET_CLOSEST_OBJECT_OF_TYPE);
		OBJECT.set_function("HAS_OBJECT_BEEN_BROKEN", LUA_NATIVE_OBJECT_HAS_OBJECT_BEEN_BROKEN);
		OBJECT.set_function("HAS_CLOSEST_OBJECT_OF_TYPE_BEEN_BROKEN", LUA_NATIVE_OBJECT_HAS_CLOSEST_OBJECT_OF_TYPE_BEEN_BROKEN);
		OBJECT.set_function("HAS_CLOSEST_OBJECT_OF_TYPE_BEEN_COMPLETELY_DESTROYED", LUA_NATIVE_OBJECT_HAS_CLOSEST_OBJECT_OF_TYPE_BEEN_COMPLETELY_DESTROYED);
		OBJECT.set_function("GET_HAS_OBJECT_BEEN_COMPLETELY_DESTROYED", LUA_NATIVE_OBJECT_GET_HAS_OBJECT_BEEN_COMPLETELY_DESTROYED);
		OBJECT.set_function("GET_OFFSET_FROM_COORD_AND_HEADING_IN_WORLD_COORDS", LUA_NATIVE_OBJECT_GET_OFFSET_FROM_COORD_AND_HEADING_IN_WORLD_COORDS);
		OBJECT.set_function("GET_COORDS_AND_ROTATION_OF_CLOSEST_OBJECT_OF_TYPE", LUA_NATIVE_OBJECT_GET_COORDS_AND_ROTATION_OF_CLOSEST_OBJECT_OF_TYPE);
		OBJECT.set_function("SET_STATE_OF_CLOSEST_DOOR_OF_TYPE", LUA_NATIVE_OBJECT_SET_STATE_OF_CLOSEST_DOOR_OF_TYPE);
		OBJECT.set_function("GET_STATE_OF_CLOSEST_DOOR_OF_TYPE", LUA_NATIVE_OBJECT_GET_STATE_OF_CLOSEST_DOOR_OF_TYPE);
		OBJECT.set_function("SET_LOCKED_UNSTREAMED_IN_DOOR_OF_TYPE", LUA_NATIVE_OBJECT_SET_LOCKED_UNSTREAMED_IN_DOOR_OF_TYPE);
		OBJECT.set_function("PLAY_OBJECT_AUTO_START_ANIM", LUA_NATIVE_OBJECT_PLAY_OBJECT_AUTO_START_ANIM);
		OBJECT.set_function("ADD_DOOR_TO_SYSTEM", LUA_NATIVE_OBJECT_ADD_DOOR_TO_SYSTEM);
		OBJECT.set_function("REMOVE_DOOR_FROM_SYSTEM", LUA_NATIVE_OBJECT_REMOVE_DOOR_FROM_SYSTEM);
		OBJECT.set_function("DOOR_SYSTEM_SET_DOOR_STATE", LUA_NATIVE_OBJECT_DOOR_SYSTEM_SET_DOOR_STATE);
		OBJECT.set_function("DOOR_SYSTEM_GET_DOOR_STATE", LUA_NATIVE_OBJECT_DOOR_SYSTEM_GET_DOOR_STATE);
		OBJECT.set_function("DOOR_SYSTEM_GET_DOOR_PENDING_STATE", LUA_NATIVE_OBJECT_DOOR_SYSTEM_GET_DOOR_PENDING_STATE);
		OBJECT.set_function("DOOR_SYSTEM_SET_AUTOMATIC_RATE", LUA_NATIVE_OBJECT_DOOR_SYSTEM_SET_AUTOMATIC_RATE);
		OBJECT.set_function("DOOR_SYSTEM_SET_AUTOMATIC_DISTANCE", LUA_NATIVE_OBJECT_DOOR_SYSTEM_SET_AUTOMATIC_DISTANCE);
		OBJECT.set_function("DOOR_SYSTEM_SET_OPEN_RATIO", LUA_NATIVE_OBJECT_DOOR_SYSTEM_SET_OPEN_RATIO);
		OBJECT.set_function("DOOR_SYSTEM_GET_AUTOMATIC_DISTANCE", LUA_NATIVE_OBJECT_DOOR_SYSTEM_GET_AUTOMATIC_DISTANCE);
		OBJECT.set_function("DOOR_SYSTEM_GET_OPEN_RATIO", LUA_NATIVE_OBJECT_DOOR_SYSTEM_GET_OPEN_RATIO);
		OBJECT.set_function("DOOR_SYSTEM_SET_SPRING_REMOVED", LUA_NATIVE_OBJECT_DOOR_SYSTEM_SET_SPRING_REMOVED);
		OBJECT.set_function("DOOR_SYSTEM_SET_HOLD_OPEN", LUA_NATIVE_OBJECT_DOOR_SYSTEM_SET_HOLD_OPEN);
		OBJECT.set_function("DOOR_SYSTEM_SET_DOOR_OPEN_FOR_RACES", LUA_NATIVE_OBJECT_DOOR_SYSTEM_SET_DOOR_OPEN_FOR_RACES);
		OBJECT.set_function("IS_DOOR_REGISTERED_WITH_SYSTEM", LUA_NATIVE_OBJECT_IS_DOOR_REGISTERED_WITH_SYSTEM);
		OBJECT.set_function("IS_DOOR_CLOSED", LUA_NATIVE_OBJECT_IS_DOOR_CLOSED);
		OBJECT.set_function("OPEN_ALL_BARRIERS_FOR_RACE", LUA_NATIVE_OBJECT_OPEN_ALL_BARRIERS_FOR_RACE);
		OBJECT.set_function("CLOSE_ALL_BARRIERS_FOR_RACE", LUA_NATIVE_OBJECT_CLOSE_ALL_BARRIERS_FOR_RACE);
		OBJECT.set_function("DOOR_SYSTEM_GET_IS_PHYSICS_LOADED", LUA_NATIVE_OBJECT_DOOR_SYSTEM_GET_IS_PHYSICS_LOADED);
		OBJECT.set_function("DOOR_SYSTEM_FIND_EXISTING_DOOR", LUA_NATIVE_OBJECT_DOOR_SYSTEM_FIND_EXISTING_DOOR);
		OBJECT.set_function("IS_GARAGE_EMPTY", LUA_NATIVE_OBJECT_IS_GARAGE_EMPTY);
		OBJECT.set_function("IS_PLAYER_ENTIRELY_INSIDE_GARAGE", LUA_NATIVE_OBJECT_IS_PLAYER_ENTIRELY_INSIDE_GARAGE);
		OBJECT.set_function("IS_PLAYER_PARTIALLY_INSIDE_GARAGE", LUA_NATIVE_OBJECT_IS_PLAYER_PARTIALLY_INSIDE_GARAGE);
		OBJECT.set_function("ARE_ENTITIES_ENTIRELY_INSIDE_GARAGE", LUA_NATIVE_OBJECT_ARE_ENTITIES_ENTIRELY_INSIDE_GARAGE);
		OBJECT.set_function("IS_ANY_ENTITY_ENTIRELY_INSIDE_GARAGE", LUA_NATIVE_OBJECT_IS_ANY_ENTITY_ENTIRELY_INSIDE_GARAGE);
		OBJECT.set_function("IS_OBJECT_ENTIRELY_INSIDE_GARAGE", LUA_NATIVE_OBJECT_IS_OBJECT_ENTIRELY_INSIDE_GARAGE);
		OBJECT.set_function("IS_OBJECT_PARTIALLY_INSIDE_GARAGE", LUA_NATIVE_OBJECT_IS_OBJECT_PARTIALLY_INSIDE_GARAGE);
		OBJECT.set_function("CLEAR_GARAGE", LUA_NATIVE_OBJECT_CLEAR_GARAGE);
		OBJECT.set_function("CLEAR_OBJECTS_INSIDE_GARAGE", LUA_NATIVE_OBJECT_CLEAR_OBJECTS_INSIDE_GARAGE);
		OBJECT.set_function("DISABLE_TIDYING_UP_IN_GARAGE", LUA_NATIVE_OBJECT_DISABLE_TIDYING_UP_IN_GARAGE);
		OBJECT.set_function("ENABLE_SAVING_IN_GARAGE", LUA_NATIVE_OBJECT_ENABLE_SAVING_IN_GARAGE);
		OBJECT.set_function("CLOSE_SAFEHOUSE_GARAGES", LUA_NATIVE_OBJECT_CLOSE_SAFEHOUSE_GARAGES);
		OBJECT.set_function("DOES_OBJECT_OF_TYPE_EXIST_AT_COORDS", LUA_NATIVE_OBJECT_DOES_OBJECT_OF_TYPE_EXIST_AT_COORDS);
		OBJECT.set_function("IS_POINT_IN_ANGLED_AREA", LUA_NATIVE_OBJECT_IS_POINT_IN_ANGLED_AREA);
		OBJECT.set_function("SET_OBJECT_ALLOW_LOW_LOD_BUOYANCY", LUA_NATIVE_OBJECT_SET_OBJECT_ALLOW_LOW_LOD_BUOYANCY);
		OBJECT.set_function("SET_OBJECT_PHYSICS_PARAMS", LUA_NATIVE_OBJECT_SET_OBJECT_PHYSICS_PARAMS);
		OBJECT.set_function("GET_OBJECT_FRAGMENT_DAMAGE_HEALTH", LUA_NATIVE_OBJECT_GET_OBJECT_FRAGMENT_DAMAGE_HEALTH);
		OBJECT.set_function("SET_ACTIVATE_OBJECT_PHYSICS_AS_SOON_AS_IT_IS_UNFROZEN", LUA_NATIVE_OBJECT_SET_ACTIVATE_OBJECT_PHYSICS_AS_SOON_AS_IT_IS_UNFROZEN);
		OBJECT.set_function("IS_ANY_OBJECT_NEAR_POINT", LUA_NATIVE_OBJECT_IS_ANY_OBJECT_NEAR_POINT);
		OBJECT.set_function("IS_OBJECT_NEAR_POINT", LUA_NATIVE_OBJECT_IS_OBJECT_NEAR_POINT);
		OBJECT.set_function("REMOVE_OBJECT_HIGH_DETAIL_MODEL", LUA_NATIVE_OBJECT_REMOVE_OBJECT_HIGH_DETAIL_MODEL);
		OBJECT.set_function("BREAK_OBJECT_FRAGMENT_CHILD", LUA_NATIVE_OBJECT_BREAK_OBJECT_FRAGMENT_CHILD);
		OBJECT.set_function("DAMAGE_OBJECT_FRAGMENT_CHILD", LUA_NATIVE_OBJECT_DAMAGE_OBJECT_FRAGMENT_CHILD);
		OBJECT.set_function("FIX_OBJECT_FRAGMENT", LUA_NATIVE_OBJECT_FIX_OBJECT_FRAGMENT);
		OBJECT.set_function("TRACK_OBJECT_VISIBILITY", LUA_NATIVE_OBJECT_TRACK_OBJECT_VISIBILITY);
		OBJECT.set_function("IS_OBJECT_VISIBLE", LUA_NATIVE_OBJECT_IS_OBJECT_VISIBLE);
		OBJECT.set_function("SET_OBJECT_IS_SPECIAL_GOLFBALL", LUA_NATIVE_OBJECT_SET_OBJECT_IS_SPECIAL_GOLFBALL);
		OBJECT.set_function("SET_OBJECT_TAKES_DAMAGE_FROM_COLLIDING_WITH_BUILDINGS", LUA_NATIVE_OBJECT_SET_OBJECT_TAKES_DAMAGE_FROM_COLLIDING_WITH_BUILDINGS);
		OBJECT.set_function("ALLOW_DAMAGE_EVENTS_FOR_NON_NETWORKED_OBJECTS", LUA_NATIVE_OBJECT_ALLOW_DAMAGE_EVENTS_FOR_NON_NETWORKED_OBJECTS);
		OBJECT.set_function("SET_CUTSCENES_WEAPON_FLASHLIGHT_ON_THIS_FRAME", LUA_NATIVE_OBJECT_SET_CUTSCENES_WEAPON_FLASHLIGHT_ON_THIS_FRAME);
		OBJECT.set_function("GET_RAYFIRE_MAP_OBJECT", LUA_NATIVE_OBJECT_GET_RAYFIRE_MAP_OBJECT);
		OBJECT.set_function("SET_STATE_OF_RAYFIRE_MAP_OBJECT", LUA_NATIVE_OBJECT_SET_STATE_OF_RAYFIRE_MAP_OBJECT);
		OBJECT.set_function("GET_STATE_OF_RAYFIRE_MAP_OBJECT", LUA_NATIVE_OBJECT_GET_STATE_OF_RAYFIRE_MAP_OBJECT);
		OBJECT.set_function("DOES_RAYFIRE_MAP_OBJECT_EXIST", LUA_NATIVE_OBJECT_DOES_RAYFIRE_MAP_OBJECT_EXIST);
		OBJECT.set_function("GET_RAYFIRE_MAP_OBJECT_ANIM_PHASE", LUA_NATIVE_OBJECT_GET_RAYFIRE_MAP_OBJECT_ANIM_PHASE);
		OBJECT.set_function("CREATE_PICKUP", LUA_NATIVE_OBJECT_CREATE_PICKUP);
		OBJECT.set_function("CREATE_PICKUP_ROTATE", LUA_NATIVE_OBJECT_CREATE_PICKUP_ROTATE);
		OBJECT.set_function("FORCE_PICKUP_ROTATE_FACE_UP", LUA_NATIVE_OBJECT_FORCE_PICKUP_ROTATE_FACE_UP);
		OBJECT.set_function("SET_CUSTOM_PICKUP_WEAPON_HASH", LUA_NATIVE_OBJECT_SET_CUSTOM_PICKUP_WEAPON_HASH);
		OBJECT.set_function("CREATE_AMBIENT_PICKUP", LUA_NATIVE_OBJECT_CREATE_AMBIENT_PICKUP);
		OBJECT.set_function("CREATE_NON_NETWORKED_AMBIENT_PICKUP", LUA_NATIVE_OBJECT_CREATE_NON_NETWORKED_AMBIENT_PICKUP);
		OBJECT.set_function("BLOCK_PLAYERS_FOR_AMBIENT_PICKUP", LUA_NATIVE_OBJECT_BLOCK_PLAYERS_FOR_AMBIENT_PICKUP);
		OBJECT.set_function("CREATE_PORTABLE_PICKUP", LUA_NATIVE_OBJECT_CREATE_PORTABLE_PICKUP);
		OBJECT.set_function("CREATE_NON_NETWORKED_PORTABLE_PICKUP", LUA_NATIVE_OBJECT_CREATE_NON_NETWORKED_PORTABLE_PICKUP);
		OBJECT.set_function("ATTACH_PORTABLE_PICKUP_TO_PED", LUA_NATIVE_OBJECT_ATTACH_PORTABLE_PICKUP_TO_PED);
		OBJECT.set_function("DETACH_PORTABLE_PICKUP_FROM_PED", LUA_NATIVE_OBJECT_DETACH_PORTABLE_PICKUP_FROM_PED);
		OBJECT.set_function("FORCE_PORTABLE_PICKUP_LAST_ACCESSIBLE_POSITION_SETTING", LUA_NATIVE_OBJECT_FORCE_PORTABLE_PICKUP_LAST_ACCESSIBLE_POSITION_SETTING);
		OBJECT.set_function("HIDE_PORTABLE_PICKUP_WHEN_DETACHED", LUA_NATIVE_OBJECT_HIDE_PORTABLE_PICKUP_WHEN_DETACHED);
		OBJECT.set_function("SET_MAX_NUM_PORTABLE_PICKUPS_CARRIED_BY_PLAYER", LUA_NATIVE_OBJECT_SET_MAX_NUM_PORTABLE_PICKUPS_CARRIED_BY_PLAYER);
		OBJECT.set_function("SET_LOCAL_PLAYER_CAN_COLLECT_PORTABLE_PICKUPS", LUA_NATIVE_OBJECT_SET_LOCAL_PLAYER_CAN_COLLECT_PORTABLE_PICKUPS);
		OBJECT.set_function("GET_SAFE_PICKUP_COORDS", LUA_NATIVE_OBJECT_GET_SAFE_PICKUP_COORDS);
		OBJECT.set_function("ADD_EXTENDED_PICKUP_PROBE_AREA", LUA_NATIVE_OBJECT_ADD_EXTENDED_PICKUP_PROBE_AREA);
		OBJECT.set_function("CLEAR_EXTENDED_PICKUP_PROBE_AREAS", LUA_NATIVE_OBJECT_CLEAR_EXTENDED_PICKUP_PROBE_AREAS);
		OBJECT.set_function("GET_PICKUP_COORDS", LUA_NATIVE_OBJECT_GET_PICKUP_COORDS);
		OBJECT.set_function("SUPPRESS_PICKUP_SOUND_FOR_PICKUP", LUA_NATIVE_OBJECT_SUPPRESS_PICKUP_SOUND_FOR_PICKUP);
		OBJECT.set_function("REMOVE_ALL_PICKUPS_OF_TYPE", LUA_NATIVE_OBJECT_REMOVE_ALL_PICKUPS_OF_TYPE);
		OBJECT.set_function("HAS_PICKUP_BEEN_COLLECTED", LUA_NATIVE_OBJECT_HAS_PICKUP_BEEN_COLLECTED);
		OBJECT.set_function("REMOVE_PICKUP", LUA_NATIVE_OBJECT_REMOVE_PICKUP);
		OBJECT.set_function("CREATE_MONEY_PICKUPS", LUA_NATIVE_OBJECT_CREATE_MONEY_PICKUPS);
		OBJECT.set_function("DOES_PICKUP_EXIST", LUA_NATIVE_OBJECT_DOES_PICKUP_EXIST);
		OBJECT.set_function("DOES_PICKUP_OBJECT_EXIST", LUA_NATIVE_OBJECT_DOES_PICKUP_OBJECT_EXIST);
		OBJECT.set_function("GET_PICKUP_OBJECT", LUA_NATIVE_OBJECT_GET_PICKUP_OBJECT);
		OBJECT.set_function("IS_OBJECT_A_PICKUP", LUA_NATIVE_OBJECT_IS_OBJECT_A_PICKUP);
		OBJECT.set_function("IS_OBJECT_A_PORTABLE_PICKUP", LUA_NATIVE_OBJECT_IS_OBJECT_A_PORTABLE_PICKUP);
		OBJECT.set_function("DOES_PICKUP_OF_TYPE_EXIST_IN_AREA", LUA_NATIVE_OBJECT_DOES_PICKUP_OF_TYPE_EXIST_IN_AREA);
		OBJECT.set_function("SET_PICKUP_REGENERATION_TIME", LUA_NATIVE_OBJECT_SET_PICKUP_REGENERATION_TIME);
		OBJECT.set_function("FORCE_PICKUP_REGENERATE", LUA_NATIVE_OBJECT_FORCE_PICKUP_REGENERATE);
		OBJECT.set_function("SET_PLAYER_PERMITTED_TO_COLLECT_PICKUPS_OF_TYPE", LUA_NATIVE_OBJECT_SET_PLAYER_PERMITTED_TO_COLLECT_PICKUPS_OF_TYPE);
		OBJECT.set_function("SET_LOCAL_PLAYER_PERMITTED_TO_COLLECT_PICKUPS_WITH_MODEL", LUA_NATIVE_OBJECT_SET_LOCAL_PLAYER_PERMITTED_TO_COLLECT_PICKUPS_WITH_MODEL);
		OBJECT.set_function("ALLOW_ALL_PLAYERS_TO_COLLECT_PICKUPS_OF_TYPE", LUA_NATIVE_OBJECT_ALLOW_ALL_PLAYERS_TO_COLLECT_PICKUPS_OF_TYPE);
		OBJECT.set_function("SET_TEAM_PICKUP_OBJECT", LUA_NATIVE_OBJECT_SET_TEAM_PICKUP_OBJECT);
		OBJECT.set_function("PREVENT_COLLECTION_OF_PORTABLE_PICKUP", LUA_NATIVE_OBJECT_PREVENT_COLLECTION_OF_PORTABLE_PICKUP);
		OBJECT.set_function("SET_PICKUP_OBJECT_GLOW_WHEN_UNCOLLECTABLE", LUA_NATIVE_OBJECT_SET_PICKUP_OBJECT_GLOW_WHEN_UNCOLLECTABLE);
		OBJECT.set_function("SET_PICKUP_GLOW_OFFSET", LUA_NATIVE_OBJECT_SET_PICKUP_GLOW_OFFSET);
		OBJECT.set_function("SET_PICKUP_OBJECT_GLOW_OFFSET", LUA_NATIVE_OBJECT_SET_PICKUP_OBJECT_GLOW_OFFSET);
		OBJECT.set_function("SET_OBJECT_GLOW_IN_SAME_TEAM", LUA_NATIVE_OBJECT_SET_OBJECT_GLOW_IN_SAME_TEAM);
		OBJECT.set_function("SET_PICKUP_OBJECT_ARROW_MARKER", LUA_NATIVE_OBJECT_SET_PICKUP_OBJECT_ARROW_MARKER);
		OBJECT.set_function("ALLOW_PICKUP_ARROW_MARKER_WHEN_UNCOLLECTABLE", LUA_NATIVE_OBJECT_ALLOW_PICKUP_ARROW_MARKER_WHEN_UNCOLLECTABLE);
		OBJECT.set_function("GET_DEFAULT_AMMO_FOR_WEAPON_PICKUP", LUA_NATIVE_OBJECT_GET_DEFAULT_AMMO_FOR_WEAPON_PICKUP);
		OBJECT.set_function("SET_PICKUP_GENERATION_RANGE_MULTIPLIER", LUA_NATIVE_OBJECT_SET_PICKUP_GENERATION_RANGE_MULTIPLIER);
		OBJECT.set_function("GET_PICKUP_GENERATION_RANGE_MULTIPLIER", LUA_NATIVE_OBJECT_GET_PICKUP_GENERATION_RANGE_MULTIPLIER);
		OBJECT.set_function("SET_ONLY_ALLOW_AMMO_COLLECTION_WHEN_LOW", LUA_NATIVE_OBJECT_SET_ONLY_ALLOW_AMMO_COLLECTION_WHEN_LOW);
		OBJECT.set_function("SET_PICKUP_UNCOLLECTABLE", LUA_NATIVE_OBJECT_SET_PICKUP_UNCOLLECTABLE);
		OBJECT.set_function("SET_PICKUP_TRANSPARENT_WHEN_UNCOLLECTABLE", LUA_NATIVE_OBJECT_SET_PICKUP_TRANSPARENT_WHEN_UNCOLLECTABLE);
		OBJECT.set_function("SET_PICKUP_HIDDEN_WHEN_UNCOLLECTABLE", LUA_NATIVE_OBJECT_SET_PICKUP_HIDDEN_WHEN_UNCOLLECTABLE);
		OBJECT.set_function("SET_PICKUP_OBJECT_TRANSPARENT_WHEN_UNCOLLECTABLE", LUA_NATIVE_OBJECT_SET_PICKUP_OBJECT_TRANSPARENT_WHEN_UNCOLLECTABLE);
		OBJECT.set_function("SET_PICKUP_OBJECT_ALPHA_WHEN_TRANSPARENT", LUA_NATIVE_OBJECT_SET_PICKUP_OBJECT_ALPHA_WHEN_TRANSPARENT);
		OBJECT.set_function("SET_PORTABLE_PICKUP_PERSIST", LUA_NATIVE_OBJECT_SET_PORTABLE_PICKUP_PERSIST);
		OBJECT.set_function("ALLOW_PORTABLE_PICKUP_TO_MIGRATE_TO_NON_PARTICIPANTS", LUA_NATIVE_OBJECT_ALLOW_PORTABLE_PICKUP_TO_MIGRATE_TO_NON_PARTICIPANTS);
		OBJECT.set_function("FORCE_ACTIVATE_PHYSICS_ON_UNFIXED_PICKUP", LUA_NATIVE_OBJECT_FORCE_ACTIVATE_PHYSICS_ON_UNFIXED_PICKUP);
		OBJECT.set_function("ALLOW_PICKUP_BY_NONE_PARTICIPANT", LUA_NATIVE_OBJECT_ALLOW_PICKUP_BY_NONE_PARTICIPANT);
		OBJECT.set_function("SUPPRESS_PICKUP_REWARD_TYPE", LUA_NATIVE_OBJECT_SUPPRESS_PICKUP_REWARD_TYPE);
		OBJECT.set_function("CLEAR_ALL_PICKUP_REWARD_TYPE_SUPPRESSION", LUA_NATIVE_OBJECT_CLEAR_ALL_PICKUP_REWARD_TYPE_SUPPRESSION);
		OBJECT.set_function("CLEAR_PICKUP_REWARD_TYPE_SUPPRESSION", LUA_NATIVE_OBJECT_CLEAR_PICKUP_REWARD_TYPE_SUPPRESSION);
		OBJECT.set_function("RENDER_FAKE_PICKUP_GLOW", LUA_NATIVE_OBJECT_RENDER_FAKE_PICKUP_GLOW);
		OBJECT.set_function("SET_PICKUP_OBJECT_COLLECTABLE_IN_VEHICLE", LUA_NATIVE_OBJECT_SET_PICKUP_OBJECT_COLLECTABLE_IN_VEHICLE);
		OBJECT.set_function("SET_PICKUP_TRACK_DAMAGE_EVENTS", LUA_NATIVE_OBJECT_SET_PICKUP_TRACK_DAMAGE_EVENTS);
		OBJECT.set_function("SET_ENTITY_FLAG_SUPPRESS_SHADOW", LUA_NATIVE_OBJECT_SET_ENTITY_FLAG_SUPPRESS_SHADOW);
		OBJECT.set_function("SET_ENTITY_FLAG_RENDER_SMALL_SHADOW", LUA_NATIVE_OBJECT_SET_ENTITY_FLAG_RENDER_SMALL_SHADOW);
		OBJECT.set_function("GET_WEAPON_TYPE_FROM_PICKUP_TYPE", LUA_NATIVE_OBJECT_GET_WEAPON_TYPE_FROM_PICKUP_TYPE);
		OBJECT.set_function("GET_PICKUP_TYPE_FROM_WEAPON_HASH", LUA_NATIVE_OBJECT_GET_PICKUP_TYPE_FROM_WEAPON_HASH);
		OBJECT.set_function("IS_PICKUP_WEAPON_OBJECT_VALID", LUA_NATIVE_OBJECT_IS_PICKUP_WEAPON_OBJECT_VALID);
		OBJECT.set_function("GET_OBJECT_TINT_INDEX", LUA_NATIVE_OBJECT_GET_OBJECT_TINT_INDEX);
		OBJECT.set_function("SET_OBJECT_TINT_INDEX", LUA_NATIVE_OBJECT_SET_OBJECT_TINT_INDEX);
		OBJECT.set_function("SET_TINT_INDEX_CLOSEST_BUILDING_OF_TYPE", LUA_NATIVE_OBJECT_SET_TINT_INDEX_CLOSEST_BUILDING_OF_TYPE);
		OBJECT.set_function("SET_PROP_TINT_INDEX", LUA_NATIVE_OBJECT_SET_PROP_TINT_INDEX);
		OBJECT.set_function("SET_PROP_LIGHT_COLOR", LUA_NATIVE_OBJECT_SET_PROP_LIGHT_COLOR);
		OBJECT.set_function("IS_PROP_LIGHT_OVERRIDEN", LUA_NATIVE_OBJECT_IS_PROP_LIGHT_OVERRIDEN);
		OBJECT.set_function("SET_OBJECT_IS_VISIBLE_IN_MIRRORS", LUA_NATIVE_OBJECT_SET_OBJECT_IS_VISIBLE_IN_MIRRORS);
		OBJECT.set_function("SET_OBJECT_SPEED_BOOST_AMOUNT", LUA_NATIVE_OBJECT_SET_OBJECT_SPEED_BOOST_AMOUNT);
		OBJECT.set_function("SET_OBJECT_SPEED_BOOST_DURATION", LUA_NATIVE_OBJECT_SET_OBJECT_SPEED_BOOST_DURATION);
		OBJECT.set_function("CONVERT_OLD_PICKUP_TYPE_TO_NEW", LUA_NATIVE_OBJECT_CONVERT_OLD_PICKUP_TYPE_TO_NEW);
		OBJECT.set_function("SET_FORCE_OBJECT_THIS_FRAME", LUA_NATIVE_OBJECT_SET_FORCE_OBJECT_THIS_FRAME);
		OBJECT.set_function("ONLY_CLEAN_UP_OBJECT_WHEN_OUT_OF_RANGE", LUA_NATIVE_OBJECT_ONLY_CLEAN_UP_OBJECT_WHEN_OUT_OF_RANGE);
		OBJECT.set_function("SET_DISABLE_COLLISIONS_BETWEEN_CARS_AND_CAR_PARACHUTE", LUA_NATIVE_OBJECT_SET_DISABLE_COLLISIONS_BETWEEN_CARS_AND_CAR_PARACHUTE);
		OBJECT.set_function("SET_PROJECTILES_SHOULD_EXPLODE_ON_CONTACT", LUA_NATIVE_OBJECT_SET_PROJECTILES_SHOULD_EXPLODE_ON_CONTACT);
		OBJECT.set_function("SET_DRIVE_ARTICULATED_JOINT", LUA_NATIVE_OBJECT_SET_DRIVE_ARTICULATED_JOINT);
		OBJECT.set_function("SET_DRIVE_ARTICULATED_JOINT_WITH_INFLICTOR", LUA_NATIVE_OBJECT_SET_DRIVE_ARTICULATED_JOINT_WITH_INFLICTOR);
		OBJECT.set_function("SET_OBJECT_IS_A_PRESSURE_PLATE", LUA_NATIVE_OBJECT_SET_OBJECT_IS_A_PRESSURE_PLATE);
		OBJECT.set_function("SET_WEAPON_IMPACTS_APPLY_GREATER_FORCE", LUA_NATIVE_OBJECT_SET_WEAPON_IMPACTS_APPLY_GREATER_FORCE);
		OBJECT.set_function("GET_IS_ARTICULATED_JOINT_AT_MIN_ANGLE", LUA_NATIVE_OBJECT_GET_IS_ARTICULATED_JOINT_AT_MIN_ANGLE);
		OBJECT.set_function("GET_IS_ARTICULATED_JOINT_AT_MAX_ANGLE", LUA_NATIVE_OBJECT_GET_IS_ARTICULATED_JOINT_AT_MAX_ANGLE);
		OBJECT.set_function("SET_IS_OBJECT_ARTICULATED", LUA_NATIVE_OBJECT_SET_IS_OBJECT_ARTICULATED);
		OBJECT.set_function("SET_IS_OBJECT_BALL", LUA_NATIVE_OBJECT_SET_IS_OBJECT_BALL);
	}
}
