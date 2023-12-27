#include "lua_native_binding.hpp"
#include "natives.hpp"

namespace lua::native
{
	static int LUA_NATIVE_SHAPETEST_START_SHAPE_TEST_LOS_PROBE(float x1, float y1, float z1, float x2, float y2, float z2, int flags, Entity entity, int p8)
	{
		auto retval = SHAPETEST::START_SHAPE_TEST_LOS_PROBE(x1, y1, z1, x2, y2, z2, flags, entity, p8);
		return retval;
	}

	static int LUA_NATIVE_SHAPETEST_START_EXPENSIVE_SYNCHRONOUS_SHAPE_TEST_LOS_PROBE(float x1, float y1, float z1, float x2, float y2, float z2, int flags, Entity entity, int p8)
	{
		auto retval = SHAPETEST::START_EXPENSIVE_SYNCHRONOUS_SHAPE_TEST_LOS_PROBE(x1, y1, z1, x2, y2, z2, flags, entity, p8);
		return retval;
	}

	static int LUA_NATIVE_SHAPETEST_START_SHAPE_TEST_BOUNDING_BOX(Entity entity, int flags1, int flags2)
	{
		auto retval = SHAPETEST::START_SHAPE_TEST_BOUNDING_BOX(entity, flags1, flags2);
		return retval;
	}

	static int LUA_NATIVE_SHAPETEST_START_SHAPE_TEST_BOX(float x, float y, float z, float dimX, float dimY, float dimZ, float rotX, float rotY, float rotZ, Any p9, int flags, Entity entity, Any p12)
	{
		auto retval = SHAPETEST::START_SHAPE_TEST_BOX(x, y, z, dimX, dimY, dimZ, rotX, rotY, rotZ, p9, flags, entity, p12);
		return retval;
	}

	static int LUA_NATIVE_SHAPETEST_START_SHAPE_TEST_BOUND(Entity entity, int flags1, int flags2)
	{
		auto retval = SHAPETEST::START_SHAPE_TEST_BOUND(entity, flags1, flags2);
		return retval;
	}

	static int LUA_NATIVE_SHAPETEST_START_SHAPE_TEST_CAPSULE(float x1, float y1, float z1, float x2, float y2, float z2, float radius, int flags, Entity entity, int p9)
	{
		auto retval = SHAPETEST::START_SHAPE_TEST_CAPSULE(x1, y1, z1, x2, y2, z2, radius, flags, entity, p9);
		return retval;
	}

	static int LUA_NATIVE_SHAPETEST_START_SHAPE_TEST_SWEPT_SPHERE(float x1, float y1, float z1, float x2, float y2, float z2, float radius, int flags, Entity entity, Any p9)
	{
		auto retval = SHAPETEST::START_SHAPE_TEST_SWEPT_SPHERE(x1, y1, z1, x2, y2, z2, radius, flags, entity, p9);
		return retval;
	}

	static std::tuple<int, Vector3, Vector3> LUA_NATIVE_SHAPETEST_START_SHAPE_TEST_MOUSE_CURSOR_LOS_PROBE(Vector3 pVec1, Vector3 pVec2, int flag, Entity entity, int flag2)
	{
		std::tuple<int, Vector3, Vector3> return_values;
		std::get<0>(return_values) = SHAPETEST::START_SHAPE_TEST_MOUSE_CURSOR_LOS_PROBE(&pVec1, &pVec2, flag, entity, flag2);
		std::get<1>(return_values) = pVec1;
		std::get<2>(return_values) = pVec2;

		return return_values;
	}

	static std::tuple<int, bool, Vector3, Vector3, Entity> LUA_NATIVE_SHAPETEST_GET_SHAPE_TEST_RESULT(int shapeTestHandle, bool hit, Vector3 endCoords, Vector3 surfaceNormal, Entity entityHit)
	{
		std::tuple<int, bool, Vector3, Vector3, Entity> return_values;
		std::get<0>(return_values) = SHAPETEST::GET_SHAPE_TEST_RESULT(shapeTestHandle, (BOOL*)&hit, &endCoords, &surfaceNormal, &entityHit);
		std::get<1>(return_values) = hit;
		std::get<2>(return_values) = endCoords;
		std::get<3>(return_values) = surfaceNormal;
		std::get<4>(return_values) = entityHit;

		return return_values;
	}

