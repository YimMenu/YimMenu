# Table: locals

Table for manipulating GTA scripts locals.

## Functions (5)

### `get_int(script, index)`

- **Parameters:**
  - `script` (string): The name of the script
  - `index` (index): Index of the script local.

- **Returns:**
  - `integer`: The value of the given local.

**Exemple Usage:**
```lua
integer = locals.get_int(script, index)
```

### `get_float(script, index)`

- **Parameters:**
  - `script` (string): The name of the script
  - `index` (index): Index of the script local.

- **Returns:**
  - `float`: The value of the given local.

**Exemple Usage:**
```lua
float = locals.get_float(script, index)
```

### `set_int(script, index, val)`

- **Parameters:**
  - `script` (string): The name of the script
  - `index` (index): Index of the script local.
  - `val` (integer): The new value of the given local.

**Exemple Usage:**
```lua
locals.set_int(script, index, val)
```

### `set_float(script, index, val)`

- **Parameters:**
  - `script` (string): The name of the script
  - `index` (index): Index of the script local.
  - `val` (float): The new value of the given local.

**Exemple Usage:**
```lua
locals.set_float(script, index, val)
```

### `get_pointer(script, index)`

- **Parameters:**
  - `script` (string): The name of the script
  - `index` (index): Index of the script local.

- **Returns:**
  - `pointer`: The pointer to the given local.

**Exemple Usage:**
```lua
pointer = locals.get_pointer(script, index)
```


