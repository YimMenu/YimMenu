#include "lua_native_binding.hpp"
#include "natives.hpp"

namespace lua::native
{
	static void LUA_NATIVE_WEAPON_ENABLE_LASER_SIGHT_RENDERING(bool toggle)
	{
		WEAPON::ENABLE_LASER_SIGHT_RENDERING(toggle);
	}

	static Hash LUA_NATIVE_WEAPON_GET_WEAPON_COMPONENT_TYPE_MODEL(Hash componentHash)
	{
		auto retval = WEAPON::GET_WEAPON_COMPONENT_TYPE_MODEL(componentHash);
		return retval;
	}

	static Hash LUA_NATIVE_WEAPON_GET_WEAPONTYPE_MODEL(Hash weaponHash)
	{
		auto retval = WEAPON::GET_WEAPONTYPE_MODEL(weaponHash);
		return retval;
	}

	static Hash LUA_NATIVE_WEAPON_GET_WEAPONTYPE_SLOT(Hash weaponHash)
	{
		auto retval = WEAPON::GET_WEAPONTYPE_SLOT(weaponHash);
		return retval;
	}

	static Hash LUA_NATIVE_WEAPON_GET_WEAPONTYPE_GROUP(Hash weaponHash)
	{
		auto retval = WEAPON::GET_WEAPONTYPE_GROUP(weaponHash);
		return retval;
	}

	static int LUA_NATIVE_WEAPON_GET_WEAPON_COMPONENT_VARIANT_EXTRA_COUNT(Hash componentHash)
	{
		auto retval = WEAPON::GET_WEAPON_COMPONENT_VARIANT_EXTRA_COUNT(componentHash);
		return retval;
	}

	static Hash LUA_NATIVE_WEAPON_GET_WEAPON_COMPONENT_VARIANT_EXTRA_MODEL(Hash componentHash, int extraComponentIndex)
	{
		auto retval = WEAPON::GET_WEAPON_COMPONENT_VARIANT_EXTRA_MODEL(componentHash, extraComponentIndex);
		return retval;
	}

	static void LUA_NATIVE_WEAPON_SET_CURRENT_PED_WEAPON(Ped ped, Hash weaponHash, bool bForceInHand)
	{
		WEAPON::SET_CURRENT_PED_WEAPON(ped, weaponHash, bForceInHand);
	}

	static std::tuple<bool, Hash> LUA_NATIVE_WEAPON_GET_CURRENT_PED_WEAPON(Ped ped, Hash weaponHash, bool p2)
	{
		std::tuple<bool, Hash> return_values;
		std::get<0>(return_values) = (bool)WEAPON::GET_CURRENT_PED_WEAPON(ped, &weaponHash, p2);
		std::get<1>(return_values) = weaponHash;

		return return_values;
	}

	static Entity LUA_NATIVE_WEAPON_GET_CURRENT_PED_WEAPON_ENTITY_INDEX(Ped ped, Any p1)
	{
		auto retval = WEAPON::GET_CURRENT_PED_WEAPON_ENTITY_INDEX(ped, p1);
		return retval;
	}

	static Hash LUA_NATIVE_WEAPON_GET_BEST_PED_WEAPON(Ped ped, bool p1)
	{
		auto retval = WEAPON::GET_BEST_PED_WEAPON(ped, p1);
		return retval;
	}

	static bool LUA_NATIVE_WEAPON_SET_CURRENT_PED_VEHICLE_WEAPON(Ped ped, Hash weaponHash)
	{
		auto retval = (bool)WEAPON::SET_CURRENT_PED_VEHICLE_WEAPON(ped, weaponHash);
		return retval;
	}

	static std::tuple<bool, Hash> LUA_NATIVE_WEAPON_GET_CURRENT_PED_VEHICLE_WEAPON(Ped ped, Hash weaponHash)
	{
		std::tuple<bool, Hash> return_values;
		std::get<0>(return_values) = (bool)WEAPON::GET_CURRENT_PED_VEHICLE_WEAPON(ped, &weaponHash);
		std::get<1>(return_values) = weaponHash;

		return return_values;
	}

	static void LUA_NATIVE_WEAPON_SET_PED_CYCLE_VEHICLE_WEAPONS_ONLY(Ped ped)
	{
		WEAPON::SET_PED_CYCLE_VEHICLE_WEAPONS_ONLY(ped);
	}

	static bool LUA_NATIVE_WEAPON_IS_PED_ARMED(Ped ped, int typeFlags)
	{
		auto retval = (bool)WEAPON::IS_PED_ARMED(ped, typeFlags);
		return retval;
	}

	static bool LUA_NATIVE_WEAPON_IS_WEAPON_VALID(Hash weaponHash)
	{
		auto retval = (bool)WEAPON::IS_WEAPON_VALID(weaponHash);
		return retval;
	}

	static bool LUA_NATIVE_WEAPON_HAS_PED_GOT_WEAPON(Ped ped, Hash weaponHash, bool p2)
	{
		auto retval = (bool)WEAPON::HAS_PED_GOT_WEAPON(ped, weaponHash, p2);
		return retval;
	}

	static bool LUA_NATIVE_WEAPON_IS_PED_WEAPON_READY_TO_SHOOT(Ped ped)
	{
		auto retval = (bool)WEAPON::IS_PED_WEAPON_READY_TO_SHOOT(ped);
		return retval;
	}

	static Hash LUA_NATIVE_WEAPON_GET_PED_WEAPONTYPE_IN_SLOT(Ped ped, Hash weaponSlot)
	{
		auto retval = WEAPON::GET_PED_WEAPONTYPE_IN_SLOT(ped, weaponSlot);
		return retval;
	}

	static int LUA_NATIVE_WEAPON_GET_AMMO_IN_PED_WEAPON(Ped ped, Hash weaponhash)
	{
		auto retval = WEAPON::GET_AMMO_IN_PED_WEAPON(ped, weaponhash);
		return retval;
	}

	static void LUA_NATIVE_WEAPON_ADD_AMMO_TO_PED(Ped ped, Hash weaponHash, int ammo)
	{
		WEAPON::ADD_AMMO_TO_PED(ped, weaponHash, ammo);
	}

	static void LUA_NATIVE_WEAPON_SET_PED_AMMO(Ped ped, Hash weaponHash, int ammo, bool p3)
	{
		WEAPON::SET_PED_AMMO(ped, weaponHash, ammo, p3);
	}

	static void LUA_NATIVE_WEAPON_SET_PED_INFINITE_AMMO(Ped ped, bool toggle, Hash weaponHash)
	{
		WEAPON::SET_PED_INFINITE_AMMO(ped, toggle, weaponHash);
	}

	static void LUA_NATIVE_WEAPON_SET_PED_INFINITE_AMMO_CLIP(Ped ped, bool toggle)
	{
		WEAPON::SET_PED_INFINITE_AMMO_CLIP(ped, toggle);
	}

	static void LUA_NATIVE_WEAPON_SET_PED_STUN_GUN_FINITE_AMMO(Any p0, Any p1)
	{
		WEAPON::SET_PED_STUN_GUN_FINITE_AMMO(p0, p1);
	}

