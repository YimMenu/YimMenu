#include "lua_native_binding.hpp"
#include "natives.hpp"

namespace lua::native
{
	static void LUA_NATIVE_PATHFIND_SET_ROADS_IN_AREA(float x1, float y1, float z1, float x2, float y2, float z2, bool nodeEnabled, bool unknown2)
	{
		PATHFIND::SET_ROADS_IN_AREA(x1, y1, z1, x2, y2, z2, nodeEnabled, unknown2);
	}

	static void LUA_NATIVE_PATHFIND_SET_ROADS_IN_ANGLED_AREA(float x1, float y1, float z1, float x2, float y2, float z2, float width, bool unknown1, bool unknown2, bool unknown3)
	{
		PATHFIND::SET_ROADS_IN_ANGLED_AREA(x1, y1, z1, x2, y2, z2, width, unknown1, unknown2, unknown3);
	}

	static void LUA_NATIVE_PATHFIND_SET_PED_PATHS_IN_AREA(float x1, float y1, float z1, float x2, float y2, float z2, bool p6, Any p7)
	{
		PATHFIND::SET_PED_PATHS_IN_AREA(x1, y1, z1, x2, y2, z2, p6, p7);
	}

	static std::tuple<bool, Vector3> LUA_NATIVE_PATHFIND_GET_SAFE_COORD_FOR_PED(float x, float y, float z, bool onGround, Vector3 outPosition, int flags)
	{
		std::tuple<bool, Vector3> return_values;
		std::get<0>(return_values) = (bool)PATHFIND::GET_SAFE_COORD_FOR_PED(x, y, z, onGround, &outPosition, flags);
		std::get<1>(return_values) = outPosition;

		return return_values;
	}

	static std::tuple<bool, Vector3> LUA_NATIVE_PATHFIND_GET_CLOSEST_VEHICLE_NODE(float x, float y, float z, Vector3 outPosition, int nodeFlags, float p5, float p6)
	{
		std::tuple<bool, Vector3> return_values;
		std::get<0>(return_values) = (bool)PATHFIND::GET_CLOSEST_VEHICLE_NODE(x, y, z, &outPosition, nodeFlags, p5, p6);
		std::get<1>(return_values) = outPosition;

		return return_values;
	}

	static std::tuple<bool, Vector3> LUA_NATIVE_PATHFIND_GET_CLOSEST_MAJOR_VEHICLE_NODE(float x, float y, float z, Vector3 outPosition, float unknown1, float unknown2)
	{
		std::tuple<bool, Vector3> return_values;
		std::get<0>(return_values) = (bool)PATHFIND::GET_CLOSEST_MAJOR_VEHICLE_NODE(x, y, z, &outPosition, unknown1, unknown2);
		std::get<1>(return_values) = outPosition;

		return return_values;
	}

	static std::tuple<bool, Vector3, float> LUA_NATIVE_PATHFIND_GET_CLOSEST_VEHICLE_NODE_WITH_HEADING(float x, float y, float z, Vector3 outPosition, float outHeading, int nodeType, float p6, float p7)
	{
		std::tuple<bool, Vector3, float> return_values;
		std::get<0>(return_values) = (bool)PATHFIND::GET_CLOSEST_VEHICLE_NODE_WITH_HEADING(x, y, z, &outPosition, &outHeading, nodeType, p6, p7);
		std::get<1>(return_values) = outPosition;
		std::get<2>(return_values) = outHeading;

		return return_values;
	}

	static std::tuple<bool, Vector3> LUA_NATIVE_PATHFIND_GET_NTH_CLOSEST_VEHICLE_NODE(float x, float y, float z, int nthClosest, Vector3 outPosition, int nodeFlags, float unknown1, float unknown2)
	{
		std::tuple<bool, Vector3> return_values;
		std::get<0>(return_values) = (bool)PATHFIND::GET_NTH_CLOSEST_VEHICLE_NODE(x, y, z, nthClosest, &outPosition, nodeFlags, unknown1, unknown2);
		std::get<1>(return_values) = outPosition;

		return return_values;
	}

	static int LUA_NATIVE_PATHFIND_GET_NTH_CLOSEST_VEHICLE_NODE_ID(float x, float y, float z, int nth, int nodeFlags, float p5, float p6)
	{
		auto retval = PATHFIND::GET_NTH_CLOSEST_VEHICLE_NODE_ID(x, y, z, nth, nodeFlags, p5, p6);
		return retval;
	}

