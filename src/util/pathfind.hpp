#pragma once

#include "gta/enums.hpp"
#include "math.hpp"
#include "natives.hpp"
#include "pointers.hpp"
#include "script.hpp"

#include <random>


namespace big::pathfind
{

	inline bool load_path_nodes(Vector3 coords)
	{
		if (PATHFIND::ARE_NODES_LOADED_FOR_AREA(coords.x, coords.y, coords.z, coords.y))
			return true;

		PATHFIND::REQUEST_PATH_NODES_IN_AREA_THIS_FRAME(coords.x, coords.y, coords.z, coords.y);

		for (int i = 0; i < 35 && !PATHFIND::ARE_NODES_LOADED_FOR_AREA(coords.x, coords.y, coords.z, coords.y); i++)
		{
			PATHFIND::REQUEST_PATH_NODES_IN_AREA_THIS_FRAME(coords.x, coords.y, coords.z, coords.y);
			script::get_current()->yield(10ms);
		}

		return PATHFIND::ARE_NODES_LOADED_FOR_AREA(coords.x, coords.y, coords.z, coords.y);
	}

	inline bool load_navmesh_area(Vector3 coords, float radius)
	{
		if (PATHFIND::ARE_ALL_NAVMESH_REGIONS_LOADED())
			return true;

		PATHFIND::ADD_NAVMESH_REQUIRED_REGION(coords.x, coords.z, radius);

		for (int i = 0; i < 35 && !PATHFIND::ARE_ALL_NAVMESH_REGIONS_LOADED(); i++)
		{
			script::get_current()->yield(10ms);
		}

		return PATHFIND::ARE_ALL_NAVMESH_REGIONS_LOADED();
	}

	/*
	Be sure to call this after having added a required region to free up memory since the game files suggest it is rather demanding to load navmesh
	*/
	inline void remove_navmesh_required_areas()
	{
		PATHFIND::REMOVE_NAVMESH_REQUIRED_REGIONS();
	}

	inline bool find_safe_pos_ped(Vector3 coords, Vector3& outcoords, bool onGround, int flag)
	{
		if (load_path_nodes(coords))
			return PATHFIND::GET_SAFE_COORD_FOR_PED(coords.x, coords.y, coords.z, onGround, &outcoords, flag);
		else
			return false;
	}

	/*
	 zMeasureMult: how strongly should the difference in Z direction be weighted? 
	 0.0 = ignored completely, 1.0 = the same as 2d distance. Default is 3.0 since we tend to care about
	 height differences more than 2d distance.
	 zTolerance: how far apart to the Z coords have to be before zMeasureMult kicks in?
	 nth: Which coords are returned, 1 being closest, 2 being second closesst and so on
	*/
	inline bool find_closest_vehicle_node(Vector3 coords, Vector3& outcoords, float& outheading, int flag, int nth = 1, float zMeasureMult = 3.f, float zTolerance = 0.f)
	{
		int lanes;
		if (load_path_nodes(coords))
			return PATHFIND::GET_NTH_CLOSEST_VEHICLE_NODE_WITH_HEADING(coords.x, coords.y, coords.z, nth, &outcoords, &outheading, &lanes, flag, zMeasureMult, zTolerance);
		else
			return false;
	}

	/*
	Same as find_closest_vehicle_node but will favour nodes that are facing the facecoords with their heading
	*/
	inline bool find_closest_vehicle_node_favour_direction(Vector3 coords, Vector3 facecoords, Vector3& outcoords, float& outheading, int flag, int nth = 1, float zMeasureMult = 3.f, float zTolerance = 0.f)
	{
		if (load_path_nodes(coords))
			return PATHFIND::GET_NTH_CLOSEST_VEHICLE_NODE_FAVOUR_DIRECTION(coords.x,
			    coords.y,
			    coords.z,
			    facecoords.x,
			    facecoords.y,
			    facecoords.z,
			    nth,
			    &outcoords,
			    &outheading,
			    flag,
			    zMeasureMult,
			    zTolerance);
		else
			return false;
	}

