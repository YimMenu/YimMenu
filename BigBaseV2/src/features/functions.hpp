#pragma once
#include "features.hpp"
#include "gta/joaat.hpp"

namespace big::features::functions
{
	void get_active_character_slot(int* statSlot);
	void join_session_type(session_type session);
	void reset_vehicle_sell_stats();
	void set_car_sell_value(int value);
	void set_player_bounty(Player player, bool anonymous = false);
	void set_player_level(int level);
	void spoof_rank(int rank);
	void toggle_protections(bool toggle);

	bool take_control_of_entity(Entity ent);

	BOOL raycast_entity(Entity* ent);
	float deg_to_rad(float deg);
	Vector3 rotation_to_direction(Vector3 rotation);
	double distance_between_vectors(Vector3 a, Vector3 b);
}