#include "lua_native_binding.hpp"
#include "natives.hpp"

namespace lua::native
{
	static int LUA_NATIVE_PHYSICS_ADD_ROPE(float x, float y, float z, float rotX, float rotY, float rotZ, float length, int ropeType, float maxLength, float minLength, float windingSpeed, bool p11, bool p12, bool rigid, float p14, bool breakWhenShot, uintptr_t unkPtr)
	{
		auto retval = PHYSICS::ADD_ROPE(x, y, z, rotX, rotY, rotZ, length, ropeType, maxLength, minLength, windingSpeed, p11, p12, rigid, p14, breakWhenShot, (Any*)unkPtr);
		return retval;
	}

	static int LUA_NATIVE_PHYSICS_DELETE_ROPE(int ropeId)
	{
		PHYSICS::DELETE_ROPE(&ropeId);
		return ropeId;
	}

	static void LUA_NATIVE_PHYSICS_DELETE_CHILD_ROPE(int ropeId)
	{
		PHYSICS::DELETE_CHILD_ROPE(ropeId);
	}

	static std::tuple<bool, int> LUA_NATIVE_PHYSICS_DOES_ROPE_EXIST(int ropeId)
	{
		std::tuple<bool, int> return_values;
		std::get<0>(return_values) = (bool)PHYSICS::DOES_ROPE_EXIST(&ropeId);
		std::get<1>(return_values) = ropeId;

		return return_values;
	}

	static int LUA_NATIVE_PHYSICS_ROPE_DRAW_ENABLED(int ropeId, bool p1)
	{
		PHYSICS::ROPE_DRAW_ENABLED(&ropeId, p1);
		return ropeId;
	}

	static int LUA_NATIVE_PHYSICS_ROPE_DRAW_SHADOW_ENABLED(int ropeId, bool toggle)
	{
		PHYSICS::ROPE_DRAW_SHADOW_ENABLED(&ropeId, toggle);
		return ropeId;
	}

	static void LUA_NATIVE_PHYSICS_LOAD_ROPE_DATA(int ropeId, sol::stack_object rope_preset)
	{
		PHYSICS::LOAD_ROPE_DATA(ropeId, rope_preset.is<const char*>() ? rope_preset.as<const char*>() : nullptr);
	}

	static void LUA_NATIVE_PHYSICS_PIN_ROPE_VERTEX(int ropeId, int vertex, float x, float y, float z)
	{
		PHYSICS::PIN_ROPE_VERTEX(ropeId, vertex, x, y, z);
	}

	static void LUA_NATIVE_PHYSICS_UNPIN_ROPE_VERTEX(int ropeId, int vertex)
	{
		PHYSICS::UNPIN_ROPE_VERTEX(ropeId, vertex);
	}

	static int LUA_NATIVE_PHYSICS_GET_ROPE_VERTEX_COUNT(int ropeId)
	{
		auto retval = PHYSICS::GET_ROPE_VERTEX_COUNT(ropeId);
		return retval;
	}

	static void LUA_NATIVE_PHYSICS_ATTACH_ENTITIES_TO_ROPE(int ropeId, Entity ent1, Entity ent2, float ent1_x, float ent1_y, float ent1_z, float ent2_x, float ent2_y, float ent2_z, float length, bool p10, bool p11, uintptr_t p12, uintptr_t p13)
	{
		PHYSICS::ATTACH_ENTITIES_TO_ROPE(ropeId, ent1, ent2, ent1_x, ent1_y, ent1_z, ent2_x, ent2_y, ent2_z, length, p10, p11, (Any*)p12, (Any*)p13);
	}

	static void LUA_NATIVE_PHYSICS_ATTACH_ROPE_TO_ENTITY(int ropeId, Entity entity, float x, float y, float z, bool p5)
	{
		PHYSICS::ATTACH_ROPE_TO_ENTITY(ropeId, entity, x, y, z, p5);
	}

	static void LUA_NATIVE_PHYSICS_DETACH_ROPE_FROM_ENTITY(int ropeId, Entity entity)
	{
		PHYSICS::DETACH_ROPE_FROM_ENTITY(ropeId, entity);
	}

