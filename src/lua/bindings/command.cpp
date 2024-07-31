#pragma once
#include "backend/command.hpp"
#include "backend/player_command.hpp"
#include "network.hpp" // for convert_sequence

namespace lua::command
{
	// Lua API: Table
	// Name: command
	// Table for calling menu commands.

	// Lua API: Function
	// Table: command
	// Name: call
	// Param: command_name: string: The name of the command that will be called.
	// Param: _args: table: Optional. List of arguments for the command.
	// Call a menu command.
	static void call(const std::string& command_name, std::optional<sol::table> _args)
	{
		big::command_arguments args = convert_sequence<uint64_t>(_args.value_or(sol::table()));

		const auto command = big::command::get(rage::joaat(command_name));

		if (command)
			command->call(args);
	}

	// Lua API: Function
	// Table: command
	// Name: call_player
	// Param: player_idx: integer: Index of the player on which the menu command will be executed.
	// Param: command_name: string: The name of the command that will be called.
	// Param: _args: table: Optional. List of arguments for the command.
	// Call a menu command on a given player.
	static void call_player(int player_idx, const std::string& command_name, std::optional<sol::table> _args)
	{
		const auto args = convert_sequence<uint64_t>(_args.value_or(sol::table()));

		const auto command = big::player_command::get(rage::joaat(command_name));

		if (command)
		{
			const auto player = big::g_player_service->get_by_id(player_idx);

			if (player)
			{
				command->call(player, args);
			}
		}
		else
		{
			LOG(FATAL) << "No player command called " << command_name;
		}
	}

	// Lua API: Function
	// Table: command
	// Name: get_all_player_command_names
	// Returns: table<integer, string>: Table that contains the names of all the player commands.
	static std::vector<std::string> get_all_player_command_names()
	{
		std::vector<std::string> res;

		for (const auto& cmd : big::g_player_commands | std::ranges::views::values)
		{
			res.push_back(cmd->get_name());
		}

		return res;
	}

	void bind(sol::state& state)
	{
		auto ns                            = state["command"].get_or_create<sol::table>();
		ns["call"]                         = call;
		ns["call_player"]                  = call_player;
		ns["get_all_player_command_names"] = get_all_player_command_names;
	}
}