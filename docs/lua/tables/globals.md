# Table: globals

Table containing functions for manipulating gta script globals.

## Functions (11)

### `get_int(global)`

Retrieves an int global value.

- **Parameters:**
  - `global` (integer): index of the global

- **Returns:**
  - `integer`: value of the global

**Example Usage:**
```lua
integer = globals.get_int(global)
```

### `get_uint(global)`

Retrieves an uint global value.

- **Parameters:**
  - `global` (integer): index of the global

- **Returns:**
  - `integer`: value of the global

**Example Usage:**
```lua
integer = globals.get_uint(global)
```

### `get_float(global)`

Retrieves a float global value.

- **Parameters:**
  - `global` (integer): index of the global

- **Returns:**
  - `float`: value of the global

**Example Usage:**
```lua
float = globals.get_float(global)
```

### `get_string(global)`

Retrieves a string global value.

- **Parameters:**
  - `global` (integer): index of the global

- **Returns:**
  - `string`: value of the global

**Example Usage:**
```lua
string = globals.get_string(global)
```

### `get_vec3(global)`

Retrieves a Vector3 global value.

- **Parameters:**
  - `global` (integer): index of the global

- **Returns:**
  - `Vector3`: value of the global

**Example Usage:**
```lua
Vector3 = globals.get_vec3(global)
```

### `set_int(global, val)`

Sets an int global value.

- **Parameters:**
  - `global` (integer): index of the global
  - `val` (integer): new value for the global

**Example Usage:**
```lua
globals.set_int(global, val)
```

### `set_uint(global, val)`

Sets an uint global value.

- **Parameters:**
  - `global` (integer): index of the global
  - `val` (integer): new value for the global

**Example Usage:**
```lua
globals.set_uint(global, val)
```

### `set_float(global, val)`

Sets a float global value.

- **Parameters:**
  - `global` (integer): index of the global
  - `val` (float): new value for the global

**Example Usage:**
```lua
globals.set_float(global, val)
```

### `set_string(global, str)`

Sets a string global value.

- **Parameters:**
  - `global` (integer): index of the global
  - `str` (string): new value for the global

**Example Usage:**
```lua
globals.set_string(global, str)
```

### `set_vec3(global, param)`

Sets a Vector3 global value.

- **Parameters:**
  - `global` (integer): index of the global
  - `param` (Vector3): new value for the global

**Example Usage:**
```lua
globals.set_vec3(global, param)
```

### `get_pointer(global)`

Retrieves a pointer global.

- **Parameters:**
  - `global` (integer): index of the global

- **Returns:**
  - `pointer`: value of the global

**Example Usage:**
```lua
pointer = globals.get_pointer(global)
```