	static std::tuple<bool, Vector3, float, int> LUA_NATIVE_PATHFIND_GET_NTH_CLOSEST_VEHICLE_NODE_WITH_HEADING(float x, float y, float z, int nthClosest, Vector3 outPosition, float outHeading, int outNumLanes, int nodeFlags, float unknown3, float unknown4)
	{
		std::tuple<bool, Vector3, float, int> return_values;
		std::get<0>(return_values) = (bool)PATHFIND::GET_NTH_CLOSEST_VEHICLE_NODE_WITH_HEADING(x, y, z, nthClosest, &outPosition, &outHeading, &outNumLanes, nodeFlags, unknown3, unknown4);
		std::get<1>(return_values) = outPosition;
		std::get<2>(return_values) = outHeading;
		std::get<3>(return_values) = outNumLanes;

		return return_values;
	}

	static std::tuple<int, Vector3, float> LUA_NATIVE_PATHFIND_GET_NTH_CLOSEST_VEHICLE_NODE_ID_WITH_HEADING(float x, float y, float z, int nthClosest, Vector3 outPosition, float outHeading, int nodeFlags, float p7, float p8)
	{
		std::tuple<int, Vector3, float> return_values;
		std::get<0>(return_values) = PATHFIND::GET_NTH_CLOSEST_VEHICLE_NODE_ID_WITH_HEADING(x, y, z, nthClosest, &outPosition, &outHeading, nodeFlags, p7, p8);
		std::get<1>(return_values) = outPosition;
		std::get<2>(return_values) = outHeading;

		return return_values;
	}

	static std::tuple<bool, Vector3, float> LUA_NATIVE_PATHFIND_GET_NTH_CLOSEST_VEHICLE_NODE_FAVOUR_DIRECTION(float x, float y, float z, float desiredX, float desiredY, float desiredZ, int nthClosest, Vector3 outPosition, float outHeading, int nodeFlags, float p10, float p11)
	{
		std::tuple<bool, Vector3, float> return_values;
		std::get<0>(return_values) = (bool)PATHFIND::GET_NTH_CLOSEST_VEHICLE_NODE_FAVOUR_DIRECTION(x, y, z, desiredX, desiredY, desiredZ, nthClosest, &outPosition, &outHeading, nodeFlags, p10, p11);
		std::get<1>(return_values) = outPosition;
		std::get<2>(return_values) = outHeading;

		return return_values;
	}

	static std::tuple<bool, int, int> LUA_NATIVE_PATHFIND_GET_VEHICLE_NODE_PROPERTIES(float x, float y, float z, int density, int flags)
	{
		std::tuple<bool, int, int> return_values;
		std::get<0>(return_values) = (bool)PATHFIND::GET_VEHICLE_NODE_PROPERTIES(x, y, z, &density, &flags);
		std::get<1>(return_values) = density;
		std::get<2>(return_values) = flags;

		return return_values;
	}

	static bool LUA_NATIVE_PATHFIND_IS_VEHICLE_NODE_ID_VALID(int vehicleNodeId)
	{
		auto retval = (bool)PATHFIND::IS_VEHICLE_NODE_ID_VALID(vehicleNodeId);
		return retval;
	}

	static Vector3 LUA_NATIVE_PATHFIND_GET_VEHICLE_NODE_POSITION(int nodeId, Vector3 outPosition)
	{
		PATHFIND::GET_VEHICLE_NODE_POSITION(nodeId, &outPosition);
		return outPosition;
	}

	static bool LUA_NATIVE_PATHFIND_GET_VEHICLE_NODE_IS_GPS_ALLOWED(int nodeID)
	{
		auto retval = (bool)PATHFIND::GET_VEHICLE_NODE_IS_GPS_ALLOWED(nodeID);
		return retval;
	}

	static bool LUA_NATIVE_PATHFIND_GET_VEHICLE_NODE_IS_SWITCHED_OFF(int nodeID)
	{
		auto retval = (bool)PATHFIND::GET_VEHICLE_NODE_IS_SWITCHED_OFF(nodeID);
		return retval;
	}

	static std::tuple<bool, Vector3, Vector3, float> LUA_NATIVE_PATHFIND_GET_CLOSEST_ROAD(float x, float y, float z, float p3, int p4, Vector3 p5, Vector3 p6, uintptr_t p7, uintptr_t p8, float p9, bool p10)
	{
		std::tuple<bool, Vector3, Vector3, float> return_values;
		std::get<0>(return_values) = (bool)PATHFIND::GET_CLOSEST_ROAD(x, y, z, p3, p4, &p5, &p6, (Any*)p7, (Any*)p8, &p9, p10);
		std::get<1>(return_values) = p5;
		std::get<2>(return_values) = p6;
		std::get<3>(return_values) = p9;

		return return_values;
	}

