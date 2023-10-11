#include "lua_native_binding.hpp"
#include "natives.hpp"
#include "util/explosion_anti_cheat_bypass.hpp"

namespace lua::native
{
	static FireId LUA_NATIVE_FIRE_START_SCRIPT_FIRE(float X, float Y, float Z, int maxChildren, bool isGasFire)
	{
		auto retval = FIRE::START_SCRIPT_FIRE(X, Y, Z, maxChildren, isGasFire);
		return retval;
	}

	static void LUA_NATIVE_FIRE_REMOVE_SCRIPT_FIRE(FireId fireHandle)
	{
		FIRE::REMOVE_SCRIPT_FIRE(fireHandle);
	}

	static FireId LUA_NATIVE_FIRE_START_ENTITY_FIRE(Entity entity)
	{
		auto retval = FIRE::START_ENTITY_FIRE(entity);
		return retval;
	}

	static void LUA_NATIVE_FIRE_STOP_ENTITY_FIRE(Entity entity)
	{
		FIRE::STOP_ENTITY_FIRE(entity);
	}

	static bool LUA_NATIVE_FIRE_IS_ENTITY_ON_FIRE(Entity entity)
	{
		auto retval = (bool)FIRE::IS_ENTITY_ON_FIRE(entity);
		return retval;
	}

	static int LUA_NATIVE_FIRE_GET_NUMBER_OF_FIRES_IN_RANGE(float x, float y, float z, float radius)
	{
		auto retval = FIRE::GET_NUMBER_OF_FIRES_IN_RANGE(x, y, z, radius);
		return retval;
	}

	static void LUA_NATIVE_FIRE_SET_FLAMMABILITY_MULTIPLIER(float p0)
	{
		FIRE::SET_FLAMMABILITY_MULTIPLIER(p0);
	}

	static void LUA_NATIVE_FIRE_STOP_FIRE_IN_RANGE(float x, float y, float z, float radius)
	{
		FIRE::STOP_FIRE_IN_RANGE(x, y, z, radius);
	}

	static std::tuple<bool, Vector3> LUA_NATIVE_FIRE_GET_CLOSEST_FIRE_POS(Vector3 outPosition, float x, float y, float z)
	{
		std::tuple<bool, Vector3> return_values;
		std::get<0>(return_values) = (bool)FIRE::GET_CLOSEST_FIRE_POS(&outPosition, x, y, z);
		std::get<1>(return_values) = outPosition;

		return return_values;
	}

	static void LUA_NATIVE_FIRE_ADD_EXPLOSION(float x, float y, float z, int explosionType, float damageScale, bool isAudible, bool isInvisible, float cameraShake, bool noDamage)
	{
		FIRE::ADD_EXPLOSION(x, y, z, explosionType, damageScale, isAudible, isInvisible, cameraShake, noDamage);
	}

	static void LUA_NATIVE_FIRE_ADD_OWNED_EXPLOSION(Ped ped, float x, float y, float z, int explosionType, float damageScale, bool isAudible, bool isInvisible, float cameraShake)
	{
		big::explosion_anti_cheat_bypass::apply();

		FIRE::ADD_OWNED_EXPLOSION(ped, x, y, z, explosionType, damageScale, isAudible, isInvisible, cameraShake);

		big::explosion_anti_cheat_bypass::restore();
	}

	static void LUA_NATIVE_FIRE_ADD_EXPLOSION_WITH_USER_VFX(float x, float y, float z, int explosionType, Hash explosionFx, float damageScale, bool isAudible, bool isInvisible, float cameraShake)
	{
		FIRE::ADD_EXPLOSION_WITH_USER_VFX(x, y, z, explosionType, explosionFx, damageScale, isAudible, isInvisible, cameraShake);
	}

	static bool LUA_NATIVE_FIRE_IS_EXPLOSION_IN_AREA(int explosionType, float x1, float y1, float z1, float x2, float y2, float z2)
	{
		auto retval = (bool)FIRE::IS_EXPLOSION_IN_AREA(explosionType, x1, y1, z1, x2, y2, z2);
		return retval;
	}

	static bool LUA_NATIVE_FIRE_IS_EXPLOSION_ACTIVE_IN_AREA(int explosionType, float x1, float y1, float z1, float x2, float y2, float z2)
	{
		auto retval = (bool)FIRE::IS_EXPLOSION_ACTIVE_IN_AREA(explosionType, x1, y1, z1, x2, y2, z2);
		return retval;
	}