	static void LUA_NATIVE_WEAPON_GIVE_WEAPON_TO_PED(Ped ped, Hash weaponHash, int ammoCount, bool isHidden, bool bForceInHand)
	{
		WEAPON::GIVE_WEAPON_TO_PED(ped, weaponHash, ammoCount, isHidden, bForceInHand);
	}

	static void LUA_NATIVE_WEAPON_GIVE_DELAYED_WEAPON_TO_PED(Ped ped, Hash weaponHash, int ammoCount, bool bForceInHand)
	{
		WEAPON::GIVE_DELAYED_WEAPON_TO_PED(ped, weaponHash, ammoCount, bForceInHand);
	}

	static void LUA_NATIVE_WEAPON_REMOVE_ALL_PED_WEAPONS(Ped ped, bool p1)
	{
		WEAPON::REMOVE_ALL_PED_WEAPONS(ped, p1);
	}

	static void LUA_NATIVE_WEAPON_REMOVE_WEAPON_FROM_PED(Ped ped, Hash weaponHash)
	{
		WEAPON::REMOVE_WEAPON_FROM_PED(ped, weaponHash);
	}

	static void LUA_NATIVE_WEAPON_HIDE_PED_WEAPON_FOR_SCRIPTED_CUTSCENE(Ped ped, bool toggle)
	{
		WEAPON::HIDE_PED_WEAPON_FOR_SCRIPTED_CUTSCENE(ped, toggle);
	}

	static void LUA_NATIVE_WEAPON_SET_PED_CURRENT_WEAPON_VISIBLE(Ped ped, bool visible, bool deselectWeapon, bool p3, bool p4)
	{
		WEAPON::SET_PED_CURRENT_WEAPON_VISIBLE(ped, visible, deselectWeapon, p3, p4);
	}

	static void LUA_NATIVE_WEAPON_SET_PED_DROPS_WEAPONS_WHEN_DEAD(Ped ped, bool toggle)
	{
		WEAPON::SET_PED_DROPS_WEAPONS_WHEN_DEAD(ped, toggle);
	}

	static bool LUA_NATIVE_WEAPON_HAS_PED_BEEN_DAMAGED_BY_WEAPON(Ped ped, Hash weaponHash, int weaponType)
	{
		auto retval = (bool)WEAPON::HAS_PED_BEEN_DAMAGED_BY_WEAPON(ped, weaponHash, weaponType);
		return retval;
	}

	static void LUA_NATIVE_WEAPON_CLEAR_PED_LAST_WEAPON_DAMAGE(Ped ped)
	{
		WEAPON::CLEAR_PED_LAST_WEAPON_DAMAGE(ped);
	}

	static bool LUA_NATIVE_WEAPON_HAS_ENTITY_BEEN_DAMAGED_BY_WEAPON(Entity entity, Hash weaponHash, int weaponType)
	{
		auto retval = (bool)WEAPON::HAS_ENTITY_BEEN_DAMAGED_BY_WEAPON(entity, weaponHash, weaponType);
		return retval;
	}

	static void LUA_NATIVE_WEAPON_CLEAR_ENTITY_LAST_WEAPON_DAMAGE(Entity entity)
	{
		WEAPON::CLEAR_ENTITY_LAST_WEAPON_DAMAGE(entity);
	}

	static void LUA_NATIVE_WEAPON_SET_PED_DROPS_WEAPON(Ped ped)
	{
		WEAPON::SET_PED_DROPS_WEAPON(ped);
	}

	static void LUA_NATIVE_WEAPON_SET_PED_DROPS_INVENTORY_WEAPON(Ped ped, Hash weaponHash, float xOffset, float yOffset, float zOffset, int ammoCount)
	{
		WEAPON::SET_PED_DROPS_INVENTORY_WEAPON(ped, weaponHash, xOffset, yOffset, zOffset, ammoCount);
	}

	static int LUA_NATIVE_WEAPON_GET_MAX_AMMO_IN_CLIP(Ped ped, Hash weaponHash, bool p2)
	{
		auto retval = WEAPON::GET_MAX_AMMO_IN_CLIP(ped, weaponHash, p2);
		return retval;
	}

	static std::tuple<bool, int> LUA_NATIVE_WEAPON_GET_AMMO_IN_CLIP(Ped ped, Hash weaponHash, int ammo)
	{
		std::tuple<bool, int> return_values;
		std::get<0>(return_values) = (bool)WEAPON::GET_AMMO_IN_CLIP(ped, weaponHash, &ammo);
		std::get<1>(return_values) = ammo;

		return return_values;
	}

	static bool LUA_NATIVE_WEAPON_SET_AMMO_IN_CLIP(Ped ped, Hash weaponHash, int ammo)
	{
		auto retval = (bool)WEAPON::SET_AMMO_IN_CLIP(ped, weaponHash, ammo);
		return retval;
	}

	static std::tuple<bool, int> LUA_NATIVE_WEAPON_GET_MAX_AMMO(Ped ped, Hash weaponHash, int ammo)
	{
		std::tuple<bool, int> return_values;
		std::get<0>(return_values) = (bool)WEAPON::GET_MAX_AMMO(ped, weaponHash, &ammo);
		std::get<1>(return_values) = ammo;

		return return_values;
	}

	static std::tuple<bool, int> LUA_NATIVE_WEAPON_GET_MAX_AMMO_BY_TYPE(Ped ped, Hash ammoTypeHash, int ammo)
	{
		std::tuple<bool, int> return_values;
		std::get<0>(return_values) = (bool)WEAPON::GET_MAX_AMMO_BY_TYPE(ped, ammoTypeHash, &ammo);
		std::get<1>(return_values) = ammo;

		return return_values;
	}

	static void LUA_NATIVE_WEAPON_ADD_PED_AMMO_BY_TYPE(Ped ped, Hash ammoTypeHash, int ammo)
	{
		WEAPON::ADD_PED_AMMO_BY_TYPE(ped, ammoTypeHash, ammo);
	}

	static void LUA_NATIVE_WEAPON_SET_PED_AMMO_BY_TYPE(Ped ped, Hash ammoTypeHash, int ammo)
	{
		WEAPON::SET_PED_AMMO_BY_TYPE(ped, ammoTypeHash, ammo);
	}

	static int LUA_NATIVE_WEAPON_GET_PED_AMMO_BY_TYPE(Ped ped, Hash ammoTypeHash)
	{
		auto retval = WEAPON::GET_PED_AMMO_BY_TYPE(ped, ammoTypeHash);
		return retval;
	}

	static void LUA_NATIVE_WEAPON_SET_PED_AMMO_TO_DROP(Ped ped, int p1)
	{
		WEAPON::SET_PED_AMMO_TO_DROP(ped, p1);
	}

	static void LUA_NATIVE_WEAPON_SET_PICKUP_AMMO_AMOUNT_SCALER(float p0)
	{
		WEAPON::SET_PICKUP_AMMO_AMOUNT_SCALER(p0);
	}