	static bool LUA_NATIVE_PATHFIND_LOAD_ALL_PATH_NODES(bool set)
	{
		auto retval = (bool)PATHFIND::LOAD_ALL_PATH_NODES(set);
		return retval;
	}

	static void LUA_NATIVE_PATHFIND_SET_ALLOW_STREAM_PROLOGUE_NODES(bool toggle)
	{
		PATHFIND::SET_ALLOW_STREAM_PROLOGUE_NODES(toggle);
	}

	static void LUA_NATIVE_PATHFIND_SET_ALLOW_STREAM_HEIST_ISLAND_NODES(int type)
	{
		PATHFIND::SET_ALLOW_STREAM_HEIST_ISLAND_NODES(type);
	}

	static bool LUA_NATIVE_PATHFIND_ARE_NODES_LOADED_FOR_AREA(float x1, float y1, float x2, float y2)
	{
		auto retval = (bool)PATHFIND::ARE_NODES_LOADED_FOR_AREA(x1, y1, x2, y2);
		return retval;
	}

	static bool LUA_NATIVE_PATHFIND_REQUEST_PATH_NODES_IN_AREA_THIS_FRAME(float x1, float y1, float x2, float y2)
	{
		auto retval = (bool)PATHFIND::REQUEST_PATH_NODES_IN_AREA_THIS_FRAME(x1, y1, x2, y2);
		return retval;
	}

	static void LUA_NATIVE_PATHFIND_SET_ROADS_BACK_TO_ORIGINAL(float p0, float p1, float p2, float p3, float p4, float p5, Any p6)
	{
		PATHFIND::SET_ROADS_BACK_TO_ORIGINAL(p0, p1, p2, p3, p4, p5, p6);
	}

	static void LUA_NATIVE_PATHFIND_SET_ROADS_BACK_TO_ORIGINAL_IN_ANGLED_AREA(float x1, float y1, float z1, float x2, float y2, float z2, float width, Any p7)
	{
		PATHFIND::SET_ROADS_BACK_TO_ORIGINAL_IN_ANGLED_AREA(x1, y1, z1, x2, y2, z2, width, p7);
	}

	static void LUA_NATIVE_PATHFIND_SET_AMBIENT_PED_RANGE_MULTIPLIER_THIS_FRAME(float multiplier)
	{
		PATHFIND::SET_AMBIENT_PED_RANGE_MULTIPLIER_THIS_FRAME(multiplier);
	}

	static void LUA_NATIVE_PATHFIND_ADJUST_AMBIENT_PED_SPAWN_DENSITIES_THIS_FRAME(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6)
	{
		PATHFIND::ADJUST_AMBIENT_PED_SPAWN_DENSITIES_THIS_FRAME(p0, p1, p2, p3, p4, p5, p6);
	}

	static void LUA_NATIVE_PATHFIND_SET_PED_PATHS_BACK_TO_ORIGINAL(float x1, float y1, float z1, float x2, float y2, float z2, Any p6)
	{
		PATHFIND::SET_PED_PATHS_BACK_TO_ORIGINAL(x1, y1, z1, x2, y2, z2, p6);
	}

	static std::tuple<bool, Vector3, int> LUA_NATIVE_PATHFIND_GET_RANDOM_VEHICLE_NODE(float x, float y, float z, float radius, bool p4, bool p5, bool p6, Vector3 outPosition, int nodeId)
	{
		std::tuple<bool, Vector3, int> return_values;
		std::get<0>(return_values) = (bool)PATHFIND::GET_RANDOM_VEHICLE_NODE(x, y, z, radius, p4, p5, p6, &outPosition, &nodeId);
		std::get<1>(return_values) = outPosition;
		std::get<2>(return_values) = nodeId;

		return return_values;
	}

	static std::tuple<Vector3, Vector3, float> LUA_NATIVE_PATHFIND_GET_SPAWN_COORDS_FOR_VEHICLE_NODE(int nodeAddress, float towardsCoorsX, float towardsCoorsY, float towardsCoorsZ, Vector3 centrePoint, float heading)
	{
		std::tuple<Vector3, Vector3, float> return_values;
		std::get<0>(return_values) = PATHFIND::GET_SPAWN_COORDS_FOR_VEHICLE_NODE(nodeAddress, towardsCoorsX, towardsCoorsY, towardsCoorsZ, &centrePoint, &heading);
		std::get<1>(return_values) = centrePoint;
		std::get<2>(return_values) = heading;

		return return_values;
	}

