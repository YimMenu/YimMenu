#pragma once
#include "backend/command.hpp"
#include "backend/player_command.hpp"
#include "network.hpp" // for convert_sequence

namespace lua::command
{
	static void call(const std::string& command_name, std::optional<sol::table> _args)
	{
		auto args = convert_sequence<uint64_t>(_args.value_or(sol::table()));

		auto command = big::command::get(rage::joaat(command_name));

		if (command)
			command->call(args, {});
	}

	static void call_player(int player_idx, const std::string& command_name, std::optional<sol::table> _args)
	{
		auto args = convert_sequence<uint64_t>(_args.value_or(sol::table()));

		auto command = (big::player_command*)big::command::get(rage::joaat(command_name));

		if (command)
		{
			auto player = big::g_player_service->get_by_id(player_idx);

			if (player)
			{
				command->call(player, args, {});
			}
		}
	}

	static void bind(sol::state& state)
	{
		auto ns           = state["command"].get_or_create<sol::table>();
		ns["call"]        = call;
		ns["call_player"] = call_player;
	}
}