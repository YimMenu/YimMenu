#include "network.hpp"

#include "../../script.hpp"
#include "hooking/hooking.hpp"
#include "pointers.hpp"
#include "services/player_database/player_database_service.hpp"
#include "util/notify.hpp"
#include "util/chat.hpp"
#include "util/scripts.hpp"
#include "util/session.hpp"
#include "util/system.hpp"
#include "util/teleport.hpp"

namespace lua::network
{
	// Lua API: Table
	// Name: network
	// Table containing helper functions for network related features.

	// Lua API: Function
	// Table: network
	// Name: trigger_script_event
	// Param: bitset: integer
	// Param: _args: table
	// Call trigger_script_event (TSE)
	static void trigger_script_event(int bitset, sol::table _args)
	{
		auto args = convert_sequence<int32_t>(_args);

		if (args.size() >= 1)
			args[1] = self::id;

		std::vector<std::int64_t> actual_args;

		for (auto arg : args)
			actual_args.push_back((uint32_t)arg);

		big::g_pointers->m_gta.m_trigger_script_event(1, actual_args.data(), actual_args.size(), bitset, args[0]);
	}

	// Lua API: Function
	// Table: network
	// Name: give_pickup_rewards
	// Param: player: integer: Index of the player.
	// Param: reward: integer: Index of the reward pickup.
	// Give the given pickup reward to the given player.
	static void give_pickup_rewards(int player, int reward)
	{
		big::g_pointers->m_gta.m_give_pickup_rewards(1 << player, reward);
	}

	// Lua API: Function
	// Table: network
	// Name: set_player_coords
	// Param: player_idx: integer: Index of the player.
	// Param: x: float: New x position.
	// Param: y: float: New y position.
	// Param: z: float: New z position.
	// Teleport the given player to the given position.
	static void set_player_coords(int player_idx, float x, float y, float z)
	{
		if (auto player = big::g_player_service->get_by_id(player_idx))
			big::teleport::teleport_player_to_coords(player, {x, y, z});
	}

	// Lua API: Function
	// Table: network
	// Name: set_all_player_coords
	// Param: x: float: New x position.
	// Param: y: float: New y position.
	// Param: z: float: New z position.
	// Teleport all players to the given position.
	static void set_all_player_coords(float x, float y, float z)
	{
		for (auto& player : big::g_player_service->players())
			big::g_fiber_pool->queue_job([player, x, y, z]() {
				big::teleport::teleport_player_to_coords(player.second, {x, y, z});
			});
	}

	// Lua API: Function
	// Table: network
	// Name: get_selected_player
	// Returns: integer: Returns the index of the currently selected player in the GUI.
	static int get_selected_player()
	{
		if (big::g_player_service->get_selected()->is_valid())
			return big::g_player_service->get_selected()->id();

		return -1;
	}

	// Lua API: Function
	// Table: network
	// Name: get_selected_database_player_rockstar_id
	// Returns: integer: Returns the rockstar id of the currently selected player in the GUI.
	static int get_selected_database_player_rockstar_id()
	{
		if (auto pers = big::g_player_database_service->get_selected())
			return pers->rockstar_id;

		return -1;
	}

	static void flag_player_as_modder(int player_idx, big::Infraction reason)
	{
		if (auto player = big::g_player_service->get_by_id(player_idx))
		{
			big::session::add_infraction(player, reason);
		}
	}

	// Lua API: Function
	// Table: network
	// Name: flag_player_as_modder
	// Param: player_idx: integer: Index of the player.
	// Param: reason: Infraction: Reason why the player is flagged as a modder, if the infraction is CUSTOM_REASON, then the custom_reason string is added in the local database. For a full list of the possible infraction reasons to use, please check the infraction page.
	// Param: custom_reason: string: Optional, required only when the infraction is CUSTOM_REASON. The custom reason why the player is flagged as a modder.
	// Flags the given player as a modder in our local database.
	static void flag_player_as_modder_custom_reason(int player_idx, big::Infraction reason, const std::string& custom_reason)
	{
		if (auto player = big::g_player_service->get_by_id(player_idx))
		{
			big::session::add_infraction(player, reason, custom_reason);
		}
	}

	// Lua API: Function
	// Table: network
	// Name: is_player_flagged_as_modder
	// Param: player_idx: integer: Index of the player.
	// Returns: boolean: Returns true if the given player is flagged as a modder.
	static bool is_player_flagged_as_modder(int player_idx)
	{
		if (auto player = big::g_player_service->get_by_id(player_idx))
			return player->is_modder;

		return false;
	}

	// Lua API: Function
	// Table: network
	// Name: is_player_friend
	// Param: player_idx: integer: Index of the player.
	// Returns: boolean: Returns true if the given player is a friend.
	static bool is_player_friend(int player_idx)
	{
		if (auto player = big::g_player_service->get_by_id(player_idx))
			return player->is_friend();

		return false;
	}