	static std::tuple<Hash, Hash> LUA_NATIVE_PATHFIND_GET_STREET_NAME_AT_COORD(float x, float y, float z, Hash streetName, Hash crossingRoad)
	{
		std::tuple<Hash, Hash> return_values;
		PATHFIND::GET_STREET_NAME_AT_COORD(x, y, z, &streetName, &crossingRoad);
		std::get<0>(return_values) = streetName;
		std::get<1>(return_values) = crossingRoad;

		return return_values;
	}

	static std::tuple<int, int, float, float> LUA_NATIVE_PATHFIND_GENERATE_DIRECTIONS_TO_COORD(float x, float y, float z, bool p3, int direction, float p5, float distToNxJunction)
	{
		std::tuple<int, int, float, float> return_values;
		std::get<0>(return_values) = PATHFIND::GENERATE_DIRECTIONS_TO_COORD(x, y, z, p3, &direction, &p5, &distToNxJunction);
		std::get<1>(return_values) = direction;
		std::get<2>(return_values) = p5;
		std::get<3>(return_values) = distToNxJunction;

		return return_values;
	}

	static void LUA_NATIVE_PATHFIND_SET_IGNORE_NO_GPS_FLAG(bool toggle)
	{
		PATHFIND::SET_IGNORE_NO_GPS_FLAG(toggle);
	}

	static void LUA_NATIVE_PATHFIND_SET_IGNORE_NO_GPS_FLAG_UNTIL_FIRST_NORMAL_NODE(bool toggle)
	{
		PATHFIND::SET_IGNORE_NO_GPS_FLAG_UNTIL_FIRST_NORMAL_NODE(toggle);
	}

	static void LUA_NATIVE_PATHFIND_SET_GPS_DISABLED_ZONE(float x1, float y1, float z1, float x2, float y2, float z3)
	{
		PATHFIND::SET_GPS_DISABLED_ZONE(x1, y1, z1, x2, y2, z3);
	}

	static int LUA_NATIVE_PATHFIND_GET_GPS_BLIP_ROUTE_LENGTH()
	{
		auto retval = PATHFIND::GET_GPS_BLIP_ROUTE_LENGTH();
		return retval;
	}

	static std::tuple<bool, Vector3> LUA_NATIVE_PATHFIND_GET_POS_ALONG_GPS_TYPE_ROUTE(Vector3 result, bool p1, float p2, int p3)
	{
		std::tuple<bool, Vector3> return_values;
		std::get<0>(return_values) = (bool)PATHFIND::GET_POS_ALONG_GPS_TYPE_ROUTE(&result, p1, p2, p3);
		std::get<1>(return_values) = result;

		return return_values;
	}

	static bool LUA_NATIVE_PATHFIND_GET_GPS_BLIP_ROUTE_FOUND()
	{
		auto retval = (bool)PATHFIND::GET_GPS_BLIP_ROUTE_FOUND();
		return retval;
	}

	static std::tuple<bool, Vector3> LUA_NATIVE_PATHFIND_GET_ROAD_BOUNDARY_USING_HEADING(float x, float y, float z, float heading, Vector3 outPosition)
	{
		std::tuple<bool, Vector3> return_values;
		std::get<0>(return_values) = (bool)PATHFIND::GET_ROAD_BOUNDARY_USING_HEADING(x, y, z, heading, &outPosition);
		std::get<1>(return_values) = outPosition;

		return return_values;
	}

	static std::tuple<bool, Vector3> LUA_NATIVE_PATHFIND_GET_POSITION_BY_SIDE_OF_ROAD(float x, float y, float z, int p3, Vector3 outPosition)
	{
		std::tuple<bool, Vector3> return_values;
		std::get<0>(return_values) = (bool)PATHFIND::GET_POSITION_BY_SIDE_OF_ROAD(x, y, z, p3, &outPosition);
		std::get<1>(return_values) = outPosition;

		return return_values;
	}

	static bool LUA_NATIVE_PATHFIND_IS_POINT_ON_ROAD(float x, float y, float z, Vehicle vehicle)
	{
		auto retval = (bool)PATHFIND::IS_POINT_ON_ROAD(x, y, z, vehicle);
		return retval;
	}

