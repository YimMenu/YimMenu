#pragma once
#include "vehicles.hpp"
#include "services/gta_data/gta_data_service.hpp"

namespace lua::vehicles
{
	// Lua API: Table
	// Name: vehicles
	// Table containing functions for getting information about vehicles in GTA V.

	// Lua API: Function
	// Table: vehicles
	// Name: get_vehicle_display_name
	// Param: Hash
	// Returns the in-game display string. If the vehicle is not found, or the call is made too early, a blank string will be returned. It is guranteed to return a safe value.
	static std::string get_vehicle_display_name(Hash vehicle_hash)
	{
		return big::g_gta_data_service->vehicle_by_hash(vehicle_hash).m_display_name;
	}

	// Lua API: Function
	// Table: vehicles
	// Name: get_vehicle_display_name
	// Param: string
	// Returns the in-game display string. If the vehicle is not found, or the call is made too early, a blank string will be returned. It is guranteed to return a safe value.
	static std::string get_vehicle_display_name_string(std::string vehicle_name)
	{
		return big::g_gta_data_service->vehicle_by_hash(rage::joaat(vehicle_name)).m_display_name;
	}

	// Lua API: Function
	// Table: vehicles
	// Name: get_all_vehicles_by_class
	// Param: string
	// Returns a list of all vehicles that match the class passed in. The list can contain anything from 0 to n elements.
	static std::vector<std::string> get_all_vehicles_by_class(std::string vehicle_class)
	{
		std::vector<std::string> return_value;
		for (auto& [name, vehicle] : big::g_gta_data_service->vehicles())
		{
			if (vehicle.m_vehicle_class == vehicle_class)
			{
				return_value.push_back(vehicle.m_name);
			}
		}
		return return_value;
	}

	// Lua API: Function
	// Table: vehicles
	// Name: get_all_vehicles_by_mfr
	// Param: string
	// Returns a list of all vehicles that match the manufacturer passed in. The list can contain anything from 0 to n elements.
	static std::vector<std::string> get_all_vehicles_by_mfr(std::string manufacturer)
	{
		std::vector<std::string> return_value;
		for (auto& [name, vehicle] : big::g_gta_data_service->vehicles())
		{
			if (vehicle.m_display_manufacturer == manufacturer)
			{
				return_value.push_back(vehicle.m_name);
			}
		}
		return return_value;
	}

	void bind(sol::state& state)
	{
		auto ns                          = state["vehicles"].get_or_create<sol::table>();
		ns["get_vehicle_display_name"]   = sol::overload(get_vehicle_display_name, get_vehicle_display_name_string);
		ns["get_all_vehicles_by_class"]  = get_all_vehicles_by_class;
		ns["get_all_vehicles_by_mfr"]    = get_all_vehicles_by_mfr;
	}
}