	static Hash LUA_NATIVE_WEAPON_GET_PED_AMMO_TYPE_FROM_WEAPON(Ped ped, Hash weaponHash)
	{
		auto retval = WEAPON::GET_PED_AMMO_TYPE_FROM_WEAPON(ped, weaponHash);
		return retval;
	}

	static Hash LUA_NATIVE_WEAPON_GET_PED_ORIGINAL_AMMO_TYPE_FROM_WEAPON(Ped ped, Hash weaponHash)
	{
		auto retval = WEAPON::GET_PED_ORIGINAL_AMMO_TYPE_FROM_WEAPON(ped, weaponHash);
		return retval;
	}

	static std::tuple<bool, Vector3> LUA_NATIVE_WEAPON_GET_PED_LAST_WEAPON_IMPACT_COORD(Ped ped, Vector3 coords)
	{
		std::tuple<bool, Vector3> return_values;
		std::get<0>(return_values) = (bool)WEAPON::GET_PED_LAST_WEAPON_IMPACT_COORD(ped, &coords);
		std::get<1>(return_values) = coords;

		return return_values;
	}

	static void LUA_NATIVE_WEAPON_SET_PED_GADGET(Ped ped, Hash gadgetHash, bool p2)
	{
		WEAPON::SET_PED_GADGET(ped, gadgetHash, p2);
	}

	static bool LUA_NATIVE_WEAPON_GET_IS_PED_GADGET_EQUIPPED(Ped ped, Hash gadgetHash)
	{
		auto retval = (bool)WEAPON::GET_IS_PED_GADGET_EQUIPPED(ped, gadgetHash);
		return retval;
	}

	static Hash LUA_NATIVE_WEAPON_GET_SELECTED_PED_WEAPON(Ped ped)
	{
		auto retval = WEAPON::GET_SELECTED_PED_WEAPON(ped);
		return retval;
	}

	static void LUA_NATIVE_WEAPON_EXPLODE_PROJECTILES(Ped ped, Hash weaponHash, bool p2)
	{
		WEAPON::EXPLODE_PROJECTILES(ped, weaponHash, p2);
	}

	static void LUA_NATIVE_WEAPON_REMOVE_ALL_PROJECTILES_OF_TYPE(Hash weaponHash, bool explode)
	{
		WEAPON::REMOVE_ALL_PROJECTILES_OF_TYPE(weaponHash, explode);
	}

	static float LUA_NATIVE_WEAPON_GET_LOCKON_DISTANCE_OF_CURRENT_PED_WEAPON(Ped ped)
	{
		auto retval = WEAPON::GET_LOCKON_DISTANCE_OF_CURRENT_PED_WEAPON(ped);
		return retval;
	}

	static float LUA_NATIVE_WEAPON_GET_MAX_RANGE_OF_CURRENT_PED_WEAPON(Ped ped)
	{
		auto retval = WEAPON::GET_MAX_RANGE_OF_CURRENT_PED_WEAPON(ped);
		return retval;
	}

	static bool LUA_NATIVE_WEAPON_HAS_VEHICLE_GOT_PROJECTILE_ATTACHED(Ped driver, Vehicle vehicle, Hash weaponHash, Any p3)
	{
		auto retval = (bool)WEAPON::HAS_VEHICLE_GOT_PROJECTILE_ATTACHED(driver, vehicle, weaponHash, p3);
		return retval;
	}

	static void LUA_NATIVE_WEAPON_GIVE_WEAPON_COMPONENT_TO_PED(Ped ped, Hash weaponHash, Hash componentHash)
	{
		WEAPON::GIVE_WEAPON_COMPONENT_TO_PED(ped, weaponHash, componentHash);
	}

	static void LUA_NATIVE_WEAPON_REMOVE_WEAPON_COMPONENT_FROM_PED(Ped ped, Hash weaponHash, Hash componentHash)
	{
		WEAPON::REMOVE_WEAPON_COMPONENT_FROM_PED(ped, weaponHash, componentHash);
	}

	static bool LUA_NATIVE_WEAPON_HAS_PED_GOT_WEAPON_COMPONENT(Ped ped, Hash weaponHash, Hash componentHash)
	{
		auto retval = (bool)WEAPON::HAS_PED_GOT_WEAPON_COMPONENT(ped, weaponHash, componentHash);
		return retval;
	}

	static bool LUA_NATIVE_WEAPON_IS_PED_WEAPON_COMPONENT_ACTIVE(Ped ped, Hash weaponHash, Hash componentHash)
	{
		auto retval = (bool)WEAPON::IS_PED_WEAPON_COMPONENT_ACTIVE(ped, weaponHash, componentHash);
		return retval;
	}

	static bool LUA_NATIVE_WEAPON_REFILL_AMMO_INSTANTLY(Ped ped)
	{
		auto retval = (bool)WEAPON::REFILL_AMMO_INSTANTLY(ped);
		return retval;
	}

	static bool LUA_NATIVE_WEAPON_MAKE_PED_RELOAD(Ped ped)
	{
		auto retval = (bool)WEAPON::MAKE_PED_RELOAD(ped);
		return retval;
	}

	static void LUA_NATIVE_WEAPON_REQUEST_WEAPON_ASSET(Hash weaponHash, int p1, int p2)
	{
		WEAPON::REQUEST_WEAPON_ASSET(weaponHash, p1, p2);
	}

	static bool LUA_NATIVE_WEAPON_HAS_WEAPON_ASSET_LOADED(Hash weaponHash)
	{
		auto retval = (bool)WEAPON::HAS_WEAPON_ASSET_LOADED(weaponHash);
		return retval;
	}

	static void LUA_NATIVE_WEAPON_REMOVE_WEAPON_ASSET(Hash weaponHash)
	{
		WEAPON::REMOVE_WEAPON_ASSET(weaponHash);
	}

	static Object LUA_NATIVE_WEAPON_CREATE_WEAPON_OBJECT(Hash weaponHash, int ammoCount, float x, float y, float z, bool showWorldModel, float scale, Any p7, Any p8, Any p9)
	{
		auto retval = WEAPON::CREATE_WEAPON_OBJECT(weaponHash, ammoCount, x, y, z, showWorldModel, scale, p7, p8, p9);
		return retval;
	}

	static void LUA_NATIVE_WEAPON_GIVE_WEAPON_COMPONENT_TO_WEAPON_OBJECT(Object weaponObject, Hash componentHash)
	{
		WEAPON::GIVE_WEAPON_COMPONENT_TO_WEAPON_OBJECT(weaponObject, componentHash);
	}

	static void LUA_NATIVE_WEAPON_REMOVE_WEAPON_COMPONENT_FROM_WEAPON_OBJECT(Object object, Hash componentHash)
	{
		WEAPON::REMOVE_WEAPON_COMPONENT_FROM_WEAPON_OBJECT(object, componentHash);
	}

	static bool LUA_NATIVE_WEAPON_HAS_WEAPON_GOT_WEAPON_COMPONENT(Object weapon, Hash componentHash)
	{
		auto retval = (bool)WEAPON::HAS_WEAPON_GOT_WEAPON_COMPONENT(weapon, componentHash);
		return retval;
	}