	static void LUA_NATIVE_PHYSICS_ROPE_SET_UPDATE_PINVERTS(int ropeId)
	{
		PHYSICS::ROPE_SET_UPDATE_PINVERTS(ropeId);
	}

	static void LUA_NATIVE_PHYSICS_ROPE_SET_UPDATE_ORDER(int ropeId, Any p1)
	{
		PHYSICS::ROPE_SET_UPDATE_ORDER(ropeId, p1);
	}

	static void LUA_NATIVE_PHYSICS_ROPE_SET_SMOOTH_REELIN(int ropeId, bool p1)
	{
		PHYSICS::ROPE_SET_SMOOTH_REELIN(ropeId, p1);
	}

	static std::tuple<bool, int> LUA_NATIVE_PHYSICS_IS_ROPE_ATTACHED_AT_BOTH_ENDS(int ropeId)
	{
		std::tuple<bool, int> return_values;
		std::get<0>(return_values) = (bool)PHYSICS::IS_ROPE_ATTACHED_AT_BOTH_ENDS(&ropeId);
		std::get<1>(return_values) = ropeId;

		return return_values;
	}

	static Vector3 LUA_NATIVE_PHYSICS_GET_ROPE_LAST_VERTEX_COORD(int ropeId)
	{
		auto retval = PHYSICS::GET_ROPE_LAST_VERTEX_COORD(ropeId);
		return retval;
	}

	static Vector3 LUA_NATIVE_PHYSICS_GET_ROPE_VERTEX_COORD(int ropeId, int vertex)
	{
		auto retval = PHYSICS::GET_ROPE_VERTEX_COORD(ropeId, vertex);
		return retval;
	}

	static void LUA_NATIVE_PHYSICS_START_ROPE_WINDING(int ropeId)
	{
		PHYSICS::START_ROPE_WINDING(ropeId);
	}

	static void LUA_NATIVE_PHYSICS_STOP_ROPE_WINDING(int ropeId)
	{
		PHYSICS::STOP_ROPE_WINDING(ropeId);
	}

	static void LUA_NATIVE_PHYSICS_START_ROPE_UNWINDING_FRONT(int ropeId)
	{
		PHYSICS::START_ROPE_UNWINDING_FRONT(ropeId);
	}

	static void LUA_NATIVE_PHYSICS_STOP_ROPE_UNWINDING_FRONT(int ropeId)
	{
		PHYSICS::STOP_ROPE_UNWINDING_FRONT(ropeId);
	}

	static void LUA_NATIVE_PHYSICS_ROPE_CONVERT_TO_SIMPLE(int ropeId)
	{
		PHYSICS::ROPE_CONVERT_TO_SIMPLE(ropeId);
	}

	static void LUA_NATIVE_PHYSICS_ROPE_LOAD_TEXTURES()
	{
		PHYSICS::ROPE_LOAD_TEXTURES();
	}

	static bool LUA_NATIVE_PHYSICS_ROPE_ARE_TEXTURES_LOADED()
	{
		auto retval = (bool)PHYSICS::ROPE_ARE_TEXTURES_LOADED();
		return retval;
	}

	static void LUA_NATIVE_PHYSICS_ROPE_UNLOAD_TEXTURES()
	{
		PHYSICS::ROPE_UNLOAD_TEXTURES();
	}

	static bool LUA_NATIVE_PHYSICS_DOES_SCRIPT_OWN_ROPE(int ropeId)
	{
		auto retval = (bool)PHYSICS::DOES_SCRIPT_OWN_ROPE(ropeId);
		return retval;
	}

	static void LUA_NATIVE_PHYSICS_ROPE_ATTACH_VIRTUAL_BOUND_GEOM(int ropeId, int p1, float p2, float p3, float p4, float p5, float p6, float p7, float p8, float p9, float p10, float p11, float p12, float p13)
	{
		PHYSICS::ROPE_ATTACH_VIRTUAL_BOUND_GEOM(ropeId, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13);
	}

	static void LUA_NATIVE_PHYSICS_ROPE_CHANGE_SCRIPT_OWNER(Any p0, bool p1, bool p2)
	{
		PHYSICS::ROPE_CHANGE_SCRIPT_OWNER(p0, p1, p2);
	}