	static int LUA_NATIVE_PATHFIND_GET_NEXT_GPS_DISABLED_ZONE_INDEX()
	{
		auto retval = PATHFIND::GET_NEXT_GPS_DISABLED_ZONE_INDEX();
		return retval;
	}

	static void LUA_NATIVE_PATHFIND_SET_GPS_DISABLED_ZONE_AT_INDEX(float x1, float y1, float z1, float x2, float y2, float z2, int index)
	{
		PATHFIND::SET_GPS_DISABLED_ZONE_AT_INDEX(x1, y1, z1, x2, y2, z2, index);
	}

	static void LUA_NATIVE_PATHFIND_CLEAR_GPS_DISABLED_ZONE_AT_INDEX(int index)
	{
		PATHFIND::CLEAR_GPS_DISABLED_ZONE_AT_INDEX(index);
	}

	static void LUA_NATIVE_PATHFIND_ADD_NAVMESH_REQUIRED_REGION(float x, float y, float radius)
	{
		PATHFIND::ADD_NAVMESH_REQUIRED_REGION(x, y, radius);
	}

	static void LUA_NATIVE_PATHFIND_REMOVE_NAVMESH_REQUIRED_REGIONS()
	{
		PATHFIND::REMOVE_NAVMESH_REQUIRED_REGIONS();
	}

	static bool LUA_NATIVE_PATHFIND_IS_NAVMESH_REQUIRED_REGION_IN_USE()
	{
		auto retval = (bool)PATHFIND::IS_NAVMESH_REQUIRED_REGION_IN_USE();
		return retval;
	}

	static void LUA_NATIVE_PATHFIND_DISABLE_NAVMESH_IN_AREA(float x1, float y1, float z1, float x2, float y2, float z2, bool toggle)
	{
		PATHFIND::DISABLE_NAVMESH_IN_AREA(x1, y1, z1, x2, y2, z2, toggle);
	}

	static bool LUA_NATIVE_PATHFIND_ARE_ALL_NAVMESH_REGIONS_LOADED()
	{
		auto retval = (bool)PATHFIND::ARE_ALL_NAVMESH_REGIONS_LOADED();
		return retval;
	}

	static bool LUA_NATIVE_PATHFIND_IS_NAVMESH_LOADED_IN_AREA(float x1, float y1, float z1, float x2, float y2, float z2)
	{
		auto retval = (bool)PATHFIND::IS_NAVMESH_LOADED_IN_AREA(x1, y1, z1, x2, y2, z2);
		return retval;
	}

	static int LUA_NATIVE_PATHFIND_GET_NUM_NAVMESHES_EXISTING_IN_AREA(float x1, float y1, float z1, float x2, float y2, float z2)
	{
		auto retval = PATHFIND::GET_NUM_NAVMESHES_EXISTING_IN_AREA(x1, y1, z1, x2, y2, z2);
		return retval;
	}

	static int LUA_NATIVE_PATHFIND_ADD_NAVMESH_BLOCKING_OBJECT(float p0, float p1, float p2, float p3, float p4, float p5, float p6, bool p7, Any p8)
	{
		auto retval = PATHFIND::ADD_NAVMESH_BLOCKING_OBJECT(p0, p1, p2, p3, p4, p5, p6, p7, p8);
		return retval;
	}

	static void LUA_NATIVE_PATHFIND_UPDATE_NAVMESH_BLOCKING_OBJECT(Any p0, float p1, float p2, float p3, float p4, float p5, float p6, float p7, Any p8)
	{
		PATHFIND::UPDATE_NAVMESH_BLOCKING_OBJECT(p0, p1, p2, p3, p4, p5, p6, p7, p8);
	}

	static void LUA_NATIVE_PATHFIND_REMOVE_NAVMESH_BLOCKING_OBJECT(Any p0)
	{
		PATHFIND::REMOVE_NAVMESH_BLOCKING_OBJECT(p0);
	}

	static bool LUA_NATIVE_PATHFIND_DOES_NAVMESH_BLOCKING_OBJECT_EXIST(Any p0)
	{
		auto retval = (bool)PATHFIND::DOES_NAVMESH_BLOCKING_OBJECT_EXIST(p0);
		return retval;
	}

	static float LUA_NATIVE_PATHFIND_GET_APPROX_HEIGHT_FOR_POINT(float x, float y)
	{
		auto retval = PATHFIND::GET_APPROX_HEIGHT_FOR_POINT(x, y);
		return retval;
	}

