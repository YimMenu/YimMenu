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

		return Vector3
		{
			-sin(z) * num,
			cos(z) * num,
			sin(x)
		};
	}

	inline float calculate_distance_from_game_cam (rage::fvector3 player_position)
	{
		const Vector3 plyr_coords = { player_position.x, player_position.y, player_position.z };
		const Vector3 cam_coords = g_pointers->m_get_gameplay_cam_coords();

		return (float)distance_between_vectors(plyr_coords, cam_coords);
	}

	inline rage::vector3<int> sector_from_coords(rage::fvector3 coords)
	{
		rage::vector3<int> sector{};
		float mag = std::sqrt(coords.x * coords.x + coords.y * coords.y + coords.z * coords.z);

		if (mag > 16.0f)
		{
			coords.x *= (16.0f / mag);
			coords.y *= (16.0f / mag);
			coords.z *= (16.0f / mag);
		}

		sector.x = std::clamp<int>(coords.x * 32.0f, -511, 511);
		sector.y = std::clamp<int>(coords.y * 32.0f, -511, 511);
		sector.z = std::clamp<int>(coords.z * 32.0f, -511, 511);
	}
}
