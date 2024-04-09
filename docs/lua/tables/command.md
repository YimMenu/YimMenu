# Table: command

Table for calling menu commands.

## Functions (3)

### `call(command_name, _args)`

Call a menu command.

- **Parameters:**
  - `command_name` (string): The name of the command that will be called.
  - `_args` (table): Optional. List of arguments for the command.

**Example Usage:**
```lua
command.call(command_name, _args)
```

### `call_player(player_idx, command_name, _args)`

Call a menu command on a given player.

- **Parameters:**
  - `player_idx` (integer): Index of the player on which the menu command will be executed.
  - `command_name` (string): The name of the command that will be called.
  - `_args` (table): Optional. List of arguments for the command.

**Example Usage:**
```lua
command.call_player(player_idx, command_name, _args)
```

### `get_all_player_command_names()`

- **Returns:**
  - `table<integer, string>`: Table that contains the names of all the player commands.

**Example Usage:**
```lua
table<integer, string> = command.get_all_player_command_names()
```


