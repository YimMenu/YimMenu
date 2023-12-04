#pragma once
#include "weapons.hpp"
#include "services/gta_data/gta_data_service.hpp"

namespace lua::weapons
{
	// Lua API: Table
	// Name: weapons
	// Table containing functions for getting information about weapons in GTA V.

	// Lua API: Function
	// Table: weapons
	// Name: get_weapon_display_name
	// Param: Hash
	// Returns the in-game display string. If the weapon is not found, or the call is made too early, a blank string will be returned. It is guranteed to return a safe value.
	static std::string get_weapon_display_name(Hash weapon_hash)
	{
		return big::g_gta_data_service->weapon_by_hash(weapon_hash).m_display_name;
	}

	// Lua API: Function
	// Table: weapons
	// Name: get_weapon_display_name
	// Param: string
	// Returns the in-game display string. If the weapon is not found, or the call is made too early, a blank string will be returned. It is guranteed to return a safe value.
	static std::string get_weapon_display_name_string(std::string weapon_name)
	{
		return big::g_gta_data_service->weapon_by_hash(rage::joaat(weapon_name)).m_display_name;
	}

	// Lua API: Function
	// Table: weapons
	// Name: get_all_weapons_of_group_type
	// Param: Hash
	// Returns a list of all weapons that match the group hash passed in. The list can contain anything from 0 to n elements.
	static std::vector<std::string> get_all_weapons_of_group_type(Hash group_hash)
	{
		std::vector<std::string> return_value;
		for (auto& [name, weapon] : big::g_gta_data_service->weapons())
		{
			if (rage::joaat("GROUP_" + weapon.m_weapon_type) == group_hash)
			{
				return_value.push_back(weapon.m_name);
			}
		}
		return return_value;
	}

	// Lua API: Function
	// Table: weapons
	// Name: get_all_weapons_of_group_type
	// Param: string
	// Returns a list of all weapons that match the group passed in. The list can contain anything from 0 to n elements.
	static std::vector<std::string> get_all_weapons_of_group_type_string(std::string group_name)
	{
		std::transform(group_name.begin(), group_name.end(), group_name.begin(), ::toupper);
		if (group_name.find("GROUP_") == 0)
		{
			group_name.erase(0, 6);
		}
		std::vector<std::string> return_value;
		for (auto& [name, weapon] : big::g_gta_data_service->weapons())
		{
			if (weapon.m_weapon_type == group_name)
			{
				return_value.push_back(weapon.m_name);
			}
		}
		return return_value;
	}

	// Lua API: Function
	// Table: weapons
	// Name: get_all_weapon_components
	// Param: Hash
	// Returns a list of all components that match the weapon passed in. The list can contain anything from 0 to n elements.
	static std::vector<std::string> get_all_weapon_components(Hash weapon_hash)
	{
		return big::g_gta_data_service->weapon_by_hash(weapon_hash).m_attachments;
	}

	// Lua API: Function
	// Table: weapons
	// Name: get_all_weapon_components
	// Param: string
	// Returns a list of all components that match the weapon passed in. The list can contain anything from 0 to n elements.
	static std::vector<std::string> get_all_weapon_components_string(std::string weapon_name)
	{
		return big::g_gta_data_service->weapon_by_hash(rage::joaat(weapon_name)).m_attachments;
	}

	// Lua API: Function
	// Table: weapons
	// Name: get_weapon_component_display_name
	// Param: Hash
	// Returns the in-game display string. If the component is not found, or the call is made too early, a blank string will be returned. It is guranteed to return a safe value.
	static std::string get_weapon_component_display_name(Hash weapon_component_hash)
	{
		return big::g_gta_data_service->weapon_component_by_hash(weapon_component_hash).m_display_name;
	}

	// Lua API: Function
	// Table: weapons
	// Name: get_weapon_component_display_name
	// Param: string
	// Returns the in-game display string. If the component is not found, or the call is made too early, a blank string will be returned. It is guranteed to return a safe value.
	static std::string get_weapon_component_display_name_string(std::string weapon_component)
	{
		return big::g_gta_data_service->weapon_component_by_hash(rage::joaat(weapon_component)).m_display_name;
	}

	// Lua API: Function
	// Table: weapons
	// Name: get_weapon_component_display_desc
	// Param: Hash
	// Returns the in-game display description string. If the component is not found, or the call is made too early, a blank string will be returned. It is guranteed to return a safe value.
	static std::string get_weapon_component_display_desc(Hash weapon_component_hash)
	{
		return big::g_gta_data_service->weapon_component_by_hash(weapon_component_hash).m_display_desc;
	}

	// Lua API: Function
	// Table: weapons
	// Name: get_weapon_component_display_desc
	// Param: string
	// Returns the in-game display description string. If the component is not found, or the call is made too early, a blank string will be returned. It is guranteed to return a safe value.
	static std::string get_weapon_component_display_desc_string(std::string weapon_component)
	{
		return big::g_gta_data_service->weapon_component_by_hash(rage::joaat(weapon_component)).m_display_desc;
	}

	void bind(sol::state& state)
	{
		auto ns                                 = state["weapons"].get_or_create<sol::table>();
		ns["get_weapon_display_name"]           = sol::overload(get_weapon_display_name, get_weapon_display_name_string);
		ns["get_all_weapons_of_group_type"]     = sol::overload(get_all_weapons_of_group_type, get_all_weapons_of_group_type_string);
		ns["get_all_weapon_components"]         = sol::overload(get_all_weapon_components, get_all_weapon_components_string);
		ns["get_weapon_component_display_name"] = sol::overload(get_weapon_component_display_name, get_weapon_component_display_name_string);
		ns["get_weapon_component_display_desc"] = sol::overload(get_weapon_component_display_desc, get_weapon_component_display_desc_string);
	}
}