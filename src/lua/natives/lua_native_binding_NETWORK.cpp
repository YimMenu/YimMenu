#include "lua_native_binding.hpp"
#include "natives.hpp"

namespace lua::native
{
	static const char* LUA_NATIVE_NETWORK_GET_ONLINE_VERSION(  )
	{
		auto retval = NETWORK::GET_ONLINE_VERSION();
		return retval;
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_IS_SIGNED_IN(  )
	{
		auto retval = (bool)NETWORK::NETWORK_IS_SIGNED_IN();
		return retval;
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_IS_SIGNED_ONLINE(  )
	{
		auto retval = (bool)NETWORK::NETWORK_IS_SIGNED_ONLINE();
		return retval;
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_IS_NP_AVAILABLE(  )
	{
		auto retval = (bool)NETWORK::NETWORK_IS_NP_AVAILABLE();
		return retval;
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_IS_NP_PENDING(  )
	{
		auto retval = (bool)NETWORK::NETWORK_IS_NP_PENDING();
		return retval;
	}

	static int LUA_NATIVE_NETWORK_NETWORK_GET_NP_UNAVAILABLE_REASON(  )
	{
		auto retval = NETWORK::NETWORK_GET_NP_UNAVAILABLE_REASON();
		return retval;
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_IS_CONNETED_TO_NP_PRESENCE(  )
	{
		auto retval = (bool)NETWORK::NETWORK_IS_CONNETED_TO_NP_PRESENCE();
		return retval;
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_IS_LOGGED_IN_TO_PSN(  )
	{
		auto retval = (bool)NETWORK::NETWORK_IS_LOGGED_IN_TO_PSN();
		return retval;
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_HAS_VALID_ROS_CREDENTIALS(  )
	{
		auto retval = (bool)NETWORK::NETWORK_HAS_VALID_ROS_CREDENTIALS();
		return retval;
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_IS_REFRESHING_ROS_CREDENTIALS(  )
	{
		auto retval = (bool)NETWORK::NETWORK_IS_REFRESHING_ROS_CREDENTIALS();
		return retval;
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_IS_CLOUD_AVAILABLE(  )
	{
		auto retval = (bool)NETWORK::NETWORK_IS_CLOUD_AVAILABLE();
		return retval;
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_HAS_SOCIAL_CLUB_ACCOUNT(  )
	{
		auto retval = (bool)NETWORK::NETWORK_HAS_SOCIAL_CLUB_ACCOUNT();
		return retval;
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_ARE_SOCIAL_CLUB_POLICIES_CURRENT(  )
	{
		auto retval = (bool)NETWORK::NETWORK_ARE_SOCIAL_CLUB_POLICIES_CURRENT();
		return retval;
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_IS_HOST(  )
	{
		auto retval = (bool)NETWORK::NETWORK_IS_HOST();
		return retval;
	}

	static Player LUA_NATIVE_NETWORK_NETWORK_GET_HOST_PLAYER_INDEX(  )
	{
		auto retval = NETWORK::NETWORK_GET_HOST_PLAYER_INDEX();
		return retval;
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_WAS_GAME_SUSPENDED(  )
	{
		auto retval = (bool)NETWORK::NETWORK_WAS_GAME_SUSPENDED();
		return retval;
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_HAVE_ONLINE_PRIVILEGES(  )
	{
		auto retval = (bool)NETWORK::NETWORK_HAVE_ONLINE_PRIVILEGES();
		return retval;
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_HAS_AGE_RESTRICTIONS(  )
	{
		auto retval = (bool)NETWORK::NETWORK_HAS_AGE_RESTRICTIONS();
		return retval;
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_HAVE_USER_CONTENT_PRIVILEGES( int p0 )
	{
		auto retval = (bool)NETWORK::NETWORK_HAVE_USER_CONTENT_PRIVILEGES(p0);
		return retval;
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_HAVE_COMMUNICATION_PRIVILEGES( int p0, Player player )
	{
		auto retval = (bool)NETWORK::NETWORK_HAVE_COMMUNICATION_PRIVILEGES(p0, player);
		return retval;
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_CHECK_ONLINE_PRIVILEGES( Any p0, bool p1 )
	{
		auto retval = (bool)NETWORK::NETWORK_CHECK_ONLINE_PRIVILEGES(p0, p1);
		return retval;
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_CHECK_USER_CONTENT_PRIVILEGES( int p0, int p1, bool p2 )
	{
		auto retval = (bool)NETWORK::NETWORK_CHECK_USER_CONTENT_PRIVILEGES(p0, p1, p2);
		return retval;
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_CHECK_COMMUNICATION_PRIVILEGES( int p0, int p1, bool p2 )
	{
		auto retval = (bool)NETWORK::NETWORK_CHECK_COMMUNICATION_PRIVILEGES(p0, p1, p2);
		return retval;
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_CHECK_TEXT_COMMUNICATION_PRIVILEGES( Any p0, Any p1, Any p2 )
	{
		auto retval = (bool)NETWORK::NETWORK_CHECK_TEXT_COMMUNICATION_PRIVILEGES(p0, p1, p2);
		return retval;
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_IS_USING_ONLINE_PROMOTION(  )
	{
		auto retval = (bool)NETWORK::NETWORK_IS_USING_ONLINE_PROMOTION();
		return retval;
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_SHOULD_SHOW_PROMOTION_ALERT_SCREEN(  )
	{
		auto retval = (bool)NETWORK::NETWORK_SHOULD_SHOW_PROMOTION_ALERT_SCREEN();
		return retval;
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_HAS_SOCIAL_NETWORKING_SHARING_PRIV(  )
	{
		auto retval = (bool)NETWORK::NETWORK_HAS_SOCIAL_NETWORKING_SHARING_PRIV();
		return retval;
	}

	static int LUA_NATIVE_NETWORK_NETWORK_GET_AGE_GROUP(  )
	{
		auto retval = NETWORK::NETWORK_GET_AGE_GROUP();
		return retval;
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_CHECK_PRIVILEGES( Any p0, Any p1, Any p2 )
	{
		auto retval = (bool)NETWORK::NETWORK_CHECK_PRIVILEGES(p0, p1, p2);
		return retval;
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_IS_PRIVILEGE_CHECK_IN_PROGRESS(  )
	{
		auto retval = (bool)NETWORK::NETWORK_IS_PRIVILEGE_CHECK_IN_PROGRESS();
		return retval;
	}

	static void LUA_NATIVE_NETWORK_NETWORK_SET_PRIVILEGE_CHECK_RESULT_NOT_NEEDED(  )
	{
		NETWORK::NETWORK_SET_PRIVILEGE_CHECK_RESULT_NOT_NEEDED();
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_RESOLVE_PRIVILEGE_USER_CONTENT(  )
	{
		auto retval = (bool)NETWORK::NETWORK_RESOLVE_PRIVILEGE_USER_CONTENT();
		return retval;
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_HAVE_PLATFORM_SUBSCRIPTION(  )
	{
		auto retval = (bool)NETWORK::NETWORK_HAVE_PLATFORM_SUBSCRIPTION();
		return retval;
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_IS_PLATFORM_SUBSCRIPTION_CHECK_PENDING(  )
	{
		auto retval = (bool)NETWORK::NETWORK_IS_PLATFORM_SUBSCRIPTION_CHECK_PENDING();
		return retval;
	}

	static void LUA_NATIVE_NETWORK_NETWORK_SHOW_ACCOUNT_UPGRADE_UI(  )
	{
		NETWORK::NETWORK_SHOW_ACCOUNT_UPGRADE_UI();
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_IS_SHOWING_SYSTEM_UI_OR_RECENTLY_REQUESTED_UPSELL(  )
	{
		auto retval = (bool)NETWORK::NETWORK_IS_SHOWING_SYSTEM_UI_OR_RECENTLY_REQUESTED_UPSELL();
		return retval;
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_NEED_TO_START_NEW_GAME_BUT_BLOCKED(  )
	{
		auto retval = (bool)NETWORK::NETWORK_NEED_TO_START_NEW_GAME_BUT_BLOCKED();
		return retval;
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_CAN_BAIL(  )
	{
		auto retval = (bool)NETWORK::NETWORK_CAN_BAIL();
		return retval;
	}

	static void LUA_NATIVE_NETWORK_NETWORK_BAIL( int p0, int p1, int p2 )
	{
		NETWORK::NETWORK_BAIL(p0, p1, p2);
	}

	static void LUA_NATIVE_NETWORK_NETWORK_ON_RETURN_TO_SINGLE_PLAYER(  )
	{
		NETWORK::NETWORK_ON_RETURN_TO_SINGLE_PLAYER();
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_TRANSITION_START( int p0, Any p1, Any p2, Any p3 )
	{
		auto retval = (bool)NETWORK::NETWORK_TRANSITION_START(p0, p1, p2, p3);
		return retval;
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_TRANSITION_ADD_STAGE( Hash hash, int p1, int p2, int state, int p4 )
	{
		auto retval = (bool)NETWORK::NETWORK_TRANSITION_ADD_STAGE(hash, p1, p2, state, p4);
		return retval;
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_TRANSITION_FINISH( Any p0, Any p1, Any p2 )
	{
		auto retval = (bool)NETWORK::NETWORK_TRANSITION_FINISH(p0, p1, p2);
		return retval;
	}

	static std::tuple<bool, int> LUA_NATIVE_NETWORK_NETWORK_CAN_ACCESS_MULTIPLAYER( int loadingState )
	{
		std::tuple<bool, int> return_values;
		std::get<0>(return_values) = (bool)NETWORK::NETWORK_CAN_ACCESS_MULTIPLAYER(&loadingState);
		std::get<1>(return_values) = loadingState;

		return return_values;
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_IS_MULTIPLAYER_DISABLED(  )
	{
		auto retval = (bool)NETWORK::NETWORK_IS_MULTIPLAYER_DISABLED();
		return retval;
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_CAN_ENTER_MULTIPLAYER(  )
	{
		auto retval = (bool)NETWORK::NETWORK_CAN_ENTER_MULTIPLAYER();
		return retval;
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_SESSION_DO_FREEROAM_QUICKMATCH( Any p0, Any p1, Any p2, int maxPlayers )
	{
		auto retval = (bool)NETWORK::NETWORK_SESSION_DO_FREEROAM_QUICKMATCH(p0, p1, p2, maxPlayers);
		return retval;
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_SESSION_DO_FRIEND_MATCHMAKING( int p0, int p1, int maxPlayers )
	{
		auto retval = (bool)NETWORK::NETWORK_SESSION_DO_FRIEND_MATCHMAKING(p0, p1, maxPlayers);
		return retval;
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_SESSION_DO_CREW_MATCHMAKING( int crewId, int p1, int p2, int maxPlayers )
	{
		auto retval = (bool)NETWORK::NETWORK_SESSION_DO_CREW_MATCHMAKING(crewId, p1, p2, maxPlayers);
		return retval;
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_SESSION_DO_ACTIVITY_QUICKMATCH( Any p0, Any p1, Any p2, Any p3, Any p4 )
	{
		auto retval = (bool)NETWORK::NETWORK_SESSION_DO_ACTIVITY_QUICKMATCH(p0, p1, p2, p3, p4);
		return retval;
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_SESSION_HOST( int p0, int maxPlayers, bool p2 )
	{
		auto retval = (bool)NETWORK::NETWORK_SESSION_HOST(p0, maxPlayers, p2);
		return retval;
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_SESSION_HOST_CLOSED( int p0, int maxPlayers )
	{
		auto retval = (bool)NETWORK::NETWORK_SESSION_HOST_CLOSED(p0, maxPlayers);
		return retval;
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_SESSION_HOST_FRIENDS_ONLY( int p0, int maxPlayers )
	{
		auto retval = (bool)NETWORK::NETWORK_SESSION_HOST_FRIENDS_ONLY(p0, maxPlayers);
		return retval;
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_SESSION_IS_CLOSED_FRIENDS(  )
	{
		auto retval = (bool)NETWORK::NETWORK_SESSION_IS_CLOSED_FRIENDS();
		return retval;
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_SESSION_IS_CLOSED_CREW(  )
	{
		auto retval = (bool)NETWORK::NETWORK_SESSION_IS_CLOSED_CREW();
		return retval;
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_SESSION_IS_SOLO(  )
	{
		auto retval = (bool)NETWORK::NETWORK_SESSION_IS_SOLO();
		return retval;
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_SESSION_IS_PRIVATE(  )
	{
		auto retval = (bool)NETWORK::NETWORK_SESSION_IS_PRIVATE();
		return retval;
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_SESSION_END( bool p0, bool p1 )
	{
		auto retval = (bool)NETWORK::NETWORK_SESSION_END(p0, p1);
		return retval;
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_SESSION_LEAVE( Any p0 )
	{
		auto retval = (bool)NETWORK::NETWORK_SESSION_LEAVE(p0);
		return retval;
	}

	static void LUA_NATIVE_NETWORK_NETWORK_SESSION_KICK_PLAYER( Player player )
	{
		NETWORK::NETWORK_SESSION_KICK_PLAYER(player);
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_SESSION_GET_KICK_VOTE( Player player )
	{
		auto retval = (bool)NETWORK::NETWORK_SESSION_GET_KICK_VOTE(player);
		return retval;
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_SESSION_RESERVE_SLOTS_TRANSITION( Any p0, Any p1, Any p2 )
	{
		auto retval = (bool)NETWORK::NETWORK_SESSION_RESERVE_SLOTS_TRANSITION(p0, p1, p2);
		return retval;
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_JOIN_PREVIOUSLY_FAILED_SESSION(  )
	{
		auto retval = (bool)NETWORK::NETWORK_JOIN_PREVIOUSLY_FAILED_SESSION();
		return retval;
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_JOIN_PREVIOUSLY_FAILED_TRANSITION(  )
	{
		auto retval = (bool)NETWORK::NETWORK_JOIN_PREVIOUSLY_FAILED_TRANSITION();
		return retval;
	}

	static void LUA_NATIVE_NETWORK_NETWORK_SESSION_SET_MATCHMAKING_GROUP( int matchmakingGroup )
	{
		NETWORK::NETWORK_SESSION_SET_MATCHMAKING_GROUP(matchmakingGroup);
	}

	static void LUA_NATIVE_NETWORK_NETWORK_SESSION_SET_MATCHMAKING_GROUP_MAX( int playerType, int playerCount )
	{
		NETWORK::NETWORK_SESSION_SET_MATCHMAKING_GROUP_MAX(playerType, playerCount);
	}

	static int LUA_NATIVE_NETWORK_NETWORK_SESSION_GET_MATCHMAKING_GROUP_FREE( int p0 )
	{
		auto retval = NETWORK::NETWORK_SESSION_GET_MATCHMAKING_GROUP_FREE(p0);
		return retval;
	}

	static void LUA_NATIVE_NETWORK_NETWORK_SESSION_ADD_ACTIVE_MATCHMAKING_GROUP( int groupId )
	{
		NETWORK::NETWORK_SESSION_ADD_ACTIVE_MATCHMAKING_GROUP(groupId);
	}

	static void LUA_NATIVE_NETWORK_NETWORK_SESSION_SET_UNIQUE_CREW_LIMIT( Any p0 )
	{
		NETWORK::NETWORK_SESSION_SET_UNIQUE_CREW_LIMIT(p0);
	}

	static void LUA_NATIVE_NETWORK_NETWORK_SESSION_SET_UNIQUE_CREW_LIMIT_TRANSITION( Any p0 )
	{
		NETWORK::NETWORK_SESSION_SET_UNIQUE_CREW_LIMIT_TRANSITION(p0);
	}

	static void LUA_NATIVE_NETWORK_NETWORK_SESSION_SET_UNIQUE_CREW_ONLY_CREWS_TRANSITION( bool p0 )
	{
		NETWORK::NETWORK_SESSION_SET_UNIQUE_CREW_ONLY_CREWS_TRANSITION(p0);
	}

	static void LUA_NATIVE_NETWORK_NETWORK_SESSION_SET_CREW_LIMIT_MAX_MEMBERS_TRANSITION( Any p0 )
	{
		NETWORK::NETWORK_SESSION_SET_CREW_LIMIT_MAX_MEMBERS_TRANSITION(p0);
	}

	static void LUA_NATIVE_NETWORK_NETWORK_SESSION_SET_MATCHMAKING_PROPERTY_ID( bool p0 )
	{
		NETWORK::NETWORK_SESSION_SET_MATCHMAKING_PROPERTY_ID(p0);
	}

	static void LUA_NATIVE_NETWORK_NETWORK_SESSION_SET_MATCHMAKING_MENTAL_STATE( int p0 )
	{
		NETWORK::NETWORK_SESSION_SET_MATCHMAKING_MENTAL_STATE(p0);
	}

	static void LUA_NATIVE_NETWORK_NETWORK_SESSION_SET_NUM_BOSSES( int num )
	{
		NETWORK::NETWORK_SESSION_SET_NUM_BOSSES(num);
	}

	static void LUA_NATIVE_NETWORK_NETWORK_SESSION_SET_SCRIPT_VALIDATE_JOIN(  )
	{
		NETWORK::NETWORK_SESSION_SET_SCRIPT_VALIDATE_JOIN();
	}

	static void LUA_NATIVE_NETWORK_NETWORK_SESSION_VALIDATE_JOIN( bool p0 )
	{
		NETWORK::NETWORK_SESSION_VALIDATE_JOIN(p0);
	}

	static int LUA_NATIVE_NETWORK_NETWORK_ADD_FOLLOWERS( int p0, int p1 )
	{
		NETWORK::NETWORK_ADD_FOLLOWERS(&p0, p1);
		return p0;
	}

	static void LUA_NATIVE_NETWORK_NETWORK_CLEAR_FOLLOWERS(  )
	{
		NETWORK::NETWORK_CLEAR_FOLLOWERS();
	}

	static std::tuple<int, int, int> LUA_NATIVE_NETWORK_NETWORK_GET_GLOBAL_MULTIPLAYER_CLOCK( int hours, int minutes, int seconds )
	{
		std::tuple<int, int, int> return_values;
		NETWORK::NETWORK_GET_GLOBAL_MULTIPLAYER_CLOCK(&hours, &minutes, &seconds);
		std::get<0>(return_values) = hours;
		std::get<1>(return_values) = minutes;
		std::get<2>(return_values) = seconds;

		return return_values;
	}

	static void LUA_NATIVE_NETWORK_NETWORK_SESSION_SET_GAMEMODE( Any p0 )
	{
		NETWORK::NETWORK_SESSION_SET_GAMEMODE(p0);
	}

	static int LUA_NATIVE_NETWORK_NETWORK_SESSION_GET_HOST_AIM_PREFERENCE(  )
	{
		auto retval = NETWORK::NETWORK_SESSION_GET_HOST_AIM_PREFERENCE();
		return retval;
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_FIND_GAMERS_IN_CREW( int crewId )
	{
		auto retval = (bool)NETWORK::NETWORK_FIND_GAMERS_IN_CREW(crewId);
		return retval;
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_FIND_MATCHED_GAMERS( int attribute, float fallbackLimit, float lowerLimit, float upperLimit )
	{
		auto retval = (bool)NETWORK::NETWORK_FIND_MATCHED_GAMERS(attribute, fallbackLimit, lowerLimit, upperLimit);
		return retval;
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_IS_FINDING_GAMERS(  )
	{
		auto retval = (bool)NETWORK::NETWORK_IS_FINDING_GAMERS();
		return retval;
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_DID_FIND_GAMERS_SUCCEED(  )
	{
		auto retval = (bool)NETWORK::NETWORK_DID_FIND_GAMERS_SUCCEED();
		return retval;
	}

	static int LUA_NATIVE_NETWORK_NETWORK_GET_NUM_FOUND_GAMERS(  )
	{
		auto retval = NETWORK::NETWORK_GET_NUM_FOUND_GAMERS();
		return retval;
	}

	static std::tuple<bool, Any> LUA_NATIVE_NETWORK_NETWORK_GET_FOUND_GAMER( Any p0, Any p1 )
	{
		std::tuple<bool, Any> return_values;
		std::get<0>(return_values) = (bool)NETWORK::NETWORK_GET_FOUND_GAMER(&p0, p1);
		std::get<1>(return_values) = p0;

		return return_values;
	}

	static void LUA_NATIVE_NETWORK_NETWORK_CLEAR_FOUND_GAMERS(  )
	{
		NETWORK::NETWORK_CLEAR_FOUND_GAMERS();
	}

	static std::tuple<bool, Any> LUA_NATIVE_NETWORK_NETWORK_QUEUE_GAMER_FOR_STATUS( Any p0 )
	{
		std::tuple<bool, Any> return_values;
		std::get<0>(return_values) = (bool)NETWORK::NETWORK_QUEUE_GAMER_FOR_STATUS(&p0);
		std::get<1>(return_values) = p0;

		return return_values;
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_GET_GAMER_STATUS_FROM_QUEUE(  )
	{
		auto retval = (bool)NETWORK::NETWORK_GET_GAMER_STATUS_FROM_QUEUE();
		return retval;
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_IS_GETTING_GAMER_STATUS(  )
	{
		auto retval = (bool)NETWORK::NETWORK_IS_GETTING_GAMER_STATUS();
		return retval;
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_DID_GET_GAMER_STATUS_SUCCEED(  )
	{
		auto retval = (bool)NETWORK::NETWORK_DID_GET_GAMER_STATUS_SUCCEED();
		return retval;
	}

	static std::tuple<bool, Any> LUA_NATIVE_NETWORK_NETWORK_GET_GAMER_STATUS_RESULT( Any p0, Any p1 )
	{
		std::tuple<bool, Any> return_values;
		std::get<0>(return_values) = (bool)NETWORK::NETWORK_GET_GAMER_STATUS_RESULT(&p0, p1);
		std::get<1>(return_values) = p0;

		return return_values;
	}

	static void LUA_NATIVE_NETWORK_NETWORK_CLEAR_GET_GAMER_STATUS(  )
	{
		NETWORK::NETWORK_CLEAR_GET_GAMER_STATUS();
	}

	static void LUA_NATIVE_NETWORK_NETWORK_SESSION_JOIN_INVITE(  )
	{
		NETWORK::NETWORK_SESSION_JOIN_INVITE();
	}

	static void LUA_NATIVE_NETWORK_NETWORK_SESSION_CANCEL_INVITE(  )
	{
		NETWORK::NETWORK_SESSION_CANCEL_INVITE();
	}

	static void LUA_NATIVE_NETWORK_NETWORK_SESSION_FORCE_CANCEL_INVITE(  )
	{
		NETWORK::NETWORK_SESSION_FORCE_CANCEL_INVITE();
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_HAS_PENDING_INVITE(  )
	{
		auto retval = (bool)NETWORK::NETWORK_HAS_PENDING_INVITE();
		return retval;
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_HAS_CONFIRMED_INVITE(  )
	{
		auto retval = (bool)NETWORK::NETWORK_HAS_CONFIRMED_INVITE();
		return retval;
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_REQUEST_INVITE_CONFIRMED_EVENT(  )
	{
		auto retval = (bool)NETWORK::NETWORK_REQUEST_INVITE_CONFIRMED_EVENT();
		return retval;
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_SESSION_WAS_INVITED(  )
	{
		auto retval = (bool)NETWORK::NETWORK_SESSION_WAS_INVITED();
		return retval;
	}

	static Any LUA_NATIVE_NETWORK_NETWORK_SESSION_GET_INVITER( Any gamerHandle )
	{
		NETWORK::NETWORK_SESSION_GET_INVITER(&gamerHandle);
		return gamerHandle;
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_SESSION_IS_AWAITING_INVITE_RESPONSE(  )
	{
		auto retval = (bool)NETWORK::NETWORK_SESSION_IS_AWAITING_INVITE_RESPONSE();
		return retval;
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_SESSION_IS_DISPLAYING_INVITE_CONFIRMATION(  )
	{
		auto retval = (bool)NETWORK::NETWORK_SESSION_IS_DISPLAYING_INVITE_CONFIRMATION();
		return retval;
	}

	static void LUA_NATIVE_NETWORK_NETWORK_SUPPRESS_INVITE( bool toggle )
	{
		NETWORK::NETWORK_SUPPRESS_INVITE(toggle);
	}

	static void LUA_NATIVE_NETWORK_NETWORK_BLOCK_INVITES( bool toggle )
	{
		NETWORK::NETWORK_BLOCK_INVITES(toggle);
	}

	static void LUA_NATIVE_NETWORK_NETWORK_BLOCK_JOIN_QUEUE_INVITES( bool toggle )
	{
		NETWORK::NETWORK_BLOCK_JOIN_QUEUE_INVITES(toggle);
	}

	static void LUA_NATIVE_NETWORK_NETWORK_SET_CAN_RECEIVE_RS_INVITES( bool p0 )
	{
		NETWORK::NETWORK_SET_CAN_RECEIVE_RS_INVITES(p0);
	}

	static void LUA_NATIVE_NETWORK_NETWORK_STORE_INVITE_THROUGH_RESTART(  )
	{
		NETWORK::NETWORK_STORE_INVITE_THROUGH_RESTART();
	}

	static void LUA_NATIVE_NETWORK_NETWORK_ALLOW_INVITE_PROCESS_IN_PLAYER_SWITCH( bool p0 )
	{
		NETWORK::NETWORK_ALLOW_INVITE_PROCESS_IN_PLAYER_SWITCH(p0);
	}

	static void LUA_NATIVE_NETWORK_NETWORK_SET_SCRIPT_READY_FOR_EVENTS( bool toggle )
	{
		NETWORK::NETWORK_SET_SCRIPT_READY_FOR_EVENTS(toggle);
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_IS_OFFLINE_INVITE_PENDING(  )
	{
		auto retval = (bool)NETWORK::NETWORK_IS_OFFLINE_INVITE_PENDING();
		return retval;
	}

	static void LUA_NATIVE_NETWORK_NETWORK_CLEAR_OFFLINE_INVITE_PENDING(  )
	{
		NETWORK::NETWORK_CLEAR_OFFLINE_INVITE_PENDING();
	}

	static void LUA_NATIVE_NETWORK_NETWORK_SESSION_HOST_SINGLE_PLAYER( int p0 )
	{
		NETWORK::NETWORK_SESSION_HOST_SINGLE_PLAYER(p0);
	}

	static void LUA_NATIVE_NETWORK_NETWORK_SESSION_LEAVE_SINGLE_PLAYER(  )
	{
		NETWORK::NETWORK_SESSION_LEAVE_SINGLE_PLAYER();
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_IS_GAME_IN_PROGRESS(  )
	{
		auto retval = (bool)NETWORK::NETWORK_IS_GAME_IN_PROGRESS();
		return retval;
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_IS_SESSION_ACTIVE(  )
	{
		auto retval = (bool)NETWORK::NETWORK_IS_SESSION_ACTIVE();
		return retval;
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_IS_IN_SESSION(  )
	{
		auto retval = (bool)NETWORK::NETWORK_IS_IN_SESSION();
		return retval;
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_IS_SESSION_STARTED(  )
	{
		auto retval = (bool)NETWORK::NETWORK_IS_SESSION_STARTED();
		return retval;
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_IS_SESSION_BUSY(  )
	{
		auto retval = (bool)NETWORK::NETWORK_IS_SESSION_BUSY();
		return retval;
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_CAN_SESSION_END(  )
	{
		auto retval = (bool)NETWORK::NETWORK_CAN_SESSION_END();
		return retval;
	}

	static int LUA_NATIVE_NETWORK_NETWORK_GET_GAME_MODE(  )
	{
		auto retval = NETWORK::NETWORK_GET_GAME_MODE();
		return retval;
	}

	static void LUA_NATIVE_NETWORK_NETWORK_SESSION_MARK_VISIBLE( bool toggle )
	{
		NETWORK::NETWORK_SESSION_MARK_VISIBLE(toggle);
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_SESSION_IS_VISIBLE(  )
	{
		auto retval = (bool)NETWORK::NETWORK_SESSION_IS_VISIBLE();
		return retval;
	}

	static void LUA_NATIVE_NETWORK_NETWORK_SESSION_BLOCK_JOIN_REQUESTS( bool toggle )
	{
		NETWORK::NETWORK_SESSION_BLOCK_JOIN_REQUESTS(toggle);
	}

	static void LUA_NATIVE_NETWORK_NETWORK_SESSION_CHANGE_SLOTS( int slots, bool p1 )
	{
		NETWORK::NETWORK_SESSION_CHANGE_SLOTS(slots, p1);
	}

	static int LUA_NATIVE_NETWORK_NETWORK_SESSION_GET_PRIVATE_SLOTS(  )
	{
		auto retval = NETWORK::NETWORK_SESSION_GET_PRIVATE_SLOTS();
		return retval;
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_SESSION_VOICE_HOST(  )
	{
		auto retval = (bool)NETWORK::NETWORK_SESSION_VOICE_HOST();
		return retval;
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_SESSION_VOICE_LEAVE(  )
	{
		auto retval = (bool)NETWORK::NETWORK_SESSION_VOICE_LEAVE();
		return retval;
	}

	static Any LUA_NATIVE_NETWORK_NETWORK_SESSION_VOICE_CONNECT_TO_PLAYER( Any gamerHandle )
	{
		NETWORK::NETWORK_SESSION_VOICE_CONNECT_TO_PLAYER(&gamerHandle);
		return gamerHandle;
	}

	static void LUA_NATIVE_NETWORK_NETWORK_SESSION_VOICE_RESPOND_TO_REQUEST( bool p0, int p1 )
	{
		NETWORK::NETWORK_SESSION_VOICE_RESPOND_TO_REQUEST(p0, p1);
	}

	static void LUA_NATIVE_NETWORK_NETWORK_SESSION_VOICE_SET_TIMEOUT( int timeout )
	{
		NETWORK::NETWORK_SESSION_VOICE_SET_TIMEOUT(timeout);
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_SESSION_IS_IN_VOICE_SESSION(  )
	{
		auto retval = (bool)NETWORK::NETWORK_SESSION_IS_IN_VOICE_SESSION();
		return retval;
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_SESSION_IS_VOICE_SESSION_ACTIVE(  )
	{
		auto retval = (bool)NETWORK::NETWORK_SESSION_IS_VOICE_SESSION_ACTIVE();
		return retval;
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_SESSION_IS_VOICE_SESSION_BUSY(  )
	{
		auto retval = (bool)NETWORK::NETWORK_SESSION_IS_VOICE_SESSION_BUSY();
		return retval;
	}

	static std::tuple<bool, Any> LUA_NATIVE_NETWORK_NETWORK_SEND_TEXT_MESSAGE( const char* message, Any gamerHandle )
	{
		std::tuple<bool, Any> return_values;
		std::get<0>(return_values) = (bool)NETWORK::NETWORK_SEND_TEXT_MESSAGE(message, &gamerHandle);
		std::get<1>(return_values) = gamerHandle;

		return return_values;
	}

	static void LUA_NATIVE_NETWORK_NETWORK_SET_ACTIVITY_SPECTATOR( bool toggle )
	{
		NETWORK::NETWORK_SET_ACTIVITY_SPECTATOR(toggle);
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_IS_ACTIVITY_SPECTATOR(  )
	{
		auto retval = (bool)NETWORK::NETWORK_IS_ACTIVITY_SPECTATOR();
		return retval;
	}

	static void LUA_NATIVE_NETWORK_NETWORK_SET_ACTIVITY_PLAYER_MAX( Any p0 )
	{
		NETWORK::NETWORK_SET_ACTIVITY_PLAYER_MAX(p0);
	}

	static void LUA_NATIVE_NETWORK_NETWORK_SET_ACTIVITY_SPECTATOR_MAX( int maxSpectators )
	{
		NETWORK::NETWORK_SET_ACTIVITY_SPECTATOR_MAX(maxSpectators);
	}

	static int LUA_NATIVE_NETWORK_NETWORK_GET_ACTIVITY_PLAYER_NUM( bool p0 )
	{
		auto retval = NETWORK::NETWORK_GET_ACTIVITY_PLAYER_NUM(p0);
		return retval;
	}

	static std::tuple<bool, Any> LUA_NATIVE_NETWORK_NETWORK_IS_ACTIVITY_SPECTATOR_FROM_HANDLE( Any gamerHandle )
	{
		std::tuple<bool, Any> return_values;
		std::get<0>(return_values) = (bool)NETWORK::NETWORK_IS_ACTIVITY_SPECTATOR_FROM_HANDLE(&gamerHandle);
		std::get<1>(return_values) = gamerHandle;

		return return_values;
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_HOST_TRANSITION( int p0, int p1, int p2, int p3, Any p4, bool p5, bool p6, int p7, Any p8, int p9 )
	{
		auto retval = (bool)NETWORK::NETWORK_HOST_TRANSITION(p0, p1, p2, p3, p4, p5, p6, p7, p8, p9);
		return retval;
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_DO_TRANSITION_QUICKMATCH( Any p0, Any p1, Any p2, Any p3, Any p4, Any p5 )
	{
		auto retval = (bool)NETWORK::NETWORK_DO_TRANSITION_QUICKMATCH(p0, p1, p2, p3, p4, p5);
		return retval;
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_DO_TRANSITION_QUICKMATCH_ASYNC( Any p0, Any p1, Any p2, Any p3, Any p4, Any p5 )
	{
		auto retval = (bool)NETWORK::NETWORK_DO_TRANSITION_QUICKMATCH_ASYNC(p0, p1, p2, p3, p4, p5);
		return retval;
	}

	static std::tuple<bool, Any> LUA_NATIVE_NETWORK_NETWORK_DO_TRANSITION_QUICKMATCH_WITH_GROUP( Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7 )
	{
		std::tuple<bool, Any> return_values;
		std::get<0>(return_values) = (bool)NETWORK::NETWORK_DO_TRANSITION_QUICKMATCH_WITH_GROUP(p0, p1, p2, p3, &p4, p5, p6, p7);
		std::get<1>(return_values) = p4;

		return return_values;
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_JOIN_GROUP_ACTIVITY(  )
	{
		auto retval = (bool)NETWORK::NETWORK_JOIN_GROUP_ACTIVITY();
		return retval;
	}

	static void LUA_NATIVE_NETWORK_NETWORK_CLEAR_GROUP_ACTIVITY(  )
	{
		NETWORK::NETWORK_CLEAR_GROUP_ACTIVITY();
	}

	static void LUA_NATIVE_NETWORK_NETWORK_RETAIN_ACTIVITY_GROUP(  )
	{
		NETWORK::NETWORK_RETAIN_ACTIVITY_GROUP();
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_IS_TRANSITION_CLOSED_FRIENDS(  )
	{
		auto retval = (bool)NETWORK::NETWORK_IS_TRANSITION_CLOSED_FRIENDS();
		return retval;
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_IS_TRANSITION_CLOSED_CREW(  )
	{
		auto retval = (bool)NETWORK::NETWORK_IS_TRANSITION_CLOSED_CREW();
		return retval;
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_IS_TRANSITION_SOLO(  )
	{
		auto retval = (bool)NETWORK::NETWORK_IS_TRANSITION_SOLO();
		return retval;
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_IS_TRANSITION_PRIVATE(  )
	{
		auto retval = (bool)NETWORK::NETWORK_IS_TRANSITION_PRIVATE();
		return retval;
	}

	static int LUA_NATIVE_NETWORK_NETWORK_GET_NUM_TRANSITION_NON_ASYNC_GAMERS(  )
	{
		auto retval = NETWORK::NETWORK_GET_NUM_TRANSITION_NON_ASYNC_GAMERS();
		return retval;
	}

	static void LUA_NATIVE_NETWORK_NETWORK_MARK_AS_PREFERRED_ACTIVITY( bool p0 )
	{
		NETWORK::NETWORK_MARK_AS_PREFERRED_ACTIVITY(p0);
	}

	static void LUA_NATIVE_NETWORK_NETWORK_MARK_AS_WAITING_ASYNC( bool p0 )
	{
		NETWORK::NETWORK_MARK_AS_WAITING_ASYNC(p0);
	}

	static void LUA_NATIVE_NETWORK_NETWORK_SET_IN_PROGRESS_FINISH_TIME( Any p0 )
	{
		NETWORK::NETWORK_SET_IN_PROGRESS_FINISH_TIME(p0);
	}

	static Any LUA_NATIVE_NETWORK_NETWORK_SET_TRANSITION_CREATOR_HANDLE( Any p0 )
	{
		NETWORK::NETWORK_SET_TRANSITION_CREATOR_HANDLE(&p0);
		return p0;
	}

	static void LUA_NATIVE_NETWORK_NETWORK_CLEAR_TRANSITION_CREATOR_HANDLE(  )
	{
		NETWORK::NETWORK_CLEAR_TRANSITION_CREATOR_HANDLE();
	}

	static std::tuple<bool, Any> LUA_NATIVE_NETWORK_NETWORK_INVITE_GAMERS_TO_TRANSITION( Any p0, Any p1 )
	{
		std::tuple<bool, Any> return_values;
		std::get<0>(return_values) = (bool)NETWORK::NETWORK_INVITE_GAMERS_TO_TRANSITION(&p0, p1);
		std::get<1>(return_values) = p0;

		return return_values;
	}

	static Any LUA_NATIVE_NETWORK_NETWORK_SET_GAMER_INVITED_TO_TRANSITION( Any gamerHandle )
	{
		NETWORK::NETWORK_SET_GAMER_INVITED_TO_TRANSITION(&gamerHandle);
		return gamerHandle;
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_LEAVE_TRANSITION(  )
	{
		auto retval = (bool)NETWORK::NETWORK_LEAVE_TRANSITION();
		return retval;
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_LAUNCH_TRANSITION(  )
	{
		auto retval = (bool)NETWORK::NETWORK_LAUNCH_TRANSITION();
		return retval;
	}

	static void LUA_NATIVE_NETWORK_NETWORK_SET_DO_NOT_LAUNCH_FROM_JOIN_AS_MIGRATED_HOST( bool toggle )
	{
		NETWORK::NETWORK_SET_DO_NOT_LAUNCH_FROM_JOIN_AS_MIGRATED_HOST(toggle);
	}

	static void LUA_NATIVE_NETWORK_NETWORK_CANCEL_TRANSITION_MATCHMAKING(  )
	{
		NETWORK::NETWORK_CANCEL_TRANSITION_MATCHMAKING();
	}

	static void LUA_NATIVE_NETWORK_NETWORK_BAIL_TRANSITION( int p0, int p1, int p2 )
	{
		NETWORK::NETWORK_BAIL_TRANSITION(p0, p1, p2);
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_DO_TRANSITION_TO_GAME( bool p0, int maxPlayers )
	{
		auto retval = (bool)NETWORK::NETWORK_DO_TRANSITION_TO_GAME(p0, maxPlayers);
		return retval;
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_DO_TRANSITION_TO_NEW_GAME( bool p0, int maxPlayers, bool p2 )
	{
		auto retval = (bool)NETWORK::NETWORK_DO_TRANSITION_TO_NEW_GAME(p0, maxPlayers, p2);
		return retval;
	}

	static std::tuple<bool, Any> LUA_NATIVE_NETWORK_NETWORK_DO_TRANSITION_TO_FREEMODE( Any p0, Any p1, bool p2, int players, bool p4 )
	{
		std::tuple<bool, Any> return_values;
		std::get<0>(return_values) = (bool)NETWORK::NETWORK_DO_TRANSITION_TO_FREEMODE(&p0, p1, p2, players, p4);
		std::get<1>(return_values) = p0;

		return return_values;
	}

	static std::tuple<bool, Any> LUA_NATIVE_NETWORK_NETWORK_DO_TRANSITION_TO_NEW_FREEMODE( Any p0, Any p1, int players, bool p3, bool p4, bool p5 )
	{
		std::tuple<bool, Any> return_values;
		std::get<0>(return_values) = (bool)NETWORK::NETWORK_DO_TRANSITION_TO_NEW_FREEMODE(&p0, p1, players, p3, p4, p5);
		std::get<1>(return_values) = p0;

		return return_values;
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_IS_TRANSITION_TO_GAME(  )
	{
		auto retval = (bool)NETWORK::NETWORK_IS_TRANSITION_TO_GAME();
		return retval;
	}

	static std::tuple<int, Any> LUA_NATIVE_NETWORK_NETWORK_GET_TRANSITION_MEMBERS( Any data, int dataCount )
	{
		std::tuple<int, Any> return_values;
		std::get<0>(return_values) = NETWORK::NETWORK_GET_TRANSITION_MEMBERS(&data, dataCount);
		std::get<1>(return_values) = data;

		return return_values;
	}

	static void LUA_NATIVE_NETWORK_NETWORK_APPLY_TRANSITION_PARAMETER( int p0, int p1 )
	{
		NETWORK::NETWORK_APPLY_TRANSITION_PARAMETER(p0, p1);
	}

	static void LUA_NATIVE_NETWORK_NETWORK_APPLY_TRANSITION_PARAMETER_STRING( int p0, const char* string, bool p2 )
	{
		NETWORK::NETWORK_APPLY_TRANSITION_PARAMETER_STRING(p0, string, p2);
	}

	static std::tuple<bool, Any> LUA_NATIVE_NETWORK_NETWORK_SEND_TRANSITION_GAMER_INSTRUCTION( Any gamerHandle, const char* p1, int p2, int p3, bool p4 )
	{
		std::tuple<bool, Any> return_values;
		std::get<0>(return_values) = (bool)NETWORK::NETWORK_SEND_TRANSITION_GAMER_INSTRUCTION(&gamerHandle, p1, p2, p3, p4);
		std::get<1>(return_values) = gamerHandle;

		return return_values;
	}

	static std::tuple<bool, Any> LUA_NATIVE_NETWORK_NETWORK_MARK_TRANSITION_GAMER_AS_FULLY_JOINED( Any p0 )
	{
		std::tuple<bool, Any> return_values;
		std::get<0>(return_values) = (bool)NETWORK::NETWORK_MARK_TRANSITION_GAMER_AS_FULLY_JOINED(&p0);
		std::get<1>(return_values) = p0;

		return return_values;
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_IS_TRANSITION_HOST(  )
	{
		auto retval = (bool)NETWORK::NETWORK_IS_TRANSITION_HOST();
		return retval;
	}

	static std::tuple<bool, Any> LUA_NATIVE_NETWORK_NETWORK_IS_TRANSITION_HOST_FROM_HANDLE( Any gamerHandle )
	{
		std::tuple<bool, Any> return_values;
		std::get<0>(return_values) = (bool)NETWORK::NETWORK_IS_TRANSITION_HOST_FROM_HANDLE(&gamerHandle);
		std::get<1>(return_values) = gamerHandle;

		return return_values;
	}

	static std::tuple<bool, Any> LUA_NATIVE_NETWORK_NETWORK_GET_TRANSITION_HOST( Any gamerHandle )
	{
		std::tuple<bool, Any> return_values;
		std::get<0>(return_values) = (bool)NETWORK::NETWORK_GET_TRANSITION_HOST(&gamerHandle);
		std::get<1>(return_values) = gamerHandle;

		return return_values;
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_IS_IN_TRANSITION(  )
	{
		auto retval = (bool)NETWORK::NETWORK_IS_IN_TRANSITION();
		return retval;
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_IS_TRANSITION_STARTED(  )
	{
		auto retval = (bool)NETWORK::NETWORK_IS_TRANSITION_STARTED();
		return retval;
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_IS_TRANSITION_BUSY(  )
	{
		auto retval = (bool)NETWORK::NETWORK_IS_TRANSITION_BUSY();
		return retval;
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_IS_TRANSITION_MATCHMAKING(  )
	{
		auto retval = (bool)NETWORK::NETWORK_IS_TRANSITION_MATCHMAKING();
		return retval;
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_IS_TRANSITION_LEAVE_POSTPONED(  )
	{
		auto retval = (bool)NETWORK::NETWORK_IS_TRANSITION_LEAVE_POSTPONED();
		return retval;
	}

	static void LUA_NATIVE_NETWORK_NETWORK_TRANSITION_SET_IN_PROGRESS( Any p0 )
	{
		NETWORK::NETWORK_TRANSITION_SET_IN_PROGRESS(p0);
	}

	static void LUA_NATIVE_NETWORK_NETWORK_TRANSITION_SET_CONTENT_CREATOR( Any p0 )
	{
		NETWORK::NETWORK_TRANSITION_SET_CONTENT_CREATOR(p0);
	}

	static void LUA_NATIVE_NETWORK_NETWORK_TRANSITION_SET_ACTIVITY_ISLAND( Any p0 )
	{
		NETWORK::NETWORK_TRANSITION_SET_ACTIVITY_ISLAND(p0);
	}

	static void LUA_NATIVE_NETWORK_NETWORK_OPEN_TRANSITION_MATCHMAKING(  )
	{
		NETWORK::NETWORK_OPEN_TRANSITION_MATCHMAKING();
	}

	static void LUA_NATIVE_NETWORK_NETWORK_CLOSE_TRANSITION_MATCHMAKING(  )
	{
		NETWORK::NETWORK_CLOSE_TRANSITION_MATCHMAKING();
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_IS_TRANSITION_OPEN_TO_MATCHMAKING(  )
	{
		auto retval = (bool)NETWORK::NETWORK_IS_TRANSITION_OPEN_TO_MATCHMAKING();
		return retval;
	}

	static void LUA_NATIVE_NETWORK_NETWORK_SET_TRANSITION_VISIBILITY_LOCK( bool p0, bool p1 )
	{
		NETWORK::NETWORK_SET_TRANSITION_VISIBILITY_LOCK(p0, p1);
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_IS_TRANSITION_VISIBILITY_LOCKED(  )
	{
		auto retval = (bool)NETWORK::NETWORK_IS_TRANSITION_VISIBILITY_LOCKED();
		return retval;
	}

	static void LUA_NATIVE_NETWORK_NETWORK_SET_TRANSITION_ACTIVITY_ID( Any p0 )
	{
		NETWORK::NETWORK_SET_TRANSITION_ACTIVITY_ID(p0);
	}

	static void LUA_NATIVE_NETWORK_NETWORK_CHANGE_TRANSITION_SLOTS( Any p0, bool p1 )
	{
		NETWORK::NETWORK_CHANGE_TRANSITION_SLOTS(p0, p1);
	}

	static void LUA_NATIVE_NETWORK_NETWORK_TRANSITION_BLOCK_JOIN_REQUESTS( bool p0 )
	{
		NETWORK::NETWORK_TRANSITION_BLOCK_JOIN_REQUESTS(p0);
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_HAS_PLAYER_STARTED_TRANSITION( Player player )
	{
		auto retval = (bool)NETWORK::NETWORK_HAS_PLAYER_STARTED_TRANSITION(player);
		return retval;
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_ARE_TRANSITION_DETAILS_VALID( Any p0 )
	{
		auto retval = (bool)NETWORK::NETWORK_ARE_TRANSITION_DETAILS_VALID(p0);
		return retval;
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_JOIN_TRANSITION( Player player )
	{
		auto retval = (bool)NETWORK::NETWORK_JOIN_TRANSITION(player);
		return retval;
	}

	static std::tuple<bool, Any> LUA_NATIVE_NETWORK_NETWORK_HAS_INVITED_GAMER_TO_TRANSITION( Any p0 )
	{
		std::tuple<bool, Any> return_values;
		std::get<0>(return_values) = (bool)NETWORK::NETWORK_HAS_INVITED_GAMER_TO_TRANSITION(&p0);
		std::get<1>(return_values) = p0;

		return return_values;
	}

	static std::tuple<bool, Any> LUA_NATIVE_NETWORK_NETWORK_HAS_TRANSITION_INVITE_BEEN_ACKED( Any p0 )
	{
		std::tuple<bool, Any> return_values;
		std::get<0>(return_values) = (bool)NETWORK::NETWORK_HAS_TRANSITION_INVITE_BEEN_ACKED(&p0);
		std::get<1>(return_values) = p0;

		return return_values;
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_IS_ACTIVITY_SESSION(  )
	{
		auto retval = (bool)NETWORK::NETWORK_IS_ACTIVITY_SESSION();
		return retval;
	}

	static void LUA_NATIVE_NETWORK_NETWORK_DISABLE_REALTIME_MULTIPLAYER(  )
	{
		NETWORK::NETWORK_DISABLE_REALTIME_MULTIPLAYER();
	}

	static void LUA_NATIVE_NETWORK_NETWORK_SET_PRESENCE_SESSION_INVITES_BLOCKED( bool toggle )
	{
		NETWORK::NETWORK_SET_PRESENCE_SESSION_INVITES_BLOCKED(toggle);
	}

	static std::tuple<bool, Any> LUA_NATIVE_NETWORK_NETWORK_SEND_INVITE_VIA_PRESENCE( Any gamerHandle, const char* p1, int dataCount, int p3 )
	{
		std::tuple<bool, Any> return_values;
		std::get<0>(return_values) = (bool)NETWORK::NETWORK_SEND_INVITE_VIA_PRESENCE(&gamerHandle, p1, dataCount, p3);
		std::get<1>(return_values) = gamerHandle;

		return return_values;
	}

	static std::tuple<bool, Any> LUA_NATIVE_NETWORK_NETWORK_SEND_TRANSITION_INVITE_VIA_PRESENCE( Any gamerHandle, const char* p1, int dataCount, int p3 )
	{
		std::tuple<bool, Any> return_values;
		std::get<0>(return_values) = (bool)NETWORK::NETWORK_SEND_TRANSITION_INVITE_VIA_PRESENCE(&gamerHandle, p1, dataCount, p3);
		std::get<1>(return_values) = gamerHandle;

		return return_values;
	}

	static std::tuple<bool, Any> LUA_NATIVE_NETWORK_NETWORK_SEND_IMPORTANT_TRANSITION_INVITE_VIA_PRESENCE( Any gamerHandle, const char* p1, int dataCount, int p3 )
	{
		std::tuple<bool, Any> return_values;
		std::get<0>(return_values) = (bool)NETWORK::NETWORK_SEND_IMPORTANT_TRANSITION_INVITE_VIA_PRESENCE(&gamerHandle, p1, dataCount, p3);
		std::get<1>(return_values) = gamerHandle;

		return return_values;
	}

	static int LUA_NATIVE_NETWORK_NETWORK_GET_PRESENCE_INVITE_INDEX_BY_ID( int p0 )
	{
		auto retval = NETWORK::NETWORK_GET_PRESENCE_INVITE_INDEX_BY_ID(p0);
		return retval;
	}

	static int LUA_NATIVE_NETWORK_NETWORK_GET_NUM_PRESENCE_INVITES(  )
	{
		auto retval = NETWORK::NETWORK_GET_NUM_PRESENCE_INVITES();
		return retval;
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_ACCEPT_PRESENCE_INVITE( int p0 )
	{
		auto retval = (bool)NETWORK::NETWORK_ACCEPT_PRESENCE_INVITE(p0);
		return retval;
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_REMOVE_PRESENCE_INVITE( int p0 )
	{
		auto retval = (bool)NETWORK::NETWORK_REMOVE_PRESENCE_INVITE(p0);
		return retval;
	}

	static int LUA_NATIVE_NETWORK_NETWORK_GET_PRESENCE_INVITE_ID( int p0 )
	{
		auto retval = NETWORK::NETWORK_GET_PRESENCE_INVITE_ID(p0);
		return retval;
	}

	static const char* LUA_NATIVE_NETWORK_NETWORK_GET_PRESENCE_INVITE_INVITER( int p0 )
	{
		auto retval = NETWORK::NETWORK_GET_PRESENCE_INVITE_INVITER(p0);
		return retval;
	}

	static std::tuple<bool, Any> LUA_NATIVE_NETWORK_NETWORK_GET_PRESENCE_INVITE_HANDLE( Any p0, Any p1 )
	{
		std::tuple<bool, Any> return_values;
		std::get<0>(return_values) = (bool)NETWORK::NETWORK_GET_PRESENCE_INVITE_HANDLE(p0, &p1);
		std::get<1>(return_values) = p1;

		return return_values;
	}

	static int LUA_NATIVE_NETWORK_NETWORK_GET_PRESENCE_INVITE_SESSION_ID( Any p0 )
	{
		auto retval = NETWORK::NETWORK_GET_PRESENCE_INVITE_SESSION_ID(p0);
		return retval;
	}

	static const char* LUA_NATIVE_NETWORK_NETWORK_GET_PRESENCE_INVITE_CONTENT_ID( int p0 )
	{
		auto retval = NETWORK::NETWORK_GET_PRESENCE_INVITE_CONTENT_ID(p0);
		return retval;
	}

	static int LUA_NATIVE_NETWORK_NETWORK_GET_PRESENCE_INVITE_PLAYLIST_LENGTH( int p0 )
	{
		auto retval = NETWORK::NETWORK_GET_PRESENCE_INVITE_PLAYLIST_LENGTH(p0);
		return retval;
	}

	static int LUA_NATIVE_NETWORK_NETWORK_GET_PRESENCE_INVITE_PLAYLIST_CURRENT( int p0 )
	{
		auto retval = NETWORK::NETWORK_GET_PRESENCE_INVITE_PLAYLIST_CURRENT(p0);
		return retval;
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_GET_PRESENCE_INVITE_FROM_ADMIN( int p0 )
	{
		auto retval = (bool)NETWORK::NETWORK_GET_PRESENCE_INVITE_FROM_ADMIN(p0);
		return retval;
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_GET_PRESENCE_INVITE_IS_TOURNAMENT( Any p0 )
	{
		auto retval = (bool)NETWORK::NETWORK_GET_PRESENCE_INVITE_IS_TOURNAMENT(p0);
		return retval;
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_HAS_FOLLOW_INVITE(  )
	{
		auto retval = (bool)NETWORK::NETWORK_HAS_FOLLOW_INVITE();
		return retval;
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_ACTION_FOLLOW_INVITE(  )
	{
		auto retval = (bool)NETWORK::NETWORK_ACTION_FOLLOW_INVITE();
		return retval;
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_CLEAR_FOLLOW_INVITE(  )
	{
		auto retval = (bool)NETWORK::NETWORK_CLEAR_FOLLOW_INVITE();
		return retval;
	}

	static void LUA_NATIVE_NETWORK_NETWORK_REMOVE_AND_CANCEL_ALL_INVITES(  )
	{
		NETWORK::NETWORK_REMOVE_AND_CANCEL_ALL_INVITES();
	}

	static Any LUA_NATIVE_NETWORK_NETWORK_REMOVE_TRANSITION_INVITE( Any p0 )
	{
		NETWORK::NETWORK_REMOVE_TRANSITION_INVITE(&p0);
		return p0;
	}

	static void LUA_NATIVE_NETWORK_NETWORK_REMOVE_ALL_TRANSITION_INVITE(  )
	{
		NETWORK::NETWORK_REMOVE_ALL_TRANSITION_INVITE();
	}

	static void LUA_NATIVE_NETWORK_NETWORK_REMOVE_AND_CANCEL_ALL_TRANSITION_INVITES(  )
	{
		NETWORK::NETWORK_REMOVE_AND_CANCEL_ALL_TRANSITION_INVITES();
	}

	static std::tuple<bool, Any, Any> LUA_NATIVE_NETWORK_NETWORK_INVITE_GAMERS( Any p0, Any p1, Any p2, Any p3 )
	{
		std::tuple<bool, Any, Any> return_values;
		std::get<0>(return_values) = (bool)NETWORK::NETWORK_INVITE_GAMERS(&p0, p1, &p2, p3);
		std::get<1>(return_values) = p0;
		std::get<2>(return_values) = p2;

		return return_values;
	}

	static std::tuple<bool, Any> LUA_NATIVE_NETWORK_NETWORK_HAS_INVITED_GAMER( Any p0 )
	{
		std::tuple<bool, Any> return_values;
		std::get<0>(return_values) = (bool)NETWORK::NETWORK_HAS_INVITED_GAMER(&p0);
		std::get<1>(return_values) = p0;

		return return_values;
	}

	static std::tuple<bool, Any> LUA_NATIVE_NETWORK_NETWORK_HAS_MADE_INVITE_DECISION( Any gamerHandle )
	{
		std::tuple<bool, Any> return_values;
		std::get<0>(return_values) = (bool)NETWORK::NETWORK_HAS_MADE_INVITE_DECISION(&gamerHandle);
		std::get<1>(return_values) = gamerHandle;

		return return_values;
	}

	static int LUA_NATIVE_NETWORK_NETWORK_GET_INVITE_REPLY_STATUS( Any p0 )
	{
		auto retval = NETWORK::NETWORK_GET_INVITE_REPLY_STATUS(p0);
		return retval;
	}

	static std::tuple<bool, Any> LUA_NATIVE_NETWORK_NETWORK_GET_CURRENTLY_SELECTED_GAMER_HANDLE_FROM_INVITE_MENU( Any p0 )
	{
		std::tuple<bool, Any> return_values;
		std::get<0>(return_values) = (bool)NETWORK::NETWORK_GET_CURRENTLY_SELECTED_GAMER_HANDLE_FROM_INVITE_MENU(&p0);
		std::get<1>(return_values) = p0;

		return return_values;
	}

	static std::tuple<bool, Any> LUA_NATIVE_NETWORK_NETWORK_SET_CURRENTLY_SELECTED_GAMER_HANDLE_FROM_INVITE_MENU( Any p0 )
	{
		std::tuple<bool, Any> return_values;
		std::get<0>(return_values) = (bool)NETWORK::NETWORK_SET_CURRENTLY_SELECTED_GAMER_HANDLE_FROM_INVITE_MENU(&p0);
		std::get<1>(return_values) = p0;

		return return_values;
	}

	static Any LUA_NATIVE_NETWORK_NETWORK_SET_INVITE_ON_CALL_FOR_INVITE_MENU( Any p0 )
	{
		NETWORK::NETWORK_SET_INVITE_ON_CALL_FOR_INVITE_MENU(&p0);
		return p0;
	}

	static std::tuple<bool, Any> LUA_NATIVE_NETWORK_NETWORK_CHECK_DATA_MANAGER_SUCCEEDED_FOR_HANDLE( int p0, Any gamerHandle )
	{
		std::tuple<bool, Any> return_values;
		std::get<0>(return_values) = (bool)NETWORK::NETWORK_CHECK_DATA_MANAGER_SUCCEEDED_FOR_HANDLE(p0, &gamerHandle);
		std::get<1>(return_values) = gamerHandle;

		return return_values;
	}

	static std::tuple<bool, Any> LUA_NATIVE_NETWORK_NETWORK_CHECK_DATA_MANAGER_FOR_HANDLE( Any p0, Any gamerHandle )
	{
		std::tuple<bool, Any> return_values;
		std::get<0>(return_values) = (bool)NETWORK::NETWORK_CHECK_DATA_MANAGER_FOR_HANDLE(p0, &gamerHandle);
		std::get<1>(return_values) = gamerHandle;

		return return_values;
	}

	static std::tuple<Any, Any> LUA_NATIVE_NETWORK_NETWORK_SET_INVITE_FAILED_MESSAGE_FOR_INVITE_MENU( Any p0, Any p1 )
	{
		std::tuple<Any, Any> return_values;
		NETWORK::NETWORK_SET_INVITE_FAILED_MESSAGE_FOR_INVITE_MENU(&p0, &p1);
		std::get<0>(return_values) = p0;
		std::get<1>(return_values) = p1;

		return return_values;
	}

	static std::tuple<bool, Any> LUA_NATIVE_NETWORK_FILLOUT_PM_PLAYER_LIST( Any gamerHandle, Any p1, Any p2 )
	{
		std::tuple<bool, Any> return_values;
		std::get<0>(return_values) = (bool)NETWORK::FILLOUT_PM_PLAYER_LIST(&gamerHandle, p1, p2);
		std::get<1>(return_values) = gamerHandle;

		return return_values;
	}

	static std::tuple<bool, Any, Any> LUA_NATIVE_NETWORK_FILLOUT_PM_PLAYER_LIST_WITH_NAMES( Any p0, Any p1, Any p2, Any p3 )
	{
		std::tuple<bool, Any, Any> return_values;
		std::get<0>(return_values) = (bool)NETWORK::FILLOUT_PM_PLAYER_LIST_WITH_NAMES(&p0, &p1, p2, p3);
		std::get<1>(return_values) = p0;
		std::get<2>(return_values) = p1;

		return return_values;
	}

	static bool LUA_NATIVE_NETWORK_REFRESH_PLAYER_LIST_STATS( int p0 )
	{
		auto retval = (bool)NETWORK::REFRESH_PLAYER_LIST_STATS(p0);
		return retval;
	}

	static std::tuple<bool, Any> LUA_NATIVE_NETWORK_NETWORK_SET_CURRENT_DATA_MANAGER_HANDLE( Any p0 )
	{
		std::tuple<bool, Any> return_values;
		std::get<0>(return_values) = (bool)NETWORK::NETWORK_SET_CURRENT_DATA_MANAGER_HANDLE(&p0);
		std::get<1>(return_values) = p0;

		return return_values;
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_IS_IN_PLATFORM_PARTY(  )
	{
		auto retval = (bool)NETWORK::NETWORK_IS_IN_PLATFORM_PARTY();
		return retval;
	}

	static int LUA_NATIVE_NETWORK_NETWORK_GET_PLATFORM_PARTY_MEMBER_COUNT(  )
	{
		auto retval = NETWORK::NETWORK_GET_PLATFORM_PARTY_MEMBER_COUNT();
		return retval;
	}

	static std::tuple<int, Any> LUA_NATIVE_NETWORK_NETWORK_GET_PLATFORM_PARTY_MEMBERS( Any data, int dataSize )
	{
		std::tuple<int, Any> return_values;
		std::get<0>(return_values) = NETWORK::NETWORK_GET_PLATFORM_PARTY_MEMBERS(&data, dataSize);
		std::get<1>(return_values) = data;

		return return_values;
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_IS_IN_PLATFORM_PARTY_CHAT(  )
	{
		auto retval = (bool)NETWORK::NETWORK_IS_IN_PLATFORM_PARTY_CHAT();
		return retval;
	}

	static std::tuple<bool, Any> LUA_NATIVE_NETWORK_NETWORK_IS_CHATTING_IN_PLATFORM_PARTY( Any gamerHandle )
	{
		std::tuple<bool, Any> return_values;
		std::get<0>(return_values) = (bool)NETWORK::NETWORK_IS_CHATTING_IN_PLATFORM_PARTY(&gamerHandle);
		std::get<1>(return_values) = gamerHandle;

		return return_values;
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_CAN_QUEUE_FOR_PREVIOUS_SESSION_JOIN(  )
	{
		auto retval = (bool)NETWORK::NETWORK_CAN_QUEUE_FOR_PREVIOUS_SESSION_JOIN();
		return retval;
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_IS_QUEUING_FOR_SESSION_JOIN(  )
	{
		auto retval = (bool)NETWORK::NETWORK_IS_QUEUING_FOR_SESSION_JOIN();
		return retval;
	}

	static void LUA_NATIVE_NETWORK_NETWORK_CLEAR_QUEUED_JOIN_REQUEST(  )
	{
		NETWORK::NETWORK_CLEAR_QUEUED_JOIN_REQUEST();
	}

	static void LUA_NATIVE_NETWORK_NETWORK_SEND_QUEUED_JOIN_REQUEST(  )
	{
		NETWORK::NETWORK_SEND_QUEUED_JOIN_REQUEST();
	}

	static void LUA_NATIVE_NETWORK_NETWORK_REMOVE_ALL_QUEUED_JOIN_REQUESTS(  )
	{
		NETWORK::NETWORK_REMOVE_ALL_QUEUED_JOIN_REQUESTS();
	}

	static void LUA_NATIVE_NETWORK_NETWORK_SEED_RANDOM_NUMBER_GENERATOR( int seed )
	{
		NETWORK::NETWORK_SEED_RANDOM_NUMBER_GENERATOR(seed);
	}

	static int LUA_NATIVE_NETWORK_NETWORK_GET_RANDOM_INT(  )
	{
		auto retval = NETWORK::NETWORK_GET_RANDOM_INT();
		return retval;
	}

	static int LUA_NATIVE_NETWORK_NETWORK_GET_RANDOM_INT_RANGED( int rangeStart, int rangeEnd )
	{
		auto retval = NETWORK::NETWORK_GET_RANDOM_INT_RANGED(rangeStart, rangeEnd);
		return retval;
	}

	static float LUA_NATIVE_NETWORK_NETWORK_GET_RANDOM_FLOAT_RANGED_( float rangeStart, float rangeEnd )
	{
		auto retval = NETWORK::NETWORK_GET_RANDOM_FLOAT_RANGED_(rangeStart, rangeEnd);
		return retval;
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_PLAYER_IS_CHEATER(  )
	{
		auto retval = (bool)NETWORK::NETWORK_PLAYER_IS_CHEATER();
		return retval;
	}

	static int LUA_NATIVE_NETWORK_NETWORK_PLAYER_GET_CHEATER_REASON(  )
	{
		auto retval = NETWORK::NETWORK_PLAYER_GET_CHEATER_REASON();
		return retval;
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_PLAYER_IS_BADSPORT(  )
	{
		auto retval = (bool)NETWORK::NETWORK_PLAYER_IS_BADSPORT();
		return retval;
	}

	static bool LUA_NATIVE_NETWORK_REMOTE_CHEATER_PLAYER_DETECTED( Player player, int a, int b )
	{
		auto retval = (bool)NETWORK::REMOTE_CHEATER_PLAYER_DETECTED(player, a, b);
		return retval;
	}

	static std::tuple<bool, Any> LUA_NATIVE_NETWORK_BAD_SPORT_PLAYER_LEFT_DETECTED( Any gamerHandle, int event, int amountReceived )
	{
		std::tuple<bool, Any> return_values;
		std::get<0>(return_values) = (bool)NETWORK::BAD_SPORT_PLAYER_LEFT_DETECTED(&gamerHandle, event, amountReceived);
		std::get<1>(return_values) = gamerHandle;

		return return_values;
	}

	static void LUA_NATIVE_NETWORK_NETWORK_ADD_INVALID_OBJECT_MODEL( Hash modelHash )
	{
		NETWORK::NETWORK_ADD_INVALID_OBJECT_MODEL(modelHash);
	}

	static void LUA_NATIVE_NETWORK_NETWORK_REMOVE_INVALID_OBJECT_MODEL( Hash modelHash )
	{
		NETWORK::NETWORK_REMOVE_INVALID_OBJECT_MODEL(modelHash);
	}

	static void LUA_NATIVE_NETWORK_NETWORK_CLEAR_INVALID_OBJECT_MODELS(  )
	{
		NETWORK::NETWORK_CLEAR_INVALID_OBJECT_MODELS();
	}

	static void LUA_NATIVE_NETWORK_NETWORK_APPLY_PED_SCAR_DATA( Ped ped, int p1 )
	{
		NETWORK::NETWORK_APPLY_PED_SCAR_DATA(ped, p1);
	}

	static void LUA_NATIVE_NETWORK_NETWORK_SET_THIS_SCRIPT_IS_NETWORK_SCRIPT( int maxNumMissionParticipants, bool p1, int instanceId )
	{
		NETWORK::NETWORK_SET_THIS_SCRIPT_IS_NETWORK_SCRIPT(maxNumMissionParticipants, p1, instanceId);
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_TRY_TO_SET_THIS_SCRIPT_IS_NETWORK_SCRIPT( Any p0, bool p1, Any p2 )
	{
		auto retval = (bool)NETWORK::NETWORK_TRY_TO_SET_THIS_SCRIPT_IS_NETWORK_SCRIPT(p0, p1, p2);
		return retval;
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_GET_THIS_SCRIPT_IS_NETWORK_SCRIPT(  )
	{
		auto retval = (bool)NETWORK::NETWORK_GET_THIS_SCRIPT_IS_NETWORK_SCRIPT();
		return retval;
	}

	static int LUA_NATIVE_NETWORK_NETWORK_GET_MAX_NUM_PARTICIPANTS(  )
	{
		auto retval = NETWORK::NETWORK_GET_MAX_NUM_PARTICIPANTS();
		return retval;
	}

	static int LUA_NATIVE_NETWORK_NETWORK_GET_NUM_PARTICIPANTS(  )
	{
		auto retval = NETWORK::NETWORK_GET_NUM_PARTICIPANTS();
		return retval;
	}

	static int LUA_NATIVE_NETWORK_NETWORK_GET_SCRIPT_STATUS(  )
	{
		auto retval = NETWORK::NETWORK_GET_SCRIPT_STATUS();
		return retval;
	}

	static int LUA_NATIVE_NETWORK_NETWORK_REGISTER_HOST_BROADCAST_VARIABLES( int vars, int numVars, const char* debugName )
	{
		NETWORK::NETWORK_REGISTER_HOST_BROADCAST_VARIABLES(&vars, numVars, debugName);
		return vars;
	}

	static int LUA_NATIVE_NETWORK_NETWORK_REGISTER_PLAYER_BROADCAST_VARIABLES( int vars, int numVars, const char* debugName )
	{
		NETWORK::NETWORK_REGISTER_PLAYER_BROADCAST_VARIABLES(&vars, numVars, debugName);
		return vars;
	}

	static void LUA_NATIVE_NETWORK_NETWORK_REGISTER_HIGH_FREQUENCY_HOST_BROADCAST_VARIABLES( Any p0, Any p1, Any p2 )
	{
		NETWORK::NETWORK_REGISTER_HIGH_FREQUENCY_HOST_BROADCAST_VARIABLES(p0, p1, p2);
	}

	static void LUA_NATIVE_NETWORK_NETWORK_REGISTER_HIGH_FREQUENCY_PLAYER_BROADCAST_VARIABLES( Any p0, Any p1, Any p2 )
	{
		NETWORK::NETWORK_REGISTER_HIGH_FREQUENCY_PLAYER_BROADCAST_VARIABLES(p0, p1, p2);
	}

	static void LUA_NATIVE_NETWORK_NETWORK_FINISH_BROADCASTING_DATA(  )
	{
		NETWORK::NETWORK_FINISH_BROADCASTING_DATA();
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_HAS_RECEIVED_HOST_BROADCAST_DATA(  )
	{
		auto retval = (bool)NETWORK::NETWORK_HAS_RECEIVED_HOST_BROADCAST_DATA();
		return retval;
	}

	static Player LUA_NATIVE_NETWORK_NETWORK_GET_PLAYER_INDEX( Player player )
	{
		auto retval = NETWORK::NETWORK_GET_PLAYER_INDEX(player);
		return retval;
	}

	static int LUA_NATIVE_NETWORK_NETWORK_GET_PARTICIPANT_INDEX( int index )
	{
		auto retval = NETWORK::NETWORK_GET_PARTICIPANT_INDEX(index);
		return retval;
	}

	static Player LUA_NATIVE_NETWORK_NETWORK_GET_PLAYER_INDEX_FROM_PED( Ped ped )
	{
		auto retval = NETWORK::NETWORK_GET_PLAYER_INDEX_FROM_PED(ped);
		return retval;
	}

	static int LUA_NATIVE_NETWORK_NETWORK_GET_NUM_CONNECTED_PLAYERS(  )
	{
		auto retval = NETWORK::NETWORK_GET_NUM_CONNECTED_PLAYERS();
		return retval;
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_IS_PLAYER_CONNECTED( Player player )
	{
		auto retval = (bool)NETWORK::NETWORK_IS_PLAYER_CONNECTED(player);
		return retval;
	}

	static int LUA_NATIVE_NETWORK_NETWORK_GET_TOTAL_NUM_PLAYERS(  )
	{
		auto retval = NETWORK::NETWORK_GET_TOTAL_NUM_PLAYERS();
		return retval;
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_IS_PARTICIPANT_ACTIVE( int p0 )
	{
		auto retval = (bool)NETWORK::NETWORK_IS_PARTICIPANT_ACTIVE(p0);
		return retval;
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_IS_PLAYER_ACTIVE( Player player )
	{
		auto retval = (bool)NETWORK::NETWORK_IS_PLAYER_ACTIVE(player);
		return retval;
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_IS_PLAYER_A_PARTICIPANT( Player player )
	{
		auto retval = (bool)NETWORK::NETWORK_IS_PLAYER_A_PARTICIPANT(player);
		return retval;
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_IS_HOST_OF_THIS_SCRIPT(  )
	{
		auto retval = (bool)NETWORK::NETWORK_IS_HOST_OF_THIS_SCRIPT();
		return retval;
	}

	static Player LUA_NATIVE_NETWORK_NETWORK_GET_HOST_OF_THIS_SCRIPT(  )
	{
		auto retval = NETWORK::NETWORK_GET_HOST_OF_THIS_SCRIPT();
		return retval;
	}

	static Player LUA_NATIVE_NETWORK_NETWORK_GET_HOST_OF_SCRIPT( const char* scriptName, int instance_id, int position_hash )
	{
		auto retval = NETWORK::NETWORK_GET_HOST_OF_SCRIPT(scriptName, instance_id, position_hash);
		return retval;
	}

	static void LUA_NATIVE_NETWORK_NETWORK_SET_MISSION_FINISHED(  )
	{
		NETWORK::NETWORK_SET_MISSION_FINISHED();
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_IS_SCRIPT_ACTIVE( const char* scriptName, int instance_id, bool p2, int position_hash )
	{
		auto retval = (bool)NETWORK::NETWORK_IS_SCRIPT_ACTIVE(scriptName, instance_id, p2, position_hash);
		return retval;
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_IS_SCRIPT_ACTIVE_BY_HASH( Hash scriptHash, int p1, bool p2, int p3 )
	{
		auto retval = (bool)NETWORK::NETWORK_IS_SCRIPT_ACTIVE_BY_HASH(scriptHash, p1, p2, p3);
		return retval;
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_IS_THREAD_A_NETWORK_SCRIPT( int threadId )
	{
		auto retval = (bool)NETWORK::NETWORK_IS_THREAD_A_NETWORK_SCRIPT(threadId);
		return retval;
	}

	static int LUA_NATIVE_NETWORK_NETWORK_GET_NUM_SCRIPT_PARTICIPANTS( const char* scriptName, int instance_id, int position_hash )
	{
		auto retval = NETWORK::NETWORK_GET_NUM_SCRIPT_PARTICIPANTS(scriptName, instance_id, position_hash);
		return retval;
	}

	static int LUA_NATIVE_NETWORK_NETWORK_GET_INSTANCE_ID_OF_THIS_SCRIPT(  )
	{
		auto retval = NETWORK::NETWORK_GET_INSTANCE_ID_OF_THIS_SCRIPT();
		return retval;
	}

	static Hash LUA_NATIVE_NETWORK_NETWORK_GET_POSITION_HASH_OF_THIS_SCRIPT(  )
	{
		auto retval = NETWORK::NETWORK_GET_POSITION_HASH_OF_THIS_SCRIPT();
		return retval;
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_IS_PLAYER_A_PARTICIPANT_ON_SCRIPT( Player player, const char* script, int instance_id )
	{
		auto retval = (bool)NETWORK::NETWORK_IS_PLAYER_A_PARTICIPANT_ON_SCRIPT(player, script, instance_id);
		return retval;
	}

	static void LUA_NATIVE_NETWORK_NETWORK_PREVENT_SCRIPT_HOST_MIGRATION(  )
	{
		NETWORK::NETWORK_PREVENT_SCRIPT_HOST_MIGRATION();
	}

	static void LUA_NATIVE_NETWORK_NETWORK_REQUEST_TO_BE_HOST_OF_THIS_SCRIPT(  )
	{
		NETWORK::NETWORK_REQUEST_TO_BE_HOST_OF_THIS_SCRIPT();
	}

	static Player LUA_NATIVE_NETWORK_PARTICIPANT_ID(  )
	{
		auto retval = NETWORK::PARTICIPANT_ID();
		return retval;
	}

	static int LUA_NATIVE_NETWORK_PARTICIPANT_ID_TO_INT(  )
	{
		auto retval = NETWORK::PARTICIPANT_ID_TO_INT();
		return retval;
	}

	static std::tuple<Player, Hash> LUA_NATIVE_NETWORK_NETWORK_GET_KILLER_OF_PLAYER( Player player, Hash weaponHash )
	{
		std::tuple<Player, Hash> return_values;
		std::get<0>(return_values) = NETWORK::NETWORK_GET_KILLER_OF_PLAYER(player, &weaponHash);
		std::get<1>(return_values) = weaponHash;

		return return_values;
	}

	static std::tuple<Player, Hash> LUA_NATIVE_NETWORK_NETWORK_GET_DESTROYER_OF_NETWORK_ID( int netId, Hash weaponHash )
	{
		std::tuple<Player, Hash> return_values;
		std::get<0>(return_values) = NETWORK::NETWORK_GET_DESTROYER_OF_NETWORK_ID(netId, &weaponHash);
		std::get<1>(return_values) = weaponHash;

		return return_values;
	}

	static std::tuple<Player, Hash> LUA_NATIVE_NETWORK_NETWORK_GET_DESTROYER_OF_ENTITY( Entity entity, Hash weaponHash )
	{
		std::tuple<Player, Hash> return_values;
		std::get<0>(return_values) = NETWORK::NETWORK_GET_DESTROYER_OF_ENTITY(entity, &weaponHash);
		std::get<1>(return_values) = weaponHash;

		return return_values;
	}

	static std::tuple<bool, int> LUA_NATIVE_NETWORK_NETWORK_GET_ASSISTED_KILL_OF_ENTITY( Player player, Entity entity, int p2 )
	{
		std::tuple<bool, int> return_values;
		std::get<0>(return_values) = (bool)NETWORK::NETWORK_GET_ASSISTED_KILL_OF_ENTITY(player, entity, &p2);
		std::get<1>(return_values) = p2;

		return return_values;
	}

	static std::tuple<bool, int> LUA_NATIVE_NETWORK_NETWORK_GET_ASSISTED_DAMAGE_OF_ENTITY( Player player, Entity entity, int p2 )
	{
		std::tuple<bool, int> return_values;
		std::get<0>(return_values) = (bool)NETWORK::NETWORK_GET_ASSISTED_DAMAGE_OF_ENTITY(player, entity, &p2);
		std::get<1>(return_values) = p2;

		return return_values;
	}

	static std::tuple<Entity, Hash> LUA_NATIVE_NETWORK_NETWORK_GET_ENTITY_KILLER_OF_PLAYER( Player player, Hash weaponHash )
	{
		std::tuple<Entity, Hash> return_values;
		std::get<0>(return_values) = NETWORK::NETWORK_GET_ENTITY_KILLER_OF_PLAYER(player, &weaponHash);
		std::get<1>(return_values) = weaponHash;

		return return_values;
	}

	static void LUA_NATIVE_NETWORK_NETWORK_SET_CURRENT_PUBLIC_CONTENT_ID( const char* missionId )
	{
		NETWORK::NETWORK_SET_CURRENT_PUBLIC_CONTENT_ID(missionId);
	}

	static void LUA_NATIVE_NETWORK_NETWORK_SET_CURRENT_CHAT_OPTION( int newChatOption )
	{
		NETWORK::NETWORK_SET_CURRENT_CHAT_OPTION(newChatOption);
	}

	static void LUA_NATIVE_NETWORK_NETWORK_SET_CURRENT_SPAWN_LOCATION_OPTION( Hash mpSettingSpawn )
	{
		NETWORK::NETWORK_SET_CURRENT_SPAWN_LOCATION_OPTION(mpSettingSpawn);
	}

	static void LUA_NATIVE_NETWORK_NETWORK_SET_VEHICLE_DRIVEN_IN_TEST_DRIVE( bool toggle )
	{
		NETWORK::NETWORK_SET_VEHICLE_DRIVEN_IN_TEST_DRIVE(toggle);
	}

	static void LUA_NATIVE_NETWORK_NETWORK_SET_VEHICLE_DRIVEN_LOCATION( Hash location )
	{
		NETWORK::NETWORK_SET_VEHICLE_DRIVEN_LOCATION(location);
	}

	static void LUA_NATIVE_NETWORK_NETWORK_RESURRECT_LOCAL_PLAYER( float x, float y, float z, float heading, bool p4, bool changetime, bool p6, int p7, int p8 )
	{
		NETWORK::NETWORK_RESURRECT_LOCAL_PLAYER(x, y, z, heading, p4, changetime, p6, p7, p8);
	}

	static void LUA_NATIVE_NETWORK_NETWORK_SET_LOCAL_PLAYER_INVINCIBLE_TIME( int time )
	{
		NETWORK::NETWORK_SET_LOCAL_PLAYER_INVINCIBLE_TIME(time);
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_IS_LOCAL_PLAYER_INVINCIBLE(  )
	{
		auto retval = (bool)NETWORK::NETWORK_IS_LOCAL_PLAYER_INVINCIBLE();
		return retval;
	}

	static void LUA_NATIVE_NETWORK_NETWORK_DISABLE_INVINCIBLE_FLASHING( Player player, bool toggle )
	{
		NETWORK::NETWORK_DISABLE_INVINCIBLE_FLASHING(player, toggle);
	}

	static void LUA_NATIVE_NETWORK_NETWORK_PATCH_POST_CUTSCENE_HS4F_TUN_ENT( Ped ped )
	{
		NETWORK::NETWORK_PATCH_POST_CUTSCENE_HS4F_TUN_ENT(ped);
	}

	static void LUA_NATIVE_NETWORK_NETWORK_SET_LOCAL_PLAYER_SYNC_LOOK_AT( bool toggle )
	{
		NETWORK::NETWORK_SET_LOCAL_PLAYER_SYNC_LOOK_AT(toggle);
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_HAS_ENTITY_BEEN_REGISTERED_WITH_THIS_THREAD( Entity entity )
	{
		auto retval = (bool)NETWORK::NETWORK_HAS_ENTITY_BEEN_REGISTERED_WITH_THIS_THREAD(entity);
		return retval;
	}

	static int LUA_NATIVE_NETWORK_NETWORK_GET_NETWORK_ID_FROM_ENTITY( Entity entity )
	{
		auto retval = NETWORK::NETWORK_GET_NETWORK_ID_FROM_ENTITY(entity);
		return retval;
	}

	static Entity LUA_NATIVE_NETWORK_NETWORK_GET_ENTITY_FROM_NETWORK_ID( int netId )
	{
		auto retval = NETWORK::NETWORK_GET_ENTITY_FROM_NETWORK_ID(netId);
		return retval;
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_GET_ENTITY_IS_NETWORKED( Entity entity )
	{
		auto retval = (bool)NETWORK::NETWORK_GET_ENTITY_IS_NETWORKED(entity);
		return retval;
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_GET_ENTITY_IS_LOCAL( Entity entity )
	{
		auto retval = (bool)NETWORK::NETWORK_GET_ENTITY_IS_LOCAL(entity);
		return retval;
	}

	static void LUA_NATIVE_NETWORK_NETWORK_REGISTER_ENTITY_AS_NETWORKED( Entity entity )
	{
		NETWORK::NETWORK_REGISTER_ENTITY_AS_NETWORKED(entity);
	}

	static void LUA_NATIVE_NETWORK_NETWORK_UNREGISTER_NETWORKED_ENTITY( Entity entity )
	{
		NETWORK::NETWORK_UNREGISTER_NETWORKED_ENTITY(entity);
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_DOES_NETWORK_ID_EXIST( int netId )
	{
		auto retval = (bool)NETWORK::NETWORK_DOES_NETWORK_ID_EXIST(netId);
		return retval;
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_DOES_ENTITY_EXIST_WITH_NETWORK_ID( int netId )
	{
		auto retval = (bool)NETWORK::NETWORK_DOES_ENTITY_EXIST_WITH_NETWORK_ID(netId);
		return retval;
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_REQUEST_CONTROL_OF_NETWORK_ID( int netId )
	{
		auto retval = (bool)NETWORK::NETWORK_REQUEST_CONTROL_OF_NETWORK_ID(netId);
		return retval;
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_HAS_CONTROL_OF_NETWORK_ID( int netId )
	{
		auto retval = (bool)NETWORK::NETWORK_HAS_CONTROL_OF_NETWORK_ID(netId);
		return retval;
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_IS_NETWORK_ID_REMOTELY_CONTROLLED( int netId )
	{
		auto retval = (bool)NETWORK::NETWORK_IS_NETWORK_ID_REMOTELY_CONTROLLED(netId);
		return retval;
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_REQUEST_CONTROL_OF_ENTITY( Entity entity )
	{
		auto retval = (bool)NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(entity);
		return retval;
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_REQUEST_CONTROL_OF_DOOR( int doorID )
	{
		auto retval = (bool)NETWORK::NETWORK_REQUEST_CONTROL_OF_DOOR(doorID);
		return retval;
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_HAS_CONTROL_OF_ENTITY( Entity entity )
	{
		auto retval = (bool)NETWORK::NETWORK_HAS_CONTROL_OF_ENTITY(entity);
		return retval;
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_HAS_CONTROL_OF_PICKUP( Pickup pickup )
	{
		auto retval = (bool)NETWORK::NETWORK_HAS_CONTROL_OF_PICKUP(pickup);
		return retval;
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_HAS_CONTROL_OF_DOOR( Hash doorHash )
	{
		auto retval = (bool)NETWORK::NETWORK_HAS_CONTROL_OF_DOOR(doorHash);
		return retval;
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_IS_DOOR_NETWORKED( Hash doorHash )
	{
		auto retval = (bool)NETWORK::NETWORK_IS_DOOR_NETWORKED(doorHash);
		return retval;
	}

	static int LUA_NATIVE_NETWORK_VEH_TO_NET( Vehicle vehicle )
	{
		auto retval = NETWORK::VEH_TO_NET(vehicle);
		return retval;
	}

	static int LUA_NATIVE_NETWORK_PED_TO_NET( Ped ped )
	{
		auto retval = NETWORK::PED_TO_NET(ped);
		return retval;
	}

	static int LUA_NATIVE_NETWORK_OBJ_TO_NET( Object object )
	{
		auto retval = NETWORK::OBJ_TO_NET(object);
		return retval;
	}

	static Vehicle LUA_NATIVE_NETWORK_NET_TO_VEH( int netHandle )
	{
		auto retval = NETWORK::NET_TO_VEH(netHandle);
		return retval;
	}

	static Ped LUA_NATIVE_NETWORK_NET_TO_PED( int netHandle )
	{
		auto retval = NETWORK::NET_TO_PED(netHandle);
		return retval;
	}

	static Object LUA_NATIVE_NETWORK_NET_TO_OBJ( int netHandle )
	{
		auto retval = NETWORK::NET_TO_OBJ(netHandle);
		return retval;
	}

	static Entity LUA_NATIVE_NETWORK_NET_TO_ENT( int netHandle )
	{
		auto retval = NETWORK::NET_TO_ENT(netHandle);
		return retval;
	}

	static Any LUA_NATIVE_NETWORK_NETWORK_GET_LOCAL_HANDLE( Any gamerHandle, int gamerHandleSize )
	{
		NETWORK::NETWORK_GET_LOCAL_HANDLE(&gamerHandle, gamerHandleSize);
		return gamerHandle;
	}

	static Any LUA_NATIVE_NETWORK_NETWORK_HANDLE_FROM_USER_ID( const char* userId, Any gamerHandle, int gamerHandleSize )
	{
		NETWORK::NETWORK_HANDLE_FROM_USER_ID(userId, &gamerHandle, gamerHandleSize);
		return gamerHandle;
	}

	static Any LUA_NATIVE_NETWORK_NETWORK_HANDLE_FROM_MEMBER_ID( const char* memberId, Any gamerHandle, int gamerHandleSize )
	{
		NETWORK::NETWORK_HANDLE_FROM_MEMBER_ID(memberId, &gamerHandle, gamerHandleSize);
		return gamerHandle;
	}

	static Any LUA_NATIVE_NETWORK_NETWORK_HANDLE_FROM_PLAYER( Player player, Any gamerHandle, int gamerHandleSize )
	{
		NETWORK::NETWORK_HANDLE_FROM_PLAYER(player, &gamerHandle, gamerHandleSize);
		return gamerHandle;
	}

	static Hash LUA_NATIVE_NETWORK_NETWORK_HASH_FROM_PLAYER_HANDLE( Player player )
	{
		auto retval = NETWORK::NETWORK_HASH_FROM_PLAYER_HANDLE(player);
		return retval;
	}

	static std::tuple<Hash, Any> LUA_NATIVE_NETWORK_NETWORK_HASH_FROM_GAMER_HANDLE( Any gamerHandle )
	{
		std::tuple<Hash, Any> return_values;
		std::get<0>(return_values) = NETWORK::NETWORK_HASH_FROM_GAMER_HANDLE(&gamerHandle);
		std::get<1>(return_values) = gamerHandle;

		return return_values;
	}

	static Any LUA_NATIVE_NETWORK_NETWORK_HANDLE_FROM_FRIEND( int friendIndex, Any gamerHandle, int gamerHandleSize )
	{
		NETWORK::NETWORK_HANDLE_FROM_FRIEND(friendIndex, &gamerHandle, gamerHandleSize);
		return gamerHandle;
	}

	static std::tuple<bool, Any> LUA_NATIVE_NETWORK_NETWORK_GAMERTAG_FROM_HANDLE_START( Any gamerHandle )
	{
		std::tuple<bool, Any> return_values;
		std::get<0>(return_values) = (bool)NETWORK::NETWORK_GAMERTAG_FROM_HANDLE_START(&gamerHandle);
		std::get<1>(return_values) = gamerHandle;

		return return_values;
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_GAMERTAG_FROM_HANDLE_PENDING(  )
	{
		auto retval = (bool)NETWORK::NETWORK_GAMERTAG_FROM_HANDLE_PENDING();
		return retval;
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_GAMERTAG_FROM_HANDLE_SUCCEEDED(  )
	{
		auto retval = (bool)NETWORK::NETWORK_GAMERTAG_FROM_HANDLE_SUCCEEDED();
		return retval;
	}

	static std::tuple<const char*, Any> LUA_NATIVE_NETWORK_NETWORK_GET_GAMERTAG_FROM_HANDLE( Any gamerHandle )
	{
		std::tuple<const char*, Any> return_values;
		std::get<0>(return_values) = NETWORK::NETWORK_GET_GAMERTAG_FROM_HANDLE(&gamerHandle);
		std::get<1>(return_values) = gamerHandle;

		return return_values;
	}

	static std::tuple<int, Any> LUA_NATIVE_NETWORK_NETWORK_DISPLAYNAMES_FROM_HANDLES_START( Any p0, Any p1 )
	{
		std::tuple<int, Any> return_values;
		std::get<0>(return_values) = NETWORK::NETWORK_DISPLAYNAMES_FROM_HANDLES_START(&p0, p1);
		std::get<1>(return_values) = p0;

		return return_values;
	}

	static int LUA_NATIVE_NETWORK_NETWORK_GET_DISPLAYNAMES_FROM_HANDLES( Any p0, Any p1, Any p2 )
	{
		auto retval = NETWORK::NETWORK_GET_DISPLAYNAMES_FROM_HANDLES(p0, p1, p2);
		return retval;
	}

	static std::tuple<bool, Any, Any> LUA_NATIVE_NETWORK_NETWORK_ARE_HANDLES_THE_SAME( Any gamerHandle1, Any gamerHandle2 )
	{
		std::tuple<bool, Any, Any> return_values;
		std::get<0>(return_values) = (bool)NETWORK::NETWORK_ARE_HANDLES_THE_SAME(&gamerHandle1, &gamerHandle2);
		std::get<1>(return_values) = gamerHandle1;
		std::get<2>(return_values) = gamerHandle2;

		return return_values;
	}

	static std::tuple<bool, Any> LUA_NATIVE_NETWORK_NETWORK_IS_HANDLE_VALID( Any gamerHandle, int gamerHandleSize )
	{
		std::tuple<bool, Any> return_values;
		std::get<0>(return_values) = (bool)NETWORK::NETWORK_IS_HANDLE_VALID(&gamerHandle, gamerHandleSize);
		std::get<1>(return_values) = gamerHandle;

		return return_values;
	}

	static std::tuple<Player, Any> LUA_NATIVE_NETWORK_NETWORK_GET_PLAYER_FROM_GAMER_HANDLE( Any gamerHandle )
	{
		std::tuple<Player, Any> return_values;
		std::get<0>(return_values) = NETWORK::NETWORK_GET_PLAYER_FROM_GAMER_HANDLE(&gamerHandle);
		std::get<1>(return_values) = gamerHandle;

		return return_values;
	}

	static std::tuple<const char*, Any> LUA_NATIVE_NETWORK_NETWORK_MEMBER_ID_FROM_GAMER_HANDLE( Any gamerHandle )
	{
		std::tuple<const char*, Any> return_values;
		std::get<0>(return_values) = NETWORK::NETWORK_MEMBER_ID_FROM_GAMER_HANDLE(&gamerHandle);
		std::get<1>(return_values) = gamerHandle;

		return return_values;
	}

	static std::tuple<bool, Any> LUA_NATIVE_NETWORK_NETWORK_IS_GAMER_IN_MY_SESSION( Any gamerHandle )
	{
		std::tuple<bool, Any> return_values;
		std::get<0>(return_values) = (bool)NETWORK::NETWORK_IS_GAMER_IN_MY_SESSION(&gamerHandle);
		std::get<1>(return_values) = gamerHandle;

		return return_values;
	}

	static Any LUA_NATIVE_NETWORK_NETWORK_SHOW_PROFILE_UI( Any gamerHandle )
	{
		NETWORK::NETWORK_SHOW_PROFILE_UI(&gamerHandle);
		return gamerHandle;
	}

	static const char* LUA_NATIVE_NETWORK_NETWORK_PLAYER_GET_NAME( Player player )
	{
		auto retval = NETWORK::NETWORK_PLAYER_GET_NAME(player);
		return retval;
	}

	static std::tuple<const char*, int> LUA_NATIVE_NETWORK_NETWORK_PLAYER_GET_USERID( Player player, int userID )
	{
		std::tuple<const char*, int> return_values;
		std::get<0>(return_values) = NETWORK::NETWORK_PLAYER_GET_USERID(player, &userID);
		std::get<1>(return_values) = userID;

		return return_values;
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_PLAYER_IS_ROCKSTAR_DEV( Player player )
	{
		auto retval = (bool)NETWORK::NETWORK_PLAYER_IS_ROCKSTAR_DEV(player);
		return retval;
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_PLAYER_INDEX_IS_CHEATER( Player player )
	{
		auto retval = (bool)NETWORK::NETWORK_PLAYER_INDEX_IS_CHEATER(player);
		return retval;
	}

	static int LUA_NATIVE_NETWORK_NETWORK_ENTITY_GET_OBJECT_ID( Entity entity )
	{
		auto retval = NETWORK::NETWORK_ENTITY_GET_OBJECT_ID(entity);
		return retval;
	}

	static Entity LUA_NATIVE_NETWORK_NETWORK_GET_ENTITY_FROM_OBJECT_ID( Any p0 )
	{
		auto retval = NETWORK::NETWORK_GET_ENTITY_FROM_OBJECT_ID(p0);
		return retval;
	}

	static std::tuple<bool, Any> LUA_NATIVE_NETWORK_NETWORK_IS_INACTIVE_PROFILE( Any p0 )
	{
		std::tuple<bool, Any> return_values;
		std::get<0>(return_values) = (bool)NETWORK::NETWORK_IS_INACTIVE_PROFILE(&p0);
		std::get<1>(return_values) = p0;

		return return_values;
	}

	static int LUA_NATIVE_NETWORK_NETWORK_GET_MAX_FRIENDS(  )
	{
		auto retval = NETWORK::NETWORK_GET_MAX_FRIENDS();
		return retval;
	}

	static int LUA_NATIVE_NETWORK_NETWORK_GET_FRIEND_COUNT(  )
	{
		auto retval = NETWORK::NETWORK_GET_FRIEND_COUNT();
		return retval;
	}

	static const char* LUA_NATIVE_NETWORK_NETWORK_GET_FRIEND_NAME( int friendIndex )
	{
		auto retval = NETWORK::NETWORK_GET_FRIEND_NAME(friendIndex);
		return retval;
	}

	static const char* LUA_NATIVE_NETWORK_NETWORK_GET_FRIEND_DISPLAY_NAME( int friendIndex )
	{
		auto retval = NETWORK::NETWORK_GET_FRIEND_DISPLAY_NAME(friendIndex);
		return retval;
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_IS_FRIEND_ONLINE( const char* name )
	{
		auto retval = (bool)NETWORK::NETWORK_IS_FRIEND_ONLINE(name);
		return retval;
	}

	static std::tuple<bool, Any> LUA_NATIVE_NETWORK_NETWORK_IS_FRIEND_HANDLE_ONLINE( Any gamerHandle )
	{
		std::tuple<bool, Any> return_values;
		std::get<0>(return_values) = (bool)NETWORK::NETWORK_IS_FRIEND_HANDLE_ONLINE(&gamerHandle);
		std::get<1>(return_values) = gamerHandle;

		return return_values;
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_IS_FRIEND_IN_SAME_TITLE( const char* friendName )
	{
		auto retval = (bool)NETWORK::NETWORK_IS_FRIEND_IN_SAME_TITLE(friendName);
		return retval;
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_IS_FRIEND_IN_MULTIPLAYER( const char* friendName )
	{
		auto retval = (bool)NETWORK::NETWORK_IS_FRIEND_IN_MULTIPLAYER(friendName);
		return retval;
	}

	static std::tuple<bool, Any> LUA_NATIVE_NETWORK_NETWORK_IS_FRIEND( Any gamerHandle )
	{
		std::tuple<bool, Any> return_values;
		std::get<0>(return_values) = (bool)NETWORK::NETWORK_IS_FRIEND(&gamerHandle);
		std::get<1>(return_values) = gamerHandle;

		return return_values;
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_IS_PENDING_FRIEND( Any p0 )
	{
		auto retval = (bool)NETWORK::NETWORK_IS_PENDING_FRIEND(p0);
		return retval;
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_IS_ADDING_FRIEND(  )
	{
		auto retval = (bool)NETWORK::NETWORK_IS_ADDING_FRIEND();
		return retval;
	}

	static std::tuple<bool, Any> LUA_NATIVE_NETWORK_NETWORK_ADD_FRIEND( Any gamerHandle, const char* message )
	{
		std::tuple<bool, Any> return_values;
		std::get<0>(return_values) = (bool)NETWORK::NETWORK_ADD_FRIEND(&gamerHandle, message);
		std::get<1>(return_values) = gamerHandle;

		return return_values;
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_IS_FRIEND_INDEX_ONLINE( int friendIndex )
	{
		auto retval = (bool)NETWORK::NETWORK_IS_FRIEND_INDEX_ONLINE(friendIndex);
		return retval;
	}

	static void LUA_NATIVE_NETWORK_NETWORK_SET_PLAYER_IS_PASSIVE( bool toggle )
	{
		NETWORK::NETWORK_SET_PLAYER_IS_PASSIVE(toggle);
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_GET_PLAYER_OWNS_WAYPOINT( Player player )
	{
		auto retval = (bool)NETWORK::NETWORK_GET_PLAYER_OWNS_WAYPOINT(player);
		return retval;
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_CAN_SET_WAYPOINT(  )
	{
		auto retval = (bool)NETWORK::NETWORK_CAN_SET_WAYPOINT();
		return retval;
	}

	static void LUA_NATIVE_NETWORK_NETWORK_IGNORE_REMOTE_WAYPOINTS(  )
	{
		NETWORK::NETWORK_IGNORE_REMOTE_WAYPOINTS();
	}

	static std::tuple<bool, Any> LUA_NATIVE_NETWORK_NETWORK_IS_PLAYER_ON_BLOCKLIST( Any gamerHandle )
	{
		std::tuple<bool, Any> return_values;
		std::get<0>(return_values) = (bool)NETWORK::NETWORK_IS_PLAYER_ON_BLOCKLIST(&gamerHandle);
		std::get<1>(return_values) = gamerHandle;

		return return_values;
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_SET_SCRIPT_AUTOMUTED( Any p0 )
	{
		auto retval = (bool)NETWORK::NETWORK_SET_SCRIPT_AUTOMUTED(p0);
		return retval;
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_HAS_AUTOMUTE_OVERRIDE(  )
	{
		auto retval = (bool)NETWORK::NETWORK_HAS_AUTOMUTE_OVERRIDE();
		return retval;
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_HAS_HEADSET(  )
	{
		auto retval = (bool)NETWORK::NETWORK_HAS_HEADSET();
		return retval;
	}

	static void LUA_NATIVE_NETWORK_NETWORK_SET_LOOK_AT_TALKERS( bool p0 )
	{
		NETWORK::NETWORK_SET_LOOK_AT_TALKERS(p0);
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_IS_PUSH_TO_TALK_ACTIVE(  )
	{
		auto retval = (bool)NETWORK::NETWORK_IS_PUSH_TO_TALK_ACTIVE();
		return retval;
	}

	static std::tuple<bool, Any> LUA_NATIVE_NETWORK_NETWORK_GAMER_HAS_HEADSET( Any gamerHandle )
	{
		std::tuple<bool, Any> return_values;
		std::get<0>(return_values) = (bool)NETWORK::NETWORK_GAMER_HAS_HEADSET(&gamerHandle);
		std::get<1>(return_values) = gamerHandle;

		return return_values;
	}

	static std::tuple<bool, Any> LUA_NATIVE_NETWORK_NETWORK_IS_GAMER_TALKING( Any gamerHandle )
	{
		std::tuple<bool, Any> return_values;
		std::get<0>(return_values) = (bool)NETWORK::NETWORK_IS_GAMER_TALKING(&gamerHandle);
		std::get<1>(return_values) = gamerHandle;

		return return_values;
	}

	static std::tuple<bool, Any> LUA_NATIVE_NETWORK_NETWORK_PERMISSIONS_HAS_GAMER_RECORD( Any gamerHandle )
	{
		std::tuple<bool, Any> return_values;
		std::get<0>(return_values) = (bool)NETWORK::NETWORK_PERMISSIONS_HAS_GAMER_RECORD(&gamerHandle);
		std::get<1>(return_values) = gamerHandle;

		return return_values;
	}

	static std::tuple<bool, Any> LUA_NATIVE_NETWORK_NETWORK_CAN_COMMUNICATE_WITH_GAMER( Any gamerHandle )
	{
		std::tuple<bool, Any> return_values;
		std::get<0>(return_values) = (bool)NETWORK::NETWORK_CAN_COMMUNICATE_WITH_GAMER(&gamerHandle);
		std::get<1>(return_values) = gamerHandle;

		return return_values;
	}

	static std::tuple<bool, Any> LUA_NATIVE_NETWORK_NETWORK_CAN_TEXT_CHAT_WITH_GAMER( Any gamerHandle )
	{
		std::tuple<bool, Any> return_values;
		std::get<0>(return_values) = (bool)NETWORK::NETWORK_CAN_TEXT_CHAT_WITH_GAMER(&gamerHandle);
		std::get<1>(return_values) = gamerHandle;

		return return_values;
	}

	static std::tuple<bool, Any> LUA_NATIVE_NETWORK_NETWORK_IS_GAMER_MUTED_BY_ME( Any gamerHandle )
	{
		std::tuple<bool, Any> return_values;
		std::get<0>(return_values) = (bool)NETWORK::NETWORK_IS_GAMER_MUTED_BY_ME(&gamerHandle);
		std::get<1>(return_values) = gamerHandle;

		return return_values;
	}

	static std::tuple<bool, Any> LUA_NATIVE_NETWORK_NETWORK_AM_I_MUTED_BY_GAMER( Any gamerHandle )
	{
		std::tuple<bool, Any> return_values;
		std::get<0>(return_values) = (bool)NETWORK::NETWORK_AM_I_MUTED_BY_GAMER(&gamerHandle);
		std::get<1>(return_values) = gamerHandle;

		return return_values;
	}

	static std::tuple<bool, Any> LUA_NATIVE_NETWORK_NETWORK_IS_GAMER_BLOCKED_BY_ME( Any gamerHandle )
	{
		std::tuple<bool, Any> return_values;
		std::get<0>(return_values) = (bool)NETWORK::NETWORK_IS_GAMER_BLOCKED_BY_ME(&gamerHandle);
		std::get<1>(return_values) = gamerHandle;

		return return_values;
	}

	static std::tuple<bool, Any> LUA_NATIVE_NETWORK_NETWORK_AM_I_BLOCKED_BY_GAMER( Any gamerHandle )
	{
		std::tuple<bool, Any> return_values;
		std::get<0>(return_values) = (bool)NETWORK::NETWORK_AM_I_BLOCKED_BY_GAMER(&gamerHandle);
		std::get<1>(return_values) = gamerHandle;

		return return_values;
	}

	static std::tuple<bool, Any> LUA_NATIVE_NETWORK_NETWORK_CAN_VIEW_GAMER_USER_CONTENT( Any gamerHandle )
	{
		std::tuple<bool, Any> return_values;
		std::get<0>(return_values) = (bool)NETWORK::NETWORK_CAN_VIEW_GAMER_USER_CONTENT(&gamerHandle);
		std::get<1>(return_values) = gamerHandle;

		return return_values;
	}

	static std::tuple<bool, Any> LUA_NATIVE_NETWORK_NETWORK_HAS_VIEW_GAMER_USER_CONTENT_RESULT( Any gamerHandle )
	{
		std::tuple<bool, Any> return_values;
		std::get<0>(return_values) = (bool)NETWORK::NETWORK_HAS_VIEW_GAMER_USER_CONTENT_RESULT(&gamerHandle);
		std::get<1>(return_values) = gamerHandle;

		return return_values;
	}

	static std::tuple<bool, Any> LUA_NATIVE_NETWORK_NETWORK_CAN_PLAY_MULTIPLAYER_WITH_GAMER( Any gamerHandle )
	{
		std::tuple<bool, Any> return_values;
		std::get<0>(return_values) = (bool)NETWORK::NETWORK_CAN_PLAY_MULTIPLAYER_WITH_GAMER(&gamerHandle);
		std::get<1>(return_values) = gamerHandle;

		return return_values;
	}

	static std::tuple<bool, Any> LUA_NATIVE_NETWORK_NETWORK_CAN_GAMER_PLAY_MULTIPLAYER_WITH_ME( Any gamerHandle )
	{
		std::tuple<bool, Any> return_values;
		std::get<0>(return_values) = (bool)NETWORK::NETWORK_CAN_GAMER_PLAY_MULTIPLAYER_WITH_ME(&gamerHandle);
		std::get<1>(return_values) = gamerHandle;

		return return_values;
	}

	static std::tuple<bool, Any> LUA_NATIVE_NETWORK_NETWORK_CAN_SEND_LOCAL_INVITE( Any gamerHandle )
	{
		std::tuple<bool, Any> return_values;
		std::get<0>(return_values) = (bool)NETWORK::NETWORK_CAN_SEND_LOCAL_INVITE(&gamerHandle);
		std::get<1>(return_values) = gamerHandle;

		return return_values;
	}

	static std::tuple<bool, Any> LUA_NATIVE_NETWORK_NETWORK_CAN_RECEIVE_LOCAL_INVITE( Any gamerHandle )
	{
		std::tuple<bool, Any> return_values;
		std::get<0>(return_values) = (bool)NETWORK::NETWORK_CAN_RECEIVE_LOCAL_INVITE(&gamerHandle);
		std::get<1>(return_values) = gamerHandle;

		return return_values;
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_IS_PLAYER_TALKING( Player player )
	{
		auto retval = (bool)NETWORK::NETWORK_IS_PLAYER_TALKING(player);
		return retval;
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_PLAYER_HAS_HEADSET( Player player )
	{
		auto retval = (bool)NETWORK::NETWORK_PLAYER_HAS_HEADSET(player);
		return retval;
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_IS_PLAYER_MUTED_BY_ME( Player player )
	{
		auto retval = (bool)NETWORK::NETWORK_IS_PLAYER_MUTED_BY_ME(player);
		return retval;
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_AM_I_MUTED_BY_PLAYER( Player player )
	{
		auto retval = (bool)NETWORK::NETWORK_AM_I_MUTED_BY_PLAYER(player);
		return retval;
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_IS_PLAYER_BLOCKED_BY_ME( Player player )
	{
		auto retval = (bool)NETWORK::NETWORK_IS_PLAYER_BLOCKED_BY_ME(player);
		return retval;
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_AM_I_BLOCKED_BY_PLAYER( Player player )
	{
		auto retval = (bool)NETWORK::NETWORK_AM_I_BLOCKED_BY_PLAYER(player);
		return retval;
	}

	static float LUA_NATIVE_NETWORK_NETWORK_GET_PLAYER_LOUDNESS( Player player )
	{
		auto retval = NETWORK::NETWORK_GET_PLAYER_LOUDNESS(player);
		return retval;
	}

	static void LUA_NATIVE_NETWORK_NETWORK_SET_TALKER_PROXIMITY( float value )
	{
		NETWORK::NETWORK_SET_TALKER_PROXIMITY(value);
	}

	static float LUA_NATIVE_NETWORK_NETWORK_GET_TALKER_PROXIMITY(  )
	{
		auto retval = NETWORK::NETWORK_GET_TALKER_PROXIMITY();
		return retval;
	}

	static void LUA_NATIVE_NETWORK_NETWORK_SET_VOICE_ACTIVE( bool toggle )
	{
		NETWORK::NETWORK_SET_VOICE_ACTIVE(toggle);
	}

	static void LUA_NATIVE_NETWORK_NETWORK_REMAIN_IN_GAME_CHAT( bool p0 )
	{
		NETWORK::NETWORK_REMAIN_IN_GAME_CHAT(p0);
	}

	static void LUA_NATIVE_NETWORK_NETWORK_OVERRIDE_TRANSITION_CHAT( bool p0 )
	{
		NETWORK::NETWORK_OVERRIDE_TRANSITION_CHAT(p0);
	}

	static void LUA_NATIVE_NETWORK_NETWORK_SET_TEAM_ONLY_CHAT( bool toggle )
	{
		NETWORK::NETWORK_SET_TEAM_ONLY_CHAT(toggle);
	}

	static void LUA_NATIVE_NETWORK_NETWORK_SET_SCRIPT_CONTROLLING_TEAMS( Any p0 )
	{
		NETWORK::NETWORK_SET_SCRIPT_CONTROLLING_TEAMS(p0);
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_SET_SAME_TEAM_AS_LOCAL_PLAYER( Any p0, Any p1 )
	{
		auto retval = (bool)NETWORK::NETWORK_SET_SAME_TEAM_AS_LOCAL_PLAYER(p0, p1);
		return retval;
	}

	static void LUA_NATIVE_NETWORK_NETWORK_OVERRIDE_TEAM_RESTRICTIONS( int team, bool toggle )
	{
		NETWORK::NETWORK_OVERRIDE_TEAM_RESTRICTIONS(team, toggle);
	}

	static void LUA_NATIVE_NETWORK_NETWORK_SET_OVERRIDE_SPECTATOR_MODE( bool toggle )
	{
		NETWORK::NETWORK_SET_OVERRIDE_SPECTATOR_MODE(toggle);
	}

	static void LUA_NATIVE_NETWORK_NETWORK_SET_OVERRIDE_TUTORIAL_SESSION_CHAT( bool toggle )
	{
		NETWORK::NETWORK_SET_OVERRIDE_TUTORIAL_SESSION_CHAT(toggle);
	}

	static void LUA_NATIVE_NETWORK_NETWORK_SET_PROXIMITY_AFFECTS_TEAM( bool toggle )
	{
		NETWORK::NETWORK_SET_PROXIMITY_AFFECTS_TEAM(toggle);
	}

	static void LUA_NATIVE_NETWORK_NETWORK_SET_NO_SPECTATOR_CHAT( bool toggle )
	{
		NETWORK::NETWORK_SET_NO_SPECTATOR_CHAT(toggle);
	}

	static void LUA_NATIVE_NETWORK_NETWORK_SET_IGNORE_SPECTATOR_CHAT_LIMITS_SAME_TEAM( bool toggle )
	{
		NETWORK::NETWORK_SET_IGNORE_SPECTATOR_CHAT_LIMITS_SAME_TEAM(toggle);
	}

	static void LUA_NATIVE_NETWORK_NETWORK_OVERRIDE_CHAT_RESTRICTIONS( Player player, bool toggle )
	{
		NETWORK::NETWORK_OVERRIDE_CHAT_RESTRICTIONS(player, toggle);
	}

	static void LUA_NATIVE_NETWORK_NETWORK_OVERRIDE_SEND_RESTRICTIONS( Player player, bool toggle )
	{
		NETWORK::NETWORK_OVERRIDE_SEND_RESTRICTIONS(player, toggle);
	}

	static void LUA_NATIVE_NETWORK_NETWORK_OVERRIDE_SEND_RESTRICTIONS_ALL( bool toggle )
	{
		NETWORK::NETWORK_OVERRIDE_SEND_RESTRICTIONS_ALL(toggle);
	}

	static void LUA_NATIVE_NETWORK_NETWORK_OVERRIDE_RECEIVE_RESTRICTIONS( Player player, bool toggle )
	{
		NETWORK::NETWORK_OVERRIDE_RECEIVE_RESTRICTIONS(player, toggle);
	}

	static void LUA_NATIVE_NETWORK_NETWORK_OVERRIDE_RECEIVE_RESTRICTIONS_ALL( bool toggle )
	{
		NETWORK::NETWORK_OVERRIDE_RECEIVE_RESTRICTIONS_ALL(toggle);
	}

	static void LUA_NATIVE_NETWORK_NETWORK_SET_VOICE_CHANNEL( int channel )
	{
		NETWORK::NETWORK_SET_VOICE_CHANNEL(channel);
	}

	static void LUA_NATIVE_NETWORK_NETWORK_CLEAR_VOICE_CHANNEL(  )
	{
		NETWORK::NETWORK_CLEAR_VOICE_CHANNEL();
	}

	static void LUA_NATIVE_NETWORK_NETWORK_APPLY_VOICE_PROXIMITY_OVERRIDE( float x, float y, float z )
	{
		NETWORK::NETWORK_APPLY_VOICE_PROXIMITY_OVERRIDE(x, y, z);
	}

	static void LUA_NATIVE_NETWORK_NETWORK_CLEAR_VOICE_PROXIMITY_OVERRIDE(  )
	{
		NETWORK::NETWORK_CLEAR_VOICE_PROXIMITY_OVERRIDE();
	}

	static void LUA_NATIVE_NETWORK_NETWORK_ENABLE_VOICE_BANDWIDTH_RESTRICTION( Player player )
	{
		NETWORK::NETWORK_ENABLE_VOICE_BANDWIDTH_RESTRICTION(player);
	}

	static void LUA_NATIVE_NETWORK_NETWORK_DISABLE_VOICE_BANDWIDTH_RESTRICTION( Player player )
	{
		NETWORK::NETWORK_DISABLE_VOICE_BANDWIDTH_RESTRICTION(player);
	}

	static std::tuple<float, float> LUA_NATIVE_NETWORK_NETWORK_GET_MUTE_COUNT_FOR_PLAYER( Player p0, float p1, float p2 )
	{
		std::tuple<float, float> return_values;
		NETWORK::NETWORK_GET_MUTE_COUNT_FOR_PLAYER(p0, &p1, &p2);
		std::get<0>(return_values) = p1;
		std::get<1>(return_values) = p2;

		return return_values;
	}

	static void LUA_NATIVE_NETWORK_NETWORK_SET_SPECTATOR_TO_NON_SPECTATOR_TEXT_CHAT( bool toggle )
	{
		NETWORK::NETWORK_SET_SPECTATOR_TO_NON_SPECTATOR_TEXT_CHAT(toggle);
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_TEXT_CHAT_IS_TYPING(  )
	{
		auto retval = (bool)NETWORK::NETWORK_TEXT_CHAT_IS_TYPING();
		return retval;
	}

	static void LUA_NATIVE_NETWORK_SHUTDOWN_AND_LAUNCH_SINGLE_PLAYER_GAME(  )
	{
		NETWORK::SHUTDOWN_AND_LAUNCH_SINGLE_PLAYER_GAME();
	}

	static bool LUA_NATIVE_NETWORK_SHUTDOWN_AND_LOAD_MOST_RECENT_SAVE(  )
	{
		auto retval = (bool)NETWORK::SHUTDOWN_AND_LOAD_MOST_RECENT_SAVE();
		return retval;
	}

	static void LUA_NATIVE_NETWORK_NETWORK_SET_FRIENDLY_FIRE_OPTION( bool toggle )
	{
		NETWORK::NETWORK_SET_FRIENDLY_FIRE_OPTION(toggle);
	}

	static void LUA_NATIVE_NETWORK_NETWORK_SET_RICH_PRESENCE( int p0, int p1, Any p2, Any p3 )
	{
		NETWORK::NETWORK_SET_RICH_PRESENCE(p0, p1, p2, p3);
	}

	static void LUA_NATIVE_NETWORK_NETWORK_SET_RICH_PRESENCE_STRING( int p0, const char* textLabel )
	{
		NETWORK::NETWORK_SET_RICH_PRESENCE_STRING(p0, textLabel);
	}

	static int LUA_NATIVE_NETWORK_NETWORK_GET_TIMEOUT_TIME(  )
	{
		auto retval = NETWORK::NETWORK_GET_TIMEOUT_TIME();
		return retval;
	}

	static void LUA_NATIVE_NETWORK_NETWORK_LEAVE_PED_BEHIND_BEFORE_WARP( Player player, float x, float y, float z, bool p4, bool p5 )
	{
		NETWORK::NETWORK_LEAVE_PED_BEHIND_BEFORE_WARP(player, x, y, z, p4, p5);
	}

	static void LUA_NATIVE_NETWORK_NETWORK_LEAVE_PED_BEHIND_BEFORE_CUTSCENE( Player player, bool p1 )
	{
		NETWORK::NETWORK_LEAVE_PED_BEHIND_BEFORE_CUTSCENE(player, p1);
	}

	static void LUA_NATIVE_NETWORK_REMOVE_ALL_STICKY_BOMBS_FROM_ENTITY( Entity entity, Ped ped )
	{
		NETWORK::REMOVE_ALL_STICKY_BOMBS_FROM_ENTITY(entity, ped);
	}

	static void LUA_NATIVE_NETWORK_NETWORK_KEEP_ENTITY_COLLISION_DISABLED_AFTER_ANIM_SCENE( Any p0, Any p1 )
	{
		NETWORK::NETWORK_KEEP_ENTITY_COLLISION_DISABLED_AFTER_ANIM_SCENE(p0, p1);
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_IS_ANY_PLAYER_NEAR( Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6 )
	{
		auto retval = (bool)NETWORK::NETWORK_IS_ANY_PLAYER_NEAR(p0, p1, p2, p3, p4, p5, p6);
		return retval;
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_CLAN_SERVICE_IS_VALID(  )
	{
		auto retval = (bool)NETWORK::NETWORK_CLAN_SERVICE_IS_VALID();
		return retval;
	}

	static std::tuple<bool, Any> LUA_NATIVE_NETWORK_NETWORK_CLAN_PLAYER_IS_ACTIVE( Any gamerHandle )
	{
		std::tuple<bool, Any> return_values;
		std::get<0>(return_values) = (bool)NETWORK::NETWORK_CLAN_PLAYER_IS_ACTIVE(&gamerHandle);
		std::get<1>(return_values) = gamerHandle;

		return return_values;
	}

	static std::tuple<bool, Any, Any> LUA_NATIVE_NETWORK_NETWORK_CLAN_PLAYER_GET_DESC( Any clanDesc, int bufferSize, Any gamerHandle )
	{
		std::tuple<bool, Any, Any> return_values;
		std::get<0>(return_values) = (bool)NETWORK::NETWORK_CLAN_PLAYER_GET_DESC(&clanDesc, bufferSize, &gamerHandle);
		std::get<1>(return_values) = clanDesc;
		std::get<2>(return_values) = gamerHandle;

		return return_values;
	}

	static std::tuple<bool, Any> LUA_NATIVE_NETWORK_NETWORK_CLAN_IS_ROCKSTAR_CLAN( Any clanDesc, int bufferSize )
	{
		std::tuple<bool, Any> return_values;
		std::get<0>(return_values) = (bool)NETWORK::NETWORK_CLAN_IS_ROCKSTAR_CLAN(&clanDesc, bufferSize);
		std::get<1>(return_values) = clanDesc;

		return return_values;
	}

	static std::tuple<Any, char> LUA_NATIVE_NETWORK_NETWORK_CLAN_GET_UI_FORMATTED_TAG( Any clanDesc, int bufferSize, char formattedTag )
	{
		std::tuple<Any, char> return_values;
		NETWORK::NETWORK_CLAN_GET_UI_FORMATTED_TAG(&clanDesc, bufferSize, &formattedTag);
		std::get<0>(return_values) = clanDesc;
		std::get<1>(return_values) = formattedTag;

		return return_values;
	}

	static int LUA_NATIVE_NETWORK_NETWORK_CLAN_GET_LOCAL_MEMBERSHIPS_COUNT(  )
	{
		auto retval = NETWORK::NETWORK_CLAN_GET_LOCAL_MEMBERSHIPS_COUNT();
		return retval;
	}

	static std::tuple<bool, Any> LUA_NATIVE_NETWORK_NETWORK_CLAN_GET_MEMBERSHIP_DESC( Any memberDesc, int p1 )
	{
		std::tuple<bool, Any> return_values;
		std::get<0>(return_values) = (bool)NETWORK::NETWORK_CLAN_GET_MEMBERSHIP_DESC(&memberDesc, p1);
		std::get<1>(return_values) = memberDesc;

		return return_values;
	}

	static std::tuple<bool, Any> LUA_NATIVE_NETWORK_NETWORK_CLAN_DOWNLOAD_MEMBERSHIP( Any gamerHandle )
	{
		std::tuple<bool, Any> return_values;
		std::get<0>(return_values) = (bool)NETWORK::NETWORK_CLAN_DOWNLOAD_MEMBERSHIP(&gamerHandle);
		std::get<1>(return_values) = gamerHandle;

		return return_values;
	}

	static std::tuple<bool, Any> LUA_NATIVE_NETWORK_NETWORK_CLAN_DOWNLOAD_MEMBERSHIP_PENDING( Any p0 )
	{
		std::tuple<bool, Any> return_values;
		std::get<0>(return_values) = (bool)NETWORK::NETWORK_CLAN_DOWNLOAD_MEMBERSHIP_PENDING(&p0);
		std::get<1>(return_values) = p0;

		return return_values;
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_CLAN_ANY_DOWNLOAD_MEMBERSHIP_PENDING(  )
	{
		auto retval = (bool)NETWORK::NETWORK_CLAN_ANY_DOWNLOAD_MEMBERSHIP_PENDING();
		return retval;
	}

	static std::tuple<bool, int> LUA_NATIVE_NETWORK_NETWORK_CLAN_REMOTE_MEMBERSHIPS_ARE_IN_CACHE( int p0 )
	{
		std::tuple<bool, int> return_values;
		std::get<0>(return_values) = (bool)NETWORK::NETWORK_CLAN_REMOTE_MEMBERSHIPS_ARE_IN_CACHE(&p0);
		std::get<1>(return_values) = p0;

		return return_values;
	}

	static std::tuple<int, int> LUA_NATIVE_NETWORK_NETWORK_CLAN_GET_MEMBERSHIP_COUNT( int p0 )
	{
		std::tuple<int, int> return_values;
		std::get<0>(return_values) = NETWORK::NETWORK_CLAN_GET_MEMBERSHIP_COUNT(&p0);
		std::get<1>(return_values) = p0;

		return return_values;
	}

	static std::tuple<bool, int> LUA_NATIVE_NETWORK_NETWORK_CLAN_GET_MEMBERSHIP_VALID( int p0, Any p1 )
	{
		std::tuple<bool, int> return_values;
		std::get<0>(return_values) = (bool)NETWORK::NETWORK_CLAN_GET_MEMBERSHIP_VALID(&p0, p1);
		std::get<1>(return_values) = p0;

		return return_values;
	}

	static std::tuple<bool, int, Any> LUA_NATIVE_NETWORK_NETWORK_CLAN_GET_MEMBERSHIP( int p0, Any clanMembership, int p2 )
	{
		std::tuple<bool, int, Any> return_values;
		std::get<0>(return_values) = (bool)NETWORK::NETWORK_CLAN_GET_MEMBERSHIP(&p0, &clanMembership, p2);
		std::get<1>(return_values) = p0;
		std::get<2>(return_values) = clanMembership;

		return return_values;
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_CLAN_JOIN( int clanDesc )
	{
		auto retval = (bool)NETWORK::NETWORK_CLAN_JOIN(clanDesc);
		return retval;
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_CLAN_CREWINFO_GET_STRING_VALUE( const char* animDict, const char* animName )
	{
		auto retval = (bool)NETWORK::NETWORK_CLAN_CREWINFO_GET_STRING_VALUE(animDict, animName);
		return retval;
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_CLAN_CREWINFO_GET_CREWRANKTITLE( int p0, const char* p1 )
	{
		auto retval = (bool)NETWORK::NETWORK_CLAN_CREWINFO_GET_CREWRANKTITLE(p0, p1);
		return retval;
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_CLAN_HAS_CREWINFO_METADATA_BEEN_RECEIVED(  )
	{
		auto retval = (bool)NETWORK::NETWORK_CLAN_HAS_CREWINFO_METADATA_BEEN_RECEIVED();
		return retval;
	}

	static std::tuple<bool, Any, char> LUA_NATIVE_NETWORK_NETWORK_CLAN_GET_EMBLEM_TXD_NAME( Any netHandle, char txdName )
	{
		std::tuple<bool, Any, char> return_values;
		std::get<0>(return_values) = (bool)NETWORK::NETWORK_CLAN_GET_EMBLEM_TXD_NAME(&netHandle, &txdName);
		std::get<1>(return_values) = netHandle;
		std::get<2>(return_values) = txdName;

		return return_values;
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_CLAN_REQUEST_EMBLEM( Any p0 )
	{
		auto retval = (bool)NETWORK::NETWORK_CLAN_REQUEST_EMBLEM(p0);
		return retval;
	}

	static std::tuple<bool, Any> LUA_NATIVE_NETWORK_NETWORK_CLAN_IS_EMBLEM_READY( Any p0, Any p1 )
	{
		std::tuple<bool, Any> return_values;
		std::get<0>(return_values) = (bool)NETWORK::NETWORK_CLAN_IS_EMBLEM_READY(p0, &p1);
		std::get<1>(return_values) = p1;

		return return_values;
	}

	static void LUA_NATIVE_NETWORK_NETWORK_CLAN_RELEASE_EMBLEM( Any p0 )
	{
		NETWORK::NETWORK_CLAN_RELEASE_EMBLEM(p0);
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_GET_PRIMARY_CLAN_DATA_CLEAR(  )
	{
		auto retval = (bool)NETWORK::NETWORK_GET_PRIMARY_CLAN_DATA_CLEAR();
		return retval;
	}

	static void LUA_NATIVE_NETWORK_NETWORK_GET_PRIMARY_CLAN_DATA_CANCEL(  )
	{
		NETWORK::NETWORK_GET_PRIMARY_CLAN_DATA_CANCEL();
	}

	static std::tuple<bool, Any> LUA_NATIVE_NETWORK_NETWORK_GET_PRIMARY_CLAN_DATA_START( Any p0, Any p1 )
	{
		std::tuple<bool, Any> return_values;
		std::get<0>(return_values) = (bool)NETWORK::NETWORK_GET_PRIMARY_CLAN_DATA_START(&p0, p1);
		std::get<1>(return_values) = p0;

		return return_values;
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_GET_PRIMARY_CLAN_DATA_PENDING(  )
	{
		auto retval = (bool)NETWORK::NETWORK_GET_PRIMARY_CLAN_DATA_PENDING();
		return retval;
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_GET_PRIMARY_CLAN_DATA_SUCCESS(  )
	{
		auto retval = (bool)NETWORK::NETWORK_GET_PRIMARY_CLAN_DATA_SUCCESS();
		return retval;
	}

	static std::tuple<bool, Any, Any> LUA_NATIVE_NETWORK_NETWORK_GET_PRIMARY_CLAN_DATA_NEW( Any p0, Any p1 )
	{
		std::tuple<bool, Any, Any> return_values;
		std::get<0>(return_values) = (bool)NETWORK::NETWORK_GET_PRIMARY_CLAN_DATA_NEW(&p0, &p1);
		std::get<1>(return_values) = p0;
		std::get<2>(return_values) = p1;

		return return_values;
	}

	static void LUA_NATIVE_NETWORK_SET_NETWORK_ID_CAN_MIGRATE( int netId, bool toggle )
	{
		NETWORK::SET_NETWORK_ID_CAN_MIGRATE(netId, toggle);
	}

	static void LUA_NATIVE_NETWORK_SET_NETWORK_ID_EXISTS_ON_ALL_MACHINES( int netId, bool toggle )
	{
		NETWORK::SET_NETWORK_ID_EXISTS_ON_ALL_MACHINES(netId, toggle);
	}

	static void LUA_NATIVE_NETWORK_SET_NETWORK_ID_ALWAYS_EXISTS_FOR_PLAYER( int netId, Player player, bool toggle )
	{
		NETWORK::SET_NETWORK_ID_ALWAYS_EXISTS_FOR_PLAYER(netId, player, toggle);
	}

	static void LUA_NATIVE_NETWORK_SET_NETWORK_ID_CAN_BE_REASSIGNED( int netId, bool toggle )
	{
		NETWORK::SET_NETWORK_ID_CAN_BE_REASSIGNED(netId, toggle);
	}

	static void LUA_NATIVE_NETWORK_NETWORK_SET_ENTITY_CAN_BLEND( Entity entity, bool toggle )
	{
		NETWORK::NETWORK_SET_ENTITY_CAN_BLEND(entity, toggle);
	}

	static void LUA_NATIVE_NETWORK_NETWORK_SET_OBJECT_CAN_BLEND_WHEN_FIXED( Object object, bool toggle )
	{
		NETWORK::NETWORK_SET_OBJECT_CAN_BLEND_WHEN_FIXED(object, toggle);
	}

	static void LUA_NATIVE_NETWORK_NETWORK_SET_ENTITY_ONLY_EXISTS_FOR_PARTICIPANTS( Entity entity, bool toggle )
	{
		NETWORK::NETWORK_SET_ENTITY_ONLY_EXISTS_FOR_PARTICIPANTS(entity, toggle);
	}

	static void LUA_NATIVE_NETWORK_SET_NETWORK_ID_VISIBLE_IN_CUTSCENE( int netId, bool p1, bool p2 )
	{
		NETWORK::SET_NETWORK_ID_VISIBLE_IN_CUTSCENE(netId, p1, p2);
	}

	static void LUA_NATIVE_NETWORK_SET_NETWORK_ID_VISIBLE_IN_CUTSCENE_HACK( int netId, bool p1, bool p2 )
	{
		NETWORK::SET_NETWORK_ID_VISIBLE_IN_CUTSCENE_HACK(netId, p1, p2);
	}

	static void LUA_NATIVE_NETWORK_SET_NETWORK_ID_VISIBLE_IN_CUTSCENE_REMAIN_HACK( Any p0, Any p1 )
	{
		NETWORK::SET_NETWORK_ID_VISIBLE_IN_CUTSCENE_REMAIN_HACK(p0, p1);
	}

	static void LUA_NATIVE_NETWORK_SET_NETWORK_CUTSCENE_ENTITIES( bool toggle )
	{
		NETWORK::SET_NETWORK_CUTSCENE_ENTITIES(toggle);
	}

	static bool LUA_NATIVE_NETWORK_ARE_CUTSCENE_ENTITIES_NETWORKED(  )
	{
		auto retval = (bool)NETWORK::ARE_CUTSCENE_ENTITIES_NETWORKED();
		return retval;
	}

	static void LUA_NATIVE_NETWORK_SET_NETWORK_ID_PASS_CONTROL_IN_TUTORIAL( int netId, bool state )
	{
		NETWORK::SET_NETWORK_ID_PASS_CONTROL_IN_TUTORIAL(netId, state);
	}

	static bool LUA_NATIVE_NETWORK_IS_NETWORK_ID_OWNED_BY_PARTICIPANT( int netId )
	{
		auto retval = (bool)NETWORK::IS_NETWORK_ID_OWNED_BY_PARTICIPANT(netId);
		return retval;
	}

	static void LUA_NATIVE_NETWORK_SET_REMOTE_PLAYER_VISIBLE_IN_CUTSCENE( Player player, bool locallyVisible )
	{
		NETWORK::SET_REMOTE_PLAYER_VISIBLE_IN_CUTSCENE(player, locallyVisible);
	}

	static void LUA_NATIVE_NETWORK_SET_LOCAL_PLAYER_VISIBLE_IN_CUTSCENE( bool p0, bool p1 )
	{
		NETWORK::SET_LOCAL_PLAYER_VISIBLE_IN_CUTSCENE(p0, p1);
	}

	static void LUA_NATIVE_NETWORK_SET_LOCAL_PLAYER_INVISIBLE_LOCALLY( bool bIncludePlayersVehicle )
	{
		NETWORK::SET_LOCAL_PLAYER_INVISIBLE_LOCALLY(bIncludePlayersVehicle);
	}

	static void LUA_NATIVE_NETWORK_SET_LOCAL_PLAYER_VISIBLE_LOCALLY( bool bIncludePlayersVehicle )
	{
		NETWORK::SET_LOCAL_PLAYER_VISIBLE_LOCALLY(bIncludePlayersVehicle);
	}

	static void LUA_NATIVE_NETWORK_SET_PLAYER_INVISIBLE_LOCALLY( Player player, bool bIncludePlayersVehicle )
	{
		NETWORK::SET_PLAYER_INVISIBLE_LOCALLY(player, bIncludePlayersVehicle);
	}

	static void LUA_NATIVE_NETWORK_SET_PLAYER_VISIBLE_LOCALLY( Player player, bool bIncludePlayersVehicle )
	{
		NETWORK::SET_PLAYER_VISIBLE_LOCALLY(player, bIncludePlayersVehicle);
	}

	static void LUA_NATIVE_NETWORK_FADE_OUT_LOCAL_PLAYER( bool p0 )
	{
		NETWORK::FADE_OUT_LOCAL_PLAYER(p0);
	}

	static void LUA_NATIVE_NETWORK_NETWORK_FADE_OUT_ENTITY( Entity entity, bool normal, bool slow )
	{
		NETWORK::NETWORK_FADE_OUT_ENTITY(entity, normal, slow);
	}

	static void LUA_NATIVE_NETWORK_NETWORK_FADE_IN_ENTITY( Entity entity, bool state, Any p2 )
	{
		NETWORK::NETWORK_FADE_IN_ENTITY(entity, state, p2);
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_IS_PLAYER_FADING( Player player )
	{
		auto retval = (bool)NETWORK::NETWORK_IS_PLAYER_FADING(player);
		return retval;
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_IS_ENTITY_FADING( Entity entity )
	{
		auto retval = (bool)NETWORK::NETWORK_IS_ENTITY_FADING(entity);
		return retval;
	}

	static bool LUA_NATIVE_NETWORK_IS_PLAYER_IN_CUTSCENE( Player player )
	{
		auto retval = (bool)NETWORK::IS_PLAYER_IN_CUTSCENE(player);
		return retval;
	}

	static void LUA_NATIVE_NETWORK_SET_ENTITY_VISIBLE_IN_CUTSCENE( Any p0, bool p1, bool p2 )
	{
		NETWORK::SET_ENTITY_VISIBLE_IN_CUTSCENE(p0, p1, p2);
	}

	static void LUA_NATIVE_NETWORK_SET_ENTITY_LOCALLY_INVISIBLE( Entity entity )
	{
		NETWORK::SET_ENTITY_LOCALLY_INVISIBLE(entity);
	}

	static void LUA_NATIVE_NETWORK_SET_ENTITY_LOCALLY_VISIBLE( Entity entity )
	{
		NETWORK::SET_ENTITY_LOCALLY_VISIBLE(entity);
	}

	static bool LUA_NATIVE_NETWORK_IS_DAMAGE_TRACKER_ACTIVE_ON_NETWORK_ID( int netID )
	{
		auto retval = (bool)NETWORK::IS_DAMAGE_TRACKER_ACTIVE_ON_NETWORK_ID(netID);
		return retval;
	}

	static void LUA_NATIVE_NETWORK_ACTIVATE_DAMAGE_TRACKER_ON_NETWORK_ID( int netID, bool toggle )
	{
		NETWORK::ACTIVATE_DAMAGE_TRACKER_ON_NETWORK_ID(netID, toggle);
	}

	static bool LUA_NATIVE_NETWORK_IS_DAMAGE_TRACKER_ACTIVE_ON_PLAYER( Player player )
	{
		auto retval = (bool)NETWORK::IS_DAMAGE_TRACKER_ACTIVE_ON_PLAYER(player);
		return retval;
	}

	static void LUA_NATIVE_NETWORK_ACTIVATE_DAMAGE_TRACKER_ON_PLAYER( Player player, bool toggle )
	{
		NETWORK::ACTIVATE_DAMAGE_TRACKER_ON_PLAYER(player, toggle);
	}

	static bool LUA_NATIVE_NETWORK_IS_SPHERE_VISIBLE_TO_ANOTHER_MACHINE( float p0, float p1, float p2, float p3 )
	{
		auto retval = (bool)NETWORK::IS_SPHERE_VISIBLE_TO_ANOTHER_MACHINE(p0, p1, p2, p3);
		return retval;
	}

	static bool LUA_NATIVE_NETWORK_IS_SPHERE_VISIBLE_TO_PLAYER( Any p0, float p1, float p2, float p3, float p4 )
	{
		auto retval = (bool)NETWORK::IS_SPHERE_VISIBLE_TO_PLAYER(p0, p1, p2, p3, p4);
		return retval;
	}

	static void LUA_NATIVE_NETWORK_RESERVE_NETWORK_MISSION_OBJECTS( int amount )
	{
		NETWORK::RESERVE_NETWORK_MISSION_OBJECTS(amount);
	}

	static void LUA_NATIVE_NETWORK_RESERVE_NETWORK_MISSION_PEDS( int amount )
	{
		NETWORK::RESERVE_NETWORK_MISSION_PEDS(amount);
	}

	static void LUA_NATIVE_NETWORK_RESERVE_NETWORK_MISSION_VEHICLES( int amount )
	{
		NETWORK::RESERVE_NETWORK_MISSION_VEHICLES(amount);
	}

	static void LUA_NATIVE_NETWORK_RESERVE_LOCAL_NETWORK_MISSION_OBJECTS( int amount )
	{
		NETWORK::RESERVE_LOCAL_NETWORK_MISSION_OBJECTS(amount);
	}

	static void LUA_NATIVE_NETWORK_RESERVE_LOCAL_NETWORK_MISSION_PEDS( int amount )
	{
		NETWORK::RESERVE_LOCAL_NETWORK_MISSION_PEDS(amount);
	}

	static void LUA_NATIVE_NETWORK_RESERVE_LOCAL_NETWORK_MISSION_VEHICLES( int amount )
	{
		NETWORK::RESERVE_LOCAL_NETWORK_MISSION_VEHICLES(amount);
	}

	static bool LUA_NATIVE_NETWORK_CAN_REGISTER_MISSION_OBJECTS( int amount )
	{
		auto retval = (bool)NETWORK::CAN_REGISTER_MISSION_OBJECTS(amount);
		return retval;
	}

	static bool LUA_NATIVE_NETWORK_CAN_REGISTER_MISSION_PEDS( int amount )
	{
		auto retval = (bool)NETWORK::CAN_REGISTER_MISSION_PEDS(amount);
		return retval;
	}

	static bool LUA_NATIVE_NETWORK_CAN_REGISTER_MISSION_VEHICLES( int amount )
	{
		auto retval = (bool)NETWORK::CAN_REGISTER_MISSION_VEHICLES(amount);
		return retval;
	}

	static bool LUA_NATIVE_NETWORK_CAN_REGISTER_MISSION_PICKUPS( int amount )
	{
		auto retval = (bool)NETWORK::CAN_REGISTER_MISSION_PICKUPS(amount);
		return retval;
	}

	static bool LUA_NATIVE_NETWORK_CAN_REGISTER_MISSION_DOORS( Any p0 )
	{
		auto retval = (bool)NETWORK::CAN_REGISTER_MISSION_DOORS(p0);
		return retval;
	}

	static bool LUA_NATIVE_NETWORK_CAN_REGISTER_MISSION_ENTITIES( int ped_amt, int vehicle_amt, int object_amt, int pickup_amt )
	{
		auto retval = (bool)NETWORK::CAN_REGISTER_MISSION_ENTITIES(ped_amt, vehicle_amt, object_amt, pickup_amt);
		return retval;
	}

	static int LUA_NATIVE_NETWORK_GET_NUM_RESERVED_MISSION_OBJECTS( bool p0, Any p1 )
	{
		auto retval = NETWORK::GET_NUM_RESERVED_MISSION_OBJECTS(p0, p1);
		return retval;
	}

	static int LUA_NATIVE_NETWORK_GET_NUM_RESERVED_MISSION_PEDS( bool p0, Any p1 )
	{
		auto retval = NETWORK::GET_NUM_RESERVED_MISSION_PEDS(p0, p1);
		return retval;
	}

	static int LUA_NATIVE_NETWORK_GET_NUM_RESERVED_MISSION_VEHICLES( bool p0, Any p1 )
	{
		auto retval = NETWORK::GET_NUM_RESERVED_MISSION_VEHICLES(p0, p1);
		return retval;
	}

	static int LUA_NATIVE_NETWORK_GET_NUM_CREATED_MISSION_OBJECTS( bool p0 )
	{
		auto retval = NETWORK::GET_NUM_CREATED_MISSION_OBJECTS(p0);
		return retval;
	}

	static int LUA_NATIVE_NETWORK_GET_NUM_CREATED_MISSION_PEDS( bool p0 )
	{
		auto retval = NETWORK::GET_NUM_CREATED_MISSION_PEDS(p0);
		return retval;
	}

	static int LUA_NATIVE_NETWORK_GET_NUM_CREATED_MISSION_VEHICLES( bool p0 )
	{
		auto retval = NETWORK::GET_NUM_CREATED_MISSION_VEHICLES(p0);
		return retval;
	}

	static std::tuple<Any, Any, Any> LUA_NATIVE_NETWORK_GET_RESERVED_MISSION_ENTITIES_IN_AREA( float x, float y, float z, Any p3, Any out1, Any out2, Any out3 )
	{
		std::tuple<Any, Any, Any> return_values;
		NETWORK::GET_RESERVED_MISSION_ENTITIES_IN_AREA(x, y, z, p3, &out1, &out2, &out3);
		std::get<0>(return_values) = out1;
		std::get<1>(return_values) = out2;
		std::get<2>(return_values) = out3;

		return return_values;
	}

	static int LUA_NATIVE_NETWORK_GET_MAX_NUM_NETWORK_OBJECTS(  )
	{
		auto retval = NETWORK::GET_MAX_NUM_NETWORK_OBJECTS();
		return retval;
	}

	static int LUA_NATIVE_NETWORK_GET_MAX_NUM_NETWORK_PEDS(  )
	{
		auto retval = NETWORK::GET_MAX_NUM_NETWORK_PEDS();
		return retval;
	}

	static int LUA_NATIVE_NETWORK_GET_MAX_NUM_NETWORK_VEHICLES(  )
	{
		auto retval = NETWORK::GET_MAX_NUM_NETWORK_VEHICLES();
		return retval;
	}

	static int LUA_NATIVE_NETWORK_GET_MAX_NUM_NETWORK_PICKUPS(  )
	{
		auto retval = NETWORK::GET_MAX_NUM_NETWORK_PICKUPS();
		return retval;
	}

	static void LUA_NATIVE_NETWORK_NETWORK_SET_OBJECT_SCOPE_DISTANCE( Object object, float range )
	{
		NETWORK::NETWORK_SET_OBJECT_SCOPE_DISTANCE(object, range);
	}

	static void LUA_NATIVE_NETWORK_NETWORK_ALLOW_CLONING_WHILE_IN_TUTORIAL( Any p0, Any p1 )
	{
		NETWORK::NETWORK_ALLOW_CLONING_WHILE_IN_TUTORIAL(p0, p1);
	}

	static void LUA_NATIVE_NETWORK_NETWORK_SET_TASK_CUTSCENE_INSCOPE_MULTIPLER( Any p0 )
	{
		NETWORK::NETWORK_SET_TASK_CUTSCENE_INSCOPE_MULTIPLER(p0);
	}

	static int LUA_NATIVE_NETWORK_GET_NETWORK_TIME(  )
	{
		auto retval = NETWORK::GET_NETWORK_TIME();
		return retval;
	}

	static int LUA_NATIVE_NETWORK_GET_NETWORK_TIME_ACCURATE(  )
	{
		auto retval = NETWORK::GET_NETWORK_TIME_ACCURATE();
		return retval;
	}

	static bool LUA_NATIVE_NETWORK_HAS_NETWORK_TIME_STARTED(  )
	{
		auto retval = (bool)NETWORK::HAS_NETWORK_TIME_STARTED();
		return retval;
	}

	static int LUA_NATIVE_NETWORK_GET_TIME_OFFSET( int timeA, int timeB )
	{
		auto retval = NETWORK::GET_TIME_OFFSET(timeA, timeB);
		return retval;
	}

	static bool LUA_NATIVE_NETWORK_IS_TIME_LESS_THAN( int timeA, int timeB )
	{
		auto retval = (bool)NETWORK::IS_TIME_LESS_THAN(timeA, timeB);
		return retval;
	}

	static bool LUA_NATIVE_NETWORK_IS_TIME_MORE_THAN( int timeA, int timeB )
	{
		auto retval = (bool)NETWORK::IS_TIME_MORE_THAN(timeA, timeB);
		return retval;
	}

	static bool LUA_NATIVE_NETWORK_IS_TIME_EQUAL_TO( int timeA, int timeB )
	{
		auto retval = (bool)NETWORK::IS_TIME_EQUAL_TO(timeA, timeB);
		return retval;
	}

	static int LUA_NATIVE_NETWORK_GET_TIME_DIFFERENCE( int timeA, int timeB )
	{
		auto retval = NETWORK::GET_TIME_DIFFERENCE(timeA, timeB);
		return retval;
	}

	static const char* LUA_NATIVE_NETWORK_GET_TIME_AS_STRING( int time )
	{
		auto retval = NETWORK::GET_TIME_AS_STRING(time);
		return retval;
	}

	static const char* LUA_NATIVE_NETWORK_GET_CLOUD_TIME_AS_STRING(  )
	{
		auto retval = NETWORK::GET_CLOUD_TIME_AS_STRING();
		return retval;
	}

	static int LUA_NATIVE_NETWORK_GET_CLOUD_TIME_AS_INT(  )
	{
		auto retval = NETWORK::GET_CLOUD_TIME_AS_INT();
		return retval;
	}

	static Any LUA_NATIVE_NETWORK_CONVERT_POSIX_TIME( int posixTime, Any timeStructure )
	{
		NETWORK::CONVERT_POSIX_TIME(posixTime, &timeStructure);
		return timeStructure;
	}

	static void LUA_NATIVE_NETWORK_NETWORK_SET_IN_SPECTATOR_MODE( bool toggle, Ped playerPed )
	{
		NETWORK::NETWORK_SET_IN_SPECTATOR_MODE(toggle, playerPed);
	}

	static void LUA_NATIVE_NETWORK_NETWORK_SET_IN_SPECTATOR_MODE_EXTENDED( bool toggle, Ped playerPed, bool p2 )
	{
		NETWORK::NETWORK_SET_IN_SPECTATOR_MODE_EXTENDED(toggle, playerPed, p2);
	}

	static void LUA_NATIVE_NETWORK_NETWORK_SET_IN_FREE_CAM_MODE( bool toggle )
	{
		NETWORK::NETWORK_SET_IN_FREE_CAM_MODE(toggle);
	}

	static void LUA_NATIVE_NETWORK_NETWORK_SET_ANTAGONISTIC_TO_PLAYER( bool toggle, Player player )
	{
		NETWORK::NETWORK_SET_ANTAGONISTIC_TO_PLAYER(toggle, player);
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_IS_IN_SPECTATOR_MODE(  )
	{
		auto retval = (bool)NETWORK::NETWORK_IS_IN_SPECTATOR_MODE();
		return retval;
	}

	static void LUA_NATIVE_NETWORK_NETWORK_SET_IN_MP_CUTSCENE( bool p0, bool p1 )
	{
		NETWORK::NETWORK_SET_IN_MP_CUTSCENE(p0, p1);
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_IS_IN_MP_CUTSCENE(  )
	{
		auto retval = (bool)NETWORK::NETWORK_IS_IN_MP_CUTSCENE();
		return retval;
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_IS_PLAYER_IN_MP_CUTSCENE( Player player )
	{
		auto retval = (bool)NETWORK::NETWORK_IS_PLAYER_IN_MP_CUTSCENE(player);
		return retval;
	}

	static void LUA_NATIVE_NETWORK_NETWORK_HIDE_PROJECTILE_IN_CUTSCENE(  )
	{
		NETWORK::NETWORK_HIDE_PROJECTILE_IN_CUTSCENE();
	}

	static void LUA_NATIVE_NETWORK_SET_NETWORK_VEHICLE_RESPOT_TIMER( int netId, int time, Any p2, Any p3 )
	{
		NETWORK::SET_NETWORK_VEHICLE_RESPOT_TIMER(netId, time, p2, p3);
	}

	static bool LUA_NATIVE_NETWORK_IS_NETWORK_VEHICLE_RUNNING_RESPOT_TIMER( int networkID )
	{
		auto retval = (bool)NETWORK::IS_NETWORK_VEHICLE_RUNNING_RESPOT_TIMER(networkID);
		return retval;
	}

	static void LUA_NATIVE_NETWORK_SET_NETWORK_VEHICLE_AS_GHOST( Vehicle vehicle, bool toggle )
	{
		NETWORK::SET_NETWORK_VEHICLE_AS_GHOST(vehicle, toggle);
	}

	static void LUA_NATIVE_NETWORK_SET_NETWORK_VEHICLE_MAX_POSITION_DELTA_MULTIPLIER( Vehicle vehicle, float multiplier )
	{
		NETWORK::SET_NETWORK_VEHICLE_MAX_POSITION_DELTA_MULTIPLIER(vehicle, multiplier);
	}

	static void LUA_NATIVE_NETWORK_SET_NETWORK_ENABLE_HIGH_SPEED_EDGE_FALL_DETECTION( Vehicle vehicle, bool toggle )
	{
		NETWORK::SET_NETWORK_ENABLE_HIGH_SPEED_EDGE_FALL_DETECTION(vehicle, toggle);
	}

	static void LUA_NATIVE_NETWORK_SET_LOCAL_PLAYER_AS_GHOST( bool toggle, bool p1 )
	{
		NETWORK::SET_LOCAL_PLAYER_AS_GHOST(toggle, p1);
	}

	static bool LUA_NATIVE_NETWORK_IS_ENTITY_A_GHOST( Entity entity )
	{
		auto retval = (bool)NETWORK::IS_ENTITY_A_GHOST(entity);
		return retval;
	}

	static void LUA_NATIVE_NETWORK_SET_NON_PARTICIPANTS_OF_THIS_SCRIPT_AS_GHOSTS( bool p0 )
	{
		NETWORK::SET_NON_PARTICIPANTS_OF_THIS_SCRIPT_AS_GHOSTS(p0);
	}

	static void LUA_NATIVE_NETWORK_SET_REMOTE_PLAYER_AS_GHOST( Player player, bool p1 )
	{
		NETWORK::SET_REMOTE_PLAYER_AS_GHOST(player, p1);
	}

	static void LUA_NATIVE_NETWORK_SET_GHOST_ALPHA( int alpha )
	{
		NETWORK::SET_GHOST_ALPHA(alpha);
	}

	static void LUA_NATIVE_NETWORK_RESET_GHOST_ALPHA(  )
	{
		NETWORK::RESET_GHOST_ALPHA();
	}

	static void LUA_NATIVE_NETWORK_SET_ENTITY_GHOSTED_FOR_GHOST_PLAYERS( Entity entity, bool toggle )
	{
		NETWORK::SET_ENTITY_GHOSTED_FOR_GHOST_PLAYERS(entity, toggle);
	}

	static void LUA_NATIVE_NETWORK_SET_INVERT_GHOSTING( bool p0 )
	{
		NETWORK::SET_INVERT_GHOSTING(p0);
	}

	static bool LUA_NATIVE_NETWORK_IS_ENTITY_IN_GHOST_COLLISION( Entity entity )
	{
		auto retval = (bool)NETWORK::IS_ENTITY_IN_GHOST_COLLISION(entity);
		return retval;
	}

	static void LUA_NATIVE_NETWORK_USE_PLAYER_COLOUR_INSTEAD_OF_TEAM_COLOUR( bool toggle )
	{
		NETWORK::USE_PLAYER_COLOUR_INSTEAD_OF_TEAM_COLOUR(toggle);
	}

	static int LUA_NATIVE_NETWORK_NETWORK_CREATE_SYNCHRONISED_SCENE( float x, float y, float z, float xRot, float yRot, float zRot, int rotationOrder, bool useOcclusionPortal, bool looped, float p9, float animTime, float p11 )
	{
		auto retval = NETWORK::NETWORK_CREATE_SYNCHRONISED_SCENE(x, y, z, xRot, yRot, zRot, rotationOrder, useOcclusionPortal, looped, p9, animTime, p11);
		return retval;
	}

	static void LUA_NATIVE_NETWORK_NETWORK_ADD_PED_TO_SYNCHRONISED_SCENE( Ped ped, int netScene, const char* animDict, const char* animnName, float speed, float speedMultiplier, int duration, int flag, float playbackRate, Any p9 )
	{
		NETWORK::NETWORK_ADD_PED_TO_SYNCHRONISED_SCENE(ped, netScene, animDict, animnName, speed, speedMultiplier, duration, flag, playbackRate, p9);
	}

	static void LUA_NATIVE_NETWORK_NETWORK_ADD_PED_TO_SYNCHRONISED_SCENE_WITH_IK( Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9 )
	{
		NETWORK::NETWORK_ADD_PED_TO_SYNCHRONISED_SCENE_WITH_IK(p0, p1, p2, p3, p4, p5, p6, p7, p8, p9);
	}

	static void LUA_NATIVE_NETWORK_NETWORK_ADD_ENTITY_TO_SYNCHRONISED_SCENE( Entity entity, int netScene, const char* animDict, const char* animName, float speed, float speedMulitiplier, int flag )
	{
		NETWORK::NETWORK_ADD_ENTITY_TO_SYNCHRONISED_SCENE(entity, netScene, animDict, animName, speed, speedMulitiplier, flag);
	}

	static void LUA_NATIVE_NETWORK_NETWORK_ADD_MAP_ENTITY_TO_SYNCHRONISED_SCENE( int netScene, Hash modelHash, float x, float y, float z, float p5, const char* p6, float p7, float p8, int flags )
	{
		NETWORK::NETWORK_ADD_MAP_ENTITY_TO_SYNCHRONISED_SCENE(netScene, modelHash, x, y, z, p5, p6, p7, p8, flags);
	}

	static void LUA_NATIVE_NETWORK_NETWORK_ADD_SYNCHRONISED_SCENE_CAMERA( int netScene, const char* animDict, const char* animName )
	{
		NETWORK::NETWORK_ADD_SYNCHRONISED_SCENE_CAMERA(netScene, animDict, animName);
	}

	static void LUA_NATIVE_NETWORK_NETWORK_ATTACH_SYNCHRONISED_SCENE_TO_ENTITY( int netScene, Entity entity, int bone )
	{
		NETWORK::NETWORK_ATTACH_SYNCHRONISED_SCENE_TO_ENTITY(netScene, entity, bone);
	}

	static void LUA_NATIVE_NETWORK_NETWORK_START_SYNCHRONISED_SCENE( int netScene )
	{
		NETWORK::NETWORK_START_SYNCHRONISED_SCENE(netScene);
	}

	static void LUA_NATIVE_NETWORK_NETWORK_STOP_SYNCHRONISED_SCENE( int netScene )
	{
		NETWORK::NETWORK_STOP_SYNCHRONISED_SCENE(netScene);
	}

	static int LUA_NATIVE_NETWORK_NETWORK_GET_LOCAL_SCENE_FROM_NETWORK_ID( int netId )
	{
		auto retval = NETWORK::NETWORK_GET_LOCAL_SCENE_FROM_NETWORK_ID(netId);
		return retval;
	}

	static void LUA_NATIVE_NETWORK_NETWORK_FORCE_LOCAL_USE_OF_SYNCED_SCENE_CAMERA( int netScene )
	{
		NETWORK::NETWORK_FORCE_LOCAL_USE_OF_SYNCED_SCENE_CAMERA(netScene);
	}

	static void LUA_NATIVE_NETWORK_NETWORK_ALLOW_REMOTE_SYNCED_SCENE_LOCAL_PLAYER_REQUESTS( Any p0 )
	{
		NETWORK::NETWORK_ALLOW_REMOTE_SYNCED_SCENE_LOCAL_PLAYER_REQUESTS(p0);
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_FIND_LARGEST_BUNCH_OF_PLAYERS( int p0, Any p1 )
	{
		auto retval = (bool)NETWORK::NETWORK_FIND_LARGEST_BUNCH_OF_PLAYERS(p0, p1);
		return retval;
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_START_RESPAWN_SEARCH_FOR_PLAYER( Player player, float x, float y, float z, float radius, float p5, float p6, float p7, int flags )
	{
		auto retval = (bool)NETWORK::NETWORK_START_RESPAWN_SEARCH_FOR_PLAYER(player, x, y, z, radius, p5, p6, p7, flags);
		return retval;
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_START_RESPAWN_SEARCH_IN_ANGLED_AREA_FOR_PLAYER( Player player, float x1, float y1, float z1, float x2, float y2, float z2, float width, float p8, float p9, float p10, int flags )
	{
		auto retval = (bool)NETWORK::NETWORK_START_RESPAWN_SEARCH_IN_ANGLED_AREA_FOR_PLAYER(player, x1, y1, z1, x2, y2, z2, width, p8, p9, p10, flags);
		return retval;
	}

	static std::tuple<int, Any> LUA_NATIVE_NETWORK_NETWORK_QUERY_RESPAWN_RESULTS( Any p0 )
	{
		std::tuple<int, Any> return_values;
		std::get<0>(return_values) = NETWORK::NETWORK_QUERY_RESPAWN_RESULTS(&p0);
		std::get<1>(return_values) = p0;

		return return_values;
	}

	static void LUA_NATIVE_NETWORK_NETWORK_CANCEL_RESPAWN_SEARCH(  )
	{
		NETWORK::NETWORK_CANCEL_RESPAWN_SEARCH();
	}

	static std::tuple<Vector3, float> LUA_NATIVE_NETWORK_NETWORK_GET_RESPAWN_RESULT( int randomInt, Vector3 coordinates, float heading )
	{
		std::tuple<Vector3, float> return_values;
		NETWORK::NETWORK_GET_RESPAWN_RESULT(randomInt, &coordinates, &heading);
		std::get<0>(return_values) = coordinates;
		std::get<1>(return_values) = heading;

		return return_values;
	}

	static int LUA_NATIVE_NETWORK_NETWORK_GET_RESPAWN_RESULT_FLAGS( int p0 )
	{
		auto retval = NETWORK::NETWORK_GET_RESPAWN_RESULT_FLAGS(p0);
		return retval;
	}

	static void LUA_NATIVE_NETWORK_NETWORK_START_SOLO_TUTORIAL_SESSION(  )
	{
		NETWORK::NETWORK_START_SOLO_TUTORIAL_SESSION();
	}

	static void LUA_NATIVE_NETWORK_NETWORK_ALLOW_GANG_TO_JOIN_TUTORIAL_SESSION( int teamId, int instanceId )
	{
		NETWORK::NETWORK_ALLOW_GANG_TO_JOIN_TUTORIAL_SESSION(teamId, instanceId);
	}

	static void LUA_NATIVE_NETWORK_NETWORK_END_TUTORIAL_SESSION(  )
	{
		NETWORK::NETWORK_END_TUTORIAL_SESSION();
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_IS_IN_TUTORIAL_SESSION(  )
	{
		auto retval = (bool)NETWORK::NETWORK_IS_IN_TUTORIAL_SESSION();
		return retval;
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_WAITING_POP_CLEAR_TUTORIAL_SESSION(  )
	{
		auto retval = (bool)NETWORK::NETWORK_WAITING_POP_CLEAR_TUTORIAL_SESSION();
		return retval;
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_IS_TUTORIAL_SESSION_CHANGE_PENDING(  )
	{
		auto retval = (bool)NETWORK::NETWORK_IS_TUTORIAL_SESSION_CHANGE_PENDING();
		return retval;
	}

	static int LUA_NATIVE_NETWORK_NETWORK_GET_PLAYER_TUTORIAL_SESSION_INSTANCE( Player player )
	{
		auto retval = NETWORK::NETWORK_GET_PLAYER_TUTORIAL_SESSION_INSTANCE(player);
		return retval;
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_ARE_PLAYERS_IN_SAME_TUTORIAL_SESSION( Player player, int index )
	{
		auto retval = (bool)NETWORK::NETWORK_ARE_PLAYERS_IN_SAME_TUTORIAL_SESSION(player, index);
		return retval;
	}

	static void LUA_NATIVE_NETWORK_NETWORK_BLOCK_PROXY_MIGRATION_BETWEEN_TUTORIAL_SESSIONS( Any p0 )
	{
		NETWORK::NETWORK_BLOCK_PROXY_MIGRATION_BETWEEN_TUTORIAL_SESSIONS(p0);
	}

	static void LUA_NATIVE_NETWORK_NETWORK_CONCEAL_PLAYER( Player player, bool toggle, bool p2 )
	{
		NETWORK::NETWORK_CONCEAL_PLAYER(player, toggle, p2);
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_IS_PLAYER_CONCEALED( Player player )
	{
		auto retval = (bool)NETWORK::NETWORK_IS_PLAYER_CONCEALED(player);
		return retval;
	}

	static void LUA_NATIVE_NETWORK_NETWORK_CONCEAL_ENTITY( Entity entity, bool toggle )
	{
		NETWORK::NETWORK_CONCEAL_ENTITY(entity, toggle);
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_IS_ENTITY_CONCEALED( Entity entity )
	{
		auto retval = (bool)NETWORK::NETWORK_IS_ENTITY_CONCEALED(entity);
		return retval;
	}

	static void LUA_NATIVE_NETWORK_NETWORK_OVERRIDE_CLOCK_TIME( int hours, int minutes, int seconds )
	{
		NETWORK::NETWORK_OVERRIDE_CLOCK_TIME(hours, minutes, seconds);
	}

	static void LUA_NATIVE_NETWORK_NETWORK_OVERRIDE_CLOCK_RATE( int ms )
	{
		NETWORK::NETWORK_OVERRIDE_CLOCK_RATE(ms);
	}

	static void LUA_NATIVE_NETWORK_NETWORK_CLEAR_CLOCK_TIME_OVERRIDE(  )
	{
		NETWORK::NETWORK_CLEAR_CLOCK_TIME_OVERRIDE();
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_IS_CLOCK_TIME_OVERRIDDEN(  )
	{
		auto retval = (bool)NETWORK::NETWORK_IS_CLOCK_TIME_OVERRIDDEN();
		return retval;
	}

	static int LUA_NATIVE_NETWORK_NETWORK_ADD_ENTITY_AREA( float x1, float y1, float z1, float x2, float y2, float z2 )
	{
		auto retval = NETWORK::NETWORK_ADD_ENTITY_AREA(x1, y1, z1, x2, y2, z2);
		return retval;
	}

	static int LUA_NATIVE_NETWORK_NETWORK_ADD_ENTITY_ANGLED_AREA( float x1, float y1, float z1, float x2, float y2, float z2, float width )
	{
		auto retval = NETWORK::NETWORK_ADD_ENTITY_ANGLED_AREA(x1, y1, z1, x2, y2, z2, width);
		return retval;
	}

	static int LUA_NATIVE_NETWORK_NETWORK_ADD_CLIENT_ENTITY_AREA( float x1, float y1, float z1, float x2, float y2, float z2 )
	{
		auto retval = NETWORK::NETWORK_ADD_CLIENT_ENTITY_AREA(x1, y1, z1, x2, y2, z2);
		return retval;
	}

	static int LUA_NATIVE_NETWORK_NETWORK_ADD_CLIENT_ENTITY_ANGLED_AREA( float x1, float y1, float z1, float x2, float y2, float z2, float radius )
	{
		auto retval = NETWORK::NETWORK_ADD_CLIENT_ENTITY_ANGLED_AREA(x1, y1, z1, x2, y2, z2, radius);
		return retval;
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_REMOVE_ENTITY_AREA( int areaHandle )
	{
		auto retval = (bool)NETWORK::NETWORK_REMOVE_ENTITY_AREA(areaHandle);
		return retval;
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_ENTITY_AREA_DOES_EXIST( int areaHandle )
	{
		auto retval = (bool)NETWORK::NETWORK_ENTITY_AREA_DOES_EXIST(areaHandle);
		return retval;
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_ENTITY_AREA_HAVE_ALL_REPLIED( int areaHandle )
	{
		auto retval = (bool)NETWORK::NETWORK_ENTITY_AREA_HAVE_ALL_REPLIED(areaHandle);
		return retval;
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_ENTITY_AREA_IS_OCCUPIED( int areaHandle )
	{
		auto retval = (bool)NETWORK::NETWORK_ENTITY_AREA_IS_OCCUPIED(areaHandle);
		return retval;
	}

	static void LUA_NATIVE_NETWORK_NETWORK_USE_HIGH_PRECISION_BLENDING( int netID, bool toggle )
	{
		NETWORK::NETWORK_USE_HIGH_PRECISION_BLENDING(netID, toggle);
	}

	static void LUA_NATIVE_NETWORK_NETWORK_SET_CUSTOM_ARENA_BALL_PARAMS( int netId )
	{
		NETWORK::NETWORK_SET_CUSTOM_ARENA_BALL_PARAMS(netId);
	}

	static void LUA_NATIVE_NETWORK_NETWORK_ENTITY_USE_HIGH_PRECISION_ROTATION( int netId, bool toggle )
	{
		NETWORK::NETWORK_ENTITY_USE_HIGH_PRECISION_ROTATION(netId, toggle);
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_REQUEST_CLOUD_BACKGROUND_SCRIPTS(  )
	{
		auto retval = (bool)NETWORK::NETWORK_REQUEST_CLOUD_BACKGROUND_SCRIPTS();
		return retval;
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_IS_CLOUD_BACKGROUND_SCRIPT_REQUEST_PENDING(  )
	{
		auto retval = (bool)NETWORK::NETWORK_IS_CLOUD_BACKGROUND_SCRIPT_REQUEST_PENDING();
		return retval;
	}

	static void LUA_NATIVE_NETWORK_NETWORK_REQUEST_CLOUD_TUNABLES(  )
	{
		NETWORK::NETWORK_REQUEST_CLOUD_TUNABLES();
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_IS_TUNABLE_CLOUD_REQUEST_PENDING(  )
	{
		auto retval = (bool)NETWORK::NETWORK_IS_TUNABLE_CLOUD_REQUEST_PENDING();
		return retval;
	}

	static int LUA_NATIVE_NETWORK_NETWORK_GET_TUNABLE_CLOUD_CRC(  )
	{
		auto retval = NETWORK::NETWORK_GET_TUNABLE_CLOUD_CRC();
		return retval;
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_DOES_TUNABLE_EXIST( const char* tunableContext, const char* tunableName )
	{
		auto retval = (bool)NETWORK::NETWORK_DOES_TUNABLE_EXIST(tunableContext, tunableName);
		return retval;
	}

	static std::tuple<bool, int> LUA_NATIVE_NETWORK_NETWORK_ACCESS_TUNABLE_INT( const char* tunableContext, const char* tunableName, int value )
	{
		std::tuple<bool, int> return_values;
		std::get<0>(return_values) = (bool)NETWORK::NETWORK_ACCESS_TUNABLE_INT(tunableContext, tunableName, &value);
		std::get<1>(return_values) = value;

		return return_values;
	}

	static std::tuple<bool, float> LUA_NATIVE_NETWORK_NETWORK_ACCESS_TUNABLE_FLOAT( const char* tunableContext, const char* tunableName, float value )
	{
		std::tuple<bool, float> return_values;
		std::get<0>(return_values) = (bool)NETWORK::NETWORK_ACCESS_TUNABLE_FLOAT(tunableContext, tunableName, &value);
		std::get<1>(return_values) = value;

		return return_values;
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_ACCESS_TUNABLE_BOOL( const char* tunableContext, const char* tunableName )
	{
		auto retval = (bool)NETWORK::NETWORK_ACCESS_TUNABLE_BOOL(tunableContext, tunableName);
		return retval;
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_DOES_TUNABLE_EXIST_HASH( Hash tunableContext, Hash tunableName )
	{
		auto retval = (bool)NETWORK::NETWORK_DOES_TUNABLE_EXIST_HASH(tunableContext, tunableName);
		return retval;
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_ACCESS_TUNABLE_MODIFICATION_DETECTION_CLEAR(  )
	{
		auto retval = (bool)NETWORK::NETWORK_ACCESS_TUNABLE_MODIFICATION_DETECTION_CLEAR();
		return retval;
	}

	static std::tuple<bool, int> LUA_NATIVE_NETWORK_NETWORK_ACCESS_TUNABLE_INT_HASH( Hash tunableContext, Hash tunableName, int value )
	{
		std::tuple<bool, int> return_values;
		std::get<0>(return_values) = (bool)NETWORK::NETWORK_ACCESS_TUNABLE_INT_HASH(tunableContext, tunableName, &value);
		std::get<1>(return_values) = value;

		return return_values;
	}

	static std::tuple<bool, int> LUA_NATIVE_NETWORK_NETWORK_ACCESS_TUNABLE_INT_MODIFICATION_DETECTION_REGISTRATION_HASH( Hash contextHash, Hash nameHash, int value )
	{
		std::tuple<bool, int> return_values;
		std::get<0>(return_values) = (bool)NETWORK::NETWORK_ACCESS_TUNABLE_INT_MODIFICATION_DETECTION_REGISTRATION_HASH(contextHash, nameHash, &value);
		std::get<1>(return_values) = value;

		return return_values;
	}

	static std::tuple<bool, float> LUA_NATIVE_NETWORK_NETWORK_ACCESS_TUNABLE_FLOAT_HASH( Hash tunableContext, Hash tunableName, float value )
	{
		std::tuple<bool, float> return_values;
		std::get<0>(return_values) = (bool)NETWORK::NETWORK_ACCESS_TUNABLE_FLOAT_HASH(tunableContext, tunableName, &value);
		std::get<1>(return_values) = value;

		return return_values;
	}

	static std::tuple<bool, float> LUA_NATIVE_NETWORK_NETWORK_ACCESS_TUNABLE_FLOAT_MODIFICATION_DETECTION_REGISTRATION_HASH( Hash contextHash, Hash nameHash, float value )
	{
		std::tuple<bool, float> return_values;
		std::get<0>(return_values) = (bool)NETWORK::NETWORK_ACCESS_TUNABLE_FLOAT_MODIFICATION_DETECTION_REGISTRATION_HASH(contextHash, nameHash, &value);
		std::get<1>(return_values) = value;

		return return_values;
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_ACCESS_TUNABLE_BOOL_HASH( Hash tunableContext, Hash tunableName )
	{
		auto retval = (bool)NETWORK::NETWORK_ACCESS_TUNABLE_BOOL_HASH(tunableContext, tunableName);
		return retval;
	}

	static std::tuple<bool, bool> LUA_NATIVE_NETWORK_NETWORK_ACCESS_TUNABLE_BOOL_MODIFICATION_DETECTION_REGISTRATION_HASH( Hash contextHash, Hash nameHash, bool value )
	{
		std::tuple<bool, bool> return_values;
		std::get<0>(return_values) = (bool)NETWORK::NETWORK_ACCESS_TUNABLE_BOOL_MODIFICATION_DETECTION_REGISTRATION_HASH(contextHash, nameHash, (BOOL*)&value);
		std::get<1>(return_values) = value;

		return return_values;
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_TRY_ACCESS_TUNABLE_BOOL_HASH( Hash tunableContext, Hash tunableName, bool defaultValue )
	{
		auto retval = (bool)NETWORK::NETWORK_TRY_ACCESS_TUNABLE_BOOL_HASH(tunableContext, tunableName, defaultValue);
		return retval;
	}

	static int LUA_NATIVE_NETWORK_NETWORK_GET_CONTENT_MODIFIER_LIST_ID( Hash contentHash )
	{
		auto retval = NETWORK::NETWORK_GET_CONTENT_MODIFIER_LIST_ID(contentHash);
		return retval;
	}

	static int LUA_NATIVE_NETWORK_NETWORK_GET_BONE_ID_OF_FATAL_HIT(  )
	{
		auto retval = NETWORK::NETWORK_GET_BONE_ID_OF_FATAL_HIT();
		return retval;
	}

	static void LUA_NATIVE_NETWORK_NETWORK_RESET_BODY_TRACKER(  )
	{
		NETWORK::NETWORK_RESET_BODY_TRACKER();
	}

	static int LUA_NATIVE_NETWORK_NETWORK_GET_NUMBER_BODY_TRACKER_HITS(  )
	{
		auto retval = NETWORK::NETWORK_GET_NUMBER_BODY_TRACKER_HITS();
		return retval;
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_HAS_BONE_BEEN_HIT_BY_KILLER( int boneIndex )
	{
		auto retval = (bool)NETWORK::NETWORK_HAS_BONE_BEEN_HIT_BY_KILLER(boneIndex);
		return retval;
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_SET_ATTRIBUTE_DAMAGE_TO_PLAYER( Ped ped, Player player )
	{
		auto retval = (bool)NETWORK::NETWORK_SET_ATTRIBUTE_DAMAGE_TO_PLAYER(ped, player);
		return retval;
	}

	static void LUA_NATIVE_NETWORK_NETWORK_TRIGGER_DAMAGE_EVENT_FOR_ZERO_DAMAGE( Entity entity, bool toggle )
	{
		NETWORK::NETWORK_TRIGGER_DAMAGE_EVENT_FOR_ZERO_DAMAGE(entity, toggle);
	}

	static void LUA_NATIVE_NETWORK_NETWORK_TRIGGER_DAMAGE_EVENT_FOR_ZERO_WEAPON_HASH( Entity entity, bool toggle )
	{
		NETWORK::NETWORK_TRIGGER_DAMAGE_EVENT_FOR_ZERO_WEAPON_HASH(entity, toggle);
	}

	static void LUA_NATIVE_NETWORK_NETWORK_SET_NO_LONGER_NEEDED( Entity entity, bool toggle )
	{
		NETWORK::NETWORK_SET_NO_LONGER_NEEDED(entity, toggle);
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_EXPLODE_VEHICLE( Vehicle vehicle, bool isAudible, bool isInvisible, int netId )
	{
		auto retval = (bool)NETWORK::NETWORK_EXPLODE_VEHICLE(vehicle, isAudible, isInvisible, netId);
		return retval;
	}

	static void LUA_NATIVE_NETWORK_NETWORK_EXPLODE_HELI( Vehicle vehicle, bool isAudible, bool isInvisible, int netId )
	{
		NETWORK::NETWORK_EXPLODE_HELI(vehicle, isAudible, isInvisible, netId);
	}

	static void LUA_NATIVE_NETWORK_NETWORK_USE_LOGARITHMIC_BLENDING_THIS_FRAME( Entity entity )
	{
		NETWORK::NETWORK_USE_LOGARITHMIC_BLENDING_THIS_FRAME(entity);
	}

	static void LUA_NATIVE_NETWORK_NETWORK_OVERRIDE_COORDS_AND_HEADING( Entity entity, float x, float y, float z, float heading )
	{
		NETWORK::NETWORK_OVERRIDE_COORDS_AND_HEADING(entity, x, y, z, heading);
	}

	static void LUA_NATIVE_NETWORK_NETWORK_ENABLE_EXTRA_VEHICLE_ORIENTATION_BLEND_CHECKS( int netId, bool toggle )
	{
		NETWORK::NETWORK_ENABLE_EXTRA_VEHICLE_ORIENTATION_BLEND_CHECKS(netId, toggle);
	}

	static void LUA_NATIVE_NETWORK_NETWORK_DISABLE_PROXIMITY_MIGRATION( int netID )
	{
		NETWORK::NETWORK_DISABLE_PROXIMITY_MIGRATION(netID);
	}

	static void LUA_NATIVE_NETWORK_NETWORK_SET_PROPERTY_ID( int id )
	{
		NETWORK::NETWORK_SET_PROPERTY_ID(id);
	}

	static void LUA_NATIVE_NETWORK_NETWORK_CLEAR_PROPERTY_ID(  )
	{
		NETWORK::NETWORK_CLEAR_PROPERTY_ID();
	}

	static void LUA_NATIVE_NETWORK_NETWORK_SET_PLAYER_MENTAL_STATE( int p0 )
	{
		NETWORK::NETWORK_SET_PLAYER_MENTAL_STATE(p0);
	}

	static void LUA_NATIVE_NETWORK_NETWORK_SET_MINIMUM_RANK_FOR_MISSION( bool p0 )
	{
		NETWORK::NETWORK_SET_MINIMUM_RANK_FOR_MISSION(p0);
	}

	static void LUA_NATIVE_NETWORK_NETWORK_CACHE_LOCAL_PLAYER_HEAD_BLEND_DATA(  )
	{
		NETWORK::NETWORK_CACHE_LOCAL_PLAYER_HEAD_BLEND_DATA();
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_HAS_CACHED_PLAYER_HEAD_BLEND_DATA( Player player )
	{
		auto retval = (bool)NETWORK::NETWORK_HAS_CACHED_PLAYER_HEAD_BLEND_DATA(player);
		return retval;
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_APPLY_CACHED_PLAYER_HEAD_BLEND_DATA( Ped ped, Player player )
	{
		auto retval = (bool)NETWORK::NETWORK_APPLY_CACHED_PLAYER_HEAD_BLEND_DATA(ped, player);
		return retval;
	}

	static int LUA_NATIVE_NETWORK_GET_NUM_COMMERCE_ITEMS(  )
	{
		auto retval = NETWORK::GET_NUM_COMMERCE_ITEMS();
		return retval;
	}

	static bool LUA_NATIVE_NETWORK_IS_COMMERCE_DATA_VALID(  )
	{
		auto retval = (bool)NETWORK::IS_COMMERCE_DATA_VALID();
		return retval;
	}

	static void LUA_NATIVE_NETWORK_TRIGGER_COMMERCE_DATA_FETCH( Any p0 )
	{
		NETWORK::TRIGGER_COMMERCE_DATA_FETCH(p0);
	}

	static bool LUA_NATIVE_NETWORK_IS_COMMERCE_DATA_FETCH_IN_PROGRESS(  )
	{
		auto retval = (bool)NETWORK::IS_COMMERCE_DATA_FETCH_IN_PROGRESS();
		return retval;
	}

	static const char* LUA_NATIVE_NETWORK_GET_COMMERCE_ITEM_ID( int index )
	{
		auto retval = NETWORK::GET_COMMERCE_ITEM_ID(index);
		return retval;
	}

	static const char* LUA_NATIVE_NETWORK_GET_COMMERCE_ITEM_NAME( int index )
	{
		auto retval = NETWORK::GET_COMMERCE_ITEM_NAME(index);
		return retval;
	}

	static const char* LUA_NATIVE_NETWORK_GET_COMMERCE_PRODUCT_PRICE( int index )
	{
		auto retval = NETWORK::GET_COMMERCE_PRODUCT_PRICE(index);
		return retval;
	}

	static int LUA_NATIVE_NETWORK_GET_COMMERCE_ITEM_NUM_CATS( int index )
	{
		auto retval = NETWORK::GET_COMMERCE_ITEM_NUM_CATS(index);
		return retval;
	}

	static const char* LUA_NATIVE_NETWORK_GET_COMMERCE_ITEM_CAT( int index, int index2 )
	{
		auto retval = NETWORK::GET_COMMERCE_ITEM_CAT(index, index2);
		return retval;
	}

	static void LUA_NATIVE_NETWORK_OPEN_COMMERCE_STORE( const char* p0, const char* p1, int p2 )
	{
		NETWORK::OPEN_COMMERCE_STORE(p0, p1, p2);
	}

	static bool LUA_NATIVE_NETWORK_IS_COMMERCE_STORE_OPEN(  )
	{
		auto retval = (bool)NETWORK::IS_COMMERCE_STORE_OPEN();
		return retval;
	}

	static void LUA_NATIVE_NETWORK_SET_STORE_ENABLED( bool toggle )
	{
		NETWORK::SET_STORE_ENABLED(toggle);
	}

	static bool LUA_NATIVE_NETWORK_REQUEST_COMMERCE_ITEM_IMAGE( int index )
	{
		auto retval = (bool)NETWORK::REQUEST_COMMERCE_ITEM_IMAGE(index);
		return retval;
	}

	static void LUA_NATIVE_NETWORK_RELEASE_ALL_COMMERCE_ITEM_IMAGES(  )
	{
		NETWORK::RELEASE_ALL_COMMERCE_ITEM_IMAGES();
	}

	static const char* LUA_NATIVE_NETWORK_GET_COMMERCE_ITEM_TEXTURENAME( int index )
	{
		auto retval = NETWORK::GET_COMMERCE_ITEM_TEXTURENAME(index);
		return retval;
	}

	static bool LUA_NATIVE_NETWORK_IS_STORE_AVAILABLE_TO_USER(  )
	{
		auto retval = (bool)NETWORK::IS_STORE_AVAILABLE_TO_USER();
		return retval;
	}

	static void LUA_NATIVE_NETWORK_DELAY_MP_STORE_OPEN(  )
	{
		NETWORK::DELAY_MP_STORE_OPEN();
	}

	static void LUA_NATIVE_NETWORK_RESET_STORE_NETWORK_GAME_TRACKING(  )
	{
		NETWORK::RESET_STORE_NETWORK_GAME_TRACKING();
	}

	static bool LUA_NATIVE_NETWORK_IS_USER_OLD_ENOUGH_TO_ACCESS_STORE(  )
	{
		auto retval = (bool)NETWORK::IS_USER_OLD_ENOUGH_TO_ACCESS_STORE();
		return retval;
	}

	static void LUA_NATIVE_NETWORK_SET_LAST_VIEWED_SHOP_ITEM( Hash p0, int p1, Hash p2 )
	{
		NETWORK::SET_LAST_VIEWED_SHOP_ITEM(p0, p1, p2);
	}

	static int LUA_NATIVE_NETWORK_GET_USER_PREMIUM_ACCESS(  )
	{
		auto retval = NETWORK::GET_USER_PREMIUM_ACCESS();
		return retval;
	}

	static int LUA_NATIVE_NETWORK_GET_USER_STARTER_ACCESS(  )
	{
		auto retval = NETWORK::GET_USER_STARTER_ACCESS();
		return retval;
	}

	static int LUA_NATIVE_NETWORK_CLOUD_DELETE_MEMBER_FILE( const char* p0 )
	{
		auto retval = NETWORK::CLOUD_DELETE_MEMBER_FILE(p0);
		return retval;
	}

	static bool LUA_NATIVE_NETWORK_CLOUD_HAS_REQUEST_COMPLETED( int requestId )
	{
		auto retval = (bool)NETWORK::CLOUD_HAS_REQUEST_COMPLETED(requestId);
		return retval;
	}

	static bool LUA_NATIVE_NETWORK_CLOUD_DID_REQUEST_SUCCEED( int requestId )
	{
		auto retval = (bool)NETWORK::CLOUD_DID_REQUEST_SUCCEED(requestId);
		return retval;
	}

	static void LUA_NATIVE_NETWORK_CLOUD_CHECK_AVAILABILITY(  )
	{
		NETWORK::CLOUD_CHECK_AVAILABILITY();
	}

	static bool LUA_NATIVE_NETWORK_CLOUD_IS_CHECKING_AVAILABILITY(  )
	{
		auto retval = (bool)NETWORK::CLOUD_IS_CHECKING_AVAILABILITY();
		return retval;
	}

	static bool LUA_NATIVE_NETWORK_CLOUD_GET_AVAILABILITY_CHECK_RESULT(  )
	{
		auto retval = (bool)NETWORK::CLOUD_GET_AVAILABILITY_CHECK_RESULT();
		return retval;
	}

	static int LUA_NATIVE_NETWORK_GET_CONTENT_TO_LOAD_TYPE(  )
	{
		auto retval = NETWORK::GET_CONTENT_TO_LOAD_TYPE();
		return retval;
	}

	static bool LUA_NATIVE_NETWORK_GET_IS_LAUNCH_FROM_LIVE_AREA(  )
	{
		auto retval = (bool)NETWORK::GET_IS_LAUNCH_FROM_LIVE_AREA();
		return retval;
	}

	static bool LUA_NATIVE_NETWORK_GET_IS_LIVE_AREA_LAUNCH_WITH_CONTENT(  )
	{
		auto retval = (bool)NETWORK::GET_IS_LIVE_AREA_LAUNCH_WITH_CONTENT();
		return retval;
	}

	static void LUA_NATIVE_NETWORK_CLEAR_SERVICE_EVENT_ARGUMENTS(  )
	{
		NETWORK::CLEAR_SERVICE_EVENT_ARGUMENTS();
	}

	static std::tuple<bool, Any, Any> LUA_NATIVE_NETWORK_UGC_COPY_CONTENT( Any p0, Any p1 )
	{
		std::tuple<bool, Any, Any> return_values;
		std::get<0>(return_values) = (bool)NETWORK::UGC_COPY_CONTENT(&p0, &p1);
		std::get<1>(return_values) = p0;
		std::get<2>(return_values) = p1;

		return return_values;
	}

	static bool LUA_NATIVE_NETWORK_UGC_IS_CREATING(  )
	{
		auto retval = (bool)NETWORK::UGC_IS_CREATING();
		return retval;
	}

	static bool LUA_NATIVE_NETWORK_UGC_HAS_CREATE_FINISHED(  )
	{
		auto retval = (bool)NETWORK::UGC_HAS_CREATE_FINISHED();
		return retval;
	}

	static bool LUA_NATIVE_NETWORK_UGC_DID_CREATE_SUCCEED(  )
	{
		auto retval = (bool)NETWORK::UGC_DID_CREATE_SUCCEED();
		return retval;
	}

	static int LUA_NATIVE_NETWORK_UGC_GET_CREATE_RESULT(  )
	{
		auto retval = NETWORK::UGC_GET_CREATE_RESULT();
		return retval;
	}

	static const char* LUA_NATIVE_NETWORK_UGC_GET_CREATE_CONTENT_ID(  )
	{
		auto retval = NETWORK::UGC_GET_CREATE_CONTENT_ID();
		return retval;
	}

	static void LUA_NATIVE_NETWORK_UGC_CLEAR_CREATE_RESULT(  )
	{
		NETWORK::UGC_CLEAR_CREATE_RESULT();
	}

	static std::tuple<bool, Any> LUA_NATIVE_NETWORK_UGC_QUERY_MY_CONTENT( Any p0, Any p1, Any p2, Any p3, Any p4, Any p5 )
	{
		std::tuple<bool, Any> return_values;
		std::get<0>(return_values) = (bool)NETWORK::UGC_QUERY_MY_CONTENT(p0, p1, &p2, p3, p4, p5);
		std::get<1>(return_values) = p2;

		return return_values;
	}

	static bool LUA_NATIVE_NETWORK_UGC_QUERY_BY_CATEGORY( Any p0, Any p1, Any p2, const char* p3, Any p4, bool p5 )
	{
		auto retval = (bool)NETWORK::UGC_QUERY_BY_CATEGORY(p0, p1, p2, p3, p4, p5);
		return retval;
	}

	static bool LUA_NATIVE_NETWORK_UGC_QUERY_BY_CONTENT_ID( const char* contentId, bool latestVersion, const char* contentTypeName )
	{
		auto retval = (bool)NETWORK::UGC_QUERY_BY_CONTENT_ID(contentId, latestVersion, contentTypeName);
		return retval;
	}

	static std::tuple<bool, Any> LUA_NATIVE_NETWORK_UGC_QUERY_BY_CONTENT_IDS( Any data, int count, bool latestVersion, const char* contentTypeName )
	{
		std::tuple<bool, Any> return_values;
		std::get<0>(return_values) = (bool)NETWORK::UGC_QUERY_BY_CONTENT_IDS(&data, count, latestVersion, contentTypeName);
		std::get<1>(return_values) = data;

		return return_values;
	}

	static bool LUA_NATIVE_NETWORK_UGC_QUERY_MOST_RECENTLY_CREATED_CONTENT( int offset, int count, const char* contentTypeName, int p3 )
	{
		auto retval = (bool)NETWORK::UGC_QUERY_MOST_RECENTLY_CREATED_CONTENT(offset, count, contentTypeName, p3);
		return retval;
	}

	static std::tuple<bool, Any> LUA_NATIVE_NETWORK_UGC_GET_BOOKMARKED_CONTENT( Any p0, Any p1, const char* p2, Any p3 )
	{
		std::tuple<bool, Any> return_values;
		std::get<0>(return_values) = (bool)NETWORK::UGC_GET_BOOKMARKED_CONTENT(p0, p1, p2, &p3);
		std::get<1>(return_values) = p3;

		return return_values;
	}

	static std::tuple<bool, Any> LUA_NATIVE_NETWORK_UGC_GET_MY_CONTENT( Any p0, Any p1, const char* p2, Any p3 )
	{
		std::tuple<bool, Any> return_values;
		std::get<0>(return_values) = (bool)NETWORK::UGC_GET_MY_CONTENT(p0, p1, p2, &p3);
		std::get<1>(return_values) = p3;

		return return_values;
	}

	static std::tuple<bool, Any> LUA_NATIVE_NETWORK_UGC_GET_FRIEND_CONTENT( Any p0, Any p1, const char* p2, Any p3 )
	{
		std::tuple<bool, Any> return_values;
		std::get<0>(return_values) = (bool)NETWORK::UGC_GET_FRIEND_CONTENT(p0, p1, p2, &p3);
		std::get<1>(return_values) = p3;

		return return_values;
	}

	static std::tuple<bool, Any> LUA_NATIVE_NETWORK_UGC_GET_CREW_CONTENT( Any p0, Any p1, Any p2, const char* p3, Any p4 )
	{
		std::tuple<bool, Any> return_values;
		std::get<0>(return_values) = (bool)NETWORK::UGC_GET_CREW_CONTENT(p0, p1, p2, p3, &p4);
		std::get<1>(return_values) = p4;

		return return_values;
	}

	static std::tuple<bool, Any> LUA_NATIVE_NETWORK_UGC_GET_GET_BY_CATEGORY( Any p0, Any p1, Any p2, const char* p3, Any p4 )
	{
		std::tuple<bool, Any> return_values;
		std::get<0>(return_values) = (bool)NETWORK::UGC_GET_GET_BY_CATEGORY(p0, p1, p2, p3, &p4);
		std::get<1>(return_values) = p4;

		return return_values;
	}

	static bool LUA_NATIVE_NETWORK_UGC_GET_GET_BY_CONTENT_ID( const char* contentId, const char* contentTypeName )
	{
		auto retval = (bool)NETWORK::UGC_GET_GET_BY_CONTENT_ID(contentId, contentTypeName);
		return retval;
	}

	static std::tuple<bool, Any> LUA_NATIVE_NETWORK_UGC_GET_GET_BY_CONTENT_IDS( Any data, int dataCount, const char* contentTypeName )
	{
		std::tuple<bool, Any> return_values;
		std::get<0>(return_values) = (bool)NETWORK::UGC_GET_GET_BY_CONTENT_IDS(&data, dataCount, contentTypeName);
		std::get<1>(return_values) = data;

		return return_values;
	}

	static std::tuple<bool, Any, Any> LUA_NATIVE_NETWORK_UGC_GET_MOST_RECENTLY_CREATED_CONTENT( Any p0, Any p1, Any p2, Any p3 )
	{
		std::tuple<bool, Any, Any> return_values;
		std::get<0>(return_values) = (bool)NETWORK::UGC_GET_MOST_RECENTLY_CREATED_CONTENT(p0, p1, &p2, &p3);
		std::get<1>(return_values) = p2;
		std::get<2>(return_values) = p3;

		return return_values;
	}

	static std::tuple<bool, Any, Any> LUA_NATIVE_NETWORK_UGC_GET_MOST_RECENTLY_PLAYED_CONTENT( Any p0, Any p1, Any p2, Any p3 )
	{
		std::tuple<bool, Any, Any> return_values;
		std::get<0>(return_values) = (bool)NETWORK::UGC_GET_MOST_RECENTLY_PLAYED_CONTENT(p0, p1, &p2, &p3);
		std::get<1>(return_values) = p2;
		std::get<2>(return_values) = p3;

		return return_values;
	}

	static std::tuple<bool, Any, Any> LUA_NATIVE_NETWORK_UGC_GET_TOP_RATED_CONTENT( Any p0, Any p1, Any p2, Any p3 )
	{
		std::tuple<bool, Any, Any> return_values;
		std::get<0>(return_values) = (bool)NETWORK::UGC_GET_TOP_RATED_CONTENT(p0, p1, &p2, &p3);
		std::get<1>(return_values) = p2;
		std::get<2>(return_values) = p3;

		return return_values;
	}

	static void LUA_NATIVE_NETWORK_UGC_CANCEL_QUERY(  )
	{
		NETWORK::UGC_CANCEL_QUERY();
	}

	static bool LUA_NATIVE_NETWORK_UGC_IS_GETTING(  )
	{
		auto retval = (bool)NETWORK::UGC_IS_GETTING();
		return retval;
	}

	static bool LUA_NATIVE_NETWORK_UGC_HAS_GET_FINISHED(  )
	{
		auto retval = (bool)NETWORK::UGC_HAS_GET_FINISHED();
		return retval;
	}

	static bool LUA_NATIVE_NETWORK_UGC_DID_GET_SUCCEED(  )
	{
		auto retval = (bool)NETWORK::UGC_DID_GET_SUCCEED();
		return retval;
	}

	static bool LUA_NATIVE_NETWORK_UGC_WAS_QUERY_FORCE_CANCELLED(  )
	{
		auto retval = (bool)NETWORK::UGC_WAS_QUERY_FORCE_CANCELLED();
		return retval;
	}

	static int LUA_NATIVE_NETWORK_UGC_GET_QUERY_RESULT(  )
	{
		auto retval = NETWORK::UGC_GET_QUERY_RESULT();
		return retval;
	}

	static int LUA_NATIVE_NETWORK_UGC_GET_CONTENT_NUM(  )
	{
		auto retval = NETWORK::UGC_GET_CONTENT_NUM();
		return retval;
	}

	static int LUA_NATIVE_NETWORK_UGC_GET_CONTENT_TOTAL(  )
	{
		auto retval = NETWORK::UGC_GET_CONTENT_TOTAL();
		return retval;
	}

	static Hash LUA_NATIVE_NETWORK_UGC_GET_CONTENT_HASH(  )
	{
		auto retval = NETWORK::UGC_GET_CONTENT_HASH();
		return retval;
	}

	static void LUA_NATIVE_NETWORK_UGC_CLEAR_QUERY_RESULTS(  )
	{
		NETWORK::UGC_CLEAR_QUERY_RESULTS();
	}

	static const char* LUA_NATIVE_NETWORK_UGC_GET_CONTENT_USER_ID( int p0 )
	{
		auto retval = NETWORK::UGC_GET_CONTENT_USER_ID(p0);
		return retval;
	}

	static std::tuple<bool, Any> LUA_NATIVE_NETWORK_UGC_GET_CONTENT_CREATOR_GAMER_HANDLE( int p0, Any p1 )
	{
		std::tuple<bool, Any> return_values;
		std::get<0>(return_values) = (bool)NETWORK::UGC_GET_CONTENT_CREATOR_GAMER_HANDLE(p0, &p1);
		std::get<1>(return_values) = p1;

		return return_values;
	}

	static bool LUA_NATIVE_NETWORK_UGC_GET_CONTENT_CREATED_BY_LOCAL_PLAYER( Any p0 )
	{
		auto retval = (bool)NETWORK::UGC_GET_CONTENT_CREATED_BY_LOCAL_PLAYER(p0);
		return retval;
	}

	static const char* LUA_NATIVE_NETWORK_UGC_GET_CONTENT_USER_NAME( Any p0 )
	{
		auto retval = NETWORK::UGC_GET_CONTENT_USER_NAME(p0);
		return retval;
	}

	static bool LUA_NATIVE_NETWORK_UGC_GET_CONTENT_IS_USING_SC_NICKNAME( Any p0 )
	{
		auto retval = (bool)NETWORK::UGC_GET_CONTENT_IS_USING_SC_NICKNAME(p0);
		return retval;
	}

	static int LUA_NATIVE_NETWORK_UGC_GET_CONTENT_CATEGORY( int p0 )
	{
		auto retval = NETWORK::UGC_GET_CONTENT_CATEGORY(p0);
		return retval;
	}

	static const char* LUA_NATIVE_NETWORK_UGC_GET_CONTENT_ID( int p0 )
	{
		auto retval = NETWORK::UGC_GET_CONTENT_ID(p0);
		return retval;
	}

	static const char* LUA_NATIVE_NETWORK_UGC_GET_ROOT_CONTENT_ID( int p0 )
	{
		auto retval = NETWORK::UGC_GET_ROOT_CONTENT_ID(p0);
		return retval;
	}

	static const char* LUA_NATIVE_NETWORK_UGC_GET_CONTENT_NAME( Any p0 )
	{
		auto retval = NETWORK::UGC_GET_CONTENT_NAME(p0);
		return retval;
	}

	static int LUA_NATIVE_NETWORK_UGC_GET_CONTENT_DESCRIPTION_HASH( Any p0 )
	{
		auto retval = NETWORK::UGC_GET_CONTENT_DESCRIPTION_HASH(p0);
		return retval;
	}

	static const char* LUA_NATIVE_NETWORK_UGC_GET_CONTENT_PATH( int p0, int p1 )
	{
		auto retval = NETWORK::UGC_GET_CONTENT_PATH(p0, p1);
		return retval;
	}

	static Any LUA_NATIVE_NETWORK_UGC_GET_CONTENT_UPDATED_DATE( Any p0, Any p1 )
	{
		NETWORK::UGC_GET_CONTENT_UPDATED_DATE(p0, &p1);
		return p1;
	}

	static int LUA_NATIVE_NETWORK_UGC_GET_CONTENT_FILE_VERSION( Any p0, Any p1 )
	{
		auto retval = NETWORK::UGC_GET_CONTENT_FILE_VERSION(p0, p1);
		return retval;
	}

	static bool LUA_NATIVE_NETWORK_UGC_GET_CONTENT_HAS_LO_RES_PHOTO( int p0 )
	{
		auto retval = (bool)NETWORK::UGC_GET_CONTENT_HAS_LO_RES_PHOTO(p0);
		return retval;
	}

	static bool LUA_NATIVE_NETWORK_UGC_GET_CONTENT_HAS_HI_RES_PHOTO( int p0 )
	{
		auto retval = (bool)NETWORK::UGC_GET_CONTENT_HAS_HI_RES_PHOTO(p0);
		return retval;
	}

	static int LUA_NATIVE_NETWORK_UGC_GET_CONTENT_LANGUAGE( Any p0 )
	{
		auto retval = NETWORK::UGC_GET_CONTENT_LANGUAGE(p0);
		return retval;
	}

	static bool LUA_NATIVE_NETWORK_UGC_GET_CONTENT_IS_PUBLISHED( Any p0 )
	{
		auto retval = (bool)NETWORK::UGC_GET_CONTENT_IS_PUBLISHED(p0);
		return retval;
	}

	static bool LUA_NATIVE_NETWORK_UGC_GET_CONTENT_IS_VERIFIED( Any p0 )
	{
		auto retval = (bool)NETWORK::UGC_GET_CONTENT_IS_VERIFIED(p0);
		return retval;
	}

	static float LUA_NATIVE_NETWORK_UGC_GET_CONTENT_RATING( Any p0, Any p1 )
	{
		auto retval = NETWORK::UGC_GET_CONTENT_RATING(p0, p1);
		return retval;
	}

	static int LUA_NATIVE_NETWORK_UGC_GET_CONTENT_RATING_COUNT( Any p0, Any p1 )
	{
		auto retval = NETWORK::UGC_GET_CONTENT_RATING_COUNT(p0, p1);
		return retval;
	}

	static int LUA_NATIVE_NETWORK_UGC_GET_CONTENT_RATING_POSITIVE_COUNT( Any p0, Any p1 )
	{
		auto retval = NETWORK::UGC_GET_CONTENT_RATING_POSITIVE_COUNT(p0, p1);
		return retval;
	}

	static int LUA_NATIVE_NETWORK_UGC_GET_CONTENT_RATING_NEGATIVE_COUNT( Any p0, Any p1 )
	{
		auto retval = NETWORK::UGC_GET_CONTENT_RATING_NEGATIVE_COUNT(p0, p1);
		return retval;
	}

	static bool LUA_NATIVE_NETWORK_UGC_GET_CONTENT_HAS_PLAYER_RECORD( Any p0 )
	{
		auto retval = (bool)NETWORK::UGC_GET_CONTENT_HAS_PLAYER_RECORD(p0);
		return retval;
	}

	static bool LUA_NATIVE_NETWORK_UGC_GET_CONTENT_HAS_PLAYER_BOOKMARKED( Any p0 )
	{
		auto retval = (bool)NETWORK::UGC_GET_CONTENT_HAS_PLAYER_BOOKMARKED(p0);
		return retval;
	}

	static int LUA_NATIVE_NETWORK_UGC_REQUEST_CONTENT_DATA_FROM_INDEX( int p0, int p1 )
	{
		auto retval = NETWORK::UGC_REQUEST_CONTENT_DATA_FROM_INDEX(p0, p1);
		return retval;
	}

	static int LUA_NATIVE_NETWORK_UGC_REQUEST_CONTENT_DATA_FROM_PARAMS( const char* contentTypeName, const char* contentId, int p2, int p3, int p4 )
	{
		auto retval = NETWORK::UGC_REQUEST_CONTENT_DATA_FROM_PARAMS(contentTypeName, contentId, p2, p3, p4);
		return retval;
	}

	static int LUA_NATIVE_NETWORK_UGC_REQUEST_CACHED_DESCRIPTION( int p0 )
	{
		auto retval = NETWORK::UGC_REQUEST_CACHED_DESCRIPTION(p0);
		return retval;
	}

	static bool LUA_NATIVE_NETWORK_UGC_IS_DESCRIPTION_REQUEST_IN_PROGRESS( Any p0 )
	{
		auto retval = (bool)NETWORK::UGC_IS_DESCRIPTION_REQUEST_IN_PROGRESS(p0);
		return retval;
	}

	static bool LUA_NATIVE_NETWORK_UGC_HAS_DESCRIPTION_REQUEST_FINISHED( Any p0 )
	{
		auto retval = (bool)NETWORK::UGC_HAS_DESCRIPTION_REQUEST_FINISHED(p0);
		return retval;
	}

	static bool LUA_NATIVE_NETWORK_UGC_DID_DESCRIPTION_REQUEST_SUCCEED( Any p0 )
	{
		auto retval = (bool)NETWORK::UGC_DID_DESCRIPTION_REQUEST_SUCCEED(p0);
		return retval;
	}

	static const char* LUA_NATIVE_NETWORK_UGC_GET_CACHED_DESCRIPTION( Any p0, Any p1 )
	{
		auto retval = NETWORK::UGC_GET_CACHED_DESCRIPTION(p0, p1);
		return retval;
	}

	static bool LUA_NATIVE_NETWORK_UGC_RELEASE_CACHED_DESCRIPTION( Any p0 )
	{
		auto retval = (bool)NETWORK::UGC_RELEASE_CACHED_DESCRIPTION(p0);
		return retval;
	}

	static void LUA_NATIVE_NETWORK_UGC_RELEASE_ALL_CACHED_DESCRIPTIONS(  )
	{
		NETWORK::UGC_RELEASE_ALL_CACHED_DESCRIPTIONS();
	}

	static bool LUA_NATIVE_NETWORK_UGC_PUBLISH( const char* contentId, const char* baseContentId, const char* contentTypeName )
	{
		auto retval = (bool)NETWORK::UGC_PUBLISH(contentId, baseContentId, contentTypeName);
		return retval;
	}

	static bool LUA_NATIVE_NETWORK_UGC_SET_BOOKMARKED( const char* contentId, bool bookmarked, const char* contentTypeName )
	{
		auto retval = (bool)NETWORK::UGC_SET_BOOKMARKED(contentId, bookmarked, contentTypeName);
		return retval;
	}

	static std::tuple<bool, Any> LUA_NATIVE_NETWORK_UGC_SET_DELETED( Any p0, bool p1, const char* p2 )
	{
		std::tuple<bool, Any> return_values;
		std::get<0>(return_values) = (bool)NETWORK::UGC_SET_DELETED(&p0, p1, p2);
		std::get<1>(return_values) = p0;

		return return_values;
	}

	static bool LUA_NATIVE_NETWORK_UGC_IS_MODIFYING(  )
	{
		auto retval = (bool)NETWORK::UGC_IS_MODIFYING();
		return retval;
	}

	static bool LUA_NATIVE_NETWORK_UGC_HAS_MODIFY_FINISHED(  )
	{
		auto retval = (bool)NETWORK::UGC_HAS_MODIFY_FINISHED();
		return retval;
	}

	static bool LUA_NATIVE_NETWORK_UGC_DID_MODIFY_SUCCEED(  )
	{
		auto retval = (bool)NETWORK::UGC_DID_MODIFY_SUCCEED();
		return retval;
	}

	static int LUA_NATIVE_NETWORK_UGC_GET_MODIFY_RESULT(  )
	{
		auto retval = NETWORK::UGC_GET_MODIFY_RESULT();
		return retval;
	}

	static void LUA_NATIVE_NETWORK_UGC_CLEAR_MODIFY_RESULT(  )
	{
		NETWORK::UGC_CLEAR_MODIFY_RESULT();
	}

	static std::tuple<bool, Any, Any> LUA_NATIVE_NETWORK_UGC_GET_CREATORS_BY_USER_ID( Any p0, Any p1 )
	{
		std::tuple<bool, Any, Any> return_values;
		std::get<0>(return_values) = (bool)NETWORK::UGC_GET_CREATORS_BY_USER_ID(&p0, &p1);
		std::get<1>(return_values) = p0;
		std::get<2>(return_values) = p1;

		return return_values;
	}

	static bool LUA_NATIVE_NETWORK_UGC_HAS_QUERY_CREATORS_FINISHED(  )
	{
		auto retval = (bool)NETWORK::UGC_HAS_QUERY_CREATORS_FINISHED();
		return retval;
	}

	static bool LUA_NATIVE_NETWORK_UGC_DID_QUERY_CREATORS_SUCCEED(  )
	{
		auto retval = (bool)NETWORK::UGC_DID_QUERY_CREATORS_SUCCEED();
		return retval;
	}

	static int LUA_NATIVE_NETWORK_UGC_GET_CREATOR_NUM(  )
	{
		auto retval = NETWORK::UGC_GET_CREATOR_NUM();
		return retval;
	}

	static bool LUA_NATIVE_NETWORK_UGC_LOAD_OFFLINE_QUERY( Any p0 )
	{
		auto retval = (bool)NETWORK::UGC_LOAD_OFFLINE_QUERY(p0);
		return retval;
	}

	static void LUA_NATIVE_NETWORK_UGC_CLEAR_OFFLINE_QUERY(  )
	{
		NETWORK::UGC_CLEAR_OFFLINE_QUERY();
	}

	static void LUA_NATIVE_NETWORK_UGC_SET_QUERY_DATA_FROM_OFFLINE( bool p0 )
	{
		NETWORK::UGC_SET_QUERY_DATA_FROM_OFFLINE(p0);
	}

	static void LUA_NATIVE_NETWORK_UGC_SET_USING_OFFLINE_CONTENT( bool p0 )
	{
		NETWORK::UGC_SET_USING_OFFLINE_CONTENT(p0);
	}

	static bool LUA_NATIVE_NETWORK_UGC_IS_LANGUAGE_SUPPORTED( Any p0 )
	{
		auto retval = (bool)NETWORK::UGC_IS_LANGUAGE_SUPPORTED(p0);
		return retval;
	}

	static bool LUA_NATIVE_NETWORK_FACEBOOK_POST_COMPLETED_HEIST( const char* heistName, int cashEarned, int xpEarned )
	{
		auto retval = (bool)NETWORK::FACEBOOK_POST_COMPLETED_HEIST(heistName, cashEarned, xpEarned);
		return retval;
	}

	static bool LUA_NATIVE_NETWORK_FACEBOOK_POST_CREATE_CHARACTER(  )
	{
		auto retval = (bool)NETWORK::FACEBOOK_POST_CREATE_CHARACTER();
		return retval;
	}

	static bool LUA_NATIVE_NETWORK_FACEBOOK_POST_COMPLETED_MILESTONE( int milestoneId )
	{
		auto retval = (bool)NETWORK::FACEBOOK_POST_COMPLETED_MILESTONE(milestoneId);
		return retval;
	}

	static bool LUA_NATIVE_NETWORK_FACEBOOK_HAS_POST_COMPLETED(  )
	{
		auto retval = (bool)NETWORK::FACEBOOK_HAS_POST_COMPLETED();
		return retval;
	}

	static bool LUA_NATIVE_NETWORK_FACEBOOK_DID_POST_SUCCEED(  )
	{
		auto retval = (bool)NETWORK::FACEBOOK_DID_POST_SUCCEED();
		return retval;
	}

	static bool LUA_NATIVE_NETWORK_FACEBOOK_CAN_POST_TO_FACEBOOK(  )
	{
		auto retval = (bool)NETWORK::FACEBOOK_CAN_POST_TO_FACEBOOK();
		return retval;
	}

	static std::tuple<int, Any> LUA_NATIVE_NETWORK_TEXTURE_DOWNLOAD_REQUEST( Any gamerHandle, const char* filePath, const char* name, bool p3 )
	{
		std::tuple<int, Any> return_values;
		std::get<0>(return_values) = NETWORK::TEXTURE_DOWNLOAD_REQUEST(&gamerHandle, filePath, name, p3);
		std::get<1>(return_values) = gamerHandle;

		return return_values;
	}

	static int LUA_NATIVE_NETWORK_TITLE_TEXTURE_DOWNLOAD_REQUEST( const char* filePath, const char* name, bool p2 )
	{
		auto retval = NETWORK::TITLE_TEXTURE_DOWNLOAD_REQUEST(filePath, name, p2);
		return retval;
	}

	static int LUA_NATIVE_NETWORK_UGC_TEXTURE_DOWNLOAD_REQUEST( const char* p0, int p1, int p2, int p3, const char* p4, bool p5 )
	{
		auto retval = NETWORK::UGC_TEXTURE_DOWNLOAD_REQUEST(p0, p1, p2, p3, p4, p5);
		return retval;
	}

	static void LUA_NATIVE_NETWORK_TEXTURE_DOWNLOAD_RELEASE( int p0 )
	{
		NETWORK::TEXTURE_DOWNLOAD_RELEASE(p0);
	}

	static bool LUA_NATIVE_NETWORK_TEXTURE_DOWNLOAD_HAS_FAILED( int p0 )
	{
		auto retval = (bool)NETWORK::TEXTURE_DOWNLOAD_HAS_FAILED(p0);
		return retval;
	}

	static const char* LUA_NATIVE_NETWORK_TEXTURE_DOWNLOAD_GET_NAME( int p0 )
	{
		auto retval = NETWORK::TEXTURE_DOWNLOAD_GET_NAME(p0);
		return retval;
	}

	static int LUA_NATIVE_NETWORK_GET_STATUS_OF_TEXTURE_DOWNLOAD( int p0 )
	{
		auto retval = NETWORK::GET_STATUS_OF_TEXTURE_DOWNLOAD(p0);
		return retval;
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_CHECK_ROS_LINK_WENTDOWN_NOT_NET(  )
	{
		auto retval = (bool)NETWORK::NETWORK_CHECK_ROS_LINK_WENTDOWN_NOT_NET();
		return retval;
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_SHOULD_SHOW_STRICT_NAT_WARNING(  )
	{
		auto retval = (bool)NETWORK::NETWORK_SHOULD_SHOW_STRICT_NAT_WARNING();
		return retval;
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_IS_CABLE_CONNECTED(  )
	{
		auto retval = (bool)NETWORK::NETWORK_IS_CABLE_CONNECTED();
		return retval;
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_HAVE_SCS_PRIVATE_MSG_PRIV(  )
	{
		auto retval = (bool)NETWORK::NETWORK_HAVE_SCS_PRIVATE_MSG_PRIV();
		return retval;
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_HAVE_ROS_SOCIAL_CLUB_PRIV(  )
	{
		auto retval = (bool)NETWORK::NETWORK_HAVE_ROS_SOCIAL_CLUB_PRIV();
		return retval;
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_HAVE_ROS_BANNED_PRIV(  )
	{
		auto retval = (bool)NETWORK::NETWORK_HAVE_ROS_BANNED_PRIV();
		return retval;
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_HAVE_ROS_CREATE_TICKET_PRIV(  )
	{
		auto retval = (bool)NETWORK::NETWORK_HAVE_ROS_CREATE_TICKET_PRIV();
		return retval;
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_HAVE_ROS_MULTIPLAYER_PRIV(  )
	{
		auto retval = (bool)NETWORK::NETWORK_HAVE_ROS_MULTIPLAYER_PRIV();
		return retval;
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_HAVE_ROS_LEADERBOARD_WRITE_PRIV(  )
	{
		auto retval = (bool)NETWORK::NETWORK_HAVE_ROS_LEADERBOARD_WRITE_PRIV();
		return retval;
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_HAS_ROS_PRIVILEGE( int index )
	{
		auto retval = (bool)NETWORK::NETWORK_HAS_ROS_PRIVILEGE(index);
		return retval;
	}

	static std::tuple<bool, int, Any> LUA_NATIVE_NETWORK_NETWORK_HAS_ROS_PRIVILEGE_END_DATE( int privilege, int banType, Any timeData )
	{
		std::tuple<bool, int, Any> return_values;
		std::get<0>(return_values) = (bool)NETWORK::NETWORK_HAS_ROS_PRIVILEGE_END_DATE(privilege, &banType, &timeData);
		std::get<1>(return_values) = banType;
		std::get<2>(return_values) = timeData;

		return return_values;
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_HAS_ROS_PRIVILEGE_PLAYED_LAST_GEN(  )
	{
		auto retval = (bool)NETWORK::NETWORK_HAS_ROS_PRIVILEGE_PLAYED_LAST_GEN();
		return retval;
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_HAS_ROS_PRIVILEGE_SPECIAL_EDITION_CONTENT(  )
	{
		auto retval = (bool)NETWORK::NETWORK_HAS_ROS_PRIVILEGE_SPECIAL_EDITION_CONTENT();
		return retval;
	}

	static int LUA_NATIVE_NETWORK_NETWORK_START_COMMUNICATION_PERMISSIONS_CHECK( Any p0 )
	{
		auto retval = NETWORK::NETWORK_START_COMMUNICATION_PERMISSIONS_CHECK(p0);
		return retval;
	}

	static std::tuple<int, Any> LUA_NATIVE_NETWORK_NETWORK_START_USER_CONTENT_PERMISSIONS_CHECK( Any netHandle )
	{
		std::tuple<int, Any> return_values;
		std::get<0>(return_values) = NETWORK::NETWORK_START_USER_CONTENT_PERMISSIONS_CHECK(&netHandle);
		std::get<1>(return_values) = netHandle;

		return return_values;
	}

	static void LUA_NATIVE_NETWORK_NETWORK_SKIP_RADIO_RESET_NEXT_CLOSE(  )
	{
		NETWORK::NETWORK_SKIP_RADIO_RESET_NEXT_CLOSE();
	}

	static void LUA_NATIVE_NETWORK_NETWORK_SKIP_RADIO_RESET_NEXT_OPEN(  )
	{
		NETWORK::NETWORK_SKIP_RADIO_RESET_NEXT_OPEN();
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_SKIP_RADIO_WARNING(  )
	{
		auto retval = (bool)NETWORK::NETWORK_SKIP_RADIO_WARNING();
		return retval;
	}

	static void LUA_NATIVE_NETWORK_NETWORK_FORCE_LOCAL_PLAYER_SCAR_SYNC(  )
	{
		NETWORK::NETWORK_FORCE_LOCAL_PLAYER_SCAR_SYNC();
	}

	static void LUA_NATIVE_NETWORK_NETWORK_DISABLE_LEAVE_REMOTE_PED_BEHIND( bool toggle )
	{
		NETWORK::NETWORK_DISABLE_LEAVE_REMOTE_PED_BEHIND(toggle);
	}

	static void LUA_NATIVE_NETWORK_NETWORK_ALLOW_REMOTE_ATTACHMENT_MODIFICATION( Entity entity, bool toggle )
	{
		NETWORK::NETWORK_ALLOW_REMOTE_ATTACHMENT_MODIFICATION(entity, toggle);
	}

	static void LUA_NATIVE_NETWORK_NETWORK_SHOW_CHAT_RESTRICTION_MSC( Player player )
	{
		NETWORK::NETWORK_SHOW_CHAT_RESTRICTION_MSC(player);
	}

	static void LUA_NATIVE_NETWORK_NETWORK_SHOW_PSN_UGC_RESTRICTION(  )
	{
		NETWORK::NETWORK_SHOW_PSN_UGC_RESTRICTION();
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_IS_TITLE_UPDATE_REQUIRED(  )
	{
		auto retval = (bool)NETWORK::NETWORK_IS_TITLE_UPDATE_REQUIRED();
		return retval;
	}

	static void LUA_NATIVE_NETWORK_NETWORK_QUIT_MP_TO_DESKTOP(  )
	{
		NETWORK::NETWORK_QUIT_MP_TO_DESKTOP();
	}

	static bool LUA_NATIVE_NETWORK_NETWORK_IS_CONNECTED_VIA_RELAY( Player player )
	{
		auto retval = (bool)NETWORK::NETWORK_IS_CONNECTED_VIA_RELAY(player);
		return retval;
	}

	static float LUA_NATIVE_NETWORK_NETWORK_GET_AVERAGE_LATENCY( Player player )
	{
		auto retval = NETWORK::NETWORK_GET_AVERAGE_LATENCY(player);
		return retval;
	}

	static float LUA_NATIVE_NETWORK_NETWORK_GET_AVERAGE_PING( Player player )
	{
		auto retval = NETWORK::NETWORK_GET_AVERAGE_PING(player);
		return retval;
	}

	static float LUA_NATIVE_NETWORK_NETWORK_GET_AVERAGE_PACKET_LOSS( Player player )
	{
		auto retval = NETWORK::NETWORK_GET_AVERAGE_PACKET_LOSS(player);
		return retval;
	}

	static int LUA_NATIVE_NETWORK_NETWORK_GET_NUM_UNACKED_RELIABLES( Player player )
	{
		auto retval = NETWORK::NETWORK_GET_NUM_UNACKED_RELIABLES(player);
		return retval;
	}

	static int LUA_NATIVE_NETWORK_NETWORK_GET_UNRELIABLE_RESEND_COUNT( Player player )
	{
		auto retval = NETWORK::NETWORK_GET_UNRELIABLE_RESEND_COUNT(player);
		return retval;
	}

	static int LUA_NATIVE_NETWORK_NETWORK_GET_HIGHEST_RELIABLE_RESEND_COUNT( Player player )
	{
		auto retval = NETWORK::NETWORK_GET_HIGHEST_RELIABLE_RESEND_COUNT(player);
		return retval;
	}

	static void LUA_NATIVE_NETWORK_NETWORK_REPORT_CODE_TAMPER(  )
	{
		NETWORK::NETWORK_REPORT_CODE_TAMPER();
	}

	static Vector3 LUA_NATIVE_NETWORK_NETWORK_GET_LAST_ENTITY_POS_RECEIVED_OVER_NETWORK( Entity entity )
	{
		auto retval = NETWORK::NETWORK_GET_LAST_ENTITY_POS_RECEIVED_OVER_NETWORK(entity);
		return retval;
	}

	static Vector3 LUA_NATIVE_NETWORK_NETWORK_GET_LAST_PLAYER_POS_RECEIVED_OVER_NETWORK( Player player )
	{
		auto retval = NETWORK::NETWORK_GET_LAST_PLAYER_POS_RECEIVED_OVER_NETWORK(player);
		return retval;
	}

	static Vector3 LUA_NATIVE_NETWORK_NETWORK_GET_LAST_VEL_RECEIVED_OVER_NETWORK( Entity entity )
	{
		auto retval = NETWORK::NETWORK_GET_LAST_VEL_RECEIVED_OVER_NETWORK(entity);
		return retval;
	}

	static Vector3 LUA_NATIVE_NETWORK_NETWORK_GET_PREDICTED_VELOCITY( Entity entity )
	{
		auto retval = NETWORK::NETWORK_GET_PREDICTED_VELOCITY(entity);
		return retval;
	}

	static void LUA_NATIVE_NETWORK_NETWORK_DUMP_NET_IF_CONFIG(  )
	{
		NETWORK::NETWORK_DUMP_NET_IF_CONFIG();
	}

	static Any LUA_NATIVE_NETWORK_NETWORK_GET_SIGNALLING_INFO( Any p0 )
	{
		NETWORK::NETWORK_GET_SIGNALLING_INFO(&p0);
		return p0;
	}

	static Any LUA_NATIVE_NETWORK_NETWORK_GET_NET_STATISTICS_INFO( Any p0 )
	{
		NETWORK::NETWORK_GET_NET_STATISTICS_INFO(&p0);
		return p0;
	}

	static int LUA_NATIVE_NETWORK_NETWORK_GET_PLAYER_ACCOUNT_ID( Player player )
	{
		auto retval = NETWORK::NETWORK_GET_PLAYER_ACCOUNT_ID(player);
		return retval;
	}

	static void LUA_NATIVE_NETWORK_NETWORK_UGC_NAV( Any p0, Any p1 )
	{
		NETWORK::NETWORK_UGC_NAV(p0, p1);
	}

	void init_native_binding_NETWORK(sol::state& L)
	{
		auto NETWORK = L["NETWORK"].get_or_create<sol::table>();
		NETWORK.set_function("GET_ONLINE_VERSION", LUA_NATIVE_NETWORK_GET_ONLINE_VERSION);
		NETWORK.set_function("NETWORK_IS_SIGNED_IN", LUA_NATIVE_NETWORK_NETWORK_IS_SIGNED_IN);
		NETWORK.set_function("NETWORK_IS_SIGNED_ONLINE", LUA_NATIVE_NETWORK_NETWORK_IS_SIGNED_ONLINE);
		NETWORK.set_function("NETWORK_IS_NP_AVAILABLE", LUA_NATIVE_NETWORK_NETWORK_IS_NP_AVAILABLE);
		NETWORK.set_function("NETWORK_IS_NP_PENDING", LUA_NATIVE_NETWORK_NETWORK_IS_NP_PENDING);
		NETWORK.set_function("NETWORK_GET_NP_UNAVAILABLE_REASON", LUA_NATIVE_NETWORK_NETWORK_GET_NP_UNAVAILABLE_REASON);
		NETWORK.set_function("NETWORK_IS_CONNETED_TO_NP_PRESENCE", LUA_NATIVE_NETWORK_NETWORK_IS_CONNETED_TO_NP_PRESENCE);
		NETWORK.set_function("NETWORK_IS_LOGGED_IN_TO_PSN", LUA_NATIVE_NETWORK_NETWORK_IS_LOGGED_IN_TO_PSN);
		NETWORK.set_function("NETWORK_HAS_VALID_ROS_CREDENTIALS", LUA_NATIVE_NETWORK_NETWORK_HAS_VALID_ROS_CREDENTIALS);
		NETWORK.set_function("NETWORK_IS_REFRESHING_ROS_CREDENTIALS", LUA_NATIVE_NETWORK_NETWORK_IS_REFRESHING_ROS_CREDENTIALS);
		NETWORK.set_function("NETWORK_IS_CLOUD_AVAILABLE", LUA_NATIVE_NETWORK_NETWORK_IS_CLOUD_AVAILABLE);
		NETWORK.set_function("NETWORK_HAS_SOCIAL_CLUB_ACCOUNT", LUA_NATIVE_NETWORK_NETWORK_HAS_SOCIAL_CLUB_ACCOUNT);
		NETWORK.set_function("NETWORK_ARE_SOCIAL_CLUB_POLICIES_CURRENT", LUA_NATIVE_NETWORK_NETWORK_ARE_SOCIAL_CLUB_POLICIES_CURRENT);
		NETWORK.set_function("NETWORK_IS_HOST", LUA_NATIVE_NETWORK_NETWORK_IS_HOST);
		NETWORK.set_function("NETWORK_GET_HOST_PLAYER_INDEX", LUA_NATIVE_NETWORK_NETWORK_GET_HOST_PLAYER_INDEX);
		NETWORK.set_function("NETWORK_WAS_GAME_SUSPENDED", LUA_NATIVE_NETWORK_NETWORK_WAS_GAME_SUSPENDED);
		NETWORK.set_function("NETWORK_HAVE_ONLINE_PRIVILEGES", LUA_NATIVE_NETWORK_NETWORK_HAVE_ONLINE_PRIVILEGES);
		NETWORK.set_function("NETWORK_HAS_AGE_RESTRICTIONS", LUA_NATIVE_NETWORK_NETWORK_HAS_AGE_RESTRICTIONS);
		NETWORK.set_function("NETWORK_HAVE_USER_CONTENT_PRIVILEGES", LUA_NATIVE_NETWORK_NETWORK_HAVE_USER_CONTENT_PRIVILEGES);
		NETWORK.set_function("NETWORK_HAVE_COMMUNICATION_PRIVILEGES", LUA_NATIVE_NETWORK_NETWORK_HAVE_COMMUNICATION_PRIVILEGES);
		NETWORK.set_function("NETWORK_CHECK_ONLINE_PRIVILEGES", LUA_NATIVE_NETWORK_NETWORK_CHECK_ONLINE_PRIVILEGES);
		NETWORK.set_function("NETWORK_CHECK_USER_CONTENT_PRIVILEGES", LUA_NATIVE_NETWORK_NETWORK_CHECK_USER_CONTENT_PRIVILEGES);
		NETWORK.set_function("NETWORK_CHECK_COMMUNICATION_PRIVILEGES", LUA_NATIVE_NETWORK_NETWORK_CHECK_COMMUNICATION_PRIVILEGES);
		NETWORK.set_function("NETWORK_CHECK_TEXT_COMMUNICATION_PRIVILEGES", LUA_NATIVE_NETWORK_NETWORK_CHECK_TEXT_COMMUNICATION_PRIVILEGES);
		NETWORK.set_function("NETWORK_IS_USING_ONLINE_PROMOTION", LUA_NATIVE_NETWORK_NETWORK_IS_USING_ONLINE_PROMOTION);
		NETWORK.set_function("NETWORK_SHOULD_SHOW_PROMOTION_ALERT_SCREEN", LUA_NATIVE_NETWORK_NETWORK_SHOULD_SHOW_PROMOTION_ALERT_SCREEN);
		NETWORK.set_function("NETWORK_HAS_SOCIAL_NETWORKING_SHARING_PRIV", LUA_NATIVE_NETWORK_NETWORK_HAS_SOCIAL_NETWORKING_SHARING_PRIV);
		NETWORK.set_function("NETWORK_GET_AGE_GROUP", LUA_NATIVE_NETWORK_NETWORK_GET_AGE_GROUP);
		NETWORK.set_function("NETWORK_CHECK_PRIVILEGES", LUA_NATIVE_NETWORK_NETWORK_CHECK_PRIVILEGES);
		NETWORK.set_function("NETWORK_IS_PRIVILEGE_CHECK_IN_PROGRESS", LUA_NATIVE_NETWORK_NETWORK_IS_PRIVILEGE_CHECK_IN_PROGRESS);
		NETWORK.set_function("NETWORK_SET_PRIVILEGE_CHECK_RESULT_NOT_NEEDED", LUA_NATIVE_NETWORK_NETWORK_SET_PRIVILEGE_CHECK_RESULT_NOT_NEEDED);
		NETWORK.set_function("NETWORK_RESOLVE_PRIVILEGE_USER_CONTENT", LUA_NATIVE_NETWORK_NETWORK_RESOLVE_PRIVILEGE_USER_CONTENT);
		NETWORK.set_function("NETWORK_HAVE_PLATFORM_SUBSCRIPTION", LUA_NATIVE_NETWORK_NETWORK_HAVE_PLATFORM_SUBSCRIPTION);
		NETWORK.set_function("NETWORK_IS_PLATFORM_SUBSCRIPTION_CHECK_PENDING", LUA_NATIVE_NETWORK_NETWORK_IS_PLATFORM_SUBSCRIPTION_CHECK_PENDING);
		NETWORK.set_function("NETWORK_SHOW_ACCOUNT_UPGRADE_UI", LUA_NATIVE_NETWORK_NETWORK_SHOW_ACCOUNT_UPGRADE_UI);
		NETWORK.set_function("NETWORK_IS_SHOWING_SYSTEM_UI_OR_RECENTLY_REQUESTED_UPSELL", LUA_NATIVE_NETWORK_NETWORK_IS_SHOWING_SYSTEM_UI_OR_RECENTLY_REQUESTED_UPSELL);
		NETWORK.set_function("NETWORK_NEED_TO_START_NEW_GAME_BUT_BLOCKED", LUA_NATIVE_NETWORK_NETWORK_NEED_TO_START_NEW_GAME_BUT_BLOCKED);
		NETWORK.set_function("NETWORK_CAN_BAIL", LUA_NATIVE_NETWORK_NETWORK_CAN_BAIL);
		NETWORK.set_function("NETWORK_BAIL", LUA_NATIVE_NETWORK_NETWORK_BAIL);
		NETWORK.set_function("NETWORK_ON_RETURN_TO_SINGLE_PLAYER", LUA_NATIVE_NETWORK_NETWORK_ON_RETURN_TO_SINGLE_PLAYER);
		NETWORK.set_function("NETWORK_TRANSITION_START", LUA_NATIVE_NETWORK_NETWORK_TRANSITION_START);
		NETWORK.set_function("NETWORK_TRANSITION_ADD_STAGE", LUA_NATIVE_NETWORK_NETWORK_TRANSITION_ADD_STAGE);
		NETWORK.set_function("NETWORK_TRANSITION_FINISH", LUA_NATIVE_NETWORK_NETWORK_TRANSITION_FINISH);
		NETWORK.set_function("NETWORK_CAN_ACCESS_MULTIPLAYER", LUA_NATIVE_NETWORK_NETWORK_CAN_ACCESS_MULTIPLAYER);
		NETWORK.set_function("NETWORK_IS_MULTIPLAYER_DISABLED", LUA_NATIVE_NETWORK_NETWORK_IS_MULTIPLAYER_DISABLED);
		NETWORK.set_function("NETWORK_CAN_ENTER_MULTIPLAYER", LUA_NATIVE_NETWORK_NETWORK_CAN_ENTER_MULTIPLAYER);
		NETWORK.set_function("NETWORK_SESSION_DO_FREEROAM_QUICKMATCH", LUA_NATIVE_NETWORK_NETWORK_SESSION_DO_FREEROAM_QUICKMATCH);
		NETWORK.set_function("NETWORK_SESSION_DO_FRIEND_MATCHMAKING", LUA_NATIVE_NETWORK_NETWORK_SESSION_DO_FRIEND_MATCHMAKING);
		NETWORK.set_function("NETWORK_SESSION_DO_CREW_MATCHMAKING", LUA_NATIVE_NETWORK_NETWORK_SESSION_DO_CREW_MATCHMAKING);
		NETWORK.set_function("NETWORK_SESSION_DO_ACTIVITY_QUICKMATCH", LUA_NATIVE_NETWORK_NETWORK_SESSION_DO_ACTIVITY_QUICKMATCH);
		NETWORK.set_function("NETWORK_SESSION_HOST", LUA_NATIVE_NETWORK_NETWORK_SESSION_HOST);
		NETWORK.set_function("NETWORK_SESSION_HOST_CLOSED", LUA_NATIVE_NETWORK_NETWORK_SESSION_HOST_CLOSED);
		NETWORK.set_function("NETWORK_SESSION_HOST_FRIENDS_ONLY", LUA_NATIVE_NETWORK_NETWORK_SESSION_HOST_FRIENDS_ONLY);
		NETWORK.set_function("NETWORK_SESSION_IS_CLOSED_FRIENDS", LUA_NATIVE_NETWORK_NETWORK_SESSION_IS_CLOSED_FRIENDS);
		NETWORK.set_function("NETWORK_SESSION_IS_CLOSED_CREW", LUA_NATIVE_NETWORK_NETWORK_SESSION_IS_CLOSED_CREW);
		NETWORK.set_function("NETWORK_SESSION_IS_SOLO", LUA_NATIVE_NETWORK_NETWORK_SESSION_IS_SOLO);
		NETWORK.set_function("NETWORK_SESSION_IS_PRIVATE", LUA_NATIVE_NETWORK_NETWORK_SESSION_IS_PRIVATE);
		NETWORK.set_function("NETWORK_SESSION_END", LUA_NATIVE_NETWORK_NETWORK_SESSION_END);
		NETWORK.set_function("NETWORK_SESSION_LEAVE", LUA_NATIVE_NETWORK_NETWORK_SESSION_LEAVE);
		NETWORK.set_function("NETWORK_SESSION_KICK_PLAYER", LUA_NATIVE_NETWORK_NETWORK_SESSION_KICK_PLAYER);
		NETWORK.set_function("NETWORK_SESSION_GET_KICK_VOTE", LUA_NATIVE_NETWORK_NETWORK_SESSION_GET_KICK_VOTE);
		NETWORK.set_function("NETWORK_SESSION_RESERVE_SLOTS_TRANSITION", LUA_NATIVE_NETWORK_NETWORK_SESSION_RESERVE_SLOTS_TRANSITION);
		NETWORK.set_function("NETWORK_JOIN_PREVIOUSLY_FAILED_SESSION", LUA_NATIVE_NETWORK_NETWORK_JOIN_PREVIOUSLY_FAILED_SESSION);
		NETWORK.set_function("NETWORK_JOIN_PREVIOUSLY_FAILED_TRANSITION", LUA_NATIVE_NETWORK_NETWORK_JOIN_PREVIOUSLY_FAILED_TRANSITION);
		NETWORK.set_function("NETWORK_SESSION_SET_MATCHMAKING_GROUP", LUA_NATIVE_NETWORK_NETWORK_SESSION_SET_MATCHMAKING_GROUP);
		NETWORK.set_function("NETWORK_SESSION_SET_MATCHMAKING_GROUP_MAX", LUA_NATIVE_NETWORK_NETWORK_SESSION_SET_MATCHMAKING_GROUP_MAX);
		NETWORK.set_function("NETWORK_SESSION_GET_MATCHMAKING_GROUP_FREE", LUA_NATIVE_NETWORK_NETWORK_SESSION_GET_MATCHMAKING_GROUP_FREE);
		NETWORK.set_function("NETWORK_SESSION_ADD_ACTIVE_MATCHMAKING_GROUP", LUA_NATIVE_NETWORK_NETWORK_SESSION_ADD_ACTIVE_MATCHMAKING_GROUP);
		NETWORK.set_function("NETWORK_SESSION_SET_UNIQUE_CREW_LIMIT", LUA_NATIVE_NETWORK_NETWORK_SESSION_SET_UNIQUE_CREW_LIMIT);
		NETWORK.set_function("NETWORK_SESSION_SET_UNIQUE_CREW_LIMIT_TRANSITION", LUA_NATIVE_NETWORK_NETWORK_SESSION_SET_UNIQUE_CREW_LIMIT_TRANSITION);
		NETWORK.set_function("NETWORK_SESSION_SET_UNIQUE_CREW_ONLY_CREWS_TRANSITION", LUA_NATIVE_NETWORK_NETWORK_SESSION_SET_UNIQUE_CREW_ONLY_CREWS_TRANSITION);
		NETWORK.set_function("NETWORK_SESSION_SET_CREW_LIMIT_MAX_MEMBERS_TRANSITION", LUA_NATIVE_NETWORK_NETWORK_SESSION_SET_CREW_LIMIT_MAX_MEMBERS_TRANSITION);
		NETWORK.set_function("NETWORK_SESSION_SET_MATCHMAKING_PROPERTY_ID", LUA_NATIVE_NETWORK_NETWORK_SESSION_SET_MATCHMAKING_PROPERTY_ID);
		NETWORK.set_function("NETWORK_SESSION_SET_MATCHMAKING_MENTAL_STATE", LUA_NATIVE_NETWORK_NETWORK_SESSION_SET_MATCHMAKING_MENTAL_STATE);
		NETWORK.set_function("NETWORK_SESSION_SET_NUM_BOSSES", LUA_NATIVE_NETWORK_NETWORK_SESSION_SET_NUM_BOSSES);
		NETWORK.set_function("NETWORK_SESSION_SET_SCRIPT_VALIDATE_JOIN", LUA_NATIVE_NETWORK_NETWORK_SESSION_SET_SCRIPT_VALIDATE_JOIN);
		NETWORK.set_function("NETWORK_SESSION_VALIDATE_JOIN", LUA_NATIVE_NETWORK_NETWORK_SESSION_VALIDATE_JOIN);
		NETWORK.set_function("NETWORK_ADD_FOLLOWERS", LUA_NATIVE_NETWORK_NETWORK_ADD_FOLLOWERS);
		NETWORK.set_function("NETWORK_CLEAR_FOLLOWERS", LUA_NATIVE_NETWORK_NETWORK_CLEAR_FOLLOWERS);
		NETWORK.set_function("NETWORK_GET_GLOBAL_MULTIPLAYER_CLOCK", LUA_NATIVE_NETWORK_NETWORK_GET_GLOBAL_MULTIPLAYER_CLOCK);
		NETWORK.set_function("NETWORK_SESSION_SET_GAMEMODE", LUA_NATIVE_NETWORK_NETWORK_SESSION_SET_GAMEMODE);
		NETWORK.set_function("NETWORK_SESSION_GET_HOST_AIM_PREFERENCE", LUA_NATIVE_NETWORK_NETWORK_SESSION_GET_HOST_AIM_PREFERENCE);
		NETWORK.set_function("NETWORK_FIND_GAMERS_IN_CREW", LUA_NATIVE_NETWORK_NETWORK_FIND_GAMERS_IN_CREW);
		NETWORK.set_function("NETWORK_FIND_MATCHED_GAMERS", LUA_NATIVE_NETWORK_NETWORK_FIND_MATCHED_GAMERS);
		NETWORK.set_function("NETWORK_IS_FINDING_GAMERS", LUA_NATIVE_NETWORK_NETWORK_IS_FINDING_GAMERS);
		NETWORK.set_function("NETWORK_DID_FIND_GAMERS_SUCCEED", LUA_NATIVE_NETWORK_NETWORK_DID_FIND_GAMERS_SUCCEED);
		NETWORK.set_function("NETWORK_GET_NUM_FOUND_GAMERS", LUA_NATIVE_NETWORK_NETWORK_GET_NUM_FOUND_GAMERS);
		NETWORK.set_function("NETWORK_GET_FOUND_GAMER", LUA_NATIVE_NETWORK_NETWORK_GET_FOUND_GAMER);
		NETWORK.set_function("NETWORK_CLEAR_FOUND_GAMERS", LUA_NATIVE_NETWORK_NETWORK_CLEAR_FOUND_GAMERS);
		NETWORK.set_function("NETWORK_QUEUE_GAMER_FOR_STATUS", LUA_NATIVE_NETWORK_NETWORK_QUEUE_GAMER_FOR_STATUS);
		NETWORK.set_function("NETWORK_GET_GAMER_STATUS_FROM_QUEUE", LUA_NATIVE_NETWORK_NETWORK_GET_GAMER_STATUS_FROM_QUEUE);
		NETWORK.set_function("NETWORK_IS_GETTING_GAMER_STATUS", LUA_NATIVE_NETWORK_NETWORK_IS_GETTING_GAMER_STATUS);
		NETWORK.set_function("NETWORK_DID_GET_GAMER_STATUS_SUCCEED", LUA_NATIVE_NETWORK_NETWORK_DID_GET_GAMER_STATUS_SUCCEED);
		NETWORK.set_function("NETWORK_GET_GAMER_STATUS_RESULT", LUA_NATIVE_NETWORK_NETWORK_GET_GAMER_STATUS_RESULT);
		NETWORK.set_function("NETWORK_CLEAR_GET_GAMER_STATUS", LUA_NATIVE_NETWORK_NETWORK_CLEAR_GET_GAMER_STATUS);
		NETWORK.set_function("NETWORK_SESSION_JOIN_INVITE", LUA_NATIVE_NETWORK_NETWORK_SESSION_JOIN_INVITE);
		NETWORK.set_function("NETWORK_SESSION_CANCEL_INVITE", LUA_NATIVE_NETWORK_NETWORK_SESSION_CANCEL_INVITE);
		NETWORK.set_function("NETWORK_SESSION_FORCE_CANCEL_INVITE", LUA_NATIVE_NETWORK_NETWORK_SESSION_FORCE_CANCEL_INVITE);
		NETWORK.set_function("NETWORK_HAS_PENDING_INVITE", LUA_NATIVE_NETWORK_NETWORK_HAS_PENDING_INVITE);
		NETWORK.set_function("NETWORK_HAS_CONFIRMED_INVITE", LUA_NATIVE_NETWORK_NETWORK_HAS_CONFIRMED_INVITE);
		NETWORK.set_function("NETWORK_REQUEST_INVITE_CONFIRMED_EVENT", LUA_NATIVE_NETWORK_NETWORK_REQUEST_INVITE_CONFIRMED_EVENT);
		NETWORK.set_function("NETWORK_SESSION_WAS_INVITED", LUA_NATIVE_NETWORK_NETWORK_SESSION_WAS_INVITED);
		NETWORK.set_function("NETWORK_SESSION_GET_INVITER", LUA_NATIVE_NETWORK_NETWORK_SESSION_GET_INVITER);
		NETWORK.set_function("NETWORK_SESSION_IS_AWAITING_INVITE_RESPONSE", LUA_NATIVE_NETWORK_NETWORK_SESSION_IS_AWAITING_INVITE_RESPONSE);
		NETWORK.set_function("NETWORK_SESSION_IS_DISPLAYING_INVITE_CONFIRMATION", LUA_NATIVE_NETWORK_NETWORK_SESSION_IS_DISPLAYING_INVITE_CONFIRMATION);
		NETWORK.set_function("NETWORK_SUPPRESS_INVITE", LUA_NATIVE_NETWORK_NETWORK_SUPPRESS_INVITE);
		NETWORK.set_function("NETWORK_BLOCK_INVITES", LUA_NATIVE_NETWORK_NETWORK_BLOCK_INVITES);
		NETWORK.set_function("NETWORK_BLOCK_JOIN_QUEUE_INVITES", LUA_NATIVE_NETWORK_NETWORK_BLOCK_JOIN_QUEUE_INVITES);
		NETWORK.set_function("NETWORK_SET_CAN_RECEIVE_RS_INVITES", LUA_NATIVE_NETWORK_NETWORK_SET_CAN_RECEIVE_RS_INVITES);
		NETWORK.set_function("NETWORK_STORE_INVITE_THROUGH_RESTART", LUA_NATIVE_NETWORK_NETWORK_STORE_INVITE_THROUGH_RESTART);
		NETWORK.set_function("NETWORK_ALLOW_INVITE_PROCESS_IN_PLAYER_SWITCH", LUA_NATIVE_NETWORK_NETWORK_ALLOW_INVITE_PROCESS_IN_PLAYER_SWITCH);
		NETWORK.set_function("NETWORK_SET_SCRIPT_READY_FOR_EVENTS", LUA_NATIVE_NETWORK_NETWORK_SET_SCRIPT_READY_FOR_EVENTS);
		NETWORK.set_function("NETWORK_IS_OFFLINE_INVITE_PENDING", LUA_NATIVE_NETWORK_NETWORK_IS_OFFLINE_INVITE_PENDING);
		NETWORK.set_function("NETWORK_CLEAR_OFFLINE_INVITE_PENDING", LUA_NATIVE_NETWORK_NETWORK_CLEAR_OFFLINE_INVITE_PENDING);
		NETWORK.set_function("NETWORK_SESSION_HOST_SINGLE_PLAYER", LUA_NATIVE_NETWORK_NETWORK_SESSION_HOST_SINGLE_PLAYER);
		NETWORK.set_function("NETWORK_SESSION_LEAVE_SINGLE_PLAYER", LUA_NATIVE_NETWORK_NETWORK_SESSION_LEAVE_SINGLE_PLAYER);
		NETWORK.set_function("NETWORK_IS_GAME_IN_PROGRESS", LUA_NATIVE_NETWORK_NETWORK_IS_GAME_IN_PROGRESS);
		NETWORK.set_function("NETWORK_IS_SESSION_ACTIVE", LUA_NATIVE_NETWORK_NETWORK_IS_SESSION_ACTIVE);
		NETWORK.set_function("NETWORK_IS_IN_SESSION", LUA_NATIVE_NETWORK_NETWORK_IS_IN_SESSION);
		NETWORK.set_function("NETWORK_IS_SESSION_STARTED", LUA_NATIVE_NETWORK_NETWORK_IS_SESSION_STARTED);
		NETWORK.set_function("NETWORK_IS_SESSION_BUSY", LUA_NATIVE_NETWORK_NETWORK_IS_SESSION_BUSY);
		NETWORK.set_function("NETWORK_CAN_SESSION_END", LUA_NATIVE_NETWORK_NETWORK_CAN_SESSION_END);
		NETWORK.set_function("NETWORK_GET_GAME_MODE", LUA_NATIVE_NETWORK_NETWORK_GET_GAME_MODE);
		NETWORK.set_function("NETWORK_SESSION_MARK_VISIBLE", LUA_NATIVE_NETWORK_NETWORK_SESSION_MARK_VISIBLE);
		NETWORK.set_function("NETWORK_SESSION_IS_VISIBLE", LUA_NATIVE_NETWORK_NETWORK_SESSION_IS_VISIBLE);
		NETWORK.set_function("NETWORK_SESSION_BLOCK_JOIN_REQUESTS", LUA_NATIVE_NETWORK_NETWORK_SESSION_BLOCK_JOIN_REQUESTS);
		NETWORK.set_function("NETWORK_SESSION_CHANGE_SLOTS", LUA_NATIVE_NETWORK_NETWORK_SESSION_CHANGE_SLOTS);
		NETWORK.set_function("NETWORK_SESSION_GET_PRIVATE_SLOTS", LUA_NATIVE_NETWORK_NETWORK_SESSION_GET_PRIVATE_SLOTS);
		NETWORK.set_function("NETWORK_SESSION_VOICE_HOST", LUA_NATIVE_NETWORK_NETWORK_SESSION_VOICE_HOST);
		NETWORK.set_function("NETWORK_SESSION_VOICE_LEAVE", LUA_NATIVE_NETWORK_NETWORK_SESSION_VOICE_LEAVE);
		NETWORK.set_function("NETWORK_SESSION_VOICE_CONNECT_TO_PLAYER", LUA_NATIVE_NETWORK_NETWORK_SESSION_VOICE_CONNECT_TO_PLAYER);
		NETWORK.set_function("NETWORK_SESSION_VOICE_RESPOND_TO_REQUEST", LUA_NATIVE_NETWORK_NETWORK_SESSION_VOICE_RESPOND_TO_REQUEST);
		NETWORK.set_function("NETWORK_SESSION_VOICE_SET_TIMEOUT", LUA_NATIVE_NETWORK_NETWORK_SESSION_VOICE_SET_TIMEOUT);
		NETWORK.set_function("NETWORK_SESSION_IS_IN_VOICE_SESSION", LUA_NATIVE_NETWORK_NETWORK_SESSION_IS_IN_VOICE_SESSION);
		NETWORK.set_function("NETWORK_SESSION_IS_VOICE_SESSION_ACTIVE", LUA_NATIVE_NETWORK_NETWORK_SESSION_IS_VOICE_SESSION_ACTIVE);
		NETWORK.set_function("NETWORK_SESSION_IS_VOICE_SESSION_BUSY", LUA_NATIVE_NETWORK_NETWORK_SESSION_IS_VOICE_SESSION_BUSY);
		NETWORK.set_function("NETWORK_SEND_TEXT_MESSAGE", LUA_NATIVE_NETWORK_NETWORK_SEND_TEXT_MESSAGE);
		NETWORK.set_function("NETWORK_SET_ACTIVITY_SPECTATOR", LUA_NATIVE_NETWORK_NETWORK_SET_ACTIVITY_SPECTATOR);
		NETWORK.set_function("NETWORK_IS_ACTIVITY_SPECTATOR", LUA_NATIVE_NETWORK_NETWORK_IS_ACTIVITY_SPECTATOR);
		NETWORK.set_function("NETWORK_SET_ACTIVITY_PLAYER_MAX", LUA_NATIVE_NETWORK_NETWORK_SET_ACTIVITY_PLAYER_MAX);
		NETWORK.set_function("NETWORK_SET_ACTIVITY_SPECTATOR_MAX", LUA_NATIVE_NETWORK_NETWORK_SET_ACTIVITY_SPECTATOR_MAX);
		NETWORK.set_function("NETWORK_GET_ACTIVITY_PLAYER_NUM", LUA_NATIVE_NETWORK_NETWORK_GET_ACTIVITY_PLAYER_NUM);
		NETWORK.set_function("NETWORK_IS_ACTIVITY_SPECTATOR_FROM_HANDLE", LUA_NATIVE_NETWORK_NETWORK_IS_ACTIVITY_SPECTATOR_FROM_HANDLE);
		NETWORK.set_function("NETWORK_HOST_TRANSITION", LUA_NATIVE_NETWORK_NETWORK_HOST_TRANSITION);
		NETWORK.set_function("NETWORK_DO_TRANSITION_QUICKMATCH", LUA_NATIVE_NETWORK_NETWORK_DO_TRANSITION_QUICKMATCH);
		NETWORK.set_function("NETWORK_DO_TRANSITION_QUICKMATCH_ASYNC", LUA_NATIVE_NETWORK_NETWORK_DO_TRANSITION_QUICKMATCH_ASYNC);
		NETWORK.set_function("NETWORK_DO_TRANSITION_QUICKMATCH_WITH_GROUP", LUA_NATIVE_NETWORK_NETWORK_DO_TRANSITION_QUICKMATCH_WITH_GROUP);
		NETWORK.set_function("NETWORK_JOIN_GROUP_ACTIVITY", LUA_NATIVE_NETWORK_NETWORK_JOIN_GROUP_ACTIVITY);
		NETWORK.set_function("NETWORK_CLEAR_GROUP_ACTIVITY", LUA_NATIVE_NETWORK_NETWORK_CLEAR_GROUP_ACTIVITY);
		NETWORK.set_function("NETWORK_RETAIN_ACTIVITY_GROUP", LUA_NATIVE_NETWORK_NETWORK_RETAIN_ACTIVITY_GROUP);
		NETWORK.set_function("NETWORK_IS_TRANSITION_CLOSED_FRIENDS", LUA_NATIVE_NETWORK_NETWORK_IS_TRANSITION_CLOSED_FRIENDS);
		NETWORK.set_function("NETWORK_IS_TRANSITION_CLOSED_CREW", LUA_NATIVE_NETWORK_NETWORK_IS_TRANSITION_CLOSED_CREW);
		NETWORK.set_function("NETWORK_IS_TRANSITION_SOLO", LUA_NATIVE_NETWORK_NETWORK_IS_TRANSITION_SOLO);
		NETWORK.set_function("NETWORK_IS_TRANSITION_PRIVATE", LUA_NATIVE_NETWORK_NETWORK_IS_TRANSITION_PRIVATE);
		NETWORK.set_function("NETWORK_GET_NUM_TRANSITION_NON_ASYNC_GAMERS", LUA_NATIVE_NETWORK_NETWORK_GET_NUM_TRANSITION_NON_ASYNC_GAMERS);
		NETWORK.set_function("NETWORK_MARK_AS_PREFERRED_ACTIVITY", LUA_NATIVE_NETWORK_NETWORK_MARK_AS_PREFERRED_ACTIVITY);
		NETWORK.set_function("NETWORK_MARK_AS_WAITING_ASYNC", LUA_NATIVE_NETWORK_NETWORK_MARK_AS_WAITING_ASYNC);
		NETWORK.set_function("NETWORK_SET_IN_PROGRESS_FINISH_TIME", LUA_NATIVE_NETWORK_NETWORK_SET_IN_PROGRESS_FINISH_TIME);
		NETWORK.set_function("NETWORK_SET_TRANSITION_CREATOR_HANDLE", LUA_NATIVE_NETWORK_NETWORK_SET_TRANSITION_CREATOR_HANDLE);
		NETWORK.set_function("NETWORK_CLEAR_TRANSITION_CREATOR_HANDLE", LUA_NATIVE_NETWORK_NETWORK_CLEAR_TRANSITION_CREATOR_HANDLE);
		NETWORK.set_function("NETWORK_INVITE_GAMERS_TO_TRANSITION", LUA_NATIVE_NETWORK_NETWORK_INVITE_GAMERS_TO_TRANSITION);
		NETWORK.set_function("NETWORK_SET_GAMER_INVITED_TO_TRANSITION", LUA_NATIVE_NETWORK_NETWORK_SET_GAMER_INVITED_TO_TRANSITION);
		NETWORK.set_function("NETWORK_LEAVE_TRANSITION", LUA_NATIVE_NETWORK_NETWORK_LEAVE_TRANSITION);
		NETWORK.set_function("NETWORK_LAUNCH_TRANSITION", LUA_NATIVE_NETWORK_NETWORK_LAUNCH_TRANSITION);
		NETWORK.set_function("NETWORK_SET_DO_NOT_LAUNCH_FROM_JOIN_AS_MIGRATED_HOST", LUA_NATIVE_NETWORK_NETWORK_SET_DO_NOT_LAUNCH_FROM_JOIN_AS_MIGRATED_HOST);
		NETWORK.set_function("NETWORK_CANCEL_TRANSITION_MATCHMAKING", LUA_NATIVE_NETWORK_NETWORK_CANCEL_TRANSITION_MATCHMAKING);
		NETWORK.set_function("NETWORK_BAIL_TRANSITION", LUA_NATIVE_NETWORK_NETWORK_BAIL_TRANSITION);
		NETWORK.set_function("NETWORK_DO_TRANSITION_TO_GAME", LUA_NATIVE_NETWORK_NETWORK_DO_TRANSITION_TO_GAME);
		NETWORK.set_function("NETWORK_DO_TRANSITION_TO_NEW_GAME", LUA_NATIVE_NETWORK_NETWORK_DO_TRANSITION_TO_NEW_GAME);
		NETWORK.set_function("NETWORK_DO_TRANSITION_TO_FREEMODE", LUA_NATIVE_NETWORK_NETWORK_DO_TRANSITION_TO_FREEMODE);
		NETWORK.set_function("NETWORK_DO_TRANSITION_TO_NEW_FREEMODE", LUA_NATIVE_NETWORK_NETWORK_DO_TRANSITION_TO_NEW_FREEMODE);
		NETWORK.set_function("NETWORK_IS_TRANSITION_TO_GAME", LUA_NATIVE_NETWORK_NETWORK_IS_TRANSITION_TO_GAME);
		NETWORK.set_function("NETWORK_GET_TRANSITION_MEMBERS", LUA_NATIVE_NETWORK_NETWORK_GET_TRANSITION_MEMBERS);
		NETWORK.set_function("NETWORK_APPLY_TRANSITION_PARAMETER", LUA_NATIVE_NETWORK_NETWORK_APPLY_TRANSITION_PARAMETER);
		NETWORK.set_function("NETWORK_APPLY_TRANSITION_PARAMETER_STRING", LUA_NATIVE_NETWORK_NETWORK_APPLY_TRANSITION_PARAMETER_STRING);
		NETWORK.set_function("NETWORK_SEND_TRANSITION_GAMER_INSTRUCTION", LUA_NATIVE_NETWORK_NETWORK_SEND_TRANSITION_GAMER_INSTRUCTION);
		NETWORK.set_function("NETWORK_MARK_TRANSITION_GAMER_AS_FULLY_JOINED", LUA_NATIVE_NETWORK_NETWORK_MARK_TRANSITION_GAMER_AS_FULLY_JOINED);
		NETWORK.set_function("NETWORK_IS_TRANSITION_HOST", LUA_NATIVE_NETWORK_NETWORK_IS_TRANSITION_HOST);
		NETWORK.set_function("NETWORK_IS_TRANSITION_HOST_FROM_HANDLE", LUA_NATIVE_NETWORK_NETWORK_IS_TRANSITION_HOST_FROM_HANDLE);
		NETWORK.set_function("NETWORK_GET_TRANSITION_HOST", LUA_NATIVE_NETWORK_NETWORK_GET_TRANSITION_HOST);
		NETWORK.set_function("NETWORK_IS_IN_TRANSITION", LUA_NATIVE_NETWORK_NETWORK_IS_IN_TRANSITION);
		NETWORK.set_function("NETWORK_IS_TRANSITION_STARTED", LUA_NATIVE_NETWORK_NETWORK_IS_TRANSITION_STARTED);
		NETWORK.set_function("NETWORK_IS_TRANSITION_BUSY", LUA_NATIVE_NETWORK_NETWORK_IS_TRANSITION_BUSY);
		NETWORK.set_function("NETWORK_IS_TRANSITION_MATCHMAKING", LUA_NATIVE_NETWORK_NETWORK_IS_TRANSITION_MATCHMAKING);
		NETWORK.set_function("NETWORK_IS_TRANSITION_LEAVE_POSTPONED", LUA_NATIVE_NETWORK_NETWORK_IS_TRANSITION_LEAVE_POSTPONED);
		NETWORK.set_function("NETWORK_TRANSITION_SET_IN_PROGRESS", LUA_NATIVE_NETWORK_NETWORK_TRANSITION_SET_IN_PROGRESS);
		NETWORK.set_function("NETWORK_TRANSITION_SET_CONTENT_CREATOR", LUA_NATIVE_NETWORK_NETWORK_TRANSITION_SET_CONTENT_CREATOR);
		NETWORK.set_function("NETWORK_TRANSITION_SET_ACTIVITY_ISLAND", LUA_NATIVE_NETWORK_NETWORK_TRANSITION_SET_ACTIVITY_ISLAND);
		NETWORK.set_function("NETWORK_OPEN_TRANSITION_MATCHMAKING", LUA_NATIVE_NETWORK_NETWORK_OPEN_TRANSITION_MATCHMAKING);
		NETWORK.set_function("NETWORK_CLOSE_TRANSITION_MATCHMAKING", LUA_NATIVE_NETWORK_NETWORK_CLOSE_TRANSITION_MATCHMAKING);
		NETWORK.set_function("NETWORK_IS_TRANSITION_OPEN_TO_MATCHMAKING", LUA_NATIVE_NETWORK_NETWORK_IS_TRANSITION_OPEN_TO_MATCHMAKING);
		NETWORK.set_function("NETWORK_SET_TRANSITION_VISIBILITY_LOCK", LUA_NATIVE_NETWORK_NETWORK_SET_TRANSITION_VISIBILITY_LOCK);
		NETWORK.set_function("NETWORK_IS_TRANSITION_VISIBILITY_LOCKED", LUA_NATIVE_NETWORK_NETWORK_IS_TRANSITION_VISIBILITY_LOCKED);
		NETWORK.set_function("NETWORK_SET_TRANSITION_ACTIVITY_ID", LUA_NATIVE_NETWORK_NETWORK_SET_TRANSITION_ACTIVITY_ID);
		NETWORK.set_function("NETWORK_CHANGE_TRANSITION_SLOTS", LUA_NATIVE_NETWORK_NETWORK_CHANGE_TRANSITION_SLOTS);
		NETWORK.set_function("NETWORK_TRANSITION_BLOCK_JOIN_REQUESTS", LUA_NATIVE_NETWORK_NETWORK_TRANSITION_BLOCK_JOIN_REQUESTS);
		NETWORK.set_function("NETWORK_HAS_PLAYER_STARTED_TRANSITION", LUA_NATIVE_NETWORK_NETWORK_HAS_PLAYER_STARTED_TRANSITION);
		NETWORK.set_function("NETWORK_ARE_TRANSITION_DETAILS_VALID", LUA_NATIVE_NETWORK_NETWORK_ARE_TRANSITION_DETAILS_VALID);
		NETWORK.set_function("NETWORK_JOIN_TRANSITION", LUA_NATIVE_NETWORK_NETWORK_JOIN_TRANSITION);
		NETWORK.set_function("NETWORK_HAS_INVITED_GAMER_TO_TRANSITION", LUA_NATIVE_NETWORK_NETWORK_HAS_INVITED_GAMER_TO_TRANSITION);
		NETWORK.set_function("NETWORK_HAS_TRANSITION_INVITE_BEEN_ACKED", LUA_NATIVE_NETWORK_NETWORK_HAS_TRANSITION_INVITE_BEEN_ACKED);
		NETWORK.set_function("NETWORK_IS_ACTIVITY_SESSION", LUA_NATIVE_NETWORK_NETWORK_IS_ACTIVITY_SESSION);
		NETWORK.set_function("NETWORK_DISABLE_REALTIME_MULTIPLAYER", LUA_NATIVE_NETWORK_NETWORK_DISABLE_REALTIME_MULTIPLAYER);
		NETWORK.set_function("NETWORK_SET_PRESENCE_SESSION_INVITES_BLOCKED", LUA_NATIVE_NETWORK_NETWORK_SET_PRESENCE_SESSION_INVITES_BLOCKED);
		NETWORK.set_function("NETWORK_SEND_INVITE_VIA_PRESENCE", LUA_NATIVE_NETWORK_NETWORK_SEND_INVITE_VIA_PRESENCE);
		NETWORK.set_function("NETWORK_SEND_TRANSITION_INVITE_VIA_PRESENCE", LUA_NATIVE_NETWORK_NETWORK_SEND_TRANSITION_INVITE_VIA_PRESENCE);
		NETWORK.set_function("NETWORK_SEND_IMPORTANT_TRANSITION_INVITE_VIA_PRESENCE", LUA_NATIVE_NETWORK_NETWORK_SEND_IMPORTANT_TRANSITION_INVITE_VIA_PRESENCE);
		NETWORK.set_function("NETWORK_GET_PRESENCE_INVITE_INDEX_BY_ID", LUA_NATIVE_NETWORK_NETWORK_GET_PRESENCE_INVITE_INDEX_BY_ID);
		NETWORK.set_function("NETWORK_GET_NUM_PRESENCE_INVITES", LUA_NATIVE_NETWORK_NETWORK_GET_NUM_PRESENCE_INVITES);
		NETWORK.set_function("NETWORK_ACCEPT_PRESENCE_INVITE", LUA_NATIVE_NETWORK_NETWORK_ACCEPT_PRESENCE_INVITE);
		NETWORK.set_function("NETWORK_REMOVE_PRESENCE_INVITE", LUA_NATIVE_NETWORK_NETWORK_REMOVE_PRESENCE_INVITE);
		NETWORK.set_function("NETWORK_GET_PRESENCE_INVITE_ID", LUA_NATIVE_NETWORK_NETWORK_GET_PRESENCE_INVITE_ID);
		NETWORK.set_function("NETWORK_GET_PRESENCE_INVITE_INVITER", LUA_NATIVE_NETWORK_NETWORK_GET_PRESENCE_INVITE_INVITER);
		NETWORK.set_function("NETWORK_GET_PRESENCE_INVITE_HANDLE", LUA_NATIVE_NETWORK_NETWORK_GET_PRESENCE_INVITE_HANDLE);
		NETWORK.set_function("NETWORK_GET_PRESENCE_INVITE_SESSION_ID", LUA_NATIVE_NETWORK_NETWORK_GET_PRESENCE_INVITE_SESSION_ID);
		NETWORK.set_function("NETWORK_GET_PRESENCE_INVITE_CONTENT_ID", LUA_NATIVE_NETWORK_NETWORK_GET_PRESENCE_INVITE_CONTENT_ID);
		NETWORK.set_function("NETWORK_GET_PRESENCE_INVITE_PLAYLIST_LENGTH", LUA_NATIVE_NETWORK_NETWORK_GET_PRESENCE_INVITE_PLAYLIST_LENGTH);
		NETWORK.set_function("NETWORK_GET_PRESENCE_INVITE_PLAYLIST_CURRENT", LUA_NATIVE_NETWORK_NETWORK_GET_PRESENCE_INVITE_PLAYLIST_CURRENT);
		NETWORK.set_function("NETWORK_GET_PRESENCE_INVITE_FROM_ADMIN", LUA_NATIVE_NETWORK_NETWORK_GET_PRESENCE_INVITE_FROM_ADMIN);
		NETWORK.set_function("NETWORK_GET_PRESENCE_INVITE_IS_TOURNAMENT", LUA_NATIVE_NETWORK_NETWORK_GET_PRESENCE_INVITE_IS_TOURNAMENT);
		NETWORK.set_function("NETWORK_HAS_FOLLOW_INVITE", LUA_NATIVE_NETWORK_NETWORK_HAS_FOLLOW_INVITE);
		NETWORK.set_function("NETWORK_ACTION_FOLLOW_INVITE", LUA_NATIVE_NETWORK_NETWORK_ACTION_FOLLOW_INVITE);
		NETWORK.set_function("NETWORK_CLEAR_FOLLOW_INVITE", LUA_NATIVE_NETWORK_NETWORK_CLEAR_FOLLOW_INVITE);
		NETWORK.set_function("NETWORK_REMOVE_AND_CANCEL_ALL_INVITES", LUA_NATIVE_NETWORK_NETWORK_REMOVE_AND_CANCEL_ALL_INVITES);
		NETWORK.set_function("NETWORK_REMOVE_TRANSITION_INVITE", LUA_NATIVE_NETWORK_NETWORK_REMOVE_TRANSITION_INVITE);
		NETWORK.set_function("NETWORK_REMOVE_ALL_TRANSITION_INVITE", LUA_NATIVE_NETWORK_NETWORK_REMOVE_ALL_TRANSITION_INVITE);
		NETWORK.set_function("NETWORK_REMOVE_AND_CANCEL_ALL_TRANSITION_INVITES", LUA_NATIVE_NETWORK_NETWORK_REMOVE_AND_CANCEL_ALL_TRANSITION_INVITES);
		NETWORK.set_function("NETWORK_INVITE_GAMERS", LUA_NATIVE_NETWORK_NETWORK_INVITE_GAMERS);
		NETWORK.set_function("NETWORK_HAS_INVITED_GAMER", LUA_NATIVE_NETWORK_NETWORK_HAS_INVITED_GAMER);
		NETWORK.set_function("NETWORK_HAS_MADE_INVITE_DECISION", LUA_NATIVE_NETWORK_NETWORK_HAS_MADE_INVITE_DECISION);
		NETWORK.set_function("NETWORK_GET_INVITE_REPLY_STATUS", LUA_NATIVE_NETWORK_NETWORK_GET_INVITE_REPLY_STATUS);
		NETWORK.set_function("NETWORK_GET_CURRENTLY_SELECTED_GAMER_HANDLE_FROM_INVITE_MENU", LUA_NATIVE_NETWORK_NETWORK_GET_CURRENTLY_SELECTED_GAMER_HANDLE_FROM_INVITE_MENU);
		NETWORK.set_function("NETWORK_SET_CURRENTLY_SELECTED_GAMER_HANDLE_FROM_INVITE_MENU", LUA_NATIVE_NETWORK_NETWORK_SET_CURRENTLY_SELECTED_GAMER_HANDLE_FROM_INVITE_MENU);
		NETWORK.set_function("NETWORK_SET_INVITE_ON_CALL_FOR_INVITE_MENU", LUA_NATIVE_NETWORK_NETWORK_SET_INVITE_ON_CALL_FOR_INVITE_MENU);
		NETWORK.set_function("NETWORK_CHECK_DATA_MANAGER_SUCCEEDED_FOR_HANDLE", LUA_NATIVE_NETWORK_NETWORK_CHECK_DATA_MANAGER_SUCCEEDED_FOR_HANDLE);
		NETWORK.set_function("NETWORK_CHECK_DATA_MANAGER_FOR_HANDLE", LUA_NATIVE_NETWORK_NETWORK_CHECK_DATA_MANAGER_FOR_HANDLE);
		NETWORK.set_function("NETWORK_SET_INVITE_FAILED_MESSAGE_FOR_INVITE_MENU", LUA_NATIVE_NETWORK_NETWORK_SET_INVITE_FAILED_MESSAGE_FOR_INVITE_MENU);
		NETWORK.set_function("FILLOUT_PM_PLAYER_LIST", LUA_NATIVE_NETWORK_FILLOUT_PM_PLAYER_LIST);
		NETWORK.set_function("FILLOUT_PM_PLAYER_LIST_WITH_NAMES", LUA_NATIVE_NETWORK_FILLOUT_PM_PLAYER_LIST_WITH_NAMES);
		NETWORK.set_function("REFRESH_PLAYER_LIST_STATS", LUA_NATIVE_NETWORK_REFRESH_PLAYER_LIST_STATS);
		NETWORK.set_function("NETWORK_SET_CURRENT_DATA_MANAGER_HANDLE", LUA_NATIVE_NETWORK_NETWORK_SET_CURRENT_DATA_MANAGER_HANDLE);
		NETWORK.set_function("NETWORK_IS_IN_PLATFORM_PARTY", LUA_NATIVE_NETWORK_NETWORK_IS_IN_PLATFORM_PARTY);
		NETWORK.set_function("NETWORK_GET_PLATFORM_PARTY_MEMBER_COUNT", LUA_NATIVE_NETWORK_NETWORK_GET_PLATFORM_PARTY_MEMBER_COUNT);
		NETWORK.set_function("NETWORK_GET_PLATFORM_PARTY_MEMBERS", LUA_NATIVE_NETWORK_NETWORK_GET_PLATFORM_PARTY_MEMBERS);
		NETWORK.set_function("NETWORK_IS_IN_PLATFORM_PARTY_CHAT", LUA_NATIVE_NETWORK_NETWORK_IS_IN_PLATFORM_PARTY_CHAT);
		NETWORK.set_function("NETWORK_IS_CHATTING_IN_PLATFORM_PARTY", LUA_NATIVE_NETWORK_NETWORK_IS_CHATTING_IN_PLATFORM_PARTY);
		NETWORK.set_function("NETWORK_CAN_QUEUE_FOR_PREVIOUS_SESSION_JOIN", LUA_NATIVE_NETWORK_NETWORK_CAN_QUEUE_FOR_PREVIOUS_SESSION_JOIN);
		NETWORK.set_function("NETWORK_IS_QUEUING_FOR_SESSION_JOIN", LUA_NATIVE_NETWORK_NETWORK_IS_QUEUING_FOR_SESSION_JOIN);
		NETWORK.set_function("NETWORK_CLEAR_QUEUED_JOIN_REQUEST", LUA_NATIVE_NETWORK_NETWORK_CLEAR_QUEUED_JOIN_REQUEST);
		NETWORK.set_function("NETWORK_SEND_QUEUED_JOIN_REQUEST", LUA_NATIVE_NETWORK_NETWORK_SEND_QUEUED_JOIN_REQUEST);
		NETWORK.set_function("NETWORK_REMOVE_ALL_QUEUED_JOIN_REQUESTS", LUA_NATIVE_NETWORK_NETWORK_REMOVE_ALL_QUEUED_JOIN_REQUESTS);
		NETWORK.set_function("NETWORK_SEED_RANDOM_NUMBER_GENERATOR", LUA_NATIVE_NETWORK_NETWORK_SEED_RANDOM_NUMBER_GENERATOR);
		NETWORK.set_function("NETWORK_GET_RANDOM_INT", LUA_NATIVE_NETWORK_NETWORK_GET_RANDOM_INT);
		NETWORK.set_function("NETWORK_GET_RANDOM_INT_RANGED", LUA_NATIVE_NETWORK_NETWORK_GET_RANDOM_INT_RANGED);
		NETWORK.set_function("NETWORK_GET_RANDOM_FLOAT_RANGED_", LUA_NATIVE_NETWORK_NETWORK_GET_RANDOM_FLOAT_RANGED_);
		NETWORK.set_function("NETWORK_PLAYER_IS_CHEATER", LUA_NATIVE_NETWORK_NETWORK_PLAYER_IS_CHEATER);
		NETWORK.set_function("NETWORK_PLAYER_GET_CHEATER_REASON", LUA_NATIVE_NETWORK_NETWORK_PLAYER_GET_CHEATER_REASON);
		NETWORK.set_function("NETWORK_PLAYER_IS_BADSPORT", LUA_NATIVE_NETWORK_NETWORK_PLAYER_IS_BADSPORT);
		NETWORK.set_function("REMOTE_CHEATER_PLAYER_DETECTED", LUA_NATIVE_NETWORK_REMOTE_CHEATER_PLAYER_DETECTED);
		NETWORK.set_function("BAD_SPORT_PLAYER_LEFT_DETECTED", LUA_NATIVE_NETWORK_BAD_SPORT_PLAYER_LEFT_DETECTED);
		NETWORK.set_function("NETWORK_ADD_INVALID_OBJECT_MODEL", LUA_NATIVE_NETWORK_NETWORK_ADD_INVALID_OBJECT_MODEL);
		NETWORK.set_function("NETWORK_REMOVE_INVALID_OBJECT_MODEL", LUA_NATIVE_NETWORK_NETWORK_REMOVE_INVALID_OBJECT_MODEL);
		NETWORK.set_function("NETWORK_CLEAR_INVALID_OBJECT_MODELS", LUA_NATIVE_NETWORK_NETWORK_CLEAR_INVALID_OBJECT_MODELS);
		NETWORK.set_function("NETWORK_APPLY_PED_SCAR_DATA", LUA_NATIVE_NETWORK_NETWORK_APPLY_PED_SCAR_DATA);
		NETWORK.set_function("NETWORK_SET_THIS_SCRIPT_IS_NETWORK_SCRIPT", LUA_NATIVE_NETWORK_NETWORK_SET_THIS_SCRIPT_IS_NETWORK_SCRIPT);
		NETWORK.set_function("NETWORK_TRY_TO_SET_THIS_SCRIPT_IS_NETWORK_SCRIPT", LUA_NATIVE_NETWORK_NETWORK_TRY_TO_SET_THIS_SCRIPT_IS_NETWORK_SCRIPT);
		NETWORK.set_function("NETWORK_GET_THIS_SCRIPT_IS_NETWORK_SCRIPT", LUA_NATIVE_NETWORK_NETWORK_GET_THIS_SCRIPT_IS_NETWORK_SCRIPT);
		NETWORK.set_function("NETWORK_GET_MAX_NUM_PARTICIPANTS", LUA_NATIVE_NETWORK_NETWORK_GET_MAX_NUM_PARTICIPANTS);
		NETWORK.set_function("NETWORK_GET_NUM_PARTICIPANTS", LUA_NATIVE_NETWORK_NETWORK_GET_NUM_PARTICIPANTS);
		NETWORK.set_function("NETWORK_GET_SCRIPT_STATUS", LUA_NATIVE_NETWORK_NETWORK_GET_SCRIPT_STATUS);
		NETWORK.set_function("NETWORK_REGISTER_HOST_BROADCAST_VARIABLES", LUA_NATIVE_NETWORK_NETWORK_REGISTER_HOST_BROADCAST_VARIABLES);
		NETWORK.set_function("NETWORK_REGISTER_PLAYER_BROADCAST_VARIABLES", LUA_NATIVE_NETWORK_NETWORK_REGISTER_PLAYER_BROADCAST_VARIABLES);
		NETWORK.set_function("NETWORK_REGISTER_HIGH_FREQUENCY_HOST_BROADCAST_VARIABLES", LUA_NATIVE_NETWORK_NETWORK_REGISTER_HIGH_FREQUENCY_HOST_BROADCAST_VARIABLES);
		NETWORK.set_function("NETWORK_REGISTER_HIGH_FREQUENCY_PLAYER_BROADCAST_VARIABLES", LUA_NATIVE_NETWORK_NETWORK_REGISTER_HIGH_FREQUENCY_PLAYER_BROADCAST_VARIABLES);
		NETWORK.set_function("NETWORK_FINISH_BROADCASTING_DATA", LUA_NATIVE_NETWORK_NETWORK_FINISH_BROADCASTING_DATA);
		NETWORK.set_function("NETWORK_HAS_RECEIVED_HOST_BROADCAST_DATA", LUA_NATIVE_NETWORK_NETWORK_HAS_RECEIVED_HOST_BROADCAST_DATA);
		NETWORK.set_function("NETWORK_GET_PLAYER_INDEX", LUA_NATIVE_NETWORK_NETWORK_GET_PLAYER_INDEX);
		NETWORK.set_function("NETWORK_GET_PARTICIPANT_INDEX", LUA_NATIVE_NETWORK_NETWORK_GET_PARTICIPANT_INDEX);
		NETWORK.set_function("NETWORK_GET_PLAYER_INDEX_FROM_PED", LUA_NATIVE_NETWORK_NETWORK_GET_PLAYER_INDEX_FROM_PED);
		NETWORK.set_function("NETWORK_GET_NUM_CONNECTED_PLAYERS", LUA_NATIVE_NETWORK_NETWORK_GET_NUM_CONNECTED_PLAYERS);
		NETWORK.set_function("NETWORK_IS_PLAYER_CONNECTED", LUA_NATIVE_NETWORK_NETWORK_IS_PLAYER_CONNECTED);
		NETWORK.set_function("NETWORK_GET_TOTAL_NUM_PLAYERS", LUA_NATIVE_NETWORK_NETWORK_GET_TOTAL_NUM_PLAYERS);
		NETWORK.set_function("NETWORK_IS_PARTICIPANT_ACTIVE", LUA_NATIVE_NETWORK_NETWORK_IS_PARTICIPANT_ACTIVE);
		NETWORK.set_function("NETWORK_IS_PLAYER_ACTIVE", LUA_NATIVE_NETWORK_NETWORK_IS_PLAYER_ACTIVE);
		NETWORK.set_function("NETWORK_IS_PLAYER_A_PARTICIPANT", LUA_NATIVE_NETWORK_NETWORK_IS_PLAYER_A_PARTICIPANT);
		NETWORK.set_function("NETWORK_IS_HOST_OF_THIS_SCRIPT", LUA_NATIVE_NETWORK_NETWORK_IS_HOST_OF_THIS_SCRIPT);
		NETWORK.set_function("NETWORK_GET_HOST_OF_THIS_SCRIPT", LUA_NATIVE_NETWORK_NETWORK_GET_HOST_OF_THIS_SCRIPT);
		NETWORK.set_function("NETWORK_GET_HOST_OF_SCRIPT", LUA_NATIVE_NETWORK_NETWORK_GET_HOST_OF_SCRIPT);
		NETWORK.set_function("NETWORK_SET_MISSION_FINISHED", LUA_NATIVE_NETWORK_NETWORK_SET_MISSION_FINISHED);
		NETWORK.set_function("NETWORK_IS_SCRIPT_ACTIVE", LUA_NATIVE_NETWORK_NETWORK_IS_SCRIPT_ACTIVE);
		NETWORK.set_function("NETWORK_IS_SCRIPT_ACTIVE_BY_HASH", LUA_NATIVE_NETWORK_NETWORK_IS_SCRIPT_ACTIVE_BY_HASH);
		NETWORK.set_function("NETWORK_IS_THREAD_A_NETWORK_SCRIPT", LUA_NATIVE_NETWORK_NETWORK_IS_THREAD_A_NETWORK_SCRIPT);
		NETWORK.set_function("NETWORK_GET_NUM_SCRIPT_PARTICIPANTS", LUA_NATIVE_NETWORK_NETWORK_GET_NUM_SCRIPT_PARTICIPANTS);
		NETWORK.set_function("NETWORK_GET_INSTANCE_ID_OF_THIS_SCRIPT", LUA_NATIVE_NETWORK_NETWORK_GET_INSTANCE_ID_OF_THIS_SCRIPT);
		NETWORK.set_function("NETWORK_GET_POSITION_HASH_OF_THIS_SCRIPT", LUA_NATIVE_NETWORK_NETWORK_GET_POSITION_HASH_OF_THIS_SCRIPT);
		NETWORK.set_function("NETWORK_IS_PLAYER_A_PARTICIPANT_ON_SCRIPT", LUA_NATIVE_NETWORK_NETWORK_IS_PLAYER_A_PARTICIPANT_ON_SCRIPT);
		NETWORK.set_function("NETWORK_PREVENT_SCRIPT_HOST_MIGRATION", LUA_NATIVE_NETWORK_NETWORK_PREVENT_SCRIPT_HOST_MIGRATION);
		NETWORK.set_function("NETWORK_REQUEST_TO_BE_HOST_OF_THIS_SCRIPT", LUA_NATIVE_NETWORK_NETWORK_REQUEST_TO_BE_HOST_OF_THIS_SCRIPT);
		NETWORK.set_function("PARTICIPANT_ID", LUA_NATIVE_NETWORK_PARTICIPANT_ID);
		NETWORK.set_function("PARTICIPANT_ID_TO_INT", LUA_NATIVE_NETWORK_PARTICIPANT_ID_TO_INT);
		NETWORK.set_function("NETWORK_GET_KILLER_OF_PLAYER", LUA_NATIVE_NETWORK_NETWORK_GET_KILLER_OF_PLAYER);
		NETWORK.set_function("NETWORK_GET_DESTROYER_OF_NETWORK_ID", LUA_NATIVE_NETWORK_NETWORK_GET_DESTROYER_OF_NETWORK_ID);
		NETWORK.set_function("NETWORK_GET_DESTROYER_OF_ENTITY", LUA_NATIVE_NETWORK_NETWORK_GET_DESTROYER_OF_ENTITY);
		NETWORK.set_function("NETWORK_GET_ASSISTED_KILL_OF_ENTITY", LUA_NATIVE_NETWORK_NETWORK_GET_ASSISTED_KILL_OF_ENTITY);
		NETWORK.set_function("NETWORK_GET_ASSISTED_DAMAGE_OF_ENTITY", LUA_NATIVE_NETWORK_NETWORK_GET_ASSISTED_DAMAGE_OF_ENTITY);
		NETWORK.set_function("NETWORK_GET_ENTITY_KILLER_OF_PLAYER", LUA_NATIVE_NETWORK_NETWORK_GET_ENTITY_KILLER_OF_PLAYER);
		NETWORK.set_function("NETWORK_SET_CURRENT_PUBLIC_CONTENT_ID", LUA_NATIVE_NETWORK_NETWORK_SET_CURRENT_PUBLIC_CONTENT_ID);
		NETWORK.set_function("NETWORK_SET_CURRENT_CHAT_OPTION", LUA_NATIVE_NETWORK_NETWORK_SET_CURRENT_CHAT_OPTION);
		NETWORK.set_function("NETWORK_SET_CURRENT_SPAWN_LOCATION_OPTION", LUA_NATIVE_NETWORK_NETWORK_SET_CURRENT_SPAWN_LOCATION_OPTION);
		NETWORK.set_function("NETWORK_SET_VEHICLE_DRIVEN_IN_TEST_DRIVE", LUA_NATIVE_NETWORK_NETWORK_SET_VEHICLE_DRIVEN_IN_TEST_DRIVE);
		NETWORK.set_function("NETWORK_SET_VEHICLE_DRIVEN_LOCATION", LUA_NATIVE_NETWORK_NETWORK_SET_VEHICLE_DRIVEN_LOCATION);
		NETWORK.set_function("NETWORK_RESURRECT_LOCAL_PLAYER", LUA_NATIVE_NETWORK_NETWORK_RESURRECT_LOCAL_PLAYER);
		NETWORK.set_function("NETWORK_SET_LOCAL_PLAYER_INVINCIBLE_TIME", LUA_NATIVE_NETWORK_NETWORK_SET_LOCAL_PLAYER_INVINCIBLE_TIME);
		NETWORK.set_function("NETWORK_IS_LOCAL_PLAYER_INVINCIBLE", LUA_NATIVE_NETWORK_NETWORK_IS_LOCAL_PLAYER_INVINCIBLE);
		NETWORK.set_function("NETWORK_DISABLE_INVINCIBLE_FLASHING", LUA_NATIVE_NETWORK_NETWORK_DISABLE_INVINCIBLE_FLASHING);
		NETWORK.set_function("NETWORK_PATCH_POST_CUTSCENE_HS4F_TUN_ENT", LUA_NATIVE_NETWORK_NETWORK_PATCH_POST_CUTSCENE_HS4F_TUN_ENT);
		NETWORK.set_function("NETWORK_SET_LOCAL_PLAYER_SYNC_LOOK_AT", LUA_NATIVE_NETWORK_NETWORK_SET_LOCAL_PLAYER_SYNC_LOOK_AT);
		NETWORK.set_function("NETWORK_HAS_ENTITY_BEEN_REGISTERED_WITH_THIS_THREAD", LUA_NATIVE_NETWORK_NETWORK_HAS_ENTITY_BEEN_REGISTERED_WITH_THIS_THREAD);
		NETWORK.set_function("NETWORK_GET_NETWORK_ID_FROM_ENTITY", LUA_NATIVE_NETWORK_NETWORK_GET_NETWORK_ID_FROM_ENTITY);
		NETWORK.set_function("NETWORK_GET_ENTITY_FROM_NETWORK_ID", LUA_NATIVE_NETWORK_NETWORK_GET_ENTITY_FROM_NETWORK_ID);
		NETWORK.set_function("NETWORK_GET_ENTITY_IS_NETWORKED", LUA_NATIVE_NETWORK_NETWORK_GET_ENTITY_IS_NETWORKED);
		NETWORK.set_function("NETWORK_GET_ENTITY_IS_LOCAL", LUA_NATIVE_NETWORK_NETWORK_GET_ENTITY_IS_LOCAL);
		NETWORK.set_function("NETWORK_REGISTER_ENTITY_AS_NETWORKED", LUA_NATIVE_NETWORK_NETWORK_REGISTER_ENTITY_AS_NETWORKED);
		NETWORK.set_function("NETWORK_UNREGISTER_NETWORKED_ENTITY", LUA_NATIVE_NETWORK_NETWORK_UNREGISTER_NETWORKED_ENTITY);
		NETWORK.set_function("NETWORK_DOES_NETWORK_ID_EXIST", LUA_NATIVE_NETWORK_NETWORK_DOES_NETWORK_ID_EXIST);
		NETWORK.set_function("NETWORK_DOES_ENTITY_EXIST_WITH_NETWORK_ID", LUA_NATIVE_NETWORK_NETWORK_DOES_ENTITY_EXIST_WITH_NETWORK_ID);
		NETWORK.set_function("NETWORK_REQUEST_CONTROL_OF_NETWORK_ID", LUA_NATIVE_NETWORK_NETWORK_REQUEST_CONTROL_OF_NETWORK_ID);
		NETWORK.set_function("NETWORK_HAS_CONTROL_OF_NETWORK_ID", LUA_NATIVE_NETWORK_NETWORK_HAS_CONTROL_OF_NETWORK_ID);
		NETWORK.set_function("NETWORK_IS_NETWORK_ID_REMOTELY_CONTROLLED", LUA_NATIVE_NETWORK_NETWORK_IS_NETWORK_ID_REMOTELY_CONTROLLED);
		NETWORK.set_function("NETWORK_REQUEST_CONTROL_OF_ENTITY", LUA_NATIVE_NETWORK_NETWORK_REQUEST_CONTROL_OF_ENTITY);
		NETWORK.set_function("NETWORK_REQUEST_CONTROL_OF_DOOR", LUA_NATIVE_NETWORK_NETWORK_REQUEST_CONTROL_OF_DOOR);
		NETWORK.set_function("NETWORK_HAS_CONTROL_OF_ENTITY", LUA_NATIVE_NETWORK_NETWORK_HAS_CONTROL_OF_ENTITY);
		NETWORK.set_function("NETWORK_HAS_CONTROL_OF_PICKUP", LUA_NATIVE_NETWORK_NETWORK_HAS_CONTROL_OF_PICKUP);
		NETWORK.set_function("NETWORK_HAS_CONTROL_OF_DOOR", LUA_NATIVE_NETWORK_NETWORK_HAS_CONTROL_OF_DOOR);
		NETWORK.set_function("NETWORK_IS_DOOR_NETWORKED", LUA_NATIVE_NETWORK_NETWORK_IS_DOOR_NETWORKED);
		NETWORK.set_function("VEH_TO_NET", LUA_NATIVE_NETWORK_VEH_TO_NET);
		NETWORK.set_function("PED_TO_NET", LUA_NATIVE_NETWORK_PED_TO_NET);
		NETWORK.set_function("OBJ_TO_NET", LUA_NATIVE_NETWORK_OBJ_TO_NET);
		NETWORK.set_function("NET_TO_VEH", LUA_NATIVE_NETWORK_NET_TO_VEH);
		NETWORK.set_function("NET_TO_PED", LUA_NATIVE_NETWORK_NET_TO_PED);
		NETWORK.set_function("NET_TO_OBJ", LUA_NATIVE_NETWORK_NET_TO_OBJ);
		NETWORK.set_function("NET_TO_ENT", LUA_NATIVE_NETWORK_NET_TO_ENT);
		NETWORK.set_function("NETWORK_GET_LOCAL_HANDLE", LUA_NATIVE_NETWORK_NETWORK_GET_LOCAL_HANDLE);
		NETWORK.set_function("NETWORK_HANDLE_FROM_USER_ID", LUA_NATIVE_NETWORK_NETWORK_HANDLE_FROM_USER_ID);
		NETWORK.set_function("NETWORK_HANDLE_FROM_MEMBER_ID", LUA_NATIVE_NETWORK_NETWORK_HANDLE_FROM_MEMBER_ID);
		NETWORK.set_function("NETWORK_HANDLE_FROM_PLAYER", LUA_NATIVE_NETWORK_NETWORK_HANDLE_FROM_PLAYER);
		NETWORK.set_function("NETWORK_HASH_FROM_PLAYER_HANDLE", LUA_NATIVE_NETWORK_NETWORK_HASH_FROM_PLAYER_HANDLE);
		NETWORK.set_function("NETWORK_HASH_FROM_GAMER_HANDLE", LUA_NATIVE_NETWORK_NETWORK_HASH_FROM_GAMER_HANDLE);
		NETWORK.set_function("NETWORK_HANDLE_FROM_FRIEND", LUA_NATIVE_NETWORK_NETWORK_HANDLE_FROM_FRIEND);
		NETWORK.set_function("NETWORK_GAMERTAG_FROM_HANDLE_START", LUA_NATIVE_NETWORK_NETWORK_GAMERTAG_FROM_HANDLE_START);
		NETWORK.set_function("NETWORK_GAMERTAG_FROM_HANDLE_PENDING", LUA_NATIVE_NETWORK_NETWORK_GAMERTAG_FROM_HANDLE_PENDING);
		NETWORK.set_function("NETWORK_GAMERTAG_FROM_HANDLE_SUCCEEDED", LUA_NATIVE_NETWORK_NETWORK_GAMERTAG_FROM_HANDLE_SUCCEEDED);
		NETWORK.set_function("NETWORK_GET_GAMERTAG_FROM_HANDLE", LUA_NATIVE_NETWORK_NETWORK_GET_GAMERTAG_FROM_HANDLE);
		NETWORK.set_function("NETWORK_DISPLAYNAMES_FROM_HANDLES_START", LUA_NATIVE_NETWORK_NETWORK_DISPLAYNAMES_FROM_HANDLES_START);
		NETWORK.set_function("NETWORK_GET_DISPLAYNAMES_FROM_HANDLES", LUA_NATIVE_NETWORK_NETWORK_GET_DISPLAYNAMES_FROM_HANDLES);
		NETWORK.set_function("NETWORK_ARE_HANDLES_THE_SAME", LUA_NATIVE_NETWORK_NETWORK_ARE_HANDLES_THE_SAME);
		NETWORK.set_function("NETWORK_IS_HANDLE_VALID", LUA_NATIVE_NETWORK_NETWORK_IS_HANDLE_VALID);
		NETWORK.set_function("NETWORK_GET_PLAYER_FROM_GAMER_HANDLE", LUA_NATIVE_NETWORK_NETWORK_GET_PLAYER_FROM_GAMER_HANDLE);
		NETWORK.set_function("NETWORK_MEMBER_ID_FROM_GAMER_HANDLE", LUA_NATIVE_NETWORK_NETWORK_MEMBER_ID_FROM_GAMER_HANDLE);
		NETWORK.set_function("NETWORK_IS_GAMER_IN_MY_SESSION", LUA_NATIVE_NETWORK_NETWORK_IS_GAMER_IN_MY_SESSION);
		NETWORK.set_function("NETWORK_SHOW_PROFILE_UI", LUA_NATIVE_NETWORK_NETWORK_SHOW_PROFILE_UI);
		NETWORK.set_function("NETWORK_PLAYER_GET_NAME", LUA_NATIVE_NETWORK_NETWORK_PLAYER_GET_NAME);
		NETWORK.set_function("NETWORK_PLAYER_GET_USERID", LUA_NATIVE_NETWORK_NETWORK_PLAYER_GET_USERID);
		NETWORK.set_function("NETWORK_PLAYER_IS_ROCKSTAR_DEV", LUA_NATIVE_NETWORK_NETWORK_PLAYER_IS_ROCKSTAR_DEV);
		NETWORK.set_function("NETWORK_PLAYER_INDEX_IS_CHEATER", LUA_NATIVE_NETWORK_NETWORK_PLAYER_INDEX_IS_CHEATER);
		NETWORK.set_function("NETWORK_ENTITY_GET_OBJECT_ID", LUA_NATIVE_NETWORK_NETWORK_ENTITY_GET_OBJECT_ID);
		NETWORK.set_function("NETWORK_GET_ENTITY_FROM_OBJECT_ID", LUA_NATIVE_NETWORK_NETWORK_GET_ENTITY_FROM_OBJECT_ID);
		NETWORK.set_function("NETWORK_IS_INACTIVE_PROFILE", LUA_NATIVE_NETWORK_NETWORK_IS_INACTIVE_PROFILE);
		NETWORK.set_function("NETWORK_GET_MAX_FRIENDS", LUA_NATIVE_NETWORK_NETWORK_GET_MAX_FRIENDS);
		NETWORK.set_function("NETWORK_GET_FRIEND_COUNT", LUA_NATIVE_NETWORK_NETWORK_GET_FRIEND_COUNT);
		NETWORK.set_function("NETWORK_GET_FRIEND_NAME", LUA_NATIVE_NETWORK_NETWORK_GET_FRIEND_NAME);
		NETWORK.set_function("NETWORK_GET_FRIEND_DISPLAY_NAME", LUA_NATIVE_NETWORK_NETWORK_GET_FRIEND_DISPLAY_NAME);
		NETWORK.set_function("NETWORK_IS_FRIEND_ONLINE", LUA_NATIVE_NETWORK_NETWORK_IS_FRIEND_ONLINE);
		NETWORK.set_function("NETWORK_IS_FRIEND_HANDLE_ONLINE", LUA_NATIVE_NETWORK_NETWORK_IS_FRIEND_HANDLE_ONLINE);
		NETWORK.set_function("NETWORK_IS_FRIEND_IN_SAME_TITLE", LUA_NATIVE_NETWORK_NETWORK_IS_FRIEND_IN_SAME_TITLE);
		NETWORK.set_function("NETWORK_IS_FRIEND_IN_MULTIPLAYER", LUA_NATIVE_NETWORK_NETWORK_IS_FRIEND_IN_MULTIPLAYER);
		NETWORK.set_function("NETWORK_IS_FRIEND", LUA_NATIVE_NETWORK_NETWORK_IS_FRIEND);
		NETWORK.set_function("NETWORK_IS_PENDING_FRIEND", LUA_NATIVE_NETWORK_NETWORK_IS_PENDING_FRIEND);
		NETWORK.set_function("NETWORK_IS_ADDING_FRIEND", LUA_NATIVE_NETWORK_NETWORK_IS_ADDING_FRIEND);
		NETWORK.set_function("NETWORK_ADD_FRIEND", LUA_NATIVE_NETWORK_NETWORK_ADD_FRIEND);
		NETWORK.set_function("NETWORK_IS_FRIEND_INDEX_ONLINE", LUA_NATIVE_NETWORK_NETWORK_IS_FRIEND_INDEX_ONLINE);
		NETWORK.set_function("NETWORK_SET_PLAYER_IS_PASSIVE", LUA_NATIVE_NETWORK_NETWORK_SET_PLAYER_IS_PASSIVE);
		NETWORK.set_function("NETWORK_GET_PLAYER_OWNS_WAYPOINT", LUA_NATIVE_NETWORK_NETWORK_GET_PLAYER_OWNS_WAYPOINT);
		NETWORK.set_function("NETWORK_CAN_SET_WAYPOINT", LUA_NATIVE_NETWORK_NETWORK_CAN_SET_WAYPOINT);
		NETWORK.set_function("NETWORK_IGNORE_REMOTE_WAYPOINTS", LUA_NATIVE_NETWORK_NETWORK_IGNORE_REMOTE_WAYPOINTS);
		NETWORK.set_function("NETWORK_IS_PLAYER_ON_BLOCKLIST", LUA_NATIVE_NETWORK_NETWORK_IS_PLAYER_ON_BLOCKLIST);
		NETWORK.set_function("NETWORK_SET_SCRIPT_AUTOMUTED", LUA_NATIVE_NETWORK_NETWORK_SET_SCRIPT_AUTOMUTED);
		NETWORK.set_function("NETWORK_HAS_AUTOMUTE_OVERRIDE", LUA_NATIVE_NETWORK_NETWORK_HAS_AUTOMUTE_OVERRIDE);
		NETWORK.set_function("NETWORK_HAS_HEADSET", LUA_NATIVE_NETWORK_NETWORK_HAS_HEADSET);
		NETWORK.set_function("NETWORK_SET_LOOK_AT_TALKERS", LUA_NATIVE_NETWORK_NETWORK_SET_LOOK_AT_TALKERS);
		NETWORK.set_function("NETWORK_IS_PUSH_TO_TALK_ACTIVE", LUA_NATIVE_NETWORK_NETWORK_IS_PUSH_TO_TALK_ACTIVE);
		NETWORK.set_function("NETWORK_GAMER_HAS_HEADSET", LUA_NATIVE_NETWORK_NETWORK_GAMER_HAS_HEADSET);
		NETWORK.set_function("NETWORK_IS_GAMER_TALKING", LUA_NATIVE_NETWORK_NETWORK_IS_GAMER_TALKING);
		NETWORK.set_function("NETWORK_PERMISSIONS_HAS_GAMER_RECORD", LUA_NATIVE_NETWORK_NETWORK_PERMISSIONS_HAS_GAMER_RECORD);
		NETWORK.set_function("NETWORK_CAN_COMMUNICATE_WITH_GAMER", LUA_NATIVE_NETWORK_NETWORK_CAN_COMMUNICATE_WITH_GAMER);
		NETWORK.set_function("NETWORK_CAN_TEXT_CHAT_WITH_GAMER", LUA_NATIVE_NETWORK_NETWORK_CAN_TEXT_CHAT_WITH_GAMER);
		NETWORK.set_function("NETWORK_IS_GAMER_MUTED_BY_ME", LUA_NATIVE_NETWORK_NETWORK_IS_GAMER_MUTED_BY_ME);
		NETWORK.set_function("NETWORK_AM_I_MUTED_BY_GAMER", LUA_NATIVE_NETWORK_NETWORK_AM_I_MUTED_BY_GAMER);
		NETWORK.set_function("NETWORK_IS_GAMER_BLOCKED_BY_ME", LUA_NATIVE_NETWORK_NETWORK_IS_GAMER_BLOCKED_BY_ME);
		NETWORK.set_function("NETWORK_AM_I_BLOCKED_BY_GAMER", LUA_NATIVE_NETWORK_NETWORK_AM_I_BLOCKED_BY_GAMER);
		NETWORK.set_function("NETWORK_CAN_VIEW_GAMER_USER_CONTENT", LUA_NATIVE_NETWORK_NETWORK_CAN_VIEW_GAMER_USER_CONTENT);
		NETWORK.set_function("NETWORK_HAS_VIEW_GAMER_USER_CONTENT_RESULT", LUA_NATIVE_NETWORK_NETWORK_HAS_VIEW_GAMER_USER_CONTENT_RESULT);
		NETWORK.set_function("NETWORK_CAN_PLAY_MULTIPLAYER_WITH_GAMER", LUA_NATIVE_NETWORK_NETWORK_CAN_PLAY_MULTIPLAYER_WITH_GAMER);
		NETWORK.set_function("NETWORK_CAN_GAMER_PLAY_MULTIPLAYER_WITH_ME", LUA_NATIVE_NETWORK_NETWORK_CAN_GAMER_PLAY_MULTIPLAYER_WITH_ME);
		NETWORK.set_function("NETWORK_CAN_SEND_LOCAL_INVITE", LUA_NATIVE_NETWORK_NETWORK_CAN_SEND_LOCAL_INVITE);
		NETWORK.set_function("NETWORK_CAN_RECEIVE_LOCAL_INVITE", LUA_NATIVE_NETWORK_NETWORK_CAN_RECEIVE_LOCAL_INVITE);
		NETWORK.set_function("NETWORK_IS_PLAYER_TALKING", LUA_NATIVE_NETWORK_NETWORK_IS_PLAYER_TALKING);
		NETWORK.set_function("NETWORK_PLAYER_HAS_HEADSET", LUA_NATIVE_NETWORK_NETWORK_PLAYER_HAS_HEADSET);
		NETWORK.set_function("NETWORK_IS_PLAYER_MUTED_BY_ME", LUA_NATIVE_NETWORK_NETWORK_IS_PLAYER_MUTED_BY_ME);
		NETWORK.set_function("NETWORK_AM_I_MUTED_BY_PLAYER", LUA_NATIVE_NETWORK_NETWORK_AM_I_MUTED_BY_PLAYER);
		NETWORK.set_function("NETWORK_IS_PLAYER_BLOCKED_BY_ME", LUA_NATIVE_NETWORK_NETWORK_IS_PLAYER_BLOCKED_BY_ME);
		NETWORK.set_function("NETWORK_AM_I_BLOCKED_BY_PLAYER", LUA_NATIVE_NETWORK_NETWORK_AM_I_BLOCKED_BY_PLAYER);
		NETWORK.set_function("NETWORK_GET_PLAYER_LOUDNESS", LUA_NATIVE_NETWORK_NETWORK_GET_PLAYER_LOUDNESS);
		NETWORK.set_function("NETWORK_SET_TALKER_PROXIMITY", LUA_NATIVE_NETWORK_NETWORK_SET_TALKER_PROXIMITY);
		NETWORK.set_function("NETWORK_GET_TALKER_PROXIMITY", LUA_NATIVE_NETWORK_NETWORK_GET_TALKER_PROXIMITY);
		NETWORK.set_function("NETWORK_SET_VOICE_ACTIVE", LUA_NATIVE_NETWORK_NETWORK_SET_VOICE_ACTIVE);
		NETWORK.set_function("NETWORK_REMAIN_IN_GAME_CHAT", LUA_NATIVE_NETWORK_NETWORK_REMAIN_IN_GAME_CHAT);
		NETWORK.set_function("NETWORK_OVERRIDE_TRANSITION_CHAT", LUA_NATIVE_NETWORK_NETWORK_OVERRIDE_TRANSITION_CHAT);
		NETWORK.set_function("NETWORK_SET_TEAM_ONLY_CHAT", LUA_NATIVE_NETWORK_NETWORK_SET_TEAM_ONLY_CHAT);
		NETWORK.set_function("NETWORK_SET_SCRIPT_CONTROLLING_TEAMS", LUA_NATIVE_NETWORK_NETWORK_SET_SCRIPT_CONTROLLING_TEAMS);
		NETWORK.set_function("NETWORK_SET_SAME_TEAM_AS_LOCAL_PLAYER", LUA_NATIVE_NETWORK_NETWORK_SET_SAME_TEAM_AS_LOCAL_PLAYER);
		NETWORK.set_function("NETWORK_OVERRIDE_TEAM_RESTRICTIONS", LUA_NATIVE_NETWORK_NETWORK_OVERRIDE_TEAM_RESTRICTIONS);
		NETWORK.set_function("NETWORK_SET_OVERRIDE_SPECTATOR_MODE", LUA_NATIVE_NETWORK_NETWORK_SET_OVERRIDE_SPECTATOR_MODE);
		NETWORK.set_function("NETWORK_SET_OVERRIDE_TUTORIAL_SESSION_CHAT", LUA_NATIVE_NETWORK_NETWORK_SET_OVERRIDE_TUTORIAL_SESSION_CHAT);
		NETWORK.set_function("NETWORK_SET_PROXIMITY_AFFECTS_TEAM", LUA_NATIVE_NETWORK_NETWORK_SET_PROXIMITY_AFFECTS_TEAM);
		NETWORK.set_function("NETWORK_SET_NO_SPECTATOR_CHAT", LUA_NATIVE_NETWORK_NETWORK_SET_NO_SPECTATOR_CHAT);
		NETWORK.set_function("NETWORK_SET_IGNORE_SPECTATOR_CHAT_LIMITS_SAME_TEAM", LUA_NATIVE_NETWORK_NETWORK_SET_IGNORE_SPECTATOR_CHAT_LIMITS_SAME_TEAM);
		NETWORK.set_function("NETWORK_OVERRIDE_CHAT_RESTRICTIONS", LUA_NATIVE_NETWORK_NETWORK_OVERRIDE_CHAT_RESTRICTIONS);
		NETWORK.set_function("NETWORK_OVERRIDE_SEND_RESTRICTIONS", LUA_NATIVE_NETWORK_NETWORK_OVERRIDE_SEND_RESTRICTIONS);
		NETWORK.set_function("NETWORK_OVERRIDE_SEND_RESTRICTIONS_ALL", LUA_NATIVE_NETWORK_NETWORK_OVERRIDE_SEND_RESTRICTIONS_ALL);
		NETWORK.set_function("NETWORK_OVERRIDE_RECEIVE_RESTRICTIONS", LUA_NATIVE_NETWORK_NETWORK_OVERRIDE_RECEIVE_RESTRICTIONS);
		NETWORK.set_function("NETWORK_OVERRIDE_RECEIVE_RESTRICTIONS_ALL", LUA_NATIVE_NETWORK_NETWORK_OVERRIDE_RECEIVE_RESTRICTIONS_ALL);
		NETWORK.set_function("NETWORK_SET_VOICE_CHANNEL", LUA_NATIVE_NETWORK_NETWORK_SET_VOICE_CHANNEL);
		NETWORK.set_function("NETWORK_CLEAR_VOICE_CHANNEL", LUA_NATIVE_NETWORK_NETWORK_CLEAR_VOICE_CHANNEL);
		NETWORK.set_function("NETWORK_APPLY_VOICE_PROXIMITY_OVERRIDE", LUA_NATIVE_NETWORK_NETWORK_APPLY_VOICE_PROXIMITY_OVERRIDE);
		NETWORK.set_function("NETWORK_CLEAR_VOICE_PROXIMITY_OVERRIDE", LUA_NATIVE_NETWORK_NETWORK_CLEAR_VOICE_PROXIMITY_OVERRIDE);
		NETWORK.set_function("NETWORK_ENABLE_VOICE_BANDWIDTH_RESTRICTION", LUA_NATIVE_NETWORK_NETWORK_ENABLE_VOICE_BANDWIDTH_RESTRICTION);
		NETWORK.set_function("NETWORK_DISABLE_VOICE_BANDWIDTH_RESTRICTION", LUA_NATIVE_NETWORK_NETWORK_DISABLE_VOICE_BANDWIDTH_RESTRICTION);
		NETWORK.set_function("NETWORK_GET_MUTE_COUNT_FOR_PLAYER", LUA_NATIVE_NETWORK_NETWORK_GET_MUTE_COUNT_FOR_PLAYER);
		NETWORK.set_function("NETWORK_SET_SPECTATOR_TO_NON_SPECTATOR_TEXT_CHAT", LUA_NATIVE_NETWORK_NETWORK_SET_SPECTATOR_TO_NON_SPECTATOR_TEXT_CHAT);
		NETWORK.set_function("NETWORK_TEXT_CHAT_IS_TYPING", LUA_NATIVE_NETWORK_NETWORK_TEXT_CHAT_IS_TYPING);
		NETWORK.set_function("SHUTDOWN_AND_LAUNCH_SINGLE_PLAYER_GAME", LUA_NATIVE_NETWORK_SHUTDOWN_AND_LAUNCH_SINGLE_PLAYER_GAME);
		NETWORK.set_function("SHUTDOWN_AND_LOAD_MOST_RECENT_SAVE", LUA_NATIVE_NETWORK_SHUTDOWN_AND_LOAD_MOST_RECENT_SAVE);
		NETWORK.set_function("NETWORK_SET_FRIENDLY_FIRE_OPTION", LUA_NATIVE_NETWORK_NETWORK_SET_FRIENDLY_FIRE_OPTION);
		NETWORK.set_function("NETWORK_SET_RICH_PRESENCE", LUA_NATIVE_NETWORK_NETWORK_SET_RICH_PRESENCE);
		NETWORK.set_function("NETWORK_SET_RICH_PRESENCE_STRING", LUA_NATIVE_NETWORK_NETWORK_SET_RICH_PRESENCE_STRING);
		NETWORK.set_function("NETWORK_GET_TIMEOUT_TIME", LUA_NATIVE_NETWORK_NETWORK_GET_TIMEOUT_TIME);
		NETWORK.set_function("NETWORK_LEAVE_PED_BEHIND_BEFORE_WARP", LUA_NATIVE_NETWORK_NETWORK_LEAVE_PED_BEHIND_BEFORE_WARP);
		NETWORK.set_function("NETWORK_LEAVE_PED_BEHIND_BEFORE_CUTSCENE", LUA_NATIVE_NETWORK_NETWORK_LEAVE_PED_BEHIND_BEFORE_CUTSCENE);
		NETWORK.set_function("REMOVE_ALL_STICKY_BOMBS_FROM_ENTITY", LUA_NATIVE_NETWORK_REMOVE_ALL_STICKY_BOMBS_FROM_ENTITY);
		NETWORK.set_function("NETWORK_KEEP_ENTITY_COLLISION_DISABLED_AFTER_ANIM_SCENE", LUA_NATIVE_NETWORK_NETWORK_KEEP_ENTITY_COLLISION_DISABLED_AFTER_ANIM_SCENE);
		NETWORK.set_function("NETWORK_IS_ANY_PLAYER_NEAR", LUA_NATIVE_NETWORK_NETWORK_IS_ANY_PLAYER_NEAR);
		NETWORK.set_function("NETWORK_CLAN_SERVICE_IS_VALID", LUA_NATIVE_NETWORK_NETWORK_CLAN_SERVICE_IS_VALID);
		NETWORK.set_function("NETWORK_CLAN_PLAYER_IS_ACTIVE", LUA_NATIVE_NETWORK_NETWORK_CLAN_PLAYER_IS_ACTIVE);
		NETWORK.set_function("NETWORK_CLAN_PLAYER_GET_DESC", LUA_NATIVE_NETWORK_NETWORK_CLAN_PLAYER_GET_DESC);
		NETWORK.set_function("NETWORK_CLAN_IS_ROCKSTAR_CLAN", LUA_NATIVE_NETWORK_NETWORK_CLAN_IS_ROCKSTAR_CLAN);
		NETWORK.set_function("NETWORK_CLAN_GET_UI_FORMATTED_TAG", LUA_NATIVE_NETWORK_NETWORK_CLAN_GET_UI_FORMATTED_TAG);
		NETWORK.set_function("NETWORK_CLAN_GET_LOCAL_MEMBERSHIPS_COUNT", LUA_NATIVE_NETWORK_NETWORK_CLAN_GET_LOCAL_MEMBERSHIPS_COUNT);
		NETWORK.set_function("NETWORK_CLAN_GET_MEMBERSHIP_DESC", LUA_NATIVE_NETWORK_NETWORK_CLAN_GET_MEMBERSHIP_DESC);
		NETWORK.set_function("NETWORK_CLAN_DOWNLOAD_MEMBERSHIP", LUA_NATIVE_NETWORK_NETWORK_CLAN_DOWNLOAD_MEMBERSHIP);
		NETWORK.set_function("NETWORK_CLAN_DOWNLOAD_MEMBERSHIP_PENDING", LUA_NATIVE_NETWORK_NETWORK_CLAN_DOWNLOAD_MEMBERSHIP_PENDING);
		NETWORK.set_function("NETWORK_CLAN_ANY_DOWNLOAD_MEMBERSHIP_PENDING", LUA_NATIVE_NETWORK_NETWORK_CLAN_ANY_DOWNLOAD_MEMBERSHIP_PENDING);
		NETWORK.set_function("NETWORK_CLAN_REMOTE_MEMBERSHIPS_ARE_IN_CACHE", LUA_NATIVE_NETWORK_NETWORK_CLAN_REMOTE_MEMBERSHIPS_ARE_IN_CACHE);
		NETWORK.set_function("NETWORK_CLAN_GET_MEMBERSHIP_COUNT", LUA_NATIVE_NETWORK_NETWORK_CLAN_GET_MEMBERSHIP_COUNT);
		NETWORK.set_function("NETWORK_CLAN_GET_MEMBERSHIP_VALID", LUA_NATIVE_NETWORK_NETWORK_CLAN_GET_MEMBERSHIP_VALID);
		NETWORK.set_function("NETWORK_CLAN_GET_MEMBERSHIP", LUA_NATIVE_NETWORK_NETWORK_CLAN_GET_MEMBERSHIP);
		NETWORK.set_function("NETWORK_CLAN_JOIN", LUA_NATIVE_NETWORK_NETWORK_CLAN_JOIN);
		NETWORK.set_function("NETWORK_CLAN_CREWINFO_GET_STRING_VALUE", LUA_NATIVE_NETWORK_NETWORK_CLAN_CREWINFO_GET_STRING_VALUE);
		NETWORK.set_function("NETWORK_CLAN_CREWINFO_GET_CREWRANKTITLE", LUA_NATIVE_NETWORK_NETWORK_CLAN_CREWINFO_GET_CREWRANKTITLE);
		NETWORK.set_function("NETWORK_CLAN_HAS_CREWINFO_METADATA_BEEN_RECEIVED", LUA_NATIVE_NETWORK_NETWORK_CLAN_HAS_CREWINFO_METADATA_BEEN_RECEIVED);
		NETWORK.set_function("NETWORK_CLAN_GET_EMBLEM_TXD_NAME", LUA_NATIVE_NETWORK_NETWORK_CLAN_GET_EMBLEM_TXD_NAME);
		NETWORK.set_function("NETWORK_CLAN_REQUEST_EMBLEM", LUA_NATIVE_NETWORK_NETWORK_CLAN_REQUEST_EMBLEM);
		NETWORK.set_function("NETWORK_CLAN_IS_EMBLEM_READY", LUA_NATIVE_NETWORK_NETWORK_CLAN_IS_EMBLEM_READY);
		NETWORK.set_function("NETWORK_CLAN_RELEASE_EMBLEM", LUA_NATIVE_NETWORK_NETWORK_CLAN_RELEASE_EMBLEM);
		NETWORK.set_function("NETWORK_GET_PRIMARY_CLAN_DATA_CLEAR", LUA_NATIVE_NETWORK_NETWORK_GET_PRIMARY_CLAN_DATA_CLEAR);
		NETWORK.set_function("NETWORK_GET_PRIMARY_CLAN_DATA_CANCEL", LUA_NATIVE_NETWORK_NETWORK_GET_PRIMARY_CLAN_DATA_CANCEL);
		NETWORK.set_function("NETWORK_GET_PRIMARY_CLAN_DATA_START", LUA_NATIVE_NETWORK_NETWORK_GET_PRIMARY_CLAN_DATA_START);
		NETWORK.set_function("NETWORK_GET_PRIMARY_CLAN_DATA_PENDING", LUA_NATIVE_NETWORK_NETWORK_GET_PRIMARY_CLAN_DATA_PENDING);
		NETWORK.set_function("NETWORK_GET_PRIMARY_CLAN_DATA_SUCCESS", LUA_NATIVE_NETWORK_NETWORK_GET_PRIMARY_CLAN_DATA_SUCCESS);
		NETWORK.set_function("NETWORK_GET_PRIMARY_CLAN_DATA_NEW", LUA_NATIVE_NETWORK_NETWORK_GET_PRIMARY_CLAN_DATA_NEW);
		NETWORK.set_function("SET_NETWORK_ID_CAN_MIGRATE", LUA_NATIVE_NETWORK_SET_NETWORK_ID_CAN_MIGRATE);
		NETWORK.set_function("SET_NETWORK_ID_EXISTS_ON_ALL_MACHINES", LUA_NATIVE_NETWORK_SET_NETWORK_ID_EXISTS_ON_ALL_MACHINES);
		NETWORK.set_function("SET_NETWORK_ID_ALWAYS_EXISTS_FOR_PLAYER", LUA_NATIVE_NETWORK_SET_NETWORK_ID_ALWAYS_EXISTS_FOR_PLAYER);
		NETWORK.set_function("SET_NETWORK_ID_CAN_BE_REASSIGNED", LUA_NATIVE_NETWORK_SET_NETWORK_ID_CAN_BE_REASSIGNED);
		NETWORK.set_function("NETWORK_SET_ENTITY_CAN_BLEND", LUA_NATIVE_NETWORK_NETWORK_SET_ENTITY_CAN_BLEND);
		NETWORK.set_function("NETWORK_SET_OBJECT_CAN_BLEND_WHEN_FIXED", LUA_NATIVE_NETWORK_NETWORK_SET_OBJECT_CAN_BLEND_WHEN_FIXED);
		NETWORK.set_function("NETWORK_SET_ENTITY_ONLY_EXISTS_FOR_PARTICIPANTS", LUA_NATIVE_NETWORK_NETWORK_SET_ENTITY_ONLY_EXISTS_FOR_PARTICIPANTS);
		NETWORK.set_function("SET_NETWORK_ID_VISIBLE_IN_CUTSCENE", LUA_NATIVE_NETWORK_SET_NETWORK_ID_VISIBLE_IN_CUTSCENE);
		NETWORK.set_function("SET_NETWORK_ID_VISIBLE_IN_CUTSCENE_HACK", LUA_NATIVE_NETWORK_SET_NETWORK_ID_VISIBLE_IN_CUTSCENE_HACK);
		NETWORK.set_function("SET_NETWORK_ID_VISIBLE_IN_CUTSCENE_REMAIN_HACK", LUA_NATIVE_NETWORK_SET_NETWORK_ID_VISIBLE_IN_CUTSCENE_REMAIN_HACK);
		NETWORK.set_function("SET_NETWORK_CUTSCENE_ENTITIES", LUA_NATIVE_NETWORK_SET_NETWORK_CUTSCENE_ENTITIES);
		NETWORK.set_function("ARE_CUTSCENE_ENTITIES_NETWORKED", LUA_NATIVE_NETWORK_ARE_CUTSCENE_ENTITIES_NETWORKED);
		NETWORK.set_function("SET_NETWORK_ID_PASS_CONTROL_IN_TUTORIAL", LUA_NATIVE_NETWORK_SET_NETWORK_ID_PASS_CONTROL_IN_TUTORIAL);
		NETWORK.set_function("IS_NETWORK_ID_OWNED_BY_PARTICIPANT", LUA_NATIVE_NETWORK_IS_NETWORK_ID_OWNED_BY_PARTICIPANT);
		NETWORK.set_function("SET_REMOTE_PLAYER_VISIBLE_IN_CUTSCENE", LUA_NATIVE_NETWORK_SET_REMOTE_PLAYER_VISIBLE_IN_CUTSCENE);
		NETWORK.set_function("SET_LOCAL_PLAYER_VISIBLE_IN_CUTSCENE", LUA_NATIVE_NETWORK_SET_LOCAL_PLAYER_VISIBLE_IN_CUTSCENE);
		NETWORK.set_function("SET_LOCAL_PLAYER_INVISIBLE_LOCALLY", LUA_NATIVE_NETWORK_SET_LOCAL_PLAYER_INVISIBLE_LOCALLY);
		NETWORK.set_function("SET_LOCAL_PLAYER_VISIBLE_LOCALLY", LUA_NATIVE_NETWORK_SET_LOCAL_PLAYER_VISIBLE_LOCALLY);
		NETWORK.set_function("SET_PLAYER_INVISIBLE_LOCALLY", LUA_NATIVE_NETWORK_SET_PLAYER_INVISIBLE_LOCALLY);
		NETWORK.set_function("SET_PLAYER_VISIBLE_LOCALLY", LUA_NATIVE_NETWORK_SET_PLAYER_VISIBLE_LOCALLY);
		NETWORK.set_function("FADE_OUT_LOCAL_PLAYER", LUA_NATIVE_NETWORK_FADE_OUT_LOCAL_PLAYER);
		NETWORK.set_function("NETWORK_FADE_OUT_ENTITY", LUA_NATIVE_NETWORK_NETWORK_FADE_OUT_ENTITY);
		NETWORK.set_function("NETWORK_FADE_IN_ENTITY", LUA_NATIVE_NETWORK_NETWORK_FADE_IN_ENTITY);
		NETWORK.set_function("NETWORK_IS_PLAYER_FADING", LUA_NATIVE_NETWORK_NETWORK_IS_PLAYER_FADING);
		NETWORK.set_function("NETWORK_IS_ENTITY_FADING", LUA_NATIVE_NETWORK_NETWORK_IS_ENTITY_FADING);
		NETWORK.set_function("IS_PLAYER_IN_CUTSCENE", LUA_NATIVE_NETWORK_IS_PLAYER_IN_CUTSCENE);
		NETWORK.set_function("SET_ENTITY_VISIBLE_IN_CUTSCENE", LUA_NATIVE_NETWORK_SET_ENTITY_VISIBLE_IN_CUTSCENE);
		NETWORK.set_function("SET_ENTITY_LOCALLY_INVISIBLE", LUA_NATIVE_NETWORK_SET_ENTITY_LOCALLY_INVISIBLE);
		NETWORK.set_function("SET_ENTITY_LOCALLY_VISIBLE", LUA_NATIVE_NETWORK_SET_ENTITY_LOCALLY_VISIBLE);
		NETWORK.set_function("IS_DAMAGE_TRACKER_ACTIVE_ON_NETWORK_ID", LUA_NATIVE_NETWORK_IS_DAMAGE_TRACKER_ACTIVE_ON_NETWORK_ID);
		NETWORK.set_function("ACTIVATE_DAMAGE_TRACKER_ON_NETWORK_ID", LUA_NATIVE_NETWORK_ACTIVATE_DAMAGE_TRACKER_ON_NETWORK_ID);
		NETWORK.set_function("IS_DAMAGE_TRACKER_ACTIVE_ON_PLAYER", LUA_NATIVE_NETWORK_IS_DAMAGE_TRACKER_ACTIVE_ON_PLAYER);
		NETWORK.set_function("ACTIVATE_DAMAGE_TRACKER_ON_PLAYER", LUA_NATIVE_NETWORK_ACTIVATE_DAMAGE_TRACKER_ON_PLAYER);
		NETWORK.set_function("IS_SPHERE_VISIBLE_TO_ANOTHER_MACHINE", LUA_NATIVE_NETWORK_IS_SPHERE_VISIBLE_TO_ANOTHER_MACHINE);
		NETWORK.set_function("IS_SPHERE_VISIBLE_TO_PLAYER", LUA_NATIVE_NETWORK_IS_SPHERE_VISIBLE_TO_PLAYER);
		NETWORK.set_function("RESERVE_NETWORK_MISSION_OBJECTS", LUA_NATIVE_NETWORK_RESERVE_NETWORK_MISSION_OBJECTS);
		NETWORK.set_function("RESERVE_NETWORK_MISSION_PEDS", LUA_NATIVE_NETWORK_RESERVE_NETWORK_MISSION_PEDS);
		NETWORK.set_function("RESERVE_NETWORK_MISSION_VEHICLES", LUA_NATIVE_NETWORK_RESERVE_NETWORK_MISSION_VEHICLES);
		NETWORK.set_function("RESERVE_LOCAL_NETWORK_MISSION_OBJECTS", LUA_NATIVE_NETWORK_RESERVE_LOCAL_NETWORK_MISSION_OBJECTS);
		NETWORK.set_function("RESERVE_LOCAL_NETWORK_MISSION_PEDS", LUA_NATIVE_NETWORK_RESERVE_LOCAL_NETWORK_MISSION_PEDS);
		NETWORK.set_function("RESERVE_LOCAL_NETWORK_MISSION_VEHICLES", LUA_NATIVE_NETWORK_RESERVE_LOCAL_NETWORK_MISSION_VEHICLES);
		NETWORK.set_function("CAN_REGISTER_MISSION_OBJECTS", LUA_NATIVE_NETWORK_CAN_REGISTER_MISSION_OBJECTS);
		NETWORK.set_function("CAN_REGISTER_MISSION_PEDS", LUA_NATIVE_NETWORK_CAN_REGISTER_MISSION_PEDS);
		NETWORK.set_function("CAN_REGISTER_MISSION_VEHICLES", LUA_NATIVE_NETWORK_CAN_REGISTER_MISSION_VEHICLES);
		NETWORK.set_function("CAN_REGISTER_MISSION_PICKUPS", LUA_NATIVE_NETWORK_CAN_REGISTER_MISSION_PICKUPS);
		NETWORK.set_function("CAN_REGISTER_MISSION_DOORS", LUA_NATIVE_NETWORK_CAN_REGISTER_MISSION_DOORS);
		NETWORK.set_function("CAN_REGISTER_MISSION_ENTITIES", LUA_NATIVE_NETWORK_CAN_REGISTER_MISSION_ENTITIES);
		NETWORK.set_function("GET_NUM_RESERVED_MISSION_OBJECTS", LUA_NATIVE_NETWORK_GET_NUM_RESERVED_MISSION_OBJECTS);
		NETWORK.set_function("GET_NUM_RESERVED_MISSION_PEDS", LUA_NATIVE_NETWORK_GET_NUM_RESERVED_MISSION_PEDS);
		NETWORK.set_function("GET_NUM_RESERVED_MISSION_VEHICLES", LUA_NATIVE_NETWORK_GET_NUM_RESERVED_MISSION_VEHICLES);
		NETWORK.set_function("GET_NUM_CREATED_MISSION_OBJECTS", LUA_NATIVE_NETWORK_GET_NUM_CREATED_MISSION_OBJECTS);
		NETWORK.set_function("GET_NUM_CREATED_MISSION_PEDS", LUA_NATIVE_NETWORK_GET_NUM_CREATED_MISSION_PEDS);
		NETWORK.set_function("GET_NUM_CREATED_MISSION_VEHICLES", LUA_NATIVE_NETWORK_GET_NUM_CREATED_MISSION_VEHICLES);
		NETWORK.set_function("GET_RESERVED_MISSION_ENTITIES_IN_AREA", LUA_NATIVE_NETWORK_GET_RESERVED_MISSION_ENTITIES_IN_AREA);
		NETWORK.set_function("GET_MAX_NUM_NETWORK_OBJECTS", LUA_NATIVE_NETWORK_GET_MAX_NUM_NETWORK_OBJECTS);
		NETWORK.set_function("GET_MAX_NUM_NETWORK_PEDS", LUA_NATIVE_NETWORK_GET_MAX_NUM_NETWORK_PEDS);
		NETWORK.set_function("GET_MAX_NUM_NETWORK_VEHICLES", LUA_NATIVE_NETWORK_GET_MAX_NUM_NETWORK_VEHICLES);
		NETWORK.set_function("GET_MAX_NUM_NETWORK_PICKUPS", LUA_NATIVE_NETWORK_GET_MAX_NUM_NETWORK_PICKUPS);
		NETWORK.set_function("NETWORK_SET_OBJECT_SCOPE_DISTANCE", LUA_NATIVE_NETWORK_NETWORK_SET_OBJECT_SCOPE_DISTANCE);
		NETWORK.set_function("NETWORK_ALLOW_CLONING_WHILE_IN_TUTORIAL", LUA_NATIVE_NETWORK_NETWORK_ALLOW_CLONING_WHILE_IN_TUTORIAL);
		NETWORK.set_function("NETWORK_SET_TASK_CUTSCENE_INSCOPE_MULTIPLER", LUA_NATIVE_NETWORK_NETWORK_SET_TASK_CUTSCENE_INSCOPE_MULTIPLER);
		NETWORK.set_function("GET_NETWORK_TIME", LUA_NATIVE_NETWORK_GET_NETWORK_TIME);
		NETWORK.set_function("GET_NETWORK_TIME_ACCURATE", LUA_NATIVE_NETWORK_GET_NETWORK_TIME_ACCURATE);
		NETWORK.set_function("HAS_NETWORK_TIME_STARTED", LUA_NATIVE_NETWORK_HAS_NETWORK_TIME_STARTED);
		NETWORK.set_function("GET_TIME_OFFSET", LUA_NATIVE_NETWORK_GET_TIME_OFFSET);
		NETWORK.set_function("IS_TIME_LESS_THAN", LUA_NATIVE_NETWORK_IS_TIME_LESS_THAN);
		NETWORK.set_function("IS_TIME_MORE_THAN", LUA_NATIVE_NETWORK_IS_TIME_MORE_THAN);
		NETWORK.set_function("IS_TIME_EQUAL_TO", LUA_NATIVE_NETWORK_IS_TIME_EQUAL_TO);
		NETWORK.set_function("GET_TIME_DIFFERENCE", LUA_NATIVE_NETWORK_GET_TIME_DIFFERENCE);
		NETWORK.set_function("GET_TIME_AS_STRING", LUA_NATIVE_NETWORK_GET_TIME_AS_STRING);
		NETWORK.set_function("GET_CLOUD_TIME_AS_STRING", LUA_NATIVE_NETWORK_GET_CLOUD_TIME_AS_STRING);
		NETWORK.set_function("GET_CLOUD_TIME_AS_INT", LUA_NATIVE_NETWORK_GET_CLOUD_TIME_AS_INT);
		NETWORK.set_function("CONVERT_POSIX_TIME", LUA_NATIVE_NETWORK_CONVERT_POSIX_TIME);
		NETWORK.set_function("NETWORK_SET_IN_SPECTATOR_MODE", LUA_NATIVE_NETWORK_NETWORK_SET_IN_SPECTATOR_MODE);
		NETWORK.set_function("NETWORK_SET_IN_SPECTATOR_MODE_EXTENDED", LUA_NATIVE_NETWORK_NETWORK_SET_IN_SPECTATOR_MODE_EXTENDED);
		NETWORK.set_function("NETWORK_SET_IN_FREE_CAM_MODE", LUA_NATIVE_NETWORK_NETWORK_SET_IN_FREE_CAM_MODE);
		NETWORK.set_function("NETWORK_SET_ANTAGONISTIC_TO_PLAYER", LUA_NATIVE_NETWORK_NETWORK_SET_ANTAGONISTIC_TO_PLAYER);
		NETWORK.set_function("NETWORK_IS_IN_SPECTATOR_MODE", LUA_NATIVE_NETWORK_NETWORK_IS_IN_SPECTATOR_MODE);
		NETWORK.set_function("NETWORK_SET_IN_MP_CUTSCENE", LUA_NATIVE_NETWORK_NETWORK_SET_IN_MP_CUTSCENE);
		NETWORK.set_function("NETWORK_IS_IN_MP_CUTSCENE", LUA_NATIVE_NETWORK_NETWORK_IS_IN_MP_CUTSCENE);
		NETWORK.set_function("NETWORK_IS_PLAYER_IN_MP_CUTSCENE", LUA_NATIVE_NETWORK_NETWORK_IS_PLAYER_IN_MP_CUTSCENE);
		NETWORK.set_function("NETWORK_HIDE_PROJECTILE_IN_CUTSCENE", LUA_NATIVE_NETWORK_NETWORK_HIDE_PROJECTILE_IN_CUTSCENE);
		NETWORK.set_function("SET_NETWORK_VEHICLE_RESPOT_TIMER", LUA_NATIVE_NETWORK_SET_NETWORK_VEHICLE_RESPOT_TIMER);
		NETWORK.set_function("IS_NETWORK_VEHICLE_RUNNING_RESPOT_TIMER", LUA_NATIVE_NETWORK_IS_NETWORK_VEHICLE_RUNNING_RESPOT_TIMER);
		NETWORK.set_function("SET_NETWORK_VEHICLE_AS_GHOST", LUA_NATIVE_NETWORK_SET_NETWORK_VEHICLE_AS_GHOST);
		NETWORK.set_function("SET_NETWORK_VEHICLE_MAX_POSITION_DELTA_MULTIPLIER", LUA_NATIVE_NETWORK_SET_NETWORK_VEHICLE_MAX_POSITION_DELTA_MULTIPLIER);
		NETWORK.set_function("SET_NETWORK_ENABLE_HIGH_SPEED_EDGE_FALL_DETECTION", LUA_NATIVE_NETWORK_SET_NETWORK_ENABLE_HIGH_SPEED_EDGE_FALL_DETECTION);
		NETWORK.set_function("SET_LOCAL_PLAYER_AS_GHOST", LUA_NATIVE_NETWORK_SET_LOCAL_PLAYER_AS_GHOST);
		NETWORK.set_function("IS_ENTITY_A_GHOST", LUA_NATIVE_NETWORK_IS_ENTITY_A_GHOST);
		NETWORK.set_function("SET_NON_PARTICIPANTS_OF_THIS_SCRIPT_AS_GHOSTS", LUA_NATIVE_NETWORK_SET_NON_PARTICIPANTS_OF_THIS_SCRIPT_AS_GHOSTS);
		NETWORK.set_function("SET_REMOTE_PLAYER_AS_GHOST", LUA_NATIVE_NETWORK_SET_REMOTE_PLAYER_AS_GHOST);
		NETWORK.set_function("SET_GHOST_ALPHA", LUA_NATIVE_NETWORK_SET_GHOST_ALPHA);
		NETWORK.set_function("RESET_GHOST_ALPHA", LUA_NATIVE_NETWORK_RESET_GHOST_ALPHA);
		NETWORK.set_function("SET_ENTITY_GHOSTED_FOR_GHOST_PLAYERS", LUA_NATIVE_NETWORK_SET_ENTITY_GHOSTED_FOR_GHOST_PLAYERS);
		NETWORK.set_function("SET_INVERT_GHOSTING", LUA_NATIVE_NETWORK_SET_INVERT_GHOSTING);
		NETWORK.set_function("IS_ENTITY_IN_GHOST_COLLISION", LUA_NATIVE_NETWORK_IS_ENTITY_IN_GHOST_COLLISION);
		NETWORK.set_function("USE_PLAYER_COLOUR_INSTEAD_OF_TEAM_COLOUR", LUA_NATIVE_NETWORK_USE_PLAYER_COLOUR_INSTEAD_OF_TEAM_COLOUR);
		NETWORK.set_function("NETWORK_CREATE_SYNCHRONISED_SCENE", LUA_NATIVE_NETWORK_NETWORK_CREATE_SYNCHRONISED_SCENE);
		NETWORK.set_function("NETWORK_ADD_PED_TO_SYNCHRONISED_SCENE", LUA_NATIVE_NETWORK_NETWORK_ADD_PED_TO_SYNCHRONISED_SCENE);
		NETWORK.set_function("NETWORK_ADD_PED_TO_SYNCHRONISED_SCENE_WITH_IK", LUA_NATIVE_NETWORK_NETWORK_ADD_PED_TO_SYNCHRONISED_SCENE_WITH_IK);
		NETWORK.set_function("NETWORK_ADD_ENTITY_TO_SYNCHRONISED_SCENE", LUA_NATIVE_NETWORK_NETWORK_ADD_ENTITY_TO_SYNCHRONISED_SCENE);
		NETWORK.set_function("NETWORK_ADD_MAP_ENTITY_TO_SYNCHRONISED_SCENE", LUA_NATIVE_NETWORK_NETWORK_ADD_MAP_ENTITY_TO_SYNCHRONISED_SCENE);
		NETWORK.set_function("NETWORK_ADD_SYNCHRONISED_SCENE_CAMERA", LUA_NATIVE_NETWORK_NETWORK_ADD_SYNCHRONISED_SCENE_CAMERA);
		NETWORK.set_function("NETWORK_ATTACH_SYNCHRONISED_SCENE_TO_ENTITY", LUA_NATIVE_NETWORK_NETWORK_ATTACH_SYNCHRONISED_SCENE_TO_ENTITY);
		NETWORK.set_function("NETWORK_START_SYNCHRONISED_SCENE", LUA_NATIVE_NETWORK_NETWORK_START_SYNCHRONISED_SCENE);
		NETWORK.set_function("NETWORK_STOP_SYNCHRONISED_SCENE", LUA_NATIVE_NETWORK_NETWORK_STOP_SYNCHRONISED_SCENE);
		NETWORK.set_function("NETWORK_GET_LOCAL_SCENE_FROM_NETWORK_ID", LUA_NATIVE_NETWORK_NETWORK_GET_LOCAL_SCENE_FROM_NETWORK_ID);
		NETWORK.set_function("NETWORK_FORCE_LOCAL_USE_OF_SYNCED_SCENE_CAMERA", LUA_NATIVE_NETWORK_NETWORK_FORCE_LOCAL_USE_OF_SYNCED_SCENE_CAMERA);
		NETWORK.set_function("NETWORK_ALLOW_REMOTE_SYNCED_SCENE_LOCAL_PLAYER_REQUESTS", LUA_NATIVE_NETWORK_NETWORK_ALLOW_REMOTE_SYNCED_SCENE_LOCAL_PLAYER_REQUESTS);
		NETWORK.set_function("NETWORK_FIND_LARGEST_BUNCH_OF_PLAYERS", LUA_NATIVE_NETWORK_NETWORK_FIND_LARGEST_BUNCH_OF_PLAYERS);
		NETWORK.set_function("NETWORK_START_RESPAWN_SEARCH_FOR_PLAYER", LUA_NATIVE_NETWORK_NETWORK_START_RESPAWN_SEARCH_FOR_PLAYER);
		NETWORK.set_function("NETWORK_START_RESPAWN_SEARCH_IN_ANGLED_AREA_FOR_PLAYER", LUA_NATIVE_NETWORK_NETWORK_START_RESPAWN_SEARCH_IN_ANGLED_AREA_FOR_PLAYER);
		NETWORK.set_function("NETWORK_QUERY_RESPAWN_RESULTS", LUA_NATIVE_NETWORK_NETWORK_QUERY_RESPAWN_RESULTS);
		NETWORK.set_function("NETWORK_CANCEL_RESPAWN_SEARCH", LUA_NATIVE_NETWORK_NETWORK_CANCEL_RESPAWN_SEARCH);
		NETWORK.set_function("NETWORK_GET_RESPAWN_RESULT", LUA_NATIVE_NETWORK_NETWORK_GET_RESPAWN_RESULT);
		NETWORK.set_function("NETWORK_GET_RESPAWN_RESULT_FLAGS", LUA_NATIVE_NETWORK_NETWORK_GET_RESPAWN_RESULT_FLAGS);
		NETWORK.set_function("NETWORK_START_SOLO_TUTORIAL_SESSION", LUA_NATIVE_NETWORK_NETWORK_START_SOLO_TUTORIAL_SESSION);
		NETWORK.set_function("NETWORK_ALLOW_GANG_TO_JOIN_TUTORIAL_SESSION", LUA_NATIVE_NETWORK_NETWORK_ALLOW_GANG_TO_JOIN_TUTORIAL_SESSION);
		NETWORK.set_function("NETWORK_END_TUTORIAL_SESSION", LUA_NATIVE_NETWORK_NETWORK_END_TUTORIAL_SESSION);
		NETWORK.set_function("NETWORK_IS_IN_TUTORIAL_SESSION", LUA_NATIVE_NETWORK_NETWORK_IS_IN_TUTORIAL_SESSION);
		NETWORK.set_function("NETWORK_WAITING_POP_CLEAR_TUTORIAL_SESSION", LUA_NATIVE_NETWORK_NETWORK_WAITING_POP_CLEAR_TUTORIAL_SESSION);
		NETWORK.set_function("NETWORK_IS_TUTORIAL_SESSION_CHANGE_PENDING", LUA_NATIVE_NETWORK_NETWORK_IS_TUTORIAL_SESSION_CHANGE_PENDING);
		NETWORK.set_function("NETWORK_GET_PLAYER_TUTORIAL_SESSION_INSTANCE", LUA_NATIVE_NETWORK_NETWORK_GET_PLAYER_TUTORIAL_SESSION_INSTANCE);
		NETWORK.set_function("NETWORK_ARE_PLAYERS_IN_SAME_TUTORIAL_SESSION", LUA_NATIVE_NETWORK_NETWORK_ARE_PLAYERS_IN_SAME_TUTORIAL_SESSION);
		NETWORK.set_function("NETWORK_BLOCK_PROXY_MIGRATION_BETWEEN_TUTORIAL_SESSIONS", LUA_NATIVE_NETWORK_NETWORK_BLOCK_PROXY_MIGRATION_BETWEEN_TUTORIAL_SESSIONS);
		NETWORK.set_function("NETWORK_CONCEAL_PLAYER", LUA_NATIVE_NETWORK_NETWORK_CONCEAL_PLAYER);
		NETWORK.set_function("NETWORK_IS_PLAYER_CONCEALED", LUA_NATIVE_NETWORK_NETWORK_IS_PLAYER_CONCEALED);
		NETWORK.set_function("NETWORK_CONCEAL_ENTITY", LUA_NATIVE_NETWORK_NETWORK_CONCEAL_ENTITY);
		NETWORK.set_function("NETWORK_IS_ENTITY_CONCEALED", LUA_NATIVE_NETWORK_NETWORK_IS_ENTITY_CONCEALED);
		NETWORK.set_function("NETWORK_OVERRIDE_CLOCK_TIME", LUA_NATIVE_NETWORK_NETWORK_OVERRIDE_CLOCK_TIME);
		NETWORK.set_function("NETWORK_OVERRIDE_CLOCK_RATE", LUA_NATIVE_NETWORK_NETWORK_OVERRIDE_CLOCK_RATE);
		NETWORK.set_function("NETWORK_CLEAR_CLOCK_TIME_OVERRIDE", LUA_NATIVE_NETWORK_NETWORK_CLEAR_CLOCK_TIME_OVERRIDE);
		NETWORK.set_function("NETWORK_IS_CLOCK_TIME_OVERRIDDEN", LUA_NATIVE_NETWORK_NETWORK_IS_CLOCK_TIME_OVERRIDDEN);
		NETWORK.set_function("NETWORK_ADD_ENTITY_AREA", LUA_NATIVE_NETWORK_NETWORK_ADD_ENTITY_AREA);
		NETWORK.set_function("NETWORK_ADD_ENTITY_ANGLED_AREA", LUA_NATIVE_NETWORK_NETWORK_ADD_ENTITY_ANGLED_AREA);
		NETWORK.set_function("NETWORK_ADD_CLIENT_ENTITY_AREA", LUA_NATIVE_NETWORK_NETWORK_ADD_CLIENT_ENTITY_AREA);
		NETWORK.set_function("NETWORK_ADD_CLIENT_ENTITY_ANGLED_AREA", LUA_NATIVE_NETWORK_NETWORK_ADD_CLIENT_ENTITY_ANGLED_AREA);
		NETWORK.set_function("NETWORK_REMOVE_ENTITY_AREA", LUA_NATIVE_NETWORK_NETWORK_REMOVE_ENTITY_AREA);
		NETWORK.set_function("NETWORK_ENTITY_AREA_DOES_EXIST", LUA_NATIVE_NETWORK_NETWORK_ENTITY_AREA_DOES_EXIST);
		NETWORK.set_function("NETWORK_ENTITY_AREA_HAVE_ALL_REPLIED", LUA_NATIVE_NETWORK_NETWORK_ENTITY_AREA_HAVE_ALL_REPLIED);
		NETWORK.set_function("NETWORK_ENTITY_AREA_IS_OCCUPIED", LUA_NATIVE_NETWORK_NETWORK_ENTITY_AREA_IS_OCCUPIED);
		NETWORK.set_function("NETWORK_USE_HIGH_PRECISION_BLENDING", LUA_NATIVE_NETWORK_NETWORK_USE_HIGH_PRECISION_BLENDING);
		NETWORK.set_function("NETWORK_SET_CUSTOM_ARENA_BALL_PARAMS", LUA_NATIVE_NETWORK_NETWORK_SET_CUSTOM_ARENA_BALL_PARAMS);
		NETWORK.set_function("NETWORK_ENTITY_USE_HIGH_PRECISION_ROTATION", LUA_NATIVE_NETWORK_NETWORK_ENTITY_USE_HIGH_PRECISION_ROTATION);
		NETWORK.set_function("NETWORK_REQUEST_CLOUD_BACKGROUND_SCRIPTS", LUA_NATIVE_NETWORK_NETWORK_REQUEST_CLOUD_BACKGROUND_SCRIPTS);
		NETWORK.set_function("NETWORK_IS_CLOUD_BACKGROUND_SCRIPT_REQUEST_PENDING", LUA_NATIVE_NETWORK_NETWORK_IS_CLOUD_BACKGROUND_SCRIPT_REQUEST_PENDING);
		NETWORK.set_function("NETWORK_REQUEST_CLOUD_TUNABLES", LUA_NATIVE_NETWORK_NETWORK_REQUEST_CLOUD_TUNABLES);
		NETWORK.set_function("NETWORK_IS_TUNABLE_CLOUD_REQUEST_PENDING", LUA_NATIVE_NETWORK_NETWORK_IS_TUNABLE_CLOUD_REQUEST_PENDING);
		NETWORK.set_function("NETWORK_GET_TUNABLE_CLOUD_CRC", LUA_NATIVE_NETWORK_NETWORK_GET_TUNABLE_CLOUD_CRC);
		NETWORK.set_function("NETWORK_DOES_TUNABLE_EXIST", LUA_NATIVE_NETWORK_NETWORK_DOES_TUNABLE_EXIST);
		NETWORK.set_function("NETWORK_ACCESS_TUNABLE_INT", LUA_NATIVE_NETWORK_NETWORK_ACCESS_TUNABLE_INT);
		NETWORK.set_function("NETWORK_ACCESS_TUNABLE_FLOAT", LUA_NATIVE_NETWORK_NETWORK_ACCESS_TUNABLE_FLOAT);
		NETWORK.set_function("NETWORK_ACCESS_TUNABLE_BOOL", LUA_NATIVE_NETWORK_NETWORK_ACCESS_TUNABLE_BOOL);
		NETWORK.set_function("NETWORK_DOES_TUNABLE_EXIST_HASH", LUA_NATIVE_NETWORK_NETWORK_DOES_TUNABLE_EXIST_HASH);
		NETWORK.set_function("NETWORK_ACCESS_TUNABLE_MODIFICATION_DETECTION_CLEAR", LUA_NATIVE_NETWORK_NETWORK_ACCESS_TUNABLE_MODIFICATION_DETECTION_CLEAR);
		NETWORK.set_function("NETWORK_ACCESS_TUNABLE_INT_HASH", LUA_NATIVE_NETWORK_NETWORK_ACCESS_TUNABLE_INT_HASH);
		NETWORK.set_function("NETWORK_ACCESS_TUNABLE_INT_MODIFICATION_DETECTION_REGISTRATION_HASH", LUA_NATIVE_NETWORK_NETWORK_ACCESS_TUNABLE_INT_MODIFICATION_DETECTION_REGISTRATION_HASH);
		NETWORK.set_function("NETWORK_ACCESS_TUNABLE_FLOAT_HASH", LUA_NATIVE_NETWORK_NETWORK_ACCESS_TUNABLE_FLOAT_HASH);
		NETWORK.set_function("NETWORK_ACCESS_TUNABLE_FLOAT_MODIFICATION_DETECTION_REGISTRATION_HASH", LUA_NATIVE_NETWORK_NETWORK_ACCESS_TUNABLE_FLOAT_MODIFICATION_DETECTION_REGISTRATION_HASH);
		NETWORK.set_function("NETWORK_ACCESS_TUNABLE_BOOL_HASH", LUA_NATIVE_NETWORK_NETWORK_ACCESS_TUNABLE_BOOL_HASH);
		NETWORK.set_function("NETWORK_ACCESS_TUNABLE_BOOL_MODIFICATION_DETECTION_REGISTRATION_HASH", LUA_NATIVE_NETWORK_NETWORK_ACCESS_TUNABLE_BOOL_MODIFICATION_DETECTION_REGISTRATION_HASH);
		NETWORK.set_function("NETWORK_TRY_ACCESS_TUNABLE_BOOL_HASH", LUA_NATIVE_NETWORK_NETWORK_TRY_ACCESS_TUNABLE_BOOL_HASH);
		NETWORK.set_function("NETWORK_GET_CONTENT_MODIFIER_LIST_ID", LUA_NATIVE_NETWORK_NETWORK_GET_CONTENT_MODIFIER_LIST_ID);
		NETWORK.set_function("NETWORK_GET_BONE_ID_OF_FATAL_HIT", LUA_NATIVE_NETWORK_NETWORK_GET_BONE_ID_OF_FATAL_HIT);
		NETWORK.set_function("NETWORK_RESET_BODY_TRACKER", LUA_NATIVE_NETWORK_NETWORK_RESET_BODY_TRACKER);
		NETWORK.set_function("NETWORK_GET_NUMBER_BODY_TRACKER_HITS", LUA_NATIVE_NETWORK_NETWORK_GET_NUMBER_BODY_TRACKER_HITS);
		NETWORK.set_function("NETWORK_HAS_BONE_BEEN_HIT_BY_KILLER", LUA_NATIVE_NETWORK_NETWORK_HAS_BONE_BEEN_HIT_BY_KILLER);
		NETWORK.set_function("NETWORK_SET_ATTRIBUTE_DAMAGE_TO_PLAYER", LUA_NATIVE_NETWORK_NETWORK_SET_ATTRIBUTE_DAMAGE_TO_PLAYER);
		NETWORK.set_function("NETWORK_TRIGGER_DAMAGE_EVENT_FOR_ZERO_DAMAGE", LUA_NATIVE_NETWORK_NETWORK_TRIGGER_DAMAGE_EVENT_FOR_ZERO_DAMAGE);
		NETWORK.set_function("NETWORK_TRIGGER_DAMAGE_EVENT_FOR_ZERO_WEAPON_HASH", LUA_NATIVE_NETWORK_NETWORK_TRIGGER_DAMAGE_EVENT_FOR_ZERO_WEAPON_HASH);
		NETWORK.set_function("NETWORK_SET_NO_LONGER_NEEDED", LUA_NATIVE_NETWORK_NETWORK_SET_NO_LONGER_NEEDED);
		NETWORK.set_function("NETWORK_EXPLODE_VEHICLE", LUA_NATIVE_NETWORK_NETWORK_EXPLODE_VEHICLE);
		NETWORK.set_function("NETWORK_EXPLODE_HELI", LUA_NATIVE_NETWORK_NETWORK_EXPLODE_HELI);
		NETWORK.set_function("NETWORK_USE_LOGARITHMIC_BLENDING_THIS_FRAME", LUA_NATIVE_NETWORK_NETWORK_USE_LOGARITHMIC_BLENDING_THIS_FRAME);
		NETWORK.set_function("NETWORK_OVERRIDE_COORDS_AND_HEADING", LUA_NATIVE_NETWORK_NETWORK_OVERRIDE_COORDS_AND_HEADING);
		NETWORK.set_function("NETWORK_ENABLE_EXTRA_VEHICLE_ORIENTATION_BLEND_CHECKS", LUA_NATIVE_NETWORK_NETWORK_ENABLE_EXTRA_VEHICLE_ORIENTATION_BLEND_CHECKS);
		NETWORK.set_function("NETWORK_DISABLE_PROXIMITY_MIGRATION", LUA_NATIVE_NETWORK_NETWORK_DISABLE_PROXIMITY_MIGRATION);
		NETWORK.set_function("NETWORK_SET_PROPERTY_ID", LUA_NATIVE_NETWORK_NETWORK_SET_PROPERTY_ID);
		NETWORK.set_function("NETWORK_CLEAR_PROPERTY_ID", LUA_NATIVE_NETWORK_NETWORK_CLEAR_PROPERTY_ID);
		NETWORK.set_function("NETWORK_SET_PLAYER_MENTAL_STATE", LUA_NATIVE_NETWORK_NETWORK_SET_PLAYER_MENTAL_STATE);
		NETWORK.set_function("NETWORK_SET_MINIMUM_RANK_FOR_MISSION", LUA_NATIVE_NETWORK_NETWORK_SET_MINIMUM_RANK_FOR_MISSION);
		NETWORK.set_function("NETWORK_CACHE_LOCAL_PLAYER_HEAD_BLEND_DATA", LUA_NATIVE_NETWORK_NETWORK_CACHE_LOCAL_PLAYER_HEAD_BLEND_DATA);
		NETWORK.set_function("NETWORK_HAS_CACHED_PLAYER_HEAD_BLEND_DATA", LUA_NATIVE_NETWORK_NETWORK_HAS_CACHED_PLAYER_HEAD_BLEND_DATA);
		NETWORK.set_function("NETWORK_APPLY_CACHED_PLAYER_HEAD_BLEND_DATA", LUA_NATIVE_NETWORK_NETWORK_APPLY_CACHED_PLAYER_HEAD_BLEND_DATA);
		NETWORK.set_function("GET_NUM_COMMERCE_ITEMS", LUA_NATIVE_NETWORK_GET_NUM_COMMERCE_ITEMS);
		NETWORK.set_function("IS_COMMERCE_DATA_VALID", LUA_NATIVE_NETWORK_IS_COMMERCE_DATA_VALID);
		NETWORK.set_function("TRIGGER_COMMERCE_DATA_FETCH", LUA_NATIVE_NETWORK_TRIGGER_COMMERCE_DATA_FETCH);
		NETWORK.set_function("IS_COMMERCE_DATA_FETCH_IN_PROGRESS", LUA_NATIVE_NETWORK_IS_COMMERCE_DATA_FETCH_IN_PROGRESS);
		NETWORK.set_function("GET_COMMERCE_ITEM_ID", LUA_NATIVE_NETWORK_GET_COMMERCE_ITEM_ID);
		NETWORK.set_function("GET_COMMERCE_ITEM_NAME", LUA_NATIVE_NETWORK_GET_COMMERCE_ITEM_NAME);
		NETWORK.set_function("GET_COMMERCE_PRODUCT_PRICE", LUA_NATIVE_NETWORK_GET_COMMERCE_PRODUCT_PRICE);
		NETWORK.set_function("GET_COMMERCE_ITEM_NUM_CATS", LUA_NATIVE_NETWORK_GET_COMMERCE_ITEM_NUM_CATS);
		NETWORK.set_function("GET_COMMERCE_ITEM_CAT", LUA_NATIVE_NETWORK_GET_COMMERCE_ITEM_CAT);
		NETWORK.set_function("OPEN_COMMERCE_STORE", LUA_NATIVE_NETWORK_OPEN_COMMERCE_STORE);
		NETWORK.set_function("IS_COMMERCE_STORE_OPEN", LUA_NATIVE_NETWORK_IS_COMMERCE_STORE_OPEN);
		NETWORK.set_function("SET_STORE_ENABLED", LUA_NATIVE_NETWORK_SET_STORE_ENABLED);
		NETWORK.set_function("REQUEST_COMMERCE_ITEM_IMAGE", LUA_NATIVE_NETWORK_REQUEST_COMMERCE_ITEM_IMAGE);
		NETWORK.set_function("RELEASE_ALL_COMMERCE_ITEM_IMAGES", LUA_NATIVE_NETWORK_RELEASE_ALL_COMMERCE_ITEM_IMAGES);
		NETWORK.set_function("GET_COMMERCE_ITEM_TEXTURENAME", LUA_NATIVE_NETWORK_GET_COMMERCE_ITEM_TEXTURENAME);
		NETWORK.set_function("IS_STORE_AVAILABLE_TO_USER", LUA_NATIVE_NETWORK_IS_STORE_AVAILABLE_TO_USER);
		NETWORK.set_function("DELAY_MP_STORE_OPEN", LUA_NATIVE_NETWORK_DELAY_MP_STORE_OPEN);
		NETWORK.set_function("RESET_STORE_NETWORK_GAME_TRACKING", LUA_NATIVE_NETWORK_RESET_STORE_NETWORK_GAME_TRACKING);
		NETWORK.set_function("IS_USER_OLD_ENOUGH_TO_ACCESS_STORE", LUA_NATIVE_NETWORK_IS_USER_OLD_ENOUGH_TO_ACCESS_STORE);
		NETWORK.set_function("SET_LAST_VIEWED_SHOP_ITEM", LUA_NATIVE_NETWORK_SET_LAST_VIEWED_SHOP_ITEM);
		NETWORK.set_function("GET_USER_PREMIUM_ACCESS", LUA_NATIVE_NETWORK_GET_USER_PREMIUM_ACCESS);
		NETWORK.set_function("GET_USER_STARTER_ACCESS", LUA_NATIVE_NETWORK_GET_USER_STARTER_ACCESS);
		NETWORK.set_function("CLOUD_DELETE_MEMBER_FILE", LUA_NATIVE_NETWORK_CLOUD_DELETE_MEMBER_FILE);
		NETWORK.set_function("CLOUD_HAS_REQUEST_COMPLETED", LUA_NATIVE_NETWORK_CLOUD_HAS_REQUEST_COMPLETED);
		NETWORK.set_function("CLOUD_DID_REQUEST_SUCCEED", LUA_NATIVE_NETWORK_CLOUD_DID_REQUEST_SUCCEED);
		NETWORK.set_function("CLOUD_CHECK_AVAILABILITY", LUA_NATIVE_NETWORK_CLOUD_CHECK_AVAILABILITY);
		NETWORK.set_function("CLOUD_IS_CHECKING_AVAILABILITY", LUA_NATIVE_NETWORK_CLOUD_IS_CHECKING_AVAILABILITY);
		NETWORK.set_function("CLOUD_GET_AVAILABILITY_CHECK_RESULT", LUA_NATIVE_NETWORK_CLOUD_GET_AVAILABILITY_CHECK_RESULT);
		NETWORK.set_function("GET_CONTENT_TO_LOAD_TYPE", LUA_NATIVE_NETWORK_GET_CONTENT_TO_LOAD_TYPE);
		NETWORK.set_function("GET_IS_LAUNCH_FROM_LIVE_AREA", LUA_NATIVE_NETWORK_GET_IS_LAUNCH_FROM_LIVE_AREA);
		NETWORK.set_function("GET_IS_LIVE_AREA_LAUNCH_WITH_CONTENT", LUA_NATIVE_NETWORK_GET_IS_LIVE_AREA_LAUNCH_WITH_CONTENT);
		NETWORK.set_function("CLEAR_SERVICE_EVENT_ARGUMENTS", LUA_NATIVE_NETWORK_CLEAR_SERVICE_EVENT_ARGUMENTS);
		NETWORK.set_function("UGC_COPY_CONTENT", LUA_NATIVE_NETWORK_UGC_COPY_CONTENT);
		NETWORK.set_function("UGC_IS_CREATING", LUA_NATIVE_NETWORK_UGC_IS_CREATING);
		NETWORK.set_function("UGC_HAS_CREATE_FINISHED", LUA_NATIVE_NETWORK_UGC_HAS_CREATE_FINISHED);
		NETWORK.set_function("UGC_DID_CREATE_SUCCEED", LUA_NATIVE_NETWORK_UGC_DID_CREATE_SUCCEED);
		NETWORK.set_function("UGC_GET_CREATE_RESULT", LUA_NATIVE_NETWORK_UGC_GET_CREATE_RESULT);
		NETWORK.set_function("UGC_GET_CREATE_CONTENT_ID", LUA_NATIVE_NETWORK_UGC_GET_CREATE_CONTENT_ID);
		NETWORK.set_function("UGC_CLEAR_CREATE_RESULT", LUA_NATIVE_NETWORK_UGC_CLEAR_CREATE_RESULT);
		NETWORK.set_function("UGC_QUERY_MY_CONTENT", LUA_NATIVE_NETWORK_UGC_QUERY_MY_CONTENT);
		NETWORK.set_function("UGC_QUERY_BY_CATEGORY", LUA_NATIVE_NETWORK_UGC_QUERY_BY_CATEGORY);
		NETWORK.set_function("UGC_QUERY_BY_CONTENT_ID", LUA_NATIVE_NETWORK_UGC_QUERY_BY_CONTENT_ID);
		NETWORK.set_function("UGC_QUERY_BY_CONTENT_IDS", LUA_NATIVE_NETWORK_UGC_QUERY_BY_CONTENT_IDS);
		NETWORK.set_function("UGC_QUERY_MOST_RECENTLY_CREATED_CONTENT", LUA_NATIVE_NETWORK_UGC_QUERY_MOST_RECENTLY_CREATED_CONTENT);
		NETWORK.set_function("UGC_GET_BOOKMARKED_CONTENT", LUA_NATIVE_NETWORK_UGC_GET_BOOKMARKED_CONTENT);
		NETWORK.set_function("UGC_GET_MY_CONTENT", LUA_NATIVE_NETWORK_UGC_GET_MY_CONTENT);
		NETWORK.set_function("UGC_GET_FRIEND_CONTENT", LUA_NATIVE_NETWORK_UGC_GET_FRIEND_CONTENT);
		NETWORK.set_function("UGC_GET_CREW_CONTENT", LUA_NATIVE_NETWORK_UGC_GET_CREW_CONTENT);
		NETWORK.set_function("UGC_GET_GET_BY_CATEGORY", LUA_NATIVE_NETWORK_UGC_GET_GET_BY_CATEGORY);
		NETWORK.set_function("UGC_GET_GET_BY_CONTENT_ID", LUA_NATIVE_NETWORK_UGC_GET_GET_BY_CONTENT_ID);
		NETWORK.set_function("UGC_GET_GET_BY_CONTENT_IDS", LUA_NATIVE_NETWORK_UGC_GET_GET_BY_CONTENT_IDS);
		NETWORK.set_function("UGC_GET_MOST_RECENTLY_CREATED_CONTENT", LUA_NATIVE_NETWORK_UGC_GET_MOST_RECENTLY_CREATED_CONTENT);
		NETWORK.set_function("UGC_GET_MOST_RECENTLY_PLAYED_CONTENT", LUA_NATIVE_NETWORK_UGC_GET_MOST_RECENTLY_PLAYED_CONTENT);
		NETWORK.set_function("UGC_GET_TOP_RATED_CONTENT", LUA_NATIVE_NETWORK_UGC_GET_TOP_RATED_CONTENT);
		NETWORK.set_function("UGC_CANCEL_QUERY", LUA_NATIVE_NETWORK_UGC_CANCEL_QUERY);
		NETWORK.set_function("UGC_IS_GETTING", LUA_NATIVE_NETWORK_UGC_IS_GETTING);
		NETWORK.set_function("UGC_HAS_GET_FINISHED", LUA_NATIVE_NETWORK_UGC_HAS_GET_FINISHED);
		NETWORK.set_function("UGC_DID_GET_SUCCEED", LUA_NATIVE_NETWORK_UGC_DID_GET_SUCCEED);
		NETWORK.set_function("UGC_WAS_QUERY_FORCE_CANCELLED", LUA_NATIVE_NETWORK_UGC_WAS_QUERY_FORCE_CANCELLED);
		NETWORK.set_function("UGC_GET_QUERY_RESULT", LUA_NATIVE_NETWORK_UGC_GET_QUERY_RESULT);
		NETWORK.set_function("UGC_GET_CONTENT_NUM", LUA_NATIVE_NETWORK_UGC_GET_CONTENT_NUM);
		NETWORK.set_function("UGC_GET_CONTENT_TOTAL", LUA_NATIVE_NETWORK_UGC_GET_CONTENT_TOTAL);
		NETWORK.set_function("UGC_GET_CONTENT_HASH", LUA_NATIVE_NETWORK_UGC_GET_CONTENT_HASH);
		NETWORK.set_function("UGC_CLEAR_QUERY_RESULTS", LUA_NATIVE_NETWORK_UGC_CLEAR_QUERY_RESULTS);
		NETWORK.set_function("UGC_GET_CONTENT_USER_ID", LUA_NATIVE_NETWORK_UGC_GET_CONTENT_USER_ID);
		NETWORK.set_function("UGC_GET_CONTENT_CREATOR_GAMER_HANDLE", LUA_NATIVE_NETWORK_UGC_GET_CONTENT_CREATOR_GAMER_HANDLE);
		NETWORK.set_function("UGC_GET_CONTENT_CREATED_BY_LOCAL_PLAYER", LUA_NATIVE_NETWORK_UGC_GET_CONTENT_CREATED_BY_LOCAL_PLAYER);
		NETWORK.set_function("UGC_GET_CONTENT_USER_NAME", LUA_NATIVE_NETWORK_UGC_GET_CONTENT_USER_NAME);
		NETWORK.set_function("UGC_GET_CONTENT_IS_USING_SC_NICKNAME", LUA_NATIVE_NETWORK_UGC_GET_CONTENT_IS_USING_SC_NICKNAME);
		NETWORK.set_function("UGC_GET_CONTENT_CATEGORY", LUA_NATIVE_NETWORK_UGC_GET_CONTENT_CATEGORY);
		NETWORK.set_function("UGC_GET_CONTENT_ID", LUA_NATIVE_NETWORK_UGC_GET_CONTENT_ID);
		NETWORK.set_function("UGC_GET_ROOT_CONTENT_ID", LUA_NATIVE_NETWORK_UGC_GET_ROOT_CONTENT_ID);
		NETWORK.set_function("UGC_GET_CONTENT_NAME", LUA_NATIVE_NETWORK_UGC_GET_CONTENT_NAME);
		NETWORK.set_function("UGC_GET_CONTENT_DESCRIPTION_HASH", LUA_NATIVE_NETWORK_UGC_GET_CONTENT_DESCRIPTION_HASH);
		NETWORK.set_function("UGC_GET_CONTENT_PATH", LUA_NATIVE_NETWORK_UGC_GET_CONTENT_PATH);
		NETWORK.set_function("UGC_GET_CONTENT_UPDATED_DATE", LUA_NATIVE_NETWORK_UGC_GET_CONTENT_UPDATED_DATE);
		NETWORK.set_function("UGC_GET_CONTENT_FILE_VERSION", LUA_NATIVE_NETWORK_UGC_GET_CONTENT_FILE_VERSION);
		NETWORK.set_function("UGC_GET_CONTENT_HAS_LO_RES_PHOTO", LUA_NATIVE_NETWORK_UGC_GET_CONTENT_HAS_LO_RES_PHOTO);
		NETWORK.set_function("UGC_GET_CONTENT_HAS_HI_RES_PHOTO", LUA_NATIVE_NETWORK_UGC_GET_CONTENT_HAS_HI_RES_PHOTO);
		NETWORK.set_function("UGC_GET_CONTENT_LANGUAGE", LUA_NATIVE_NETWORK_UGC_GET_CONTENT_LANGUAGE);
		NETWORK.set_function("UGC_GET_CONTENT_IS_PUBLISHED", LUA_NATIVE_NETWORK_UGC_GET_CONTENT_IS_PUBLISHED);
		NETWORK.set_function("UGC_GET_CONTENT_IS_VERIFIED", LUA_NATIVE_NETWORK_UGC_GET_CONTENT_IS_VERIFIED);
		NETWORK.set_function("UGC_GET_CONTENT_RATING", LUA_NATIVE_NETWORK_UGC_GET_CONTENT_RATING);
		NETWORK.set_function("UGC_GET_CONTENT_RATING_COUNT", LUA_NATIVE_NETWORK_UGC_GET_CONTENT_RATING_COUNT);
		NETWORK.set_function("UGC_GET_CONTENT_RATING_POSITIVE_COUNT", LUA_NATIVE_NETWORK_UGC_GET_CONTENT_RATING_POSITIVE_COUNT);
		NETWORK.set_function("UGC_GET_CONTENT_RATING_NEGATIVE_COUNT", LUA_NATIVE_NETWORK_UGC_GET_CONTENT_RATING_NEGATIVE_COUNT);
		NETWORK.set_function("UGC_GET_CONTENT_HAS_PLAYER_RECORD", LUA_NATIVE_NETWORK_UGC_GET_CONTENT_HAS_PLAYER_RECORD);
		NETWORK.set_function("UGC_GET_CONTENT_HAS_PLAYER_BOOKMARKED", LUA_NATIVE_NETWORK_UGC_GET_CONTENT_HAS_PLAYER_BOOKMARKED);
		NETWORK.set_function("UGC_REQUEST_CONTENT_DATA_FROM_INDEX", LUA_NATIVE_NETWORK_UGC_REQUEST_CONTENT_DATA_FROM_INDEX);
		NETWORK.set_function("UGC_REQUEST_CONTENT_DATA_FROM_PARAMS", LUA_NATIVE_NETWORK_UGC_REQUEST_CONTENT_DATA_FROM_PARAMS);
		NETWORK.set_function("UGC_REQUEST_CACHED_DESCRIPTION", LUA_NATIVE_NETWORK_UGC_REQUEST_CACHED_DESCRIPTION);
		NETWORK.set_function("UGC_IS_DESCRIPTION_REQUEST_IN_PROGRESS", LUA_NATIVE_NETWORK_UGC_IS_DESCRIPTION_REQUEST_IN_PROGRESS);
		NETWORK.set_function("UGC_HAS_DESCRIPTION_REQUEST_FINISHED", LUA_NATIVE_NETWORK_UGC_HAS_DESCRIPTION_REQUEST_FINISHED);
		NETWORK.set_function("UGC_DID_DESCRIPTION_REQUEST_SUCCEED", LUA_NATIVE_NETWORK_UGC_DID_DESCRIPTION_REQUEST_SUCCEED);
		NETWORK.set_function("UGC_GET_CACHED_DESCRIPTION", LUA_NATIVE_NETWORK_UGC_GET_CACHED_DESCRIPTION);
		NETWORK.set_function("UGC_RELEASE_CACHED_DESCRIPTION", LUA_NATIVE_NETWORK_UGC_RELEASE_CACHED_DESCRIPTION);
		NETWORK.set_function("UGC_RELEASE_ALL_CACHED_DESCRIPTIONS", LUA_NATIVE_NETWORK_UGC_RELEASE_ALL_CACHED_DESCRIPTIONS);
		NETWORK.set_function("UGC_PUBLISH", LUA_NATIVE_NETWORK_UGC_PUBLISH);
		NETWORK.set_function("UGC_SET_BOOKMARKED", LUA_NATIVE_NETWORK_UGC_SET_BOOKMARKED);
		NETWORK.set_function("UGC_SET_DELETED", LUA_NATIVE_NETWORK_UGC_SET_DELETED);
		NETWORK.set_function("UGC_IS_MODIFYING", LUA_NATIVE_NETWORK_UGC_IS_MODIFYING);
		NETWORK.set_function("UGC_HAS_MODIFY_FINISHED", LUA_NATIVE_NETWORK_UGC_HAS_MODIFY_FINISHED);
		NETWORK.set_function("UGC_DID_MODIFY_SUCCEED", LUA_NATIVE_NETWORK_UGC_DID_MODIFY_SUCCEED);
		NETWORK.set_function("UGC_GET_MODIFY_RESULT", LUA_NATIVE_NETWORK_UGC_GET_MODIFY_RESULT);
		NETWORK.set_function("UGC_CLEAR_MODIFY_RESULT", LUA_NATIVE_NETWORK_UGC_CLEAR_MODIFY_RESULT);
		NETWORK.set_function("UGC_GET_CREATORS_BY_USER_ID", LUA_NATIVE_NETWORK_UGC_GET_CREATORS_BY_USER_ID);
		NETWORK.set_function("UGC_HAS_QUERY_CREATORS_FINISHED", LUA_NATIVE_NETWORK_UGC_HAS_QUERY_CREATORS_FINISHED);
		NETWORK.set_function("UGC_DID_QUERY_CREATORS_SUCCEED", LUA_NATIVE_NETWORK_UGC_DID_QUERY_CREATORS_SUCCEED);
		NETWORK.set_function("UGC_GET_CREATOR_NUM", LUA_NATIVE_NETWORK_UGC_GET_CREATOR_NUM);
		NETWORK.set_function("UGC_LOAD_OFFLINE_QUERY", LUA_NATIVE_NETWORK_UGC_LOAD_OFFLINE_QUERY);
		NETWORK.set_function("UGC_CLEAR_OFFLINE_QUERY", LUA_NATIVE_NETWORK_UGC_CLEAR_OFFLINE_QUERY);
		NETWORK.set_function("UGC_SET_QUERY_DATA_FROM_OFFLINE", LUA_NATIVE_NETWORK_UGC_SET_QUERY_DATA_FROM_OFFLINE);
		NETWORK.set_function("UGC_SET_USING_OFFLINE_CONTENT", LUA_NATIVE_NETWORK_UGC_SET_USING_OFFLINE_CONTENT);
		NETWORK.set_function("UGC_IS_LANGUAGE_SUPPORTED", LUA_NATIVE_NETWORK_UGC_IS_LANGUAGE_SUPPORTED);
		NETWORK.set_function("FACEBOOK_POST_COMPLETED_HEIST", LUA_NATIVE_NETWORK_FACEBOOK_POST_COMPLETED_HEIST);
		NETWORK.set_function("FACEBOOK_POST_CREATE_CHARACTER", LUA_NATIVE_NETWORK_FACEBOOK_POST_CREATE_CHARACTER);
		NETWORK.set_function("FACEBOOK_POST_COMPLETED_MILESTONE", LUA_NATIVE_NETWORK_FACEBOOK_POST_COMPLETED_MILESTONE);
		NETWORK.set_function("FACEBOOK_HAS_POST_COMPLETED", LUA_NATIVE_NETWORK_FACEBOOK_HAS_POST_COMPLETED);
		NETWORK.set_function("FACEBOOK_DID_POST_SUCCEED", LUA_NATIVE_NETWORK_FACEBOOK_DID_POST_SUCCEED);
		NETWORK.set_function("FACEBOOK_CAN_POST_TO_FACEBOOK", LUA_NATIVE_NETWORK_FACEBOOK_CAN_POST_TO_FACEBOOK);
		NETWORK.set_function("TEXTURE_DOWNLOAD_REQUEST", LUA_NATIVE_NETWORK_TEXTURE_DOWNLOAD_REQUEST);
		NETWORK.set_function("TITLE_TEXTURE_DOWNLOAD_REQUEST", LUA_NATIVE_NETWORK_TITLE_TEXTURE_DOWNLOAD_REQUEST);
		NETWORK.set_function("UGC_TEXTURE_DOWNLOAD_REQUEST", LUA_NATIVE_NETWORK_UGC_TEXTURE_DOWNLOAD_REQUEST);
		NETWORK.set_function("TEXTURE_DOWNLOAD_RELEASE", LUA_NATIVE_NETWORK_TEXTURE_DOWNLOAD_RELEASE);
		NETWORK.set_function("TEXTURE_DOWNLOAD_HAS_FAILED", LUA_NATIVE_NETWORK_TEXTURE_DOWNLOAD_HAS_FAILED);
		NETWORK.set_function("TEXTURE_DOWNLOAD_GET_NAME", LUA_NATIVE_NETWORK_TEXTURE_DOWNLOAD_GET_NAME);
		NETWORK.set_function("GET_STATUS_OF_TEXTURE_DOWNLOAD", LUA_NATIVE_NETWORK_GET_STATUS_OF_TEXTURE_DOWNLOAD);
		NETWORK.set_function("NETWORK_CHECK_ROS_LINK_WENTDOWN_NOT_NET", LUA_NATIVE_NETWORK_NETWORK_CHECK_ROS_LINK_WENTDOWN_NOT_NET);
		NETWORK.set_function("NETWORK_SHOULD_SHOW_STRICT_NAT_WARNING", LUA_NATIVE_NETWORK_NETWORK_SHOULD_SHOW_STRICT_NAT_WARNING);
		NETWORK.set_function("NETWORK_IS_CABLE_CONNECTED", LUA_NATIVE_NETWORK_NETWORK_IS_CABLE_CONNECTED);
		NETWORK.set_function("NETWORK_HAVE_SCS_PRIVATE_MSG_PRIV", LUA_NATIVE_NETWORK_NETWORK_HAVE_SCS_PRIVATE_MSG_PRIV);
		NETWORK.set_function("NETWORK_HAVE_ROS_SOCIAL_CLUB_PRIV", LUA_NATIVE_NETWORK_NETWORK_HAVE_ROS_SOCIAL_CLUB_PRIV);
		NETWORK.set_function("NETWORK_HAVE_ROS_BANNED_PRIV", LUA_NATIVE_NETWORK_NETWORK_HAVE_ROS_BANNED_PRIV);
		NETWORK.set_function("NETWORK_HAVE_ROS_CREATE_TICKET_PRIV", LUA_NATIVE_NETWORK_NETWORK_HAVE_ROS_CREATE_TICKET_PRIV);
		NETWORK.set_function("NETWORK_HAVE_ROS_MULTIPLAYER_PRIV", LUA_NATIVE_NETWORK_NETWORK_HAVE_ROS_MULTIPLAYER_PRIV);
		NETWORK.set_function("NETWORK_HAVE_ROS_LEADERBOARD_WRITE_PRIV", LUA_NATIVE_NETWORK_NETWORK_HAVE_ROS_LEADERBOARD_WRITE_PRIV);
		NETWORK.set_function("NETWORK_HAS_ROS_PRIVILEGE", LUA_NATIVE_NETWORK_NETWORK_HAS_ROS_PRIVILEGE);
		NETWORK.set_function("NETWORK_HAS_ROS_PRIVILEGE_END_DATE", LUA_NATIVE_NETWORK_NETWORK_HAS_ROS_PRIVILEGE_END_DATE);
		NETWORK.set_function("NETWORK_HAS_ROS_PRIVILEGE_PLAYED_LAST_GEN", LUA_NATIVE_NETWORK_NETWORK_HAS_ROS_PRIVILEGE_PLAYED_LAST_GEN);
		NETWORK.set_function("NETWORK_HAS_ROS_PRIVILEGE_SPECIAL_EDITION_CONTENT", LUA_NATIVE_NETWORK_NETWORK_HAS_ROS_PRIVILEGE_SPECIAL_EDITION_CONTENT);
		NETWORK.set_function("NETWORK_START_COMMUNICATION_PERMISSIONS_CHECK", LUA_NATIVE_NETWORK_NETWORK_START_COMMUNICATION_PERMISSIONS_CHECK);
		NETWORK.set_function("NETWORK_START_USER_CONTENT_PERMISSIONS_CHECK", LUA_NATIVE_NETWORK_NETWORK_START_USER_CONTENT_PERMISSIONS_CHECK);
		NETWORK.set_function("NETWORK_SKIP_RADIO_RESET_NEXT_CLOSE", LUA_NATIVE_NETWORK_NETWORK_SKIP_RADIO_RESET_NEXT_CLOSE);
		NETWORK.set_function("NETWORK_SKIP_RADIO_RESET_NEXT_OPEN", LUA_NATIVE_NETWORK_NETWORK_SKIP_RADIO_RESET_NEXT_OPEN);
		NETWORK.set_function("NETWORK_SKIP_RADIO_WARNING", LUA_NATIVE_NETWORK_NETWORK_SKIP_RADIO_WARNING);
		NETWORK.set_function("NETWORK_FORCE_LOCAL_PLAYER_SCAR_SYNC", LUA_NATIVE_NETWORK_NETWORK_FORCE_LOCAL_PLAYER_SCAR_SYNC);
		NETWORK.set_function("NETWORK_DISABLE_LEAVE_REMOTE_PED_BEHIND", LUA_NATIVE_NETWORK_NETWORK_DISABLE_LEAVE_REMOTE_PED_BEHIND);
		NETWORK.set_function("NETWORK_ALLOW_REMOTE_ATTACHMENT_MODIFICATION", LUA_NATIVE_NETWORK_NETWORK_ALLOW_REMOTE_ATTACHMENT_MODIFICATION);
		NETWORK.set_function("NETWORK_SHOW_CHAT_RESTRICTION_MSC", LUA_NATIVE_NETWORK_NETWORK_SHOW_CHAT_RESTRICTION_MSC);
		NETWORK.set_function("NETWORK_SHOW_PSN_UGC_RESTRICTION", LUA_NATIVE_NETWORK_NETWORK_SHOW_PSN_UGC_RESTRICTION);
		NETWORK.set_function("NETWORK_IS_TITLE_UPDATE_REQUIRED", LUA_NATIVE_NETWORK_NETWORK_IS_TITLE_UPDATE_REQUIRED);
		NETWORK.set_function("NETWORK_QUIT_MP_TO_DESKTOP", LUA_NATIVE_NETWORK_NETWORK_QUIT_MP_TO_DESKTOP);
		NETWORK.set_function("NETWORK_IS_CONNECTED_VIA_RELAY", LUA_NATIVE_NETWORK_NETWORK_IS_CONNECTED_VIA_RELAY);
		NETWORK.set_function("NETWORK_GET_AVERAGE_LATENCY", LUA_NATIVE_NETWORK_NETWORK_GET_AVERAGE_LATENCY);
		NETWORK.set_function("NETWORK_GET_AVERAGE_PING", LUA_NATIVE_NETWORK_NETWORK_GET_AVERAGE_PING);
		NETWORK.set_function("NETWORK_GET_AVERAGE_PACKET_LOSS", LUA_NATIVE_NETWORK_NETWORK_GET_AVERAGE_PACKET_LOSS);
		NETWORK.set_function("NETWORK_GET_NUM_UNACKED_RELIABLES", LUA_NATIVE_NETWORK_NETWORK_GET_NUM_UNACKED_RELIABLES);
		NETWORK.set_function("NETWORK_GET_UNRELIABLE_RESEND_COUNT", LUA_NATIVE_NETWORK_NETWORK_GET_UNRELIABLE_RESEND_COUNT);
		NETWORK.set_function("NETWORK_GET_HIGHEST_RELIABLE_RESEND_COUNT", LUA_NATIVE_NETWORK_NETWORK_GET_HIGHEST_RELIABLE_RESEND_COUNT);
		NETWORK.set_function("NETWORK_REPORT_CODE_TAMPER", LUA_NATIVE_NETWORK_NETWORK_REPORT_CODE_TAMPER);
		NETWORK.set_function("NETWORK_GET_LAST_ENTITY_POS_RECEIVED_OVER_NETWORK", LUA_NATIVE_NETWORK_NETWORK_GET_LAST_ENTITY_POS_RECEIVED_OVER_NETWORK);
		NETWORK.set_function("NETWORK_GET_LAST_PLAYER_POS_RECEIVED_OVER_NETWORK", LUA_NATIVE_NETWORK_NETWORK_GET_LAST_PLAYER_POS_RECEIVED_OVER_NETWORK);
		NETWORK.set_function("NETWORK_GET_LAST_VEL_RECEIVED_OVER_NETWORK", LUA_NATIVE_NETWORK_NETWORK_GET_LAST_VEL_RECEIVED_OVER_NETWORK);
		NETWORK.set_function("NETWORK_GET_PREDICTED_VELOCITY", LUA_NATIVE_NETWORK_NETWORK_GET_PREDICTED_VELOCITY);
		NETWORK.set_function("NETWORK_DUMP_NET_IF_CONFIG", LUA_NATIVE_NETWORK_NETWORK_DUMP_NET_IF_CONFIG);
		NETWORK.set_function("NETWORK_GET_SIGNALLING_INFO", LUA_NATIVE_NETWORK_NETWORK_GET_SIGNALLING_INFO);
		NETWORK.set_function("NETWORK_GET_NET_STATISTICS_INFO", LUA_NATIVE_NETWORK_NETWORK_GET_NET_STATISTICS_INFO);
		NETWORK.set_function("NETWORK_GET_PLAYER_ACCOUNT_ID", LUA_NATIVE_NETWORK_NETWORK_GET_PLAYER_ACCOUNT_ID);
		NETWORK.set_function("NETWORK_UGC_NAV", LUA_NATIVE_NETWORK_NETWORK_UGC_NAV);
	}
}