	static bool LUA_NATIVE_FIRE_IS_EXPLOSION_IN_SPHERE(int explosionType, float x, float y, float z, float radius)
	{
		auto retval = (bool)FIRE::IS_EXPLOSION_IN_SPHERE(explosionType, x, y, z, radius);
		return retval;
	}

	static Entity LUA_NATIVE_FIRE_GET_OWNER_OF_EXPLOSION_IN_SPHERE(int explosionType, float x, float y, float z, float radius)
	{
		auto retval = FIRE::GET_OWNER_OF_EXPLOSION_IN_SPHERE(explosionType, x, y, z, radius);
		return retval;
	}

	static bool LUA_NATIVE_FIRE_IS_EXPLOSION_IN_ANGLED_AREA(int explosionType, float x1, float y1, float z1, float x2, float y2, float z2, float width)
	{
		auto retval = (bool)FIRE::IS_EXPLOSION_IN_ANGLED_AREA(explosionType, x1, y1, z1, x2, y2, z2, width);
		return retval;
	}

	static Entity LUA_NATIVE_FIRE_GET_OWNER_OF_EXPLOSION_IN_ANGLED_AREA(int explosionType, float x1, float y1, float z1, float x2, float y2, float z2, float radius)
	{
		auto retval = FIRE::GET_OWNER_OF_EXPLOSION_IN_ANGLED_AREA(explosionType, x1, y1, z1, x2, y2, z2, radius);
		return retval;
	}

	void init_native_binding_FIRE(sol::state& L)
	{
		auto FIRE = L["FIRE"].get_or_create<sol::table>();
		FIRE.set_function("START_SCRIPT_FIRE", LUA_NATIVE_FIRE_START_SCRIPT_FIRE);
		FIRE.set_function("REMOVE_SCRIPT_FIRE", LUA_NATIVE_FIRE_REMOVE_SCRIPT_FIRE);
		FIRE.set_function("START_ENTITY_FIRE", LUA_NATIVE_FIRE_START_ENTITY_FIRE);
		FIRE.set_function("STOP_ENTITY_FIRE", LUA_NATIVE_FIRE_STOP_ENTITY_FIRE);
		FIRE.set_function("IS_ENTITY_ON_FIRE", LUA_NATIVE_FIRE_IS_ENTITY_ON_FIRE);
		FIRE.set_function("GET_NUMBER_OF_FIRES_IN_RANGE", LUA_NATIVE_FIRE_GET_NUMBER_OF_FIRES_IN_RANGE);
		FIRE.set_function("SET_FLAMMABILITY_MULTIPLIER", LUA_NATIVE_FIRE_SET_FLAMMABILITY_MULTIPLIER);
		FIRE.set_function("STOP_FIRE_IN_RANGE", LUA_NATIVE_FIRE_STOP_FIRE_IN_RANGE);
		FIRE.set_function("GET_CLOSEST_FIRE_POS", LUA_NATIVE_FIRE_GET_CLOSEST_FIRE_POS);
		FIRE.set_function("ADD_EXPLOSION", LUA_NATIVE_FIRE_ADD_EXPLOSION);
		FIRE.set_function("ADD_OWNED_EXPLOSION", LUA_NATIVE_FIRE_ADD_OWNED_EXPLOSION);
		FIRE.set_function("ADD_EXPLOSION_WITH_USER_VFX", LUA_NATIVE_FIRE_ADD_EXPLOSION_WITH_USER_VFX);
		FIRE.set_function("IS_EXPLOSION_IN_AREA", LUA_NATIVE_FIRE_IS_EXPLOSION_IN_AREA);
		FIRE.set_function("IS_EXPLOSION_ACTIVE_IN_AREA", LUA_NATIVE_FIRE_IS_EXPLOSION_ACTIVE_IN_AREA);
		FIRE.set_function("IS_EXPLOSION_IN_SPHERE", LUA_NATIVE_FIRE_IS_EXPLOSION_IN_SPHERE);
		FIRE.set_function("GET_OWNER_OF_EXPLOSION_IN_SPHERE", LUA_NATIVE_FIRE_GET_OWNER_OF_EXPLOSION_IN_SPHERE);
		FIRE.set_function("IS_EXPLOSION_IN_ANGLED_AREA", LUA_NATIVE_FIRE_IS_EXPLOSION_IN_ANGLED_AREA);
		FIRE.set_function("GET_OWNER_OF_EXPLOSION_IN_ANGLED_AREA", LUA_NATIVE_FIRE_GET_OWNER_OF_EXPLOSION_IN_ANGLED_AREA);
	}
}
