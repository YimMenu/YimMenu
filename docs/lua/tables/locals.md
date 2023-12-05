# Table: locals

Table for manipulating GTA scripts locals.

## Functions (9)

### `get_int(script, index)`

- **Parameters:**
  - `script` (string): The name of the script
  - `index` (index): Index of the script local.

- **Returns:**
  - `integer`: The value of the given local.

**Example Usage:**
```lua
integer = locals.get_int(script, index)
```

### `get_uint(script, index)`

- **Parameters:**
  - `script` (string): The name of the script
  - `index` (index): Index of the script local.

- **Returns:**
  - `unsigned integer`: The value of the given local.

**Example Usage:**
```lua
unsigned integer = locals.get_uint(script, index)
```

### `get_float(script, index)`

- **Parameters:**
  - `script` (string): The name of the script
  - `index` (index): Index of the script local.

- **Returns:**
  - `float`: The value of the given local.

**Example Usage:**
```lua
float = locals.get_float(script, index)
```

### `get_vec3(script, index)`

- **Parameters:**
  - `script` (string): The name of the script
  - `index` (index): Index of the script local.

- **Returns:**
  - `Vector3`: The value of the given local.

**Example Usage:**
```lua
Vector3 = locals.get_vec3(script, index)
```

### `set_int(script, index, val)`

- **Parameters:**
  - `script` (string): The name of the script
  - `index` (index): Index of the script local.
  - `val` (integer): The new value of the given local.

**Example Usage:**
```lua
locals.set_int(script, index, val)
```

### `set_int(script, index, val)`

- **Parameters:**
  - `script` (string): The name of the script
  - `index` (index): Index of the script local.
  - `val` (unsigned integer): The new value of the given local.

**Example Usage:**
```lua
locals.set_int(script, index, val)
```

### `set_float(script, index, val)`

- **Parameters:**
  - `script` (string): The name of the script
  - `index` (index): Index of the script local.
  - `val` (float): The new value of the given local.

**Example Usage:**
```lua
locals.set_float(script, index, val)
```

### `set_vec3(script, index, val)`

- **Parameters:**
  - `script` (string): The name of the script
  - `index` (index): Index of the script local.
  - `val` (Vector3): The new value of the given local.

**Example Usage:**
```lua
locals.set_vec3(script, index, val)
```

### `get_pointer(script, index)`

- **Parameters:**
  - `script` (string): The name of the script
  - `index` (index): Index of the script local.

- **Returns:**
  - `pointer`: The pointer to the given local.

**Example Usage:**
```lua
pointer = locals.get_pointer(script, index)
```


