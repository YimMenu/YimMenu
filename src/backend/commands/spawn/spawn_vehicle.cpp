#include "backend/bool_command.hpp"
#include "core/settings.hpp"

namespace big
{
	bool_command g_spawn_maxed("spawnmaxed", "Spawn Maxed", "Controls whether the vehicle spawned will have its mods maxed out",
	    g.spawn_vehicle.spawn_maxed);
	bool_command g_spawn_inside("spawnin", "Spawn Inside", "Controls whether the player should be set inside the vehicle after it spawns",
	    g.spawn_vehicle.spawn_inside);
}
