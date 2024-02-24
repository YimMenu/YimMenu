# Table: vehicles

Table containing functions for getting information about vehicles in GTA V.

## Functions (4)

### `get_vehicle_display_name(vehicle_hash)`

- **Example Usage:**
```lua
log.info(vehicles.get_vehicle_display_name('BTYPE2'))
```

- **Parameters:**
  - `vehicle_hash` (Hash): JOAAT hash of the vehicle.

- **Returns:**
  - `vehicle_display_string`: String: the in-game display string. If the vehicle is not found, or the call is made too early, a blank string will be returned. It is guranteed to return a safe value.

**Example Usage:**
```lua
vehicle_display_string = vehicles.get_vehicle_display_name(vehicle_hash)
```

### `get_vehicle_display_name(vehicle_name)`

- **Example Usage:**
```lua
log.info(vehicles.get_vehicle_display_name('BTYPE2'))
```

- **Parameters:**
  - `vehicle_name` (String): Name of the vehicle.

- **Returns:**
  - `vehicle_display_string`: String: the in-game display string. If the vehicle is not found, or the call is made too early, a blank string will be returned. It is guranteed to return a safe value.

**Example Usage:**
```lua
vehicle_display_string = vehicles.get_vehicle_display_name(vehicle_name)
```

### `get_all_vehicles_by_class(vehicle_class)`

- **Example Usage:**
```lua
local sports_classics = vehicles.get_all_vehicles_by_class('Sports Classics')
for i = 1, #sports_classics do
    log.info(sports_classics[i])
end
```

- **Parameters:**
  - `vehicle_class` (String): The vehicle class.

- **Returns:**
  - `vehicles`: table<int, String>: a list of all vehicles that match the class passed in. The list can contain anything from 0 to n elements.

**Example Usage:**
```lua
vehicles = vehicles.get_all_vehicles_by_class(vehicle_class)
```

### `get_all_vehicles_by_mfr(manufacturer)`

- **Example Usage:**
```lua
local albanies = vehicles.get_all_vehicles_by_mfr('Albany')
for i = 1, #albanies do
    log.info(albanies[i])
end
```

- **Parameters:**
  - `manufacturer` (String): The vehicle manufacturer.

- **Returns:**
  - `vehicles`: table<int, String>: a list of all vehicles that match the manufacturer passed in. The list can contain anything from 0 to n elements.

**Example Usage:**
```lua
vehicles = vehicles.get_all_vehicles_by_mfr(manufacturer)
```


