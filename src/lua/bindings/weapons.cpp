#pragma once
#include "services/gta_data/gta_data_service.hpp"

namespace lua::weapons
{
	// Lua API: Table
	// Name: weapons
	// Table containing functions for getting information about weapons in GTA V.

	// Lua API: Function
	// Table: weapons
	// Name: get_weapon_display_name
	// Param: weapon_hash: Hash: JOAAT hash of the weapon.
	// Returns: weapon_display_name: String: the in-game display string. If the weapon is not found, or the call is made too early, a blank string will be returned. It is guranteed to return a safe value.
	//- **Example Usage:**
	//```lua
	//log.info(weapons.get_weapon_display_name(joaat('WEAPON_REVOLVER')))
	//```
	static std::string get_weapon_display_name(Hash weapon_hash)
	{
		return big::g_gta_data_service.weapon_by_hash(weapon_hash).m_display_name;
	}

	// Lua API: Function
	// Table: weapons
	// Name: get_weapon_display_name
	// Param: weapon_name: String: Name of the weapon.
	// Returns: weapon_display_name: String: the in-game display string. If the weapon is not found, or the call is made too early, a blank string will be returned. It is guranteed to return a safe value.
	//- **Example Usage:**
	//```lua
	//log.info(weapons.get_weapon_display_name('WEAPON_REVOLVER'))
	//```
	static std::string get_weapon_display_name_string(std::string weapon_name)
	{
		return big::g_gta_data_service.weapon_by_hash(rage::joaat(weapon_name)).m_display_name;
	}

