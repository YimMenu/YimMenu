#pragma once
#include "gta/joaat.hpp"
#include "gta_util.hpp"
#include "math.hpp"
#include "natives.hpp"
#include "pools.hpp"
#include "script.hpp"
#include "services/players/player_service.hpp"

namespace big::entity
{
	void cage_ped(Ped ped);
	void clean_ped(Ped ped);
	bool take_control_of(Entity ent, int timeout = 300);
	void delete_entity(Entity ent);
	bool raycast(Entity* ent);
	bool raycast(Vector3* endcoor);
	bool network_has_control_of_entity(rage::netObject* net_object);
	std::vector<Entity> get_entities(bool vehicles, bool peds, bool props = false, bool include_self_veh = false);
	bool load_ground_at_3dcoord(Vector3& location);
	double distance_to_middle_of_screen(const rage::fvector2& screen_pos);
	Entity get_entity_closest_to_middle_of_screen(rage::fwEntity** pointer = nullptr, std::vector<Entity> ignore_entities = {}, bool include_veh = true, bool include_ped = true, bool include_prop = true, bool include_players = true);
}
