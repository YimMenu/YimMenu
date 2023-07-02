# Table: tunables

Table for manipulating gta tunables.

## Functions (6)

### `get_int(tunable_name)`

- **Parameters:**
  - `tunable_name` (string): The name of the tunable.

- **Returns:**
  - `integer`: The value of the given tunable.

**Exemple Usage:**
```lua
integer = tunables.get_int(tunable_name)
```

### `get_float(tunable_name)`

- **Parameters:**
  - `tunable_name` (string): The name of the tunable.

- **Returns:**
  - `float`: The value of the given tunable.

**Exemple Usage:**
```lua
float = tunables.get_float(tunable_name)
```

### `get_bool(tunable_name)`

- **Parameters:**
  - `tunable_name` (string): The name of the tunable.

- **Returns:**
  - `boolean`: The value of the given tunable.

**Exemple Usage:**
```lua
boolean = tunables.get_bool(tunable_name)
```

### `set_int(tunable_name, val)`

- **Parameters:**
  - `tunable_name` (string): The name of the tunable.
  - `val` (integer): The new value of the given tunable.

**Exemple Usage:**
```lua
tunables.set_int(tunable_name, val)
```

### `set_float(tunable_name, val)`

- **Parameters:**
  - `tunable_name` (string): The name of the tunable.
  - `val` (float): The new value of the given tunable.

**Exemple Usage:**
```lua
tunables.set_float(tunable_name, val)
```

### `set_bool(tunable_name, val)`

- **Parameters:**
  - `tunable_name` (string): The name of the tunable.
  - `val` (boolean): The new value of the given tunable.

**Exemple Usage:**
```lua
tunables.set_bool(tunable_name, val)
```