	inline bool find_random_vehicle_node(Vector3 center, Vector3& outcoords, float radius, bool avoid_dead_ends, bool avoid_highways, int min_lanes = 0)
	{
		int node_id;
		if (load_path_nodes(center))
			return PATHFIND::GET_RANDOM_VEHICLE_NODE(center.x, center.y, center.z, radius, 0, avoid_dead_ends, avoid_highways, &outcoords, &node_id);
		else
			return false;
	}

	inline void apply_distance_to_random_direction(Vector3& outcoords, float distance)
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> dis(0, 1);

		if (dis(gen))
		{
			dis(gen) ? outcoords.x += distance : outcoords.x -= distance;
		}
		else
		{
			dis(gen) ? outcoords.y += distance : outcoords.y -= distance;
		}
	}

	inline bool find_random_location_in_vicinity(Vector3 coords, Vector3& outcoords, float& outheading, int flag, int vicinity, bool favour_heading_to_original_coords = false)
	{
		outcoords = coords;

		apply_distance_to_random_direction(outcoords, vicinity);

		Vector3 changed_coords = outcoords;

		if ((favour_heading_to_original_coords ? !find_closest_vehicle_node_favour_direction(outcoords, outcoords, outcoords, outheading, flag) : !find_closest_vehicle_node(outcoords, outcoords, outheading, flag)) || math::distance_between_vectors(outcoords, coords) > vicinity || math::distance_between_vectors(outcoords, coords) < (vicinity / 2))
		{
			outcoords = coords;

			if (!pathfind::find_safe_pos_ped(changed_coords, outcoords, false, 0))
			{
				outcoords = coords;
			}
		}

		return outcoords != coords;
	}

	/*
	The precision means the algorithm will try and get a position as close to the desired distance as possible
	Param precision goes up to a value of 200 meaning how many positions it will try and filter from
	Might prove resource demanding based on hardware
	*/
	inline bool find_random_location_in_vicinity_precise(Vector3 coords, Vector3& outcoords, float& outheading, int flag, float vicinity, int precision = 50, bool favour_heading_to_original_coords = false)
	{
		if (precision > 200)
			precision = 200;

		std::vector<Vector3> found_locations{};

		//Find random positions
		for (int i = 0; i < precision; i++)
		{
			Vector3 new_pos{};
			find_random_location_in_vicinity(coords, new_pos, outheading, flag, vicinity, favour_heading_to_original_coords);
			found_locations.push_back(new_pos);
		}

		Vector3 best_location = found_locations[0];
		//Measure the distance of the position to the given vicinity distance
		static float distance_to_vicinity = std::abs(vicinity - math::distance_between_vectors(best_location, coords));
		for (auto l : found_locations)
		{
			float new_distance_to_vicinity = std::abs(vicinity - math::distance_between_vectors(l, coords));
			//If the new distance is smaller, that means we have a position that is closer to the edge
			if (new_distance_to_vicinity < distance_to_vicinity)
			{
				distance_to_vicinity = new_distance_to_vicinity;
				best_location        = l;
			}
		}
		outcoords = best_location;

		return outcoords != coords;
	}

	/*
	Will give you two vectors representing the road extremes of the road closest to the given coords.
	*/
	inline bool find_closest_road(Vector3 coords, Vector3* south_end, Vector3* north_end, int* south_bound_lanes = nullptr, int* north_bound_lanes = nullptr, float* width_between_directional_lanes = nullptr, bool ignore_disabled_nodes = true, float min_lenght = 10.f, float min_lanes = 1)
	{
		return PATHFIND::GET_CLOSEST_ROAD(coords.x, coords.y, coords.z, min_lenght, min_lanes, south_end, north_end, south_bound_lanes, north_bound_lanes, width_between_directional_lanes, ignore_disabled_nodes);
	}
}