	static void LUA_NATIVE_PHYSICS_ROPE_SET_REFFRAMEVELOCITY_COLLIDERORDER(int ropeId, int p1)
	{
		PHYSICS::ROPE_SET_REFFRAMEVELOCITY_COLLIDERORDER(ropeId, p1);
	}

	static float LUA_NATIVE_PHYSICS_ROPE_GET_DISTANCE_BETWEEN_ENDS(int ropeId)
	{
		auto retval = PHYSICS::ROPE_GET_DISTANCE_BETWEEN_ENDS(ropeId);
		return retval;
	}

	static void LUA_NATIVE_PHYSICS_ROPE_FORCE_LENGTH(int ropeId, float length)
	{
		PHYSICS::ROPE_FORCE_LENGTH(ropeId, length);
	}

	static void LUA_NATIVE_PHYSICS_ROPE_RESET_LENGTH(int ropeId, float length)
	{
		PHYSICS::ROPE_RESET_LENGTH(ropeId, length);
	}

	static void LUA_NATIVE_PHYSICS_APPLY_IMPULSE_TO_CLOTH(float posX, float posY, float posZ, float vecX, float vecY, float vecZ, float impulse)
	{
		PHYSICS::APPLY_IMPULSE_TO_CLOTH(posX, posY, posZ, vecX, vecY, vecZ, impulse);
	}

	static void LUA_NATIVE_PHYSICS_SET_DAMPING(Entity entity, int vertex, float value)
	{
		PHYSICS::SET_DAMPING(entity, vertex, value);
	}

	static void LUA_NATIVE_PHYSICS_ACTIVATE_PHYSICS(Entity entity)
	{
		PHYSICS::ACTIVATE_PHYSICS(entity);
	}

	static void LUA_NATIVE_PHYSICS_SET_CGOFFSET(Entity entity, float x, float y, float z)
	{
		PHYSICS::SET_CGOFFSET(entity, x, y, z);
	}

	static Vector3 LUA_NATIVE_PHYSICS_GET_CGOFFSET(Entity entity)
	{
		auto retval = PHYSICS::GET_CGOFFSET(entity);
		return retval;
	}

	static void LUA_NATIVE_PHYSICS_SET_CG_AT_BOUNDCENTER(Entity entity)
	{
		PHYSICS::SET_CG_AT_BOUNDCENTER(entity);
	}

	static void LUA_NATIVE_PHYSICS_BREAK_ENTITY_GLASS(Entity entity, float p1, float p2, float p3, float p4, float p5, float p6, float p7, float p8, Any p9, bool p10)
	{
		PHYSICS::BREAK_ENTITY_GLASS(entity, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10);
	}

	static bool LUA_NATIVE_PHYSICS_GET_IS_ENTITY_A_FRAG(Object object)
	{
		auto retval = (bool)PHYSICS::GET_IS_ENTITY_A_FRAG(object);
		return retval;
	}

	static void LUA_NATIVE_PHYSICS_SET_DISABLE_BREAKING(Object object, bool toggle)
	{
		PHYSICS::SET_DISABLE_BREAKING(object, toggle);
	}

	static void LUA_NATIVE_PHYSICS_RESET_DISABLE_BREAKING(Object object)
	{
		PHYSICS::RESET_DISABLE_BREAKING(object);
	}

	static void LUA_NATIVE_PHYSICS_SET_DISABLE_FRAG_DAMAGE(Object object, bool toggle)
	{
		PHYSICS::SET_DISABLE_FRAG_DAMAGE(object, toggle);
	}

	static void LUA_NATIVE_PHYSICS_SET_USE_KINEMATIC_PHYSICS(Entity entity, bool toggle)
	{
		PHYSICS::SET_USE_KINEMATIC_PHYSICS(entity, toggle);
	}

	static void LUA_NATIVE_PHYSICS_SET_IN_STUNT_MODE(bool p0)
	{
		PHYSICS::SET_IN_STUNT_MODE(p0);
	}

