# Table: script

Table containing helper functions related to gta scripts.

## Functions (7)

### `register_looped(name, func)`

Registers a function that will be looped as a gta script.

- **Parameters:**
  - `name` (string): name of your new looped script
  - `func` (function): function that will be executed in a forever loop.

**Example Usage:**
```lua
script.register_looped("nameOfMyLoopedScript", function (script)
     -- sleep until next game frame
     script:yield()

     local ModelHash = joaat("adder")
     if not STREAMING.IS_MODEL_IN_CDIMAGE(ModelHash) then return end
     STREAMING.REQUEST_MODEL(ModelHash) -- Request the model
     while not STREAMING.HAS_MODEL_LOADED(ModelHash) do -- Waits for the model to load
         script:yield()
     end
     local myPed = PLAYER.PLAYER_PED_ID()
     local myCoords = ENTITY.GET_ENTITY_COORDS(myPed, true)
     -- Spawns a networked vehicle on your current coords
     local spawnedVehicle = VEHICLE.CREATE_VEHICLE(ModelHash, myCoords.x, myCoords.y, myCoords.z, ENTITY.GET_ENTITY_HEADING(myPed), true, false)
     -- removes model from game memory as we no longer need it
     STREAMING.SET_MODEL_AS_NO_LONGER_NEEDED(ModelHash)
     -- sleep for 2s
     script:sleep(2000)
     ENTITY.DELETE_ENTITY(spawnedVehicle)
end)
```

### `run_in_fiber(func)`

Executes a function once inside the fiber pool, you can call natives inside it and yield or sleep.

- **Parameters:**
  - `func` (function): function that will be executed once in the fiber pool.

**Example Usage:**
```lua
script.run_in_fiber(function (script)
     -- sleep until next game frame
     script:yield()

     local ModelHash = joaat("adder")
     if not STREAMING.IS_MODEL_IN_CDIMAGE(ModelHash) then return end
     STREAMING.REQUEST_MODEL(ModelHash) -- Request the model
     while not STREAMING.HAS_MODEL_LOADED(ModelHash) do -- Waits for the model to load
         script:yield()
     end
     local myPed = PLAYER.PLAYER_PED_ID()
     local myCoords = ENTITY.GET_ENTITY_COORDS(myPed, true)
     -- Spawns a networked vehicle on your current coords
     local spawnedVehicle = VEHICLE.CREATE_VEHICLE(ModelHash, myCoords.x, myCoords.y, myCoords.z, ENTITY.GET_ENTITY_HEADING(myPed), true, false)
     -- removes model from game memory as we no longer need it
     STREAMING.SET_MODEL_AS_NO_LONGER_NEEDED(ModelHash)
     -- sleep for 2s
     script:sleep(2000)
     ENTITY.DELETE_ENTITY(spawnedVehicle)
end)
```

### `is_active(script_name)`

Returns true if the specified script is currently active/running.

- **Parameters:**
  - `script_name` (string): The name of the script.

**Example Usage:**
```lua
local is_freemode_active = script.is_active("freemode")
```

### `execute_as_script(script_name, func)`

- **Parameters:**
  - `script_name` (string): Target script thread.
  - `func` (function): Function that will be executed once in the script thread.

**Example Usage:**
```lua
script.execute_as_script(script_name, func)
```

### `add_patch(script_name, name, pattern, offset, _patch)`

Adds a patch for the specified script.

- **Parameters:**
  - `script_name` (string): The name of the script.
  - `name` (string): The name of the patch.
  - `pattern` (string): Pattern to scan for within the script.
  - `offset` (integer): The position within the pattern.
  - `_patch` (table): The bytes to be written into the script's bytecode.

**Example Usage:**
```lua
script.add_patch("fm_content_xmas_truck", "Flickering Fix", "56 ? ? 4F ? ? 40 ? 5D ? ? ? 74", 0, {0x2B, 0x00, 0x00})
```

### `call_function(name, script_name, pattern, offset, _args)`

Calls a function from the specified script.

- **Parameters:**
  - `name` (string): The name of the script function.
  - `script_name` (string): The name of the script.
  - `pattern` (string): The pattern to scan for within the script.
  - `offset` (integer): The position within the pattern.
  - `_args` (table): The arguments to pass to the script function.

**Example Usage:**
```lua
script.call_function("Collect Collectible", "freemode", "2D 05 33 00 00", 0, {17, 0, 1, 1, 0})
```

### `start_launcher_script(script_name)`

Tries to start a launcher script. Needs to be called in the fiber pool or a loop.

- **Parameters:**
  - `name` (string): The name of the script.

**Example Usage:**
```lua
script.run_in_fiber(function()
    script.start_launcher_script("am_hunt_the_beast")
end)
```