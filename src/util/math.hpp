#pragma once
#include "pointers.hpp"
#include "natives.hpp"

namespace big::math
{
	inline float deg_to_rad(float deg)
	{
		double radian = (3.14159265359 / 180) * deg;
		return (float)radian;
	}

	inline float distance_between_vectors(Vector3 a, Vector3 b)
	{
		return (float)sqrt(pow((a.x - b.x), 2) + pow((a.y - b.y), 2) + pow((a.z - b.z), 2));
	}

	inline Vector3 rotation_to_direction(Vector3 rotation)
	{
		float x = deg_to_rad(rotation.x);
		float z = deg_to_rad(rotation.z);

		float num = abs(cos(x));

		return Vector3{-sin(z) * num, cos(z) * num, sin(x)};
	}

	inline float calculate_distance_from_game_cam(rage::fvector3 player_position)
	{
		const Vector3 plyr_coords = {player_position.x, player_position.y, player_position.z};
		const Vector3 cam_coords  = g_pointers->m_gta.m_get_gameplay_cam_coords();

		return (float)distance_between_vectors(plyr_coords, cam_coords);
	}

	inline Vector3 raycast_coords(Vector3 coord, Vector3 rot, Entity ignore){

		BOOL hit;
		Vector3 endCoords;
		Vector3 surfaceNormal;
		Entity hit_entity;
		Vector3 dir       = math::rotation_to_direction(rot);
		Vector3 farCoords;

		farCoords.x = coord.x + dir.x * 1000;
		farCoords.y = coord.y + dir.y * 1000;
		farCoords.z = coord.z + dir.z * 1000;

		int ray = SHAPETEST::START_EXPENSIVE_SYNCHRONOUS_SHAPE_TEST_LOS_PROBE(coord.x,
		    coord.y,
		    coord.z,
		    farCoords.x,
		    farCoords.y,
		    farCoords.z,
		    -1,
		    ignore,
		    7);
		SHAPETEST::GET_SHAPE_TEST_RESULT(ray, &hit, &endCoords, &surfaceNormal, &hit_entity);
		return endCoords;
	}
}
