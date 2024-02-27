#include "lua_native_binding.hpp"
#include "natives.hpp"

namespace lua::native
{
	static int LUA_NATIVE_FILES_GET_NUM_TATTOO_SHOP_DLC_ITEMS(int character)
	{
		auto retval = FILES::GET_NUM_TATTOO_SHOP_DLC_ITEMS(character);
		return retval;
	}

	static bool LUA_NATIVE_FILES_GET_TATTOO_SHOP_DLC_ITEM_DATA(int characterType, int decorationIndex, uintptr_t outComponent)
	{
		auto retval = (bool)FILES::GET_TATTOO_SHOP_DLC_ITEM_DATA(characterType, decorationIndex, (Any*)outComponent);
		return retval;
	}

	static int LUA_NATIVE_FILES_GET_TATTOO_SHOP_DLC_ITEM_INDEX(Hash overlayHash, Any p1, int character)
	{
		auto retval = FILES::GET_TATTOO_SHOP_DLC_ITEM_INDEX(overlayHash, p1, character);
		return retval;
	}

	static void LUA_NATIVE_FILES_INIT_SHOP_PED_COMPONENT(uintptr_t outComponent)
	{
		FILES::INIT_SHOP_PED_COMPONENT((Any*)outComponent);
	}

	static void LUA_NATIVE_FILES_INIT_SHOP_PED_PROP(uintptr_t outProp)
	{
		FILES::INIT_SHOP_PED_PROP((Any*)outProp);
	}

	static int LUA_NATIVE_FILES_SETUP_SHOP_PED_APPAREL_QUERY(int p0, int p1, int p2, int p3)
	{
		auto retval = FILES::SETUP_SHOP_PED_APPAREL_QUERY(p0, p1, p2, p3);
		return retval;
	}

	static int LUA_NATIVE_FILES_SETUP_SHOP_PED_APPAREL_QUERY_TU(int character, int p1, int p2, bool p3, int p4, int componentId)
	{
		auto retval = FILES::SETUP_SHOP_PED_APPAREL_QUERY_TU(character, p1, p2, p3, p4, componentId);
		return retval;
	}

	static void LUA_NATIVE_FILES_GET_SHOP_PED_QUERY_COMPONENT(int componentId, uintptr_t outComponent)
	{
		FILES::GET_SHOP_PED_QUERY_COMPONENT(componentId, (Any*)outComponent);
	}

	static int LUA_NATIVE_FILES_GET_SHOP_PED_QUERY_COMPONENT_INDEX(Hash componentHash)
	{
		auto retval = FILES::GET_SHOP_PED_QUERY_COMPONENT_INDEX(componentHash);
		return retval;
	}

	static void LUA_NATIVE_FILES_GET_SHOP_PED_COMPONENT(Hash componentHash, uintptr_t outComponent)
	{
		FILES::GET_SHOP_PED_COMPONENT(componentHash, (Any*)outComponent);
	}

	static void LUA_NATIVE_FILES_GET_SHOP_PED_QUERY_PROP(int componentId, uintptr_t outProp)
	{
		FILES::GET_SHOP_PED_QUERY_PROP(componentId, (Any*)outProp);
	}

	static int LUA_NATIVE_FILES_GET_SHOP_PED_QUERY_PROP_INDEX(Hash componentHash)
	{
		auto retval = FILES::GET_SHOP_PED_QUERY_PROP_INDEX(componentHash);
		return retval;
	}

	static void LUA_NATIVE_FILES_GET_SHOP_PED_PROP(Hash componentHash, uintptr_t outProp)
	{
		FILES::GET_SHOP_PED_PROP(componentHash, (Any*)outProp);
	}

	static Hash LUA_NATIVE_FILES_GET_HASH_NAME_FOR_COMPONENT(Entity entity, int componentId, int drawableVariant, int textureVariant)
	{
		auto retval = FILES::GET_HASH_NAME_FOR_COMPONENT(entity, componentId, drawableVariant, textureVariant);
		return retval;
	}