	static void LUA_NATIVE_WEAPON_GIVE_WEAPON_OBJECT_TO_PED(Object weaponObject, Ped ped)
	{
		WEAPON::GIVE_WEAPON_OBJECT_TO_PED(weaponObject, ped);
	}

	static bool LUA_NATIVE_WEAPON_DOES_WEAPON_TAKE_WEAPON_COMPONENT(Hash weaponHash, Hash componentHash)
	{
		auto retval = (bool)WEAPON::DOES_WEAPON_TAKE_WEAPON_COMPONENT(weaponHash, componentHash);
		return retval;
	}

	static Object LUA_NATIVE_WEAPON_GET_WEAPON_OBJECT_FROM_PED(Ped ped, bool p1)
	{
		auto retval = WEAPON::GET_WEAPON_OBJECT_FROM_PED(ped, p1);
		return retval;
	}

	static void LUA_NATIVE_WEAPON_GIVE_LOADOUT_TO_PED(Ped ped, Hash loadoutHash)
	{
		WEAPON::GIVE_LOADOUT_TO_PED(ped, loadoutHash);
	}

	static void LUA_NATIVE_WEAPON_SET_PED_WEAPON_TINT_INDEX(Ped ped, Hash weaponHash, int tintIndex)
	{
		WEAPON::SET_PED_WEAPON_TINT_INDEX(ped, weaponHash, tintIndex);
	}

	static int LUA_NATIVE_WEAPON_GET_PED_WEAPON_TINT_INDEX(Ped ped, Hash weaponHash)
	{
		auto retval = WEAPON::GET_PED_WEAPON_TINT_INDEX(ped, weaponHash);
		return retval;
	}

	static void LUA_NATIVE_WEAPON_SET_WEAPON_OBJECT_TINT_INDEX(Object weapon, int tintIndex)
	{
		WEAPON::SET_WEAPON_OBJECT_TINT_INDEX(weapon, tintIndex);
	}

	static int LUA_NATIVE_WEAPON_GET_WEAPON_OBJECT_TINT_INDEX(Object weapon)
	{
		auto retval = WEAPON::GET_WEAPON_OBJECT_TINT_INDEX(weapon);
		return retval;
	}

	static int LUA_NATIVE_WEAPON_GET_WEAPON_TINT_COUNT(Hash weaponHash)
	{
		auto retval = WEAPON::GET_WEAPON_TINT_COUNT(weaponHash);
		return retval;
	}

	static void LUA_NATIVE_WEAPON_SET_PED_WEAPON_COMPONENT_TINT_INDEX(Ped ped, Hash weaponHash, Hash camoComponentHash, int colorIndex)
	{
		WEAPON::SET_PED_WEAPON_COMPONENT_TINT_INDEX(ped, weaponHash, camoComponentHash, colorIndex);
	}

	static int LUA_NATIVE_WEAPON_GET_PED_WEAPON_COMPONENT_TINT_INDEX(Ped ped, Hash weaponHash, Hash camoComponentHash)
	{
		auto retval = WEAPON::GET_PED_WEAPON_COMPONENT_TINT_INDEX(ped, weaponHash, camoComponentHash);
		return retval;
	}

	static void LUA_NATIVE_WEAPON_SET_WEAPON_OBJECT_COMPONENT_TINT_INDEX(Object weaponObject, Hash camoComponentHash, int colorIndex)
	{
		WEAPON::SET_WEAPON_OBJECT_COMPONENT_TINT_INDEX(weaponObject, camoComponentHash, colorIndex);
	}

	static int LUA_NATIVE_WEAPON_GET_WEAPON_OBJECT_COMPONENT_TINT_INDEX(Object weaponObject, Hash camoComponentHash)
	{
		auto retval = WEAPON::GET_WEAPON_OBJECT_COMPONENT_TINT_INDEX(weaponObject, camoComponentHash);
		return retval;
	}

	static int LUA_NATIVE_WEAPON_GET_PED_WEAPON_CAMO_INDEX(Ped ped, Hash weaponHash)
	{
		auto retval = WEAPON::GET_PED_WEAPON_CAMO_INDEX(ped, weaponHash);
		return retval;
	}

	static void LUA_NATIVE_WEAPON_SET_WEAPON_OBJECT_CAMO_INDEX(Object weaponObject, int p1)
	{
		WEAPON::SET_WEAPON_OBJECT_CAMO_INDEX(weaponObject, p1);
	}

	static bool LUA_NATIVE_WEAPON_GET_WEAPON_HUD_STATS(Hash weaponHash, uintptr_t outData)
	{
		auto retval = (bool)WEAPON::GET_WEAPON_HUD_STATS(weaponHash, (Any*)outData);
		return retval;
	}

	static bool LUA_NATIVE_WEAPON_GET_WEAPON_COMPONENT_HUD_STATS(Hash componentHash, uintptr_t outData)
	{
		auto retval = (bool)WEAPON::GET_WEAPON_COMPONENT_HUD_STATS(componentHash, (Any*)outData);
		return retval;
	}

	static float LUA_NATIVE_WEAPON_GET_WEAPON_DAMAGE(Hash weaponHash, Hash componentHash)
	{
		auto retval = WEAPON::GET_WEAPON_DAMAGE(weaponHash, componentHash);
		return retval;
	}

	static int LUA_NATIVE_WEAPON_GET_WEAPON_CLIP_SIZE(Hash weaponHash)
	{
		auto retval = WEAPON::GET_WEAPON_CLIP_SIZE(weaponHash);
		return retval;
	}

	static float LUA_NATIVE_WEAPON_GET_WEAPON_TIME_BETWEEN_SHOTS(Hash weaponHash)
	{
		auto retval = WEAPON::GET_WEAPON_TIME_BETWEEN_SHOTS(weaponHash);
		return retval;
	}

	static void LUA_NATIVE_WEAPON_SET_PED_CHANCE_OF_FIRING_BLANKS(Ped ped, float xBias, float yBias)
	{
		WEAPON::SET_PED_CHANCE_OF_FIRING_BLANKS(ped, xBias, yBias);
	}

	static Object LUA_NATIVE_WEAPON_SET_PED_SHOOT_ORDNANCE_WEAPON(Ped ped, float p1)
	{
		auto retval = WEAPON::SET_PED_SHOOT_ORDNANCE_WEAPON(ped, p1);
		return retval;
	}

	static void LUA_NATIVE_WEAPON_REQUEST_WEAPON_HIGH_DETAIL_MODEL(Entity weaponObject)
	{
		WEAPON::REQUEST_WEAPON_HIGH_DETAIL_MODEL(weaponObject);
	}

	static void LUA_NATIVE_WEAPON_SET_WEAPON_PED_DAMAGE_MODIFIER_(Hash weapon, float damageModifier)
	{
		WEAPON::_SET_WEAPON_PED_DAMAGE_MODIFIER(weapon, damageModifier);
	}

