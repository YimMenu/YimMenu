#pragma once

#include "backend/bool_command.hpp"
#include "backend/command.hpp"

namespace big
{
	class spawn_vehicle : public command
	{
		using command::command;

		virtual std::optional<std::vector<std::uint64_t>> parse_args(const std::vector<std::string>& args, const std::shared_ptr<command_context> ctx);

		virtual CommandAccessLevel get_access_level();

		virtual void execute(const std::vector<std::uint64_t>& args, const std::shared_ptr<command_context> ctx);
	};

	namespace cmd
	{
		inline spawn_vehicle g_spawn_vehicle("spawn", "Spawn Vehicle", "Spawn a vehicle with the specified model", 1);

		inline bool_command g_spawn_maxed("spawnmaxed", "Spawn Maxed", "Controls whether the vehicle spawned will have its mods maxed out",
		    g.spawn_vehicle.spawn_maxed);

		inline bool_command g_spawn_inside("spawnin", "Spawn Inside", "Controls whether the player should be set inside the vehicle after it spawns",
		    g.spawn_vehicle.spawn_inside);
	}
}