	static Hash LUA_NATIVE_FILES_GET_HASH_NAME_FOR_PROP(Entity entity, int componentId, int propIndex, int propTextureIndex)
	{
		auto retval = FILES::GET_HASH_NAME_FOR_PROP(entity, componentId, propIndex, propTextureIndex);
		return retval;
	}

	static int LUA_NATIVE_FILES_GET_SHOP_PED_APPAREL_VARIANT_COMPONENT_COUNT(Hash componentHash)
	{
		auto retval = FILES::GET_SHOP_PED_APPAREL_VARIANT_COMPONENT_COUNT(componentHash);
		return retval;
	}

	static int LUA_NATIVE_FILES_GET_SHOP_PED_APPAREL_VARIANT_PROP_COUNT(Hash propHash)
	{
		auto retval = FILES::GET_SHOP_PED_APPAREL_VARIANT_PROP_COUNT(propHash);
		return retval;
	}

	static std::tuple<Hash, int, int> LUA_NATIVE_FILES_GET_VARIANT_COMPONENT(Hash componentHash, int variantComponentIndex, Hash nameHash, int enumValue, int componentType)
	{
		std::tuple<Hash, int, int> return_values;
		FILES::GET_VARIANT_COMPONENT(componentHash, variantComponentIndex, &nameHash, &enumValue, &componentType);
		std::get<0>(return_values) = nameHash;
		std::get<1>(return_values) = enumValue;
		std::get<2>(return_values) = componentType;

		return return_values;
	}

	static std::tuple<Hash, int, int> LUA_NATIVE_FILES_GET_VARIANT_PROP(Hash componentHash, int variantPropIndex, Hash nameHash, int enumValue, int anchorPoint)
	{
		std::tuple<Hash, int, int> return_values;
		FILES::GET_VARIANT_PROP(componentHash, variantPropIndex, &nameHash, &enumValue, &anchorPoint);
		std::get<0>(return_values) = nameHash;
		std::get<1>(return_values) = enumValue;
		std::get<2>(return_values) = anchorPoint;

		return return_values;
	}

	static int LUA_NATIVE_FILES_GET_SHOP_PED_APPAREL_FORCED_COMPONENT_COUNT(Hash componentHash)
	{
		auto retval = FILES::GET_SHOP_PED_APPAREL_FORCED_COMPONENT_COUNT(componentHash);
		return retval;
	}

	static int LUA_NATIVE_FILES_GET_SHOP_PED_APPAREL_FORCED_PROP_COUNT(Hash componentHash)
	{
		auto retval = FILES::GET_SHOP_PED_APPAREL_FORCED_PROP_COUNT(componentHash);
		return retval;
	}

	static std::tuple<Hash, int, int> LUA_NATIVE_FILES_GET_FORCED_COMPONENT(Hash componentHash, int forcedComponentIndex, Hash nameHash, int enumValue, int componentType)
	{
		std::tuple<Hash, int, int> return_values;
		FILES::GET_FORCED_COMPONENT(componentHash, forcedComponentIndex, &nameHash, &enumValue, &componentType);
		std::get<0>(return_values) = nameHash;
		std::get<1>(return_values) = enumValue;
		std::get<2>(return_values) = componentType;

		return return_values;
	}

	static std::tuple<Hash, int, int> LUA_NATIVE_FILES_GET_FORCED_PROP(Hash componentHash, int forcedPropIndex, Hash nameHash, int enumValue, int anchorPoint)
	{
		std::tuple<Hash, int, int> return_values;
		FILES::GET_FORCED_PROP(componentHash, forcedPropIndex, &nameHash, &enumValue, &anchorPoint);
		std::get<0>(return_values) = nameHash;
		std::get<1>(return_values) = enumValue;
		std::get<2>(return_values) = anchorPoint;

		return return_values;
	}

	static bool LUA_NATIVE_FILES_DOES_SHOP_PED_APPAREL_HAVE_RESTRICTION_TAG(Hash componentHash, Hash restrictionTagHash, int componentId)
	{
		auto retval = (bool)FILES::DOES_SHOP_PED_APPAREL_HAVE_RESTRICTION_TAG(componentHash, restrictionTagHash, componentId);
		return retval;
	}

