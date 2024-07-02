#include "lua_native_binding.hpp"
#include "natives.hpp"

namespace lua::native
{
	static Ped LUA_NATIVE_PLAYER_GET_PLAYER_PED(Player player)
	{
		auto retval = PLAYER::GET_PLAYER_PED(player);
		return retval;
	}

	static Ped LUA_NATIVE_PLAYER_GET_PLAYER_PED_SCRIPT_INDEX(Player player)
	{
		auto retval = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player);
		return retval;
	}

	static void LUA_NATIVE_PLAYER_SET_PLAYER_MODEL(Player player, Hash model)
	{
		PLAYER::SET_PLAYER_MODEL(player, model);
	}

	static void LUA_NATIVE_PLAYER_CHANGE_PLAYER_PED(Player player, Ped ped, bool p2, bool resetDamage)
	{
		PLAYER::CHANGE_PLAYER_PED(player, ped, p2, resetDamage);
	}

	static std::tuple<int, int, int> LUA_NATIVE_PLAYER_GET_PLAYER_RGB_COLOUR(Player player, int r, int g, int b)
	{
		std::tuple<int, int, int> return_values;
		PLAYER::GET_PLAYER_RGB_COLOUR(player, &r, &g, &b);
		std::get<0>(return_values) = r;
		std::get<1>(return_values) = g;
		std::get<2>(return_values) = b;

		return return_values;
	}

	static int LUA_NATIVE_PLAYER_GET_NUMBER_OF_PLAYERS()
	{
		auto retval = PLAYER::GET_NUMBER_OF_PLAYERS();
		return retval;
	}

	static int LUA_NATIVE_PLAYER_GET_PLAYER_TEAM(Player player)
	{
		auto retval = PLAYER::GET_PLAYER_TEAM(player);
		return retval;
	}

	static void LUA_NATIVE_PLAYER_SET_PLAYER_TEAM(Player player, int team)
	{
		PLAYER::SET_PLAYER_TEAM(player, team);
	}

	static int LUA_NATIVE_PLAYER_GET_NUMBER_OF_PLAYERS_IN_TEAM(int team)
	{
		auto retval = PLAYER::GET_NUMBER_OF_PLAYERS_IN_TEAM(team);
		return retval;
	}

	static const char* LUA_NATIVE_PLAYER_GET_PLAYER_NAME(Player player)
	{
		auto retval = PLAYER::GET_PLAYER_NAME(player);
		return retval;
	}

	static float LUA_NATIVE_PLAYER_GET_WANTED_LEVEL_RADIUS(Player player)
	{
		auto retval = PLAYER::GET_WANTED_LEVEL_RADIUS(player);
		return retval;
	}

	static Vector3 LUA_NATIVE_PLAYER_GET_PLAYER_WANTED_CENTRE_POSITION(Player player)
	{
		auto retval = PLAYER::GET_PLAYER_WANTED_CENTRE_POSITION(player);
		return retval;
	}

	static Vector3 LUA_NATIVE_PLAYER_SET_PLAYER_WANTED_CENTRE_POSITION(Player player, Vector3 position, bool p2, bool p3)
	{
		PLAYER::SET_PLAYER_WANTED_CENTRE_POSITION(player, &position, p2, p3);
		return position;
	}

	static int LUA_NATIVE_PLAYER_GET_WANTED_LEVEL_THRESHOLD(int wantedLevel)
	{
		auto retval = PLAYER::GET_WANTED_LEVEL_THRESHOLD(wantedLevel);
		return retval;
	}

	static void LUA_NATIVE_PLAYER_SET_PLAYER_WANTED_LEVEL(Player player, int wantedLevel, bool disableNoMission)
	{
		PLAYER::SET_PLAYER_WANTED_LEVEL(player, wantedLevel, disableNoMission);
	}

	static void LUA_NATIVE_PLAYER_SET_PLAYER_WANTED_LEVEL_NO_DROP(Player player, int wantedLevel, bool p2)
	{
		PLAYER::SET_PLAYER_WANTED_LEVEL_NO_DROP(player, wantedLevel, p2);
	}

	static void LUA_NATIVE_PLAYER_SET_PLAYER_WANTED_LEVEL_NOW(Player player, bool p1)
	{
		PLAYER::SET_PLAYER_WANTED_LEVEL_NOW(player, p1);
	}

	static bool LUA_NATIVE_PLAYER_ARE_PLAYER_FLASHING_STARS_ABOUT_TO_DROP(Player player)
	{
		auto retval = (bool)PLAYER::ARE_PLAYER_FLASHING_STARS_ABOUT_TO_DROP(player);
		return retval;
	}

	static bool LUA_NATIVE_PLAYER_ARE_PLAYER_STARS_GREYED_OUT(Player player)
	{
		auto retval = (bool)PLAYER::ARE_PLAYER_STARS_GREYED_OUT(player);
		return retval;
	}

	static bool LUA_NATIVE_PLAYER_IS_WANTED_AND_HAS_BEEN_SEEN_BY_COPS(Player player)
	{
		auto retval = (bool)PLAYER::IS_WANTED_AND_HAS_BEEN_SEEN_BY_COPS(player);
		return retval;
	}

	static void LUA_NATIVE_PLAYER_SET_DISPATCH_COPS_FOR_PLAYER(Player player, bool toggle)
	{
		PLAYER::SET_DISPATCH_COPS_FOR_PLAYER(player, toggle);
	}

	static bool LUA_NATIVE_PLAYER_IS_PLAYER_WANTED_LEVEL_GREATER(Player player, int wantedLevel)
	{
		auto retval = (bool)PLAYER::IS_PLAYER_WANTED_LEVEL_GREATER(player, wantedLevel);
		return retval;
	}

	static void LUA_NATIVE_PLAYER_CLEAR_PLAYER_WANTED_LEVEL(Player player)
	{
		PLAYER::CLEAR_PLAYER_WANTED_LEVEL(player);
	}

	static bool LUA_NATIVE_PLAYER_IS_PLAYER_DEAD(Player player)
	{
		auto retval = (bool)PLAYER::IS_PLAYER_DEAD(player);
		return retval;
	}

	static bool LUA_NATIVE_PLAYER_IS_PLAYER_PRESSING_HORN(Player player)
	{
		auto retval = (bool)PLAYER::IS_PLAYER_PRESSING_HORN(player);
		return retval;
	}

	static void LUA_NATIVE_PLAYER_SET_PLAYER_CONTROL(Player player, bool bHasControl, int flags)
	{
		PLAYER::SET_PLAYER_CONTROL(player, bHasControl, flags);
	}

	static int LUA_NATIVE_PLAYER_GET_PLAYER_WANTED_LEVEL(Player player)
	{
		auto retval = PLAYER::GET_PLAYER_WANTED_LEVEL(player);
		return retval;
	}

	static void LUA_NATIVE_PLAYER_SET_MAX_WANTED_LEVEL(int maxWantedLevel)
	{
		PLAYER::SET_MAX_WANTED_LEVEL(maxWantedLevel);
	}

	static void LUA_NATIVE_PLAYER_SET_POLICE_RADAR_BLIPS(bool toggle)
	{
		PLAYER::SET_POLICE_RADAR_BLIPS(toggle);
	}

	static void LUA_NATIVE_PLAYER_SET_POLICE_IGNORE_PLAYER(Player player, bool toggle)
	{
		PLAYER::SET_POLICE_IGNORE_PLAYER(player, toggle);
	}

	static bool LUA_NATIVE_PLAYER_IS_PLAYER_PLAYING(Player player)
	{
		auto retval = (bool)PLAYER::IS_PLAYER_PLAYING(player);
		return retval;
	}

	static void LUA_NATIVE_PLAYER_SET_EVERYONE_IGNORE_PLAYER(Player player, bool toggle)
	{
		PLAYER::SET_EVERYONE_IGNORE_PLAYER(player, toggle);
	}

	static void LUA_NATIVE_PLAYER_SET_ALL_RANDOM_PEDS_FLEE(Player player, bool toggle)
	{
		PLAYER::SET_ALL_RANDOM_PEDS_FLEE(player, toggle);
	}

	static void LUA_NATIVE_PLAYER_SET_ALL_RANDOM_PEDS_FLEE_THIS_FRAME(Player player)
	{
		PLAYER::SET_ALL_RANDOM_PEDS_FLEE_THIS_FRAME(player);
	}

	static void LUA_NATIVE_PLAYER_SET_ALL_NEUTRAL_RANDOM_PEDS_FLEE(Player player, bool toggle)
	{
		PLAYER::SET_ALL_NEUTRAL_RANDOM_PEDS_FLEE(player, toggle);
	}

	static void LUA_NATIVE_PLAYER_SET_ALL_NEUTRAL_RANDOM_PEDS_FLEE_THIS_FRAME(Player player)
	{
		PLAYER::SET_ALL_NEUTRAL_RANDOM_PEDS_FLEE_THIS_FRAME(player);
	}

	static void LUA_NATIVE_PLAYER_SET_LAW_PEDS_CAN_ATTACK_NON_WANTED_PLAYER_THIS_FRAME(Player player)
	{
		PLAYER::SET_LAW_PEDS_CAN_ATTACK_NON_WANTED_PLAYER_THIS_FRAME(player);
	}

	static void LUA_NATIVE_PLAYER_SET_IGNORE_LOW_PRIORITY_SHOCKING_EVENTS(Player player, bool toggle)
	{
		PLAYER::SET_IGNORE_LOW_PRIORITY_SHOCKING_EVENTS(player, toggle);
	}

	static void LUA_NATIVE_PLAYER_SET_WANTED_LEVEL_MULTIPLIER(float multiplier)
	{
		PLAYER::SET_WANTED_LEVEL_MULTIPLIER(multiplier);
	}

	static void LUA_NATIVE_PLAYER_SET_WANTED_LEVEL_DIFFICULTY(Player player, float difficulty)
	{
		PLAYER::SET_WANTED_LEVEL_DIFFICULTY(player, difficulty);
	}

	static void LUA_NATIVE_PLAYER_RESET_WANTED_LEVEL_DIFFICULTY(Player player)
	{
		PLAYER::RESET_WANTED_LEVEL_DIFFICULTY(player);
	}

	static int LUA_NATIVE_PLAYER_GET_WANTED_LEVEL_TIME_TO_ESCAPE()
	{
		auto retval = PLAYER::GET_WANTED_LEVEL_TIME_TO_ESCAPE();
		return retval;
	}

	static void LUA_NATIVE_PLAYER_SET_WANTED_LEVEL_HIDDEN_ESCAPE_TIME(Player player, int wantedLevel, int lossTime)
	{
		PLAYER::SET_WANTED_LEVEL_HIDDEN_ESCAPE_TIME(player, wantedLevel, lossTime);
	}

	static void LUA_NATIVE_PLAYER_RESET_WANTED_LEVEL_HIDDEN_ESCAPE_TIME(Player player)
	{
		PLAYER::RESET_WANTED_LEVEL_HIDDEN_ESCAPE_TIME(player);
	}

	static void LUA_NATIVE_PLAYER_START_FIRING_AMNESTY(int duration)
	{
		PLAYER::START_FIRING_AMNESTY(duration);
	}

	static void LUA_NATIVE_PLAYER_REPORT_CRIME(Player player, int crimeType, int wantedLvlThresh)
	{
		PLAYER::REPORT_CRIME(player, crimeType, wantedLvlThresh);
	}

	static void LUA_NATIVE_PLAYER_SUPPRESS_CRIME_THIS_FRAME(Player player, int crimeType)
	{
		PLAYER::SUPPRESS_CRIME_THIS_FRAME(player, crimeType);
	}

	static void LUA_NATIVE_PLAYER_UPDATE_WANTED_POSITION_THIS_FRAME(Player player)
	{
		PLAYER::UPDATE_WANTED_POSITION_THIS_FRAME(player);
	}

	static void LUA_NATIVE_PLAYER_SUPPRESS_LOSING_WANTED_LEVEL_IF_HIDDEN_THIS_FRAME(Player player)
	{
		PLAYER::SUPPRESS_LOSING_WANTED_LEVEL_IF_HIDDEN_THIS_FRAME(player);
	}

	static void LUA_NATIVE_PLAYER_ALLOW_EVASION_HUD_IF_DISABLING_HIDDEN_EVASION_THIS_FRAME(Player player, Any p1)
	{
		PLAYER::ALLOW_EVASION_HUD_IF_DISABLING_HIDDEN_EVASION_THIS_FRAME(player, p1);
	}

	static void LUA_NATIVE_PLAYER_FORCE_START_HIDDEN_EVASION(Player player)
	{
		PLAYER::FORCE_START_HIDDEN_EVASION(player);
	}

	static void LUA_NATIVE_PLAYER_SUPPRESS_WITNESSES_CALLING_POLICE_THIS_FRAME(Player player)
	{
		PLAYER::SUPPRESS_WITNESSES_CALLING_POLICE_THIS_FRAME(player);
	}

	static void LUA_NATIVE_PLAYER_REPORT_POLICE_SPOTTED_PLAYER(Player player)
	{
		PLAYER::REPORT_POLICE_SPOTTED_PLAYER(player);
	}

	static void LUA_NATIVE_PLAYER_SET_LAW_RESPONSE_DELAY_OVERRIDE(float p0)
	{
		PLAYER::SET_LAW_RESPONSE_DELAY_OVERRIDE(p0);
	}

	static void LUA_NATIVE_PLAYER_RESET_LAW_RESPONSE_DELAY_OVERRIDE()
	{
		PLAYER::RESET_LAW_RESPONSE_DELAY_OVERRIDE();
	}

	static bool LUA_NATIVE_PLAYER_CAN_PLAYER_START_MISSION(Player player)
	{
		auto retval = (bool)PLAYER::CAN_PLAYER_START_MISSION(player);
		return retval;
	}

	static bool LUA_NATIVE_PLAYER_IS_PLAYER_READY_FOR_CUTSCENE(Player player)
	{
		auto retval = (bool)PLAYER::IS_PLAYER_READY_FOR_CUTSCENE(player);
		return retval;
	}

	static bool LUA_NATIVE_PLAYER_IS_PLAYER_TARGETTING_ENTITY(Player player, Entity entity)
	{
		auto retval = (bool)PLAYER::IS_PLAYER_TARGETTING_ENTITY(player, entity);
		return retval;
	}

	static std::tuple<bool, Entity> LUA_NATIVE_PLAYER_GET_PLAYER_TARGET_ENTITY(Player player, Entity entity)
	{
		std::tuple<bool, Entity> return_values;
		std::get<0>(return_values) = (bool)PLAYER::GET_PLAYER_TARGET_ENTITY(player, &entity);
		std::get<1>(return_values) = entity;

		return return_values;
	}

	static bool LUA_NATIVE_PLAYER_IS_PLAYER_FREE_AIMING(Player player)
	{
		auto retval = (bool)PLAYER::IS_PLAYER_FREE_AIMING(player);
		return retval;
	}

	static bool LUA_NATIVE_PLAYER_IS_PLAYER_FREE_AIMING_AT_ENTITY(Player player, Entity entity)
	{
		auto retval = (bool)PLAYER::IS_PLAYER_FREE_AIMING_AT_ENTITY(player, entity);
		return retval;
	}

	static std::tuple<bool, Entity> LUA_NATIVE_PLAYER_GET_ENTITY_PLAYER_IS_FREE_AIMING_AT(Player player, Entity entity)
	{
		std::tuple<bool, Entity> return_values;
		std::get<0>(return_values) = (bool)PLAYER::GET_ENTITY_PLAYER_IS_FREE_AIMING_AT(player, &entity);
		std::get<1>(return_values) = entity;

		return return_values;
	}

	static void LUA_NATIVE_PLAYER_SET_PLAYER_LOCKON_RANGE_OVERRIDE(Player player, float range)
	{
		PLAYER::SET_PLAYER_LOCKON_RANGE_OVERRIDE(player, range);
	}

	static void LUA_NATIVE_PLAYER_SET_PLAYER_CAN_DO_DRIVE_BY(Player player, bool toggle)
	{
		PLAYER::SET_PLAYER_CAN_DO_DRIVE_BY(player, toggle);
	}

	static void LUA_NATIVE_PLAYER_SET_PLAYER_CAN_BE_HASSLED_BY_GANGS(Player player, bool toggle)
	{
		PLAYER::SET_PLAYER_CAN_BE_HASSLED_BY_GANGS(player, toggle);
	}

	static void LUA_NATIVE_PLAYER_SET_PLAYER_CAN_USE_COVER(Player player, bool toggle)
	{
		PLAYER::SET_PLAYER_CAN_USE_COVER(player, toggle);
	}

	static int LUA_NATIVE_PLAYER_GET_MAX_WANTED_LEVEL()
	{
		auto retval = PLAYER::GET_MAX_WANTED_LEVEL();
		return retval;
	}

	static bool LUA_NATIVE_PLAYER_IS_PLAYER_TARGETTING_ANYTHING(Player player)
	{
		auto retval = (bool)PLAYER::IS_PLAYER_TARGETTING_ANYTHING(player);
		return retval;
	}

	static void LUA_NATIVE_PLAYER_SET_PLAYER_SPRINT(Player player, bool toggle)
	{
		PLAYER::SET_PLAYER_SPRINT(player, toggle);
	}

	static void LUA_NATIVE_PLAYER_RESET_PLAYER_STAMINA(Player player)
	{
		PLAYER::RESET_PLAYER_STAMINA(player);
	}

	static void LUA_NATIVE_PLAYER_RESTORE_PLAYER_STAMINA(Player player, float p1)
	{
		PLAYER::RESTORE_PLAYER_STAMINA(player, p1);
	}

	static float LUA_NATIVE_PLAYER_GET_PLAYER_SPRINT_STAMINA_REMAINING(Player player)
	{
		auto retval = PLAYER::GET_PLAYER_SPRINT_STAMINA_REMAINING(player);
		return retval;
	}

	static float LUA_NATIVE_PLAYER_GET_PLAYER_SPRINT_TIME_REMAINING(Player player)
	{
		auto retval = PLAYER::GET_PLAYER_SPRINT_TIME_REMAINING(player);
		return retval;
	}

	static float LUA_NATIVE_PLAYER_GET_PLAYER_UNDERWATER_TIME_REMAINING(Player player)
	{
		auto retval = PLAYER::GET_PLAYER_UNDERWATER_TIME_REMAINING(player);
		return retval;
	}

	static float LUA_NATIVE_PLAYER_SET_PLAYER_UNDERWATER_BREATH_PERCENT_REMAINING(Player player, float time)
	{
		auto retval = PLAYER::SET_PLAYER_UNDERWATER_BREATH_PERCENT_REMAINING(player, time);
		return retval;
	}

	static int LUA_NATIVE_PLAYER_GET_PLAYER_GROUP(Player player)
	{
		auto retval = PLAYER::GET_PLAYER_GROUP(player);
		return retval;
	}

	static int LUA_NATIVE_PLAYER_GET_PLAYER_MAX_ARMOUR(Player player)
	{
		auto retval = PLAYER::GET_PLAYER_MAX_ARMOUR(player);
		return retval;
	}

	static bool LUA_NATIVE_PLAYER_IS_PLAYER_CONTROL_ON(Player player)
	{
		auto retval = (bool)PLAYER::IS_PLAYER_CONTROL_ON(player);
		return retval;
	}

	static bool LUA_NATIVE_PLAYER_GET_ARE_CAMERA_CONTROLS_DISABLED()
	{
		auto retval = (bool)PLAYER::GET_ARE_CAMERA_CONTROLS_DISABLED();
		return retval;
	}

	static bool LUA_NATIVE_PLAYER_IS_PLAYER_SCRIPT_CONTROL_ON(Player player)
	{
		auto retval = (bool)PLAYER::IS_PLAYER_SCRIPT_CONTROL_ON(player);
		return retval;
	}

	static bool LUA_NATIVE_PLAYER_IS_PLAYER_CLIMBING(Player player)
	{
		auto retval = (bool)PLAYER::IS_PLAYER_CLIMBING(player);
		return retval;
	}

	static bool LUA_NATIVE_PLAYER_IS_PLAYER_BEING_ARRESTED(Player player, bool atArresting)
	{
		auto retval = (bool)PLAYER::IS_PLAYER_BEING_ARRESTED(player, atArresting);
		return retval;
	}

	static void LUA_NATIVE_PLAYER_RESET_PLAYER_ARREST_STATE(Player player)
	{
		PLAYER::RESET_PLAYER_ARREST_STATE(player);
	}

	static Vehicle LUA_NATIVE_PLAYER_GET_PLAYERS_LAST_VEHICLE()
	{
		auto retval = PLAYER::GET_PLAYERS_LAST_VEHICLE();
		return retval;
	}

	static Player LUA_NATIVE_PLAYER_GET_PLAYER_INDEX()
	{
		auto retval = PLAYER::GET_PLAYER_INDEX();
		return retval;
	}

	static Player LUA_NATIVE_PLAYER_INT_TO_PLAYERINDEX(int value)
	{
		auto retval = PLAYER::INT_TO_PLAYERINDEX(value);
		return retval;
	}

	static int LUA_NATIVE_PLAYER_INT_TO_PARTICIPANTINDEX(int value)
	{
		auto retval = PLAYER::INT_TO_PARTICIPANTINDEX(value);
		return retval;
	}

	static int LUA_NATIVE_PLAYER_GET_TIME_SINCE_PLAYER_HIT_VEHICLE(Player player)
	{
		auto retval = PLAYER::GET_TIME_SINCE_PLAYER_HIT_VEHICLE(player);
		return retval;
	}

	static int LUA_NATIVE_PLAYER_GET_TIME_SINCE_PLAYER_HIT_PED(Player player)
	{
		auto retval = PLAYER::GET_TIME_SINCE_PLAYER_HIT_PED(player);
		return retval;
	}

	static int LUA_NATIVE_PLAYER_GET_TIME_SINCE_PLAYER_DROVE_ON_PAVEMENT(Player player)
	{
		auto retval = PLAYER::GET_TIME_SINCE_PLAYER_DROVE_ON_PAVEMENT(player);
		return retval;
	}

	static int LUA_NATIVE_PLAYER_GET_TIME_SINCE_PLAYER_DROVE_AGAINST_TRAFFIC(Player player)
	{
		auto retval = PLAYER::GET_TIME_SINCE_PLAYER_DROVE_AGAINST_TRAFFIC(player);
		return retval;
	}

	static bool LUA_NATIVE_PLAYER_IS_PLAYER_FREE_FOR_AMBIENT_TASK(Player player)
	{
		auto retval = (bool)PLAYER::IS_PLAYER_FREE_FOR_AMBIENT_TASK(player);
		return retval;
	}

	static Player LUA_NATIVE_PLAYER_PLAYER_ID()
	{
		auto retval = PLAYER::PLAYER_ID();
		return retval;
	}

	static Ped LUA_NATIVE_PLAYER_PLAYER_PED_ID()
	{
		auto retval = PLAYER::PLAYER_PED_ID();
		return retval;
	}

	static int LUA_NATIVE_PLAYER_NETWORK_PLAYER_ID_TO_INT()
	{
		auto retval = PLAYER::NETWORK_PLAYER_ID_TO_INT();
		return retval;
	}

	static bool LUA_NATIVE_PLAYER_HAS_FORCE_CLEANUP_OCCURRED(int cleanupFlags)
	{
		auto retval = (bool)PLAYER::HAS_FORCE_CLEANUP_OCCURRED(cleanupFlags);
		return retval;
	}

	static void LUA_NATIVE_PLAYER_FORCE_CLEANUP(int cleanupFlags)
	{
		PLAYER::FORCE_CLEANUP(cleanupFlags);
	}

	static void LUA_NATIVE_PLAYER_FORCE_CLEANUP_FOR_ALL_THREADS_WITH_THIS_NAME(sol::stack_object name, int cleanupFlags)
	{
		PLAYER::FORCE_CLEANUP_FOR_ALL_THREADS_WITH_THIS_NAME(name.is<const char*>() ? name.as<const char*>() : nullptr, cleanupFlags);
	}

	static void LUA_NATIVE_PLAYER_FORCE_CLEANUP_FOR_THREAD_WITH_THIS_ID(int id, int cleanupFlags)
	{
		PLAYER::FORCE_CLEANUP_FOR_THREAD_WITH_THIS_ID(id, cleanupFlags);
	}

	static int LUA_NATIVE_PLAYER_GET_CAUSE_OF_MOST_RECENT_FORCE_CLEANUP()
	{
		auto retval = PLAYER::GET_CAUSE_OF_MOST_RECENT_FORCE_CLEANUP();
		return retval;
	}

	static void LUA_NATIVE_PLAYER_SET_PLAYER_MAY_ONLY_ENTER_THIS_VEHICLE(Player player, Vehicle vehicle)
	{
		PLAYER::SET_PLAYER_MAY_ONLY_ENTER_THIS_VEHICLE(player, vehicle);
	}

	static void LUA_NATIVE_PLAYER_SET_PLAYER_MAY_NOT_ENTER_ANY_VEHICLE(Player player)
	{
		PLAYER::SET_PLAYER_MAY_NOT_ENTER_ANY_VEHICLE(player);
	}

	static bool LUA_NATIVE_PLAYER_GIVE_ACHIEVEMENT_TO_PLAYER(int achievementId)
	{
		auto retval = (bool)PLAYER::GIVE_ACHIEVEMENT_TO_PLAYER(achievementId);
		return retval;
	}

	static bool LUA_NATIVE_PLAYER_SET_ACHIEVEMENT_PROGRESS(int achievementId, int progress)
	{
		auto retval = (bool)PLAYER::SET_ACHIEVEMENT_PROGRESS(achievementId, progress);
		return retval;
	}

	static int LUA_NATIVE_PLAYER_GET_ACHIEVEMENT_PROGRESS(int achievementId)
	{
		auto retval = PLAYER::GET_ACHIEVEMENT_PROGRESS(achievementId);
		return retval;
	}

	static bool LUA_NATIVE_PLAYER_HAS_ACHIEVEMENT_BEEN_PASSED(int achievementId)
	{
		auto retval = (bool)PLAYER::HAS_ACHIEVEMENT_BEEN_PASSED(achievementId);
		return retval;
	}

	static bool LUA_NATIVE_PLAYER_IS_PLAYER_ONLINE()
	{
		auto retval = (bool)PLAYER::IS_PLAYER_ONLINE();
		return retval;
	}

	static bool LUA_NATIVE_PLAYER_IS_PLAYER_LOGGING_IN_NP()
	{
		auto retval = (bool)PLAYER::IS_PLAYER_LOGGING_IN_NP();
		return retval;
	}

	static void LUA_NATIVE_PLAYER_DISPLAY_SYSTEM_SIGNIN_UI(bool p0)
	{
		PLAYER::DISPLAY_SYSTEM_SIGNIN_UI(p0);
	}

	static bool LUA_NATIVE_PLAYER_IS_SYSTEM_UI_BEING_DISPLAYED()
	{
		auto retval = (bool)PLAYER::IS_SYSTEM_UI_BEING_DISPLAYED();
		return retval;
	}

	static void LUA_NATIVE_PLAYER_SET_PLAYER_INVINCIBLE(Player player, bool toggle)
	{
		PLAYER::SET_PLAYER_INVINCIBLE(player, toggle);
	}

	static bool LUA_NATIVE_PLAYER_GET_PLAYER_INVINCIBLE(Player player)
	{
		auto retval = (bool)PLAYER::GET_PLAYER_INVINCIBLE(player);
		return retval;
	}

	static bool LUA_NATIVE_PLAYER_GET_PLAYER_DEBUG_INVINCIBLE(Player player)
	{
		auto retval = (bool)PLAYER::GET_PLAYER_DEBUG_INVINCIBLE(player);
		return retval;
	}

	static void LUA_NATIVE_PLAYER_SET_PLAYER_INVINCIBLE_BUT_HAS_REACTIONS(Player player, bool toggle)
	{
		PLAYER::SET_PLAYER_INVINCIBLE_BUT_HAS_REACTIONS(player, toggle);
	}

	static void LUA_NATIVE_PLAYER_SET_PLAYER_CAN_COLLECT_DROPPED_MONEY(Player player, bool p1)
	{
		PLAYER::SET_PLAYER_CAN_COLLECT_DROPPED_MONEY(player, p1);
	}

	static void LUA_NATIVE_PLAYER_REMOVE_PLAYER_HELMET(Player player, bool p2)
	{
		PLAYER::REMOVE_PLAYER_HELMET(player, p2);
	}

	static void LUA_NATIVE_PLAYER_GIVE_PLAYER_RAGDOLL_CONTROL(Player player, bool toggle)
	{
		PLAYER::GIVE_PLAYER_RAGDOLL_CONTROL(player, toggle);
	}

	static void LUA_NATIVE_PLAYER_SET_PLAYER_LOCKON(Player player, bool toggle)
	{
		PLAYER::SET_PLAYER_LOCKON(player, toggle);
	}

	static void LUA_NATIVE_PLAYER_SET_PLAYER_TARGETING_MODE(int targetMode)
	{
		PLAYER::SET_PLAYER_TARGETING_MODE(targetMode);
	}

	static void LUA_NATIVE_PLAYER_SET_PLAYER_TARGET_LEVEL(int targetLevel)
	{
		PLAYER::SET_PLAYER_TARGET_LEVEL(targetLevel);
	}

	static bool LUA_NATIVE_PLAYER_GET_IS_USING_FPS_THIRD_PERSON_COVER()
	{
		auto retval = (bool)PLAYER::GET_IS_USING_FPS_THIRD_PERSON_COVER();
		return retval;
	}

	static bool LUA_NATIVE_PLAYER_GET_IS_USING_HOOD_CAMERA()
	{
		auto retval = (bool)PLAYER::GET_IS_USING_HOOD_CAMERA();
		return retval;
	}

	static void LUA_NATIVE_PLAYER_CLEAR_PLAYER_HAS_DAMAGED_AT_LEAST_ONE_PED(Player player)
	{
		PLAYER::CLEAR_PLAYER_HAS_DAMAGED_AT_LEAST_ONE_PED(player);
	}

	static bool LUA_NATIVE_PLAYER_HAS_PLAYER_DAMAGED_AT_LEAST_ONE_PED(Player player)
	{
		auto retval = (bool)PLAYER::HAS_PLAYER_DAMAGED_AT_LEAST_ONE_PED(player);
		return retval;
	}

	static void LUA_NATIVE_PLAYER_CLEAR_PLAYER_HAS_DAMAGED_AT_LEAST_ONE_NON_ANIMAL_PED(Player player)
	{
		PLAYER::CLEAR_PLAYER_HAS_DAMAGED_AT_LEAST_ONE_NON_ANIMAL_PED(player);
	}

	static bool LUA_NATIVE_PLAYER_HAS_PLAYER_DAMAGED_AT_LEAST_ONE_NON_ANIMAL_PED(Player player)
	{
		auto retval = (bool)PLAYER::HAS_PLAYER_DAMAGED_AT_LEAST_ONE_NON_ANIMAL_PED(player);
		return retval;
	}

	static void LUA_NATIVE_PLAYER_SET_AIR_DRAG_MULTIPLIER_FOR_PLAYERS_VEHICLE(Player player, float multiplier)
	{
		PLAYER::SET_AIR_DRAG_MULTIPLIER_FOR_PLAYERS_VEHICLE(player, multiplier);
	}

	static void LUA_NATIVE_PLAYER_SET_SWIM_MULTIPLIER_FOR_PLAYER(Player player, float multiplier)
	{
		PLAYER::SET_SWIM_MULTIPLIER_FOR_PLAYER(player, multiplier);
	}

	static void LUA_NATIVE_PLAYER_SET_RUN_SPRINT_MULTIPLIER_FOR_PLAYER(Player player, float multiplier)
	{
		PLAYER::SET_RUN_SPRINT_MULTIPLIER_FOR_PLAYER(player, multiplier);
	}

	static int LUA_NATIVE_PLAYER_GET_TIME_SINCE_LAST_ARREST()
	{
		auto retval = PLAYER::GET_TIME_SINCE_LAST_ARREST();
		return retval;
	}

	static int LUA_NATIVE_PLAYER_GET_TIME_SINCE_LAST_DEATH()
	{
		auto retval = PLAYER::GET_TIME_SINCE_LAST_DEATH();
		return retval;
	}

	static void LUA_NATIVE_PLAYER_ASSISTED_MOVEMENT_CLOSE_ROUTE()
	{
		PLAYER::ASSISTED_MOVEMENT_CLOSE_ROUTE();
	}

	static void LUA_NATIVE_PLAYER_ASSISTED_MOVEMENT_FLUSH_ROUTE()
	{
		PLAYER::ASSISTED_MOVEMENT_FLUSH_ROUTE();
	}

	static void LUA_NATIVE_PLAYER_SET_PLAYER_FORCED_AIM(Player player, bool toggle)
	{
		PLAYER::SET_PLAYER_FORCED_AIM(player, toggle);
	}

	static void LUA_NATIVE_PLAYER_SET_PLAYER_FORCED_ZOOM(Player player, bool toggle)
	{
		PLAYER::SET_PLAYER_FORCED_ZOOM(player, toggle);
	}

	static void LUA_NATIVE_PLAYER_SET_PLAYER_FORCE_SKIP_AIM_INTRO(Player player, bool toggle)
	{
		PLAYER::SET_PLAYER_FORCE_SKIP_AIM_INTRO(player, toggle);
	}

	static void LUA_NATIVE_PLAYER_DISABLE_PLAYER_FIRING(Player player, bool toggle)
	{
		PLAYER::DISABLE_PLAYER_FIRING(player, toggle);
	}

	static void LUA_NATIVE_PLAYER_DISABLE_PLAYER_THROW_GRENADE_WHILE_USING_GUN()
	{
		PLAYER::DISABLE_PLAYER_THROW_GRENADE_WHILE_USING_GUN();
	}

	static void LUA_NATIVE_PLAYER_SET_DISABLE_AMBIENT_MELEE_MOVE(Player player, bool toggle)
	{
		PLAYER::SET_DISABLE_AMBIENT_MELEE_MOVE(player, toggle);
	}

	static void LUA_NATIVE_PLAYER_SET_PLAYER_MAX_ARMOUR(Player player, int value)
	{
		PLAYER::SET_PLAYER_MAX_ARMOUR(player, value);
	}

	static void LUA_NATIVE_PLAYER_SPECIAL_ABILITY_ACTIVATE(Player player, int p1)
	{
		PLAYER::SPECIAL_ABILITY_ACTIVATE(player, p1);
	}

	static void LUA_NATIVE_PLAYER_SET_SPECIAL_ABILITY_MP(Player player, int p1, Any p2)
	{
		PLAYER::SET_SPECIAL_ABILITY_MP(player, p1, p2);
	}

	static void LUA_NATIVE_PLAYER_SPECIAL_ABILITY_DEACTIVATE_MP(Player player, int p1)
	{
		PLAYER::SPECIAL_ABILITY_DEACTIVATE_MP(player, p1);
	}

	static void LUA_NATIVE_PLAYER_SPECIAL_ABILITY_DEACTIVATE(Player player, Any p1)
	{
		PLAYER::SPECIAL_ABILITY_DEACTIVATE(player, p1);
	}

	static void LUA_NATIVE_PLAYER_SPECIAL_ABILITY_DEACTIVATE_FAST(Player player, Any p1)
	{
		PLAYER::SPECIAL_ABILITY_DEACTIVATE_FAST(player, p1);
	}

	static void LUA_NATIVE_PLAYER_SPECIAL_ABILITY_RESET(Player player, Any p1)
	{
		PLAYER::SPECIAL_ABILITY_RESET(player, p1);
	}

	static void LUA_NATIVE_PLAYER_SPECIAL_ABILITY_CHARGE_ON_MISSION_FAILED(Player player, Any p1)
	{
		PLAYER::SPECIAL_ABILITY_CHARGE_ON_MISSION_FAILED(player, p1);
	}

	static void LUA_NATIVE_PLAYER_SPECIAL_ABILITY_CHARGE_SMALL(Player player, bool p1, bool p2, Any p3)
	{
		PLAYER::SPECIAL_ABILITY_CHARGE_SMALL(player, p1, p2, p3);
	}

	static void LUA_NATIVE_PLAYER_SPECIAL_ABILITY_CHARGE_MEDIUM(Player player, bool p1, bool p2, Any p3)
	{
		PLAYER::SPECIAL_ABILITY_CHARGE_MEDIUM(player, p1, p2, p3);
	}

	static void LUA_NATIVE_PLAYER_SPECIAL_ABILITY_CHARGE_LARGE(Player player, bool p1, bool p2, Any p3)
	{
		PLAYER::SPECIAL_ABILITY_CHARGE_LARGE(player, p1, p2, p3);
	}

	static void LUA_NATIVE_PLAYER_SPECIAL_ABILITY_CHARGE_CONTINUOUS(Player player, Ped p1, Any p2)
	{
		PLAYER::SPECIAL_ABILITY_CHARGE_CONTINUOUS(player, p1, p2);
	}

	static void LUA_NATIVE_PLAYER_SPECIAL_ABILITY_CHARGE_ABSOLUTE(Player player, int p1, bool p2, Any p3)
	{
		PLAYER::SPECIAL_ABILITY_CHARGE_ABSOLUTE(player, p1, p2, p3);
	}

	static void LUA_NATIVE_PLAYER_SPECIAL_ABILITY_CHARGE_NORMALIZED(Player player, float normalizedValue, bool p2, Any p3)
	{
		PLAYER::SPECIAL_ABILITY_CHARGE_NORMALIZED(player, normalizedValue, p2, p3);
	}

	static void LUA_NATIVE_PLAYER_SPECIAL_ABILITY_FILL_METER(Player player, bool p1, Any p2)
	{
		PLAYER::SPECIAL_ABILITY_FILL_METER(player, p1, p2);
	}

	static void LUA_NATIVE_PLAYER_SPECIAL_ABILITY_DEPLETE_METER(Player player, bool p1, Any p2)
	{
		PLAYER::SPECIAL_ABILITY_DEPLETE_METER(player, p1, p2);
	}

	static void LUA_NATIVE_PLAYER_SPECIAL_ABILITY_LOCK(Hash playerModel, Any p1)
	{
		PLAYER::SPECIAL_ABILITY_LOCK(playerModel, p1);
	}

	static void LUA_NATIVE_PLAYER_SPECIAL_ABILITY_UNLOCK(Hash playerModel, Any p1)
	{
		PLAYER::SPECIAL_ABILITY_UNLOCK(playerModel, p1);
	}

	static bool LUA_NATIVE_PLAYER_IS_SPECIAL_ABILITY_UNLOCKED(Hash playerModel)
	{
		auto retval = (bool)PLAYER::IS_SPECIAL_ABILITY_UNLOCKED(playerModel);
		return retval;
	}

	static bool LUA_NATIVE_PLAYER_IS_SPECIAL_ABILITY_ACTIVE(Player player, Any p1)
	{
		auto retval = (bool)PLAYER::IS_SPECIAL_ABILITY_ACTIVE(player, p1);
		return retval;
	}

	static bool LUA_NATIVE_PLAYER_IS_SPECIAL_ABILITY_METER_FULL(Player player, Any p1)
	{
		auto retval = (bool)PLAYER::IS_SPECIAL_ABILITY_METER_FULL(player, p1);
		return retval;
	}

	static void LUA_NATIVE_PLAYER_ENABLE_SPECIAL_ABILITY(Player player, bool toggle, Any p2)
	{
		PLAYER::ENABLE_SPECIAL_ABILITY(player, toggle, p2);
	}

	static bool LUA_NATIVE_PLAYER_IS_SPECIAL_ABILITY_ENABLED(Player player, Any p1)
	{
		auto retval = (bool)PLAYER::IS_SPECIAL_ABILITY_ENABLED(player, p1);
		return retval;
	}

	static void LUA_NATIVE_PLAYER_SET_SPECIAL_ABILITY_MULTIPLIER(float multiplier)
	{
		PLAYER::SET_SPECIAL_ABILITY_MULTIPLIER(multiplier);
	}

	static void LUA_NATIVE_PLAYER_UPDATE_SPECIAL_ABILITY_FROM_STAT(Player player, Any p1)
	{
		PLAYER::UPDATE_SPECIAL_ABILITY_FROM_STAT(player, p1);
	}

	static bool LUA_NATIVE_PLAYER_GET_IS_PLAYER_DRIVING_ON_HIGHWAY(Player player)
	{
		auto retval = (bool)PLAYER::GET_IS_PLAYER_DRIVING_ON_HIGHWAY(player);
		return retval;
	}

	static bool LUA_NATIVE_PLAYER_GET_IS_PLAYER_DRIVING_WRECKLESS(Player player, int p1)
	{
		auto retval = (bool)PLAYER::GET_IS_PLAYER_DRIVING_WRECKLESS(player, p1);
		return retval;
	}

	static bool LUA_NATIVE_PLAYER_GET_IS_MOPPING_AREA_FREE_IN_FRONT_OF_PLAYER(Player player, float p1)
	{
		auto retval = (bool)PLAYER::GET_IS_MOPPING_AREA_FREE_IN_FRONT_OF_PLAYER(player, p1);
		return retval;
	}

	static void LUA_NATIVE_PLAYER_START_PLAYER_TELEPORT(Player player, float x, float y, float z, float heading, bool p5, bool findCollisionLand, bool p7)
	{
		PLAYER::START_PLAYER_TELEPORT(player, x, y, z, heading, p5, findCollisionLand, p7);
	}

	static bool LUA_NATIVE_PLAYER_UPDATE_PLAYER_TELEPORT(Player player)
	{
		auto retval = (bool)PLAYER::UPDATE_PLAYER_TELEPORT(player);
		return retval;
	}

	static void LUA_NATIVE_PLAYER_STOP_PLAYER_TELEPORT()
	{
		PLAYER::STOP_PLAYER_TELEPORT();
	}

	static bool LUA_NATIVE_PLAYER_IS_PLAYER_TELEPORT_ACTIVE()
	{
		auto retval = (bool)PLAYER::IS_PLAYER_TELEPORT_ACTIVE();
		return retval;
	}

	static float LUA_NATIVE_PLAYER_GET_PLAYER_CURRENT_STEALTH_NOISE(Player player)
	{
		auto retval = PLAYER::GET_PLAYER_CURRENT_STEALTH_NOISE(player);
		return retval;
	}

	static void LUA_NATIVE_PLAYER_SET_PLAYER_HEALTH_RECHARGE_MULTIPLIER(Player player, float regenRate)
	{
		PLAYER::SET_PLAYER_HEALTH_RECHARGE_MULTIPLIER(player, regenRate);
	}

	static float LUA_NATIVE_PLAYER_GET_PLAYER_HEALTH_RECHARGE_MAX_PERCENT(Player player)
	{
		auto retval = PLAYER::GET_PLAYER_HEALTH_RECHARGE_MAX_PERCENT(player);
		return retval;
	}

	static void LUA_NATIVE_PLAYER_SET_PLAYER_HEALTH_RECHARGE_MAX_PERCENT(Player player, float limit)
	{
		PLAYER::SET_PLAYER_HEALTH_RECHARGE_MAX_PERCENT(player, limit);
	}

	static void LUA_NATIVE_PLAYER_DISABLE_PLAYER_HEALTH_RECHARGE(Player player)
	{
		PLAYER::DISABLE_PLAYER_HEALTH_RECHARGE(player);
	}

	static void LUA_NATIVE_PLAYER_SET_PLAYER_FALL_DISTANCE_TO_TRIGGER_RAGDOLL_OVERRIDE(Player player, float p1)
	{
		PLAYER::SET_PLAYER_FALL_DISTANCE_TO_TRIGGER_RAGDOLL_OVERRIDE(player, p1);
	}

	static void LUA_NATIVE_PLAYER_SET_PLAYER_WEAPON_DAMAGE_MODIFIER(Player player, float modifier)
	{
		PLAYER::SET_PLAYER_WEAPON_DAMAGE_MODIFIER(player, modifier);
	}

	static void LUA_NATIVE_PLAYER_SET_PLAYER_WEAPON_DEFENSE_MODIFIER(Player player, float modifier)
	{
		PLAYER::SET_PLAYER_WEAPON_DEFENSE_MODIFIER(player, modifier);
	}

	static void LUA_NATIVE_PLAYER_SET_PLAYER_WEAPON_MINIGUN_DEFENSE_MODIFIER(Player player, float modifier)
	{
		PLAYER::SET_PLAYER_WEAPON_MINIGUN_DEFENSE_MODIFIER(player, modifier);
	}

	static void LUA_NATIVE_PLAYER_SET_PLAYER_MELEE_WEAPON_DAMAGE_MODIFIER(Player player, float modifier, bool p2)
	{
		PLAYER::SET_PLAYER_MELEE_WEAPON_DAMAGE_MODIFIER(player, modifier, p2);
	}

	static void LUA_NATIVE_PLAYER_SET_PLAYER_MELEE_WEAPON_DEFENSE_MODIFIER(Player player, float modifier)
	{
		PLAYER::SET_PLAYER_MELEE_WEAPON_DEFENSE_MODIFIER(player, modifier);
	}

	static void LUA_NATIVE_PLAYER_SET_PLAYER_VEHICLE_DAMAGE_MODIFIER(Player player, float modifier)
	{
		PLAYER::SET_PLAYER_VEHICLE_DAMAGE_MODIFIER(player, modifier);
	}

	static void LUA_NATIVE_PLAYER_SET_PLAYER_VEHICLE_DEFENSE_MODIFIER(Player player, float modifier)
	{
		PLAYER::SET_PLAYER_VEHICLE_DEFENSE_MODIFIER(player, modifier);
	}

	static void LUA_NATIVE_PLAYER_SET_PLAYER_MAX_EXPLOSIVE_DAMAGE(Player player, float p1)
	{
		PLAYER::SET_PLAYER_MAX_EXPLOSIVE_DAMAGE(player, p1);
	}

	static void LUA_NATIVE_PLAYER_SET_PLAYER_EXPLOSIVE_DAMAGE_MODIFIER(Player player, Any p1)
	{
		PLAYER::SET_PLAYER_EXPLOSIVE_DAMAGE_MODIFIER(player, p1);
	}

	static void LUA_NATIVE_PLAYER_SET_PLAYER_WEAPON_TAKEDOWN_DEFENSE_MODIFIER(Player player, float p1)
	{
		PLAYER::SET_PLAYER_WEAPON_TAKEDOWN_DEFENSE_MODIFIER(player, p1);
	}

	static void LUA_NATIVE_PLAYER_SET_PLAYER_PARACHUTE_TINT_INDEX(Player player, int tintIndex)
	{
		PLAYER::SET_PLAYER_PARACHUTE_TINT_INDEX(player, tintIndex);
	}

	static int LUA_NATIVE_PLAYER_GET_PLAYER_PARACHUTE_TINT_INDEX(Player player, int tintIndex)
	{
		PLAYER::GET_PLAYER_PARACHUTE_TINT_INDEX(player, &tintIndex);
		return tintIndex;
	}

	static void LUA_NATIVE_PLAYER_SET_PLAYER_RESERVE_PARACHUTE_TINT_INDEX(Player player, int index)
	{
		PLAYER::SET_PLAYER_RESERVE_PARACHUTE_TINT_INDEX(player, index);
	}

	static int LUA_NATIVE_PLAYER_GET_PLAYER_RESERVE_PARACHUTE_TINT_INDEX(Player player, int index)
	{
		PLAYER::GET_PLAYER_RESERVE_PARACHUTE_TINT_INDEX(player, &index);
		return index;
	}

	static void LUA_NATIVE_PLAYER_SET_PLAYER_PARACHUTE_PACK_TINT_INDEX(Player player, int tintIndex)
	{
		PLAYER::SET_PLAYER_PARACHUTE_PACK_TINT_INDEX(player, tintIndex);
	}

	static int LUA_NATIVE_PLAYER_GET_PLAYER_PARACHUTE_PACK_TINT_INDEX(Player player, int tintIndex)
	{
		PLAYER::GET_PLAYER_PARACHUTE_PACK_TINT_INDEX(player, &tintIndex);
		return tintIndex;
	}

	static void LUA_NATIVE_PLAYER_SET_PLAYER_HAS_RESERVE_PARACHUTE(Player player)
	{
		PLAYER::SET_PLAYER_HAS_RESERVE_PARACHUTE(player);
	}

	static bool LUA_NATIVE_PLAYER_GET_PLAYER_HAS_RESERVE_PARACHUTE(Player player)
	{
		auto retval = (bool)PLAYER::GET_PLAYER_HAS_RESERVE_PARACHUTE(player);
		return retval;
	}

	static void LUA_NATIVE_PLAYER_SET_PLAYER_CAN_LEAVE_PARACHUTE_SMOKE_TRAIL(Player player, bool enabled)
	{
		PLAYER::SET_PLAYER_CAN_LEAVE_PARACHUTE_SMOKE_TRAIL(player, enabled);
	}

	static void LUA_NATIVE_PLAYER_SET_PLAYER_PARACHUTE_SMOKE_TRAIL_COLOR(Player player, int r, int g, int b)
	{
		PLAYER::SET_PLAYER_PARACHUTE_SMOKE_TRAIL_COLOR(player, r, g, b);
	}

	static std::tuple<int, int, int> LUA_NATIVE_PLAYER_GET_PLAYER_PARACHUTE_SMOKE_TRAIL_COLOR(Player player, int r, int g, int b)
	{
		std::tuple<int, int, int> return_values;
		PLAYER::GET_PLAYER_PARACHUTE_SMOKE_TRAIL_COLOR(player, &r, &g, &b);
		std::get<0>(return_values) = r;
		std::get<1>(return_values) = g;
		std::get<2>(return_values) = b;

		return return_values;
	}

	static void LUA_NATIVE_PLAYER_SET_PLAYER_PHONE_PALETTE_IDX(Player player, int flags)
	{
		PLAYER::SET_PLAYER_PHONE_PALETTE_IDX(player, flags);
	}

	static void LUA_NATIVE_PLAYER_SET_PLAYER_NOISE_MULTIPLIER(Player player, float multiplier)
	{
		PLAYER::SET_PLAYER_NOISE_MULTIPLIER(player, multiplier);
	}

	static void LUA_NATIVE_PLAYER_SET_PLAYER_SNEAKING_NOISE_MULTIPLIER(Player player, float multiplier)
	{
		PLAYER::SET_PLAYER_SNEAKING_NOISE_MULTIPLIER(player, multiplier);
	}

	static bool LUA_NATIVE_PLAYER_CAN_PED_HEAR_PLAYER(Player player, Ped ped)
	{
		auto retval = (bool)PLAYER::CAN_PED_HEAR_PLAYER(player, ped);
		return retval;
	}

	static void LUA_NATIVE_PLAYER_SIMULATE_PLAYER_INPUT_GAIT(Player player, float amount, int gaitType, float speed, bool p4, bool p5, Any p6)
	{
		PLAYER::SIMULATE_PLAYER_INPUT_GAIT(player, amount, gaitType, speed, p4, p5, p6);
	}

	static void LUA_NATIVE_PLAYER_RESET_PLAYER_INPUT_GAIT(Player player)
	{
		PLAYER::RESET_PLAYER_INPUT_GAIT(player);
	}

	static void LUA_NATIVE_PLAYER_SET_AUTO_GIVE_PARACHUTE_WHEN_ENTER_PLANE(Player player, bool toggle)
	{
		PLAYER::SET_AUTO_GIVE_PARACHUTE_WHEN_ENTER_PLANE(player, toggle);
	}

	static void LUA_NATIVE_PLAYER_SET_AUTO_GIVE_SCUBA_GEAR_WHEN_EXIT_VEHICLE(Player player, bool toggle)
	{
		PLAYER::SET_AUTO_GIVE_SCUBA_GEAR_WHEN_EXIT_VEHICLE(player, toggle);
	}

	static void LUA_NATIVE_PLAYER_SET_PLAYER_STEALTH_PERCEPTION_MODIFIER(Player player, float value)
	{
		PLAYER::SET_PLAYER_STEALTH_PERCEPTION_MODIFIER(player, value);
	}

	static bool LUA_NATIVE_PLAYER_IS_REMOTE_PLAYER_IN_NON_CLONED_VEHICLE(Player player)
	{
		auto retval = (bool)PLAYER::IS_REMOTE_PLAYER_IN_NON_CLONED_VEHICLE(player);
		return retval;
	}

	static void LUA_NATIVE_PLAYER_INCREASE_PLAYER_JUMP_SUPPRESSION_RANGE(Player player)
	{
		PLAYER::INCREASE_PLAYER_JUMP_SUPPRESSION_RANGE(player);
	}

	static void LUA_NATIVE_PLAYER_SET_PLAYER_SIMULATE_AIMING(Player player, bool toggle)
	{
		PLAYER::SET_PLAYER_SIMULATE_AIMING(player, toggle);
	}

	static void LUA_NATIVE_PLAYER_SET_PLAYER_CLOTH_PIN_FRAMES(Player player, int p1)
	{
		PLAYER::SET_PLAYER_CLOTH_PIN_FRAMES(player, p1);
	}

	static void LUA_NATIVE_PLAYER_SET_PLAYER_CLOTH_PACKAGE_INDEX(int index)
	{
		PLAYER::SET_PLAYER_CLOTH_PACKAGE_INDEX(index);
	}

	static void LUA_NATIVE_PLAYER_SET_PLAYER_CLOTH_LOCK_COUNTER(int value)
	{
		PLAYER::SET_PLAYER_CLOTH_LOCK_COUNTER(value);
	}

	static void LUA_NATIVE_PLAYER_PLAYER_ATTACH_VIRTUAL_BOUND(float p0, float p1, float p2, float p3, float p4, float p5, float p6, float p7)
	{
		PLAYER::PLAYER_ATTACH_VIRTUAL_BOUND(p0, p1, p2, p3, p4, p5, p6, p7);
	}

	static void LUA_NATIVE_PLAYER_PLAYER_DETACH_VIRTUAL_BOUND()
	{
		PLAYER::PLAYER_DETACH_VIRTUAL_BOUND();
	}

	static bool LUA_NATIVE_PLAYER_HAS_PLAYER_BEEN_SPOTTED_IN_STOLEN_VEHICLE(Player player)
	{
		auto retval = (bool)PLAYER::HAS_PLAYER_BEEN_SPOTTED_IN_STOLEN_VEHICLE(player);
		return retval;
	}

	static bool LUA_NATIVE_PLAYER_IS_PLAYER_BATTLE_AWARE(Player player)
	{
		auto retval = (bool)PLAYER::IS_PLAYER_BATTLE_AWARE(player);
		return retval;
	}

	static bool LUA_NATIVE_PLAYER_GET_PLAYER_RECEIVED_BATTLE_EVENT_RECENTLY(Player player, int p1, bool p2)
	{
		auto retval = (bool)PLAYER::GET_PLAYER_RECEIVED_BATTLE_EVENT_RECENTLY(player, p1, p2);
		return retval;
	}

	static void LUA_NATIVE_PLAYER_EXTEND_WORLD_BOUNDARY_FOR_PLAYER(float x, float y, float z)
	{
		PLAYER::EXTEND_WORLD_BOUNDARY_FOR_PLAYER(x, y, z);
	}

	static void LUA_NATIVE_PLAYER_RESET_WORLD_BOUNDARY_FOR_PLAYER()
	{
		PLAYER::RESET_WORLD_BOUNDARY_FOR_PLAYER();
	}

	static bool LUA_NATIVE_PLAYER_IS_PLAYER_RIDING_TRAIN(Player player)
	{
		auto retval = (bool)PLAYER::IS_PLAYER_RIDING_TRAIN(player);
		return retval;
	}

	static bool LUA_NATIVE_PLAYER_HAS_PLAYER_LEFT_THE_WORLD(Player player)
	{
		auto retval = (bool)PLAYER::HAS_PLAYER_LEFT_THE_WORLD(player);
		return retval;
	}

	static void LUA_NATIVE_PLAYER_SET_PLAYER_LEAVE_PED_BEHIND(Player player, bool toggle)
	{
		PLAYER::SET_PLAYER_LEAVE_PED_BEHIND(player, toggle);
	}

	static void LUA_NATIVE_PLAYER_SET_PLAYER_PARACHUTE_VARIATION_OVERRIDE(Player player, int p1, Any p2, Any p3, bool p4)
	{
		PLAYER::SET_PLAYER_PARACHUTE_VARIATION_OVERRIDE(player, p1, p2, p3, p4);
	}

	static void LUA_NATIVE_PLAYER_CLEAR_PLAYER_PARACHUTE_VARIATION_OVERRIDE(Player player)
	{
		PLAYER::CLEAR_PLAYER_PARACHUTE_VARIATION_OVERRIDE(player);
	}

	static void LUA_NATIVE_PLAYER_SET_PLAYER_PARACHUTE_MODEL_OVERRIDE(Player player, Hash model)
	{
		PLAYER::SET_PLAYER_PARACHUTE_MODEL_OVERRIDE(player, model);
	}

	static void LUA_NATIVE_PLAYER_SET_PLAYER_RESERVE_PARACHUTE_MODEL_OVERRIDE(Player player, Hash model)
	{
		PLAYER::SET_PLAYER_RESERVE_PARACHUTE_MODEL_OVERRIDE(player, model);
	}

	static Hash LUA_NATIVE_PLAYER_GET_PLAYER_PARACHUTE_MODEL_OVERRIDE(Player player)
	{
		auto retval = PLAYER::GET_PLAYER_PARACHUTE_MODEL_OVERRIDE(player);
		return retval;
	}

	static Hash LUA_NATIVE_PLAYER_GET_PLAYER_RESERVE_PARACHUTE_MODEL_OVERRIDE(Player player)
	{
		auto retval = PLAYER::GET_PLAYER_RESERVE_PARACHUTE_MODEL_OVERRIDE(player);
		return retval;
	}

	static void LUA_NATIVE_PLAYER_CLEAR_PLAYER_PARACHUTE_MODEL_OVERRIDE(Player player)
	{
		PLAYER::CLEAR_PLAYER_PARACHUTE_MODEL_OVERRIDE(player);
	}

	static void LUA_NATIVE_PLAYER_CLEAR_PLAYER_RESERVE_PARACHUTE_MODEL_OVERRIDE(Player player)
	{
		PLAYER::CLEAR_PLAYER_RESERVE_PARACHUTE_MODEL_OVERRIDE(player);
	}

	static void LUA_NATIVE_PLAYER_SET_PLAYER_PARACHUTE_PACK_MODEL_OVERRIDE(Player player, Hash model)
	{
		PLAYER::SET_PLAYER_PARACHUTE_PACK_MODEL_OVERRIDE(player, model);
	}

	static void LUA_NATIVE_PLAYER_CLEAR_PLAYER_PARACHUTE_PACK_MODEL_OVERRIDE(Player player)
	{
		PLAYER::CLEAR_PLAYER_PARACHUTE_PACK_MODEL_OVERRIDE(player);
	}

	static void LUA_NATIVE_PLAYER_DISABLE_PLAYER_VEHICLE_REWARDS(Player player)
	{
		PLAYER::DISABLE_PLAYER_VEHICLE_REWARDS(player);
	}

	static void LUA_NATIVE_PLAYER_SET_PLAYER_SPECTATED_VEHICLE_RADIO_OVERRIDE(bool p0)
	{
		PLAYER::SET_PLAYER_SPECTATED_VEHICLE_RADIO_OVERRIDE(p0);
	}

	static void LUA_NATIVE_PLAYER_SET_PLAYER_BLUETOOTH_STATE(Player player, bool state)
	{
		PLAYER::SET_PLAYER_BLUETOOTH_STATE(player, state);
	}

	static bool LUA_NATIVE_PLAYER_IS_PLAYER_BLUETOOTH_ENABLE(Player player)
	{
		auto retval = (bool)PLAYER::IS_PLAYER_BLUETOOTH_ENABLE(player);
		return retval;
	}

	static void LUA_NATIVE_PLAYER_DISABLE_CAMERA_VIEW_MODE_CYCLE(Player player)
	{
		PLAYER::DISABLE_CAMERA_VIEW_MODE_CYCLE(player);
	}

	static int LUA_NATIVE_PLAYER_GET_PLAYER_FAKE_WANTED_LEVEL(Player player)
	{
		auto retval = PLAYER::GET_PLAYER_FAKE_WANTED_LEVEL(player);
		return retval;
	}

	static void LUA_NATIVE_PLAYER_SET_PLAYER_CAN_DAMAGE_PLAYER(Player player1, Player player2, bool toggle)
	{
		PLAYER::SET_PLAYER_CAN_DAMAGE_PLAYER(player1, player2, toggle);
	}

	static void LUA_NATIVE_PLAYER_SET_APPLY_WAYPOINT_OF_PLAYER(Player player, int hudColor)
	{
		PLAYER::SET_APPLY_WAYPOINT_OF_PLAYER(player, hudColor);
	}

	static bool LUA_NATIVE_PLAYER_IS_PLAYER_VEHICLE_WEAPON_TOGGLED_TO_NON_HOMING(Any p0)
	{
		auto retval = (bool)PLAYER::IS_PLAYER_VEHICLE_WEAPON_TOGGLED_TO_NON_HOMING(p0);
		return retval;
	}

	static void LUA_NATIVE_PLAYER_SET_PLAYER_VEHICLE_WEAPON_TO_NON_HOMING(Any p0)
	{
		PLAYER::SET_PLAYER_VEHICLE_WEAPON_TO_NON_HOMING(p0);
	}

	static void LUA_NATIVE_PLAYER_SET_PLAYER_HOMING_DISABLED_FOR_ALL_VEHICLE_WEAPONS(Any p0, Any p1)
	{
		PLAYER::SET_PLAYER_HOMING_DISABLED_FOR_ALL_VEHICLE_WEAPONS(p0, p1);
	}

	static void LUA_NATIVE_PLAYER_ADD_PLAYER_TARGETABLE_ENTITY(Player player, Entity entity)
	{
		PLAYER::ADD_PLAYER_TARGETABLE_ENTITY(player, entity);
	}

	static void LUA_NATIVE_PLAYER_REMOVE_PLAYER_TARGETABLE_ENTITY(Player player, Entity entity)
	{
		PLAYER::REMOVE_PLAYER_TARGETABLE_ENTITY(player, entity);
	}

	static void LUA_NATIVE_PLAYER_SET_PLAYER_PREVIOUS_VARIATION_DATA(Player player, int p1, int p2, Any p3, Any p4, Any p5)
	{
		PLAYER::SET_PLAYER_PREVIOUS_VARIATION_DATA(player, p1, p2, p3, p4, p5);
	}

	static void LUA_NATIVE_PLAYER_REMOVE_SCRIPT_FIRE_POSITION()
	{
		PLAYER::REMOVE_SCRIPT_FIRE_POSITION();
	}

	static void LUA_NATIVE_PLAYER_SET_SCRIPT_FIRE_POSITION(float coordX, float coordY, float coordZ)
	{
		PLAYER::SET_SCRIPT_FIRE_POSITION(coordX, coordY, coordZ);
	}

	void init_native_binding_PLAYER(sol::state& L)
	{
		auto PLAYER = L["PLAYER"].get_or_create<sol::table>();
		PLAYER.set_function("GET_PLAYER_PED", LUA_NATIVE_PLAYER_GET_PLAYER_PED);
		PLAYER.set_function("GET_PLAYER_PED_SCRIPT_INDEX", LUA_NATIVE_PLAYER_GET_PLAYER_PED_SCRIPT_INDEX);
		PLAYER.set_function("SET_PLAYER_MODEL", LUA_NATIVE_PLAYER_SET_PLAYER_MODEL);
		PLAYER.set_function("CHANGE_PLAYER_PED", LUA_NATIVE_PLAYER_CHANGE_PLAYER_PED);
		PLAYER.set_function("GET_PLAYER_RGB_COLOUR", LUA_NATIVE_PLAYER_GET_PLAYER_RGB_COLOUR);
		PLAYER.set_function("GET_NUMBER_OF_PLAYERS", LUA_NATIVE_PLAYER_GET_NUMBER_OF_PLAYERS);
		PLAYER.set_function("GET_PLAYER_TEAM", LUA_NATIVE_PLAYER_GET_PLAYER_TEAM);
		PLAYER.set_function("SET_PLAYER_TEAM", LUA_NATIVE_PLAYER_SET_PLAYER_TEAM);
		PLAYER.set_function("GET_NUMBER_OF_PLAYERS_IN_TEAM", LUA_NATIVE_PLAYER_GET_NUMBER_OF_PLAYERS_IN_TEAM);
		PLAYER.set_function("GET_PLAYER_NAME", LUA_NATIVE_PLAYER_GET_PLAYER_NAME);
		PLAYER.set_function("GET_WANTED_LEVEL_RADIUS", LUA_NATIVE_PLAYER_GET_WANTED_LEVEL_RADIUS);
		PLAYER.set_function("GET_PLAYER_WANTED_CENTRE_POSITION", LUA_NATIVE_PLAYER_GET_PLAYER_WANTED_CENTRE_POSITION);
		PLAYER.set_function("SET_PLAYER_WANTED_CENTRE_POSITION", LUA_NATIVE_PLAYER_SET_PLAYER_WANTED_CENTRE_POSITION);
		PLAYER.set_function("GET_WANTED_LEVEL_THRESHOLD", LUA_NATIVE_PLAYER_GET_WANTED_LEVEL_THRESHOLD);
		PLAYER.set_function("SET_PLAYER_WANTED_LEVEL", LUA_NATIVE_PLAYER_SET_PLAYER_WANTED_LEVEL);
		PLAYER.set_function("SET_PLAYER_WANTED_LEVEL_NO_DROP", LUA_NATIVE_PLAYER_SET_PLAYER_WANTED_LEVEL_NO_DROP);
		PLAYER.set_function("SET_PLAYER_WANTED_LEVEL_NOW", LUA_NATIVE_PLAYER_SET_PLAYER_WANTED_LEVEL_NOW);
		PLAYER.set_function("ARE_PLAYER_FLASHING_STARS_ABOUT_TO_DROP", LUA_NATIVE_PLAYER_ARE_PLAYER_FLASHING_STARS_ABOUT_TO_DROP);
		PLAYER.set_function("ARE_PLAYER_STARS_GREYED_OUT", LUA_NATIVE_PLAYER_ARE_PLAYER_STARS_GREYED_OUT);
		PLAYER.set_function("IS_WANTED_AND_HAS_BEEN_SEEN_BY_COPS", LUA_NATIVE_PLAYER_IS_WANTED_AND_HAS_BEEN_SEEN_BY_COPS);
		PLAYER.set_function("SET_DISPATCH_COPS_FOR_PLAYER", LUA_NATIVE_PLAYER_SET_DISPATCH_COPS_FOR_PLAYER);
		PLAYER.set_function("IS_PLAYER_WANTED_LEVEL_GREATER", LUA_NATIVE_PLAYER_IS_PLAYER_WANTED_LEVEL_GREATER);
		PLAYER.set_function("CLEAR_PLAYER_WANTED_LEVEL", LUA_NATIVE_PLAYER_CLEAR_PLAYER_WANTED_LEVEL);
		PLAYER.set_function("IS_PLAYER_DEAD", LUA_NATIVE_PLAYER_IS_PLAYER_DEAD);
		PLAYER.set_function("IS_PLAYER_PRESSING_HORN", LUA_NATIVE_PLAYER_IS_PLAYER_PRESSING_HORN);
		PLAYER.set_function("SET_PLAYER_CONTROL", LUA_NATIVE_PLAYER_SET_PLAYER_CONTROL);
		PLAYER.set_function("GET_PLAYER_WANTED_LEVEL", LUA_NATIVE_PLAYER_GET_PLAYER_WANTED_LEVEL);
		PLAYER.set_function("SET_MAX_WANTED_LEVEL", LUA_NATIVE_PLAYER_SET_MAX_WANTED_LEVEL);
		PLAYER.set_function("SET_POLICE_RADAR_BLIPS", LUA_NATIVE_PLAYER_SET_POLICE_RADAR_BLIPS);
		PLAYER.set_function("SET_POLICE_IGNORE_PLAYER", LUA_NATIVE_PLAYER_SET_POLICE_IGNORE_PLAYER);
		PLAYER.set_function("IS_PLAYER_PLAYING", LUA_NATIVE_PLAYER_IS_PLAYER_PLAYING);
		PLAYER.set_function("SET_EVERYONE_IGNORE_PLAYER", LUA_NATIVE_PLAYER_SET_EVERYONE_IGNORE_PLAYER);
		PLAYER.set_function("SET_ALL_RANDOM_PEDS_FLEE", LUA_NATIVE_PLAYER_SET_ALL_RANDOM_PEDS_FLEE);
		PLAYER.set_function("SET_ALL_RANDOM_PEDS_FLEE_THIS_FRAME", LUA_NATIVE_PLAYER_SET_ALL_RANDOM_PEDS_FLEE_THIS_FRAME);
		PLAYER.set_function("SET_ALL_NEUTRAL_RANDOM_PEDS_FLEE", LUA_NATIVE_PLAYER_SET_ALL_NEUTRAL_RANDOM_PEDS_FLEE);
		PLAYER.set_function("SET_ALL_NEUTRAL_RANDOM_PEDS_FLEE_THIS_FRAME", LUA_NATIVE_PLAYER_SET_ALL_NEUTRAL_RANDOM_PEDS_FLEE_THIS_FRAME);
		PLAYER.set_function("SET_LAW_PEDS_CAN_ATTACK_NON_WANTED_PLAYER_THIS_FRAME", LUA_NATIVE_PLAYER_SET_LAW_PEDS_CAN_ATTACK_NON_WANTED_PLAYER_THIS_FRAME);
		PLAYER.set_function("SET_IGNORE_LOW_PRIORITY_SHOCKING_EVENTS", LUA_NATIVE_PLAYER_SET_IGNORE_LOW_PRIORITY_SHOCKING_EVENTS);
		PLAYER.set_function("SET_WANTED_LEVEL_MULTIPLIER", LUA_NATIVE_PLAYER_SET_WANTED_LEVEL_MULTIPLIER);
		PLAYER.set_function("SET_WANTED_LEVEL_DIFFICULTY", LUA_NATIVE_PLAYER_SET_WANTED_LEVEL_DIFFICULTY);
		PLAYER.set_function("RESET_WANTED_LEVEL_DIFFICULTY", LUA_NATIVE_PLAYER_RESET_WANTED_LEVEL_DIFFICULTY);
		PLAYER.set_function("GET_WANTED_LEVEL_TIME_TO_ESCAPE", LUA_NATIVE_PLAYER_GET_WANTED_LEVEL_TIME_TO_ESCAPE);
		PLAYER.set_function("SET_WANTED_LEVEL_HIDDEN_ESCAPE_TIME", LUA_NATIVE_PLAYER_SET_WANTED_LEVEL_HIDDEN_ESCAPE_TIME);
		PLAYER.set_function("RESET_WANTED_LEVEL_HIDDEN_ESCAPE_TIME", LUA_NATIVE_PLAYER_RESET_WANTED_LEVEL_HIDDEN_ESCAPE_TIME);
		PLAYER.set_function("START_FIRING_AMNESTY", LUA_NATIVE_PLAYER_START_FIRING_AMNESTY);
		PLAYER.set_function("REPORT_CRIME", LUA_NATIVE_PLAYER_REPORT_CRIME);
		PLAYER.set_function("SUPPRESS_CRIME_THIS_FRAME", LUA_NATIVE_PLAYER_SUPPRESS_CRIME_THIS_FRAME);
		PLAYER.set_function("UPDATE_WANTED_POSITION_THIS_FRAME", LUA_NATIVE_PLAYER_UPDATE_WANTED_POSITION_THIS_FRAME);
		PLAYER.set_function("SUPPRESS_LOSING_WANTED_LEVEL_IF_HIDDEN_THIS_FRAME", LUA_NATIVE_PLAYER_SUPPRESS_LOSING_WANTED_LEVEL_IF_HIDDEN_THIS_FRAME);
		PLAYER.set_function("ALLOW_EVASION_HUD_IF_DISABLING_HIDDEN_EVASION_THIS_FRAME", LUA_NATIVE_PLAYER_ALLOW_EVASION_HUD_IF_DISABLING_HIDDEN_EVASION_THIS_FRAME);
		PLAYER.set_function("FORCE_START_HIDDEN_EVASION", LUA_NATIVE_PLAYER_FORCE_START_HIDDEN_EVASION);
		PLAYER.set_function("SUPPRESS_WITNESSES_CALLING_POLICE_THIS_FRAME", LUA_NATIVE_PLAYER_SUPPRESS_WITNESSES_CALLING_POLICE_THIS_FRAME);
		PLAYER.set_function("REPORT_POLICE_SPOTTED_PLAYER", LUA_NATIVE_PLAYER_REPORT_POLICE_SPOTTED_PLAYER);
		PLAYER.set_function("SET_LAW_RESPONSE_DELAY_OVERRIDE", LUA_NATIVE_PLAYER_SET_LAW_RESPONSE_DELAY_OVERRIDE);
		PLAYER.set_function("RESET_LAW_RESPONSE_DELAY_OVERRIDE", LUA_NATIVE_PLAYER_RESET_LAW_RESPONSE_DELAY_OVERRIDE);
		PLAYER.set_function("CAN_PLAYER_START_MISSION", LUA_NATIVE_PLAYER_CAN_PLAYER_START_MISSION);
		PLAYER.set_function("IS_PLAYER_READY_FOR_CUTSCENE", LUA_NATIVE_PLAYER_IS_PLAYER_READY_FOR_CUTSCENE);
		PLAYER.set_function("IS_PLAYER_TARGETTING_ENTITY", LUA_NATIVE_PLAYER_IS_PLAYER_TARGETTING_ENTITY);
		PLAYER.set_function("GET_PLAYER_TARGET_ENTITY", LUA_NATIVE_PLAYER_GET_PLAYER_TARGET_ENTITY);
		PLAYER.set_function("IS_PLAYER_FREE_AIMING", LUA_NATIVE_PLAYER_IS_PLAYER_FREE_AIMING);
		PLAYER.set_function("IS_PLAYER_FREE_AIMING_AT_ENTITY", LUA_NATIVE_PLAYER_IS_PLAYER_FREE_AIMING_AT_ENTITY);
		PLAYER.set_function("GET_ENTITY_PLAYER_IS_FREE_AIMING_AT", LUA_NATIVE_PLAYER_GET_ENTITY_PLAYER_IS_FREE_AIMING_AT);
		PLAYER.set_function("SET_PLAYER_LOCKON_RANGE_OVERRIDE", LUA_NATIVE_PLAYER_SET_PLAYER_LOCKON_RANGE_OVERRIDE);
		PLAYER.set_function("SET_PLAYER_CAN_DO_DRIVE_BY", LUA_NATIVE_PLAYER_SET_PLAYER_CAN_DO_DRIVE_BY);
		PLAYER.set_function("SET_PLAYER_CAN_BE_HASSLED_BY_GANGS", LUA_NATIVE_PLAYER_SET_PLAYER_CAN_BE_HASSLED_BY_GANGS);
		PLAYER.set_function("SET_PLAYER_CAN_USE_COVER", LUA_NATIVE_PLAYER_SET_PLAYER_CAN_USE_COVER);
		PLAYER.set_function("GET_MAX_WANTED_LEVEL", LUA_NATIVE_PLAYER_GET_MAX_WANTED_LEVEL);
		PLAYER.set_function("IS_PLAYER_TARGETTING_ANYTHING", LUA_NATIVE_PLAYER_IS_PLAYER_TARGETTING_ANYTHING);
		PLAYER.set_function("SET_PLAYER_SPRINT", LUA_NATIVE_PLAYER_SET_PLAYER_SPRINT);
		PLAYER.set_function("RESET_PLAYER_STAMINA", LUA_NATIVE_PLAYER_RESET_PLAYER_STAMINA);
		PLAYER.set_function("RESTORE_PLAYER_STAMINA", LUA_NATIVE_PLAYER_RESTORE_PLAYER_STAMINA);
		PLAYER.set_function("GET_PLAYER_SPRINT_STAMINA_REMAINING", LUA_NATIVE_PLAYER_GET_PLAYER_SPRINT_STAMINA_REMAINING);
		PLAYER.set_function("GET_PLAYER_SPRINT_TIME_REMAINING", LUA_NATIVE_PLAYER_GET_PLAYER_SPRINT_TIME_REMAINING);
		PLAYER.set_function("GET_PLAYER_UNDERWATER_TIME_REMAINING", LUA_NATIVE_PLAYER_GET_PLAYER_UNDERWATER_TIME_REMAINING);
		PLAYER.set_function("SET_PLAYER_UNDERWATER_BREATH_PERCENT_REMAINING", LUA_NATIVE_PLAYER_SET_PLAYER_UNDERWATER_BREATH_PERCENT_REMAINING);
		PLAYER.set_function("GET_PLAYER_GROUP", LUA_NATIVE_PLAYER_GET_PLAYER_GROUP);
		PLAYER.set_function("GET_PLAYER_MAX_ARMOUR", LUA_NATIVE_PLAYER_GET_PLAYER_MAX_ARMOUR);
		PLAYER.set_function("IS_PLAYER_CONTROL_ON", LUA_NATIVE_PLAYER_IS_PLAYER_CONTROL_ON);
		PLAYER.set_function("GET_ARE_CAMERA_CONTROLS_DISABLED", LUA_NATIVE_PLAYER_GET_ARE_CAMERA_CONTROLS_DISABLED);
		PLAYER.set_function("IS_PLAYER_SCRIPT_CONTROL_ON", LUA_NATIVE_PLAYER_IS_PLAYER_SCRIPT_CONTROL_ON);
		PLAYER.set_function("IS_PLAYER_CLIMBING", LUA_NATIVE_PLAYER_IS_PLAYER_CLIMBING);
		PLAYER.set_function("IS_PLAYER_BEING_ARRESTED", LUA_NATIVE_PLAYER_IS_PLAYER_BEING_ARRESTED);
		PLAYER.set_function("RESET_PLAYER_ARREST_STATE", LUA_NATIVE_PLAYER_RESET_PLAYER_ARREST_STATE);
		PLAYER.set_function("GET_PLAYERS_LAST_VEHICLE", LUA_NATIVE_PLAYER_GET_PLAYERS_LAST_VEHICLE);
		PLAYER.set_function("GET_PLAYER_INDEX", LUA_NATIVE_PLAYER_GET_PLAYER_INDEX);
		PLAYER.set_function("INT_TO_PLAYERINDEX", LUA_NATIVE_PLAYER_INT_TO_PLAYERINDEX);
		PLAYER.set_function("INT_TO_PARTICIPANTINDEX", LUA_NATIVE_PLAYER_INT_TO_PARTICIPANTINDEX);
		PLAYER.set_function("GET_TIME_SINCE_PLAYER_HIT_VEHICLE", LUA_NATIVE_PLAYER_GET_TIME_SINCE_PLAYER_HIT_VEHICLE);
		PLAYER.set_function("GET_TIME_SINCE_PLAYER_HIT_PED", LUA_NATIVE_PLAYER_GET_TIME_SINCE_PLAYER_HIT_PED);
		PLAYER.set_function("GET_TIME_SINCE_PLAYER_DROVE_ON_PAVEMENT", LUA_NATIVE_PLAYER_GET_TIME_SINCE_PLAYER_DROVE_ON_PAVEMENT);
		PLAYER.set_function("GET_TIME_SINCE_PLAYER_DROVE_AGAINST_TRAFFIC", LUA_NATIVE_PLAYER_GET_TIME_SINCE_PLAYER_DROVE_AGAINST_TRAFFIC);
		PLAYER.set_function("IS_PLAYER_FREE_FOR_AMBIENT_TASK", LUA_NATIVE_PLAYER_IS_PLAYER_FREE_FOR_AMBIENT_TASK);
		PLAYER.set_function("PLAYER_ID", LUA_NATIVE_PLAYER_PLAYER_ID);
		PLAYER.set_function("PLAYER_PED_ID", LUA_NATIVE_PLAYER_PLAYER_PED_ID);
		PLAYER.set_function("NETWORK_PLAYER_ID_TO_INT", LUA_NATIVE_PLAYER_NETWORK_PLAYER_ID_TO_INT);
		PLAYER.set_function("HAS_FORCE_CLEANUP_OCCURRED", LUA_NATIVE_PLAYER_HAS_FORCE_CLEANUP_OCCURRED);
		PLAYER.set_function("FORCE_CLEANUP", LUA_NATIVE_PLAYER_FORCE_CLEANUP);
		PLAYER.set_function("FORCE_CLEANUP_FOR_ALL_THREADS_WITH_THIS_NAME", LUA_NATIVE_PLAYER_FORCE_CLEANUP_FOR_ALL_THREADS_WITH_THIS_NAME);
		PLAYER.set_function("FORCE_CLEANUP_FOR_THREAD_WITH_THIS_ID", LUA_NATIVE_PLAYER_FORCE_CLEANUP_FOR_THREAD_WITH_THIS_ID);
		PLAYER.set_function("GET_CAUSE_OF_MOST_RECENT_FORCE_CLEANUP", LUA_NATIVE_PLAYER_GET_CAUSE_OF_MOST_RECENT_FORCE_CLEANUP);
		PLAYER.set_function("SET_PLAYER_MAY_ONLY_ENTER_THIS_VEHICLE", LUA_NATIVE_PLAYER_SET_PLAYER_MAY_ONLY_ENTER_THIS_VEHICLE);
		PLAYER.set_function("SET_PLAYER_MAY_NOT_ENTER_ANY_VEHICLE", LUA_NATIVE_PLAYER_SET_PLAYER_MAY_NOT_ENTER_ANY_VEHICLE);
		PLAYER.set_function("GIVE_ACHIEVEMENT_TO_PLAYER", LUA_NATIVE_PLAYER_GIVE_ACHIEVEMENT_TO_PLAYER);
		PLAYER.set_function("SET_ACHIEVEMENT_PROGRESS", LUA_NATIVE_PLAYER_SET_ACHIEVEMENT_PROGRESS);
		PLAYER.set_function("GET_ACHIEVEMENT_PROGRESS", LUA_NATIVE_PLAYER_GET_ACHIEVEMENT_PROGRESS);
		PLAYER.set_function("HAS_ACHIEVEMENT_BEEN_PASSED", LUA_NATIVE_PLAYER_HAS_ACHIEVEMENT_BEEN_PASSED);
		PLAYER.set_function("IS_PLAYER_ONLINE", LUA_NATIVE_PLAYER_IS_PLAYER_ONLINE);
		PLAYER.set_function("IS_PLAYER_LOGGING_IN_NP", LUA_NATIVE_PLAYER_IS_PLAYER_LOGGING_IN_NP);
		PLAYER.set_function("DISPLAY_SYSTEM_SIGNIN_UI", LUA_NATIVE_PLAYER_DISPLAY_SYSTEM_SIGNIN_UI);
		PLAYER.set_function("IS_SYSTEM_UI_BEING_DISPLAYED", LUA_NATIVE_PLAYER_IS_SYSTEM_UI_BEING_DISPLAYED);
		PLAYER.set_function("SET_PLAYER_INVINCIBLE", LUA_NATIVE_PLAYER_SET_PLAYER_INVINCIBLE);
		PLAYER.set_function("GET_PLAYER_INVINCIBLE", LUA_NATIVE_PLAYER_GET_PLAYER_INVINCIBLE);
		PLAYER.set_function("GET_PLAYER_DEBUG_INVINCIBLE", LUA_NATIVE_PLAYER_GET_PLAYER_DEBUG_INVINCIBLE);
		PLAYER.set_function("SET_PLAYER_INVINCIBLE_BUT_HAS_REACTIONS", LUA_NATIVE_PLAYER_SET_PLAYER_INVINCIBLE_BUT_HAS_REACTIONS);
		PLAYER.set_function("SET_PLAYER_CAN_COLLECT_DROPPED_MONEY", LUA_NATIVE_PLAYER_SET_PLAYER_CAN_COLLECT_DROPPED_MONEY);
		PLAYER.set_function("REMOVE_PLAYER_HELMET", LUA_NATIVE_PLAYER_REMOVE_PLAYER_HELMET);
		PLAYER.set_function("GIVE_PLAYER_RAGDOLL_CONTROL", LUA_NATIVE_PLAYER_GIVE_PLAYER_RAGDOLL_CONTROL);
		PLAYER.set_function("SET_PLAYER_LOCKON", LUA_NATIVE_PLAYER_SET_PLAYER_LOCKON);
		PLAYER.set_function("SET_PLAYER_TARGETING_MODE", LUA_NATIVE_PLAYER_SET_PLAYER_TARGETING_MODE);
		PLAYER.set_function("SET_PLAYER_TARGET_LEVEL", LUA_NATIVE_PLAYER_SET_PLAYER_TARGET_LEVEL);
		PLAYER.set_function("GET_IS_USING_FPS_THIRD_PERSON_COVER", LUA_NATIVE_PLAYER_GET_IS_USING_FPS_THIRD_PERSON_COVER);
		PLAYER.set_function("GET_IS_USING_HOOD_CAMERA", LUA_NATIVE_PLAYER_GET_IS_USING_HOOD_CAMERA);
		PLAYER.set_function("CLEAR_PLAYER_HAS_DAMAGED_AT_LEAST_ONE_PED", LUA_NATIVE_PLAYER_CLEAR_PLAYER_HAS_DAMAGED_AT_LEAST_ONE_PED);
		PLAYER.set_function("HAS_PLAYER_DAMAGED_AT_LEAST_ONE_PED", LUA_NATIVE_PLAYER_HAS_PLAYER_DAMAGED_AT_LEAST_ONE_PED);
		PLAYER.set_function("CLEAR_PLAYER_HAS_DAMAGED_AT_LEAST_ONE_NON_ANIMAL_PED", LUA_NATIVE_PLAYER_CLEAR_PLAYER_HAS_DAMAGED_AT_LEAST_ONE_NON_ANIMAL_PED);
		PLAYER.set_function("HAS_PLAYER_DAMAGED_AT_LEAST_ONE_NON_ANIMAL_PED", LUA_NATIVE_PLAYER_HAS_PLAYER_DAMAGED_AT_LEAST_ONE_NON_ANIMAL_PED);
		PLAYER.set_function("SET_AIR_DRAG_MULTIPLIER_FOR_PLAYERS_VEHICLE", LUA_NATIVE_PLAYER_SET_AIR_DRAG_MULTIPLIER_FOR_PLAYERS_VEHICLE);
		PLAYER.set_function("SET_SWIM_MULTIPLIER_FOR_PLAYER", LUA_NATIVE_PLAYER_SET_SWIM_MULTIPLIER_FOR_PLAYER);
		PLAYER.set_function("SET_RUN_SPRINT_MULTIPLIER_FOR_PLAYER", LUA_NATIVE_PLAYER_SET_RUN_SPRINT_MULTIPLIER_FOR_PLAYER);
		PLAYER.set_function("GET_TIME_SINCE_LAST_ARREST", LUA_NATIVE_PLAYER_GET_TIME_SINCE_LAST_ARREST);
		PLAYER.set_function("GET_TIME_SINCE_LAST_DEATH", LUA_NATIVE_PLAYER_GET_TIME_SINCE_LAST_DEATH);
		PLAYER.set_function("ASSISTED_MOVEMENT_CLOSE_ROUTE", LUA_NATIVE_PLAYER_ASSISTED_MOVEMENT_CLOSE_ROUTE);
		PLAYER.set_function("ASSISTED_MOVEMENT_FLUSH_ROUTE", LUA_NATIVE_PLAYER_ASSISTED_MOVEMENT_FLUSH_ROUTE);
		PLAYER.set_function("SET_PLAYER_FORCED_AIM", LUA_NATIVE_PLAYER_SET_PLAYER_FORCED_AIM);
		PLAYER.set_function("SET_PLAYER_FORCED_ZOOM", LUA_NATIVE_PLAYER_SET_PLAYER_FORCED_ZOOM);
		PLAYER.set_function("SET_PLAYER_FORCE_SKIP_AIM_INTRO", LUA_NATIVE_PLAYER_SET_PLAYER_FORCE_SKIP_AIM_INTRO);
		PLAYER.set_function("DISABLE_PLAYER_FIRING", LUA_NATIVE_PLAYER_DISABLE_PLAYER_FIRING);
		PLAYER.set_function("DISABLE_PLAYER_THROW_GRENADE_WHILE_USING_GUN", LUA_NATIVE_PLAYER_DISABLE_PLAYER_THROW_GRENADE_WHILE_USING_GUN);
		PLAYER.set_function("SET_DISABLE_AMBIENT_MELEE_MOVE", LUA_NATIVE_PLAYER_SET_DISABLE_AMBIENT_MELEE_MOVE);
		PLAYER.set_function("SET_PLAYER_MAX_ARMOUR", LUA_NATIVE_PLAYER_SET_PLAYER_MAX_ARMOUR);
		PLAYER.set_function("SPECIAL_ABILITY_ACTIVATE", LUA_NATIVE_PLAYER_SPECIAL_ABILITY_ACTIVATE);
		PLAYER.set_function("SET_SPECIAL_ABILITY_MP", LUA_NATIVE_PLAYER_SET_SPECIAL_ABILITY_MP);
		PLAYER.set_function("SPECIAL_ABILITY_DEACTIVATE_MP", LUA_NATIVE_PLAYER_SPECIAL_ABILITY_DEACTIVATE_MP);
		PLAYER.set_function("SPECIAL_ABILITY_DEACTIVATE", LUA_NATIVE_PLAYER_SPECIAL_ABILITY_DEACTIVATE);
		PLAYER.set_function("SPECIAL_ABILITY_DEACTIVATE_FAST", LUA_NATIVE_PLAYER_SPECIAL_ABILITY_DEACTIVATE_FAST);
		PLAYER.set_function("SPECIAL_ABILITY_RESET", LUA_NATIVE_PLAYER_SPECIAL_ABILITY_RESET);
		PLAYER.set_function("SPECIAL_ABILITY_CHARGE_ON_MISSION_FAILED", LUA_NATIVE_PLAYER_SPECIAL_ABILITY_CHARGE_ON_MISSION_FAILED);
		PLAYER.set_function("SPECIAL_ABILITY_CHARGE_SMALL", LUA_NATIVE_PLAYER_SPECIAL_ABILITY_CHARGE_SMALL);
		PLAYER.set_function("SPECIAL_ABILITY_CHARGE_MEDIUM", LUA_NATIVE_PLAYER_SPECIAL_ABILITY_CHARGE_MEDIUM);
		PLAYER.set_function("SPECIAL_ABILITY_CHARGE_LARGE", LUA_NATIVE_PLAYER_SPECIAL_ABILITY_CHARGE_LARGE);
		PLAYER.set_function("SPECIAL_ABILITY_CHARGE_CONTINUOUS", LUA_NATIVE_PLAYER_SPECIAL_ABILITY_CHARGE_CONTINUOUS);
		PLAYER.set_function("SPECIAL_ABILITY_CHARGE_ABSOLUTE", LUA_NATIVE_PLAYER_SPECIAL_ABILITY_CHARGE_ABSOLUTE);
		PLAYER.set_function("SPECIAL_ABILITY_CHARGE_NORMALIZED", LUA_NATIVE_PLAYER_SPECIAL_ABILITY_CHARGE_NORMALIZED);
		PLAYER.set_function("SPECIAL_ABILITY_FILL_METER", LUA_NATIVE_PLAYER_SPECIAL_ABILITY_FILL_METER);
		PLAYER.set_function("SPECIAL_ABILITY_DEPLETE_METER", LUA_NATIVE_PLAYER_SPECIAL_ABILITY_DEPLETE_METER);
		PLAYER.set_function("SPECIAL_ABILITY_LOCK", LUA_NATIVE_PLAYER_SPECIAL_ABILITY_LOCK);
		PLAYER.set_function("SPECIAL_ABILITY_UNLOCK", LUA_NATIVE_PLAYER_SPECIAL_ABILITY_UNLOCK);
		PLAYER.set_function("IS_SPECIAL_ABILITY_UNLOCKED", LUA_NATIVE_PLAYER_IS_SPECIAL_ABILITY_UNLOCKED);
		PLAYER.set_function("IS_SPECIAL_ABILITY_ACTIVE", LUA_NATIVE_PLAYER_IS_SPECIAL_ABILITY_ACTIVE);
		PLAYER.set_function("IS_SPECIAL_ABILITY_METER_FULL", LUA_NATIVE_PLAYER_IS_SPECIAL_ABILITY_METER_FULL);
		PLAYER.set_function("ENABLE_SPECIAL_ABILITY", LUA_NATIVE_PLAYER_ENABLE_SPECIAL_ABILITY);
		PLAYER.set_function("IS_SPECIAL_ABILITY_ENABLED", LUA_NATIVE_PLAYER_IS_SPECIAL_ABILITY_ENABLED);
		PLAYER.set_function("SET_SPECIAL_ABILITY_MULTIPLIER", LUA_NATIVE_PLAYER_SET_SPECIAL_ABILITY_MULTIPLIER);
		PLAYER.set_function("UPDATE_SPECIAL_ABILITY_FROM_STAT", LUA_NATIVE_PLAYER_UPDATE_SPECIAL_ABILITY_FROM_STAT);
		PLAYER.set_function("GET_IS_PLAYER_DRIVING_ON_HIGHWAY", LUA_NATIVE_PLAYER_GET_IS_PLAYER_DRIVING_ON_HIGHWAY);
		PLAYER.set_function("GET_IS_PLAYER_DRIVING_WRECKLESS", LUA_NATIVE_PLAYER_GET_IS_PLAYER_DRIVING_WRECKLESS);
		PLAYER.set_function("GET_IS_MOPPING_AREA_FREE_IN_FRONT_OF_PLAYER", LUA_NATIVE_PLAYER_GET_IS_MOPPING_AREA_FREE_IN_FRONT_OF_PLAYER);
		PLAYER.set_function("START_PLAYER_TELEPORT", LUA_NATIVE_PLAYER_START_PLAYER_TELEPORT);
		PLAYER.set_function("UPDATE_PLAYER_TELEPORT", LUA_NATIVE_PLAYER_UPDATE_PLAYER_TELEPORT);
		PLAYER.set_function("STOP_PLAYER_TELEPORT", LUA_NATIVE_PLAYER_STOP_PLAYER_TELEPORT);
		PLAYER.set_function("IS_PLAYER_TELEPORT_ACTIVE", LUA_NATIVE_PLAYER_IS_PLAYER_TELEPORT_ACTIVE);
		PLAYER.set_function("GET_PLAYER_CURRENT_STEALTH_NOISE", LUA_NATIVE_PLAYER_GET_PLAYER_CURRENT_STEALTH_NOISE);
		PLAYER.set_function("SET_PLAYER_HEALTH_RECHARGE_MULTIPLIER", LUA_NATIVE_PLAYER_SET_PLAYER_HEALTH_RECHARGE_MULTIPLIER);
		PLAYER.set_function("GET_PLAYER_HEALTH_RECHARGE_MAX_PERCENT", LUA_NATIVE_PLAYER_GET_PLAYER_HEALTH_RECHARGE_MAX_PERCENT);
		PLAYER.set_function("SET_PLAYER_HEALTH_RECHARGE_MAX_PERCENT", LUA_NATIVE_PLAYER_SET_PLAYER_HEALTH_RECHARGE_MAX_PERCENT);
		PLAYER.set_function("DISABLE_PLAYER_HEALTH_RECHARGE", LUA_NATIVE_PLAYER_DISABLE_PLAYER_HEALTH_RECHARGE);
		PLAYER.set_function("SET_PLAYER_FALL_DISTANCE_TO_TRIGGER_RAGDOLL_OVERRIDE", LUA_NATIVE_PLAYER_SET_PLAYER_FALL_DISTANCE_TO_TRIGGER_RAGDOLL_OVERRIDE);
		PLAYER.set_function("SET_PLAYER_WEAPON_DAMAGE_MODIFIER", LUA_NATIVE_PLAYER_SET_PLAYER_WEAPON_DAMAGE_MODIFIER);
		PLAYER.set_function("SET_PLAYER_WEAPON_DEFENSE_MODIFIER", LUA_NATIVE_PLAYER_SET_PLAYER_WEAPON_DEFENSE_MODIFIER);
		PLAYER.set_function("SET_PLAYER_WEAPON_MINIGUN_DEFENSE_MODIFIER", LUA_NATIVE_PLAYER_SET_PLAYER_WEAPON_MINIGUN_DEFENSE_MODIFIER);
		PLAYER.set_function("SET_PLAYER_MELEE_WEAPON_DAMAGE_MODIFIER", LUA_NATIVE_PLAYER_SET_PLAYER_MELEE_WEAPON_DAMAGE_MODIFIER);
		PLAYER.set_function("SET_PLAYER_MELEE_WEAPON_DEFENSE_MODIFIER", LUA_NATIVE_PLAYER_SET_PLAYER_MELEE_WEAPON_DEFENSE_MODIFIER);
		PLAYER.set_function("SET_PLAYER_VEHICLE_DAMAGE_MODIFIER", LUA_NATIVE_PLAYER_SET_PLAYER_VEHICLE_DAMAGE_MODIFIER);
		PLAYER.set_function("SET_PLAYER_VEHICLE_DEFENSE_MODIFIER", LUA_NATIVE_PLAYER_SET_PLAYER_VEHICLE_DEFENSE_MODIFIER);
		PLAYER.set_function("SET_PLAYER_MAX_EXPLOSIVE_DAMAGE", LUA_NATIVE_PLAYER_SET_PLAYER_MAX_EXPLOSIVE_DAMAGE);
		PLAYER.set_function("SET_PLAYER_EXPLOSIVE_DAMAGE_MODIFIER", LUA_NATIVE_PLAYER_SET_PLAYER_EXPLOSIVE_DAMAGE_MODIFIER);
		PLAYER.set_function("SET_PLAYER_WEAPON_TAKEDOWN_DEFENSE_MODIFIER", LUA_NATIVE_PLAYER_SET_PLAYER_WEAPON_TAKEDOWN_DEFENSE_MODIFIER);
		PLAYER.set_function("SET_PLAYER_PARACHUTE_TINT_INDEX", LUA_NATIVE_PLAYER_SET_PLAYER_PARACHUTE_TINT_INDEX);
		PLAYER.set_function("GET_PLAYER_PARACHUTE_TINT_INDEX", LUA_NATIVE_PLAYER_GET_PLAYER_PARACHUTE_TINT_INDEX);
		PLAYER.set_function("SET_PLAYER_RESERVE_PARACHUTE_TINT_INDEX", LUA_NATIVE_PLAYER_SET_PLAYER_RESERVE_PARACHUTE_TINT_INDEX);
		PLAYER.set_function("GET_PLAYER_RESERVE_PARACHUTE_TINT_INDEX", LUA_NATIVE_PLAYER_GET_PLAYER_RESERVE_PARACHUTE_TINT_INDEX);
		PLAYER.set_function("SET_PLAYER_PARACHUTE_PACK_TINT_INDEX", LUA_NATIVE_PLAYER_SET_PLAYER_PARACHUTE_PACK_TINT_INDEX);
		PLAYER.set_function("GET_PLAYER_PARACHUTE_PACK_TINT_INDEX", LUA_NATIVE_PLAYER_GET_PLAYER_PARACHUTE_PACK_TINT_INDEX);
		PLAYER.set_function("SET_PLAYER_HAS_RESERVE_PARACHUTE", LUA_NATIVE_PLAYER_SET_PLAYER_HAS_RESERVE_PARACHUTE);
		PLAYER.set_function("GET_PLAYER_HAS_RESERVE_PARACHUTE", LUA_NATIVE_PLAYER_GET_PLAYER_HAS_RESERVE_PARACHUTE);
		PLAYER.set_function("SET_PLAYER_CAN_LEAVE_PARACHUTE_SMOKE_TRAIL", LUA_NATIVE_PLAYER_SET_PLAYER_CAN_LEAVE_PARACHUTE_SMOKE_TRAIL);
		PLAYER.set_function("SET_PLAYER_PARACHUTE_SMOKE_TRAIL_COLOR", LUA_NATIVE_PLAYER_SET_PLAYER_PARACHUTE_SMOKE_TRAIL_COLOR);
		PLAYER.set_function("GET_PLAYER_PARACHUTE_SMOKE_TRAIL_COLOR", LUA_NATIVE_PLAYER_GET_PLAYER_PARACHUTE_SMOKE_TRAIL_COLOR);
		PLAYER.set_function("SET_PLAYER_PHONE_PALETTE_IDX", LUA_NATIVE_PLAYER_SET_PLAYER_PHONE_PALETTE_IDX);
		PLAYER.set_function("SET_PLAYER_NOISE_MULTIPLIER", LUA_NATIVE_PLAYER_SET_PLAYER_NOISE_MULTIPLIER);
		PLAYER.set_function("SET_PLAYER_SNEAKING_NOISE_MULTIPLIER", LUA_NATIVE_PLAYER_SET_PLAYER_SNEAKING_NOISE_MULTIPLIER);
		PLAYER.set_function("CAN_PED_HEAR_PLAYER", LUA_NATIVE_PLAYER_CAN_PED_HEAR_PLAYER);
		PLAYER.set_function("SIMULATE_PLAYER_INPUT_GAIT", LUA_NATIVE_PLAYER_SIMULATE_PLAYER_INPUT_GAIT);
		PLAYER.set_function("RESET_PLAYER_INPUT_GAIT", LUA_NATIVE_PLAYER_RESET_PLAYER_INPUT_GAIT);
		PLAYER.set_function("SET_AUTO_GIVE_PARACHUTE_WHEN_ENTER_PLANE", LUA_NATIVE_PLAYER_SET_AUTO_GIVE_PARACHUTE_WHEN_ENTER_PLANE);
		PLAYER.set_function("SET_AUTO_GIVE_SCUBA_GEAR_WHEN_EXIT_VEHICLE", LUA_NATIVE_PLAYER_SET_AUTO_GIVE_SCUBA_GEAR_WHEN_EXIT_VEHICLE);
		PLAYER.set_function("SET_PLAYER_STEALTH_PERCEPTION_MODIFIER", LUA_NATIVE_PLAYER_SET_PLAYER_STEALTH_PERCEPTION_MODIFIER);
		PLAYER.set_function("IS_REMOTE_PLAYER_IN_NON_CLONED_VEHICLE", LUA_NATIVE_PLAYER_IS_REMOTE_PLAYER_IN_NON_CLONED_VEHICLE);
		PLAYER.set_function("INCREASE_PLAYER_JUMP_SUPPRESSION_RANGE", LUA_NATIVE_PLAYER_INCREASE_PLAYER_JUMP_SUPPRESSION_RANGE);
		PLAYER.set_function("SET_PLAYER_SIMULATE_AIMING", LUA_NATIVE_PLAYER_SET_PLAYER_SIMULATE_AIMING);
		PLAYER.set_function("SET_PLAYER_CLOTH_PIN_FRAMES", LUA_NATIVE_PLAYER_SET_PLAYER_CLOTH_PIN_FRAMES);
		PLAYER.set_function("SET_PLAYER_CLOTH_PACKAGE_INDEX", LUA_NATIVE_PLAYER_SET_PLAYER_CLOTH_PACKAGE_INDEX);
		PLAYER.set_function("SET_PLAYER_CLOTH_LOCK_COUNTER", LUA_NATIVE_PLAYER_SET_PLAYER_CLOTH_LOCK_COUNTER);
		PLAYER.set_function("PLAYER_ATTACH_VIRTUAL_BOUND", LUA_NATIVE_PLAYER_PLAYER_ATTACH_VIRTUAL_BOUND);
		PLAYER.set_function("PLAYER_DETACH_VIRTUAL_BOUND", LUA_NATIVE_PLAYER_PLAYER_DETACH_VIRTUAL_BOUND);
		PLAYER.set_function("HAS_PLAYER_BEEN_SPOTTED_IN_STOLEN_VEHICLE", LUA_NATIVE_PLAYER_HAS_PLAYER_BEEN_SPOTTED_IN_STOLEN_VEHICLE);
		PLAYER.set_function("IS_PLAYER_BATTLE_AWARE", LUA_NATIVE_PLAYER_IS_PLAYER_BATTLE_AWARE);
		PLAYER.set_function("GET_PLAYER_RECEIVED_BATTLE_EVENT_RECENTLY", LUA_NATIVE_PLAYER_GET_PLAYER_RECEIVED_BATTLE_EVENT_RECENTLY);
		PLAYER.set_function("EXTEND_WORLD_BOUNDARY_FOR_PLAYER", LUA_NATIVE_PLAYER_EXTEND_WORLD_BOUNDARY_FOR_PLAYER);
		PLAYER.set_function("RESET_WORLD_BOUNDARY_FOR_PLAYER", LUA_NATIVE_PLAYER_RESET_WORLD_BOUNDARY_FOR_PLAYER);
		PLAYER.set_function("IS_PLAYER_RIDING_TRAIN", LUA_NATIVE_PLAYER_IS_PLAYER_RIDING_TRAIN);
		PLAYER.set_function("HAS_PLAYER_LEFT_THE_WORLD", LUA_NATIVE_PLAYER_HAS_PLAYER_LEFT_THE_WORLD);
		PLAYER.set_function("SET_PLAYER_LEAVE_PED_BEHIND", LUA_NATIVE_PLAYER_SET_PLAYER_LEAVE_PED_BEHIND);
		PLAYER.set_function("SET_PLAYER_PARACHUTE_VARIATION_OVERRIDE", LUA_NATIVE_PLAYER_SET_PLAYER_PARACHUTE_VARIATION_OVERRIDE);
		PLAYER.set_function("CLEAR_PLAYER_PARACHUTE_VARIATION_OVERRIDE", LUA_NATIVE_PLAYER_CLEAR_PLAYER_PARACHUTE_VARIATION_OVERRIDE);
		PLAYER.set_function("SET_PLAYER_PARACHUTE_MODEL_OVERRIDE", LUA_NATIVE_PLAYER_SET_PLAYER_PARACHUTE_MODEL_OVERRIDE);
		PLAYER.set_function("SET_PLAYER_RESERVE_PARACHUTE_MODEL_OVERRIDE", LUA_NATIVE_PLAYER_SET_PLAYER_RESERVE_PARACHUTE_MODEL_OVERRIDE);
		PLAYER.set_function("GET_PLAYER_PARACHUTE_MODEL_OVERRIDE", LUA_NATIVE_PLAYER_GET_PLAYER_PARACHUTE_MODEL_OVERRIDE);
		PLAYER.set_function("GET_PLAYER_RESERVE_PARACHUTE_MODEL_OVERRIDE", LUA_NATIVE_PLAYER_GET_PLAYER_RESERVE_PARACHUTE_MODEL_OVERRIDE);
		PLAYER.set_function("CLEAR_PLAYER_PARACHUTE_MODEL_OVERRIDE", LUA_NATIVE_PLAYER_CLEAR_PLAYER_PARACHUTE_MODEL_OVERRIDE);
		PLAYER.set_function("CLEAR_PLAYER_RESERVE_PARACHUTE_MODEL_OVERRIDE", LUA_NATIVE_PLAYER_CLEAR_PLAYER_RESERVE_PARACHUTE_MODEL_OVERRIDE);
		PLAYER.set_function("SET_PLAYER_PARACHUTE_PACK_MODEL_OVERRIDE", LUA_NATIVE_PLAYER_SET_PLAYER_PARACHUTE_PACK_MODEL_OVERRIDE);
		PLAYER.set_function("CLEAR_PLAYER_PARACHUTE_PACK_MODEL_OVERRIDE", LUA_NATIVE_PLAYER_CLEAR_PLAYER_PARACHUTE_PACK_MODEL_OVERRIDE);
		PLAYER.set_function("DISABLE_PLAYER_VEHICLE_REWARDS", LUA_NATIVE_PLAYER_DISABLE_PLAYER_VEHICLE_REWARDS);
		PLAYER.set_function("SET_PLAYER_SPECTATED_VEHICLE_RADIO_OVERRIDE", LUA_NATIVE_PLAYER_SET_PLAYER_SPECTATED_VEHICLE_RADIO_OVERRIDE);
		PLAYER.set_function("SET_PLAYER_BLUETOOTH_STATE", LUA_NATIVE_PLAYER_SET_PLAYER_BLUETOOTH_STATE);
		PLAYER.set_function("IS_PLAYER_BLUETOOTH_ENABLE", LUA_NATIVE_PLAYER_IS_PLAYER_BLUETOOTH_ENABLE);
		PLAYER.set_function("DISABLE_CAMERA_VIEW_MODE_CYCLE", LUA_NATIVE_PLAYER_DISABLE_CAMERA_VIEW_MODE_CYCLE);
		PLAYER.set_function("GET_PLAYER_FAKE_WANTED_LEVEL", LUA_NATIVE_PLAYER_GET_PLAYER_FAKE_WANTED_LEVEL);
		PLAYER.set_function("SET_PLAYER_CAN_DAMAGE_PLAYER", LUA_NATIVE_PLAYER_SET_PLAYER_CAN_DAMAGE_PLAYER);
		PLAYER.set_function("SET_APPLY_WAYPOINT_OF_PLAYER", LUA_NATIVE_PLAYER_SET_APPLY_WAYPOINT_OF_PLAYER);
		PLAYER.set_function("IS_PLAYER_VEHICLE_WEAPON_TOGGLED_TO_NON_HOMING", LUA_NATIVE_PLAYER_IS_PLAYER_VEHICLE_WEAPON_TOGGLED_TO_NON_HOMING);
		PLAYER.set_function("SET_PLAYER_VEHICLE_WEAPON_TO_NON_HOMING", LUA_NATIVE_PLAYER_SET_PLAYER_VEHICLE_WEAPON_TO_NON_HOMING);
		PLAYER.set_function("SET_PLAYER_HOMING_DISABLED_FOR_ALL_VEHICLE_WEAPONS", LUA_NATIVE_PLAYER_SET_PLAYER_HOMING_DISABLED_FOR_ALL_VEHICLE_WEAPONS);
		PLAYER.set_function("ADD_PLAYER_TARGETABLE_ENTITY", LUA_NATIVE_PLAYER_ADD_PLAYER_TARGETABLE_ENTITY);
		PLAYER.set_function("REMOVE_PLAYER_TARGETABLE_ENTITY", LUA_NATIVE_PLAYER_REMOVE_PLAYER_TARGETABLE_ENTITY);
		PLAYER.set_function("SET_PLAYER_PREVIOUS_VARIATION_DATA", LUA_NATIVE_PLAYER_SET_PLAYER_PREVIOUS_VARIATION_DATA);
		PLAYER.set_function("REMOVE_SCRIPT_FIRE_POSITION", LUA_NATIVE_PLAYER_REMOVE_SCRIPT_FIRE_POSITION);
		PLAYER.set_function("SET_SCRIPT_FIRE_POSITION", LUA_NATIVE_PLAYER_SET_SCRIPT_FIRE_POSITION);
	}
}
