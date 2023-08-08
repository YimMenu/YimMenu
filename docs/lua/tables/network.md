# Table: network

Table containing helper functions for network related features.

## Functions (10)

### `trigger_script_event(bitset, _args)`

Call trigger_script_event (TSE)

- **Parameters:**
  - `bitset` (integer)
  - `_args` (table)

**Example Usage:**
```lua
network.trigger_script_event(bitset, _args)
```

### `give_pickup_rewards(player, reward)`

Give the given pickup reward to the given player.

- **Parameters:**
  - `player` (integer): Index of the player.
  - `reward` (integer): Index of the reward pickup.

**Example Usage:**
```lua
network.give_pickup_rewards(player, reward)
```

### `set_player_coords(player_idx, x, y, z)`

Teleport the given player to the given position.

- **Parameters:**
  - `player_idx` (integer): Index of the player.
  - `x` (float): New x position.
  - `y` (float): New y position.
  - `z` (float): New z position.

**Example Usage:**
```lua
network.set_player_coords(player_idx, x, y, z)
```

### `set_all_player_coords(x, y, z)`

Teleport all players to the given position.

- **Parameters:**
  - `x` (float): New x position.
  - `y` (float): New y position.
  - `z` (float): New z position.

**Example Usage:**
```lua
network.set_all_player_coords(x, y, z)
```

### `get_selected_player()`

- **Returns:**
  - `integer`: Returns the index of the currently selected player in the GUI.

**Example Usage:**
```lua
integer = network.get_selected_player()
```

### `get_selected_database_player_rockstar_id()`

- **Returns:**
  - `integer`: Returns the rockstar id of the currently selected player in the GUI.

**Example Usage:**
```lua
integer = network.get_selected_database_player_rockstar_id()
```

### `flag_player_as_modder(player_idx)`

Flags the given player as a modder in our local database.

- **Parameters:**
  - `player_idx` (integer): Index of the player.

**Example Usage:**
```lua
network.flag_player_as_modder(player_idx)
```

### `is_player_flagged_as_modder(player_idx)`

- **Parameters:**
  - `player_idx` (integer): Index of the player.

- **Returns:**
  - `boolean`: Returns true if the given player is flagged as a modder.

**Example Usage:**
```lua
boolean = network.is_player_flagged_as_modder(player_idx)
```

### `force_script_host(script_name)`

Try to force ourself to be host for the given GTA Script.

- **Parameters:**
  - `script_name` (string): Name of the script

**Example Usage:**
```lua
network.force_script_host(script_name)
```

### `send_chat_message(msg, team_only)`

Sends a message to the in game chat.

- **Parameters:**
  - `msg` (string): Message to be sent.
  - `team_only` (boolean): Should be true if the msg should only be sent to our team.

**Example Usage:**
```lua
network.send_chat_message(msg, team_only)
```