	static bool LUA_NATIVE_FILES_DOES_CURRENT_PED_COMPONENT_HAVE_RESTRICTION_TAG(Ped ped, int componentId, Hash restrictionTagHash)
	{
		auto retval = (bool)FILES::DOES_CURRENT_PED_COMPONENT_HAVE_RESTRICTION_TAG(ped, componentId, restrictionTagHash);
		return retval;
	}

	static bool LUA_NATIVE_FILES_DOES_CURRENT_PED_PROP_HAVE_RESTRICTION_TAG(Ped ped, int componentId, Hash restrictionTagHash)
	{
		auto retval = (bool)FILES::DOES_CURRENT_PED_PROP_HAVE_RESTRICTION_TAG(ped, componentId, restrictionTagHash);
		return retval;
	}

	static int LUA_NATIVE_FILES_SETUP_SHOP_PED_OUTFIT_QUERY(int character, bool p1)
	{
		auto retval = FILES::SETUP_SHOP_PED_OUTFIT_QUERY(character, p1);
		return retval;
	}

	static void LUA_NATIVE_FILES_GET_SHOP_PED_QUERY_OUTFIT(int outfitIndex, uintptr_t outfit)
	{
		FILES::GET_SHOP_PED_QUERY_OUTFIT(outfitIndex, (Any*)outfit);
	}

	static void LUA_NATIVE_FILES_GET_SHOP_PED_OUTFIT(Any p0, uintptr_t p1)
	{
		FILES::GET_SHOP_PED_OUTFIT(p0, (Any*)p1);
	}

	static int LUA_NATIVE_FILES_GET_SHOP_PED_OUTFIT_LOCATE(Any p0)
	{
		auto retval = FILES::GET_SHOP_PED_OUTFIT_LOCATE(p0);
		return retval;
	}

	static bool LUA_NATIVE_FILES_GET_SHOP_PED_OUTFIT_PROP_VARIANT(Hash outfitHash, int variantIndex, uintptr_t outPropVariant)
	{
		auto retval = (bool)FILES::GET_SHOP_PED_OUTFIT_PROP_VARIANT(outfitHash, variantIndex, (Any*)outPropVariant);
		return retval;
	}

	static bool LUA_NATIVE_FILES_GET_SHOP_PED_OUTFIT_COMPONENT_VARIANT(Hash outfitHash, int variantIndex, uintptr_t outComponentVariant)
	{
		auto retval = (bool)FILES::GET_SHOP_PED_OUTFIT_COMPONENT_VARIANT(outfitHash, variantIndex, (Any*)outComponentVariant);
		return retval;
	}

	static int LUA_NATIVE_FILES_GET_NUM_DLC_VEHICLES()
	{
		auto retval = FILES::GET_NUM_DLC_VEHICLES();
		return retval;
	}

	static Hash LUA_NATIVE_FILES_GET_DLC_VEHICLE_MODEL(int dlcVehicleIndex)
	{
		auto retval = FILES::GET_DLC_VEHICLE_MODEL(dlcVehicleIndex);
		return retval;
	}

	static bool LUA_NATIVE_FILES_GET_DLC_VEHICLE_DATA(int dlcVehicleIndex, uintptr_t outData)
	{
		auto retval = (bool)FILES::GET_DLC_VEHICLE_DATA(dlcVehicleIndex, (Any*)outData);
		return retval;
	}

	static int LUA_NATIVE_FILES_GET_DLC_VEHICLE_FLAGS(int dlcVehicleIndex)
	{
		auto retval = FILES::GET_DLC_VEHICLE_FLAGS(dlcVehicleIndex);
		return retval;
	}

	static int LUA_NATIVE_FILES_GET_NUM_DLC_WEAPONS()
	{
		auto retval = FILES::GET_NUM_DLC_WEAPONS();
		return retval;
	}

	static int LUA_NATIVE_FILES_GET_NUM_DLC_WEAPONS_SP()
	{
		auto retval = FILES::GET_NUM_DLC_WEAPONS_SP();
		return retval;
	}

