# Table: globals

Table containing functions for manipulating gta script globals.

## Functions (7)

### `get_int(global)`

Retrieves an int global value.

- **Parameters:**
  - `global` (integer): index of the global

- **Returns:**
  - `integer`: value of the global

**Exemple Usage:**
```lua
integer = globals.get_int(global)
```

### `get_float(global)`

Retrieves a float global value.

- **Parameters:**
  - `global` (integer): index of the global

- **Returns:**
  - `float`: value of the global

**Exemple Usage:**
```lua
float = globals.get_float(global)
```

### `get_string(global)`

Retrieves a string global value.

- **Parameters:**
  - `global` (integer): index of the global

- **Returns:**
  - `string`: value of the global

**Exemple Usage:**
```lua
string = globals.get_string(global)
```

### `set_int(global, val)`

Sets an int global value.

- **Parameters:**
  - `global` (integer): index of the global
  - `val` (integer): new value for the global

**Exemple Usage:**
```lua
globals.set_int(global, val)
```

### `set_float(global, val)`

Sets a float global value.

- **Parameters:**
  - `global` (integer): index of the global
  - `val` (float): new value for the global

**Exemple Usage:**
```lua
globals.set_float(global, val)
```

### `set_string(global, str)`

Sets a string global value.

- **Parameters:**
  - `global` (integer): index of the global
  - `str` (string): new value for the global

**Exemple Usage:**
```lua
globals.set_string(global, str)
```

### `get_pointer(global)`

Retrieves a pointer global.

- **Parameters:**
  - `global` (integer): index of the global

- **Returns:**
  - `pointer`: value of the global

**Exemple Usage:**
```lua
pointer = globals.get_pointer(global)
```