	// Lua API: Function
	// Table: weapons
	// Name: get_all_weapons_of_group_type
	// Param: group_hash: Hash: The JOAAT hash of the group the weapon(s) belong to.
	// Returns: weapons_of_group_type: table<int, String>: a list of all weapons that match the group hash passed in. The list can contain anything from 0 to n elements.
	//- **Example Usage:**
	//```lua
	//local pistols = weapons.get_all_weapons_of_group_type(joaat('GROUP_PISTOL'))
	//for i = 1, #pistols do
	//    log.info(pistols[i])
	//end
	//```
	static std::vector<std::string> get_all_weapons_of_group_type(Hash group_hash)
	{
		std::vector<std::string> return_value;
		for (auto& [name, weapon] : big::g_gta_data_service.weapons())
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
	// Param: group_name: String: The group the weapon(s) belong to. Can be in either GROUP_ format or not. Parameter is case-insensitive.
	// Returns: weapons_of_group_type: table<int, String>: a list of all weapons that match the group hash passed in. The list can contain anything from 0 to n elements.
	//- **Example Usage:**
	//```lua
	//local pistols = weapons.get_all_weapons_of_group_type('GROUP_PISTOL')
	//for i = 1, #pistols do
	//	log.info(pistols[i])
	//end
	//
	//local pistols = weapons.get_all_weapons_of_group_type('PISTOL')
	//for i = 1, #pistols do
	//	log.info(pistols[i])
	//end
	//```
	static std::vector<std::string> get_all_weapons_of_group_type_string(std::string group_name)
	{
		std::transform(group_name.begin(), group_name.end(), group_name.begin(), ::toupper);
		if (group_name.find("GROUP_") == 0)
		{
			group_name.erase(0, 6);
		}
		std::vector<std::string> return_value;
		for (auto& [name, weapon] : big::g_gta_data_service.weapons())
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
	// Param: weapon_hash: Hash: The JOAAT hash of the weapon the component(s) belong to.
	// Returns: weapon_components: table<int, String>: a list of all components that match the weapon passed in. The list can contain anything from 0 to n elements.
	//- **Example Usage:**
	//```lua
	//local pistol_attachments = weapons.get_all_weapon_components(joaat('WEAPON_PISTOL'))
	//for i = 1, #pistol_attachments do
	//	log.info(pistol_attachments[i])
	//end
	//```
	static std::vector<std::string> get_all_weapon_components(Hash weapon_hash)
	{
		return big::g_gta_data_service.weapon_by_hash(weapon_hash).m_attachments;
	}

	// Lua API: Function
	// Table: weapons
	// Name: get_all_weapon_components
	// Param: weapon_name: String: The weapon the component(s) belong to.
	// Returns: weapon_components: table<int, String>: a list of all components that match the weapon passed in. The list can contain anything from 0 to n elements.
	//- **Example Usage:**
	//```lua
	//local pistol_attachments = weapons.get_all_weapon_components('WEAPON_PISTOL')
	//for i = 1, #pistol_attachments do
	//	log.info(pistol_attachments[i])
	//end
	//```
	static std::vector<std::string> get_all_weapon_components_string(std::string weapon_name)
	{
		return big::g_gta_data_service.weapon_by_hash(rage::joaat(weapon_name)).m_attachments;
	}

	// Lua API: Function
	// Table: weapons
	// Name: get_weapon_component_display_name
	// Param: weapon_component_hash: Hash: JOAAT hash of the weapon component.
	// Returns: component_display_name: String: the in-game display string. If the component is not found, or the call is made too early, a blank string will be returned. It is guranteed to return a safe value.
	//- **Example Usage:**
	//```lua
	//log.info(weapons.get_weapon_component_display_name(joaat('COMPONENT_PISTOL_CLIP_01')))
	//```
	static std::string get_weapon_component_display_name(Hash weapon_component_hash)
	{
		return big::g_gta_data_service.weapon_component_by_hash(weapon_component_hash).m_display_name;
	}

	// Lua API: Function
	// Table: weapons
	// Name: get_weapon_component_display_name
	// Param: weapon_component: String: The weapon component.
	// Returns: component_display_name: String: the in-game display string. If the component is not found, or the call is made too early, a blank string will be returned. It is guranteed to return a safe value.
	//- **Example Usage:**
	//```lua
	//log.info(weapons.get_weapon_component_display_name('COMPONENT_PISTOL_CLIP_01'))
	//```
	static std::string get_weapon_component_display_name_string(std::string weapon_component)
	{
		return big::g_gta_data_service.weapon_component_by_hash(rage::joaat(weapon_component)).m_display_name;
	}

	// Lua API: Function
	// Table: weapons
	// Name: get_weapon_component_display_desc
	// Param: weapon_component_hash: Hash: JOAAT hash of the weapon component.
	// Returns: component_display_desc: String: the in-game display string. If the component is not found, or the call is made too early, a blank string will be returned. It is guranteed to return a safe value.
	//- **Example Usage:**
	//```lua
	//log.info(weapons.get_weapon_component_display_desc(joaat('COMPONENT_PISTOL_CLIP_01')))
	//```
	static std::string get_weapon_component_display_desc(Hash weapon_component_hash)
	{
		return big::g_gta_data_service.weapon_component_by_hash(weapon_component_hash).m_display_desc;
	}

	// Lua API: Function
	// Table: weapons
	// Name: get_weapon_component_display_desc
	// Param: weapon_component: String: The weapon component.
	// Returns: component_display_desc: String: the in-game display string. If the component is not found, or the call is made too early, a blank string will be returned. It is guranteed to return a safe value.
	//- **Example Usage:**
	//```lua
	//log.info(weapons.get_weapon_component_display_desc('COMPONENT_PISTOL_CLIP_01'))
	//```
	static std::string get_weapon_component_display_desc_string(std::string weapon_component)
	{
		return big::g_gta_data_service.weapon_component_by_hash(rage::joaat(weapon_component)).m_display_desc;
	}

	void bind(sol::state& state)
	{
		auto ns                       = state["weapons"].get_or_create<sol::table>();
		ns["get_weapon_display_name"] = sol::overload(get_weapon_display_name, get_weapon_display_name_string);
		ns["get_all_weapons_of_group_type"] = sol::overload(get_all_weapons_of_group_type, get_all_weapons_of_group_type_string);
		ns["get_all_weapon_components"] = sol::overload(get_all_weapon_components, get_all_weapon_components_string);
		ns["get_weapon_component_display_name"] = sol::overload(get_weapon_component_display_name, get_weapon_component_display_name_string);
		ns["get_weapon_component_display_desc"] = sol::overload(get_weapon_component_display_desc, get_weapon_component_display_desc_string);
	}
}