	// Lua API: Function
	// Table: network
	// Name: get_flagged_modder_reason
	// Param: player_idx: integer: Index of the player.
	// Returns: string: Returns a string which contains the reason(s) why the player is flagged as a modder.
	static std::string get_flagged_modder_reason(int player_idx)
	{
		if (auto player = big::g_player_service->get_by_id(player_idx))
		{
			return big::g_player_database_service->get_or_create_player(player)->get_all_infraction_descriptions();
		}

		return "";
	}

	// Lua API: Function
	// Table: network
	// Name: force_script_host
	// Param: script_name: string: Name of the script
	// Try to force ourself to be host for the given GTA Script.
	static void force_script_host(const std::string& script_name)
	{
		big::scripts::force_host(rage::joaat(script_name));
	}

	// Lua API: Function
	// Table: network
	// Name: send_chat_message
	// Param: msg: string: Message to be sent.
	// Param: team_only: boolean: Should be true if the msg should only be sent to our team.
	// Sends a message to the in game chat.
	static void send_chat_message(const std::string& msg, bool team_only)
	{
		big::chat::send_message(msg, nullptr, true, team_only);
	}

	// Lua API: Function
	// Table: network
	// Name: send_chat_message_to_player
	// Param: player_idx: integer: Index of the player.
	// Param: msg: string: Message to be sent.
	// Sends a chat message to the specified player. Other players would not be able to see the message
	static void send_chat_message_to_player(int player_idx, const std::string& msg)
	{
		if (auto player = big::g_player_service->get_by_id(player_idx))
		{
			big::chat::send_message(msg, player);

		}
	}

	void bind(sol::state& state)
	{
		state.new_enum<big::Infraction>("infraction",
		    {
		        {"ATTACKING_WHEN_HIDDEN_FROM_PLAYER_LIST", big::Infraction::ATTACKING_WHEN_HIDDEN_FROM_PLAYER_LIST},
		        {"ATTACKING_WITH_GODMODE", big::Infraction::ATTACKING_WITH_GODMODE},
		        {"ATTACKING_WITH_INVISIBILITY", big::Infraction::ATTACKING_WITH_INVISIBILITY},
		        {"BLAME_EXPLOSION_DETECTED", big::Infraction::BLAME_EXPLOSION_DETECTED},
		        {"BREAKUP_KICK_DETECTED", big::Infraction::BREAKUP_KICK_DETECTED},
		        {"CUSTOM_REASON", big::Infraction::CUSTOM_REASON},
		        {"DESYNC_PROTECTION", big::Infraction::DESYNC_PROTECTION},
		        {"INVALID_PLAYER_MODEL", big::Infraction::INVALID_PLAYER_MODEL},
		        {"LOST_CONNECTION_KICK_DETECTED", big::Infraction::LOST_CONNECTION_KICK_DETECTED},
		        {"SPOOFED_DATA", big::Infraction::SPOOFED_DATA},
		        {"SPOOFED_HOST_TOKEN", big::Infraction::SPOOFED_HOST_TOKEN},
		        {"SPOOFED_ROCKSTAR_ID", big::Infraction::SPOOFED_ROCKSTAR_ID},
		        {"SUPER_JUMP", big::Infraction::SUPER_JUMP},
		        {"TRIED_CRASH_PLAYER", big::Infraction::TRIED_CRASH_PLAYER},
		        {"TRIED_KICK_PLAYER", big::Infraction::TRIED_KICK_PLAYER},
		        {"TRIGGERED_ANTICHEAT", big::Infraction::TRIGGERED_ANTICHEAT},
		        {"UNDEAD_OTR", big::Infraction::UNDEAD_OTR},
		    });

		auto ns = state["network"].get_or_create<sol::table>();

		ns["trigger_script_event"]                     = trigger_script_event;
		ns["give_pickup_rewards"]                      = give_pickup_rewards;
		ns["set_player_coords"]                        = set_player_coords;
		ns["set_all_player_coords"]                    = set_all_player_coords;
		ns["get_selected_player"]                      = get_selected_player;
		ns["get_selected_database_player_rockstar_id"] = get_selected_database_player_rockstar_id;
		ns["flag_player_as_modder"]                    = sol::overload(flag_player_as_modder, flag_player_as_modder_custom_reason);
		ns["is_player_flagged_as_modder"]              = is_player_flagged_as_modder;
		ns["is_player_friend"]                         = is_player_friend;
		ns["get_flagged_modder_reason"]                = get_flagged_modder_reason;
		ns["force_script_host"]                        = force_script_host;
		ns["send_chat_message"]                        = send_chat_message;
		ns["send_chat_message_to_player"]              = send_chat_message_to_player;
	}
}