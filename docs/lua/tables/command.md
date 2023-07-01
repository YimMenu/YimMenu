# Table: command

Table for calling menu commands.

## Functions (2)

### `call(command_name, _args)`

Call a menu command.

- **Parameters:**
  - `command_name` (string): The name of the command that will be called.
  - `_args` (table): Optional. List of arguments for the command.

**Exemple Usage:**
```lua
command.call(command_name, _args)
```

### `call_player(player_idx, command_name, _args)`

Call a menu command on a given player.

- **Parameters:**
  - `player_idx` (integer): Index of the player on which the menu command will be executed.
  - `command_name` (string): The name of the command that will be called.
  - `_args` (table): Optional. List of arguments for the command.

**Exemple Usage:**
```lua
command.call_player(player_idx, command_name, _args)
```


