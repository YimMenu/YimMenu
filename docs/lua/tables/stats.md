# Table: stats

Table for manipulating GTA stats.
For stats that get prefixed by either `MP0` or `MP1`, you can use `MPX` instead and the menu will resolve to the correct number automatically.

## Functions (25)

### `get_character_index()`

- **Returns:**
  - `integer`: The current multiplayer character index (0 or 1).

**Example Usage:**
```lua
integer = stats.get_character_index()
```

### `get_bool(stat_hash)`

- **Parameters:**
  - `stat_hash` (integer): the stat hash.

- **Returns:**
  - `boolean`: The value of the given stat.

**Example Usage:**
```lua
boolean = stats.get_bool(stat_hash)
```

### `get_bool(stat_name)`

- **Parameters:**
  - `stat_name` (string): the stat name.

- **Returns:**
  - `boolean`: The value of the given stat.

**Example Usage:**
```lua
boolean = stats.get_bool(stat_name)
```

### `get_bool_masked(stat_hash, bit_index)`

- **Parameters:**
  - `stat_hash` (integer): the stat hash.
  - `bit_index` (integer): bit index.

- **Returns:**
  - `boolean`: The value of the given stat.

**Example Usage:**
```lua
boolean = stats.get_bool_masked(stat_hash, bit_index)
```

### `get_bool_masked(stat_name, bit_index)`

- **Parameters:**
  - `stat_name` (string): the stat name.
  - `bit_index` (integer): bit index.

- **Returns:**
  - `boolean`: The value of the given stat.

**Example Usage:**
```lua
boolean = stats.get_bool_masked(stat_name, bit_index)
```

### `get_float(stat_hash)`

- **Parameters:**
  - `stat_hash` (integer): the stat hash.

- **Returns:**
  - `float`: The value of the given stat.

**Example Usage:**
```lua
float = stats.get_float(stat_hash)
```

### `get_float(stat_name)`

- **Parameters:**
  - `stat_name` (string): the stat name.

- **Returns:**
  - `float`: The value of the given stat.

**Example Usage:**
```lua
float = stats.get_float(stat_name)
```

### `get_int(stat_hash)`

- **Parameters:**
  - `stat_hash` (integer): the stat hash.

- **Returns:**
  - `integer`: The value of the given stat.

**Example Usage:**
```lua
integer = stats.get_int(stat_hash)
```

### `get_int(stat_name)`

- **Parameters:**
  - `stat_name` (string): the stat name.

- **Returns:**
  - `integer`: The value of the given stat.

**Example Usage:**
```lua
integer = stats.get_int(stat_name)
```

### `get_masked_int(stat_hash, bit_start, bit_size)`

- **Parameters:**
  - `stat_hash` (integer): the stat hash.
  - `bit_start` (integer): bit start.
  - `bit_size` (integer): bit size.

- **Returns:**
  - `integer`: The value of the given stat.

**Example Usage:**
```lua
integer = stats.get_masked_int(stat_hash, bit_start, bit_size)
```

### `get_masked_int(stat_name, bit_index, bit_size)`

- **Parameters:**
  - `stat_name` (string): the stat name.
  - `bit_index` (integer): bit index.
  - `bit_size` (integer): bit size.

- **Returns:**
  - `integer`: The value of the given stat.

**Example Usage:**
```lua
integer = stats.get_masked_int(stat_name, bit_index, bit_size)
```

### `set_bool(stat_hash, new_value)`

- **Parameters:**
  - `stat_hash` (integer): the stat hash.
  - `new_value` (boolean): the new value for the stat.

- **Returns:**
  - `boolean`: True if succeeded.

**Example Usage:**
```lua
boolean = stats.set_bool(stat_hash, new_value)
```

### `set_bool(stat_name, new_value)`

- **Parameters:**
  - `stat_name` (string): the stat name.
  - `new_value` (boolean): the new value for the stat.

- **Returns:**
  - `boolean`: True if succeeded.

**Example Usage:**
```lua
boolean = stats.set_bool(stat_name, new_value)
```