	static bool LUA_NATIVE_FILES_GET_DLC_WEAPON_DATA(int dlcWeaponIndex, uintptr_t outData)
	{
		auto retval = (bool)FILES::GET_DLC_WEAPON_DATA(dlcWeaponIndex, (Any*)outData);
		return retval;
	}

	static bool LUA_NATIVE_FILES_GET_DLC_WEAPON_DATA_SP(int dlcWeaponIndex, uintptr_t outData)
	{
		auto retval = (bool)FILES::GET_DLC_WEAPON_DATA_SP(dlcWeaponIndex, (Any*)outData);
		return retval;
	}

	static int LUA_NATIVE_FILES_GET_NUM_DLC_WEAPON_COMPONENTS(int dlcWeaponIndex)
	{
		auto retval = FILES::GET_NUM_DLC_WEAPON_COMPONENTS(dlcWeaponIndex);
		return retval;
	}

	static int LUA_NATIVE_FILES_GET_NUM_DLC_WEAPON_COMPONENTS_SP(int dlcWeaponIndex)
	{
		auto retval = FILES::GET_NUM_DLC_WEAPON_COMPONENTS_SP(dlcWeaponIndex);
		return retval;
	}

	static bool LUA_NATIVE_FILES_GET_DLC_WEAPON_COMPONENT_DATA(int dlcWeaponIndex, int dlcWeapCompIndex, uintptr_t ComponentDataPtr)
	{
		auto retval = (bool)FILES::GET_DLC_WEAPON_COMPONENT_DATA(dlcWeaponIndex, dlcWeapCompIndex, (Any*)ComponentDataPtr);
		return retval;
	}

	static bool LUA_NATIVE_FILES_GET_DLC_WEAPON_COMPONENT_DATA_SP(int dlcWeaponIndex, int dlcWeapCompIndex, uintptr_t ComponentDataPtr)
	{
		auto retval = (bool)FILES::GET_DLC_WEAPON_COMPONENT_DATA_SP(dlcWeaponIndex, dlcWeapCompIndex, (Any*)ComponentDataPtr);
		return retval;
	}

	static bool LUA_NATIVE_FILES_IS_CONTENT_ITEM_LOCKED(Hash itemHash)
	{
		auto retval = (bool)FILES::IS_CONTENT_ITEM_LOCKED(itemHash);
		return retval;
	}

	static bool LUA_NATIVE_FILES_IS_DLC_VEHICLE_MOD(Hash hash)
	{
		auto retval = (bool)FILES::IS_DLC_VEHICLE_MOD(hash);
		return retval;
	}

	static Hash LUA_NATIVE_FILES_GET_DLC_VEHICLE_MOD_LOCK_HASH(Hash hash)
	{
		auto retval = FILES::GET_DLC_VEHICLE_MOD_LOCK_HASH(hash);
		return retval;
	}

	static void LUA_NATIVE_FILES_EXECUTE_CONTENT_CHANGESET_GROUP_FOR_ALL(Hash hash)
	{
		FILES::EXECUTE_CONTENT_CHANGESET_GROUP_FOR_ALL(hash);
	}

	static void LUA_NATIVE_FILES_REVERT_CONTENT_CHANGESET_GROUP_FOR_ALL(Hash hash)
	{
		FILES::REVERT_CONTENT_CHANGESET_GROUP_FOR_ALL(hash);
	}