	static void LUA_NATIVE_WEAPON_SET_WEAPON_DAMAGE_MODIFIER(Hash weaponHash, float damageMultiplier)
	{
		WEAPON::SET_WEAPON_DAMAGE_MODIFIER(weaponHash, damageMultiplier);
	}

	static void LUA_NATIVE_WEAPON_SET_WEAPON_AOE_MODIFIER(Hash weaponHash, float multiplier)
	{
		WEAPON::SET_WEAPON_AOE_MODIFIER(weaponHash, multiplier);
	}

	static void LUA_NATIVE_WEAPON_SET_WEAPON_EFFECT_DURATION_MODIFIER(Hash p0, float p1)
	{
		WEAPON::SET_WEAPON_EFFECT_DURATION_MODIFIER(p0, p1);
	}

	static bool LUA_NATIVE_WEAPON_IS_PED_CURRENT_WEAPON_SILENCED(Ped ped)
	{
		auto retval = (bool)WEAPON::IS_PED_CURRENT_WEAPON_SILENCED(ped);
		return retval;
	}

	static bool LUA_NATIVE_WEAPON_IS_FLASH_LIGHT_ON(Ped ped)
	{
		auto retval = (bool)WEAPON::IS_FLASH_LIGHT_ON(ped);
		return retval;
	}

	static bool LUA_NATIVE_WEAPON_SET_FLASH_LIGHT_FADE_DISTANCE(float distance)
	{
		auto retval = (bool)WEAPON::SET_FLASH_LIGHT_FADE_DISTANCE(distance);
		return retval;
	}

	static void LUA_NATIVE_WEAPON_SET_FLASH_LIGHT_ACTIVE_HISTORY(Ped ped, bool toggle)
	{
		WEAPON::SET_FLASH_LIGHT_ACTIVE_HISTORY(ped, toggle);
	}

	static void LUA_NATIVE_WEAPON_SET_WEAPON_ANIMATION_OVERRIDE(Ped ped, Hash animStyle)
	{
		WEAPON::SET_WEAPON_ANIMATION_OVERRIDE(ped, animStyle);
	}

	static int LUA_NATIVE_WEAPON_GET_WEAPON_DAMAGE_TYPE(Hash weaponHash)
	{
		auto retval = WEAPON::GET_WEAPON_DAMAGE_TYPE(weaponHash);
		return retval;
	}

	static void LUA_NATIVE_WEAPON_SET_EQIPPED_WEAPON_START_SPINNING_AT_FULL_SPEED(Ped ped)
	{
		WEAPON::SET_EQIPPED_WEAPON_START_SPINNING_AT_FULL_SPEED(ped);
	}

	static bool LUA_NATIVE_WEAPON_CAN_USE_WEAPON_ON_PARACHUTE(Hash weaponHash)
	{
		auto retval = (bool)WEAPON::CAN_USE_WEAPON_ON_PARACHUTE(weaponHash);
		return retval;
	}

	static int LUA_NATIVE_WEAPON_CREATE_AIR_DEFENCE_SPHERE(float x, float y, float z, float radius, float p4, float p5, float p6, Hash weaponHash)
	{
		auto retval = WEAPON::CREATE_AIR_DEFENCE_SPHERE(x, y, z, radius, p4, p5, p6, weaponHash);
		return retval;
	}

	static int LUA_NATIVE_WEAPON_CREATE_AIR_DEFENCE_ANGLED_AREA(float p0, float p1, float p2, float p3, float p4, float p5, float p6, float p7, float p8, float radius, Hash weaponHash)
	{
		auto retval = WEAPON::CREATE_AIR_DEFENCE_ANGLED_AREA(p0, p1, p2, p3, p4, p5, p6, p7, p8, radius, weaponHash);
		return retval;
	}

	static bool LUA_NATIVE_WEAPON_REMOVE_AIR_DEFENCE_SPHERE(int zoneId)
	{
		auto retval = (bool)WEAPON::REMOVE_AIR_DEFENCE_SPHERE(zoneId);
		return retval;
	}

	static void LUA_NATIVE_WEAPON_REMOVE_ALL_AIR_DEFENCE_SPHERES()
	{
		WEAPON::REMOVE_ALL_AIR_DEFENCE_SPHERES();
	}

	static void LUA_NATIVE_WEAPON_SET_PLAYER_TARGETTABLE_FOR_AIR_DEFENCE_SPHERE(Player player, int zoneId, bool enable)
	{
		WEAPON::SET_PLAYER_TARGETTABLE_FOR_AIR_DEFENCE_SPHERE(player, zoneId, enable);
	}

	static std::tuple<bool, int> LUA_NATIVE_WEAPON_IS_AIR_DEFENCE_SPHERE_IN_AREA(float x, float y, float z, float radius, int outZoneId)
	{
		std::tuple<bool, int> return_values;
		std::get<0>(return_values) = (bool)WEAPON::IS_AIR_DEFENCE_SPHERE_IN_AREA(x, y, z, radius, &outZoneId);
		std::get<1>(return_values) = outZoneId;

		return return_values;
	}

	static void LUA_NATIVE_WEAPON_FIRE_AIR_DEFENCE_SPHERE_WEAPON_AT_POSITION(int zoneId, float x, float y, float z)
	{
		WEAPON::FIRE_AIR_DEFENCE_SPHERE_WEAPON_AT_POSITION(zoneId, x, y, z);
	}

	static bool LUA_NATIVE_WEAPON_DOES_AIR_DEFENCE_SPHERE_EXIST(int zoneId)
	{
		auto retval = (bool)WEAPON::DOES_AIR_DEFENCE_SPHERE_EXIST(zoneId);
		return retval;
	}

	static void LUA_NATIVE_WEAPON_SET_CAN_PED_SELECT_INVENTORY_WEAPON(Ped ped, Hash weaponHash, bool toggle)
	{
		WEAPON::SET_CAN_PED_SELECT_INVENTORY_WEAPON(ped, weaponHash, toggle);
	}

	static void LUA_NATIVE_WEAPON_SET_CAN_PED_SELECT_ALL_WEAPONS(Ped ped, bool toggle)
	{
		WEAPON::SET_CAN_PED_SELECT_ALL_WEAPONS(ped, toggle);
	}

