# Table: weapons

Table containing functions for getting information about weapons in GTA V.

## Functions (10)

### `get_weapon_display_name(weapon_hash)`

- **Parameters:**
  - `weapon_hash` (Hash): JOAAT hash of the weapon.

- **Returns:**
  - `weapon_display_name`: String: the in-game display string. If the weapon is not found, or the call is made too early, a blank string will be returned. It is guranteed to return a safe value.

- **Example Usage:**
```lua
log.info(weapons.get_weapon_display_name(joaat('WEAPON_REVOLVER')))
```

### `get_weapon_display_name(weapon_name)`

- **Parameters:**
  - `weapon_name` (String): Name of the weapon.

- **Returns:**
  - `weapon_display_name`: String: the in-game display string. If the weapon is not found, or the call is made too early, a blank string will be returned. It is guranteed to return a safe value.

- **Example Usage:**
```lua
log.info(weapons.get_weapon_display_name('WEAPON_REVOLVER'))
```

### `get_all_weapons_of_group_type(group_hash)`

- **Parameters:**
  - `group_hash` (Hash): The JOAAT hash of the group the weapon(s) belong to.

- **Returns:**
  - `weapons_of_group_type`: table<int, String>: a list of all weapons that match the group hash passed in. The list can contain anything from 0 to n elements.

- **Example Usage:**
```lua
local pistols = weapons.get_all_weapons_of_group_type(joaat('GROUP_PISTOL'))
for i = 1, #pistols do
    log.info(pistols[i])
end
```

### `get_all_weapons_of_group_type(group_name)`

- **Parameters:**
  - `group_name` (String): The group the weapon(s) belong to. Can be in either GROUP_ format or not. Parameter is case-insensitive.

- **Returns:**
  - `weapons_of_group_type`: table<int, String>: a list of all weapons that match the group hash passed in. The list can contain anything from 0 to n elements.

- **Example Usage:**
```lua
local pistols = weapons.get_all_weapons_of_group_type('GROUP_PISTOL')
for i = 1, #pistols do
	log.info(pistols[i])
end

local pistols = weapons.get_all_weapons_of_group_type('PISTOL')
for i = 1, #pistols do
	log.info(pistols[i])
end
```

### `get_all_weapon_components(weapon_hash)`

- **Parameters:**
  - `weapon_hash` (Hash): The JOAAT hash of the weapon the component(s) belong to.

- **Returns:**
  - `weapon_components`: table<int, String>: a list of all components that match the weapon passed in. The list can contain anything from 0 to n elements.

- **Example Usage:**
```lua
local pistol_attachments = weapons.get_all_weapon_components(joaat('WEAPON_PISTOL'))
for i = 1, #pistol_attachments do
	log.info(pistol_attachments[i])
end
```

### `get_all_weapon_components(weapon_name)`

- **Parameters:**
  - `weapon_name` (String): The weapon the component(s) belong to.

- **Returns:**
  - `weapon_components`: table<int, String>: a list of all components that match the weapon passed in. The list can contain anything from 0 to n elements.

- **Example Usage:**
```lua
local pistol_attachments = weapons.get_all_weapon_components('WEAPON_PISTOL')
for i = 1, #pistol_attachments do
	log.info(pistol_attachments[i])
end
```

### `get_weapon_component_display_name(weapon_component_hash)`

- **Parameters:**
  - `weapon_component_hash` (Hash): JOAAT hash of the weapon component.

- **Returns:**
  - `component_display_name`: String: the in-game display string. If the component is not found, or the call is made too early, a blank string will be returned. It is guranteed to return a safe value.

- **Example Usage:**
```lua
log.info(weapons.get_weapon_component_display_name(joaat('COMPONENT_PISTOL_CLIP_01')))
```

### `get_weapon_component_display_name(weapon_component)`

- **Parameters:**
  - `weapon_component` (String): The weapon component.

- **Returns:**
  - `component_display_name`: String: the in-game display string. If the component is not found, or the call is made too early, a blank string will be returned. It is guranteed to return a safe value.

- **Example Usage:**
```lua
log.info(weapons.get_weapon_component_display_name('COMPONENT_PISTOL_CLIP_01'))
```

### `get_weapon_component_display_desc(weapon_component_hash)`

- **Parameters:**
  - `weapon_component_hash` (Hash): JOAAT hash of the weapon component.

- **Returns:**
  - `component_display_desc`: String: the in-game display string. If the component is not found, or the call is made too early, a blank string will be returned. It is guranteed to return a safe value.

- **Example Usage:**
```lua
log.info(weapons.get_weapon_component_display_desc(joaat('COMPONENT_PISTOL_CLIP_01')))
```

### `get_weapon_component_display_desc(weapon_component)`

- **Parameters:**
  - `weapon_component` (String): The weapon component.

- **Returns:**
  - `component_display_desc`: String: the in-game display string. If the component is not found, or the call is made too early, a blank string will be returned. It is guranteed to return a safe value.

- **Example Usage:**
```lua
log.info(weapons.get_weapon_component_display_desc('COMPONENT_PISTOL_CLIP_01'))
```