	static std::tuple<int, bool, Vector3, Vector3, Hash, Entity> LUA_NATIVE_SHAPETEST_GET_SHAPE_TEST_RESULT_INCLUDING_MATERIAL(int shapeTestHandle, bool hit, Vector3 endCoords, Vector3 surfaceNormal, Hash materialHash, Entity entityHit)
	{
		std::tuple<int, bool, Vector3, Vector3, Hash, Entity> return_values;
		std::get<0>(return_values) = SHAPETEST::GET_SHAPE_TEST_RESULT_INCLUDING_MATERIAL(shapeTestHandle, (BOOL*)&hit, &endCoords, &surfaceNormal, &materialHash, &entityHit);
		std::get<1>(return_values) = hit;
		std::get<2>(return_values) = endCoords;
		std::get<3>(return_values) = surfaceNormal;
		std::get<4>(return_values) = materialHash;
		std::get<5>(return_values) = entityHit;

		return return_values;
	}

	static void LUA_NATIVE_SHAPETEST_RELEASE_SCRIPT_GUID_FROM_ENTITY(Entity entityHit)
	{
		SHAPETEST::RELEASE_SCRIPT_GUID_FROM_ENTITY(entityHit);
	}

	void init_native_binding_SHAPETEST(sol::state& L)
	{
		auto SHAPETEST = L["SHAPETEST"].get_or_create<sol::table>();
		SHAPETEST.set_function("START_SHAPE_TEST_LOS_PROBE", LUA_NATIVE_SHAPETEST_START_SHAPE_TEST_LOS_PROBE);
		SHAPETEST.set_function("START_EXPENSIVE_SYNCHRONOUS_SHAPE_TEST_LOS_PROBE", LUA_NATIVE_SHAPETEST_START_EXPENSIVE_SYNCHRONOUS_SHAPE_TEST_LOS_PROBE);
		SHAPETEST.set_function("START_SHAPE_TEST_BOUNDING_BOX", LUA_NATIVE_SHAPETEST_START_SHAPE_TEST_BOUNDING_BOX);
		SHAPETEST.set_function("START_SHAPE_TEST_BOX", LUA_NATIVE_SHAPETEST_START_SHAPE_TEST_BOX);
		SHAPETEST.set_function("START_SHAPE_TEST_BOUND", LUA_NATIVE_SHAPETEST_START_SHAPE_TEST_BOUND);
		SHAPETEST.set_function("START_SHAPE_TEST_CAPSULE", LUA_NATIVE_SHAPETEST_START_SHAPE_TEST_CAPSULE);
		SHAPETEST.set_function("START_SHAPE_TEST_SWEPT_SPHERE", LUA_NATIVE_SHAPETEST_START_SHAPE_TEST_SWEPT_SPHERE);
		SHAPETEST.set_function("START_SHAPE_TEST_MOUSE_CURSOR_LOS_PROBE", LUA_NATIVE_SHAPETEST_START_SHAPE_TEST_MOUSE_CURSOR_LOS_PROBE);
		SHAPETEST.set_function("GET_SHAPE_TEST_RESULT", LUA_NATIVE_SHAPETEST_GET_SHAPE_TEST_RESULT);
		SHAPETEST.set_function("GET_SHAPE_TEST_RESULT_INCLUDING_MATERIAL", LUA_NATIVE_SHAPETEST_GET_SHAPE_TEST_RESULT_INCLUDING_MATERIAL);
		SHAPETEST.set_function("RELEASE_SCRIPT_GUID_FROM_ENTITY", LUA_NATIVE_SHAPETEST_RELEASE_SCRIPT_GUID_FROM_ENTITY);
	}
}