### `set_bool_masked(stat_hash, new_value, bit_index)`

- **Parameters:**
  - `stat_hash` (integer): the stat hash.
  - `new_value` (boolean): the new value for the stat.
  - `bit_index` (integer): bit_index.

- **Returns:**
  - `boolean`: True if succeeded.

**Example Usage:**
```lua
boolean = stats.set_bool_masked(stat_hash, new_value, bit_index)
```

### `set_bool_masked(stat_name, new_value, bit_index)`

- **Parameters:**
  - `stat_name` (string): the stat name.
  - `new_value` (boolean): the new value for the stat.
  - `bit_index` (integer): bit_index.

- **Returns:**
  - `boolean`: True if succeeded.

**Example Usage:**
```lua
boolean = stats.set_bool_masked(stat_name, new_value, bit_index)
```

### `set_float(stat_hash, new_value)`

- **Parameters:**
  - `stat_hash` (integer): the stat hash.
  - `new_value` (float): the new value for the stat.

- **Returns:**
  - `boolean`: True if succeeded.

**Example Usage:**
```lua
boolean = stats.set_float(stat_hash, new_value)
```

### `set_float(stat_name, new_value)`

- **Parameters:**
  - `stat_name` (string): the stat name.
  - `new_value` (float): the new value for the stat.

- **Returns:**
  - `boolean`: True if succeeded.

**Example Usage:**
```lua
boolean = stats.set_float(stat_name, new_value)
```

### `set_int(stat_hash, new_value)`

- **Parameters:**
  - `stat_hash` (integer): the stat hash.
  - `new_value` (integer): the new value for the stat.

- **Returns:**
  - `boolean`: True if succeeded.

**Example Usage:**
```lua
boolean = stats.set_int(stat_hash, new_value)
```

### `set_int(stat_name, new_value)`

- **Parameters:**
  - `stat_name` (string): the stat name.
  - `new_value` (integer): the new value for the stat.

- **Returns:**
  - `boolean`: True if succeeded.

**Example Usage:**
```lua
boolean = stats.set_int(stat_name, new_value)
```

### `set_masked_int(stat_hash, new_value, bit_start, bit_size)`

- **Parameters:**
  - `stat_hash` (integer): the stat hash.
  - `new_value` (integer): the new value for the stat.
  - `bit_start` (integer): bit_start.
  - `bit_size` (integer): bit_size.

- **Returns:**
  - `boolean`: True if succeeded.

**Example Usage:**
```lua
boolean = stats.set_masked_int(stat_hash, new_value, bit_start, bit_size)
```

### `set_masked_int(stat_name, new_value, bit_start, bit_size)`

- **Parameters:**
  - `stat_name` (string): the stat name.
  - `new_value` (integer): the new value for the stat.
  - `bit_start` (integer): bit_start.
  - `bit_size` (integer): bit_size.

- **Returns:**
  - `boolean`: True if succeeded.

**Example Usage:**
```lua
boolean = stats.set_masked_int(stat_name, new_value, bit_start, bit_size)
```

### `get_packed_stat_bool(index)`

- **Parameters:**
  - `index` (int): packed stat's index

- **Returns:**
  - `boolean`: Value of the stat.

**Example Usage:**
```lua
boolean = stats.get_packed_stat_bool(index)
```

### `set_packed_stat_bool(index, value)`

- **Parameters:**
  - `index` (int): packed stat's index.
  - `value` (bool): value to set the packed stat to.

**Example Usage:**
```lua
stats.set_packed_stat_bool(index, value)
```

### `get_packed_stat_int(index)`

- **Parameters:**
  - `index` (int): packed stat's index.

- **Returns:**
  - `int`: Value of the stat.

**Example Usage:**
```lua
int = stats.get_packed_stat_int(index)
```

### `set_packed_stat_int(index, value)`

- **Parameters:**
  - `index` (int): packed stat's index.
  - `value` (int): value to set the packed stat to.

**Example Usage:**
```lua
stats.set_packed_stat_int(index, value)
```