	static void LUA_NATIVE_PHYSICS_SET_IN_ARENA_MODE(bool toggle)
	{
		PHYSICS::SET_IN_ARENA_MODE(toggle);
	}

	void init_native_binding_PHYSICS(sol::state& L)
	{
		auto PHYSICS = L["PHYSICS"].get_or_create<sol::table>();
		PHYSICS.set_function("ADD_ROPE", LUA_NATIVE_PHYSICS_ADD_ROPE);
		PHYSICS.set_function("DELETE_ROPE", LUA_NATIVE_PHYSICS_DELETE_ROPE);
		PHYSICS.set_function("DELETE_CHILD_ROPE", LUA_NATIVE_PHYSICS_DELETE_CHILD_ROPE);
		PHYSICS.set_function("DOES_ROPE_EXIST", LUA_NATIVE_PHYSICS_DOES_ROPE_EXIST);
		PHYSICS.set_function("ROPE_DRAW_ENABLED", LUA_NATIVE_PHYSICS_ROPE_DRAW_ENABLED);
		PHYSICS.set_function("ROPE_DRAW_SHADOW_ENABLED", LUA_NATIVE_PHYSICS_ROPE_DRAW_SHADOW_ENABLED);
		PHYSICS.set_function("LOAD_ROPE_DATA", LUA_NATIVE_PHYSICS_LOAD_ROPE_DATA);
		PHYSICS.set_function("PIN_ROPE_VERTEX", LUA_NATIVE_PHYSICS_PIN_ROPE_VERTEX);
		PHYSICS.set_function("UNPIN_ROPE_VERTEX", LUA_NATIVE_PHYSICS_UNPIN_ROPE_VERTEX);
		PHYSICS.set_function("GET_ROPE_VERTEX_COUNT", LUA_NATIVE_PHYSICS_GET_ROPE_VERTEX_COUNT);
		PHYSICS.set_function("ATTACH_ENTITIES_TO_ROPE", LUA_NATIVE_PHYSICS_ATTACH_ENTITIES_TO_ROPE);
		PHYSICS.set_function("ATTACH_ROPE_TO_ENTITY", LUA_NATIVE_PHYSICS_ATTACH_ROPE_TO_ENTITY);
		PHYSICS.set_function("DETACH_ROPE_FROM_ENTITY", LUA_NATIVE_PHYSICS_DETACH_ROPE_FROM_ENTITY);
		PHYSICS.set_function("ROPE_SET_UPDATE_PINVERTS", LUA_NATIVE_PHYSICS_ROPE_SET_UPDATE_PINVERTS);
		PHYSICS.set_function("ROPE_SET_UPDATE_ORDER", LUA_NATIVE_PHYSICS_ROPE_SET_UPDATE_ORDER);
		PHYSICS.set_function("ROPE_SET_SMOOTH_REELIN", LUA_NATIVE_PHYSICS_ROPE_SET_SMOOTH_REELIN);
		PHYSICS.set_function("IS_ROPE_ATTACHED_AT_BOTH_ENDS", LUA_NATIVE_PHYSICS_IS_ROPE_ATTACHED_AT_BOTH_ENDS);
		PHYSICS.set_function("GET_ROPE_LAST_VERTEX_COORD", LUA_NATIVE_PHYSICS_GET_ROPE_LAST_VERTEX_COORD);
		PHYSICS.set_function("GET_ROPE_VERTEX_COORD", LUA_NATIVE_PHYSICS_GET_ROPE_VERTEX_COORD);
		PHYSICS.set_function("START_ROPE_WINDING", LUA_NATIVE_PHYSICS_START_ROPE_WINDING);
		PHYSICS.set_function("STOP_ROPE_WINDING", LUA_NATIVE_PHYSICS_STOP_ROPE_WINDING);
		PHYSICS.set_function("START_ROPE_UNWINDING_FRONT", LUA_NATIVE_PHYSICS_START_ROPE_UNWINDING_FRONT);
		PHYSICS.set_function("STOP_ROPE_UNWINDING_FRONT", LUA_NATIVE_PHYSICS_STOP_ROPE_UNWINDING_FRONT);
		PHYSICS.set_function("ROPE_CONVERT_TO_SIMPLE", LUA_NATIVE_PHYSICS_ROPE_CONVERT_TO_SIMPLE);
		PHYSICS.set_function("ROPE_LOAD_TEXTURES", LUA_NATIVE_PHYSICS_ROPE_LOAD_TEXTURES);
		PHYSICS.set_function("ROPE_ARE_TEXTURES_LOADED", LUA_NATIVE_PHYSICS_ROPE_ARE_TEXTURES_LOADED);
		PHYSICS.set_function("ROPE_UNLOAD_TEXTURES", LUA_NATIVE_PHYSICS_ROPE_UNLOAD_TEXTURES);
		PHYSICS.set_function("DOES_SCRIPT_OWN_ROPE", LUA_NATIVE_PHYSICS_DOES_SCRIPT_OWN_ROPE);
		PHYSICS.set_function("ROPE_ATTACH_VIRTUAL_BOUND_GEOM", LUA_NATIVE_PHYSICS_ROPE_ATTACH_VIRTUAL_BOUND_GEOM);
		PHYSICS.set_function("ROPE_CHANGE_SCRIPT_OWNER", LUA_NATIVE_PHYSICS_ROPE_CHANGE_SCRIPT_OWNER);
		PHYSICS.set_function("ROPE_SET_REFFRAMEVELOCITY_COLLIDERORDER", LUA_NATIVE_PHYSICS_ROPE_SET_REFFRAMEVELOCITY_COLLIDERORDER);
		PHYSICS.set_function("ROPE_GET_DISTANCE_BETWEEN_ENDS", LUA_NATIVE_PHYSICS_ROPE_GET_DISTANCE_BETWEEN_ENDS);
		PHYSICS.set_function("ROPE_FORCE_LENGTH", LUA_NATIVE_PHYSICS_ROPE_FORCE_LENGTH);
		PHYSICS.set_function("ROPE_RESET_LENGTH", LUA_NATIVE_PHYSICS_ROPE_RESET_LENGTH);
		PHYSICS.set_function("APPLY_IMPULSE_TO_CLOTH", LUA_NATIVE_PHYSICS_APPLY_IMPULSE_TO_CLOTH);
		PHYSICS.set_function("SET_DAMPING", LUA_NATIVE_PHYSICS_SET_DAMPING);
		PHYSICS.set_function("ACTIVATE_PHYSICS", LUA_NATIVE_PHYSICS_ACTIVATE_PHYSICS);
		PHYSICS.set_function("SET_CGOFFSET", LUA_NATIVE_PHYSICS_SET_CGOFFSET);
		PHYSICS.set_function("GET_CGOFFSET", LUA_NATIVE_PHYSICS_GET_CGOFFSET);
		PHYSICS.set_function("SET_CG_AT_BOUNDCENTER", LUA_NATIVE_PHYSICS_SET_CG_AT_BOUNDCENTER);
		PHYSICS.set_function("BREAK_ENTITY_GLASS", LUA_NATIVE_PHYSICS_BREAK_ENTITY_GLASS);
		PHYSICS.set_function("GET_IS_ENTITY_A_FRAG", LUA_NATIVE_PHYSICS_GET_IS_ENTITY_A_FRAG);
		PHYSICS.set_function("SET_DISABLE_BREAKING", LUA_NATIVE_PHYSICS_SET_DISABLE_BREAKING);
		PHYSICS.set_function("RESET_DISABLE_BREAKING", LUA_NATIVE_PHYSICS_RESET_DISABLE_BREAKING);
		PHYSICS.set_function("SET_DISABLE_FRAG_DAMAGE", LUA_NATIVE_PHYSICS_SET_DISABLE_FRAG_DAMAGE);
		PHYSICS.set_function("SET_USE_KINEMATIC_PHYSICS", LUA_NATIVE_PHYSICS_SET_USE_KINEMATIC_PHYSICS);
		PHYSICS.set_function("SET_IN_STUNT_MODE", LUA_NATIVE_PHYSICS_SET_IN_STUNT_MODE);
		PHYSICS.set_function("SET_IN_ARENA_MODE", LUA_NATIVE_PHYSICS_SET_IN_ARENA_MODE);
	}
}
