#pragma once
#include "common.hpp"
#include "structs/session_type.hpp"

namespace big
{
	class func
	{
	public:
		static void		cage_ped(Ped ped);
		static void		create_ambient_money(Vector3 location, int amount);
		static void		create_ambient_rp(Vector3 location);
		static float	deg_to_rad(float deg);
		static void		delete_entity(Entity ent);
		static double	distance_between_vectors(Vector3 a, Vector3 b);
		static void		get_active_character_slot(int* statSlot);
		static void		join_message(Player player);
		static void		join_session_type(session_type session);
		static bool		raycast_entity(Entity* ent);
		static void		reset_vehicle_sell_stats();
		static Vector3	rotation_to_direction(Vector3 rotation);
		static void		set_car_sell_value(int value);
		static void		set_player_bounty(Player player, int amount = 1e4, bool anonymous = false);
		static void		set_player_level(int level);
		static Entity	spawn_vehicle(const char* model, Vector3 location, float heading);
		static void		spoof_rank(int rank);
		static bool		take_control_of_entity(Entity ent);
		static void		toggle_protections(bool toggle);

	private:

	};
}