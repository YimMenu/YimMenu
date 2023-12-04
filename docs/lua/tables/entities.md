# Table: entities

Table for manipulating GTA entities.

## Functions (4)

### `get_all_vehicles_as_handles()`

- **Returns:**
  - `table<int, int>`: Returns all vehicles as script handles

**Example Usage:**
```lua
local all_vehicles = entities.get_all_vehicles_as_handles()
for i = 1, #all_vehicles do
    log.info(tostring(all_vehicles[i]))
end
```

### `get_all_peds_as_handles()`

- **Returns:**
  - `table<int, int>`: Returns all peds as script handles

**Example Usage:**
```lua
local all_peds = entities.get_all_peds_as_handles()
for i = 1, #all_peds do
    log.info(tostring(all_peds[i]))
end
```

### `get_all_objects_as_handles()`

- **Returns:**
  - `table<int, int>`: Returns all objects as script handles

**Example Usage:**
```lua
local all_objs = entities.get_all_objects_as_handles()
for i = 1, #all_objs do
    log.info(tostring(all_objs[i]))
end
```

### `take_control_of(entity, try_count)`

Must be called from a script (script.run_in_fiber for example)

- **Parameters:**
  - `entity` (Entity): Script handle of the entity we are trying to take control of.
  - `try_count` (integer): Optional. Number of time we'll try taking control of the entity. Default to 300.

- **Returns:**
  - `boolean`: Returns true if we successfully got control of the entity.

**Example Usage:**
```lua
boolean = entities.take_control_of(entity, try_count)
```


