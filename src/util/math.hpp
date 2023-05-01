#pragma once
#include "pointers.hpp"

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
	
	inline Vector3 add_v3(Vector3 vectorA, Vector3 vectorB) {
		Vector3 result;
		result.x = vectorA.x;
		result.y = vectorA.y;
		result.z = vectorA.z;
		result.x += vectorB.x;
		result.y += vectorB.y;
		result.z += vectorB.z;
		return result;
	}

	inline Vector3 subtract_v3(Vector3 vectorA, Vector3 vectorB) {
		Vector3 result;
		result.x = vectorA.x;
		result.y = vectorA.y;
		result.z = vectorA.z;
		result.x -= vectorB.x;
		result.y -= vectorB.y;
		result.z -= vectorB.z;
		return result;
	}

	inline Vector3 multiply_v3(Vector3 vector, float x) {
		Vector3 result;
		result.x = vector.x;
		result.y = vector.y;
		result.z = vector.z;
		result.x *= x;
		result.y *= x;
		result.z *= x;
		return result;
	}

	inline float calculate_distance_from_game_cam(rage::fvector3 player_position)
	{
		const Vector3 plyr_coords = {player_position.x, player_position.y, player_position.z};
		const Vector3 cam_coords  = g_pointers->m_gta.m_get_gameplay_cam_coords();

		return (float)distance_between_vectors(plyr_coords, cam_coords);
	}
}