	void init_native_binding_FILES(sol::state& L)
	{
		auto FILES = L["FILES"].get_or_create<sol::table>();
		FILES.set_function("GET_NUM_TATTOO_SHOP_DLC_ITEMS", LUA_NATIVE_FILES_GET_NUM_TATTOO_SHOP_DLC_ITEMS);
		FILES.set_function("GET_TATTOO_SHOP_DLC_ITEM_DATA", LUA_NATIVE_FILES_GET_TATTOO_SHOP_DLC_ITEM_DATA);
		FILES.set_function("GET_TATTOO_SHOP_DLC_ITEM_INDEX", LUA_NATIVE_FILES_GET_TATTOO_SHOP_DLC_ITEM_INDEX);
		FILES.set_function("INIT_SHOP_PED_COMPONENT", LUA_NATIVE_FILES_INIT_SHOP_PED_COMPONENT);
		FILES.set_function("INIT_SHOP_PED_PROP", LUA_NATIVE_FILES_INIT_SHOP_PED_PROP);
		FILES.set_function("SETUP_SHOP_PED_APPAREL_QUERY", LUA_NATIVE_FILES_SETUP_SHOP_PED_APPAREL_QUERY);
		FILES.set_function("SETUP_SHOP_PED_APPAREL_QUERY_TU", LUA_NATIVE_FILES_SETUP_SHOP_PED_APPAREL_QUERY_TU);
		FILES.set_function("GET_SHOP_PED_QUERY_COMPONENT", LUA_NATIVE_FILES_GET_SHOP_PED_QUERY_COMPONENT);
		FILES.set_function("GET_SHOP_PED_QUERY_COMPONENT_INDEX", LUA_NATIVE_FILES_GET_SHOP_PED_QUERY_COMPONENT_INDEX);
		FILES.set_function("GET_SHOP_PED_COMPONENT", LUA_NATIVE_FILES_GET_SHOP_PED_COMPONENT);
		FILES.set_function("GET_SHOP_PED_QUERY_PROP", LUA_NATIVE_FILES_GET_SHOP_PED_QUERY_PROP);
		FILES.set_function("GET_SHOP_PED_QUERY_PROP_INDEX", LUA_NATIVE_FILES_GET_SHOP_PED_QUERY_PROP_INDEX);
		FILES.set_function("GET_SHOP_PED_PROP", LUA_NATIVE_FILES_GET_SHOP_PED_PROP);
		FILES.set_function("GET_HASH_NAME_FOR_COMPONENT", LUA_NATIVE_FILES_GET_HASH_NAME_FOR_COMPONENT);
		FILES.set_function("GET_HASH_NAME_FOR_PROP", LUA_NATIVE_FILES_GET_HASH_NAME_FOR_PROP);
		FILES.set_function("GET_SHOP_PED_APPAREL_VARIANT_COMPONENT_COUNT", LUA_NATIVE_FILES_GET_SHOP_PED_APPAREL_VARIANT_COMPONENT_COUNT);
		FILES.set_function("GET_SHOP_PED_APPAREL_VARIANT_PROP_COUNT", LUA_NATIVE_FILES_GET_SHOP_PED_APPAREL_VARIANT_PROP_COUNT);
		FILES.set_function("GET_VARIANT_COMPONENT", LUA_NATIVE_FILES_GET_VARIANT_COMPONENT);
		FILES.set_function("GET_VARIANT_PROP", LUA_NATIVE_FILES_GET_VARIANT_PROP);
		FILES.set_function("GET_SHOP_PED_APPAREL_FORCED_COMPONENT_COUNT", LUA_NATIVE_FILES_GET_SHOP_PED_APPAREL_FORCED_COMPONENT_COUNT);
		FILES.set_function("GET_SHOP_PED_APPAREL_FORCED_PROP_COUNT", LUA_NATIVE_FILES_GET_SHOP_PED_APPAREL_FORCED_PROP_COUNT);
		FILES.set_function("GET_FORCED_COMPONENT", LUA_NATIVE_FILES_GET_FORCED_COMPONENT);
		FILES.set_function("GET_FORCED_PROP", LUA_NATIVE_FILES_GET_FORCED_PROP);
		FILES.set_function("DOES_SHOP_PED_APPAREL_HAVE_RESTRICTION_TAG", LUA_NATIVE_FILES_DOES_SHOP_PED_APPAREL_HAVE_RESTRICTION_TAG);
		FILES.set_function("DOES_CURRENT_PED_COMPONENT_HAVE_RESTRICTION_TAG", LUA_NATIVE_FILES_DOES_CURRENT_PED_COMPONENT_HAVE_RESTRICTION_TAG);
		FILES.set_function("DOES_CURRENT_PED_PROP_HAVE_RESTRICTION_TAG", LUA_NATIVE_FILES_DOES_CURRENT_PED_PROP_HAVE_RESTRICTION_TAG);
		FILES.set_function("SETUP_SHOP_PED_OUTFIT_QUERY", LUA_NATIVE_FILES_SETUP_SHOP_PED_OUTFIT_QUERY);
		FILES.set_function("GET_SHOP_PED_QUERY_OUTFIT", LUA_NATIVE_FILES_GET_SHOP_PED_QUERY_OUTFIT);
		FILES.set_function("GET_SHOP_PED_OUTFIT", LUA_NATIVE_FILES_GET_SHOP_PED_OUTFIT);
		FILES.set_function("GET_SHOP_PED_OUTFIT_LOCATE", LUA_NATIVE_FILES_GET_SHOP_PED_OUTFIT_LOCATE);
		FILES.set_function("GET_SHOP_PED_OUTFIT_PROP_VARIANT", LUA_NATIVE_FILES_GET_SHOP_PED_OUTFIT_PROP_VARIANT);
		FILES.set_function("GET_SHOP_PED_OUTFIT_COMPONENT_VARIANT", LUA_NATIVE_FILES_GET_SHOP_PED_OUTFIT_COMPONENT_VARIANT);
		FILES.set_function("GET_NUM_DLC_VEHICLES", LUA_NATIVE_FILES_GET_NUM_DLC_VEHICLES);
		FILES.set_function("GET_DLC_VEHICLE_MODEL", LUA_NATIVE_FILES_GET_DLC_VEHICLE_MODEL);
		FILES.set_function("GET_DLC_VEHICLE_DATA", LUA_NATIVE_FILES_GET_DLC_VEHICLE_DATA);
		FILES.set_function("GET_DLC_VEHICLE_FLAGS", LUA_NATIVE_FILES_GET_DLC_VEHICLE_FLAGS);
		FILES.set_function("GET_NUM_DLC_WEAPONS", LUA_NATIVE_FILES_GET_NUM_DLC_WEAPONS);
		FILES.set_function("GET_NUM_DLC_WEAPONS_SP", LUA_NATIVE_FILES_GET_NUM_DLC_WEAPONS_SP);
		FILES.set_function("GET_DLC_WEAPON_DATA", LUA_NATIVE_FILES_GET_DLC_WEAPON_DATA);
		FILES.set_function("GET_DLC_WEAPON_DATA_SP", LUA_NATIVE_FILES_GET_DLC_WEAPON_DATA_SP);
		FILES.set_function("GET_NUM_DLC_WEAPON_COMPONENTS", LUA_NATIVE_FILES_GET_NUM_DLC_WEAPON_COMPONENTS);
		FILES.set_function("GET_NUM_DLC_WEAPON_COMPONENTS_SP", LUA_NATIVE_FILES_GET_NUM_DLC_WEAPON_COMPONENTS_SP);
		FILES.set_function("GET_DLC_WEAPON_COMPONENT_DATA", LUA_NATIVE_FILES_GET_DLC_WEAPON_COMPONENT_DATA);
		FILES.set_function("GET_DLC_WEAPON_COMPONENT_DATA_SP", LUA_NATIVE_FILES_GET_DLC_WEAPON_COMPONENT_DATA_SP);
		FILES.set_function("IS_CONTENT_ITEM_LOCKED", LUA_NATIVE_FILES_IS_CONTENT_ITEM_LOCKED);
		FILES.set_function("IS_DLC_VEHICLE_MOD", LUA_NATIVE_FILES_IS_DLC_VEHICLE_MOD);
		FILES.set_function("GET_DLC_VEHICLE_MOD_LOCK_HASH", LUA_NATIVE_FILES_GET_DLC_VEHICLE_MOD_LOCK_HASH);
		FILES.set_function("EXECUTE_CONTENT_CHANGESET_GROUP_FOR_ALL", LUA_NATIVE_FILES_EXECUTE_CONTENT_CHANGESET_GROUP_FOR_ALL);
		FILES.set_function("REVERT_CONTENT_CHANGESET_GROUP_FOR_ALL", LUA_NATIVE_FILES_REVERT_CONTENT_CHANGESET_GROUP_FOR_ALL);
	}
}