	static float LUA_NATIVE_PATHFIND_GET_APPROX_HEIGHT_FOR_AREA(float x1, float y1, float x2, float y2)
	{
		auto retval = PATHFIND::GET_APPROX_HEIGHT_FOR_AREA(x1, y1, x2, y2);
		return retval;
	}

	static float LUA_NATIVE_PATHFIND_GET_APPROX_FLOOR_FOR_POINT(float x, float y)
	{
		auto retval = PATHFIND::GET_APPROX_FLOOR_FOR_POINT(x, y);
		return retval;
	}

	static float LUA_NATIVE_PATHFIND_GET_APPROX_FLOOR_FOR_AREA(float x1, float y1, float x2, float y2)
	{
		auto retval = PATHFIND::GET_APPROX_FLOOR_FOR_AREA(x1, y1, x2, y2);
		return retval;
	}

	static float LUA_NATIVE_PATHFIND_CALCULATE_TRAVEL_DISTANCE_BETWEEN_POINTS(float x1, float y1, float z1, float x2, float y2, float z2)
	{
		auto retval = PATHFIND::CALCULATE_TRAVEL_DISTANCE_BETWEEN_POINTS(x1, y1, z1, x2, y2, z2);
		return retval;
	}

	void init_native_binding_PATHFIND(sol::state& L)
	{
		auto PATHFIND = L["PATHFIND"].get_or_create<sol::table>();
		PATHFIND.set_function("SET_ROADS_IN_AREA", LUA_NATIVE_PATHFIND_SET_ROADS_IN_AREA);
		PATHFIND.set_function("SET_ROADS_IN_ANGLED_AREA", LUA_NATIVE_PATHFIND_SET_ROADS_IN_ANGLED_AREA);
		PATHFIND.set_function("SET_PED_PATHS_IN_AREA", LUA_NATIVE_PATHFIND_SET_PED_PATHS_IN_AREA);
		PATHFIND.set_function("GET_SAFE_COORD_FOR_PED", LUA_NATIVE_PATHFIND_GET_SAFE_COORD_FOR_PED);
		PATHFIND.set_function("GET_CLOSEST_VEHICLE_NODE", LUA_NATIVE_PATHFIND_GET_CLOSEST_VEHICLE_NODE);
		PATHFIND.set_function("GET_CLOSEST_MAJOR_VEHICLE_NODE", LUA_NATIVE_PATHFIND_GET_CLOSEST_MAJOR_VEHICLE_NODE);
		PATHFIND.set_function("GET_CLOSEST_VEHICLE_NODE_WITH_HEADING", LUA_NATIVE_PATHFIND_GET_CLOSEST_VEHICLE_NODE_WITH_HEADING);
		PATHFIND.set_function("GET_NTH_CLOSEST_VEHICLE_NODE", LUA_NATIVE_PATHFIND_GET_NTH_CLOSEST_VEHICLE_NODE);
		PATHFIND.set_function("GET_NTH_CLOSEST_VEHICLE_NODE_ID", LUA_NATIVE_PATHFIND_GET_NTH_CLOSEST_VEHICLE_NODE_ID);
		PATHFIND.set_function("GET_NTH_CLOSEST_VEHICLE_NODE_WITH_HEADING", LUA_NATIVE_PATHFIND_GET_NTH_CLOSEST_VEHICLE_NODE_WITH_HEADING);
		PATHFIND.set_function("GET_NTH_CLOSEST_VEHICLE_NODE_ID_WITH_HEADING", LUA_NATIVE_PATHFIND_GET_NTH_CLOSEST_VEHICLE_NODE_ID_WITH_HEADING);
		PATHFIND.set_function("GET_NTH_CLOSEST_VEHICLE_NODE_FAVOUR_DIRECTION", LUA_NATIVE_PATHFIND_GET_NTH_CLOSEST_VEHICLE_NODE_FAVOUR_DIRECTION);
		PATHFIND.set_function("GET_VEHICLE_NODE_PROPERTIES", LUA_NATIVE_PATHFIND_GET_VEHICLE_NODE_PROPERTIES);
		PATHFIND.set_function("IS_VEHICLE_NODE_ID_VALID", LUA_NATIVE_PATHFIND_IS_VEHICLE_NODE_ID_VALID);
		PATHFIND.set_function("GET_VEHICLE_NODE_POSITION", LUA_NATIVE_PATHFIND_GET_VEHICLE_NODE_POSITION);
		PATHFIND.set_function("GET_VEHICLE_NODE_IS_GPS_ALLOWED", LUA_NATIVE_PATHFIND_GET_VEHICLE_NODE_IS_GPS_ALLOWED);
		PATHFIND.set_function("GET_VEHICLE_NODE_IS_SWITCHED_OFF", LUA_NATIVE_PATHFIND_GET_VEHICLE_NODE_IS_SWITCHED_OFF);
		PATHFIND.set_function("GET_CLOSEST_ROAD", LUA_NATIVE_PATHFIND_GET_CLOSEST_ROAD);
		PATHFIND.set_function("LOAD_ALL_PATH_NODES", LUA_NATIVE_PATHFIND_LOAD_ALL_PATH_NODES);
		PATHFIND.set_function("SET_ALLOW_STREAM_PROLOGUE_NODES", LUA_NATIVE_PATHFIND_SET_ALLOW_STREAM_PROLOGUE_NODES);
		PATHFIND.set_function("SET_ALLOW_STREAM_HEIST_ISLAND_NODES", LUA_NATIVE_PATHFIND_SET_ALLOW_STREAM_HEIST_ISLAND_NODES);
		PATHFIND.set_function("ARE_NODES_LOADED_FOR_AREA", LUA_NATIVE_PATHFIND_ARE_NODES_LOADED_FOR_AREA);
		PATHFIND.set_function("REQUEST_PATH_NODES_IN_AREA_THIS_FRAME", LUA_NATIVE_PATHFIND_REQUEST_PATH_NODES_IN_AREA_THIS_FRAME);
		PATHFIND.set_function("SET_ROADS_BACK_TO_ORIGINAL", LUA_NATIVE_PATHFIND_SET_ROADS_BACK_TO_ORIGINAL);
		PATHFIND.set_function("SET_ROADS_BACK_TO_ORIGINAL_IN_ANGLED_AREA", LUA_NATIVE_PATHFIND_SET_ROADS_BACK_TO_ORIGINAL_IN_ANGLED_AREA);
		PATHFIND.set_function("SET_AMBIENT_PED_RANGE_MULTIPLIER_THIS_FRAME", LUA_NATIVE_PATHFIND_SET_AMBIENT_PED_RANGE_MULTIPLIER_THIS_FRAME);
		PATHFIND.set_function("ADJUST_AMBIENT_PED_SPAWN_DENSITIES_THIS_FRAME", LUA_NATIVE_PATHFIND_ADJUST_AMBIENT_PED_SPAWN_DENSITIES_THIS_FRAME);
		PATHFIND.set_function("SET_PED_PATHS_BACK_TO_ORIGINAL", LUA_NATIVE_PATHFIND_SET_PED_PATHS_BACK_TO_ORIGINAL);
		PATHFIND.set_function("GET_RANDOM_VEHICLE_NODE", LUA_NATIVE_PATHFIND_GET_RANDOM_VEHICLE_NODE);
		PATHFIND.set_function("GET_SPAWN_COORDS_FOR_VEHICLE_NODE", LUA_NATIVE_PATHFIND_GET_SPAWN_COORDS_FOR_VEHICLE_NODE);
		PATHFIND.set_function("GET_STREET_NAME_AT_COORD", LUA_NATIVE_PATHFIND_GET_STREET_NAME_AT_COORD);
		PATHFIND.set_function("GENERATE_DIRECTIONS_TO_COORD", LUA_NATIVE_PATHFIND_GENERATE_DIRECTIONS_TO_COORD);
		PATHFIND.set_function("SET_IGNORE_NO_GPS_FLAG", LUA_NATIVE_PATHFIND_SET_IGNORE_NO_GPS_FLAG);
		PATHFIND.set_function("SET_IGNORE_NO_GPS_FLAG_UNTIL_FIRST_NORMAL_NODE", LUA_NATIVE_PATHFIND_SET_IGNORE_NO_GPS_FLAG_UNTIL_FIRST_NORMAL_NODE);
		PATHFIND.set_function("SET_GPS_DISABLED_ZONE", LUA_NATIVE_PATHFIND_SET_GPS_DISABLED_ZONE);
		PATHFIND.set_function("GET_GPS_BLIP_ROUTE_LENGTH", LUA_NATIVE_PATHFIND_GET_GPS_BLIP_ROUTE_LENGTH);
		PATHFIND.set_function("GET_POS_ALONG_GPS_TYPE_ROUTE", LUA_NATIVE_PATHFIND_GET_POS_ALONG_GPS_TYPE_ROUTE);
		PATHFIND.set_function("GET_GPS_BLIP_ROUTE_FOUND", LUA_NATIVE_PATHFIND_GET_GPS_BLIP_ROUTE_FOUND);
		PATHFIND.set_function("GET_ROAD_BOUNDARY_USING_HEADING", LUA_NATIVE_PATHFIND_GET_ROAD_BOUNDARY_USING_HEADING);
		PATHFIND.set_function("GET_POSITION_BY_SIDE_OF_ROAD", LUA_NATIVE_PATHFIND_GET_POSITION_BY_SIDE_OF_ROAD);
		PATHFIND.set_function("IS_POINT_ON_ROAD", LUA_NATIVE_PATHFIND_IS_POINT_ON_ROAD);
		PATHFIND.set_function("GET_NEXT_GPS_DISABLED_ZONE_INDEX", LUA_NATIVE_PATHFIND_GET_NEXT_GPS_DISABLED_ZONE_INDEX);
		PATHFIND.set_function("SET_GPS_DISABLED_ZONE_AT_INDEX", LUA_NATIVE_PATHFIND_SET_GPS_DISABLED_ZONE_AT_INDEX);
		PATHFIND.set_function("CLEAR_GPS_DISABLED_ZONE_AT_INDEX", LUA_NATIVE_PATHFIND_CLEAR_GPS_DISABLED_ZONE_AT_INDEX);
		PATHFIND.set_function("ADD_NAVMESH_REQUIRED_REGION", LUA_NATIVE_PATHFIND_ADD_NAVMESH_REQUIRED_REGION);
		PATHFIND.set_function("REMOVE_NAVMESH_REQUIRED_REGIONS", LUA_NATIVE_PATHFIND_REMOVE_NAVMESH_REQUIRED_REGIONS);
		PATHFIND.set_function("IS_NAVMESH_REQUIRED_REGION_IN_USE", LUA_NATIVE_PATHFIND_IS_NAVMESH_REQUIRED_REGION_IN_USE);
		PATHFIND.set_function("DISABLE_NAVMESH_IN_AREA", LUA_NATIVE_PATHFIND_DISABLE_NAVMESH_IN_AREA);
		PATHFIND.set_function("ARE_ALL_NAVMESH_REGIONS_LOADED", LUA_NATIVE_PATHFIND_ARE_ALL_NAVMESH_REGIONS_LOADED);
		PATHFIND.set_function("IS_NAVMESH_LOADED_IN_AREA", LUA_NATIVE_PATHFIND_IS_NAVMESH_LOADED_IN_AREA);
		PATHFIND.set_function("GET_NUM_NAVMESHES_EXISTING_IN_AREA", LUA_NATIVE_PATHFIND_GET_NUM_NAVMESHES_EXISTING_IN_AREA);
		PATHFIND.set_function("ADD_NAVMESH_BLOCKING_OBJECT", LUA_NATIVE_PATHFIND_ADD_NAVMESH_BLOCKING_OBJECT);
		PATHFIND.set_function("UPDATE_NAVMESH_BLOCKING_OBJECT", LUA_NATIVE_PATHFIND_UPDATE_NAVMESH_BLOCKING_OBJECT);
		PATHFIND.set_function("REMOVE_NAVMESH_BLOCKING_OBJECT", LUA_NATIVE_PATHFIND_REMOVE_NAVMESH_BLOCKING_OBJECT);
		PATHFIND.set_function("DOES_NAVMESH_BLOCKING_OBJECT_EXIST", LUA_NATIVE_PATHFIND_DOES_NAVMESH_BLOCKING_OBJECT_EXIST);
		PATHFIND.set_function("GET_APPROX_HEIGHT_FOR_POINT", LUA_NATIVE_PATHFIND_GET_APPROX_HEIGHT_FOR_POINT);
		PATHFIND.set_function("GET_APPROX_HEIGHT_FOR_AREA", LUA_NATIVE_PATHFIND_GET_APPROX_HEIGHT_FOR_AREA);
		PATHFIND.set_function("GET_APPROX_FLOOR_FOR_POINT", LUA_NATIVE_PATHFIND_GET_APPROX_FLOOR_FOR_POINT);
		PATHFIND.set_function("GET_APPROX_FLOOR_FOR_AREA", LUA_NATIVE_PATHFIND_GET_APPROX_FLOOR_FOR_AREA);
		PATHFIND.set_function("CALCULATE_TRAVEL_DISTANCE_BETWEEN_POINTS", LUA_NATIVE_PATHFIND_CALCULATE_TRAVEL_DISTANCE_BETWEEN_POINTS);
	}
}