	void init_native_binding_WEAPON(sol::state& L)
	{
		auto WEAPON = L["WEAPON"].get_or_create<sol::table>();
		WEAPON.set_function("ENABLE_LASER_SIGHT_RENDERING", LUA_NATIVE_WEAPON_ENABLE_LASER_SIGHT_RENDERING);
		WEAPON.set_function("GET_WEAPON_COMPONENT_TYPE_MODEL", LUA_NATIVE_WEAPON_GET_WEAPON_COMPONENT_TYPE_MODEL);
		WEAPON.set_function("GET_WEAPONTYPE_MODEL", LUA_NATIVE_WEAPON_GET_WEAPONTYPE_MODEL);
		WEAPON.set_function("GET_WEAPONTYPE_SLOT", LUA_NATIVE_WEAPON_GET_WEAPONTYPE_SLOT);
		WEAPON.set_function("GET_WEAPONTYPE_GROUP", LUA_NATIVE_WEAPON_GET_WEAPONTYPE_GROUP);
		WEAPON.set_function("GET_WEAPON_COMPONENT_VARIANT_EXTRA_COUNT", LUA_NATIVE_WEAPON_GET_WEAPON_COMPONENT_VARIANT_EXTRA_COUNT);
		WEAPON.set_function("GET_WEAPON_COMPONENT_VARIANT_EXTRA_MODEL", LUA_NATIVE_WEAPON_GET_WEAPON_COMPONENT_VARIANT_EXTRA_MODEL);
		WEAPON.set_function("SET_CURRENT_PED_WEAPON", LUA_NATIVE_WEAPON_SET_CURRENT_PED_WEAPON);
		WEAPON.set_function("GET_CURRENT_PED_WEAPON", LUA_NATIVE_WEAPON_GET_CURRENT_PED_WEAPON);
		WEAPON.set_function("GET_CURRENT_PED_WEAPON_ENTITY_INDEX", LUA_NATIVE_WEAPON_GET_CURRENT_PED_WEAPON_ENTITY_INDEX);
		WEAPON.set_function("GET_BEST_PED_WEAPON", LUA_NATIVE_WEAPON_GET_BEST_PED_WEAPON);
		WEAPON.set_function("SET_CURRENT_PED_VEHICLE_WEAPON", LUA_NATIVE_WEAPON_SET_CURRENT_PED_VEHICLE_WEAPON);
		WEAPON.set_function("GET_CURRENT_PED_VEHICLE_WEAPON", LUA_NATIVE_WEAPON_GET_CURRENT_PED_VEHICLE_WEAPON);
		WEAPON.set_function("SET_PED_CYCLE_VEHICLE_WEAPONS_ONLY", LUA_NATIVE_WEAPON_SET_PED_CYCLE_VEHICLE_WEAPONS_ONLY);
		WEAPON.set_function("IS_PED_ARMED", LUA_NATIVE_WEAPON_IS_PED_ARMED);
		WEAPON.set_function("IS_WEAPON_VALID", LUA_NATIVE_WEAPON_IS_WEAPON_VALID);
		WEAPON.set_function("HAS_PED_GOT_WEAPON", LUA_NATIVE_WEAPON_HAS_PED_GOT_WEAPON);
		WEAPON.set_function("IS_PED_WEAPON_READY_TO_SHOOT", LUA_NATIVE_WEAPON_IS_PED_WEAPON_READY_TO_SHOOT);
		WEAPON.set_function("GET_PED_WEAPONTYPE_IN_SLOT", LUA_NATIVE_WEAPON_GET_PED_WEAPONTYPE_IN_SLOT);
		WEAPON.set_function("GET_AMMO_IN_PED_WEAPON", LUA_NATIVE_WEAPON_GET_AMMO_IN_PED_WEAPON);
		WEAPON.set_function("ADD_AMMO_TO_PED", LUA_NATIVE_WEAPON_ADD_AMMO_TO_PED);
		WEAPON.set_function("SET_PED_AMMO", LUA_NATIVE_WEAPON_SET_PED_AMMO);
		WEAPON.set_function("SET_PED_INFINITE_AMMO", LUA_NATIVE_WEAPON_SET_PED_INFINITE_AMMO);
		WEAPON.set_function("SET_PED_INFINITE_AMMO_CLIP", LUA_NATIVE_WEAPON_SET_PED_INFINITE_AMMO_CLIP);
		WEAPON.set_function("SET_PED_STUN_GUN_FINITE_AMMO", LUA_NATIVE_WEAPON_SET_PED_STUN_GUN_FINITE_AMMO);
		WEAPON.set_function("GIVE_WEAPON_TO_PED", LUA_NATIVE_WEAPON_GIVE_WEAPON_TO_PED);
		WEAPON.set_function("GIVE_DELAYED_WEAPON_TO_PED", LUA_NATIVE_WEAPON_GIVE_DELAYED_WEAPON_TO_PED);
		WEAPON.set_function("REMOVE_ALL_PED_WEAPONS", LUA_NATIVE_WEAPON_REMOVE_ALL_PED_WEAPONS);
		WEAPON.set_function("REMOVE_WEAPON_FROM_PED", LUA_NATIVE_WEAPON_REMOVE_WEAPON_FROM_PED);
		WEAPON.set_function("HIDE_PED_WEAPON_FOR_SCRIPTED_CUTSCENE", LUA_NATIVE_WEAPON_HIDE_PED_WEAPON_FOR_SCRIPTED_CUTSCENE);
		WEAPON.set_function("SET_PED_CURRENT_WEAPON_VISIBLE", LUA_NATIVE_WEAPON_SET_PED_CURRENT_WEAPON_VISIBLE);
		WEAPON.set_function("SET_PED_DROPS_WEAPONS_WHEN_DEAD", LUA_NATIVE_WEAPON_SET_PED_DROPS_WEAPONS_WHEN_DEAD);
		WEAPON.set_function("HAS_PED_BEEN_DAMAGED_BY_WEAPON", LUA_NATIVE_WEAPON_HAS_PED_BEEN_DAMAGED_BY_WEAPON);
		WEAPON.set_function("CLEAR_PED_LAST_WEAPON_DAMAGE", LUA_NATIVE_WEAPON_CLEAR_PED_LAST_WEAPON_DAMAGE);
		WEAPON.set_function("HAS_ENTITY_BEEN_DAMAGED_BY_WEAPON", LUA_NATIVE_WEAPON_HAS_ENTITY_BEEN_DAMAGED_BY_WEAPON);
		WEAPON.set_function("CLEAR_ENTITY_LAST_WEAPON_DAMAGE", LUA_NATIVE_WEAPON_CLEAR_ENTITY_LAST_WEAPON_DAMAGE);
		WEAPON.set_function("SET_PED_DROPS_WEAPON", LUA_NATIVE_WEAPON_SET_PED_DROPS_WEAPON);
		WEAPON.set_function("SET_PED_DROPS_INVENTORY_WEAPON", LUA_NATIVE_WEAPON_SET_PED_DROPS_INVENTORY_WEAPON);
		WEAPON.set_function("GET_MAX_AMMO_IN_CLIP", LUA_NATIVE_WEAPON_GET_MAX_AMMO_IN_CLIP);
		WEAPON.set_function("GET_AMMO_IN_CLIP", LUA_NATIVE_WEAPON_GET_AMMO_IN_CLIP);
		WEAPON.set_function("SET_AMMO_IN_CLIP", LUA_NATIVE_WEAPON_SET_AMMO_IN_CLIP);
		WEAPON.set_function("GET_MAX_AMMO", LUA_NATIVE_WEAPON_GET_MAX_AMMO);
		WEAPON.set_function("GET_MAX_AMMO_BY_TYPE", LUA_NATIVE_WEAPON_GET_MAX_AMMO_BY_TYPE);
		WEAPON.set_function("ADD_PED_AMMO_BY_TYPE", LUA_NATIVE_WEAPON_ADD_PED_AMMO_BY_TYPE);
		WEAPON.set_function("SET_PED_AMMO_BY_TYPE", LUA_NATIVE_WEAPON_SET_PED_AMMO_BY_TYPE);
		WEAPON.set_function("GET_PED_AMMO_BY_TYPE", LUA_NATIVE_WEAPON_GET_PED_AMMO_BY_TYPE);
		WEAPON.set_function("SET_PED_AMMO_TO_DROP", LUA_NATIVE_WEAPON_SET_PED_AMMO_TO_DROP);
		WEAPON.set_function("SET_PICKUP_AMMO_AMOUNT_SCALER", LUA_NATIVE_WEAPON_SET_PICKUP_AMMO_AMOUNT_SCALER);
		WEAPON.set_function("GET_PED_AMMO_TYPE_FROM_WEAPON", LUA_NATIVE_WEAPON_GET_PED_AMMO_TYPE_FROM_WEAPON);
		WEAPON.set_function("GET_PED_ORIGINAL_AMMO_TYPE_FROM_WEAPON", LUA_NATIVE_WEAPON_GET_PED_ORIGINAL_AMMO_TYPE_FROM_WEAPON);
		WEAPON.set_function("GET_PED_LAST_WEAPON_IMPACT_COORD", LUA_NATIVE_WEAPON_GET_PED_LAST_WEAPON_IMPACT_COORD);
		WEAPON.set_function("SET_PED_GADGET", LUA_NATIVE_WEAPON_SET_PED_GADGET);
		WEAPON.set_function("GET_IS_PED_GADGET_EQUIPPED", LUA_NATIVE_WEAPON_GET_IS_PED_GADGET_EQUIPPED);
		WEAPON.set_function("GET_SELECTED_PED_WEAPON", LUA_NATIVE_WEAPON_GET_SELECTED_PED_WEAPON);
		WEAPON.set_function("EXPLODE_PROJECTILES", LUA_NATIVE_WEAPON_EXPLODE_PROJECTILES);
		WEAPON.set_function("REMOVE_ALL_PROJECTILES_OF_TYPE", LUA_NATIVE_WEAPON_REMOVE_ALL_PROJECTILES_OF_TYPE);
		WEAPON.set_function("GET_LOCKON_DISTANCE_OF_CURRENT_PED_WEAPON", LUA_NATIVE_WEAPON_GET_LOCKON_DISTANCE_OF_CURRENT_PED_WEAPON);
		WEAPON.set_function("GET_MAX_RANGE_OF_CURRENT_PED_WEAPON", LUA_NATIVE_WEAPON_GET_MAX_RANGE_OF_CURRENT_PED_WEAPON);
		WEAPON.set_function("HAS_VEHICLE_GOT_PROJECTILE_ATTACHED", LUA_NATIVE_WEAPON_HAS_VEHICLE_GOT_PROJECTILE_ATTACHED);
		WEAPON.set_function("GIVE_WEAPON_COMPONENT_TO_PED", LUA_NATIVE_WEAPON_GIVE_WEAPON_COMPONENT_TO_PED);
		WEAPON.set_function("REMOVE_WEAPON_COMPONENT_FROM_PED", LUA_NATIVE_WEAPON_REMOVE_WEAPON_COMPONENT_FROM_PED);
		WEAPON.set_function("HAS_PED_GOT_WEAPON_COMPONENT", LUA_NATIVE_WEAPON_HAS_PED_GOT_WEAPON_COMPONENT);
		WEAPON.set_function("IS_PED_WEAPON_COMPONENT_ACTIVE", LUA_NATIVE_WEAPON_IS_PED_WEAPON_COMPONENT_ACTIVE);
		WEAPON.set_function("REFILL_AMMO_INSTANTLY", LUA_NATIVE_WEAPON_REFILL_AMMO_INSTANTLY);
		WEAPON.set_function("MAKE_PED_RELOAD", LUA_NATIVE_WEAPON_MAKE_PED_RELOAD);
		WEAPON.set_function("REQUEST_WEAPON_ASSET", LUA_NATIVE_WEAPON_REQUEST_WEAPON_ASSET);
		WEAPON.set_function("HAS_WEAPON_ASSET_LOADED", LUA_NATIVE_WEAPON_HAS_WEAPON_ASSET_LOADED);
		WEAPON.set_function("REMOVE_WEAPON_ASSET", LUA_NATIVE_WEAPON_REMOVE_WEAPON_ASSET);
		WEAPON.set_function("CREATE_WEAPON_OBJECT", LUA_NATIVE_WEAPON_CREATE_WEAPON_OBJECT);
		WEAPON.set_function("GIVE_WEAPON_COMPONENT_TO_WEAPON_OBJECT", LUA_NATIVE_WEAPON_GIVE_WEAPON_COMPONENT_TO_WEAPON_OBJECT);
		WEAPON.set_function("REMOVE_WEAPON_COMPONENT_FROM_WEAPON_OBJECT", LUA_NATIVE_WEAPON_REMOVE_WEAPON_COMPONENT_FROM_WEAPON_OBJECT);
		WEAPON.set_function("HAS_WEAPON_GOT_WEAPON_COMPONENT", LUA_NATIVE_WEAPON_HAS_WEAPON_GOT_WEAPON_COMPONENT);
		WEAPON.set_function("GIVE_WEAPON_OBJECT_TO_PED", LUA_NATIVE_WEAPON_GIVE_WEAPON_OBJECT_TO_PED);
		WEAPON.set_function("DOES_WEAPON_TAKE_WEAPON_COMPONENT", LUA_NATIVE_WEAPON_DOES_WEAPON_TAKE_WEAPON_COMPONENT);
		WEAPON.set_function("GET_WEAPON_OBJECT_FROM_PED", LUA_NATIVE_WEAPON_GET_WEAPON_OBJECT_FROM_PED);
		WEAPON.set_function("GIVE_LOADOUT_TO_PED", LUA_NATIVE_WEAPON_GIVE_LOADOUT_TO_PED);
		WEAPON.set_function("SET_PED_WEAPON_TINT_INDEX", LUA_NATIVE_WEAPON_SET_PED_WEAPON_TINT_INDEX);
		WEAPON.set_function("GET_PED_WEAPON_TINT_INDEX", LUA_NATIVE_WEAPON_GET_PED_WEAPON_TINT_INDEX);
		WEAPON.set_function("SET_WEAPON_OBJECT_TINT_INDEX", LUA_NATIVE_WEAPON_SET_WEAPON_OBJECT_TINT_INDEX);
		WEAPON.set_function("GET_WEAPON_OBJECT_TINT_INDEX", LUA_NATIVE_WEAPON_GET_WEAPON_OBJECT_TINT_INDEX);
		WEAPON.set_function("GET_WEAPON_TINT_COUNT", LUA_NATIVE_WEAPON_GET_WEAPON_TINT_COUNT);
		WEAPON.set_function("SET_PED_WEAPON_COMPONENT_TINT_INDEX", LUA_NATIVE_WEAPON_SET_PED_WEAPON_COMPONENT_TINT_INDEX);
		WEAPON.set_function("GET_PED_WEAPON_COMPONENT_TINT_INDEX", LUA_NATIVE_WEAPON_GET_PED_WEAPON_COMPONENT_TINT_INDEX);
		WEAPON.set_function("SET_WEAPON_OBJECT_COMPONENT_TINT_INDEX", LUA_NATIVE_WEAPON_SET_WEAPON_OBJECT_COMPONENT_TINT_INDEX);
		WEAPON.set_function("GET_WEAPON_OBJECT_COMPONENT_TINT_INDEX", LUA_NATIVE_WEAPON_GET_WEAPON_OBJECT_COMPONENT_TINT_INDEX);
		WEAPON.set_function("GET_PED_WEAPON_CAMO_INDEX", LUA_NATIVE_WEAPON_GET_PED_WEAPON_CAMO_INDEX);
		WEAPON.set_function("SET_WEAPON_OBJECT_CAMO_INDEX", LUA_NATIVE_WEAPON_SET_WEAPON_OBJECT_CAMO_INDEX);
		WEAPON.set_function("GET_WEAPON_HUD_STATS", LUA_NATIVE_WEAPON_GET_WEAPON_HUD_STATS);
		WEAPON.set_function("GET_WEAPON_COMPONENT_HUD_STATS", LUA_NATIVE_WEAPON_GET_WEAPON_COMPONENT_HUD_STATS);
		WEAPON.set_function("GET_WEAPON_DAMAGE", LUA_NATIVE_WEAPON_GET_WEAPON_DAMAGE);
		WEAPON.set_function("GET_WEAPON_CLIP_SIZE", LUA_NATIVE_WEAPON_GET_WEAPON_CLIP_SIZE);
		WEAPON.set_function("GET_WEAPON_TIME_BETWEEN_SHOTS", LUA_NATIVE_WEAPON_GET_WEAPON_TIME_BETWEEN_SHOTS);
		WEAPON.set_function("SET_PED_CHANCE_OF_FIRING_BLANKS", LUA_NATIVE_WEAPON_SET_PED_CHANCE_OF_FIRING_BLANKS);
		WEAPON.set_function("SET_PED_SHOOT_ORDNANCE_WEAPON", LUA_NATIVE_WEAPON_SET_PED_SHOOT_ORDNANCE_WEAPON);
		WEAPON.set_function("REQUEST_WEAPON_HIGH_DETAIL_MODEL", LUA_NATIVE_WEAPON_REQUEST_WEAPON_HIGH_DETAIL_MODEL);
		WEAPON.set_function("SET_WEAPON_PED_DAMAGE_MODIFIER_", LUA_NATIVE_WEAPON_SET_WEAPON_PED_DAMAGE_MODIFIER_);
		WEAPON.set_function("SET_WEAPON_DAMAGE_MODIFIER", LUA_NATIVE_WEAPON_SET_WEAPON_DAMAGE_MODIFIER);
		WEAPON.set_function("SET_WEAPON_AOE_MODIFIER", LUA_NATIVE_WEAPON_SET_WEAPON_AOE_MODIFIER);
		WEAPON.set_function("SET_WEAPON_EFFECT_DURATION_MODIFIER", LUA_NATIVE_WEAPON_SET_WEAPON_EFFECT_DURATION_MODIFIER);
		WEAPON.set_function("IS_PED_CURRENT_WEAPON_SILENCED", LUA_NATIVE_WEAPON_IS_PED_CURRENT_WEAPON_SILENCED);
		WEAPON.set_function("IS_FLASH_LIGHT_ON", LUA_NATIVE_WEAPON_IS_FLASH_LIGHT_ON);
		WEAPON.set_function("SET_FLASH_LIGHT_FADE_DISTANCE", LUA_NATIVE_WEAPON_SET_FLASH_LIGHT_FADE_DISTANCE);
		WEAPON.set_function("SET_FLASH_LIGHT_ACTIVE_HISTORY", LUA_NATIVE_WEAPON_SET_FLASH_LIGHT_ACTIVE_HISTORY);
		WEAPON.set_function("SET_WEAPON_ANIMATION_OVERRIDE", LUA_NATIVE_WEAPON_SET_WEAPON_ANIMATION_OVERRIDE);
		WEAPON.set_function("GET_WEAPON_DAMAGE_TYPE", LUA_NATIVE_WEAPON_GET_WEAPON_DAMAGE_TYPE);
		WEAPON.set_function("SET_EQIPPED_WEAPON_START_SPINNING_AT_FULL_SPEED", LUA_NATIVE_WEAPON_SET_EQIPPED_WEAPON_START_SPINNING_AT_FULL_SPEED);
		WEAPON.set_function("CAN_USE_WEAPON_ON_PARACHUTE", LUA_NATIVE_WEAPON_CAN_USE_WEAPON_ON_PARACHUTE);
		WEAPON.set_function("CREATE_AIR_DEFENCE_SPHERE", LUA_NATIVE_WEAPON_CREATE_AIR_DEFENCE_SPHERE);
		WEAPON.set_function("CREATE_AIR_DEFENCE_ANGLED_AREA", LUA_NATIVE_WEAPON_CREATE_AIR_DEFENCE_ANGLED_AREA);
		WEAPON.set_function("REMOVE_AIR_DEFENCE_SPHERE", LUA_NATIVE_WEAPON_REMOVE_AIR_DEFENCE_SPHERE);
		WEAPON.set_function("REMOVE_ALL_AIR_DEFENCE_SPHERES", LUA_NATIVE_WEAPON_REMOVE_ALL_AIR_DEFENCE_SPHERES);
		WEAPON.set_function("SET_PLAYER_TARGETTABLE_FOR_AIR_DEFENCE_SPHERE", LUA_NATIVE_WEAPON_SET_PLAYER_TARGETTABLE_FOR_AIR_DEFENCE_SPHERE);
		WEAPON.set_function("IS_AIR_DEFENCE_SPHERE_IN_AREA", LUA_NATIVE_WEAPON_IS_AIR_DEFENCE_SPHERE_IN_AREA);
		WEAPON.set_function("FIRE_AIR_DEFENCE_SPHERE_WEAPON_AT_POSITION", LUA_NATIVE_WEAPON_FIRE_AIR_DEFENCE_SPHERE_WEAPON_AT_POSITION);
		WEAPON.set_function("DOES_AIR_DEFENCE_SPHERE_EXIST", LUA_NATIVE_WEAPON_DOES_AIR_DEFENCE_SPHERE_EXIST);
		WEAPON.set_function("SET_CAN_PED_SELECT_INVENTORY_WEAPON", LUA_NATIVE_WEAPON_SET_CAN_PED_SELECT_INVENTORY_WEAPON);
		WEAPON.set_function("SET_CAN_PED_SELECT_ALL_WEAPONS", LUA_NATIVE_WEAPON_SET_CAN_PED_SELECT_ALL_WEAPONS);
	}
}
